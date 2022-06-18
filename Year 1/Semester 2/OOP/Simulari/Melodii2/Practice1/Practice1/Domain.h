#pragma once
#include <string>
using std::string;
class Melodie
{
private:
	int id;
	string titlu;
	string artist;
	string gen;
public:
	Melodie(int id, string titlu, string artist, string gen) : id{id},titlu{titlu},artist{artist},gen{gen}{}
	int getID() const;
	const string& getTitlu() const;
	const string& getArtist() const;
	const string& getGen() const;
};

class ValidException {
private:
	string msg;
public:
	ValidException(string& msg) : msg{msg}{}
	string what() { return msg; }
};

class RepoException {
private:
	string msg;
public:
	RepoException(string& msg) : msg{ msg } {}
	string what() { return msg; }
};

