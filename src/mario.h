#include <jin.h>

using namespace jin; 

class MarioGame: public jin::Game
{
public: 
    void update(float dt); 
    void handle(); 
    void draw(); 
}