use MusicDatabase
go
create or alter procedure deadlock1
as
begin
	set deadlock_priority high
	begin tran
		update ProducatoriCoarde set nume_prod='prod1' where id_prod=14
		waitfor delay '00:00:03'
		update MaterialeCoarde set nume_material='mat1' where id_material_coarda=14
	commit tran
end
go
create or alter procedure deadlock2
as
begin
	begin tran
		update MaterialeCoarde set nume_material='mat1' where id_material_coarda=14
		waitfor delay '00:00:03'
		update ProducatoriCoarde set nume_prod='prod1' where id_prod=14
	commit tran
end