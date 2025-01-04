#pragma once
#include<SDL.h>
#include<cmath>
#include<chrono>
#include<vector>

//structures for 2d 3d and vertices
struct point2d {
	float x, y;
};
struct point3d {
	float x, y, z;
};
struct vertex {
	int start, end;
};

class render3d
{
public:
	render3d(SDL_Window* window, SDL_Renderer* renderer, std::vector<point3d>& points, std::vector<vertex>& vertices);
	void render();
private:
	point3d rotateX(point3d point);		//function for X-axis rotation
	point3d rotateY(point3d point);		//function for Y-axis rotation
	point2d projection(point3d point);	//function for projecting 3d objects on a 2d screen

	float rotation = 0.0f;			//rotation co-efficient
	float focal_length = 10.0;		//focal length for projection calculation
	float dt = 0.0f;				//time step

	//variables to customize window size
	int WindowSizeX;				
	int WindowSizeY;
	SDL_Renderer* renderer;

	//arrays to store points and vertices to render 
	std::vector<point3d>points;
	std::vector<vertex>vertices;

};