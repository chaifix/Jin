#include <string.h>

namespace jin
{
namespace fs
{

    /**
    * A file data buffer. 
    */
    class Buffer
    {
    public:
        
        inline Buffer(): data(0), size(0)
        {
        }

        inline ~Buffer()
        {
            size = 0;
            delete[] data; 
        }

        inline Buffer(void* d, int size)
        {
            data = new char(size);
            memcpy(data, d, size);
        }

    public:

        // data position in memory     
        void* data;

        // data buffer size 
        unsigned int size; 
    
    };

}
}