#pragma once
#include <string>

using std::string;

class Masina
{
private:
	int id;
	string nrInmatriculare;
	string producator;
	string model;
	string tip;

public:
	Masina(int id, const string& nrInm, const string& prod, const string& model, const string& tip) :id{id},nrInmatriculare { nrInm }, producator{ prod }, model{ model }, tip{ tip }{}
	const string& getNrInmatriculare() const;
	const string& getProducator() const;
	const string& getModel() const;
	const string& getTip() const;
	int getID() const;
	void setNrInmatriculare(const string& nri);
	void setProducator(const string& pr);
	void setModel(const string& model);
	void setTip(const string& tip);



	Masina& operator=(const Masina& ot) {
		this->id = ot.id;
		this->nrInmatriculare = ot.nrInmatriculare;
		this->producator = ot.producator;
		this->model = ot.model;
		this->tip = ot.tip;
		return *this;
	}


};

