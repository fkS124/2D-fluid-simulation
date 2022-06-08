#include "./lib/particle.h"


#define WIDTH 500
#define HEIGHT 500
void SDL_ExitWithError( string message );


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

    while ( running ) {
        SDL_Event event;
        while ( SDL_PollEvent ) {
            switch( event.type ) {
                case SDL_QUIT:
                    running = false;
            }
        }
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255);
        SDL_RenderClear( renderer );

        SDL_RenderPresent( renderer );
    }

    SDL_DestroyWindow( window );
    SDL_DestroyRenderer( renderer );
    SDL_Quit( );
}


void SDL_ExitWithError( string message ) 
{
    std::cerr << "Error : " << message << " > " << SDL_GetError() << std::endl;
    SDL_Quit();
    exit(EXIT_FAILURE);
}