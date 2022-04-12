#include "UI.h"
#include <iostream>
void UI::filterUI()
{
	string cmd;
	cout << "Introduceti modul filtrarii(prod/tip): ";
	cin >> cmd;
	if (cmd == "prod") {
		string producator;

		cout << "Introduceti producator: ";
		cin >> producator;

		vector<Masina>v = srv.filter(producator, 1);
		for (const auto& el : v)
			cout <<"ID: "<< el.getID() << " Nr. Inm:" << el.getNrInmatriculare() << " Model:" << el.getModel() << " Producator:" << el.getProducator() << " Tip:" << el.getTip() << '\n';

		
	}

	else if (cmd == "tip") {
		string tip;

		cout << "Introduceti tip: ";
		cin >> tip;

		vector<Masina>v = srv.filter(tip, 2);
		for (const auto& el : v)
			cout <<"ID: "<< el.getID() << " Nr. Inm:" << el.getNrInmatriculare() << " Model:" << el.getModel() << " Producator:" << el.getProducator() << " Tip:" << el.getTip() << '\n';

	}

	else cout << "Comanda invalida!";
	cout << "\n\n\n";
}
void UI::sortUI()
{
	string cmd;
	cout << "Sortare dupa(nrInm=1,tip=2,prod+model=3): ";
	getline(cin, cmd);

	if (cmd == "1") {
		vector<Masina>v = srv.sort([](const Masina& m1, const Masina& m2) {if (m1.getNrInmatriculare() < m2.getNrInmatriculare()) return true; else return false; });
		for (const auto& el : v)
			cout <<"ID: "<< el.getID() << " Nr. Inm:" << el.getNrInmatriculare() << " Model:" << el.getModel() << " Producator:" << el.getProducator() << " Tip:" << el.getTip() << '\n';


	}
	else if (cmd == "2") {
		vector<Masina>v = srv.sort([](const Masina& m1, const Masina& m2) {if (m1.getTip() < m2.getTip()) return true; else return false; });
		for (const auto& el : v)
			cout <<"ID: "<< el.getID() << " Nr. Inm:" << el.getNrInmatriculare() << " Model:" << el.getModel() << " Producator:" << el.getProducator() << " Tip:" << el.getTip() << '\n';

	}
	else if (cmd == "3") {
		vector<Masina>v = srv.sort([](const Masina& m1, const Masina& m2) {
			if (m1.getProducator() < m2.getProducator())
				return true;
			else if (m1.getProducator() == m2.getProducator())
				if (m1.getModel() < m2.getModel())
					return true;
				else return false;
			else return false;
			});
		for (const auto& el : v)
			cout <<"ID: "<< el.getID() << " Nr. Inm:" << el.getNrInmatriculare() << " Model:" << el.getModel() << " Producator:" << el.getProducator() << " Tip:" << el.getTip() << '\n';

	}
	else cout << "Comanda invalida\n";
	cout << "\n\n\n";
}
void UI::showUI()
{
	cout << "Lista de comenzi:\n\n";
	cout << "'add' - adauga o masina\n";
	cout << "'del' - sterge o masina\n";
	cout << "'update' - modifica o masina\n";
	cout << "'print' - tipareste masinile\n";
	cout << "'find' - gaseste o masina\n";
	cout << "'filter' - filtreaza masinile\n";
	cout << "'sort' - sorteaza masinile\n";
	cout << "'add2' - adauga o masina dupa numar de inmatriculare\n";
	cout << "'clear' - goleste lista de masini\n";
	cout << "'random' - adauga n masini\n";
	cout << "'help - tipareste acest meniu\n";
	cout << "'exit' - iesire\n";


}
void UI::addUI()
{
	string id;
	string nrI;
	string prod;
	string model;
	string tip;
	//cin.ignore();
	cout << "Introduceti ID:\n";
	getline(cin, id);
	cout << "Introduceti Nr. inmatriculare:\n";
	getline(cin, nrI);
	cout << "Introduceti producator:\n";
	getline(cin, prod);
	cout << "Introduceti model:\n";
	getline(cin, model);
	cout << "Introduceti tip:\n";
	getline(cin, tip);
	if (id.length() > 16)
		cout << "ID-ul este prea mare!\n";
	else {
		int id_int=0;
		
		try {
			id_int = stoi(id);
		}
		catch (exception&) {

			cout << "ID-ul este invalid!\n";
			return;
		}
		try {

			srv.srv_add(id_int, nrI, prod, model, tip);
			cout << "Adaugat cu succes!\n";
		}
		catch (const exception& ex) {
			cout << ex.what();
		}
		
	}
	cout << "\n\n\n";
}
void UI::delUI()
{
	string id;
	//cin.ignore();
	cout << "Introduceti ID:\n";
	getline(cin, id);
	if (id.length()>16)
		cout << "ID-ul este prea mare!\n";
	else {
		int id_int = 0;

		try {
			id_int = stoi(id);
		}
		catch (exception&) {

			cout << "ID-ul este invalid!\n";
			return;
		}
		try {
			srv.srv_del(id_int);
			cout << "Sters cu succes!\n";
		}
		catch (const exception& ex) {
			cout << ex.what();
		}
	}
	cout << "\n\n\n";
}
void UI::updateUI()
{
	string id;
	string nrI;
	string prod;
	string model;
	string tip;

	//cin.ignore();
	cout << "Introduceti ID:\n";
	getline(cin, id);
	cout << "Introduceti Nr. inmatriculare:\n";
	getline(cin, nrI);
	cout << "Introduceti producator:\n";
	getline(cin, prod);
	cout << "Introduceti model:\n";
	getline(cin, model);
	cout << "Introduceti tip:\n";
	getline(cin, tip);
	if (id.length() > 16)
		cout << "ID-ul este prea mare!\n";
	else {
		int id_int = 0;

		try {
			id_int = stoi(id);
		}
		catch (exception&) {

			cout << "ID-ul este invalid!\n";
			return;
		}
		try {
			srv.srv_update(id_int, nrI, prod, model, tip);
			cout << "Actualizat cu succes!\n";
		}
		catch (const exception& ex) {
			cout << ex.what();
		}

	}
	cout << "\n\n\n";
}
void UI::printUI()
{
	vector<Masina>v = srv.srv_getAll();
	for (const auto& el : v)

		cout <<"ID: "<< el.getID() << " Nr. Inm:" << el.getNrInmatriculare() << " Model:" << el.getModel() << " Producator:" << el.getProducator() << " Tip:" << el.getTip() << '\n';
	
	cout << "\n\n\n";
}
void UI::findCarUI()
{
	string id;
	cout << "Introduceti ID: ";
	cin >> id;
	if (id.length() > 16) {
		cout << "ID invalid!\n";
	}
	else {
		try {
			const int id_int = stoi(id);
			Masina el = srv.srv_findCar(id_int);
			cout <<"ID: "<< el.getID() << " Nr. Inm:" << el.getNrInmatriculare() << " Model:" << el.getModel() << " Producator:" << el.getProducator() << " Tip:" << el.getTip() << '\n';
			
			
		}
		catch (const exception& ex) {
			cout << ex.what();
		}
	}
	cout << "\n\n\n";
}
void UI::addUI_nrInm()
{
	string nrI;
	cout << "Introduceti nr. de inmatriculare:\n";
	getline(cin, nrI);

	srv.srv_add(nrI);

	

}
void UI::clearUI()
{
	srv.srv_clearRepo();
	cout << "Lista de masini s-a golit!\n";
}
void UI::addRandomUI()
{
	cout << "Cate masini doriti sa adaugati?\n>>>";
	string numar;
	int numar_int=0;
	getline(cin, numar);
	if (numar.length() > 6)
	{
		cout << "Ati introdus un numar prea mare!\n";
	}
	else {
		try {
			numar_int = stoi(numar);
			
		}
		catch(const exception&) {
			cout << "Id-ul este invalid!\n";
			return;
		}

		int nr = srv.addRandom(numar_int);
		cout << nr << " masini au fost invalide!\n\n";

	}

}
void UI::run() {
	string cmd;
	while (1) {

		cout << "In lista sunt " << srv.srv_getNumberOfCars() << " masini.\n\n";

		cout << "help - pentru a vedea lista de comenzi!\n";
		cout << "Introduceti comanda\n>>>";

		
		getline(cin, cmd);
		if (cmd == "add")
			addUI();
		else if (cmd == "del")
			delUI();
		else if (cmd == "print")
			printUI();
		else if (cmd == "update")
			updateUI();
		else if (cmd == "exit")
			return;
		else if (cmd == "find")
			findCarUI();
		else if (cmd == "filter")
			filterUI();
		else if (cmd == "sort")
			sortUI();
		else if (cmd == "help")
			showUI();
		else if (cmd == "add2")
			addUI_nrInm();
		else if (cmd == "clear")
			clearUI();
		else if (cmd == "random")
			addRandomUI();
	}
}