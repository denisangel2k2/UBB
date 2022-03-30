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
	
	const Masina& srv_findCar(int id) const;

	vector<Masina>filter(const string& what, int whichFilter) const;
	vector<Masina>sort(function<bool(const Masina& m1, const Masina& m2)>compareFunction) const;
	
	vector<Masina> srv_getAll() const;

};

