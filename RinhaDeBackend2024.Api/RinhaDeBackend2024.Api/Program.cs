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

    TransactionRequest request = await TransactionSerialize(httpRequest);
    if (request is null)
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

async Task<TransactionRequest> TransactionSerialize(HttpRequest request)
{
    string bodyText = null;
    using (var bodyStream = new StreamReader(request.Body))
    {
        bodyText = await bodyStream.ReadToEndAsync();
    }

    if (string.IsNullOrEmpty(bodyText))
        return null;

    string valueInCents = null;
    char type = '\0';
    string description = null;

    byte propertyToBeSet = 1;
    /*
        propertyToBeSet 1 = valueInCents
        propertyToBeSet 2 = type
        propertyToBeSet 3 = description
     */

    byte status = 1;
    /*
        Status 1 = Looking for a { to start the objet.
        Status 2 = Looking for a " of property name
        Status 3 = Gathering the property name
        Status 4 = Looking for the :
        Status 5 = Looking for a " of value or for a number
        Status 6 = Setting value in variable
        Status 7 = Looking for the , or for the }
        Status 8 = Jumping the property
        Status 9 = Jumping to the end
     */

    StringBuilder stringBuilder = new StringBuilder();
    bool valueIsString = false;
    bool jsonFinished = false;

    for (int i = 0; i < bodyText.Length;)
    {
        if (bodyText[i] == '\r' || bodyText[i] == '\n')
        {
            i++;
            continue;
        }

        if (status == 1)
        {
            if (bodyText[i] != ' ')
            {
                if (bodyText[i] == '{')
                    status = 2;
                else
                    return null;
            }
        }
        else if (status == 2)
        {
            if (bodyText[i] != ' ')
            {
                if (bodyText[i] == '"')
                    status = 3;
                else
                    return null;
            }
        }
        else if (status == 3)
        {
            if (bodyText[i] == '"')
                status = 4;
            else
            {
                var sizeLeft = bodyText.Length - (i + 1);
                if (sizeLeft >= 6 &&
                    bodyText[i] == 'v' &&
                    bodyText[i + 1] == 'a' &&
                    bodyText[i + 2] == 'l' &&
                    bodyText[i + 3] == 'o' &&
                    bodyText[i + 4] == 'r' &&
                    bodyText[i + 5] == '"')
                {
                    if (valueInCents is null)
                    {
                        propertyToBeSet = 1;
                        i += 6;
                        status = 4;
                        continue;
                    }
                    else
                        return null;
                }
                else if (sizeLeft >= 5 &&
                    bodyText[i] == 't' &&
                    bodyText[i + 1] == 'i' &&
                    bodyText[i + 2] == 'p' &&
                    bodyText[i + 3] == 'o' &&
                    bodyText[i + 4] == '"')
                {
                    if (type == '\0')
                    {
                        propertyToBeSet = 2;
                        i += 5;
                        status = 4;
                        continue;
                    }
                    else
                        return null;
                }
                else if (sizeLeft >= 10 &&
                    bodyText[i] == 'd' &&
                    bodyText[i + 1] == 'e' &&
                    bodyText[i + 2] == 's' &&
                    bodyText[i + 3] == 'c' &&
                    bodyText[i + 4] == 'r' &&
                    bodyText[i + 5] == 'i' &&
                    bodyText[i + 6] == 'c' &&
                    bodyText[i + 7] == 'a' &&
                    bodyText[i + 8] == 'o' &&
                    bodyText[i + 9] == '"')
                {
                    if (description is null)
                    {
                        propertyToBeSet = 3;
                        i += 10;
                        status = 4;
                        continue;
                    }
                    else
                        return null;
                }
                else
                    status = 8;
            }
        }
        else if (status == 4)
        {
            if (bodyText[i] != ' ')
            {
                if (bodyText[i] == ':')
                    status = 5;
                else
                    return null;
            }
        }
        else if (status == 5)
        {
            if (bodyText[i] != ' ')
            {
                if (bodyText[i] == '"')
                {
                    valueIsString = true;
                    stringBuilder.Clear();
                    status = 6;
                }
                else if (bodyText[i] >= 48 && bodyText[i] <= 57)
                {
                    valueIsString = false;
                    stringBuilder.Clear();
                    stringBuilder.Append(bodyText[i]);
                    status = 6;
                }
                else
                    return null;
            }
        }
        else if (status == 6)
        {
            if (propertyToBeSet == 1)
            {
                if (valueIsString)
                    return null;

                if (bodyText[i] == ' ')
                {
                    if (stringBuilder.Length == 0)
                        return null;

                    valueInCents = stringBuilder.ToString();
                    status = 7;
                }
                else if (bodyText[i] == ',')
                {
                    if (stringBuilder.Length == 0)
                        return null;

                    valueInCents = stringBuilder.ToString();
                    status = 2;
                }
                else if (bodyText[i] == '}')
                {
                    if (stringBuilder.Length == 0)
                        return null;

                    valueInCents = stringBuilder.ToString();
                    status = 9;
                    jsonFinished = true;
                }
                else if (bodyText[i] >= 48 && bodyText[i] <= 57)
                {
                    stringBuilder.Append(bodyText[i]);
                }
                else
                    return null;
            }
            else if (propertyToBeSet == 2)
            {
                if (!valueIsString)
                    return null;

                if (bodyText[i] == '"')
                {
                    if (stringBuilder.Length != 1)
                        return null;

                    type = stringBuilder[0];
                    if (type != 'c' && type != 'd')
                        return null;

                    status = 7;
                }
                else if (bodyText[i] == ',')
                {
                    if (stringBuilder.Length != 1)
                        return null;

                    type = stringBuilder[0];
                    if (type != 'c' && type != 'd')
                        return null;

                    status = 2;
                }
                else if (bodyText[i] == '}')
                {
                    if (stringBuilder.Length != 1)
                        return null;

                    type = stringBuilder[0];
                    if (type != 'c' && type != 'd')
                        return null;

                    status = 9;
                    jsonFinished = true;
                }
                else
                {
                    stringBuilder.Append(bodyText[i]);
                }
            }
            else if (propertyToBeSet == 3)
            {
                if (!valueIsString)
                    return null;

                if (bodyText[i] == '"')
                {
                    if (stringBuilder.Length > 10 || stringBuilder.Length == 0)
                        return null;

                    description = stringBuilder.ToString();
                    status = 7;
                }
                else if (bodyText[i] == ',')
                {
                    if (stringBuilder.Length > 10 || stringBuilder.Length == 0)
                        return null;

                    description = stringBuilder.ToString();
                    status = 2;
                }
                else if (bodyText[i] == '}')
                {
                    if (stringBuilder.Length > 10 || stringBuilder.Length == 0)
                        return null;

                    description = stringBuilder.ToString();
                    status = 9;
                    jsonFinished = true;
                }
                else
                {
                    stringBuilder.Append(bodyText[i]);
                }
            }
            else
                return null;
        }
        else if (status == 7)
        {
            if (bodyText[i] != ' ')
            {
                if (bodyText[i] == ',')
                    status = 2;
                else if (bodyText[i] == '}')
                {
                    jsonFinished = true;
                    status = 9;
                }
                else
                    return null;
            }
        }
        else if (status == 8)
        {
            return null;
        }
        else if (status == 9)
        {
            if (bodyText[i] != ' ')
                return null;
        }
        else
            return null;

        i++;
    }

    if (jsonFinished && valueInCents != null && type != '\0' && description != null)
    {
        return new TransactionRequest()
        {
            Description = description,
            Type = type,
            ValueInCents = int.Parse(valueInCents)
        };
    }
    else
        return null;
}


[JsonSerializable(typeof(TransactionRequest[]))]
[JsonSerializable(typeof(TransactionResponse[]))]
[JsonSerializable(typeof(ExtractResponse[]))]
[JsonSerializable(typeof(BalanceResponse[]))]
internal partial class AppJsonSerializerContext : JsonSerializerContext;
#endregion