#include "Domain.h"
#include <iostream>

/*
Masina::Masina(const Masina& ot)
{
	this->id = ot.id;
	this->nrInmatriculare = ot.nrInmatriculare;
	this->model = ot.model;
	this->tip = ot.tip;
}
*/
const string& Masina::getNrInmatriculare() const
{
	return this->nrInmatriculare;
}

const string& Masina::getProducator() const
{
	return this->producator;
}

const string& Masina::getModel() const
{
	return this->model;
}

const string& Masina::getTip() const
{
	return this->tip;
}

int Masina::getID() const
{
	return this->id;
}

void Masina::setNrInmatriculare(const string& nri)
{
	this->nrInmatriculare = nri;
}

void Masina::setProducator(const string& pr)
{
	this->producator = pr;
}

void Masina::setModel(const string& _model)
{
	this->model = _model;
}

void Masina::setTip(const string& _tip)
{
	this->tip = _tip;
}




