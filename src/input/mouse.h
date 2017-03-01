#ifndef __JIN_MOUSE_H
#define __JIN_MOUSE_H
namespace jin
{
namespace input
{
    class Mouse
    {
    public:

    };

    inline const char* buttonStr(int id) {
        switch (id) {
        case 1: return "left";
        case 2: return "middle";
        case 3: return "right";
        case 4: return "wheelup";
        case 5: return "wheeldown";
        default: return "?";
        }
    }

    inline const char* wheelStr(int dir)
    {

    }
}
}
#endif