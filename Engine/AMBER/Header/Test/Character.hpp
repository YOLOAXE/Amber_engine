#ifndef __CHARACTER_LIA__
#define __CHARACTER_LIA__

#include <iostream>
#include <vector>
#include "Debug.hpp"
#include "Race.hpp"
#include "Statistique.hpp"
#include "BodyForme.hpp"
#include "Genre.hpp"
#include "Age.hpp"
#include "CharacterState.hpp"
#include "CharacterNeed.hpp"
#include "Behaviour.hpp"
#include <map>

using namespace std;

namespace lia
{
    class Character : Behaviour
    {
        public:
            Character(vector<string> names,vector<RACE> r,BodyForme * b,GENRE g,Age * a);            
        protected:            
            vector<string> names;
            map<string,Statistique *> stats;   
            BodyForme * bodyForme;
            vector<RACE> races;
            map<string,CharacterState *> characterStates;
            map<string,CharacterNeed *> characterNeeds;
            GENRE genre = GENRE::Male;
            Age * age;
    };
}
#endif //__CHARACTER_LIA__