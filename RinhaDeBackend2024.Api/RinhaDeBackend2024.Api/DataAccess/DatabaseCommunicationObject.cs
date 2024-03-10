using System.Text.Json.Serialization;

namespace RinhaDeBackend2024.Api.DataAccess
{
    public sealed class DatabaseCommunicationObject
    {
        [JsonPropertyName("e")]
        public string EndPoint { get; set; }
        [JsonPropertyName("d")]
        public string Data { get; set; }
    }
}
