using Microsoft.AspNetCore.Mvc;
using Microsoft.Data.SqlClient;
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
builder.Services.AddSingleton(new SqlAccess(new SqlConnection(builder.Configuration.GetConnectionString("Rinha"))));
#endregion

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

    return Results.Ok(new ExtractResponse()
    {
        Saldo = customer,
        UltimasTransacoes = transactions
    });
});

app.Run();

#endregion


#region SerializeConfigs
[JsonSerializable(typeof(TransactionRequest[]))]
[JsonSerializable(typeof(TransactionResponse[]))]
[JsonSerializable(typeof(ExtractResponse[]))]
internal partial class AppJsonSerializerContext : JsonSerializerContext;
#endregion