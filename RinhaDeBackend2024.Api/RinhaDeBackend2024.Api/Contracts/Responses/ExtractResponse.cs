using RinhaDeBackend2024.Api.Contracts.Entities;

namespace RinhaDeBackend2024.Api.Contracts.Responses
{
    public sealed class ExtractResponse
    {
        public Customer Saldo;
        public List<TransactionResponse> UltimasTransacoes;
    }
}
