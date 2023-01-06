
--1)
create database Clinica;
go
use Clinica;

create table Pacienti
(
	id_pacient int primary key identity,
	nume varchar(20),
	prenume varchar(20),
	adresa nvarchar(60)
);
go
create table Diagnostice
(
	id_diagnostic int primary key identity,
	denumire nvarchar(50),
	descriere nvarchar(200)
);
go
create table Specializari
(
	id_specializare int primary key identity,
	denumire varchar(50)
);
go
create table Medici
(
	id_medic int primary key identity,
	nume varchar(20),
	prenume varchar(20),
	id_specializare int,
	constraint fk_Specializare foreign key(id_specializare) references Specializari(id_specializare)
);
go

create table Consultatii
(
	id_medic int,
	id_pacient int,
	id_diagnostic int,
	data_consult date,
	ora_consult time,
	observatii nvarchar(100),
	constraint fk_Medic foreign key(id_medic) references Medici(id_medic),
	constraint fk_Pacient foreign key(id_pacient) references Pacienti(id_pacient),
	constraint fk_Diagnostic foreign key(id_diagnostic) references Diagnostice(id_diagnostic),
	--primary key (id_medic,id_pacient)
	constraint uniqueConsult unique (id_medic,id_pacient,data_consult,ora_consult)
);
--inserare date
insert into Pacienti(nume,prenume,adresa) values
('NumePacient1','PrenumePacient1','AdresaPacient1'),
('NumePacient2','PrenumePacient2','AdresaPacient2'),
('NumePacient3','PrenumePacient3','AdresaPacient3'),
('NumePacient4','PrenumePacient4','AdresaPacient4'),
('NumePacient5','PrenumePacient5','AdresaPacient5')

go
insert into Diagnostice(denumire,descriere) values
('Diagnostic1','DescriereDiagnostic1'),
('Diagnostic2','DescriereDiagnostic2'),
('Diagnostic3','DescriereDiagnostic3'),
('Diagnostic4','DescriereDiagnostic4')
go
insert into Specializari(denumire) values
('Specializare1'),
('Specializare2'),
('Specializare3')
go
insert into Medici(nume,prenume,id_specializare) values
('NumeMedic1','PrenumeMedic1',1),
('NumeMedic2','PrenumeMedic2',1),
('NumeMedic3','PrenumeMedic3',2),
('NumeMedic4','PrenumeMedic4',2)
go
insert into Consultatii(id_medic,id_pacient,id_diagnostic,data_consult,ora_consult,observatii) values
(1,1,1,'2022-02-13','11:00','Consult1'),
(1,2,2,'2022-02-13','11:30','Consult2'),
(3,1,3,'2022-02-14','11:00','Consult3'),
(2,4,1,'2022-02-14','11:00','Consult4')

--2)

create or alter procedure Programare
@id_pacient int,
@id_medic int,
@id_diagnostic int,
@observatii nvarchar(100),
@data_consult date,
@ora_consult time
as
begin
	if exists(select * from Consultatii where id_medic=@id_medic and id_pacient=@id_pacient and data_consult=@data_consult)
	begin
		update Consultatii
		set ora_consult=@ora_consult, id_diagnostic=@id_diagnostic, observatii=@observatii
		where id_medic=@id_medic and id_pacient=@id_pacient and data_consult=@data_consult
	end;
	else
	begin
		insert into Consultatii(id_pacient,id_medic,id_diagnostic,data_consult,ora_consult,observatii) values
		(@id_pacient,@id_medic,@id_diagnostic,@data_consult,@ora_consult,@observatii)
	end;
end;

exec Programare 5,1,1,'dada','2023-01-10','11:00'
exec Programare 5,1,2,'Observatie noua','2023-01-10','12:00'
exec Programare 4,1,2,'Observatie noua','2023-01-10','12:00'
select * from Consultatii
--3)

create or alter view ViewMediciPopulari
as
select M.nume, M.prenume from Medici M
inner join Consultatii C on M.id_medic=C.id_medic
where MONTH(C.data_consult)=MONTH(GETDATE())
group by M.nume, M.prenume
having count(*)>20


select * from ViewMediciPopulari

--4)
--afiseaza, deci habar nu am ce ar trebui sa returneze(tabel???) => fac sa returneze un tabel
-- sa aiba mai mult de o consultatie la aceeasi data si ora?
-- enunt: un consult medical dureaza o ora, iar programul incepe la ora fixa
-- selecteaza medicii care au mai multe consultatii in ziua respectiva cu conditia ca acestia sa aiba o consultatie la ora data?

create or alter function MediciConsultatii(@data date, @ora time)
returns table
as
--begin   <-- Incorrect syntax near 'BEGIN'. 
return select M.nume, M.prenume from Medici M
		inner join Consultatii C on C.id_medic=M.id_medic
		where MONTH(C.data_consult)=MONTH(@data) and
			  YEAR(C.data_consult)=YEAR(@data) and
			  DAY(C.data_consult)=DAY(@data) and 
			  C.ora_consult=@ora

		group by M.nume, M.prenume
		having count(*)>1
--end
	
select * from MediciConsultatii('2023-01-10','12:00')
