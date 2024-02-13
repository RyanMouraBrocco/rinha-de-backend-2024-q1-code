using Microsoft.AspNetCore.Mvc;
using RinhaDeBackend2024.Api;
using RinhaDeBackend2024.Api.Contracts.Requests;
using RinhaDeBackend2024.Api.Contracts.Responses;
using RinhaDeBackend2024.Api.DataAccess;
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
        request = await httpRequest.ReadFromJsonAsync<TransactionRequest>();
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
        response = await sqlAccess.AddInCreditAsync(id, value);
    }
    else
    {
        var value = request.ValueInCents;
        response = await sqlAccess.DiscontInDebtAsync(id, value);
        if (response is null)
            return Results.UnprocessableEntity();
    }

    await sqlAccess.InsertTransactionAsync(id, request); // this could be in parallel in a queue

    return Results.Ok(response);
});


customerGroup.MapGet("/{id}/extrato", async ([FromRoute] int id, [FromServices] SqlAccess sqlAccess) =>
{
    if (id > 5 || id < 0)
        return Results.NotFound();

    var customer = await sqlAccess.GetCustomerByIdAsync(id);
    var transactions = await sqlAccess.GetLast10TransactionsByCustomerIdAsync(id);

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