#ifndef __STATISTIQUE_LIA__
#define __STATISTIQUE_LIA__

#include <iostream>
using namespace std;

namespace lia
{
    class Statistique
    {
        public:
            Statistique(string n);
            Statistique(string n,float v);
            string name;
            float value;
    };
}

#endif //__STATISTIQUE_LIA__