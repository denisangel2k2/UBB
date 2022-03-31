#include "DynamicVector.h"

void DynamicVector::resize()
{
	TElem* elems_new = new TElem[2 * cp];
	for (int i = 0; i < size; i++)
		elems_new[i] = elems[i];
	cp = 2 * cp;

	delete[] elems;

	elems = elems_new;
}

DynamicVector::DynamicVector(int cap)
{
	elems = new TElem[cap];
	this->cp = cap;
	this->size = 0;
}

DynamicVector::~DynamicVector()
{
	delete[] elems;
}

void DynamicVector::append(TElem element)
{
	if (size == cp)
		resize();
	else {
		elems[size++] = element;
	}
}

int DynamicVector::len() const
{
	return size;
}

TElem DynamicVector::elem(int pos) const
{
	return elems[pos];
}

TElem& DynamicVector::operator[](int pos) const
{
	return elems[pos];
}

void DynamicVector::del(int pos)
{
	for (int i = pos; i < size; i++)
		elems[i] = elems[i + 1];
	size--;
}

Iterator::Iterator(const DynamicVector& vv) : v{vv}
{

	this->curent = 0;
}

void Iterator::prim()
{
	curent = 0;
}

void Iterator::urmator()
{
	curent++;
}

TElem Iterator::element() const
{
	return v.elems[curent];
}

bool Iterator::valid() const
{
	return curent < v.len();
}
DynamicVector& DynamicVector::operator=(const DynamicVector& ot) {
	this->cp = ot.cp;
	TElem* nou = new TElem[ot.cp];
	for (int i = 0; i < ot.size; i++)
		nou[i] = ot.elems[i];
	delete[] this->elems;
	this->elems = nou;
	this->size = ot.size;
	return (*this);
}

Iterator DynamicVector::iterator()
{
	return Iterator{*this};
}
