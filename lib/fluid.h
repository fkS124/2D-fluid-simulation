#pragma once
#include "./cell.h"


class Fluid {
    private:
        cell_matrix allCells; 
    public:
        int size;
        double diffusion;
        double viscosity;
        double getDensity(int i, int j);
        double getDensity0(int i, int j);
        void setDensity(int i, int j, double val);
        double getVx(int i, int j);
        double getVx0(int i, int j);
        void setVx(int i, int j, double val);
        double getVy(int i, int j);
        double getVy0(int i, int j);
        void setVy(int i, int j, double val);
        Fluid(int size, int diffusion, int viscosity, float dt);
        ~Fluid();
        void draw( SDL_Renderer* renderer );
        void calculate();
        void diffuse(int mode, Fluid &fluid, double dt, int iter);
};