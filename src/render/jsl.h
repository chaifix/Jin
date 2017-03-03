#ifndef __JIN_JSL_H
#define __JIN_JSL_H
#include <string>
#include "libs/GLee/GLee.h"
namespace jin
{
namespace render
{
    /**
    * A JSL program for shadering textures which is 
    * actually a glsl program.
    */
    class JSLProgram
    {
    public:

        // psuedo constructor 
         void init(); 

        void use();
        
        static void unuse();

        void sendFloat(const char* name, int size, const GLfloat* vec, int count);
        void sendMatrix(const char*  name, int size, const GLfloat* m, int count);
        //void sendImage(const char*  name, const Image& image);
        //void sendCanvas(const char* name, const Canvas& canvas);

        static void hasuse(GLint id); 

    private:
        
        // only id for identify glsl program
        GLuint pid; 

        // currently used jsl program
        static GLint cur;
    };
}
}
#endif