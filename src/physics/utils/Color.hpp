#pragma once

class Color {
    public:
        using Color_t = double; 
    public:
        Color_t r;
        Color_t g; 
        Color_t b;
    public:
        Color();
        Color(Color_t,Color_t,Color_t);
        ~Color();

};

