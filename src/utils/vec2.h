#ifndef __JIN_VEC2_H
#define __JIN_VEC2_H

namespace jin 
{
class Vec2
{
public: 
    float x, y; 
    Vec2 operator + (const Vec2& v); 
    Vec2 operator - (const Vec2& v); 
    Vec2 operator * (const Vec2& v); 
     
}// Vec2   
Vec2 operator * (float n, const Vec2& v); 

}// jin 

#endif