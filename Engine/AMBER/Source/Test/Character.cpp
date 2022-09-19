#include "Character.hpp"
#include "HumanoidForme.hpp"

namespace lia
{
    Character::Character(vector<string> names,vector<RACE> r,BodyForme * b,GENRE g,Age * a)
    {
        stats["Magie soin"] = new Statistique("Magie soin");
        stats["Magie Destruction"] = new Statistique("Magie Destruction");
        stats["Magie Alteration"] = new Statistique("Magie Alteration");//interagie avec le monde
        stats["Magie Conjuration"] = new Statistique("Magie Conjuration");//interagie avec les mort
        stats["Enchantement"] = new Statistique("Enchantement");
        stats["Anti Magie"] = new Statistique("Anti Magie");
        stats["Tir leger"] = new Statistique("Tir leger");
        stats["Tir lourd"] = new Statistique("Tir lourd");
        stats["Arme leger"] = new Statistique("Arme leger");
        stats["Arme lourd"] = new Statistique("Arme lourd");
        stats["Defence"] = new Statistique("Defence");   
        stats["Vitesse"] = new Statistique("Vitesse");
        stats["Construction"] = new Statistique("Construction");
        stats["Minage"] = new Statistique("Minage");
        stats["Cuisine"] = new Statistique("Cuisine");
        stats["Vegetation"] = new Statistique("Vegetation");
        stats["Animeaux"] = new Statistique("Animeaux");
        stats["Artisanat"] = new Statistique("Artisanat");
        stats["Social"] = new Statistique("Social");
        stats["Inteligence"] = new Statistique("Inteligence");

        if(b)
        {
            bodyForme = b;
        }
        else
        {
            bodyForme = new HumanoidForme();
        }
        genre = g;
        age = a;

        characterStates["Soufrance"] = new CharacterState("Soufrance");
        characterStates["Conscience"] = new CharacterState("Conscience");
        characterStates["Mouvement"] = new CharacterState("Mouvement");
        characterStates["Manipulation"] = new CharacterState("Manipulation");
        characterStates["Talking"] = new CharacterState("Talking");
        characterStates["Eating"] = new CharacterState("Eating");
        characterStates["Vue"] = new CharacterState("Vue");
        characterStates["Hearing"] = new CharacterState("Hearing");
        characterStates["Breathing"] = new CharacterState("Breathing");
        characterStates["Blood filtration"] = new CharacterState("Blood filtration");
        characterStates["Blood pumping"] = new CharacterState("Blood pumping");
        characterStates["Metabolism"] = new CharacterState("Metabolism");
        characterStates["Fertility"] = new CharacterState("Fertility");

        characterNeeds["Repos"] = new CharacterNeed("Repos");
        characterNeeds["Nouriture"] = new CharacterNeed("Nouriture");
        characterNeeds["Hygiene"] = new CharacterNeed("Hygiene");
    }
}