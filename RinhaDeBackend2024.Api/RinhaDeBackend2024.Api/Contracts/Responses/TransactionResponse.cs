namespace RinhaDeBackend2024.Api.Contracts.Responses
{
    public sealed class TransactionResponse // here could be a unsign integer or maybe somethin with less bytes
    {
        public int ValueInCents;
        public char Type;
        public string Description;
        public DateTime CreateDate;
    }
}
