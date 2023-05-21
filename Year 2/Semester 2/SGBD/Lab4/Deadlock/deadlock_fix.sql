set deadlock_priority high
begin transaction
update MaterialeCoarde set nume_material='Material2' where id_material_coarda=14
insert into Logs(table_name,executed_action,action_time) values ('deadlock2','Update material',CURRENT_TIMESTAMP)
waitfor delay '00:00:05'
update ProducatoriCoarde set nume_prod='Producator2' where id_prod=13
insert into Logs(table_name,executed_action,action_time) values ('deadlock2','Update producator',CURRENT_TIMESTAMP)
commit transaction