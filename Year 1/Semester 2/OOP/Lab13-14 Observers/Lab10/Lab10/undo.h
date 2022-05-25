#pragma once
#include "Domain.h"
#include "Repository.h"
class UndoAction
{
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction() = default;
};

class UndoAdd : public UndoAction
{
private:
	Masina masinaAdaugata;
	Repository& repo;
public:
	UndoAdd(const Masina& m, Repository& rep) : masinaAdaugata{ m }, repo{ rep }{}
	void doUndo() override;

};

class UndoUpdate : public UndoAction
{
private:
	Masina masinaActualizata;
	Repository& repo;
public:
	UndoUpdate(const Masina& m, Repository& rep) : repo{ rep }, masinaActualizata{ m }{}
	void doUndo() override;

};

class UndoDelete : public UndoAction
{

private:
	Masina masinaStearsa;
	Repository& repo;
public:
	UndoDelete(const Masina& m, Repository& rep) : repo{ rep }, masinaStearsa{ m }{}
	void doUndo() override;


};
