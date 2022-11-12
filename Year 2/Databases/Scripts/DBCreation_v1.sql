CREATE TABLE Culori
(
	id_culoare INT PRIMARY KEY IDENTITY,
	culoare VARCHAR(20)
);

ALTER TABLE Instrumente
DROP COLUMN culoare;




CREATE TABLE Huse
(
	id_husa INT PRIMARY KEY IDENTITY,
	id_brand INT FOREIGN KEY(id_brand) REFERENCES Branduri(id_brand),
	id_culoare INT FOREIGN KEY(id_culoare) REFERENCES Culori(id_culoare)

);

ALTER TABLE Instrumente
ADD id_culoare INT FOREIGN KEY(id_culoare) REFERENCES Culori(id_culoare);

ALTER TABLE Instrumente
ADD id_husa INT FOREIGN KEY(id_husa) REFERENCES Huse(id_husa);



CREATE TABLE InstrumenteColorate
(
	id_instrument INT,
	id_culoare INT,
	CONSTRAINT fk_Instrument FOREIGN KEY(id_instrument) REFERENCES Instrumente(id_instr),
	CONSTRAINT fk_Culoare FOREIGN KEY(id_culoare) REFERENCES Culori(id_culoare),
	CONSTRAINT pk_InstrumentColorat PRIMARY KEY(id_instrument,id_culoare)
);
ALTER TABLE Instrumente
DROP COLUMN id_culoare;

ALTER TABLE Huse
DROP COLUMN id_culoare;

CREATE TABLE HuseColorate
(
	id_husa INT,
	id_culoare INT,
	CONSTRAINT fk_Husa FOREIGN KEY(id_husa) REFERENCES Huse(id_husa),
	CONSTRAINT fk_CuloareHusa FOREIGN KEY(id_culoare) REFERENCES Culori(id_culoare),
	CONSTRAINT pk_HusaColorata PRIMARY KEY(id_husa,id_culoare)
);

ALTER TABLE Huse
ADD culoare VARCHAR(20);
