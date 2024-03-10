using System.Text.Json.Serialization;

namespace RinhaDeBackend2024.Api.Contracts.Responses
{
    public sealed class TransactionResponse
    {
        [JsonPropertyName("valor")]
        public int ValueInCents { get; set; }
        [JsonPropertyName("tipo")]
        public char Type { get; set; }
        [JsonPropertyName("descricao")]
        public string Description { get; set; }
        [JsonPropertyName("realizada_em")]
        public DateTime CreateDate { get; set; }
    }
}
