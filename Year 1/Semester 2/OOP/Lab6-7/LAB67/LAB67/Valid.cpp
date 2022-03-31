#include "Valid.h"
#include <iostream>
using namespace std;
bool Valid::validateID(int id) noexcept
{

    if (id <= 0)
        return false;

    return true;
}

bool Valid::validate(const Masina& masina)
{
    vector<string>ex;
    Exceptions exceptie;

    if (!validateID(masina.getID()))
        ex.push_back("ID invalid!\n");

    if (masina.getModel().length() < 2)
        ex.push_back("Model invalid!\n");

    if (masina.getNrInmatriculare().length() < 2)
        ex.push_back("Nr. inmatriculare invalid!\n");

    if (masina.getProducator().length() < 2)
        ex.push_back("Producator invalid!\n");
    if (masina.getTip().length() < 2)
        ex.push_back("Tip invalid!\n");

    if (ex.size() > 0)
        throw runtime_error(exceptie.getEx(ex));

    return true;

}

string Exceptions::getEx(const vector<string>& ex)
{
    string s;

    for (const auto& el : ex) {
        s = s + el;
    }
    return s;
}
