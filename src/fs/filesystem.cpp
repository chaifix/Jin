#include "filesystem.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>  /* defines FILENAME_MAX */

namespace jin
{
namespace fs
{

    Filesystem* Filesystem::fs = 0;

    Filesystem::Filesystem()
    {
        S = sm_newshared(); 
    }

    Filesystem* Filesystem::get()
    {
        return fs ? fs : (fs = new Filesystem());
    }

    /**
    * r is relative path 
    */
    void Filesystem::mount(const char * path)
    {
        int err = sm_mount(S, path);
        if (err)
        {
            printf("%s mounted path %s", sm_errstr(err), path);
            exit(1); 
        }
    }

    /**
    * 
    */
    int Filesystem::read(const char* path, Buffer* buffer)
    {
        buffer->data = sm_read(S, path, &buffer->size);
        if (buffer->data == 0)
            return 0; 
        return 1; 
    }

    const char* Filesystem::getFull(const char* path)
    {
        return sm_fullpath(S, path);
    }

    bool Filesystem::isDir(const char* path)
    {
        return sm_isdir(S, path);
    }

    bool Filesystem::isFile(const char* path)
    {
        return sm_isreg(S, path); 
    }

    bool Filesystem::exists(const char* path)
    {
        return sm_exists(S, path) == 0;
    }

}
}