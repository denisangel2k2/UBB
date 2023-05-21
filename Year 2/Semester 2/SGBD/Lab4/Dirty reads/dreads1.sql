begin transaction
update MaterialeCoarde set nume_material='material' where id_material_coarda=14
insert into Logs values('dreads','update material',CURRENT_TIMESTAMP)
waitfor delay '00:00:05'
rollback transaction