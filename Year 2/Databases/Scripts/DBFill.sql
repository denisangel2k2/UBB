

insert into Semnaturi(nume_muzician) values ('Eric Clapton')
insert into Semnaturi(nume_muzician) values ('Jimmy Hendrix')
insert into Semnaturi(nume_muzician) values ('Angus Young')
insert into Semnaturi(nume_muzician) values ('John Mayer')

insert into Tipuri(nume_tip) values ('Percutie')
insert into Tipuri(nume_tip) values ('Cu coarde')
insert into Tipuri(nume_tip) values ('Cu clape')

insert into Branduri(nume_brand) values('Organic')

insert into Culori(culoare) values ('Midnight purple')
insert into Culori(culoare) values ('Stars glitter white')
insert into Culori(culoare) values ('Frozen lake blue')
insert into Culori(culoare) values ('Sunshine burn wood brown')
insert into Culori(culoare) values ('Petrol black')

insert into Huse(id_brand,culoare) values (1,'Rosu')
insert into Huse(id_brand,culoare) values (3,'Albastru')
insert into Huse(id_brand,culoare) values (1,'Rosu')
insert into Huse(id_brand,culoare) values (2,'Violet')
insert into Huse(id_brand,culoare) values (1,'Negru')

insert into Instrumente(model,an_fabricatie,id_tip,id_coarda,id_brand,id_material,id_cat,id_semnatura) 
values('S789-32','2002','2','1','1','1','1','1');

insert into Instrumente(model,an_fabricatie,id_tip,id_coarda,id_brand,id_material,id_cat,id_semnatura) 
values('50s classic','2002','2','1','1','1','1','1');

insert into Instrumente(model,an_fabricatie,id_tip,id_coarda,id_brand,id_material,id_cat,id_semnatura,id_husa) 
values('70s classic','1983','2','1','1','2','1','1','1');

insert into Instrumente(model,an_fabricatie,id_tip,id_brand,id_material,id_cat) 
values('Holkenbauden','2010','3','3','2','2');

insert into Instrumente(model,an_fabricatie,id_tip,id_brand,id_material,id_cat) 
values('T103','2013','4','3','2','2');

Insert into InstrumenteColorate(id_culoare,id_instrument) values (11,9)
Insert into InstrumenteColorate(id_culoare,id_instrument) values (12,8)
Insert into InstrumenteColorate(id_culoare,id_instrument) values (14,10)
Insert into InstrumenteColorate(id_culoare,id_instrument) values (11,4)
Insert into InstrumenteColorate(id_culoare,id_instrument) values (12,5)
Insert into InstrumenteColorate(id_culoare,id_instrument) values (13,6)
Insert into InstrumenteColorate(id_culoare,id_instrument) values (13,7)




