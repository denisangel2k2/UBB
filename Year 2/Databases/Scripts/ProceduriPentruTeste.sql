create or alter procedure InsertINTO 
@table_name nvarchar(25), @number_of_items INT
as
begin
	declare @sqlstatement nvarchar(200);
	declare @index int
	set @index=0
	set @sqlstatement = N'INSERT INTO '
	declare @item_name nvarchar(20)


	if @table_name = 'ProducatoriCoarde'
	begin
		while @index < @number_of_items
		begin
			set @item_name = 'PCoarda'+CAST (@index as NVARCHAR)
			set @sqlstatement = N'INSERT INTO ProducatoriCoarde(nume_prod) VALUES '+N'('''+@item_name+N''')'
			exec sp_executesql @sqlstatement
			set @index = @index + 1;

		end;
	end;

	else if @table_name='Coarde'
	begin
		--daugam inregistrare ca sa putem face conexiunea
		insert into ProducatoriCoarde (nume_prod) values ('Producator')
			
		declare @id_prodd int
		select top(1) @id_prodd=id_prod from ProducatoriCoarde
		
		while @index < @number_of_items
		begin
			set @item_name = 'Coarda'+CAST (@index as NVARCHAR)
			set @sqlstatement = N'INSERT INTO Coarde(material_coarda,id_prod) VALUES '+N'(''' +@item_name+N''','+CAST(@id_prodd as nvarchar)+N')'
			exec sp_executesql @sqlstatement
			set @index = @index + 1;
		end;
	end;

	else if @table_name='Tipuri'
	begin
		while @index < @number_of_items
		begin
			set @item_name = 'Tip'+CAST (@index as NVARCHAR)
			set @sqlstatement = N'INSERT INTO Tipuri(nume_tip) VALUES '+N'('''+@item_name+N''')'
			exec sp_executesql @sqlstatement
			set @index = @index + 1;
		end;
	end;

	else if @table_name='Categorii'
	begin
		while @index < @number_of_items
		begin
			set @item_name = 'Categorie'+CAST (@index as NVARCHAR)
			set @sqlstatement = N'INSERT INTO Categorii(nume_categorie) VALUES '+N'('''+@item_name+N''')'
			exec sp_executesql @sqlstatement
			set @index = @index + 1;
		end;
	end;

	else if @table_name='Materiale'
	begin
		while @index < @number_of_items
		begin
			set @item_name='Material' + CAST (@index as NVARCHAR)
			set @sqlstatement = N'INSERT INTO Materiale(nume_mat) VALUES '+N'('''+@item_name+N''')'
			exec sp_executesql @sqlstatement
			set @index = @index + 1; 
		end;
	end;

	else if @table_name='Instrumente'
	begin
		--adaugam date in celalalte tabele sa facem conexiunea
		declare @id_proddd int
		declare @id_coardaa int
		declare @id_tipp int
		declare @id_catt int
		declare @id_matt int

		delete from ProducatoriCoarde where nume_prod='Producator'
		delete from Materiale where nume_mat='Material'
		delete from Coarde where material_coarda='Coarda'
		delete from Tipuri where nume_tip='Tip'
		delete from Categorii where nume_categorie='Categorie'

		insert into ProducatoriCoarde(nume_prod) values ('Producator')
		
		set @id_proddd = (select top(1) id_prod from ProducatoriCoarde)

		insert into Coarde(material_coarda,id_prod) values ('Coarda',@id_proddd)
		select top(1) @id_coardaa=id_coarda from Coarde

		insert into Materiale(nume_mat) values('Material')
		select top(1) @id_matt=id_mat from Materiale

		insert into Categorii(nume_categorie) values ('Categorie')
		select top(1) @id_catt=id_categorie from Categorii

		insert into Tipuri(nume_tip) values ('Tip')
		select top(1) @id_tipp=id_tip from Tipuri

		while @index < @number_of_items
		begin
			set @item_name='ModelInstrument' + CAST (@index as nvarchar)
			set @sqlstatement = 'INSERT INTO Instrumente(model,id_coarda,id_material,id_cat,id_tip) VALUES ('+N''''+@item_name+N''','+CAST(@id_coardaa as nvarchar)+N','+CAST(@id_matt as nvarchar)+N','+CAST(@id_catt as nvarchar)+N','+CAST(@id_tipp as nvarchar)+N')'
			exec sp_executesql @sqlstatement
			set @index = @index+1
		end;
		
	end;

	
end;


exec InsertINTO 'Instrumente',100
select * from Instrumente

create or alter procedure DeleteFromTable 
@table_name VARCHAR(25)
as
begin
	declare @sqlstatement nvarchar(100)
	set @sqlstatement = N'DELETE FROM '+@table_name
	exec sp_executesql @sqlstatement

end


select * from tests
create or alter procedure TestDatabase
as
begin

	set nocount on
	declare @maximumTestId int
	declare @currentTestId int

	select @maximumTestId=max(TestID) from Tests 
	select @currentTestId=min(TestID) from Tests 

	print @maximumTestId

	declare @tableId int
	declare @tableName varchar(25)
	declare @noOfRows int
	
	declare @startGlobal datetime
	set @startGlobal = getdate()

	insert into TestRuns(StartAt) values (@startGlobal)

	declare @maxTestRunId int
	select @maxTestRunId=max(TestRunID) from TestRuns;
	
	declare @endGlobal datetime


	while @currentTestId<=@maximumTestId
	begin
		declare cursorForDelete cursor forward_only for
		select T.name, T.TableID from TestTables TT
		inner join Tables T on T.TableID=TT.TableID
		where TT.TestID = @currentTestId
		order by Position desc

		declare @testStart datetime
		set @testStart = getdate()

		open cursorForDelete
			fetch next from cursorForDelete into @tableName, @tableId
			while @@FETCH_STATUS=0
			begin
				--aici masor timpul de executie pentru delete al fiecarui tabel si il stochez in TestRunTables

				exec DeleteFromTable @tableName

				fetch next from cursorForDelete into @tableName, @tableId
			end
			
		close cursorForDelete
		deallocate cursorForDelete
		

		declare cursorForInsert cursor forward_only for
		select T.name, TT.NoOfRows, T.TableID from TestTables TT
		inner join Tables T on T.TableID=TT.TableID
		where TT.TestID = @currentTestId
		order by Position

		open cursorForInsert
			fetch next from cursorForInsert into @tableName, @noOfRows, @tableId
			while @@FETCH_STATUS=0
			begin
				--aici masor timpul de executie pentru insert al fiecarui tabel si il stochez in TestRunTables
				exec InsertINTO @tableName, @noOfRows

				fetch next from cursorForInsert into @tableName, @noOfRows, @tableId
			end
			
		close cursorForInsert
		deallocate cursorForInsert

		declare @testEnd datetime
		set @testEnd = getdate();
		
	


		set @currentTestId=@currentTestId+1

		--aici mai fac si pentru
	end;
	


end



exec TestDatabase
exec DeleteFromTable 'ProducatoriCoarde'