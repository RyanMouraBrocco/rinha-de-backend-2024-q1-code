namespace RinhaDeBackend2024.Api.Contracts.Requests
{
    public sealed class TransactionRequest // here could be a unsign integer or maybe somethin with less bytes
    {
        public int ValueInCents;
        public char Type;
        public string Description;
    }
}
