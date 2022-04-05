#pragma once
#include "Repository.h"
#include "Valid.h"
#include "Domain.h"
#include <functional>

class Service
{
private:
	Repository& repo;
	Valid& valid;

public:

	Service(Repository& rep, Valid& _valid);
	/// <summary>
	/// Functie care creeaza, valideaza si adauga in repo o masina
	/// </summary>
	/// <param name="id">int</param>
	/// <param name="nrI">string</param>
	/// <param name="prod">string</param>
	/// <param name="model">string</param>
	/// <param name="tip">string</param>
	/// <returns>1 - daca a fost adaugat cu succes  exceptie - altfel</returns>
	int srv_add(int id, const string& nrI, const string& prod, const string& model, const string& tip);
	/// <summary>
	/// Functie care sterge o masina dupa id
	/// </summary>
	/// <param name="id">int</param>
	///<returns>1 - daca a fost sters cu succes  exceptie - altfel</returns>
	int srv_del(int id);
	/// <summary>
	/// Functie care actualizeaza o masina dupa id-ul dat cu atributele date ca si parametri
	/// </summary>
	/// <param name="id">int</param>
	/// <param name="nrI">string</param>
	/// <param name="prod">string</param>
	/// <param name="model">string</param>
	/// <param name="tip">string</param>
	/// <returns>1 - daca a fost actualizat cu succes  exceptie - altfel</returns>
	int srv_update(int id, const string& nrI, const string& prod, const string& model, const string& tip);
	/// <summary>
	/// Functie care cauta si returneaza o masina
	/// pre : id - int
	/// post : masina
	/// </summary>
	const Masina& srv_findCar(int id) const;
	/// <summary>
	/// Functia care filtreaza in functie de parametrul dat
	/// pre : what - string 
	///		whichFilter - int
	/// post : DynamicVector<Masina>
	/// </summary>
	//DynamicVector<Masina> filter(const string& what, int whichFilter) const;
	DynamicVector<Masina> filter(const string& what, int whichFilter) const;
	/// <summary>
	/// Functia care sorteaza in functie de parametrul dat
	/// pre : *functie
	/// post : DynamicVector<Masina>
	/// </summary>
	//DynamicVector<Masina>sort(function<bool(const Masina& m1, const Masina& m2)>compareFunction) const;
	DynamicVector<Masina> sort(function<bool(const Masina& m1, const Masina& m2)>compareFunction) const;
	/// <summary>
	/// Functia care returneaza getAll
	/// pre : what - string 
	///		whichFilter - int
	/// post : DynamicVector<Masina>
	/// </summary>
	//DynamicVector<Masina> srv_getAll() const;
	DynamicVector<Masina>srv_getAll() const;
};

