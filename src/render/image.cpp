#include "image.h"
#include "libs/stb/stb_image.h"
#include "utils/utils.h"
namespace jin
{
namespace render
{
    Image::Image(): Drawable(), pixels(0)
    {
        int a = 1; 
    }

    Image::~Image()
    {
        Drawable::~Drawable();
        stbi_image_free(pixels);
    }

    void Image::init()
    {
        Drawable::init();
        pixels  = 0; 
    }

    color Image::getPixel(int x, int y)
    {
        if (without(x, 0, width) || without(y, 0, height))
            return 0; 
        return pixels[x + y * width];
    }
    
    bool Image::loadf(const char* f)
    {
        unsigned char* imageData = stbi_load(f, &width, &height, NULL, STBI_rgb_alpha);
        if (imageData == 0) return false; 
        pixels = (color*)imageData; 

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,
            height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

        // set render vertices 
        Drawable::setVertices(
            new float [DRAWABLE_V_SIZE] {
                0, 0,
                0, (float)height,
                (float)width, (float)height,
                (float)width, 0,
            },
            new float [DRAWABLE_V_SIZE] {
                0, 0,
                0, 1,
                1, 1,
                1, 0
            }
        );

        return true;
    }

    bool Image::loadb(const char* b, int size)
    {
        // Ê¹ÓÃstbi_load_from_memoryÌæ´ú
        unsigned char* imageData = stbi_load_from_memory((unsigned char *)b, size, &width, &height, NULL, STBI_rgb_alpha);
        if (imageData == 0) return false;
        pixels = (color*)imageData;

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,
            height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

        // set render vertices 
        Drawable::setVertices(
            new float [DRAWABLE_V_SIZE] {
            0, 0,
                0, (float)height,
                (float)width, (float)height,
                (float)width, 0,
        },
            new float [DRAWABLE_V_SIZE] {
                0, 0,
                    0, 1,
                    1, 1,
                    1, 0
            }
            );

        return true; 
    }
}
}