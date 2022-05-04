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
class GUI;
class Advanced : public QWidget
{
	
private:
	AdminService& srv2;
	QListWidget* lista2;
	QPushButton* randomBtn2;
	QPushButton* addBtn2;
	QPushButton* clearBtn2;
	QLineEdit* numberOfCarsTxt2;
	QLineEdit* nrInmTxt2;
	QVBoxLayout* mainLayout2;
	QLabel* numberOfCarsPresentTxt2;
	void init();
	void connectSignalsAndSlots();
	void reloadList(vector<Masina>v);
	void addGUI2();
	void addRnd2(); 

public:
	Advanced(AdminService& srv) :srv2{ srv } {
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
	Service& srv;
	AdminService& srv2;
	QListWidget* lista;
	QHBoxLayout* mainLayout = new QHBoxLayout;
	
	
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
	int randGUI();
public:
	GUI(Service& serv, AdminService& serv2) : srv{ serv }, srv2{ serv2 } {
		init();
		connectSignalsAndSlots();
		reloadList(srv.srv_getAll());

	}
	

};