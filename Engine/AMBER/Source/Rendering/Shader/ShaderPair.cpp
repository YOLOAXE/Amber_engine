#include "ShaderPair.hpp"

namespace Ge
{
	ShaderPair::ShaderPair(std::string f, std::string v)
	{
		this->Frag = f;
		this->Vert = v;
	}

	ShaderPair::ShaderPair(){}
}