using System.Text.Json.Serialization;

namespace RinhaDeBackend2024.Api.Contracts.Responses
{
    public sealed class TransactionResponse // here could be a unsign integer or maybe somethin with less bytes
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
