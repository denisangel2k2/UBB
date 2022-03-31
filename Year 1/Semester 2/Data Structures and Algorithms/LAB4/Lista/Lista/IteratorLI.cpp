#include "IteratorLI.h"
#include "LI.h"
#include <exception>
#include <iostream>

using std::cout;
IteratorLI::IteratorLI(const LI& li) : lista{ li } {
 	/* de adaugat */

    curent = lista.prim;
   
}

void IteratorLI::prim(){
 	/* de adaugat */
    curent = lista.prim;
   // cout << lista.elemente[curent] << "\n";
}

void IteratorLI::urmator(){
 	/* de adaugat */
    if (valid())
        curent = lista.urmator[curent];
    else 
        throw std::exception();

}

bool IteratorLI::valid() const{
 	/* de adaugat */
    if (curent == nothing)
        return false;
    else return true;
}

TElem IteratorLI::element() const{
 	/* de adaugat */
    if (valid())
        return lista.elemente[curent];
    else throw std::exception();
	return -1;
}
