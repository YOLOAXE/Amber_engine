#include "Statistique.hpp"

namespace lia
{    
    Statistique::Statistique(string n)
    {
        name = n;
        value = 0;
    }

    Statistique::Statistique(string n,float v)
    {
        name = n;
        value = v;
    }
}