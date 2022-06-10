#include "../lib/cell.h"

void SDL_ExitWithError( string message ) 
{
    std::cerr << "Error : " << message << " > " << SDL_GetError() << std::endl;
    SDL_Quit();
    exit(EXIT_FAILURE);
}


Vec2::Vec2(double x, double y) {
    this->x = x;
    this->y = y;
}

Vec2 Vec2::operator+(const Vec2 other) {
    return Vec2(this->x + other.x, this->y + other.y);
}

Vec2 Vec2::operator-(const Vec2 other) {
    return Vec2(this->x - other.x, this->y - other.y);
}


void Vec2::operator+=(const Vec2 other) {
    x += other.x;
    y += other.y;
}


Cell::Cell(Vec2 pos, Vec2 vel, double density) {
    this->pos = pos;
    this->vel = vel;
    this->vel0 = vel;
    this->d = density;
    this->d0 = density;

    rect.x = pos.x;
    rect.y = pos.y;
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

void Cell::addVelocity( Vec2 amount ) {
    vel += amount;
}