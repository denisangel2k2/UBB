#include "GUI.h"
#include "Service.h"
#include <iostream>
#include <string>
#include "Exceptii.h"
using std::string;
void GUI::init()
{
	
	conditional_var = false;
	setLayout(mainLayout);
	setWindowTitle("Inchirieri masini");
	lista = new QListWidget;
		addBtn=new QPushButton("Adauga");
		delBtn = new QPushButton("Sterge");
		updateBtn = new QPushButton("Modifica");
		sort1Btn = new QPushButton("Sortare Nr. inmatriculare");
		sort2Btn = new QPushButton("Sortare tip");
		sort3Btn = new QPushButton("Sortare producator+model");
		showListBtn = new QPushButton("Afisare lista");
		undoBtn = new QPushButton("Undo");
		showCarWashBtn = new QPushButton("Avansat");
		randBtn = new QPushButton("Random");

		idBox = new QLineEdit();
		nrInmBox = new QLineEdit();
		prodBox = new QLineEdit();
		tipBox = new QLineEdit();
		modelBox = new QLineEdit();
		filter1Box = new QLineEdit();
		filter2Box = new QLineEdit();
		filter3Box = new QLineEdit();

	QWidget* leftSide = new QWidget;
	QVBoxLayout* leftSideLay = new QVBoxLayout;
	leftSide->setLayout(leftSideLay);

	leftSideLay->addWidget(new QLabel{ "Lista" });
	leftSideLay->addWidget(lista);
	leftSideLay->addWidget(new QLabel{ "Soratari & Filtrari" });

		QWidget* leftButtons=new QWidget;
		QGridLayout* leftButtonsLay = new QGridLayout;
	
		leftButtonsLay->addWidget(sort1Btn,0,0);
		leftButtonsLay->addWidget(sort2Btn,1,0);
		leftButtonsLay->addWidget(sort3Btn,2,0);
		leftButtonsLay->addWidget(showListBtn,3,0);

		leftButtons->setLayout(leftButtonsLay);

		QWidget* filterDetails = new QWidget;
		QFormLayout* filterDetailsLay = new QFormLayout;

		filterDetailsLay->addRow(new QLabel{ "Filtru producator" }, filter1Box);
		filterDetailsLay->addRow(new QLabel{ "Filtru tip" }, filter2Box);
		//filterDetailsLay->addRow(new QLabel{ "Filter3" }, filter3Box);
		filterDetails->setLayout(filterDetailsLay);

		QWidget* leftButtonsAndFilters = new QWidget;
		QHBoxLayout* leftButtonsAndFilterslay = new QHBoxLayout;
		leftButtonsAndFilters->setLayout(leftButtonsAndFilterslay);

		leftButtonsAndFilterslay->addWidget(leftButtons);
		leftButtonsAndFilterslay->addWidget(filterDetails);
	
	leftSideLay->addWidget(leftButtonsAndFilters);
	
	

	QWidget* rightSide = new QWidget;
	QVBoxLayout* rightSideLay = new QVBoxLayout;
	rightSide->setLayout(rightSideLay);

		QWidget* textBoxes = new QWidget;
		QFormLayout* textBoxesLay = new QFormLayout;

		textBoxesLay->addRow(new QLabel("ID:"), idBox);
		textBoxesLay->addRow(new QLabel("Nr. inmatriculare:"), nrInmBox);
		textBoxesLay->addRow(new QLabel("Producator:"), prodBox);
		textBoxesLay->addRow(new QLabel("Model:"), modelBox);
		textBoxesLay->addRow(new QLabel("Tip:"), tipBox);
		
		textBoxes->setLayout(textBoxesLay);

		QWidget* rightButtons = new QWidget;
		QGridLayout* rightButtonsLay = new QGridLayout;

		rightButtonsLay->addWidget(addBtn);
		rightButtonsLay->addWidget(delBtn);
		rightButtonsLay->addWidget(updateBtn);
		rightButtonsLay->addWidget(undoBtn);
		rightButtonsLay->addWidget(showCarWashBtn);
		rightButtonsLay->addWidget(randBtn);

		rightButtons->setLayout(rightButtonsLay);

	//rightSideLay->addWidget(new QLabel("Panou"));
	rightSideLay->addWidget(textBoxes);
	rightSideLay->addWidget(rightButtons);

	advancedWnd = new Advanced(srv2);
	advancedWnd->setVisible(conditional_var);

	mainLayout->addWidget(leftSide);
	mainLayout->addWidget(rightSide);
	mainLayout->addWidget(advancedWnd);
	
}

void GUI::reloadList(const std::vector<Masina>& masini)
{
	lista->clear();
	for (const auto& el : masini) {
		//QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(el.getNrInmatriculare()));
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(el.getNrInmatriculare()));
		string id = to_string(el.getID());

		item->setData(Qt::UserRole,  QString::fromStdString(id));
		
		if (el.getTip() == "SUV") {
			item->setData(Qt::BackgroundRole, QBrush{ Qt::yellow, Qt::SolidPattern });
		}
		lista->addItem(item); 
	}
}

void GUI::connectSignalsAndSlots()
{
	QObject::connect(sort1Btn, &QPushButton::clicked, [&]() {
		qDebug() << "buton apasat!";
		reloadList(srv.sort([](const Masina& m1, const Masina& m2) {if (m1.getNrInmatriculare() < m2.getNrInmatriculare()) return true; else return false; }));
		});
	QObject::connect(sort2Btn, &QPushButton::clicked, [&]() {
		reloadList(srv.sort([](const Masina& m1, const Masina& m2) {if (m1.getTip() < m2.getTip()) return true; else return false; }));
		});
	QObject::connect(sort3Btn, &QPushButton::clicked, [&]() {
		reloadList(srv.sort([](const Masina& m1, const Masina& m2) {
			if (m1.getProducator() < m2.getProducator())
				return true;
			else if (m1.getProducator() == m2.getProducator())
				if (m1.getModel() < m2.getModel())
					return true;
				else return false;
			else return false;
			}));
		});
	QObject::connect(addBtn, &QPushButton::clicked,this, &GUI::addGUI);
	QObject::connect(lista, &QListWidget::itemSelectionChanged, [&]() {
		auto selected = lista->selectedItems();
		if (selected.isEmpty()) {
			idBox->setText("");
			prodBox->setText("");
			modelBox->setText("");
			tipBox->setText("");
			nrInmBox->setText("");
		}
		else {
			auto item = selected.at(0);
			QString id_qstring = item->data(Qt::UserRole).toString();
			string id_string = id_qstring.toStdString();
			int id = stoi(id_string);
			auto m = srv.srv_findCar(id);
			idBox->setText(id_qstring);
			prodBox->setText(QString::fromStdString(m.getProducator() ));
			modelBox->setText(QString::fromStdString(m.getModel()));
			tipBox->setText(QString::fromStdString(m.getTip()));
			nrInmBox->setText(QString::fromStdString(m.getNrInmatriculare()));
		}
		});
	QObject::connect(delBtn, &QPushButton::clicked, this, &GUI::delGUI);
	QObject::connect(updateBtn, &QPushButton::clicked, this, &GUI::updateGUI);
	QObject::connect(filter1Box, &QLineEdit::textChanged, [&](QString filtru) {
		string filtr = filtru.toStdString();
		reloadList(srv.filter(filtr, 1));
		});
	QObject::connect(filter2Box, &QLineEdit::textChanged, [&](QString filtru) {
		string filtr = filtru.toStdString();
		reloadList(srv.filter(filtr, 2));
		});
	QObject::connect(showListBtn, &QPushButton::clicked, [&]() {
		reloadList(srv.srv_getAll());
		});
	QObject::connect(undoBtn, &QPushButton::clicked, this, &GUI::undoGUI);
	QObject::connect(showCarWashBtn, &QPushButton::clicked, [&]() {
		
		if (conditional_var == true) {
			conditional_var = !conditional_var;
			advancedWnd->setVisible(conditional_var);
			showCarWashBtn->setText("Avansat");
		}
		else {
			conditional_var = !conditional_var;
			advancedWnd->setVisible(conditional_var);
			showCarWashBtn->setText("Close");
		}
		});
}

void GUI::addGUI()
{
	try {
		srv.srv_add(idBox->text().toInt(), nrInmBox->text().toStdString(), prodBox->text().toStdString(), modelBox->text().toStdString(), tipBox->text().toStdString());
		reloadList(srv.srv_getAll());
	}
	catch(const std::exception& ex) {
		std::string s = ex.what();
		QMessageBox::warning(this, "Warning", QString::fromStdString(s));
	}
}

void GUI::delGUI()
{
	try {
		auto idQ = idBox->text();
		if (idQ != "") {
			string idS = idQ.toStdString();
			if (idS.length() <= 16)
			{
				try {
					int id = stoi(idS);
					srv.srv_del(id);
					reloadList(srv.srv_getAll());
				}
				catch (const exception&) {
					throw std::runtime_error("Invalid argument!\n");
				}
			}	
		}
	}
	catch (const exception& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.what()));
	}
}

void GUI::updateGUI()
{
	try {
		auto idQ = idBox->text();
		if (idQ != "") {
			string prodN = prodBox->text().toStdString();
			string tipN = tipBox->text().toStdString();
			string nrInmN = nrInmBox->text().toStdString();
			string modelN = modelBox->text().toStdString();
			int id;
			try {
				if (idQ.length() <= 16)
					id = stoi(idQ.toStdString());
				else throw exception();
			}
			catch (const exception&) {
				throw std::runtime_error("Invalid argument!\n");
			}
			
			srv.srv_update(id, nrInmN, prodN, modelN, tipN);
			reloadList(srv.srv_getAll());
		}
	}
	catch (const exception& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.what()));
	}
}

void GUI::undoGUI()
{
	try {
		srv.undo();
		reloadList(srv.srv_getAll());
	}
	catch (const Exceptie& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
}

void Advanced::init()
{
	mainLayout2 = new QVBoxLayout;
	this->setLayout(mainLayout2);
	addBtn2 = new QPushButton("Adauga");
	nrInmTxt2 = new QLineEdit;
	lista2 = new QListWidget;
	randomBtn2 = new QPushButton("Adauga aleator");
	numberOfCarsTxt2 = new QLineEdit;
	numberOfCarsPresentTxt2 = new QLabel("Show no. cars");

	mainLayout2->addWidget(numberOfCarsPresentTxt2);

	mainLayout2->addWidget(lista2);
	QWidget* butoane=new QWidget;
	QGridLayout* butoaneLay = new QGridLayout;
	butoane->setLayout(butoaneLay);

	butoaneLay->addWidget(new QLabel("Adauga dupa nr. inmatriculare: "), 0, 0);
	butoaneLay->addWidget(addBtn2, 0, 1);
	butoaneLay->addWidget(nrInmTxt2, 0, 2);
	butoaneLay->addWidget(new QLabel("Adauga un numar de masini: "), 1, 0);
	butoaneLay->addWidget(randomBtn2, 1, 1);
	butoaneLay->addWidget(numberOfCarsTxt2, 1, 2);

	mainLayout2->addWidget(butoane);

}

void Advanced::connectSignalsAndSlots()
{
	QObject::connect(addBtn2, &QPushButton::clicked, this, &Advanced::addGUI2);
	QObject::connect(randomBtn2, &QPushButton::clicked, this, &Advanced::addRnd2);
	QObject::connect(numberOfCarsPresentTxt2, &QLabel::linkActivated, [&]() {

		int cate = (int)srv2.srv_getNumberOfCars();
		string cateS = to_string(cate);
		numberOfCarsPresentTxt2->setText(QString::fromStdString(cateS));
		});
}

void Advanced::reloadList(vector<Masina> v)
{
	lista2->clear();
	for (const auto& el : v) {
		string s = el.getNrInmatriculare();
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(s));
		string id = to_string(el.getID());
		item->setData(256, QString::fromStdString(id));

		lista2->addItem(item);
	}
}

void Advanced::addGUI2()
{
	QString qNrinm = nrInmTxt2->text();
	string nrInm = qNrinm.toStdString();
	

	try {
		srv2.srv_add(nrInm);
		reloadList(srv2.srv_getall());
	}
	catch (const exception& ex) {
		string s = ex.what();
		QMessageBox::warning(this, "Warning", QString::fromStdString(s));
	}
	
}

void Advanced::addRnd2()
{
	QString qcate = numberOfCarsTxt2->text();
	int cate = qcate.toInt();
	try {
		srv2.addRandom(cate);
		reloadList(srv2.srv_getall());
	}
	catch (const exception& ex) {
		string s = ex.what();
		QMessageBox::warning(this, "Warning", QString::fromStdString(s));
	}
}
