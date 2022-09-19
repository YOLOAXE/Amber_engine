#ifndef __BODYFORME_LIA__
#define __BODYFORME_LIA__

#include <iostream>
#include <vector>
#include "BodyPart.hpp"

using namespace std;

namespace lia
{
    class BodyForme
    {
        public:
            BodyForme(string n);
            vector<BodyPart *> GetBodyParts();
        protected:
            string name;
            vector<BodyPart *> bodyParts;
    };
}

#endif //__BODYFORME_LIA__