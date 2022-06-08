#pragma once
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <vector>

using std::string, std::vector;
using vec2 = vector<double>;

class Cell {
    private:
        SDL_Color color = {255, 255, 255};

        vec2 pos = vec2(2, 0);

        vec2 vel0 = vec2(2, 0);
        vec2 vel = vec2(2, 0);

        double d0;
        double d;
        
        SDL_Rect rect;
    public:
        Cell(vec2 pos, vec2 vel, double density);
        ~Cell();
        void SetColor(SDL_Color color);
        void addDensity(double amount);
        void addVelocity(vec2 amount);
        void draw( SDL_Renderer* renderer );
};

using cell_array = vector<Cell>;
using cell_matrix = vector<cell_array>;

void SDL_ExitWithError( string message );