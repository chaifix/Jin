#ifndef __JIN_GAME_H
#define __JIN_GAME_H

namespace jin 
{
class Game
{
public:
    virtual void update(float dt) = 0; 
    virtual void handle() = 0; 
    virtual void draw() = 0 ; 
    void run();
private:  
}// Game 
}// jin 

#endif