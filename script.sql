CREATE DATABASE Rinha
GO
USE Rinha
GO
CREATE TABLE Customer
(
 Id INT IDENTITY NOT NULL PRIMARY KEY,
 Limit INT NOT NULL,
 Balance INT NOT NULL
)
GO
CREATE TABLE [Balance_Transaction]
(
 Id INT IDENTITY NOT NULL PRIMARY KEY,
 CustomerId INT NOT NULL,
 ValueInCents INT NOT NULL,
 IsCredit BIT NOT NULL,
 [Description] NVARCHAR(10) NOT NULL,
 CreateDate DATETIME NOT NULL
)
GO
ALTER TABLE [Balance_Transaction] ADD CONSTRAINT [FK_Balance_Transaction_Customer] FOREIGN KEY (CustomerId) References Customer(Id)
GO
CREATE PROCEDURE Stp_DebtTransaction 
(
	@CustomerId INT,
	@Value INT
)
AS
BEGIN
	SET NOCOUNT ON
	
	DECLARE @TmpTable TABLE (Limit INT NOT NULL, Balance INT NOT NULL)

	UPDATE Customer
	SET Balance = Balance - @Value
	OUTPUT INSERTED.Limit, INSERTED.Balance INTO @TmpTable
	WHERE Id = @CustomerId AND (Balance - @Value) >= -Limit
	
	SELECT Limit, Balance FROM @TmpTable
END
GO
CREATE PROCEDURE Stp_CreditTransaction 
(
	@CustomerId INT,
	@Value INT
)
AS
BEGIN
	SET NOCOUNT ON
	DECLARE @TmpTable TABLE (Limit INT NOT NULL, Balance INT NOT NULL)
	UPDATE Customer
	SET Balance = Balance + @Value
	OUTPUT INSERTED.Limit, INSERTED.Balance INTO @TmpTable
	WHERE Id = @CustomerId
	
	SELECT Limit, Balance FROM @TmpTable
END
GO
INSERT INTO Customer VALUES (100000, 0)
INSERT INTO Customer VALUES (80000, 0)
INSERT INTO Customer VALUES (1000000, 0)
INSERT INTO Customer VALUES (10000000, 0)
INSERT INTO Customer VALUES (500000, 0)
GO