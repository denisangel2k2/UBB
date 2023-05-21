begin transaction
update MaterialeCoarde set nume_material='material' where id_material_coarda=14
waitfor delay '00:00:05'
rollback transaction