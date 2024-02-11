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
ALTER PROCEDURE Stp_DebtTransaction 
(
	@CustomerId INT,
	@Value INT
)
AS
BEGIN
	SET NOCOUNT ON
	UPDATE Customer
	SET Balance = Balance - @Value
	WHERE Id = @CustomerId AND (Balance - @Value) >= -Limit
	SELECT @@ROWCOUNT
END
GO
INSERT INTO Customer VALUES (100000, 0)
INSERT INTO Customer VALUES (80000, 0)
INSERT INTO Customer VALUES (1000000, 0)
INSERT INTO Customer VALUES (10000000, 0)
INSERT INTO Customer VALUES (500000, 0)
GO