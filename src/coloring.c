#include "../lib/coloring.h"


float getMaxVel(float *velX, float *velY) 
{   
    size_t n = sizeof(velX)/sizeof(velX[0]);
    float maximum = 0;

    for (int i = 0; i < n; i++) {
        maximum = fmax(maximum, sqrt(pow(velX[i], 2) + pow(velY[i], 2)));
    }

    return maximum;
}


float getMinVel(float *velX, float *velY)
{
    size_t n = sizeof(velX)/sizeof(velX[0]);
    float minimum = 10000;

    for (int i = 0; i < n; i++) {
        minimum = fmin(minimum, sqrt(pow(velX[i], 2) + pow(velY[i], 2)));
    }

    return minimum;
}



SDL_Color getColorVel(float *velX, float *velY, float maxVel, float minVel, int i, int j, SDL_Color color_max, SDL_Color color_min) 
{
    size_t N = sizeof(velX)/sizeof(velX[0]);

    SDL_Color finalColor = {0, 0, 0};
    float vel = sqrt(pow(velX[IX(i, j)], 2) + pow(velY[IX(i, j)], 2));

    int rMax = color_max.r;
    int gMax = color_max.g;
    int bMax = color_max.b;

    int rMin = color_max.r;
    int gMin = color_max.g;
    int bMin = color_max.b;


    finalColor.r = vel/(maxVel - minVel) * (rMax - rMin);
    finalColor.g = vel/(maxVel - minVel) * (gMax - gMin);
    finalColor.b = vel/(maxVel - minVel) * (bMax - bMin);

    return finalColor;
}
