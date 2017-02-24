#ifndef __JIN_JSL_H
#define __JIN_JSL_H
#include <string>
namespace jin
{
	class JSLProgram
	{
		/**
		* translate JSL to GLSL
		*/
		std::string toGLSL();
		void use(); 
		void unuse(); 
	};
}
#endif