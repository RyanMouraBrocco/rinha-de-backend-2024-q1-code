using System.Text.Json.Serialization;
using RinhaDeBackend2024.Api.Contracts.Entities;

namespace RinhaDeBackend2024.Api.Contracts.Responses
{
    public sealed class ExtractResponse
    {
        [JsonPropertyName("saldo")]
        public CustomerResponse Balance { get; set; }
        [JsonPropertyName("ultimas_transacoes")]
        public List<TransactionResponse> LastTransactions { get; set; }
    }
}
