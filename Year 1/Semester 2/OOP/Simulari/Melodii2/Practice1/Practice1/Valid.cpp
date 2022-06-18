#include "Valid.h"

int Valid::validate(const Melodie& m)
{
    string exceptii="";
    if (m.getID() < 1)
        exceptii = exceptii + "ID invalid!\n";
    if (m.getGen() != "pop" && m.getGen() != "rock" && m.getGen() != "folk" && m.getGen() != "disco")
        exceptii = exceptii + "Gen invalid!\n";
    if (exceptii.length() > 0)
        throw ValidException{ exceptii };

    return 0;
}
