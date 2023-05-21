set transaction isolation level read committed
begin transaction
select * from MaterialeCoarde where id_material_coarda=14
insert into Logs values('dreads','fixed select',CURRENT_TIMESTAMP)
waitfor delay '00:00:05'
select * from MaterialeCoarde where id_material_coarda=14
insert into Logs values('dreads','fixed select',CURRENT_TIMESTAMP)
commit transaction