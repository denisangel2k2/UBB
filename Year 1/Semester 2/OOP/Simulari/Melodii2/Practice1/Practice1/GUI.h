#pragma once
#include <qwidget.h>
#include <qpushbutton.h>
#include <qtableview.h>
#include <qlineedit.h>
#include <qformlayout.h>
#include <qgridlayout.h>
#include <qboxlayout.h>
#include "Service.h"
#include "MyTableModel.h"
#include "qpainter.h"
class GUI : public QWidget, public Observer
{
private:
	Service& srv;
	QLineEdit* idBox;
	QLineEdit* titluBox;
	QLineEdit* genBox;
	QLineEdit* artistBox;
	QPushButton* addBtn;
	QPushButton* delBtn;
	QTableView* lista;
	MyTableModel* model=new MyTableModel(srv.getAll());
	QHBoxLayout* mainLay = new QHBoxLayout;
	void paintEvent(QPaintEvent* ev) override;
	void connectSignals();
	void init();
	void reloadList();
	void update() override;
public:
	GUI(Service& sr) : srv{ sr } { init(); connectSignals(); srv.addObserver(this); }
	~GUI() { srv.removeObserver(this); }
};

