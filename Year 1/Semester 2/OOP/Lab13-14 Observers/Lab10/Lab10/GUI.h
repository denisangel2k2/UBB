#pragma once

#include <qwidget.h>
#include <qlistwidget.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qgridlayout.h>
#include <qlineedit.h>
#include "Service.h"
#include "Domain.h"
#include "Valid.h"
#include <qformlayout.h>
#include "AdminService.h"
#include <qmessagebox.h>
#include <qobject.h>
#include <qlabel.h>
#include <qtablewidget.h>
#include <qpainter.h>
#include "observer.h"
#include <random>


class GUI;
class Desenator : public QWidget, public Observer
{
private:
	AdminService& srv2;
	void connectSignals() {
		srv2.addObserver(this);
	}
public:
	Desenator(AdminService& srv2) : srv2{ srv2 } { connectSignals(); }
	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, 100);
		for (const auto& el : srv2.srv_getall()) {
			int rndNr = dist(mt);
			p.drawEllipse(rndNr, rndNr, 70, 70);
		}
		
	}
	void update() override {
		repaint();
		//QMessageBox::warning(this, "titlu", "ive been notified!");
	}
	
	~Desenator() {
		srv2.removeObserver(this);
	}
};
class Advanced : public QWidget
{
	
private:
	
	
	AdminService& srv2;
	Service& srv;
	//QListWidget* lista2;
	QTableWidget* lista2;
	QPushButton* randomBtn2;
	QPushButton* addBtn2;
	QPushButton* exportBtn;
	QPushButton* clearBtn2;
	QLineEdit* numberOfCarsTxt2;
	QLineEdit* nrInmTxt2;
	QVBoxLayout* mainLayout2;
	QLabel* numberOfCarsPresentTxt2;
	QLabel* idBox2;
	QLabel* nrInmBox2;
	QLabel* prodBox2;
	QLabel* tipBox2;
	QLabel* modelBox2;


	void init();
	void connectSignalsAndSlots();
	//void reloadList(vector<Masina>v);
	void reloadList(vector<Masina>masini);
	void addGUI2();
	void addRnd2(); 

public:
	Advanced(AdminService& srv, Service& srv_s) :srv2{ srv }, srv{ srv_s } {
		this->init();
		this->reloadList(srv2.srv_getall());
		this->connectSignalsAndSlots();
	};

};
class GUI : public QWidget
{
	
private:
	friend class Advanced;
	bool conditional_var = true;
	bool prod_var = false;
	Service& srv;
	AdminService& srv2;
	//QListWidget* lista;
	QHBoxLayout* mainLayout = new QHBoxLayout();
	
	QVBoxLayout* butoaneProducatoriLay=new QVBoxLayout;
	QWidget* butoaneProducatori=new QWidget;
	QTableWidget* lista;
	QPushButton* producatoriBtn;
	QPushButton* addBtn;
	QPushButton* delBtn;
	QPushButton* updateBtn;
	QPushButton* sort1Btn;
	QPushButton* sort2Btn;
	QPushButton* sort3Btn;
	QPushButton* showListBtn;
	QPushButton* undoBtn;
	QPushButton* showCarWashBtn;
	QPushButton* randBtn;
	

	QLineEdit* idBox;
	QLineEdit* nrInmBox;
	QLineEdit* prodBox;
	QLineEdit* tipBox;
	QLineEdit* modelBox;
	QLineEdit* filter1Box;
	QLineEdit* filter2Box;
	QLineEdit* filter3Box;
	Advanced* advancedWnd;

	void init();
	void reloadList(const std::vector<Masina>& masini);
	void connectSignalsAndSlots();
	void addGUI();
	void delGUI();
	void updateGUI();
	void undoGUI();
	void producatoriGUI();
	int randGUI();
	void refreshProdGui();
	void clearLayout(QLayout* Layout);
public:
	GUI(Service& serv, AdminService& serv2) : srv{ serv }, srv2{ serv2 } {
		init();
		connectSignalsAndSlots();
		reloadList(srv.srv_getAll());
		refreshProdGui();

	}
	

};