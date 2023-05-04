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

create or alter function validareProdCoardeParams(
@nume_prod varchar(20),
@an_aparitie int,
@nationalitate varchar(40)
)
returns varchar(200)
as
begin
	declare @error varchar(200)
	set @error=''
	if (dbo.validareNumeProducator(@nume_prod) = 0)
		set @error = @error + 'Nume producator invalid.'
	if (dbo.validareAnAparitie(@an_aparitie) = 0)
		set @error = @error + 'An aparitie invalid.'
	if (dbo.validareNationalitate(@nationalitate) = 0)
		set @error = @error + 'Nationalitate invalida.'

	return @error
end
go

create or alter function validareMaterialeCoardeParams(
@nume_material varchar(30),
@rezistenta real,
@denisitate real
)
returns varchar(200)
as
begin
	declare @error varchar(200)
	set @error=''
	if (dbo.validareNumeMaterial(@nume_material) = 0)
		set @error = @error + 'Nume material invalid.'
	if (dbo.validareRezistenta(@rezistenta) = 0)
		set @error = @error + 'Rezistenta invalida.'
	if (dbo.validareDensitate(@denisitate) = 0)
		set @error = @error + 'Densitate invalida.'

	return @error

end
go

create or alter function validareCoardeParams(
	@id_prod int,
	@id_mat_coarda int,
	@vechime int,
	@refolosit bit
)
returns varchar(200)
as
begin
	declare @error varchar(200)
	set @error=''
	if (dbo.validareVechime(@vechime) = 0)
		set @error = @error + 'Vechime invalida.';
	if (dbo.validareIdProducator(@id_prod) = 0)
		set @error = @error + 'Id producator invalid.';
	if (dbo.validareIdMaterialCoarda(@id_mat_coarda) = 0)
		set @error = @error + 'Id material coarda invalid.';

	return @error

end
go


create or alter procedure insert_coarda_prodcoarda_materialcoarda(
@nume_prod varchar(20),
@an_aparitie int,
@nationalitate varchar(40),
@vechime int,
@refolosit bit,
@nume_material varchar(30),
@rezistenta real,
@denisitate real
)
as
begin
	begin tran
	begin try
		declare @error varchar(200)
		set @error = dbo.validareProdCoardeParams(@nume_prod,@an_aparitie,@nationalitate);
		if (@error !='')
			begin
				print @error
				raiserror(@error,14,1)
			end
		insert into ProducatoriCoarde(nume_prod,an_aparitie,nationalitate) values(@nume_prod,@an_aparitie,@nationalitate);
		insert into Logs(table_name,executed_action,action_time) values ('ProducatoriCoarde','Insert',CURRENT_TIMESTAMP)
		set @error = dbo.validareMaterialeCoardeParams(@nume_material,@rezistenta,@denisitate)
		if (@error !='')
			begin
				print @error
				raiserror(@error,14,1)
			end
		insert into MaterialeCoarde(nume_material,rezistenta,densitate) values (@nume_material,@rezistenta,@denisitate)
		insert into Logs(table_name,executed_action,action_time) values ('MaterialeCoarde','Insert',CURRENT_TIMESTAMP)

		declare @insertedProdCoardeId int, @insertedMatCoardeId int
		set @insertedProdCoardeId = (select max(id_prod) from ProducatoriCoarde)
		set @insertedMatCoardeId = (select max(id_material_coarda) from MaterialeCoarde)
		

		set @error = dbo.validareCoardeParams(@insertedProdCoardeId,@insertedMatCoardeId,@vechime,@refolosit)
		if (@error !='')
			begin
				print @error
				raiserror(@error,14,1)
			end

		insert into Coarde(id_prod,id_material_coarda,vechime,refolosit) values(@insertedProdCoardeId, @insertedMatCoardeId, @vechime, @refolosit)
		insert into Logs(table_name,executed_action,action_time) values ('Coarde','Insert',CURRENT_TIMESTAMP)
		commit tran
		--insert into Logs(table_name,executed_action,action_time) values ('Coarde','Commited',CURRENT_TIMESTAMP)
		select 'Commited!'
	end try
	begin catch
		rollback tran
		--insert into Logs(table_name,executed_action,action_time) values ('Coarde','Rollbacked',CURRENT_TIMESTAMP)
		select 'Rollback!'

	end catch
end
go


select * from ProducatoriCoarde
select * from MaterialeCoarde
select * from Coarde
select * from Logs

--commit
execute dbo.insert_coarda_prodcoarda_materialcoarda
'ProdSem2',
2000,
'Romania',
23,
0,
'Nichel',
23.3,
25.3

select * from ProducatoriCoarde
select * from MaterialeCoarde
select * from Coarde
select * from Logs

--rollback
execute dbo.insert_coarda_prodcoarda_materialcoarda
'P',
-2000,
'R',
-23,
0,
'N',
5000,
5000.3

select * from ProducatoriCoarde
select * from MaterialeCoarde
select * from Coarde
select * from Logs
go

create or alter procedure insert_coarda_prodcoarda_materialcoarda_version2(
@nume_prod varchar(20),
@an_aparitie int,
@nationalitate varchar(40),
@vechime int,
@refolosit bit,
@nume_material varchar(30),
@rezistenta real,
@denisitate real
)
as
begin
	declare @error varchar(200)

	begin tran
	begin try
		set @error = dbo.validareProdCoardeParams(@nume_prod,@an_aparitie,@nationalitate);
		if (@error !='')
			begin
				print @error
				raiserror(@error,14,1)
			end
		insert into ProducatoriCoarde(nume_prod,an_aparitie,nationalitate) values(@nume_prod,@an_aparitie,@nationalitate);
		insert into Logs(table_name,executed_action,action_time) values ('ProducatoriCoarde','Insert',CURRENT_TIMESTAMP)
		commit tran
		select 'Commited for Producatori Coarde'
	end try
	begin catch
		
		rollback tran
		insert into Logs(table_name,executed_action,action_time) values ('ProducatoriCoarde','Rollback',CURRENT_TIMESTAMP)
		select 'Rollback for Producatori Coarde'
	end catch


	begin tran
	begin try
		set @error = dbo.validareMaterialeCoardeParams(@nume_material,@rezistenta,@denisitate)
		if (@error !='')
			begin
				print @error
				raiserror(@error,14,1)
			end
		insert into MaterialeCoarde(nume_material,rezistenta,densitate) values (@nume_material,@rezistenta,@denisitate)
		insert into Logs(table_name,executed_action,action_time) values ('MaterialeCoarde','Insert',CURRENT_TIMESTAMP)
		commit tran
		select 'Commited for Material Coarde'
	end try
	begin catch
		rollback tran
		insert into Logs(table_name,executed_action,action_time) values ('MaterialeCoarde','Rollback',CURRENT_TIMESTAMP)
		select 'Rollback for Material Coarde'
	end catch

	begin tran
	begin try

		declare @insertedProdCoardeId int, @insertedMatCoardeId int
		set @insertedProdCoardeId = (select max(id_prod) from ProducatoriCoarde)
		set @insertedMatCoardeId = (select max(id_material_coarda) from MaterialeCoarde)

		set @error = dbo.validareCoardeParams(@insertedProdCoardeId,@insertedMatCoardeId,@vechime,@refolosit)
		if (@error !='')
			begin
				print @error
				raiserror(@error,14,1)
			end

		insert into Coarde(id_prod,id_material_coarda,vechime,refolosit) values(@insertedProdCoardeId, @insertedMatCoardeId, @vechime, @refolosit)
		insert into Logs(table_name,executed_action,action_time) values ('Coarde','Insert',CURRENT_TIMESTAMP)
		commit tran
		select 'Commited for Coarde'
	end try
	begin catch
		rollback tran
		insert into Logs(table_name,executed_action,action_time) values ('Coarde','Rollback',CURRENT_TIMESTAMP)
		select 'Rollback for Coarde'
	end catch
end
go

select * from ProducatoriCoarde
select * from MaterialeCoarde
select * from Coarde
select * from Logs

--commit
execute dbo.insert_coarda_prodcoarda_materialcoarda_version2
'ProdSem2v2',
2000,
'Romania',
23,
0,
'Nichel',
23.3,
25.3

select * from ProducatoriCoarde
select * from MaterialeCoarde
select * from Coarde
select * from Logs

--rollback
execute dbo.insert_coarda_prodcoarda_materialcoarda_version2
'ProdSem2v2',
2000,
'Romania',
-23,
0,
'Nichel',
50,
50.3

select * from ProducatoriCoarde
select * from MaterialeCoarde
select * from Coarde
select * from Logs


drop table Logs
create table Logs
(
	table_name varchar(200),
	executed_action varchar(200),
	action_time time
);