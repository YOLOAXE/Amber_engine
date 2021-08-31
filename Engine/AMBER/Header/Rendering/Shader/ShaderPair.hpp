#ifndef __ENGINE_SHADER_PAIR__
#define __ENGINE_SHADER_PAIR__

#include <iostream>
namespace Ge
{
	class ShaderPair
	{
	public:
		ShaderPair(std::string f, std::string v);
		ShaderPair();
		std::string Frag;
		std::string Vert;
	};
}

#endif //__ENGINE_SHADER_PAIR__