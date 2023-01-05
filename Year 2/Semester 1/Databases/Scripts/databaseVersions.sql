
CREATE OR ALTER PROCEDURE dbUpdate1 
AS
BEGIN
	ALTER TABLE Instrumente
	ALTER COLUMN pret MONEY;
END


GO

CREATE OR ALTER PROCEDURE dbUpdate2
AS
BEGIN
	ALTER TABLE Semnaturi
	ADD CONSTRAINT df_numeMuzician DEFAULT NULL FOR nume_muzician
END

GO

CREATE OR ALTER PROCEDURE dbUpdate3
AS
BEGIN
	CREATE TABLE Resigilate
	(
	id int primary key
	);
END

GO

CREATE OR ALTER PROCEDURE dbUpdate4
AS
BEGIN
	ALTER TABLE Resigilate
	ADD id_instr INT
END;

GO

CREATE OR ALTER PROCEDURE dbUpdate5
AS
BEGIN
	ALTER TABLE Resigilate
	ADD CONSTRAINT fk_InstrumentResigilat FOREIGN KEY(id_instr) REFERENCES Instrumente(id_instr);
END

GO

CREATE OR ALTER PROCEDURE dbDowngrade1
AS
BEGIN
	ALTER TABLE Instrumente
	ALTER COLUMN pret INT;
END

GO

CREATE OR ALTER PROCEDURE dbDowngrade2
AS
BEGIN
	ALTER TABLE Semnaturi
	DROP CONSTRAINT df_numeMuzician
END

GO

CREATE OR ALTER PROCEDURE dbDowngrade3
AS
	
BEGIN
DROP TABLE Resigilate
END
GO

CREATE OR ALTER PROCEDURE dbDowngrade4
AS
BEGIN
	ALTER TABLE Resigilate
	DROP COLUMN id_instr
END
GO

CREATE OR ALTER PROCEDURE dbDowngrade5
AS
BEGIN
	ALTER TABLE Resigilate
	DROP CONSTRAINT fk_InstrumentResigilat
END

CREATE OR ALTER PROCEDURE GetToVersion
@demandedVersion INT
AS
BEGIN
	SET NOCOUNT ON

	DECLARE @currentVersion INT;
	SET @currentVersion=(SELECT TOP 1 versiune FROM Versiuni);
	DECLARE @procedure VARCHAR(25);
	DECLARE @procedureNumber VARCHAR(5);
	
	IF (@demandedVersion<0 OR @demandedVersion>5)
	begin
		RAISERROR('Versiunea dorita este incorecta!',11,1);
		RETURN;
	end
	IF @demandedVersion < @currentVersion
	begin
	--downgrade
		WHILE @currentVersion <> @demandedVersion
		BEGIN
			SET @procedureNumber=CAST(@currentVersion AS VARCHAR);
			SET @currentVersion = @currentVersion-1;
			SET @procedure='dbDowngrade'+@procedureNumber;
			PRINT 'EXECUTING PROCEDURE ' + @procedure;
			EXEC (@procedure)
		END
	end
	ELSE
	--update
	begin
		WHILE @currentVersion<>@demandedVersion
		BEGIN
			SET @currentVersion=@currentVersion+1;
			SET @procedureNumber=CAST(@currentVersion AS VARCHAR);
			SET @procedure='dbUpdate'+@procedureNumber;
			PRINT 'EXECUTING PROCEDURE '+@procedure;
			EXEC(@procedure);
			
		END
	end

	UPDATE Versiuni
	SET versiune=@demandedVersion;
	PRINT 'Versiunea curenta a bazei de date este '+CAST(@demandedVersion as VARCHAR);

END





