#pragma once
#include <string>
#include <iostream>
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
	Masina() = default;
	Masina(int id, const string& nrInm, const string& prod, const string& model, const string& tip) :id{ id }, nrInmatriculare{ nrInm }, producator{ prod }, model{ model }, tip{ tip }{}
	Masina(const Masina& ot);
	/// <summary>
	/// Functia care returneaza nr inmatriculare
	/// </summary>
	/// <returns></returns>
	const string& getNrInmatriculare() const noexcept;
	/// <summary>
	/// Functia care returneaza producatorul
	/// </summary>
	/// <returns></returns>
	const string& getProducator() const noexcept;
	/// <summary>
	/// Functia care returneaza modelul
	/// </summary>
	/// <returns></returns>
	const string& getModel() const noexcept;
	/// <summary>
	/// Functia care returneaza tipul
	/// </summary>
	/// <returns></returns>
	const string& getTip() const noexcept;
	/// <summary>
	/// Functia care returneaza id
	/// </summary>
	/// <returns></returns>
	int getID() const noexcept;
	/// <summary>
	/// Functia care seteaza numarul de inmatriculare
	/// </summary>
	/// <param name="nri"></param>
	void setNrInmatriculare(const string& nri);
	/// <summary>
	/// Functia care seteaza producatorul
	/// </summary>
	/// <param name="pr"></param>
	void setProducator(const string& pr);
	/// <summary>
	/// Functia care seteaza modelul
	/// </summary>
	/// <param name="model"></param>
	void setModel(const string& model);
	/// <summary>
	/// Functia care seteaza tipul
	/// </summary>
	/// <param name="tip"></param>
	void setTip(const string& tip);
	
	


	Masina& operator=(const Masina& ot) {
		this->id = ot.id;
		this->nrInmatriculare = ot.nrInmatriculare;
		this->producator = ot.producator;
		this->model = ot.model;
		this->tip = ot.tip;
		return *this;
	}

	bool operator==(const Masina& ot) noexcept {
		return ((this->id == ot.id) && (this->nrInmatriculare == ot.nrInmatriculare) && (this->producator == ot.producator) && (this->model == ot.model) && (this->tip == ot.tip));
	}


};

