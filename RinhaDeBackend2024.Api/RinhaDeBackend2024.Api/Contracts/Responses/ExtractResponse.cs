using RinhaDeBackend2024.Api.Contracts.Entities;

namespace RinhaDeBackend2024.Api.Contracts.Responses
{
    public sealed class ExtractResponse
    {
        public Customer Saldo { get; set; }
        public List<TransactionResponse> UltimasTransacoes { get; set; }
    }
}
