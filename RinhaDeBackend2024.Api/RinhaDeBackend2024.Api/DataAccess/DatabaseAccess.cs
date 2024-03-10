using RinhaDeBackend2024.Api.Contracts.Entities;
using RinhaDeBackend2024.Api.Contracts.Requests;
using RinhaDeBackend2024.Api.Contracts.Responses;
using RinhaDeBackend2024.Api.DataAccess.Dtos;
using System;
using System.Net.Sockets;
using System.Text.Json;

namespace RinhaDeBackend2024.Api.DataAccess
{
    public sealed class DatabaseAccess
    {
        private readonly string[] IdConversionCache = ["1", "2", "3", "4", "5"];

        private const byte CONNECTION_POOL_LEN = 20;
        private readonly TcpClient[] _connectionPool;
        private readonly NetworkStream[] _networkPool;
        private byte _connectionSelector;
        private readonly string _connectionHost;
        private readonly int _connectionPort;
        public DatabaseAccess(string connectionHost, int port)
        {
            _connectionHost = connectionHost;
            _connectionPort = port;

            _connectionPool = new TcpClient[CONNECTION_POOL_LEN];
            _networkPool = new NetworkStream[CONNECTION_POOL_LEN];
            bool someConnectionWorks = false;
            for (byte i = 0; i < CONNECTION_POOL_LEN; i++)
            {
                while (true)
                {
                    try
                    {
                        _connectionPool[i] = new TcpClient(connectionHost, port);
                        _networkPool[i] = _connectionPool[i].GetStream();
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

        private NetworkStream GetConnection()
        {
            lock (_connectionPool)
            {
                if (!_connectionPool[_connectionSelector].Connected)
                {
                    _connectionPool[_connectionSelector].Connect(_connectionHost, _connectionPort);
                    _networkPool[_connectionSelector] = _connectionPool[_connectionSelector].GetStream();
                }

                var connection = _connectionPool[_connectionSelector];
                var stream = _networkPool[_connectionSelector];

                if (_connectionSelector == CONNECTION_POOL_LEN - 1)
                    _connectionSelector = 0;
                else
                    _connectionSelector++;

                return stream;
            }
        }

        public ExtractResponse GetCustomerWithLast10TransactionsByCustomerId(ref readonly int customerId)
        {
            var connection = GetConnection();


            lock (connection)
            {
                var dataCommunitationObject = new DatabaseCommunicationObject()
                {
                    EndPoint = "GetCustomersWithJoinInTransactions",
                    Data = System.Text.Json.JsonSerializer.Serialize(new DatabaseGetCustomerWithTransactionsDto()
                    {
                        Id = IdConversionCache[customerId - 1],
                    }, AppJsonSerializerContext.Default.DatabaseGetCustomerWithTransactionsDto)
                };

                byte[] data = System.Text.Encoding.ASCII.GetBytes(JsonSerializer.Serialize(dataCommunitationObject, AppJsonSerializerContext.Default.DatabaseCommunicationObject));
                connection.Write(data, 0, data.Length);
                data = new byte[4096];
                int bytes = connection.Read(data, 0, data.Length);
                return JsonSerializer.Deserialize(System.Text.Encoding.ASCII.GetString(data, 0, bytes), AppJsonSerializerContext.Default.ExtractResponse);
            }
        }

        public BalanceResponse DiscontInDebt(ref readonly int customerId, ref readonly int value, string description)
        {
            var connection = GetConnection();

            lock (connection)
            {
                var dataCommunitationObject = new DatabaseCommunicationObject()
                {
                    EndPoint = "DebtTransaction",
                    Data = System.Text.Json.JsonSerializer.Serialize(new DatabaseCreditAndDebtDto()
                    {
                        Id = IdConversionCache[customerId - 1],
                        Balance = value,
                        Description = description
                    }, AppJsonSerializerContext.Default.DatabaseCreditAndDebtDto)
                };

                byte[] data = System.Text.Encoding.ASCII.GetBytes(JsonSerializer.Serialize(dataCommunitationObject, AppJsonSerializerContext.Default.DatabaseCommunicationObject));
                connection.Write(data, 0, data.Length);
                data = new byte[4096];
                int bytes = connection.Read(data, 0, data.Length);
                var textResult = System.Text.Encoding.ASCII.GetString(data, 0, bytes);
                if (textResult == "InvalidOp")
                    return null;

                return JsonSerializer.Deserialize(textResult, AppJsonSerializerContext.Default.BalanceResponse);
            }
        }

        public BalanceResponse AddInCredit(ref readonly int customerId, ref readonly int value, string description)
        {
            var connection = GetConnection();

            lock (connection)
            {
                var dataCommunitationObject = new DatabaseCommunicationObject()
                {
                    EndPoint = "CreditTransaction",
                    Data = System.Text.Json.JsonSerializer.Serialize(new DatabaseCreditAndDebtDto()
                    {
                        Id = IdConversionCache[customerId - 1],
                        Balance = value,
                        Description = description
                    }, AppJsonSerializerContext.Default.DatabaseCreditAndDebtDto)
                };

                byte[] data = System.Text.Encoding.ASCII.GetBytes(JsonSerializer.Serialize(dataCommunitationObject, AppJsonSerializerContext.Default.DatabaseCommunicationObject));
                connection.Write(data, 0, data.Length);
                data = new byte[4096];
                int bytes = connection.Read(data, 0, data.Length);
                return JsonSerializer.Deserialize(System.Text.Encoding.ASCII.GetString(data, 0, bytes), AppJsonSerializerContext.Default.BalanceResponse);
            }
        }
    }
}
