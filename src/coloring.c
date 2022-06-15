#include "../lib/coloring.h"


SDL_Color getColorVel(float *velX, float *velY, int i, int j)
{
    size_t N = sizeof(velX)/sizeof(float);
    SDL_Color finalColor = {0, 0, 0};
    float vel = sqrt(pow(velX[IX(i, j)], 2) + pow(velY[IX(i, j)], 2));

    int r = (vel / 20) * 255;
    printf("r : %f \n", vel);
    finalColor.r = r;

    return finalColor;
}
