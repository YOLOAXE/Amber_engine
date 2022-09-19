#ifndef __BODYPART_LIA__
#define __BODYPART_LIA__

#include <iostream>
#include <vector>
#include "BodyPart.hpp"

using namespace std;

namespace lia
{
    class BodyPart
    {
        public:
            BodyPart(string n,float h,int q,float c,float hc,bool i,vector<string> g,vector<BodyPart *> sbp);
            void AddSubPart(BodyPart * b);
        private:            
            string name;
            float health;
            int quantity;
            float coverage;
            float hitChance;
            vector<BodyPart *> subBodyParts;
            bool internal;
            vector<string> groups;
    };
}

#endif //__BODYPART_LIA__