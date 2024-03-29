﻿using System.Text.Json.Serialization;

namespace RinhaDeBackend2024.Api.Contracts.Requests
{
    public sealed class TransactionRequest // here could be a unsign integer or maybe somethin with less bytes
    {
        [JsonPropertyName("valor")]
        public int ValueInCents { get; set; }
        [JsonPropertyName("tipo")]
        public char Type { get; set; }
        [JsonPropertyName("descricao")]
        public string Description { get; set; }
    }
}
