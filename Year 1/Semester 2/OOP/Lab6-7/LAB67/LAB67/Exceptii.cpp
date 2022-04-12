#include "Exceptii.h"

RepoException::RepoException(const string& _mesaj) : mesaj{_mesaj}
{
}

const string& RepoException::getMessage()
{
	return mesaj;
}
