#include "GUI.h"
#include <qlabel.h>
#include <qmessagebox.h>

void GUI::connectSignals()
{

	QObject::connect(addBtn, &QPushButton::clicked,[&]() {
		string titlu = titluBox->text().toStdString();
		string gen = genBox->text().toStdString();
		string artist = artistBox->text().toStdString();
		try {
			srv.srv_add(titlu, artist, gen);
			//reloadList();
		}
		catch (RepoException& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.what()));
		}
		catch (ValidException& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.what()));
		}
		});
	QObject::connect(delBtn, &QPushButton::clicked, [&]() {
		string id = idBox->text().toStdString();
		int idint = stoi(id);
		try {
			srv.srv_del(idint);

		}
		catch (RepoException& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.what()));
		}
		catch (ValidException& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.what()));
		}
		});
	QObject::connect(lista->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (lista->selectionModel()->selectedIndexes().isEmpty()) {
			return;
			}
		int selRow = lista->selectionModel()->selectedIndexes().at(0).row();
		auto cel0 = lista->model()->index(selRow, 0);
		auto id = stoi(lista->model()->data(cel0,Qt::UserRole).toString().toStdString());
		Melodie m = srv.find(id);
		artistBox->setText(QString::fromStdString(m.getArtist()));
		idBox->setText(QString::fromStdString(std::to_string(m.getID())));
		titluBox->setText(QString::fromStdString(m.getTitlu()));
		genBox->setText(QString::fromStdString(m.getGen()));
		});
}
void GUI::init()
{
	setLayout(mainLay);
	titluBox = new QLineEdit();
	genBox = new QLineEdit();
	artistBox = new QLineEdit();
	idBox = new QLineEdit();

	addBtn = new QPushButton("Add");
	delBtn = new QPushButton("Delete");

	lista = new QTableView;
	lista->setModel(model);
	mainLay->addWidget(lista);
	
	QVBoxLayout* rightSideLay = new QVBoxLayout;
	QWidget* rightSide = new QWidget;
	rightSide->setLayout(rightSideLay);

	QFormLayout* boxeslay = new QFormLayout;
	boxeslay->addRow(new QLabel("Artist"), artistBox);
	boxeslay->addRow(new QLabel("Titlu"), titluBox);
	boxeslay->addRow(new QLabel("Gen"), genBox);
	
	QWidget* boxes = new QWidget;
	boxes->setLayout(boxeslay);
	

	rightSideLay->addWidget(boxes);
	rightSideLay->addWidget(addBtn);
	rightSideLay->addWidget(delBtn);
	
	mainLay->addWidget(rightSide);
	mainLay->addWidget(idBox);
	idBox->setVisible(false);


}

void GUI::reloadList()
{
	model->setTable(srv.getAll());
}

void GUI::paintEvent(QPaintEvent* ev) 
{
	QPainter p{ this };
	int radiusPop = 100;
	int radiusRock = 10;
	int radiusFolk = 10;
	int radiusDisco = 10;
	//p.setBrush(50, 50, 50);
	
	for (const auto& el : srv.getAll()) {
		if (el.getGen() == "pop") {
			p.drawEllipse(0+10, 0+10, radiusPop, radiusPop);
			radiusPop += 5;
		}
		if (el.getGen() == "rock") {
			p.drawEllipse(0+10, height()-10, radiusRock, radiusRock);
			radiusRock += 5;
		}
		if (el.getGen() == "folk") {
			p.drawEllipse(width()-10, height()-radiusFolk, radiusFolk, radiusFolk);
			radiusFolk += 5;
		}
		if (el.getGen() == "disco") {
			p.drawEllipse(width()-10, 0+10, radiusDisco, radiusDisco);
			radiusDisco += 5;
		}
	}
}
void GUI::update()
{
	reloadList();
	repaint();
}
