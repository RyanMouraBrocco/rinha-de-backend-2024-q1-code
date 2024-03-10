using Microsoft.AspNetCore.Mvc;
using RinhaDeBackend2024.Api;
using RinhaDeBackend2024.Api.Contracts.Requests;
using RinhaDeBackend2024.Api.Contracts.Responses;
using RinhaDeBackend2024.Api.DataAccess;
using RinhaDeBackend2024.Api.DataAccess.Dtos;
using System.Text.Json.Serialization;

var builder = WebApplication.CreateSlimBuilder(args);

builder.Services.ConfigureHttpJsonOptions(options =>
{
    options.SerializerOptions.TypeInfoResolverChain.Insert(0, AppJsonSerializerContext.Default);
});

#region Services Injections
builder.Services.AddSingleton(new DatabaseAccess("db", 5432));
#endregion

var app = builder.Build();


#region MinimalApi
var customerGroup = app.MapGroup("/clientes");
customerGroup.MapPost("/{id}/transacoes", async ([FromRoute] int id,
                                           [FromServices] DatabaseAccess sqlAccess,
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
        response = sqlAccess.AddInCredit(ref id, ref value, request.Description);
    }
    else
    {
        var value = request.ValueInCents;
        response = sqlAccess.DiscontInDebt(ref id, ref value, request.Description);
        if (response is null)
            return Results.UnprocessableEntity();
    }

    return Results.Ok(response);
});


customerGroup.MapGet("/{id}/extrato", ([FromRoute] int id, [FromServices] DatabaseAccess sqlAccess) =>
{
    if (id > 5 || id < 0)
        return Results.NotFound();

    var extract = sqlAccess.GetCustomerWithLast10TransactionsByCustomerId(ref id);
    extract.Balance.Date = DateTime.UtcNow;
    extract.LastTransactions.Reverse();

    return Results.Ok(extract);
});

app.Run();

#endregion

#region SerializeConfigs
[JsonSerializable(typeof(TransactionRequest[]))]
[JsonSerializable(typeof(TransactionResponse[]))]
[JsonSerializable(typeof(ExtractResponse[]))]
[JsonSerializable(typeof(BalanceResponse[]))]
[JsonSerializable(typeof(DatabaseCreditAndDebtDto[]))]
[JsonSerializable(typeof(DatabaseCommunicationObject[]))]
[JsonSerializable(typeof(DatabaseGetCustomerWithTransactionsDto[]))]
internal partial class AppJsonSerializerContext : JsonSerializerContext;
#endregion