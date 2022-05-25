#include "undo.h"

void UndoAdd::doUndo()
{
	repo.del(masinaAdaugata.getID());
}

void UndoUpdate::doUndo()
{
	repo.del(masinaActualizata.getID());
	repo.add(Masina{ masinaActualizata.getID(),masinaActualizata.getNrInmatriculare(),masinaActualizata.getProducator(),masinaActualizata.getModel(),masinaActualizata.getTip() });
}

void UndoDelete::doUndo()
{
	repo.add(masinaStearsa);
}
