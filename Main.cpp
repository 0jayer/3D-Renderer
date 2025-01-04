#include "Render3d.h"
#include<SDL.h>
#include<vector>


//cube points
std::vector<point3d>points{
	point3d{-1.0f,-1.0f,-1.0f},point3d{-1.0f,-1.0f,1.0f},
	point3d{1.0f,-1.0f,-1.0f},point3d{-1.0f,1.0f,-1.0f},
	point3d{-1.0f,1.0f,1.0f},point3d{1.0f,-1.0f,1.0f},
	point3d{1.0f,1.0f,-1.0f},point3d{1.0f,1.0f,1.0f}
};

//cube vertices
std::vector<vertex> vertices{
	vertex{0,1},vertex{0,2},vertex{0,3},
	vertex{2,5},vertex{3,6},vertex{3,4},
	vertex{4,7},vertex{6,7},vertex{7,5},
	vertex{5,1},vertex{4,1},vertex{2,6}
};


int main(int argc,char* argv[])
{
	//creating a window
	SDL_Window* window;
	SDL_Renderer* renderer;
	window = SDL_CreateWindow("3drenderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	bool running = true;

	//creating the render object
	render3d render3d1(window, renderer, points, vertices);

	while (running)
	{
		//how to quit
		if (SDL_QuitRequested())
		{
			running = false;
			break;
		}
		render3d1.render();
	}
	return 0;
}