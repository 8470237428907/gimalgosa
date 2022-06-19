#pragma once

#include "Vector2D.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Obstacle.h"

class Vehicle
{

public:
	Vehicle(int x, int y);
	void draw(SDL_Renderer* renderer);
	void update();
	void applyForce(Vector2D* f);
	void seek(Vector2D* target);
	void arrive(Vector2D* target);
	void edges();
	Vector2D Radian(float x, float y, float r);
	Vector2D getHidingPosition(Obstacle* obstacle, const Vector2D& hunterPos);
	Vector2D hide(const std::vector<Obstacle*>& obstacles, Vehicle* hunter);
private:
	Vector2D* pos;
	Vector2D* vel;
	Vector2D* acc;
	Vector2D* force;
	Vector2D* rd1;
	Vector2D* rd2;
	Vector2D* rd3;
	Vector2D* rotate;

	int maxSpeed;
	float maxForce;
	int r;

	double radian;
};