#pragma once
#include <qwidget.h>
#include <qtableview.h>
#include "Domain.h"
using std::vector;
class MyTableModel : public QAbstractTableModel 
{
	vector<Melodie>melodii;
public:
	MyTableModel(vector<Melodie>m) : melodii{m}{}
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return melodii.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 3;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayPropertyRole) const override {
		if (role == Qt::DisplayRole) {
			if (index.column() == 0)
				return QString::fromStdString(melodii[index.row()].getArtist());
			if (index.column() == 1)
				return QString::fromStdString(melodii[index.row()].getTitlu());
			if (index.column() == 2)
				return QString::fromStdString(melodii[index.row()].getGen());
		}
		if (role == Qt::UserRole)
			return QString::fromStdString(std::to_string(melodii[index.row()].getID()));
		return QVariant{};
	}
	void clear() {
		melodii.clear();
	}
	void setTable(const vector<Melodie>& m) {
		this->melodii = m;
		QModelIndex topLeft = createIndex(0, 0);
		QModelIndex botRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, botRight);
		emit layoutChanged();
	}
};