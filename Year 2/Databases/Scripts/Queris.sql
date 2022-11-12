
-- Toate chitarele care sunt din lemn de stejar
-- distinct,>2,where

SELECT DISTINCT  T.nume_tip, I.model, M.nume_mat
FROM Instrumente I, Tipuri T, Materiale M
WHERE T.id_tip=I.id_tip and T.nume_tip='Chitara' and M.nume_mat='Lemn stejar' and M.id_mat=I.id_material

SELECT DISTINCT T.nume_tip, I.model, M.nume_mat
FROM Instrumente I
	INNER JOIN Tipuri T ON T.id_tip=I.id_tip
	INNER JOIN Materiale M ON M.id_mat=I.id_material
WHERE T.nume_tip='Chitara' and M.nume_mat='Lemn stejar'
--

-- Toate orgile ordonate in mod crescator dupa pret
-- >2,where,
SELECT T.nume_tip, I.model, M.nume_mat, I.pret
FROM Instrumente I, Tipuri T, Materiale M
WHERE I.id_tip=T.id_tip and M.id_mat=I.id_material and T.nume_tip='Orga'
ORDER BY I.pret


SELECT T.nume_tip, I.model, M.nume_mat, I.pret
FROM Instrumente I
	INNER JOIN Tipuri T ON I.id_tip=T.id_tip
	INNER JOIN Materiale M ON I.id_material=M.id_mat
WHERE T.nume_tip='Orga'
ORDER BY I.pret
--

-- Cate instrumente sunt de fiecare tip
-- where,group by
SELECT T.nume_tip as Tip, COUNT(I.id_tip) AS Cate
FROM Tipuri T, Instrumente I
WHERE I.id_tip=T.id_tip
GROUP BY T.nume_tip

SELECT T.nume_tip as Tip, COUNT(I.id_tip) AS Cate
FROM Tipuri T
	INNER JOIN Instrumente I ON I.id_tip=T.id_tip
GROUP BY T.nume_tip
--


-- Cate instrumente sunt de fiecare categorie
-- where, group by

SELECT C.nume_categorie as Categorie, COUNT(I.id_cat) AS Cate
FROM Categorii C, Instrumente I
WHERE I.id_cat=C.id_categorie
GROUP BY C.nume_categorie, I.id_cat

SELECT C.nume_categorie as Categorie, COUNT(I.id_cat) AS Cate
FROM Categorii C
	INNER JOIN Instrumente I ON I.id_cat=C.id_categorie
GROUP BY C.nume_categorie, I.id_cat


-- TOATE INSTRUMENTELE CARE AU FOST FABRICATE PANA IN ANUL 1990
-- distinct, where, group by, having, >2
SELECT DISTINCT T.nume_tip, B.nume_brand, I.model, I.an_fabricatie
FROM Tipuri T, Instrumente I, Branduri B
WHERE T.id_tip=I.id_tip and B.id_brand=I.id_brand
GROUP BY T.nume_tip,B.nume_brand,I.model,I.an_fabricatie
HAVING MAX(I.an_fabricatie)<1990


SELECT DISTINCT T.nume_tip, B.nume_brand, I.model, I.an_fabricatie
FROM Instrumente I
	INNER JOIN Branduri B ON B.id_brand=I.id_brand
	INNER JOIN Tipuri T ON T.id_tip=I.id_tip
GROUP BY T.nume_tip,B.nume_brand,I.model,I.an_fabricatie
HAVING MAX(I.an_fabricatie)<1990

-- Toate chitarele care au coarde produse de brandul Fionix
-- >2,where
SELECT T.nume_tip, I.model, P.nume_prod as Prod_Coarde
FROM Instrumente I, Tipuri T, Coarde C, ProducatoriCoarde P
WHERE I.id_tip=T.id_tip AND T.nume_tip='Chitara' AND I.id_coarda=C.id_coarda AND C.id_prod=P.id_prod and P.nume_prod='Fionix'

SELECT T.nume_tip, I.model, P.nume_prod as Prod_Coarde
FROM Instrumente I 
	INNER JOIN Tipuri T ON I.id_tip=T.id_tip
	INNER JOIN Coarde C ON I.id_coarda=C.id_coarda
	INNER JOIN ProducatoriCoarde P ON C.id_prod=P.id_prod
WHERE T.nume_tip='Chitara' AND P.nume_prod='Fionix'

-- Cum fac sa am doua campuri de brand, diferite
SELECT I.id_instr,B.nume_brand, I.model, H.culoare as Culoare_Husa, Branduri.nume_brand as Brand_husa
FROM Branduri B,Instrumente I,Huse H
WHERE Instrumente.id_husa=Huse.id_husa and Instrumente.id_brand=Branduri.id_brand and 


-- Toate instrumentele cu husa de culoare rosie
-- >2, where
SELECT Branduri.nume_brand, Instrumente.model, Huse.culoare as [Culoare Husa]
FROM Branduri,Instrumente,Huse
WHERE Instrumente.id_husa=Huse.id_husa and Instrumente.id_brand=Branduri.id_brand and Huse.culoare='Rosu'

SELECT B.nume_brand, I.model, H.culoare as [Culoare Husa]
FROM Instrumente I
	INNER JOIN Branduri B ON I.id_brand=B.id_brand
	INNER JOIN Huse H ON I.id_husa=H.id_husa
WHERE H.culoare='Rosu'

-- DOAR INSTRUMENTELE CARE SUNT SEMNATE
-- >2
SELECT T.nume_tip, B.nume_brand, I.model,I.an_fabricatie, S.nume_muzician as Semnatura
FROM Instrumente I
	INNER JOIN Semnaturi S ON S.id_semnatura=I.id_semnatura
	INNER JOIN Branduri B ON B.id_brand=I.id_brand
	INNER JOIN Tipuri T ON T.id_tip=I.id_tip
ORDER BY Semnatura

-- toate instrumentele semnate cu pretul mai mic decat 850
-- group by,where,having, >2
SELECT T.nume_tip, B.nume_brand, I.model, I.an_fabricatie, I.pret, S.nume_muzician as Semnatura
FROM Tipuri T, Instrumente I, Branduri B,Semnaturi S
WHERE T.id_tip=I.id_tip and B.id_brand=I.id_brand and S.id_semnatura=I.id_semnatura
GROUP BY T.nume_tip,B.nume_brand,I.model,I.an_fabricatie,I.pret,S.nume_muzician
HAVING MAX(I.pret)<850


--Toate instrumentele impreuna cu culorile
-- where >2,mn
SELECT T.nume_tip,I.model,C.culoare
FROM Instrumente I, InstrumenteColorate IC, Culori C, Tipuri T
WHERE I.id_instr=IC.id_instrument and IC.id_culoare=C.id_culoare and T.id_tip=I.id_tip


-- Toate instrumentele distincte de la brandul Fender din material Lemn stejar
-- mn,where,>2,distinct
SELECT DISTINCT T.nume_tip,B.nume_brand,I.model,M.nume_mat
FROM Instrumente I, Branduri B, Materiale M, Tipuri T
WHERE I.id_brand=B.id_brand and I.id_material=M.id_mat and T.id_tip=I.id_tip and M.nume_mat='Lemn stejar' and B.nume_brand='Fender'
