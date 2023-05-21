set transaction isolation level serializable
begin transaction

select * from ProducatoriCoarde
insert into Logs values('preads2','fixed select',CURRENT_TIMESTAMP)
waitfor delay '00:00:05'
select * from ProducatoriCoarde
insert into Logs values('preads2','fixed select',CURRENT_TIMESTAMP)

commit transaction


select * from Logs order by action_time
delete from Logs