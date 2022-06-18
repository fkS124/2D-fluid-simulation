#include "./coloring.h"

struct FluidSquare {
    int size;
    float dt;
    float diff;
    float visc;

    float *s;
    float *density;

    float *Vx;
    float *Vy;

    float *Vx0;
    float *Vy0;
};
typedef struct FluidSquare FluidSquare;

FluidSquare *FluidSquareCreate(int size, float diffusion, float viscosity, float dt);
void FluidSquareFree(FluidSquare *square);
void FluidSquareAddDensity(FluidSquare *square, int x, int y, float amount);
void FluidSquareAddVelocity(FluidSquare *square, int x, int y, float amtX, float amtY);
void FluidSquareStep(FluidSquare *square);

void SDL_ExitWithError(const char *);