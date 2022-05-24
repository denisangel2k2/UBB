#include "IteratorMDO.h"
#include "MDO.h"

IteratorMDO::IteratorMDO(const MDO& d) : dict(d){
	prim();
}

void IteratorMDO::prim(){
	/* de adaugat */
	curent = dict.minim(dict.rad);
	poz = 0;
}

void IteratorMDO::urmator(){
	if (valid()) {
		poz++;
		if (poz >= curent->e.second.size()) { curent = dict.succesor(curent); poz = 0; }
	}
}

bool IteratorMDO::valid() const{
	if (curent==nullptr)
		return false;
	return true;
}

TElem IteratorMDO::element() const{
	if (valid())
		return TElem(curent->e.first, curent->e.second[poz]);
	else throw std::exception();
	
}


