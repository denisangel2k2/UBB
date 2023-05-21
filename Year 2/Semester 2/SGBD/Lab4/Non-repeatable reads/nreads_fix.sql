set transaction isolation level repeatable read
begin transaction
select * from MaterialeCoarde
insert into Logs values('nreads','fixed select',CURRENT_TIMESTAMP)
waitfor delay '00:00:05'
select * from MaterialeCoarde
insert into Logs values('nreads','fixed select',CURRENT_TIMESTAMP)
commit transaction



select * from Logs