#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265
#define IX(x, y) ((x) + (y) * N)

SDL_Color getColorVel(float *velX, float *velY, float maxVel, float minVel, int i, int j, SDL_Color color_max, SDL_Color color_min);
float getMinVel(float *velX, float *velY);
float getMaxVel(float *velX, float *velY);