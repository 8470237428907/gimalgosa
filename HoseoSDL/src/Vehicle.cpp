#include "Vehicle.h"
#include <math.h>
#include "Obstacle.h"
#include "Vector2D.h"
#define WIDTH 600
#define HEIGHT 400


Vehicle::Vehicle(int x, int y) {
	pos = new Vector2D(0, 0);
	acc = new Vector2D(0, 0);
	vel = new Vector2D(0, 0);
	force = new Vector2D(0, 0);
	rd1 = new Vector2D(1, 1);
	rd2 = new Vector2D(1, 1);
	rd3 = new Vector2D(1, 1);
	rotate = new Vector2D(0, 0);
	maxSpeed = 4;
	maxForce = 0.25f;
	r = 16;
}

void Vehicle::update() {
	*vel += *acc;
	vel->limit(maxSpeed);
	*pos += *vel;
	*acc *= 0;

	radian = atan2(vel->getY(), vel->getX());

	*rd1 = Radian(-r, -r / 2, radian);
	*rd2 = Radian(-r, r / 2, radian);
	*rd3 = Radian(r, 0, radian);

	edges();
}

void Vehicle::draw(SDL_Renderer* renderer) {
	filledTrigonRGBA(renderer, rd1->getX() + pos->getX(), rd1->getY() + pos->getY(),
		rd2->getX() + pos->getX(), rd2->getY() + pos->getY(),
		rd3->getX() + pos->getX(), rd3->getY() + pos->getY(),
		255, 255, 255, 255);
}

Vector2D Vehicle::Radian(float x, float y, float r) {
	rotate = new Vector2D(0, 0);
	rotate->setX(cos(radian) * x - sin(radian) * y);
	rotate->setY(sin(radian) * x + cos(radian) * y);

	return *rotate;
}

void Vehicle::applyForce(Vector2D* f) {
	*acc += *force;
}

void Vehicle::seek(Vector2D* target) {
	*force = *target - *pos;
	force->normalize();
	*force *= maxSpeed;
	*force -= *vel;
	force->limit(maxForce);
	applyForce(force);
}

Vector2D Vehicle::getHidingPosition(Obstacle* obstacle, const Vector2D& hunterPos)
{
	Vector2D direction = obstacle->position - hunterPos;
	//direction = direction.normalized() * (obstacle->radius + 20);
	return obstacle->position + direction;
}

void Vehicle::edges()
{
	if (pos->getX() > WIDTH + r)
	{
		pos->setX(r);
	}
	else if (pos->getX() < -r)
	{
		pos->setX(WIDTH + r);
	}
	if (pos->getY() > HEIGHT + r)
	{
		pos->setY(-r);
	}
	else if (pos->getY() < -r)
	{
		pos->setY(HEIGHT + r);
	}
}