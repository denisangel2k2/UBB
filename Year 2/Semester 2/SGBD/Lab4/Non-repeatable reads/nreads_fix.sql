set transaction isolation level repeatable read
begin transaction
select * from MaterialeCoarde
waitfor delay '00:00:05'
select * from MaterialeCoarde
commit transaction