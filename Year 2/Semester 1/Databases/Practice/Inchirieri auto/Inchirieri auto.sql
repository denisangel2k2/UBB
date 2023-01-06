create database InchirieriAuto
go
use InchirieriAuto

--1)

create table Clienti
(
	id_client int primary key identity,
	nume varchar(20),
	prenume varchar(20)
);
go
create table Angajati
(
	id_angajat int primary key identity,
	nume varchar(20),
	prenume varchar(20)
);
go
create table Marci
(
	id_marca int primary key identity,
	denumire nvarchar(40)
);
go
create table Autovehicule
(
	id_auto int primary key identity,
	nr_inm varchar(8),
	tip varchar(20),
	id_marca int,
	constraint fk_Marca foreign key(id_marca) references Marci(id_marca)

);
go

create table Inchirieri
(
	id_angajat int,
	id_client int,
	id_auto int,
	data_get datetime,
	data_return datetime,

	constraint fk_Angajat foreign key(id_angajat) references Angajati(id_angajat),
	constraint fk_Client foreign key(id_client) references Clienti(id_client),
	constraint fk_Auto foreign key(id_auto) references Autovehicule(id_auto)
);

--2)
insert into Angajati(nume,prenume) values
('NumeAngajat1','PrenumeAngajat1'),
('NumeAngajat2','PrenumeAngajat2')
go

insert into Clienti(nume,prenume) values
('NumeClient1','PrenumeClient1'),
('NumeClient2','PrenumeClient2')
go
insert into Marci(denumire) values
('Marca1'),
('Marca2')
go
insert into Autovehicule(nr_inm,tip,id_marca) values
('NRINM1','benzina',1),
('NRINM2','motorina',2),
('NRINM3','gaz',1),
('NRINM4','benzina',2)
go
insert into Inchirieri(id_angajat,id_client,id_auto,data_get,data_return) values
(1,1,4,'2020-10-20 12:00','2020-11-01 01:25'),
(2,2,6,'2023-01-10 17:25','2023-01-12 13:25'),
(1,1,7,'2023-01-01 16:10','2023-01-12 17:03')


--2)
create or alter procedure Procedura2
	@id_angajat int,
	@id_client int,
	@id_auto int,
	@data_get datetime,
	@data_return datetime,
	@operatie bit
as
begin
	if @operatie=1
	begin
		insert into Inchirieri(id_angajat,id_client,id_auto,data_get,data_return) values
		(@id_angajat,@id_client,@id_auto,@data_get,@data_return)
	end;
	else
	begin
		update Inchirieri set data_get=@data_get, data_return=@data_return 
		where
		id_angajat=@id_angajat and id_auto=@id_auto and id_client=@id_client
	end;
end;

exec Procedura2 1,2,5,'2020-10-20 12:00','2020-11-01 14:25','TRUE'
select * from Inchirieri

--3)
create or alter view ViewAngajatiLuna
as
select A.nume, A.prenume, count(I.id_angajat) as Cati from Angajati A
inner join Inchirieri I on I.id_angajat=A.id_angajat
inner join Autovehicule AV on I.id_auto=AV.id_auto
inner join Marci M on M.id_marca=AV.id_marca
where M.denumire='Marca2'
group by A.nume,A.prenume
having count(I.id_angajat)>1

select * from ViewAngajatiLuna

--4)
create or alter function AutovehiculeLibere(@ora_dorita datetime)
returns @tab table
(
	numar varchar(8),
	marca nvarchar(40),
	tip varchar(20)
)
as
begin
	insert into @tab 
	select A.nr_inm,M.denumire,A.tip from Autovehicule A
	inner join Marci M on A.id_marca=M.id_marca
	left join Inchirieri I on I.id_auto=A.id_auto
	where I.data_return<=@ora_dorita

	return
end;

select * from Inchirieri

select * from AutovehiculeLibere('2020-11-01 01:26')