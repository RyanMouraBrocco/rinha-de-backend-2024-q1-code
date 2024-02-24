using RinhaDeBackend2024.Api.Contracts.Requests;
using RinhaDeBackend2024.Api.DataAccess;
using System.Threading.Channels;

namespace RinhaDeBackend2024.Api.Background
{
    public class TrasactionBackgroundService : BackgroundService
    {
        public static Channel<(int, TransactionRequest)> TransactionChannel { get; } = Channel.CreateUnbounded<(int, TransactionRequest)>();
        private readonly SqlAccess _sqlAccess;

        public TrasactionBackgroundService(IConfiguration configuration)
        {
            var rawConnectionString = configuration.GetConnectionString("Rinha");
            var connectionString = rawConnectionString.Replace("@HOSTNAME", Environment.GetEnvironmentVariable("DB_HOSTNAME"))
                                                      .Replace("@PASSWORD", Environment.GetEnvironmentVariable("DB_PASSWORD"));

            _sqlAccess = new SqlAccess(connectionString, 1);
        }

        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            while (!stoppingToken.IsCancellationRequested)
            {
                var (customerId, transaction) = await TransactionChannel.Reader.ReadAsync();
                _sqlAccess.InsertTransaction(ref customerId, transaction);
            }
        }
    }
}
