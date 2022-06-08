#include "../lib/cell.h"

void SDL_ExitWithError( string message ) 
{
    std::cerr << "Error : " << message << " > " << SDL_GetError() << std::endl;
    SDL_Quit();
    exit(EXIT_FAILURE);
}



Cell::Cell(vec2 pos, vec2 vel, double density) {
    this->pos = pos;
    this->vel = vel;
    this->vel0 = vel;
    this->d = density;
    this->d0 = density;

    rect.x = pos[0];
    rect.y = pos[1];
    rect.w = 5;
    rect.h = 5;
}

Cell::~Cell() {}


void Cell::draw( SDL_Renderer* renderer ) {
    if (SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, 255) != 0)
        SDL_ExitWithError( "Could not set color" );
    if (SDL_RenderFillRect( renderer, &rect ) != 0 )
        SDL_ExitWithError( "Could not draw rect");
}

void Cell::SetColor( SDL_Color color ) {
    this->color = color;
}

void Cell::addDensity( double amount ) {
    d += amount;
}

void Cell::addVelocity( vec2 amount ) {
    vel[0] += amount[0];
    vel[1] += amount[1];
}