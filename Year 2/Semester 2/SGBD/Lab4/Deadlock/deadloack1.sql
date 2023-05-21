begin transaction
update ProducatoriCoarde set nume_prod='Producator' where id_prod=13
insert into Logs(table_name,executed_action,action_time) values ('deadlock1','Update producator',CURRENT_TIMESTAMP)
waitfor delay '00:00:05'
update MaterialeCoarde set nume_material='Material' where id_material_coarda=14
insert into Logs(table_name,executed_action,action_time) values ('deadlock1','Update materiale',CURRENT_TIMESTAMP)
commit transaction

begin try
	begin transaction
	update ProducatoriCoarde set nume_prod='Producator' where id_prod=13
	insert into Logs(table_name,executed_action,action_time) values ('deadlock1','Update producator',CURRENT_TIMESTAMP)
	waitfor delay '00:00:05'
	update MaterialeCoarde set nume_material='Material' where id_material_coarda=14
	insert into Logs(table_name,executed_action,action_time) values ('deadlock1','Update materiale',CURRENT_TIMESTAMP)
	commit transaction
end try
begin catch
	if ERROR_NUMBER()=1205
	begin
		rollback;
		begin transaction
			--update ProducatoriCoarde set nume_prod='Producator' where id_prod=13
			insert into Logs(table_name,executed_action,action_time) values ('deadlock1 bug','bug',CURRENT_TIMESTAMP)
			--update MaterialeCoarde set nume_material='Material' where id_material_coarda=14
			insert into Logs(table_name,executed_action,action_time) values ('deadlock1 bug','bug',CURRENT_TIMESTAMP)
		commit transaction
	end
end catch

delete from Logs


select * from Logs
select * from ProducatoriCoarde
select * from MaterialeCoarde