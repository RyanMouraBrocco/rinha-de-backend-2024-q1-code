using System.Text.Json.Serialization;

namespace RinhaDeBackend2024.Api;

public sealed class BalanceResponse
{
    [JsonPropertyName("limite")]
    public int Limit { get; set; }
    [JsonPropertyName("saldo")]
    public int Balance { get; set; }
}
