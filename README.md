# rinha-de-backend-2024-q1 (Verão Ryan's DB)

Essa versão foi realizada com base na `main` desse mesmo projeto, com o diferencial de que foi criado um Banco de dados próprio (SIM SALVANDO EM DISCO) com a ideia de reduzir as complexidades que um banco de dados de propósito geral tem.

Na pasta `/RyansDB`, você irá encontrar um código em C++ que realiza a criação de conexões TCP/IP para uma determinada porta. Essas conexões esperam um formato JSON que indica qual operação será realizada no banco de dados. A operação é realizada e salva o binário em disco (um arquivo por cliente) usando o protobuf.

# TO DO
* Adicionar tratamento nas conexões para caso uma conexão seja perdida, não derrubar o DB
* Adicionar tratamentos de timeout para recebimento e envio de mensagens
* Adicionar uma forma de inserção de clientes via script
* Adicionar configuração de pool de conexões
* Adicionar configuração de porta do serviço
* Adicionar tratamento de mensagens em formatos errados (BadRequest)
* Adicionar cache dos clientes e transações em memória para o extrato ser mais rápido
* Melhorar a comunicação de JSON para binário (talvez o próprio protobuf ou talvez um MessagePack)