#include "ShaderPair.hpp"

namespace Ge
{
	void ShaderPair::ShaderPair(std::string f, std::string v)
	{
		this.Frag = f;
		this.Vert = v;
	}

	void ShaderPair::ShaderPair(){}
}