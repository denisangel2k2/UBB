set transaction isolation level read uncommitted
begin transaction
select * from MaterialeCoarde where id_material_coarda=14
insert into Logs values('dreads','bug select',CURRENT_TIMESTAMP)
waitfor delay '00:00:05'
select * from MaterialeCoarde where id_material_coarda=14
insert into Logs values('dreads','bug select',CURRENT_TIMESTAMP)
commit transaction