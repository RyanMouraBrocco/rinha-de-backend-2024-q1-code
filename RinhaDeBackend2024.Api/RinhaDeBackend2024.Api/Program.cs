using Microsoft.AspNetCore.Mvc;
using Microsoft.Data.SqlClient;
using System.Text.Json.Serialization;

var builder = WebApplication.CreateSlimBuilder(args);

builder.Services.ConfigureHttpJsonOptions(options =>
{
    options.SerializerOptions.TypeInfoResolverChain.Insert(0, AppJsonSerializerContext.Default);
});

var app = builder.Build();


#region MinimalApi
var customerGroup = app.MapGroup("/clientes");
customerGroup.MapPost("/{id}/transacoes", (int id, [FromBody] TransactionRequest request) =>
{
    var sqlAccess = new SqlAccess(new SqlConnection());

    var contactCheck = sqlAccess.GetCustomerById(ref id);
    if (contactCheck is null)
        return Results.NotFound();


    // i need to understand better to create the validations rules here
    if (request.Type == 'c')
    {
        // no idea man
    }
    else
    {
        var value = request.ValueInCents;
        if (!sqlAccess.DiscontInDebt(ref id, ref value))
            return Results.StatusCode(422);
    }


    sqlAccess.InsertTransaction(ref id, request); // this could be in parallel in a queue

    return Results.Ok();
});

app.Run();

#endregion


#region Contracts
public record TransactionRequest(int ValueInCents, char Type, string Description); // here could be a unsign integer or maybe somethin with less bytes
public record Customer(int Id, int Limit, int Balance); // same here
#endregion


#region SerializeConfigs
[JsonSerializable(typeof(TransactionRequest[]))]
internal partial class AppJsonSerializerContext : JsonSerializerContext;
#endregion

#region SqlConnection
internal class SqlAccess
{
    private readonly SqlConnection _connection;
    public SqlAccess(SqlConnection connection)
    {
        _connection = connection;
    }

    public Customer GetCustomerById(ref readonly int id)
    {
        if (_connection.State != System.Data.ConnectionState.Open)
            _connection.Open();

        var command = new SqlCommand("SELECT Id, Limit, Balance FROM [Customer] (nolock) WHERE Id = @Id", _connection);
        command.Parameters.AddWithValue("Id", id); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
        var result = command.ExecuteReader();

        Customer customer = null;

        if (result.Read())
        {
            customer = new Customer(result.GetInt32(0), result.GetInt32(1), result.GetInt32(2));
        }

        return customer;
    }

    public void InsertTransaction(ref readonly int customerId, TransactionRequest transactionRequest)
    {
        if (_connection.State != System.Data.ConnectionState.Open)
            _connection.Open();

        var command = new SqlCommand("INSERT INTO [Balance_Transaction] VALUES (@CustomerId, @ValuesInCents, @IsCredit, @Description, @CreateDate)", _connection);
        command.Parameters.AddWithValue("CustomerId", customerId); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
        command.Parameters.AddWithValue("ValuesInCents", transactionRequest.ValueInCents); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
        command.Parameters.AddWithValue("IsCredit", transactionRequest.Type == 'c'); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
        command.Parameters.AddWithValue("Description", transactionRequest.Description); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
        command.Parameters.AddWithValue("CreateDate", DateTime.Now); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
        _ = command.ExecuteNonQuery();
    }

    public bool DiscontInDebt(ref readonly int customerId, ref readonly int value)
    {
        if (_connection.State != System.Data.ConnectionState.Open)
            _connection.Open();

        var command = new SqlCommand("[Stp_DebtTransaction]", _connection);
        command.CommandType = System.Data.CommandType.StoredProcedure;

        command.Parameters.AddWithValue("CustomerId", customerId); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
        command.Parameters.AddWithValue("Value", value); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
        return (int)command.ExecuteScalar() > 1;
    }
}

#endregion
