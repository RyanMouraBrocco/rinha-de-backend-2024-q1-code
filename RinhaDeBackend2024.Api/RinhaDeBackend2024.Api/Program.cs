using Microsoft.AspNetCore.Mvc;
using Microsoft.Data.SqlClient;
using System.Text.Json.Serialization;

var builder = WebApplication.CreateSlimBuilder(args);

builder.Services.ConfigureHttpJsonOptions(options =>
{
    options.SerializerOptions.TypeInfoResolverChain.Insert(0, AppJsonSerializerContext.Default);
});

builder.Services.AddSingleton(new SqlAccess(new SqlConnection(builder.Configuration.GetConnectionString("Rinha"))));

var app = builder.Build();


#region MinimalApi
var customerGroup = app.MapGroup("/clientes");
customerGroup.MapPost("/{id}/transacoes", ([FromRoute] int id,
                                           [FromBody] TransactionRequest request,
                                           [FromServices] SqlAccess sqlAccess) =>
{
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


customerGroup.MapGet("/{id}/extrato", ([FromRoute] int id, [FromServices] SqlAccess sqlAccess) =>
{
    var customer = sqlAccess.GetCustomerById(ref id);
    if (customer is null)
        return Results.NotFound();

    var transactions = sqlAccess.GetLast10TransactionsByCustomerId(ref id);

    return Results.Ok(new ExtractResponse(customer, transactions));
});

app.Run();

#endregion




#region Contracts
public record TransactionRequest(int ValueInCents, char Type, string Description); // here could be a unsign integer or maybe somethin with less bytes
public record TransactionResponse(int ValueInCents, char Type, string Description, DateTime CreateDate); // here could be a unsign integer or maybe somethin with less bytes
public record ExtractResponse(Customer Saldo, List<TransactionResponse> UltimasTransacoes);
public record Customer(int Id, int Limit, int Balance); // same here
#endregion


#region SerializeConfigs
[JsonSerializable(typeof(TransactionRequest[]))]
[JsonSerializable(typeof(TransactionResponse[]))]
[JsonSerializable(typeof(ExtractResponse[]))]
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

    private const string QUERY_GETCUSTOMER_BY_ID = "SELECT Id,Limit,Balance FROM[Customer](NOLOCK)WHERE Id=@Id";
    public Customer GetCustomerById(ref readonly int id)
    {
        if (_connection.State != System.Data.ConnectionState.Open)
            _connection.Open();

        var command = new SqlCommand(QUERY_GETCUSTOMER_BY_ID, _connection);
        command.Parameters.AddWithValue("Id", id); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
        var result = command.ExecuteReader();

        Customer customer = null;

        if (result.Read())
        {
            customer = new Customer(result.GetInt32(0), result.GetInt32(1), result.GetInt32(2));
        }

        result.Close();

        return customer;
    }

    private const string QUERY_INSERT_TRANSACTION = "INSERT INTO[Balance_Transaction]VALUES(@CustomerId,@ValuesInCents,@IsCredit,@Description,@CreateDate)";
    public void InsertTransaction(ref readonly int customerId, TransactionRequest transactionRequest)
    {
        if (_connection.State != System.Data.ConnectionState.Open)
            _connection.Open();

        var command = new SqlCommand(QUERY_INSERT_TRANSACTION, _connection);
        command.Parameters.AddWithValue("CustomerId", customerId); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
        command.Parameters.AddWithValue("ValuesInCents", transactionRequest.ValueInCents); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
        command.Parameters.AddWithValue("IsCredit", transactionRequest.Type == 'c'); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
        command.Parameters.AddWithValue("Description", transactionRequest.Description); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
        command.Parameters.AddWithValue("CreateDate", DateTime.Now); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
        _ = command.ExecuteNonQuery();
    }

    private const string QUERY_GET_LAST_10_TRANSACTIONS_BY_CUSTOMERID = "SELECT TOP 10ValueInCents,IsCredit,[Description],CreateDate FROM[Balance_Transaction](NOLOCK)WHERE CustomerId=1";
    public List<TransactionResponse> GetLast10TransactionsByCustomerId(ref readonly int customerId)
    {
        if (_connection.State != System.Data.ConnectionState.Open)
            _connection.Open();

        var command = new SqlCommand(QUERY_GET_LAST_10_TRANSACTIONS_BY_CUSTOMERID, _connection);
        command.Parameters.AddWithValue("CustomerId", customerId); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value

        var result = command.ExecuteReader();

        var transactions = new List<TransactionResponse>();

        while (result.Read())
        {
            transactions.Add(new TransactionResponse(result.GetInt32(0), result.GetBoolean(1) ? 'c' : 'd', result.GetString(2), result.GetDateTime(3)));
        }

        result.Close();

        return transactions;
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
