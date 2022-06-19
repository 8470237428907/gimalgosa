#include "Walker.h"
#include "Vector2D.h"
#include "Vehicle.h"
#include "InputHandler.h"
#include <random>
#define WIDTH 600
#define HEIGHT 400

Vector2D* Dir;
Vehicle* m_vehicle;


Walker::Walker(int x, int y) 
{
    Dir = new Vector2D(0, 0);
    m_vehicle = new Vehicle(100, 100);
}

void Walker::update() 
{
    //m_vehicle->seek(Dir);
    m_vehicle->arrive(Dir);
    m_vehicle->update();
    Dir = TheInputHandler::Instance()->getMousePosition();
}

void Walker::draw(SDL_Renderer* renderer)
{
    filledCircleRGBA(renderer, Dir->getX(), Dir->getY(), 15, 255, 255, 0, 200);
    m_vehicle->draw(renderer);

    filledCircleRGBA(renderer, WIDTH / 2, HEIGHT / 2, 20, 255, 0, 0, 200);
    m_vehicle->draw(renderer);
}
