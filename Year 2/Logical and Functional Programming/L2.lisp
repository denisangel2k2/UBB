;6. Sa se construiasca lista nodurilor unui arbore de tipul (1) parcurs in inordine.
;(A 2 B 0 C 2 D 0 E 0)


;parcurge_stanga(l1 l2 ... ln, nr_varfuri, nr_muchii) = vida, daca n=0 sau nr_muchii+1=nr_varfuri
;                                                      l1+l2+parcurge_stanga(l3 ... ln, nr_varfuri+1, nr_muchii+l2), altfel  
;parcurge_stanga(arbore,nr_varfuri,nr_muchii)
;arbore - lista ce reprezinta arborele
;nr_varfuri - nr de varfuri curent
;nr_muchii - nr de muchii curent

(defun parcurge_stanga(arbore nr_varfuri nr_muchii)

    (cond
        ((null arbore) nil)
        ((= nr_varfuri (+ 1 nr_muchii)) nil)
        ;(T (append (list (car arbore)) (list (cadr arbore)) (parcurge_stanga (cddr arbore) (+ 1 nr_varfuri) (+ (cadr arbore) nr_muchii))))
        (T (cons (car arbore) (cons (cadr arbore) (parcurge_stanga (cddr arbore) (+ 1 nr_varfuri) (+ (cadr arbore) nr_muchii)))))
    )
)


;parcurge_dreapta(l1 l2 ... ln, nr_varfuri, nr_muchii) = vida, daca n=0 
;                                                       l1 l2 ... ln, daca nr_muchii+1=nr_varfuri
;                                                      parcurge_dreapta(l3 ... ln, nr_varfuri+1, nr_muchii+l2), altfel  

;parcurge_dreapta(arbore,nr_varfuri,nr_muchii)
;arbore - lista ce reprezinta arborele
;nr_varfuri - nr de varfuri curent
;nr_muchii - nr de muchii curent

(defun parcurge_dreapta(arbore nr_varfuri nr_muchii)

    (cond
        ((null arbore) nil)
        ((= nr_varfuri (+ 1 nr_muchii)) arbore)
        (T (parcurge_dreapta (cddr arbore) (+ 1 nr_varfuri) (+ (cadr arbore) nr_muchii)))
    )

)

;stanga(l1 l2 ... ln) = parcurge_stanga(l3 l4 ... ln, 0, 0)
;stanga(arbore)
;arbore - lista ce reprezinta arborele
(defun stanga(arbore)

    (parcurge_stanga (cddr arbore) 0 0)
)


;dreapta(l1 l2 ... ln) = parcurge_dreapta(l3 l4 ... ln, 0, 0)
;dreapta (arbore)
;arbore - lista ce reprezinta arborele
(defun dreapta(arbore)

    (parcurge_dreapta (cddr arbore) 0 0)
)


(print (stanga '(A 2 B 0 C 2 D 0 E 0)))
(print (dreapta '(A 2 B 0 C 2 D 0 E 0)))


;inorder(l1 l2 ... ln)= vida, daca n=0
;                       inorder(stanga(l1 l2 ... ln)) + (l1) + inorder(dreapta(l1 l2 ... ln)) altfel
;inorder(arbore)
;arbore - lista ce reprezinta arborele
(defun inorder(arbore)
    (cond
        ((null arbore) nil)
        (T (append (inorder (stanga arbore) )  (list (car arbore))  (inorder (dreapta arbore) ) ) )
    )
)

(print (inorder '(A 2 B 0 C 2 D 0 E 0)))