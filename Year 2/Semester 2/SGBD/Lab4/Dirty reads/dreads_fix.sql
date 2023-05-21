set transaction isolation level read committed
begin transaction
select * from MaterialeCoarde where id_material_coarda=14
waitfor delay '00:00:05'
select * from MaterialeCoarde where id_material_coarda=14
commit transaction