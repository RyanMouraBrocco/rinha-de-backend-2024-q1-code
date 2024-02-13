using Npgsql;
using RinhaDeBackend2024.Api.Contracts.Entities;
using RinhaDeBackend2024.Api.Contracts.Requests;
using RinhaDeBackend2024.Api.Contracts.Responses;

namespace RinhaDeBackend2024.Api.DataAccess
{
    public sealed class SqlAccess
    {
        private const byte CONNECTION_POOL_LEN = 50;
        private readonly NpgsqlConnection[] _connectionPool;
        private readonly Semaphore[] _connectionLock;
        private byte _connectionSelector;
        public SqlAccess(string connectionString)
        {
            _connectionPool = new NpgsqlConnection[CONNECTION_POOL_LEN];
            _connectionLock = new Semaphore[CONNECTION_POOL_LEN];
            bool someConnectionWorks = false;
            for (byte i = 0; i < CONNECTION_POOL_LEN; i++)
            {
                _connectionPool[i] = new NpgsqlConnection(connectionString);
                _connectionLock[i] = new Semaphore(1, 1);
                while (true)
                {
                    try
                    {
                        _connectionPool[i].Open();
                        someConnectionWorks = true;
                        break;
                    }
                    catch
                    {
                        if (!someConnectionWorks)
                        {
                            Console.WriteLine("Waiting bd starts");
                            Thread.Sleep(2000);
                        }
                        else
                            break;
                    }
                }
            }
            _connectionSelector = 0;
        }

        private (NpgsqlConnection, Semaphore) GetConnection()
        {
            lock (_connectionPool)
            {
                var connection = _connectionPool[_connectionSelector];
                var connectionLock = _connectionLock[_connectionSelector];

                if (_connectionPool[_connectionSelector].State != System.Data.ConnectionState.Open)
                    _connectionPool[_connectionSelector].Open();

                if (_connectionSelector == CONNECTION_POOL_LEN - 1)
                    _connectionSelector = 0;
                else
                    _connectionSelector++;

                return (connection, connectionLock);
            }
        }

        private const string QUERY_GETCUSTOMER_BY_ID = "SELECT Id,\"Limit\",Balance FROM Customer WHERE Id=@Id;";
        public async Task<Customer> GetCustomerByIdAsync(int id)
        {
            var (connection, connectionLock) = GetConnection();

            using var command = new NpgsqlCommand(QUERY_GETCUSTOMER_BY_ID, connection);
            command.Parameters.AddWithValue("Id", id); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value

            try
            {
                connectionLock.WaitOne();
                var result = await command.ExecuteReaderAsync();

                Customer customer = null;

                if (await result.ReadAsync())
                {
                    customer = new Customer()
                    {
                        Id = result.GetInt32(0),
                        Limit = result.GetInt32(1),
                        Balance = result.GetInt32(2)
                    };
                }

                await result.CloseAsync();

                return customer;
            }
            catch
            {
                return null;
            }
            finally
            {
                connectionLock.Release();
            }
        }

        private const string QUERY_INSERT_TRANSACTION = "INSERT INTO Balance_Transaction (CustomerId,ValueInCents,IsCredit,Description,CreateDate)VALUES(@CustomerId,@ValueInCents,@IsCredit,@Description,@CreateDate);";
        public async Task InsertTransactionAsync(int customerId, TransactionRequest transactionRequest)
        {
            var (connection, connectionLock) = GetConnection();

            using var command = new NpgsqlCommand(QUERY_INSERT_TRANSACTION, connection);
            command.Parameters.AddWithValue("CustomerId", customerId); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
            command.Parameters.AddWithValue("ValueInCents", transactionRequest.ValueInCents); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
            command.Parameters.AddWithValue("IsCredit", transactionRequest.Type == 'c'); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
            command.Parameters.AddWithValue("Description", transactionRequest.Description); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
            command.Parameters.AddWithValue("CreateDate", DateTime.Now); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value

            connectionLock.WaitOne();
            try
            {
                _ = await command.ExecuteNonQueryAsync();
            }
            catch
            {
            }
            finally
            {
                connectionLock.Release();
            }
        }

        private const string QUERY_GET_LAST_10_TRANSACTIONS_BY_CUSTOMERID = "SELECT ValueInCents,IsCredit,Description,CreateDate FROM Balance_Transaction WHERE CustomerId=@CustomerId ORDER BY ID DESC LIMIT 10;";
        public async Task<List<TransactionResponse>> GetLast10TransactionsByCustomerIdAsync(int customerId)
        {
            var (connection, connectionLock) = GetConnection();

            using var command = new NpgsqlCommand(QUERY_GET_LAST_10_TRANSACTIONS_BY_CUSTOMERID, connection);
            command.Parameters.AddWithValue("CustomerId", customerId); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value

            connectionLock.WaitOne();
            try
            {
                var result = await command.ExecuteReaderAsync();

                var transactions = new List<TransactionResponse>();

                while (await result.ReadAsync())
                {
                    transactions.Add(new TransactionResponse()
                    {
                        ValueInCents = result.GetInt32(0),
                        Type = result.GetBoolean(1) ? 'c' : 'd',
                        Description = result.GetString(2),
                        CreateDate = result.GetDateTime(3),
                    });
                }

                await result.CloseAsync();

                return transactions;
            }
            catch (Exception)
            {
                return null;
            }
            finally
            {
                connectionLock.Release();
            }

        }

        private const string QUERY_DEBT_PROCEDURE = "SELECT l,b FROM Stp_DebtTransaction(@CustomerId,@Value);";
        public async Task<BalanceResponse> DiscontInDebtAsync(int customerId, int value)
        {
            var (connection, connectionLock) = GetConnection();

            using var command = new NpgsqlCommand(QUERY_DEBT_PROCEDURE, connection);
            command.Parameters.AddWithValue("CustomerId", customerId); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
            command.Parameters.AddWithValue("Value", value); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value

            connectionLock.WaitOne();

            try
            {
                var reader = await command.ExecuteReaderAsync();

                BalanceResponse response = null;

                if (await reader.ReadAsync())
                {
                    response = new BalanceResponse()
                    {
                        Limit = reader.GetInt32(0),
                        Balance = reader.GetInt32(1)
                    };
                }
                await reader.CloseAsync();

                return response;
            }
            catch
            {
                return null;
            }
            finally
            {
                connectionLock.Release();
            }
        }

        private const string QUERY_CREDIT_PROCEDURE = "SELECT l,b FROM Stp_CreditTransaction(@CustomerId,@Value);";
        public async Task<BalanceResponse> AddInCreditAsync(int customerId, int value)
        {
            var (connection, connectionLock) = GetConnection();

            using var command = new NpgsqlCommand(QUERY_CREDIT_PROCEDURE, connection);
            command.Parameters.AddWithValue("CustomerId", customerId); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
            command.Parameters.AddWithValue("Value", value); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value

            connectionLock.WaitOne();
            try
            {
                var reader = await command.ExecuteReaderAsync();

                BalanceResponse response = null;

                if (await reader.ReadAsync())
                {
                    response = new BalanceResponse()
                    {
                        Limit = reader.GetInt32(0),
                        Balance = reader.GetInt32(1)
                    };
                }
                await reader.CloseAsync();

                return response;
            }
            catch
            {
                return null;
            }
            finally
            {
                connectionLock.Release();
            }
        }
    }
}
