#pragma once
#include "./cell.h"


class Fluid {
    private:
        int size;
        double diffusion;
        double viscosity;
        cell_matrix allCells;
    public:
        Fluid(int size, int diffusion, int viscosity, float dt);
        ~Fluid();
        void draw( SDL_Renderer* renderer );
        void calculate();
        void diffuse();
};