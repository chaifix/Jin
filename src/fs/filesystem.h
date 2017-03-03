#include "buffer.h"
#include "libs/smount/smount.h"

namespace jin
{
namespace fs
{
    
    class Filesystem
    {
    public:
        
        Filesystem();

        static Filesystem* get();

        /**
        * is a path a directroy or a single file
        */
        bool isDir(const char* path);

        /**
        * is a path a directroy or a single file
        */
        bool isFile(const char* path);

        /**
        * is path a valid path
        */
        bool exists(const char* path);

        /**
        * read a file and return data buffer
        */
        int read(const char* path, Buffer* buffer);

        /**
        * set root directory, can only mount once.
        */
        void mount(const char* root);

        /**
        * convret relative path to absolute path 
        */
        const char* getFull(const char* path);

    private:

        static Filesystem* fs;

        sm_Shared* S; 

    };
}
}