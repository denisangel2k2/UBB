#include <assert.h>
#include <exception>

#include "TestScurt.h"
#include "LI.h"
#include "IteratorLI.h"
#include "DynamicVector.h"
#include <iostream>

using namespace std;



void testAll() {
    LI lista = LI();
    assert(lista.vida());
    lista.adaugaSfarsit(1);
    assert(lista.dim() == 1);
    lista.adauga(0,2);
    assert(lista.dim() == 2);

    IteratorLI it = lista.iterator();
    assert(it.valid());
    it.urmator();

    assert(it.element() == 1);

    it.prim();
    

    assert(it.element() == 2);
    assert(lista.cauta(1) == 1);
    assert(lista.modifica(1,3) == 1);
    assert(lista.element(1) == 3);
    assert(lista.sterge(0) == 2);
    assert(lista.dim() == 1);
    
    LI lista2 = LI();
    lista2.adaugaSfarsit(3);
    lista2.adaugaSfarsit(4);
    lista2.adaugaSfarsit(4);
    lista2.adaugaSfarsit(5);
    lista2.adaugaSfarsit(6);

    assert(lista2.ultimulIndex(4) == 2);
    assert(lista2.ultimulIndex(3) == 0);
    assert(lista2.ultimulIndex(5) == 3);
    assert(lista2.ultimulIndex(8) == -1);
    assert(lista2.ultimulIndex(6) == lista2.dim()-1);
    
}
