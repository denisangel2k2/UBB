create database GestiuneVanzari
go
use GestiuneVanzari

--1)

create table Clienti
(
	id_client int primary key identity,
	denumire nvarchar(25),
	cod_fiscal nvarchar(10)
);
go
create table Produse
(
	id_produs int primary key identity,
	denumire nvarchar(25),
	cantitate real
);
go 
create table Agenti
(
	id_agent int primary key identity,
	nume varchar(20),
	prenume varchar(20)
);
go
create table Facturi
(
	id_factura int primary key identity,
	id_agent int,
	id_client int,
	constraint fk_Agent foreign key(id_agent) references Agenti(id_agent),
	constraint fk_Client foreign key(id_client) references Clienti(id_client)
);
go
alter table Facturi
add numar int
alter table Facturi
add data_emitere datetime
go
create table ProduseFacturi
(
	id_factura int,
	id_produs int,
	nr_ordine int,
	pret money,
	cantitate smallint,
	constraint fk_Factura foreign key(id_factura) references Facturi(id_factura),
	constraint fk_Produs foreign key(id_produs) references Produse(id_produs),
	
);


insert into Produse(cantitate,denumire) values
(10,'Produs1'),
(12,'Produs2'),
(3,'Produs3'),
(14.3,'Produs4')
go
insert into Clienti(denumire,cod_fiscal) values
('Client1','CodFiscal1'),
('Client2','CodFiscal2'),
('Client3','CodFiscal3'),
('Client4','CodFiscal4')
go
insert into Agenti(nume,prenume) values
('NumeAgent1','PrenumeAgent1'),
('NumeAgent2','PrenumeAgent2'),
('NumeAgent3','PrenumeAgent3'),
('NumeAgent4','PrenumeAgent4')
go
insert into Facturi(id_agent,id_client,numar,data_emitere) values
(1,3,4,'2022-10-10 12:00'),
(1,1,3,'2022-10-10 11:00'),
(2,2,2,'2023-05-01 09:00')
go
insert into ProduseFacturi(id_factura,id_produs,cantitate,nr_ordine,pret) values
(3,1,2,1,15),
(1,1,3,1,20),
(1,2,1,2,14),
(2,3,2,1,3)

--2)

create or alter procedure InsertIntoProduseFacturi
	@id_factura int,
	@id_produs int,
	@nrord int,
	@pret money,
	@cantitate smallint
as
begin
	if (not exists(select * from ProduseFacturi where id_produs=@id_produs and id_factura=@id_factura))
		insert into ProduseFacturi(id_factura,id_produs,nr_ordine,cantitate,pret) values
		(@id_factura,@id_produs,@nrord,@cantitate,@pret)
	else
		insert into ProduseFacturi(id_factura,id_produs,nr_ordine,cantitate,pret) values
		(@id_factura,@id_produs,@nrord,-@cantitate,@pret)
end;

exec InsertIntoProduseFacturi 1,3,4,10,20
select * from ProduseFacturi

--3)
create or alter view ViewShaorme
as
select C.denumire,F.numar,F.data_emitere,SUM(PF.pret) as Pret from Clienti C
inner join Facturi F on F.id_client=C.id_client
inner join ProduseFacturi PF on PF.id_factura=F.id_factura
inner join Produse P on P.id_produs=PF.id_produs
where P.denumire='Produs1' and PF.pret>11 -- where P.denumire='Shaorma' and PF.pret>300
group by C.denumire,F.numar,F.data_emitere

select * from ViewShaorme

--4)
create or alter function Raport(@an int)
returns @tab table
(
	luna int,
	nume varchar(20),
	prenume varchar(20),
	valoare money
)
as
begin
	insert into @tab select month(F.data_emitere),A.nume,A.prenume,sum(PF.pret) from Facturi F
	inner join Agenti A on F.id_agent=A.id_agent
	inner join ProduseFacturi PF on PF.id_factura=F.id_factura
	where year(F.data_emitere)=@an
	group by month(F.data_emitere),A.nume,A.prenume
	order by month(F.data_emitere),A.nume,A.prenume
	return
end;

select * from Raport(2022)