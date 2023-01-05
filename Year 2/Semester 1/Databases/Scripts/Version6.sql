
alter table Coarde
drop column material_coarda
go

create table MaterialeCoarde
(
id_material_coarda int primary key identity not null,
nume_material varchar(30)
);


alter table Coarde
add id_material_coarda int

alter table Coarde
add constraint fk_matCoarde foreign key(id_material_coarda) references MaterialeCoarde(id_material_coarda)


alter table ProducatoriCoarde
add an_aparitie int

alter table ProducatoriCoarde
add nationalitate varchar(40)

alter table MaterialeCoarde
add rezistenta real

alter table Coarde
add vechime int

alter table Coarde
add refolosit bit

alter table MaterialeCoarde
add densitate real

alter table Coarde
drop column id_coarda



