#include "Render3d.h"

render3d::render3d(SDL_Window* window, SDL_Renderer* renderer, std::vector<point3d>& points, std::vector<vertex>& vertices)
{
	SDL_GetWindowSize(window, &WindowSizeX, &WindowSizeY);
	this->renderer = renderer;
	this->points = points;
	this->vertices = vertices;
}

void render3d::render()
{
	//making the simulation frame independent
	auto time1 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration(0);

	SDL_SetRenderDrawColor(renderer,0 , 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	rotation += 1 * dt;

	//rotating and drawing the lines
	for (auto& vertex : vertices)
	{
		point3d rotatedstartpoint = rotateX(rotateY(points[vertex.start]));
		point3d rotatedendpoint = rotateX(rotateY(points[vertex.end]));
		point2d start = projection(rotatedstartpoint);
		point2d end = projection(rotatedendpoint);
		SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
	}
	//rendering the lines
	SDL_RenderPresent(renderer);

	//changing in dt
	auto time2 = std::chrono::high_resolution_clock::now();
	duration = time2 - time1;
	dt = duration.count();
	time1 = time2;
}

//function for X-axis rotation
point3d render3d::rotateX(point3d point)
{
	point3d returnpoint;
	returnpoint.x = point.x;
	returnpoint.y = cos(rotation) * point.y - sin(rotation) * point.z;
	returnpoint.z = sin(rotation) * point.y + cos(rotation) * point.z;
	return returnpoint;
}

//function for Y-axis rotation
point3d render3d::rotateY(point3d point)
{
	point3d returnpoint;
	returnpoint.x = cos(rotation) * point.x - sin(rotation) * point.z;
	returnpoint.y = point.y;
	returnpoint.z = sin(rotation) * point.x + cos(rotation) * point.z;
	return returnpoint;
}

//function for projecting 3d objects on a 2d screen
point2d render3d::projection(point3d point)
{
	return point2d{
		WindowSizeX / 2 + (focal_length * point.x) / (focal_length + point.z) * 100,
		WindowSizeY / 2 + (focal_length * point.y) / (focal_length + point.z) * 100
	};
}