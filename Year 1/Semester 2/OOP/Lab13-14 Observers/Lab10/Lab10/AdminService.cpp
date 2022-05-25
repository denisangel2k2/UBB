#include "AdminService.h"
#include <random>
#include "Domain.h"
#include <vector>
#include <fstream>

using std::vector;


void AdminService::exportSrv(string filepath)
{
	filepath = filepath + "/output.csv";
	std::ofstream fout(filepath);
	vector<Masina>v = repo.getAllFictiv();
	if (fout.is_open())
	{
		for(const auto& masina:v)
			fout << to_string(masina.getID()) << "," << masina.getNrInmatriculare() << "," << masina.getProducator() << "," << masina.getModel() << "," << masina.getTip() << '\n';

	}
	
}

const size_t AdminService::srv_getNumberOfCars() const
{
	return repo.sizeAdmin();
}

int AdminService::srv_add(const string& nrI)
{

	vector<Masina> v = repo.getAll();
	auto m = find_if(v.begin(), v.end(), [&](const Masina& ot) {if (ot.getNrInmatriculare() == nrI)
		return 1;
	return 0; });
	if (m != v.end())
		srv_add_fictiv((*m).getID(), (*m).getNrInmatriculare(), (*m).getProducator(), (*m).getModel(), (*m).getTip());

	else throw runtime_error("Nu exista masina!\n");

	return 1;
}

void AdminService::srv_clearRepo()
{
	repo.clearRepoFictiv();
}


const vector<Masina>& AdminService::srv_getall()
{
	return this->repo.getAllFictiv();
}

int AdminService::addRandom(int numberToAdd)
{

	int rndNr = 1;
	int size = (int)repo.size();
	cout << size;
	
	if (size > 0) {
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, size-1);
		int cateAdaugate = 0;

		while (cateAdaugate < numberToAdd) {
			rndNr = dist(mt);
			try {
				Masina m = repo.findCarIndex(rndNr);
				srv_add_fictiv(m.getID(), m.getNrInmatriculare(), m.getProducator(), m.getModel(), m.getTip());
				cateAdaugate++;
			}
			catch (const exception&) {
				continue;
			}
		}
		return cateAdaugate;
	}
	else throw runtime_error("Nu s-a putut adauga!\n");
	//return 1;
}

int AdminService::srv_add_fictiv(int id, const string& nrI, const string& prod, const string& model, const string& tip)
{
	Masina m{ id,nrI,prod,model,tip };
	valid.validate(m);
	repo.add_fictiv(m);
	notify();
	return 1;
}