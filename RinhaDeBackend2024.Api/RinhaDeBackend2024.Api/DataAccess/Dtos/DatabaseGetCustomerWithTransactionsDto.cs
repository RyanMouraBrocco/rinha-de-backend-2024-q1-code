using System.Text.Json.Serialization;

namespace RinhaDeBackend2024.Api.DataAccess.Dtos
{
    public sealed class DatabaseGetCustomerWithTransactionsDto
    {
        [JsonPropertyName("id")]
        public string Id { get; set; }
    }
}
