-- pentru testul 2
create view ViewCoardeSiProducatori
as 
SELECT P.nume_prod, C.material_coarda
FROM ProducatoriCoarde P 
INNER JOIN Coarde C 
ON P.id_prod=C.id_prod;

create view ViewNrInstrumenteTipuri
as
SELECT T.nume_tip,COUNT(*) AS Cate
FROM Tipuri T 
INNER JOIN Instrumente I ON T.id_tip=I.id_tip
GROUP BY T.nume_tip;

--pentru testul 3

create view ViewTotal
as
SELECT T.nume_tip,C.nume_categorie,I.model,M.nume_mat,Co.material_coarda
FROM Instrumente I 
	INNER JOIN Categorii C ON C.id_categorie=I.id_cat
	INNER JOIN Coarde Co ON Co.id_coarda=I.id_coarda
	INNER JOIN Materiale M ON M.id_mat=I.id_material
	INNER JOIN Tipuri T ON T.id_tip=I.id_tip



