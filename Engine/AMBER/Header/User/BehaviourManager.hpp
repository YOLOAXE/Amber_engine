#ifndef __ENGINE_BEHAVIOUR_MANAGER__
#define __ENGINE_BEHAVIOUR_MANAGER__

#include "Behaviour.hpp"
#include <vector>
#include <algorithm>

namespace Ge
{
	class BehaviourManager
	{
	public:
		void addBehaviour(Behaviour * b);
		void removeBehaviour(Behaviour * b);	
		void update();
		void fixedUpdate();		
	private:
		std::vector<Behaviour *>  m_behaviours;
	};
}

#endif//__ENGINE_BEHAVIOUR_MANAGER__