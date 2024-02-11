using System.Text.Json.Serialization;

namespace RinhaDeBackend2024.Api;

public sealed class CustomerResponse
{
        [JsonPropertyName("limite")]
        public int Limit { get; set; }
        [JsonPropertyName("data_extrato")]
        public DateTime Date { get; set; }
        [JsonPropertyName("total")]
        public int Balance { get; set; }
}
