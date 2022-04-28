#include "IteratorColectie.h"
#include <exception>


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	//NodIt* p = new NodIt{ NULL_TELEM,nullptr };
	int cate;
	for (int i = 0; i < col.m; i++) {
		if (col.tabela[i] != nullptr) {
			PNod nod = col.tabela[i];
			while (nod != nullptr) {
				cate = nod->element.second;
				while (cate--) {
					NodIt* p = new NodIt{ nod->element.first, nullptr };
					if (first == nullptr)
						first = p;
					else
					{
						p->urm = first;
						first = p;
					}
				}
				nod = nod->urm;
			}
		}
	}
	
	curent = first;
	
}
void IteratorColectie::urmator() {
	if (valid())
		curent = curent->urm;

}


bool IteratorColectie::valid() const {
	
	if (curent == nullptr)
		return false;
	return true;
	
}



TElem IteratorColectie::element() const {
	if (valid())
		return curent->element; 
	
}

void IteratorColectie::prim() {
	curent = first; 
}

IteratorColectie::~IteratorColectie()
{
	
	NodIt* p = first;
	while (p != nullptr)
	{
		NodIt* p2 = p;
		p = p->urm;
		delete p2;
	}
}

NodIt::NodIt(TElem el, NodIt* ur):element{el},urm{ur}{}
