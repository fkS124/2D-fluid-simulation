#include "./lib/fluid_square.h"

const int WIDTH = 1000;
const int HEIGHT = 1000;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_ExitWithError( "Couldn't init SDL2" );
    } 

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    // Initialize window and renderer
    window = SDL_CreateWindow( "Fluid Simulation", 
                               SDL_WINDOWPOS_UNDEFINED, 
                               SDL_WINDOWPOS_UNDEFINED, 
                               WIDTH, HEIGHT,
                               SDL_WINDOW_ALLOW_HIGHDPI);

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_SOFTWARE );

    if ( window == NULL ) {
        SDL_ExitWithError( "Could not create window" );
    }
    if ( renderer == NULL ) {
        SDL_ExitWithError( "Could not create renderer" );
    }

    // App related variables
    int running = 1;
    int holdingClick = 0;

    int mode = 0;

    int delayCalculations = 50;
    int lastCalculated = 0;
    int lastSprayed = 0;

    int mx, my;
    Uint32 buttons;

    FluidSquare *fluid;
    int SCALE = 5;
    fluid = FluidSquareCreate(WIDTH / SCALE, 0.001f, 0.0f, 0.001f);

    int angle = 0;

    while ( running ) {
        SDL_Event event;
        while ( SDL_PollEvent(&event) ) {
            switch( event.type ) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button)
                    {
                    case SDL_BUTTON_LEFT:
                        holdingClick = 1;
                        break;
                    
                    default:
                        break;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    switch (event.button.button)
                    {
                    case SDL_BUTTON_LEFT:
                        holdingClick = 0;
                        break;
                    
                    default:
                        break;
                    }
                    break;
                default:
                    break;
            }
        }
        if ( holdingClick ) {
            int tmpx, tmpy;
            SDL_GetMouseState(&tmpx, &tmpy);
            

            FluidSquareAddDensity(fluid, tmpx/SCALE, tmpy/SCALE, 100);
            FluidSquareAddVelocity(fluid, tmpx/SCALE, tmpy/SCALE, (tmpx-mx), (tmpy-my));
                
        }
        
        // fill bg with black
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255);
        // clear renderer
        SDL_RenderClear( renderer );

        for (int i = 0; i < fluid->size; i++) {
            for (int j = 0; j < fluid->size; j++) {
                int N = fluid->size;
                if (mode == 0) {
                    int color = fluid->density[IX(i, j)];
                    if (color > 255)
                        color = 255;
                    
                    SDL_SetRenderDrawColor(renderer, color, color, color, 255);
                }
                else {
                    // TODO : here set color according to velocity;
                }
                SDL_Rect rect;
                rect.x = i * SCALE;
                rect.y = j * SCALE;
                rect.w = SCALE;
                rect.h = SCALE;
                SDL_RenderFillRect(renderer, &rect);
            }
        }

        if ( SDL_GetTicks() - lastSprayed > 20) {
            lastSprayed = SDL_GetTicks();
            angle = (angle + rand() % 360) % 360;

            int vel = rand() % 25 + 60;
            int density = 40;
            float velX = cos(angle*PI/180)*vel;
            float velY = sin(angle*PI/180)*vel;

            FluidSquareAddDensity(fluid, 100, 100, density);
            FluidSquareAddVelocity(fluid, 100, 100, velX, velY);
        } 
    

        if ( SDL_GetTicks() - lastCalculated > delayCalculations ) {
            lastCalculated = SDL_GetTicks();
            FluidSquareStep(fluid);

            // Get mouse pos
            buttons = SDL_GetMouseState(&mx, &my);
        }

        // show current frame
        SDL_RenderPresent( renderer );
    }

    FluidSquareFree( fluid );
    SDL_DestroyWindow( window );
    SDL_DestroyRenderer( renderer );
    SDL_Quit( );
}