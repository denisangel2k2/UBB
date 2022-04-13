#pragma once
#include <exception>
#include <string>

using std::exception;
using std::string;

class RepoException : public exception
{
private:
	string mesaj;

public:
	RepoException(const string&);
	const string& getMessage();

};

