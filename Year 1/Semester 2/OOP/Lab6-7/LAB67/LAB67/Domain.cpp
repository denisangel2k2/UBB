#include "Domain.h"
#include <iostream>




Masina::Masina(const Masina& ot)
{
	this->id = ot.id;
	this->nrInmatriculare = ot.nrInmatriculare;
	this->producator = ot.producator;
	this->model = ot.model;
	this->tip = ot.tip;
	std::cout << "Masina creata!\n";
}

const string& Masina::getNrInmatriculare() const noexcept
{
	return this->nrInmatriculare;
}

const string& Masina::getProducator() const noexcept
{
	return this->producator;
}

const string& Masina::getModel() const noexcept
{
	return this->model;
}

const string& Masina::getTip() const noexcept
{
	return this->tip;
}

int Masina::getID() const noexcept
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




