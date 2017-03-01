#ifndef __JIN_CORE_GAME_H
#define __JIN_CORE_GAME_H

namespace jin
{
namespace core
{
    class Game
    {
    public:
    
        void quit(); 
    
        bool running(); 
        
        static Game* get(); 
    
    private:
    
        Game();
        
        static Game* g_game; 
        
        bool run;
    };
}
}

#endif