namespace RinhaDeBackend2024.Api.Contracts.Responses
{
    public sealed class TransactionResponse // here could be a unsign integer or maybe somethin with less bytes
    {
        public int ValueInCents { get; set; }
        public char Type { get; set; }
        public string Description { get; set; }
        public DateTime CreateDate { get; set; }
    }
}
