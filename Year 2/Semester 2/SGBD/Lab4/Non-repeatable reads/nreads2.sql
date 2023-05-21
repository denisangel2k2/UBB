set transaction isolation level read committed
begin transaction
select * from MaterialeCoarde
waitfor delay '00:00:05'
select * from MaterialeCoarde
commit transaction