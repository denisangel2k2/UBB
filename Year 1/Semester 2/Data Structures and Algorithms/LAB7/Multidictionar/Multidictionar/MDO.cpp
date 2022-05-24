#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>
#include <queue>
#include <exception>
using namespace std;

MDO::MDO(Relatie r) {
	rel = r;
	rad = nullptr;
}

PNod MDO::adauga_rec(PNod p, TCheie c, TValoare v, PNod p_ant) // O(h)
{
	if (p == nullptr)
	{
		p = new Nod(TElem(c, v), nullptr, nullptr, p_ant);
	}
	else if (p->e.first == c) {
		p->e.second.push_back(v);

	}
	else if (!rel(p->e.first, c)) {
		p->st = adauga_rec(p->st, c, v,p);
	}
	else if (rel(p->e.first, c)) {
		p->dr = adauga_rec(p->dr, c, v,p);
	}
	return p;

}


void MDO::adauga(TCheie c, TValoare v) { //O(h)
	rad = adauga_rec(rad, c, v,nullptr);
}
PNod MDO::cauta_rec(PNod r, TCheie c) const{ //O(h)
	if (r == nullptr) return nullptr;
	else if (r->e.first == c) return r;
	else if (!rel(r->e.first, c)) return cauta_rec(r->st, c);
	else if(rel(r->e.first, c)) return cauta_rec(r->dr, c);
}
PNod MDO::minim(PNod p)  const{ //teta(h)
	if (p == nullptr) return p;
	while (p->st != nullptr)
		p = p->st;
	return p;
	
}
PNod MDO::succesor(PNod p) const //o(h)
{

	if (p->dr != nullptr)
		return minim(p->dr);
	else {
		auto prec = p->tata;
		while (prec != nullptr && p == prec->dr) {
			p = prec;
			prec = p->tata;
		}
		return prec;
	}
}
PNod MDO::sterge_rec(PNod p, TCheie c, TValoare v)
{
	return nullptr;

}
vector<TValoare> MDO::cauta(TCheie c) const {  
	PNod r = cauta_rec(rad, c);
	if (r == nullptr) return {};
	return r->e.second;
}

bool MDO::sterge(TCheie c, TValoare v) { //o(h)
	
	PNod r = cauta_rec(rad, c);
	if (r == nullptr) return false;

	auto it = std::find(r->e.second.begin(), r->e.second.end(), v);
	if (it == r->e.second.end()) return false;

	r->e.second.erase(it);
	if (r->e.second.size() != 0) return true;


	if (r->dr == nullptr && r->st == nullptr)
	{
		if (r != rad) {
			if (r->tata->st == r)
				r->tata->st == nullptr;
			else r->tata->dr = nullptr;
		}
		else {
			rad = nullptr;
		}
		delete r;
	}
	else if (r->dr!=nullptr) {
		PNod temp = minim(r->dr);

		if (temp == r->dr) {
			if (temp->dr!=nullptr)
				temp->dr->tata = r;
			r->dr = temp->dr;
		}
		else { 
			if (temp->dr != nullptr)
				temp->dr->tata = temp->tata;
			temp->tata->st = temp->dr;
		}
		
		r->e.first = temp->e.first;
		r->e.second = temp->e.second;
		delete temp;
	}
	else {
		if (r == rad) {
			rad = r->st;
			delete r;
		}
		else {
			r->st->tata = r->tata;
			if (r->tata->dr == r)
				r->tata->dr = r->st;
			else
				r->tata->st = r->st;
			delete r;
		}
	}
	return true;
	
}

int MDO::dim() const{ // teta(n), n - nr chei
	/* de adaugat */
	int dimensiune = 0;
	if (rad == nullptr)
		dimensiune = 0;
	else {
		queue<PNod>q;
		q.push(rad);
		while (!q.empty()) {
			PNod p = q.front();
			q.pop();
			if (p->st != nullptr)
				q.push(p->st);
			if (p->dr != nullptr)
				q.push(p->dr);
			dimensiune += p->e.second.size();
		}
	}

	return dimensiune;
	
}

bool MDO::vid() const { // teta(1)
	return rad == nullptr;
}

IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}

MDO::~MDO() { // teta(n)
	if (rad != nullptr) {
		queue<PNod>q;
		q.push(rad);
		while (!q.empty()) {
			PNod p = q.front();
			q.pop();
			if (p->st != nullptr)
				q.push(p->st);
			if (p->dr != nullptr)
				q.push(p->dr);
			delete p;
		}
	}
	
		
}

Nod::Nod(TElem e, PNod st, PNod dr, PNod tata) // teta(1)
{
	this->e.first = e.first;
	this->e.second.push_back(e.second);
	this->st = st;
	this->dr = dr;
	this->tata = tata;
}

PNod Nod::stanga()
{
	return this->st;
}

PNod Nod::dreapta()
{
	return this->dr;
}

pair < TCheie, vector<TValoare> >& Nod::element()
{
	return e;
}
