#pragma once
#include <vector>
#include <string>
#include "Domain.h"
using namespace std;

class Repository
{

private:

	vector<Masina>lista;
	vector<Masina>lista_fictiva;

public:
	int add_fictiv(const Masina& m);
	/// <summary>
	/// Adauga o masina la repo
	/// </summary>
	/// <param name="m">Masina</param>
	/// <returns>1 - daca adauga cu succes  exceptie - nu poate fi adaugat</returns>
	int add(const Masina& m);
	/// <summary>
	/// Sterge o masina din repo
	/// </summary>
	/// <param name="id">int</param>
	/// <returns>1 - daca a fost sterg cu succes  exceptie - altfel</returns>
	int del(int id);
	/// <summary>
	/// Actualizeaza o masina din repo
	/// </summary>
	/// <param name="m">Masina</param>
	/// <returns>1 - daca a fost actualizat cu succes  exceptie - altfel</returns>
	int update(const Masina& m);
	/// <summary>
	/// Functie care cauta o masina dupa id in repo
	/// </summary>
	/// <param name="id">int</param>
	/// <returns>1 - daca exista masina in repo, 0 altfel</returns>
	int find(int id);
	/// <summary>
	/// Functie care cauta o masina dupa id in repo
	/// </summary>
	/// <param name="id">int</param>
	/// <returns>Masina gasita, exceptie altfel</returns>
	const Masina& findCar(int id) const; 
	/// <summary>
	/// Functie care returneaza lungimea repo-ului
	/// </summary>
	/// <returns>size_t</returns>
	size_t size() noexcept;
	const size_t sizeAdmin() noexcept;
	/// <summary>
	/// Functie care returneaza o copie a intregului repo
	/// </summary>
	/// <returns> vector of Masina type </returns>
	const vector<Masina>& getAll() const;
	const vector<Masina>& getAllFictiv() const;
	const size_t getNumberOfCars() const;
	void clearRepo();

	void clearRepoFictiv();
};

