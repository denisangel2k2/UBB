-- validari pentru tabelul ProducatoriCoarde

CREATE OR ALTER FUNCTION validareNumeProducator(@nume_prod VARCHAR(20))
RETURNS BIT
AS
BEGIN
	IF @nume_prod IS NULL
		return 0;
	if LTRIM(@nume_prod)=''
		return 0;
	if len(@nume_prod)<2
		return 0;

	declare @lungime int
	set @lungime=len(@nume_prod)

	declare @contor int
	set @contor=1

	while @contor<=@lungime
	begin
		if not SUBSTRING(@nume_prod,@contor,1) like '%[A-Za-z 0-9-]' -- poate aici bai
			return 0;
		set @contor=@contor+1
	end;
	return 1;


END;
GO


create or alter function validareNationalitate(@nationalitate varchar(40))
returns bit
as
begin

	if LTRIM(@nationalitate) = ''
		return 0;

	if len(@nationalitate)<3
		return 0;

	declare @lungime int
	set @lungime = len(@nationalitate)

	declare @contor int
	set @contor = 1
	while @contor <= @lungime
	begin

		if @contor = 1
			begin
				if not substring(@nationalitate,@contor,1) like '%[A-Z]'
					return 0;
			end;
		else
				if not substring(@nationalitate,@contor,1) like '%[a-z]'
					return 0;
			
		set @contor = @contor+1
	end;
	return 1;
end;
go

create or alter function validareAnAparitie(@an_aparitie int)
returns bit
as
begin
	if not (@an_aparitie<=2023 and @an_aparitie>=0)
		return 0;
	return 1;
end;

go


-- validari pentru tabelul MaterialeCoarde

create or alter function validareNumeMaterial(@nume_mat varchar(30))
returns bit
as
begin

	if LTRIM(@nume_mat)=''
		return 0;
	if len(@nume_mat)<2
		return 0;

	declare @lungime int
	set @lungime = len(@nume_mat)

	declare @contor int
	set @contor = 1
	while @contor <= @lungime
	begin

		if not SUBSTRING(@nume_mat,@contor,1) like '%[A-Za-z]'
			return 0;

		set @contor = @contor+1
	end;
	return 1;

end;
go

create or alter function validareRezistenta(@rezistenta real)
returns bit
as
begin
	if @rezistenta > 100 or @rezistenta < 0
		return 0;
	return 1;

end;
go

create or alter function validareDensitate(@denisitate real)
returns bit
as
begin
	if @denisitate > 100 or @denisitate < 0
		return 0;
	return 1;

end;
go


-- validari pentru tabelul Coarde

create or alter function validareVechime(@vechime int)
returns bit
as
begin
	if @vechime>501 or @vechime<0
		return 0;
	return 1;
end;
go

create or alter function validareRefolosit(@refolosit bit)
returns bit
as
begin
	if not (@refolosit = 0 or @refolosit = 1)
		return 0;
	return 1;
end;
go

create or alter function validareIdProducator(@id_prod int)
returns bit
as
begin
	if(exists(select * from ProducatoriCoarde where id_prod=@id_prod))
		return 1;
	return 0;
end;
go

create or alter function validareIdMaterialCoarda(@id_material_coarda int)
returns bit
as
begin
	if(exists(select * from MaterialeCoarde where id_material_coarda=@id_material_coarda))
		return 1;
	return 0;
end;
go

-- procedura CRUDProducatoriCoarde


create or alter procedure CRUDProducatoriCoarde
	@flag bit output,
	@action varchar(20),
	@nume_prod varchar(20),
	@an_aparitie int,
	@nationalitate varchar(40),
	@idProdCoarde int
as
begin

	set nocount on;
	set @flag=1;
	if dbo.validareAnAparitie(@an_aparitie) = 0 or 
		dbo.validareNumeProducator(@nume_prod) = 0 or dbo.validareNationalitate(@nationalitate) = 0
		set @flag=0;

	if @flag = 1
	begin
		if @action='insert'
		begin
			if exists (select * from ProducatoriCoarde where nume_prod=@nume_prod)
			begin
				print 'The ProducatoriCoarde already exists: '+@nume_prod;
				set @flag=0;
			end;
			else
			begin
				insert into ProducatoriCoarde(nume_prod,an_aparitie,nationalitate) values (@nume_prod,@an_aparitie,@nationalitate)
				print 'Inserted new ProducatorCoarde with: '+@nume_prod+' '+cast(@an_aparitie as varchar)+' '+@nationalitate;
			end;
			
		end;
		else if @action = 'delete'
		begin

			if (not exists(select * from ProducatoriCoarde where id_prod=@idProdCoarde) or @idProdCoarde is null)
			begin	
				print 'Item does not exist in ProducatoriCoarde!'
				set @flag=0;
			end
			else
			begin
				delete from ProducatoriCoarde where id_prod=@idProdCoarde
				print 'Delete successful from ProducatoriCoarde!'
			end;
			
		end;
		else if @action = 'update'
		begin
			if (not exists(select * from ProducatoriCoarde where id_prod=@idProdCoarde) or @idProdCoarde is null)
			begin
				print 'Item does not exist in ProducatoriCoarde!'
				set @flag=0;
			end;
			else
			begin
				update ProducatoriCoarde set nume_prod=@nume_prod, an_aparitie=@an_aparitie, nationalitate=@nationalitate where id_prod=@idProdCoarde
				print 'Update successfully on ProducatoriCoarde: '+@nume_prod+' '+cast(@an_aparitie as varchar)+' '+@nationalitate;
			end;
		end;
		else if @action = 'select'
		begin
			select * from ProducatoriCoarde where id_prod=@idProdCoarde
		end;
		else
			print 'No action found!'
	end;
	else
		print 'Validation error ProducatoriCoarde'
end;
go
-- procedura CRUDMaterialeCoarde

create or alter procedure CRUDMaterialeCoarde
	@action varchar(20),
	@nume_material varchar(30),
	@rezistenta real,
	@densitate real,
	@idMaterial int
as
begin
	set nocount on;
	declare @ok bit = 1;
	if dbo.validareNumeMaterial(@nume_material)=0 or dbo.validareRezistenta(@rezistenta)=0 or dbo.validareDensitate(@densitate)=0
		set @ok = 0;

	if @ok=1
	begin
		if @action = 'insert'
		begin
			if exists (select * from MaterialeCoarde where nume_material=@nume_material)
				print 'The MaterialCoarda already exists: '+@nume_material;
			else
			begin
				insert into MaterialeCoarde(nume_material,rezistenta,densitate) values (@nume_material,@rezistenta,@densitate)
				print 'Inserted successfully into MaterialeCoarde: '+@nume_material+' '+cast(@rezistenta as varchar)+' '+cast(@densitate as varchar);
			end
		end;
		else if @action='delete'
		begin
			if (not exists(select * from MaterialeCoarde where id_material_coarda=@idMaterial))
				print 'Item does not exist in MaterialeCoarde'
			else
			begin
				delete from MaterialeCoarde where id_material_coarda=@idMaterial
				print 'Delete successful from MaterialeCoarde!'
			end;
		end;
		else if @action='update'
		begin
			if (not exists(select * from MaterialeCoarde where id_material_coarda=@idMaterial))
				print 'Item does not exist in MaterialeCoarde'
			else
			begin
				update MaterialeCoarde set nume_material=@nume_material, rezistenta=@rezistenta, densitate=@densitate
				where id_material_coarda=@idMaterial
				print 'Update successfully on MaterialeCoarde: '+@nume_material+' '+cast(@rezistenta as varchar)+' '+cast(@densitate as varchar);
			end;
		end;
		else if @action='select'
		begin
			select * from MaterialeCoarde where id_material_coarda=@idMaterial
		end;
		else
			print 'No action found!'
	end;
	else
		print 'Validation error MaterialeCoarde'
end;
go
-- procedura CRUDCoarde
create or alter procedure CRUDCoarde
	@action varchar(20),
	@idProd int,
	@idMaterial int,
	@vechime int,
	@refolosit bit,
	@idCoarda int
as
begin
	set nocount on;
	declare @ok bit = 1;
	
	if dbo.validareIdProducator(@idProd)=0 or dbo.validareIdMaterialCoarda(@idMaterial)=0 or
	dbo.validareVechime(@vechime)=0 or dbo.validareRefolosit(@refolosit)=0
		set @ok=0;

	if @ok=1
	begin
		if @action = 'insert'
		begin
			insert into Coarde(id_prod,id_material_coarda,vechime,refolosit) values (@idProd,@idMaterial,@vechime,@refolosit)
			print 'Inserted successfully into Coarde: '+cast(@idProd as varchar)+' '+cast(@idMaterial as varchar)+' '+cast(@vechime as varchar)+' '+cast(@refolosit as varchar);
		end;
		else if @action='delete'
		begin
			if (not exists(select * from Coarde where id_coarda=@idCoarda))
				print 'Item does not exist in Coarde!'
			else
			begin
				delete from Coarde where id_coarda=@idCoarda
				print 'Delete successful from Coarde!'
			end;
		end;
		else if @action='update'
		begin
			if (not exists(select * from Coarde where id_coarda=@idCoarda))
				print 'Item does not exist in Coarde!'
			else
			begin
				update Coarde set id_prod=@idProd, id_material_coarda=@idMaterial, vechime=@vechime, refolosit=@refolosit where id_coarda=@idCoarda
				print 'Update successful on Coarde: '+cast(@idProd as varchar)+' '+cast(@idMaterial as varchar)+' '+cast(@vechime as varchar)+' '+cast(@refolosit as varchar);
			end;
		end;
		else if @action='select'
		begin
			select * from Coarde where id_coarda=@idCoarda
		end;
		else
			print 'No action found!'
	end;
	else
		print 'Validation error Coarde'
end;
go
-- procedura CRUDMain
create or alter procedure CRUDMain
as
begin
	set nocount on;
	delete from Instrumente
	delete from Coarde
	delete from ProducatoriCoarde
	delete from MaterialeCoarde

	DBCC CHECKIDENT (Coarde, RESEED, 0);
	DBCC CHECKIDENT (ProducatoriCoarde, RESEED, 0);
	DBCC CHECKIDENT (MaterialeCoarde, RESEED, 0);


	declare @flag bit
	print 'Starting CRUD operations...'

	-- CRUD pe ProducatoriCoarde

	exec CRUDProducatoriCoarde @flag output,'insert','Producator1',2000,'Romania',1
	if @flag=0 print'		Nothing happend...'
	exec CRUDProducatoriCoarde @flag output,'insert','Producator2',1995,'Danemarca',2
	if @flag=0 print'		Nothing happend...'
	exec CRUDProducatoriCoarde @flag output,'insert','Producator3',2001,'Suedia',3
	if @flag=0 print'		Nothing happend...'
	exec CRUDProducatoriCoarde @flag output,'insert','Producator4',1966,'Norvegia',4
	if @flag=0 print'		Nothing happend...'
	exec CRUDProducatoriCoarde @flag output,'insert','Producator1',2000,'Romania',1 -- gresit
	if @flag=0 print'		Nothing happend...'
	exec CRUDProducatoriCoarde @flag output,'delete','Producator1',2000,'Romania',1
	if @flag=0 print'		Nothing happend...'
	exec CRUDProducatoriCoarde @flag output,'delete','Producator1',2000,'romania',3 --gresit
	if @flag=0 print'		Nothing happend...'
	exec CRUDProducatoriCoarde @flag output,'update','ProducatorUpdated1',2001,'Romania',2
	if @flag=0 print'		Nothing happend...'

	-- CRUD pe MaterialeCoarde
	exec CRUDMaterialeCoarde 'insert','Otel',22.3,4.93,1

	exec CRUDMaterialeCoarde 'insert','Pirita',22.3,4.93,2
	exec CRUDMaterialeCoarde 'insert','Aur',22.3,4.93,3
	exec CRUDMaterialeCoarde 'insert','Zircon',22.3,4.93,4
	exec CRUDMaterialeCoarde 'insert','Cupru',22.3,4.93,5
	exec CRUDMaterialeCoarde 'insert','Nylon?',22.3,-5.3,6 --gresit
	exec CRUDMaterialeCoarde 'insert','   otel12',22.3,4.93,7 -- gresit
	exec CRUDMaterialeCoarde 'insert','  ',22.3,4.93,1 -- gresit
	exec CRUDMaterialeCoarde 'delete','dada',22.3,4.93,1
	exec CRUDMaterialeCoarde 'insert','  ',22.3,4.93,9 --gresit
	exec CRUDMaterialeCoarde 'update','Otel',22.99,5.12,2
	exec CRUDMaterialeCoarde 'select','Otel',22.99,5.12,2
	exec CRUDMaterialeCoarde 'blabla','Otel',22.99,5.12,2

	-- CRUD pe Coarde

	select * from ProducatoriCoarde

	exec CRUDCoarde 'insert',2,2,15,1,1
	exec CRUDCoarde 'insert',2,2,10,0,2
	exec CRUDCoarde 'insert',2,3,1,0,3
	exec CRUDCoarde 'insert',2,3,13,0,4
	exec CRUDCoarde 'insert',2,3,4,1,5
	exec CRUDCoarde 'insert',2,-3,15,1,6 --gresit
	exec CRUDCoarde 'insert',2,3,-15,1,7 --gresit
	exec CRUDCoarde 'delete',2,3,15,1,3
	exec CRUDCoarde 'delete',2,3,15,1,3 -- gresit
	exec CRUDCoarde 'update',2,3,1,0,1
	exec CRUDCoarde 'select',2,3,1,0,1
end;
go

exec CRUDMain
go
select * from ProducatoriCoarde
select * from MaterialeCoarde
select * from Coarde
go
-- VIEW-URI

create or alter view ViewProducatoriCoarde
as
	select nume_prod,an_aparitie,nationalitate from ProducatoriCoarde
go

create or alter view ViewCoardeDensitatiRezistente
as
	select id_coarda as ID_Coarda, rezistenta, densitate from Coarde C
	inner join MaterialeCoarde M on M.id_material_coarda=C.id_material_coarda
go

-- INDECSI

create index IX_NumeProd_asc on ProducatoriCoarde (nume_prod asc)
alter index IX_NumeProd_asc on ProducatoriCoarde disable
alter index IX_NumeProd_asc on ProducatoriCoarde rebuild

create index IX_RezistentaDensitate_asc on MaterialeCoarde (rezistenta asc, densitate asc)
alter index IX_RezistentaDensitate_asc on MaterialeCoarde disable
alter index IX_RezistentaDensitate_asc on MaterialeCoarde rebuild

-- SELECT PE VIEW-URI

select * from ViewCoardeDensitatiRezistente

select * from ViewCoardeDensitatiRezistente
order by rezistenta asc, densitate asc


select * from ProducatoriCoarde
select * from ViewProducatoriCoarde order by nume_prod asc





