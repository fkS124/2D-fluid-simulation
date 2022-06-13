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

double Fluid::getDensity(int i, int j) {return allCells[i][j].getDensity();}
double Fluid::getDensity0(int i, int j) {return allCells[i][j].getDensity0();}
void Fluid::setDensity(int i, int j, double val) {allCells[i][j].setDensity(val);}
double Fluid::getVx(int i, int j) {return allCells[i][j].getVelocity().x;}
double Fluid::getVx0(int i, int j) {return allCells[i][j].getVelocity0().x;}
void Fluid::setVx(int i, int j, double val) {allCells[i][j].setVx(val);}
double Fluid::getVy(int i, int j) {return allCells[i][j].getVelocity().y;}
double Fluid::getVy0(int i, int j) {return allCells[i][j].getVelocity0().y;}
void Fluid::setVy(int i, int j, double val){allCells[i][j].setVy(val);}

void Fluid::draw( SDL_Renderer* renderer ) {
    // draw all the cells
    for (int i = 0; i < allCells.size(); i++) {
        for (int j = 0; j < allCells[i].size(); j++) {
            allCells[i][j].draw( renderer );
        }
    }
}


void set_bnd(int mode, Fluid &fluid) {
    // 0 density
    // 1 vx
    // 2 vy
    const int N = fluid.size;
    double (Fluid::*getf)(int, int);
    void (Fluid::*setf)(int, int, double);
    
    if (mode == 0) {
        getf = &Fluid::getDensity;
        setf = &Fluid::setDensity;
    }
    else if (mode == 1) {
        getf = &Fluid::getVx;
        setf = &Fluid::setVx;
    }
    else {
        getf = &Fluid::getVy;
        setf = &Fluid::setVy;
    }

    // (fluid.*setf)(0, 0, 0.5);
    // (fluid.*getf)(0, 0);

    for (int i = 1; i < N - 1; i++) {
        (fluid.*setf)(i, 0, (mode == 2 ? -(fluid.*getf)(i, 1) : (fluid.*getf)(i, 1)));
        (fluid.*setf)(i, N-1, (mode == 2 ? -(fluid.*getf)(i, N-2) : (fluid.*getf)(i, N-2)));
    }

    for (int j = 1; j < N -1; j++) {
        (fluid.*setf)(0, j, (mode == 1 ? -(fluid.*getf)(1, j) : (fluid.*getf)(1, j)));
        (fluid.*setf)(N-1, j, (mode == 1 ? -(fluid.*getf)(N-2, j) : (fluid.*getf)(N-2, j)));
    }

    (fluid.*setf)(0, 0, 0.33 * ((fluid.*getf)(1, 0) + (fluid.*getf)(0, 1)));
    (fluid.*setf)(0, N-1, 0.33 * ((fluid.*getf)(1, N-1) + (fluid.*getf)(0, N-2)));
    (fluid.*setf)(N-1, 0, 0.33 * ((fluid.*getf)(N-2, 0) + (fluid.*getf)(N-1, 1)));
    (fluid.*setf)(N-1, N-1, 0.33 * ((fluid.*getf)(N-2, N-1) + (fluid.*getf)(N-1, N-2)));
}


void lin_solve(int mode, Fluid &fluid, float a, float c, int iter) {
    double (Fluid::*getf)(int, int);
    double (Fluid::*getf0)(int, int);
    void (Fluid::*setf)(int, int, double);
    
    if (mode == 0) {
        getf0 = &Fluid::getDensity0;
        getf = &Fluid::getDensity;
        setf = &Fluid::setDensity;
    }
    else if (mode == 1) {
        getf0 = &Fluid::getVx0;
        getf = &Fluid::getVx;
        setf = &Fluid::setVx;
    }
    else {
        getf0 = &Fluid::getVy0;
        getf = &Fluid::getVy;
        setf = &Fluid::setVy;
    }


    const int N = fluid.size;
    double cRecip = 1.0 / c;
    for (int k = 0; k < iter; k++) {
        for (int j = 1; j < N - 1; j++) {
            for (int i = 1; i < N - 1; i++) {
                (fluid.*setf)(i, j, (
                    (fluid.*getf0)(i, j) + a * (
                          (fluid.*getf)(i+1, j) 
                        + (fluid.*getf)(i-1, j) 
                        + (fluid.*getf)(i, j+1) 
                        + (fluid.*getf)(i, j-1)
                    )
                )*cRecip);
            }
        }
        set_bnd(mode, fluid);
    }
}


void Fluid::diffuse(int mode, Fluid &fluid, double dt, int iter) {
    double a = dt * fluid.diffusion * (fluid.size - 2) * (fluid.size - 2);
    lin_solve(mode, fluid, a, 1 + 6 * a, iter);
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
