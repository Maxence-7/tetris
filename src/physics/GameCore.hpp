#pragma once
#include "./containers/Shape.hpp"
class GameCore {
    public:
        using Score_t = unsigned;
        using Tick_t = long long;

    private:
        Score_t m_score;
        Tick_t m_tick;
        Shape m_curShape; 
        Shape m_nextShape;
        
    public:
        GameCore(/* args */);
        ~GameCore();
};
