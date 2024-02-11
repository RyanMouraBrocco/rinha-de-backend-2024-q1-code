using Microsoft.Data.SqlClient;
using RinhaDeBackend2024.Api.Contracts.Entities;
using RinhaDeBackend2024.Api.Contracts.Requests;
using RinhaDeBackend2024.Api.Contracts.Responses;

namespace RinhaDeBackend2024.Api.DataAccess
{
    public sealed class SqlAccess
    {
        private const byte CONNECTION_POOL_LEN = 80;
        private readonly SqlConnection[] _connectionPool;
        private byte _connectionSelector;
        public SqlAccess(string connectionString)
        {
            _connectionPool = new SqlConnection[CONNECTION_POOL_LEN];
            for (byte i = 0; i < CONNECTION_POOL_LEN; i++)
            {
                _connectionPool[i] = new SqlConnection(connectionString);
            }
            _connectionSelector = 0;
        }

        private SqlConnection GetConnection()
        {
            lock (_connectionPool)
            {
                var connection = _connectionPool[_connectionSelector];

                if (_connectionPool[_connectionSelector].State != System.Data.ConnectionState.Open)
                    _connectionPool[_connectionSelector].Open();

                if (_connectionSelector == CONNECTION_POOL_LEN - 1)
                    _connectionSelector = 0;
                else
                    _connectionSelector++;

                return connection;
            }
        }

        private const string QUERY_GETCUSTOMER_BY_ID = "SELECT Id,Limit,Balance FROM[Customer](NOLOCK)WHERE Id=@Id";
        public Customer GetCustomerById(ref readonly int id)
        {
            var connection = GetConnection();

            var command = new SqlCommand(QUERY_GETCUSTOMER_BY_ID, connection);
            command.Parameters.AddWithValue("Id", id); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value

            lock (connection)
            {
                var result = command.ExecuteReader();

                Customer customer = null;

                if (result.Read())
                {
                    customer = new Customer()
                    {
                        Id = result.GetInt32(0),
                        Limit = result.GetInt32(1),
                        Balance = result.GetInt32(2)
                    };
                }

                result.Close();

                return customer;
            }
        }

        private const string QUERY_INSERT_TRANSACTION = "INSERT INTO[Balance_Transaction]VALUES(@CustomerId,@ValuesInCents,@IsCredit,@Description,@CreateDate)";
        public void InsertTransaction(ref readonly int customerId, TransactionRequest transactionRequest)
        {
            var connection = GetConnection();

            var command = new SqlCommand(QUERY_INSERT_TRANSACTION, connection);
            command.Parameters.AddWithValue("CustomerId", customerId); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
            command.Parameters.AddWithValue("ValuesInCents", transactionRequest.ValueInCents); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
            command.Parameters.AddWithValue("IsCredit", transactionRequest.Type == 'c'); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
            command.Parameters.AddWithValue("Description", transactionRequest.Description); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
            command.Parameters.AddWithValue("CreateDate", DateTime.Now); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value

            lock (connection)
                _ = command.ExecuteNonQuery();
        }

        private const string QUERY_GET_LAST_10_TRANSACTIONS_BY_CUSTOMERID = "SELECT TOP 10ValueInCents,IsCredit,[Description],CreateDate FROM[Balance_Transaction](NOLOCK)WHERE CustomerId=1 ORDER BY ID DESC";
        public List<TransactionResponse> GetLast10TransactionsByCustomerId(ref readonly int customerId)
        {
            var connection = GetConnection();

            var command = new SqlCommand(QUERY_GET_LAST_10_TRANSACTIONS_BY_CUSTOMERID, connection);
            command.Parameters.AddWithValue("CustomerId", customerId); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value


            lock (connection)
            {
                var result = command.ExecuteReader();

                var transactions = new List<TransactionResponse>();

                while (result.Read())
                {
                    transactions.Add(new TransactionResponse()
                    {
                        ValueInCents = result.GetInt32(0),
                        Type = result.GetBoolean(1) ? 'c' : 'd',
                        Description = result.GetString(2),
                        CreateDate = result.GetDateTime(3),
                    });
                }

                result.Close();

                return transactions;
            }
        }

        public BalanceResponse DiscontInDebt(ref readonly int customerId, ref readonly int value)
        {
            var connection = GetConnection();

            var command = new SqlCommand("[Stp_DebtTransaction]", connection);
            command.CommandType = System.Data.CommandType.StoredProcedure;

            command.Parameters.AddWithValue("CustomerId", customerId); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
            command.Parameters.AddWithValue("Value", value); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value

            lock (connection)
            {
                var reader = command.ExecuteReader();

                BalanceResponse response = null;

                if (reader.Read())
                {
                    response = new BalanceResponse()
                    {
                        Limit = reader.GetInt32(0),
                        Balance = reader.GetInt32(1)
                    };
                }
                reader.Close();

                return response;
            }
        }

        public BalanceResponse AddInCredit(ref readonly int customerId, ref readonly int value)
        {
            var connection = GetConnection();

            var command = new SqlCommand("[Stp_CreditTransaction]", connection);
            command.CommandType = System.Data.CommandType.StoredProcedure;

            command.Parameters.AddWithValue("CustomerId", customerId); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value
            command.Parameters.AddWithValue("Value", value); // I belive is possible to improve performance here, because here the AddWithValue is accepting a object and could be the excat value

            lock (connection)
            {
                var reader = command.ExecuteReader();

                BalanceResponse response = null;

                if (reader.Read())
                {
                    response = new BalanceResponse()
                    {
                        Limit = reader.GetInt32(0),
                        Balance = reader.GetInt32(1)
                    };
                }
                reader.Close();

                return response;
            }
        }
    }
}
