begin transaction
waitfor delay '00:00:05'
insert into ProducatoriCoarde(nume_prod,an_aparitie,nationalitate) values ('bubu',1111,'romania')
insert into Logs values('preads1','insert prodcoarde',CURRENT_TIMESTAMP)
commit transaction

select * from ProducatoriCoarde
--delete from ProducatoriCoarde where nume_prod='bubu'