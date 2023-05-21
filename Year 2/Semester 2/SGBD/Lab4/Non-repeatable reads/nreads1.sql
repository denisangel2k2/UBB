delete from MaterialeCoarde where nume_material='nonrepeat' or nume_material='nonrepeat2'
insert into MaterialeCoarde(nume_material,rezistenta,densitate) values ('nonrepeat',99,99)
begin transaction
waitfor delay '00:00:05'
update MaterialeCoarde set nume_material='nonrepeat2'
where nume_material='nonrepeat'
commit transaction

