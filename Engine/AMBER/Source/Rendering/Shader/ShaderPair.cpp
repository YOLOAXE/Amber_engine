#include "ShaderPair.hpp"

namespace Ge
{
	ShaderPair::ShaderPair(std::string f, std::string v, bool b)
	{
		this->Frag = f;
		this->Vert = v;
		this->back = b;
	}

	ShaderPair::ShaderPair(){}
}