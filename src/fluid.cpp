#include "../lib/fluid.h"


Fluid::Fluid(int size, int diffusion, int viscosity, float dt) {
    this->size = size;

    for (double i = 0; i < size; i+=5) {
        cell_array row;
        for (double j = 0; j < size; j+=5) {
            row.push_back(Cell(Vec2(i, j), Vec2(0, 0), 1));
        }
        allCells.push_back(row);
    }

    this->diffusion = diffusion;
    this->viscosity = viscosity;
}

Fluid::~Fluid() {
}

void Fluid::draw( SDL_Renderer* renderer ) {
    // draw all the cells
    for (int i = 0; i < allCells.size(); i++) {
        for (int j = 0; j < allCells[i].size(); j++) {
            allCells[i][j].draw( renderer );
        }
    }
}

void Fluid::calculate() {
    // diffuse vx
    // diffuse vy
    
    // projet vx and vy

    // advect vx
    // advect vy

    // project vx and vy

    // diffuse density
    // advect density
}
