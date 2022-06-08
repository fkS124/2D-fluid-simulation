#include "./lib/fluid.h"

const int WIDTH = 500;
const int HEIGHT = 500;

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
    bool running = true;

    int delayCalculations = 50;
    int lastCalculated = 0;

    Fluid fluid(WIDTH, 5, 1, 0.5f);

    while ( running ) {
        SDL_Event event;
        while ( SDL_PollEvent(&event) ) {
            switch( event.type ) {
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }
        // fill bg with black
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255);
        // clear renderer
        SDL_RenderClear( renderer );
        
        fluid.draw( renderer );

        if ( SDL_GetTicks() - lastCalculated > delayCalculations ) {
            lastCalculated = SDL_GetTicks();
            fluid.calculate();
        }

        // show current frame
        SDL_RenderPresent( renderer );
    }

    SDL_DestroyWindow( window );
    SDL_DestroyRenderer( renderer );
    SDL_Quit( );
}