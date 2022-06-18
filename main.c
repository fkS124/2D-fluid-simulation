#include "./lib/fluid_square.h"

const int WIDTH = 500;
const int HEIGHT = 500;


int min(int a, int b) {
    return (a > b) ? b : a;
}


int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_ExitWithError( "Couldn't init SDL2" );
    } 

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    // Initialize window and renderer
    window = SDL_CreateWindow( "Fluid Simulation (Visualization : density)", 
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
    int velThreshold = 5;


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
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_s:
                        mode = (mode + 1) % 3;
                        switch (mode) {
                            case 0:
                                SDL_SetWindowTitle(window, "Fluid Simulation (Visualization : density)");
                                break;
                            case 1:
                                SDL_SetWindowTitle(window, "Fluid Simulation (Visualization : velocity)");
                                break;
                            case 2:
                                SDL_SetWindowTitle(window, "Fluid Simulation (Visualization : density and velocity)");
                                break;
                            default:
                                break;
                        }
                        break;
                    
                    default:
                        break;
                    }
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
                SDL_Rect rect;
                rect.x = i * SCALE;
                rect.y = j * SCALE;
                rect.w = SCALE;
                rect.h = SCALE;
                if (mode < 2) {

                    if (mode == 0) {
                        int color = min(fluid->density[IX(i, j)], 255);
                        SDL_SetRenderDrawColor(renderer, color, color, color, 255);
                    }
                    else if (mode == 1) {
                        float vel = min(sqrt(pow(fluid->Vx[IX(i, j)], 2) + pow(fluid->Vy[IX(i, j)], 2)), velThreshold);
                        SDL_SetRenderDrawColor(renderer, (vel / velThreshold) * 255, 0, 0, 255);
                    }
                    SDL_RenderFillRect(renderer, &rect);
                }
                else if (mode == 2) {
                    int color = min(fluid->density[IX(i, j)], 255);
                
                    float vel = min(sqrt(pow(fluid->Vx[IX(i, j)], 2) + pow(fluid->Vy[IX(i, j)], 2)), velThreshold);
                    if (color+vel != 0)
                        SDL_SetRenderDrawColor(renderer, 0, min(50+(color+vel)/2, 255), min(100+(color+vel)/2, 255), 255);
                    else 
                        SDL_SetRenderDrawColor(renderer, 0, 40, 40, 0);
                    SDL_RenderFillRect(renderer, &rect);
                    
                }
            }
        }

        if ( SDL_GetTicks() - lastSprayed > 20) {
            lastSprayed = SDL_GetTicks();
            angle = (angle + rand() % 360) % 360;

            int vel = rand() % 25 + 60;
            int density = 40;
            float velX = cos(angle*PI/180)*vel;
            float velY = sin(angle*PI/180)*vel;

            FluidSquareAddDensity(fluid, WIDTH / SCALE / 2, WIDTH / SCALE / 2, density);
            FluidSquareAddVelocity(fluid, WIDTH / SCALE / 2, WIDTH / SCALE / 2, velX, velY);
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
