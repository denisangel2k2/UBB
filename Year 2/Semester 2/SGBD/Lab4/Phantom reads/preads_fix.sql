set transaction isolation level serializable
begin transaction

select * from ProducatoriCoarde
waitfor delay '00:00:05'
select * from ProducatoriCoarde

commit transaction
