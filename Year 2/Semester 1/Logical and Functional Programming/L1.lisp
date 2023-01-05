;a)Sa  se  construiasca  o  functie  care  intoarce  produsul  atomilor  numerici dintr-o lista, de la nivelul superficial.

;l - lista pe care calculam produsul superficial
(defun produsSuperficial(l)
    (cond
        ((null l) 1)
        ((numberp (car l)) (* (car l) (produsSuperficial (cdr l))))
        (T (produsSuperficial (cdr l)))
    )
)
(print (produsSuperficial '(1 2 (3 4) 4)))
;b)Sa  se  scrie  o  functie  care,  primind  o  lista,  intoarce  multimea  tuturor perechilor din lista. De exemplu: (a b c d) --> ((a b) (a c) (a d)(b c) (b d) (c d))

;e - elementul cu care facem perechi
;l - lista cu care facem perechile
(defun pereche(e l) 
    (cond
        ((null l) ())
        (T (cons (list e (car l)) (pereche e (cdr l))))
    )
)

;l - lista pe care facem perechi
(defun perechi(l)
    (cond
        ((null l) ())
        (T (append (pereche (car l) (cdr l)) (perechi (cdr l)) ))
    )
)

(print (perechi '(A B C D)))

;c)Sa se determine rezultatul unei expresii aritmetice memorate in preordine pe o stiva. 
;Exemple:(+ 1 3) ==> 4 (1 + 3)   (+ * 2 4 3) ==> 11 ((2 * 4) + 3)(+ * 2 4 -5 * 2 2) ==> 9 ((2 * 4) + (5 -(2 * 2))

;operator - operator matematic
;a - primul operand
;b - al doilea operand
(defun calcul(operator a b)
    (cond 
        ((string= operator "+")(+ a b))
        ((string= operator "-")(- a b))
        ((string= operator "*")(* a b))
        ((string= operator "/")(floor a b))
    )
)
;l - lista expresia data in preordine
(defun expresie(l)
    (cond
        ((null l) nil)
        ( (and (atom (car l)) (numberp (cadr l)) (numberp (caddr l)) ) (cons (calcul (car l) (cadr l) (caddr l)) (expresie (cdddr l))))
        (T (cons (car l) (expresie (cdr l))))
    )
)
;l - lista expresia data in preordine, in final va fi un numar
(defun rezultat(l)
    (cond
        ((null (cdr l)) (car l))
        (T (rezultat (expresie l) ))
    )
)

(print (rezultat '(+ * 2 4 - 5 * 2 2)))


;d)Definiti  o  functie  care,  dintr-o  lista  de  atomi,  produce  o  lista  de perechi (atom n), unde atom apare in lista initiala de n ori. De ex:(A B A B A C A) --> ((A 4) (B 2) (C 1)).

;l - lista in care numaram aparitiile elementului e
;e - elementul pe care il cautam in lista
(defun nrAparitii(l e)
    (cond
        ((null l) 0)
        ((equal (car l) e) (+ 1 (nrAparitii (cdr l) e)))
        (T (nrAparitii (cdr l) e))
    )
)
;(print (nrAparitii '(A B A B B A C) 'B))

;l - lista din care stergem toate elementele e
;e - elementul pe care il stergem
(defun removeAp(l e)
    (cond
        ((null l) nil)
        ((equal e (car l)) (removeAp (cdr l) e))
        (T (cons (car l) (removeAp (cdr l) e)))
    )
)
;(print (removeAp '(A B A B B A C) 'B))

;l - lista pe care numaram aparitiile fiecarui element din lista
(defun perechiNr(l)
    (cond
        ((null l) nil)
        (T (cons (list (car l) (nrAparitii l (car l))) (perechiNr (removeAp l (car l)))))
    )
)

(print (perechiNr '(A B A B A C A)))

