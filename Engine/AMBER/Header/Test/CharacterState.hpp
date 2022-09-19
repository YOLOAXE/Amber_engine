#ifndef __CHARACTERSTATE_LIA__
#define __CHARACTERSTATE_LIA__

#include <iostream>
using namespace std;

namespace lia
{
    class CharacterState
    {
        public:
            CharacterState(string n);
            string toString();
        private:
            string name;
            float value;
    };
}

#endif //__CHARACTERSTATE_LIA__