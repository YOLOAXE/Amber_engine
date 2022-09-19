#ifndef __WORLDGENERATION_LIA__
#define __WORLDGENERATION_LIA__

#include "Scene.hpp"
#include "Debug.hpp"
#include "GameEngine.hpp"
#include "PointeurClass.hpp"

using namespace Ge;

namespace lia
{
    class WorldGeneration : public Scene
    {
        public:            
            void load();
	        void unload();
    };
}

#endif //__WORLDGENERATION_LIA__