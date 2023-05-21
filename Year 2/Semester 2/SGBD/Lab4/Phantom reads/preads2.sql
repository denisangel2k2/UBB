set transaction isolation level repeatable read
begin transaction
select * from ProducatoriCoarde
insert into Logs values('preads2','bug select',CURRENT_TIMESTAMP)
waitfor delay '00:00:05'
select * from ProducatoriCoarde
insert into Logs values('preads2','bug select',CURRENT_TIMESTAMP)
commit transaction

