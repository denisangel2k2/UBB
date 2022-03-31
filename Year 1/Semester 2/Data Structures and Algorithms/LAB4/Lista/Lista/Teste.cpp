#include "Teste.h"
#include "DynamicVector.h"
#include <cassert>
#include <iostream>

void Teste::runTeste()
{
    DynamicVector v{ 1 };
    assert(v.len() == 0);
    v.append(2);
    assert(v.len() == 1);
    assert(v[0] == 2);
    assert(v.elem(0) == 2);
    v.del(0);
    assert(v.len() == 0);
    v.append(2);
    v[0] = 3;
    assert(v[0] == 3);

    
}
