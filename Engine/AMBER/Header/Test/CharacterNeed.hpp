#ifndef __CHARACTERNEED_LIA__
#define __CHARACTERNEED_LIA__

#include <iostream>

using namespace std;

namespace lia
{
    class CharacterNeed
    {
        public:
            CharacterNeed(string n);
        private:
            string name;
            float value;            
    };
}

#endif //__CHARACTERNEED_LIA__