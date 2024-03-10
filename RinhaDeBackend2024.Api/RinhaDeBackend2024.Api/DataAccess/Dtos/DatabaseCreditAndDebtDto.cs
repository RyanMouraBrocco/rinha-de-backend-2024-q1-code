using System.Text.Json.Serialization;

namespace RinhaDeBackend2024.Api.DataAccess.Dtos
{
    public sealed class DatabaseCreditAndDebtDto
    {
        [JsonPropertyName("id")]
        public string Id { get; set; }
        [JsonPropertyName("balance")]
        public int Balance { get; set; }
        [JsonPropertyName("description")]
        public string Description { get; set; }
    }
}
