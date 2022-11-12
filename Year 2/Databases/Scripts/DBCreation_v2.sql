CREATE TABLE Tipuri
(
id_tip INT PRIMARY KEY IDENTITY,
nume_tip VARCHAR(20) NOT NULL UNIQUE
);

CREATE TABLE Materiale
(
id_mat INT PRIMARY KEY IDENTITY,
nume_mat VARCHAR(20) NOT NULL UNIQUE

);

CREATE TABLE Categorii
(
id_cat INT PRIMARY KEY IDENTITY,
nume_cat VARCHAR(20) NOT NULL UNIQUE
);

CREATE TABLE BranduriInstrumente
(
id_brand INT PRIMARY KEY IDENTITY,
nume_brand VARCHAR(20) NOT NULL UNIQUE
);

CREATE TABLE ProducatoriCoarde
(
id_prod INT PRIMARY KEY IDENTITY,
nume_prod VARCHAR(20) NOT NULL UNIQUE
);

CREATE TABLE Coarde
(
id_coarda INT PRIMARY KEY IDENTITY,
material_coarda VARCHAR(20) NOT NULL,
id_prod INT FOREIGN KEY REFERENCES ProducatoriCoarde(id_prod)

);
CREATE TABLE Materiale
(
id_material INT PRIMARY KEY IDENTITY,
nume_material VARCHAR(20) NOT NULL
);

CREATE TABLE Instrumente
(
id_instr INT PRIMARY KEY IDENTITY,
id_tip INT,
id_coarda INT,
id_brand INT,
culoare VARCHAR(30) NOT NULL,
model VARCHAR(50) NOT NULL,
an_fabricatie INT 
CONSTRAINT fk_Branduri FOREIGN KEY(id_brand) REFERENCES BranduriInstrumente(id_brand),
CONSTRAINT fk_Tipuri FOREIGN KEY(id_tip) REFERENCES Tipuri(id_tip),
CONSTRAINT fk_Coarde FOREIGN KEY(id_coarda) REFERENCES Coarde(id_coarda)
);

ALTER TABLE Instrumente
ADD id_cat INT FOREIGN KEY(id_cat) REFERENCES Categorii(id_cat);
