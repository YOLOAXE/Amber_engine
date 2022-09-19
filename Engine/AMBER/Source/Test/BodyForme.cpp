#include "BodyForme.hpp"

namespace lia
{
    BodyForme::BodyForme(string n)
    {
        name = n;
    }

    vector<BodyPart *> BodyForme::GetBodyParts()
    {
        return bodyParts;
    }
}