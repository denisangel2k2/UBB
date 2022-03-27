#include "Domain.h"
#include <iostream>


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

void Masina::setModel(const string& model)
{
	this->model = model;
}

void Masina::setTip(const string& tip)
{
	this->tip = tip;
}




