using Microsoft.AspNetCore.Mvc;
using RinhaDeBackend2024.Api;
using RinhaDeBackend2024.Api.Contracts.Requests;
using RinhaDeBackend2024.Api.Contracts.Responses;
using RinhaDeBackend2024.Api.DataAccess;
using System.Text;
using System.Text.Json.Serialization;

var builder = WebApplication.CreateSlimBuilder(args);

builder.Services.ConfigureHttpJsonOptions(options =>
{
    options.SerializerOptions.TypeInfoResolverChain.Insert(0, AppJsonSerializerContext.Default);
});

#region Services Injections
var rawConnectionString = builder.Configuration.GetConnectionString("Rinha");
var connectionString = rawConnectionString.Replace("@HOSTNAME", Environment.GetEnvironmentVariable("DB_HOSTNAME"))
                                          .Replace("@PASSWORD", Environment.GetEnvironmentVariable("DB_PASSWORD"));

builder.Services.AddSingleton(new SqlAccess(connectionString));
#endregion

var app = builder.Build();


#region MinimalApi
var customerGroup = app.MapGroup("/clientes");
customerGroup.MapPost("/{id}/transacoes", async ([FromRoute] int id,
                                           [FromServices] SqlAccess sqlAccess,
                                           HttpRequest httpRequest) =>
{
    if (id > 5 || id < 0)
        return Results.NotFound();

    TransactionRequest request = null;

    try
    {
        request = await System.Text.Json.JsonSerializer.DeserializeAsync(httpRequest.Body, AppJsonSerializerContext.Default.TransactionRequest);
        if (request.ValueInCentsCheck % 1 != 0)
            return Results.UnprocessableEntity();

        request.ValueInCents = (int)request.ValueInCentsCheck;
    }
    catch
    {
        return Results.UnprocessableEntity();
    }

    if (request.Type != 'c' && request.Type != 'd')
        return Results.UnprocessableEntity();

    if (request.ValueInCents < 0)
        return Results.UnprocessableEntity();

    if (string.IsNullOrEmpty(request.Description) || request.Description.Length > 10)
        return Results.UnprocessableEntity();

    BalanceResponse response = null;

    if (request.Type == 'c')
    {
        var value = request.ValueInCents;
        response = sqlAccess.AddInCredit(ref id, ref value);
    }
    else
    {
        var value = request.ValueInCents;
        response = sqlAccess.DiscontInDebt(ref id, ref value);
        if (response is null)
            return Results.UnprocessableEntity();
    }

    sqlAccess.InsertTransaction(ref id, request); // this could be in parallel in a queue

    return Results.Ok(response);
});


customerGroup.MapGet("/{id}/extrato", ([FromRoute] int id, [FromServices] SqlAccess sqlAccess) =>
{
    if (id > 5 || id < 0)
        return Results.NotFound();

    var customer = sqlAccess.GetCustomerById(ref id);
    var transactions = sqlAccess.GetLast10TransactionsByCustomerId(ref id);

    return Results.Ok(new ExtractResponse()
    {
        Balance = new CustomerResponse()
        {
            Balance = customer.Balance,
            Date = DateTime.Now,
            Limit = customer.Limit
        },
        LastTransactions = transactions
    });
});

app.Run();

#endregion

#region SerializeConfigs
[JsonSerializable(typeof(TransactionRequest[]))]
[JsonSerializable(typeof(TransactionResponse[]))]
[JsonSerializable(typeof(ExtractResponse[]))]
[JsonSerializable(typeof(BalanceResponse[]))]
internal partial class AppJsonSerializerContext : JsonSerializerContext;
#endregion