#include "BodyPart.hpp"

namespace lia
{
    BodyPart::BodyPart(string n,float h,int q,float c,float hc,bool i,vector<string> g,vector<BodyPart *> sbp)
    {
        name = n;
        health = h;
        quantity = q;
        coverage = c;
        hitChance = hc;
        internal = i;
        groups = g;
        subBodyParts = sbp;
    }

    void BodyPart::AddSubPart(BodyPart * b)
    {
        subBodyParts.push_back(b);
    }
}