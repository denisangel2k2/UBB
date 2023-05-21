set transaction isolation level read committed
begin transaction
select * from MaterialeCoarde
insert into Logs values('nreads','bug select',CURRENT_TIMESTAMP)
waitfor delay '00:00:05'
select * from MaterialeCoarde
insert into Logs values('nreads','bug select',CURRENT_TIMESTAMP)
commit transaction