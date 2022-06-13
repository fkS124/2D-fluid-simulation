#pragma once
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <vector>

using std::string;
using std::vector;


class Vec2 {
    public:
        double x, y;
        Vec2(double x, double y);
        ~Vec2();

        Vec2 operator+(const Vec2 other);
        Vec2 operator-(const Vec2 other);
        void operator+=(const Vec2 other);
};



class Cell {
    private:
        SDL_Color color = {255, 255, 255};

        Vec2 pos = Vec2(0, 0);

        Vec2 vel0 = Vec2(0, 0);
        Vec2 vel = Vec2(0, 0);

        double d0;
        double d;
        
        SDL_Rect rect;
    public:
        Cell(Vec2 pos, Vec2 vel, double density);
        ~Cell();
        void SetColor(SDL_Color color);
        
        void addDensity(double amount);
        void setDensity(double density);
        double getDensity();
        double getDensity0();

        void setVx(double Vx);
        void setVy(double Vy);
        Vec2 getVelocity();
        Vec2 getVelocity0();
        void addVelocity(Vec2 amount);

        void draw( SDL_Renderer* renderer );
};

using cell_array = vector<Cell>;
using cell_matrix = vector<cell_array>;

void SDL_ExitWithError( string message );