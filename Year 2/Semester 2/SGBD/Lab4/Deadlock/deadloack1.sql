begin transaction
update ProducatoriCoarde set nume_prod='Producator' where id_prod=13
waitfor delay '00:00:10'
update MaterialeCoarde set nume_material='Material' where id_material_coarda=14
commit transaction
