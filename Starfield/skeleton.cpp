// Introduction lab that covers:
// * C++
// * SDL
// * 2D graphics
// * Plotting pixels
// * Video memory
// * Projection
// * glm::vec3 and std::vector

#include "SDL.h"
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "SDLauxiliary.h"

using namespace std;
using glm::vec3;

// --------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 1320;
const int SCREEN_HEIGHT = 720;
SDL_Surface* screen;
vector<vec3> stars( 1000 );
int f = SCREEN_HEIGHT / 2;
int t;
float v = 0.0005;

// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw();
void Update();

// --------------------------------------------------------
// FUNCTION DEFINITIONS

int main( int argc, char* argv[] )
{
	for (int s = 0; s < stars.size(); s++) {
		stars[s].x = -1 + float (rand()) / float (RAND_MAX/(1-(-1))); // Random -1< x <1
		stars[s].y = -1 + float (rand()) / float (RAND_MAX/(1-(-1))); // Random -1< y <1
		stars[s].z = float(rand()) / float(RAND_MAX);                 // Random 0< z <1
		// cout << stars[s].x << " " << stars[s].y << " " << stars[s].z << endl;
	}

	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
	while( NoQuitMessageSDL() )
	{
		Update();
		Draw();
	}
	SDL_SaveBMP( screen, "screenshot.bmp" );
	return 0;
}

void Draw()
{
	SDL_FillRect(screen, 0, 0);
	if (SDL_MUSTLOCK(screen))
		SDL_LockSurface(screen);

	for( size_t s=0; s<stars.size(); ++s ) {
		int u = f*stars[s].x / stars[s].z + SCREEN_WIDTH / 2;
		int v = f*stars[s].y / stars[s].z + SCREEN_HEIGHT / 2;

		vec3 color= 0.2f* vec3(1, 1, 1) / (stars[s].z * stars[s].z);
		PutPixelSDL(screen, u, v, color);
	}

	if (SDL_MUSTLOCK(screen))
		SDL_UnlockSurface(screen);

	SDL_UpdateRect( screen, 0, 0, 0, 0 );
}

void Update()
{
	int t2 = SDL_GetTicks();
	float dt = float(t2 - t);
	t = t2;

	for (int s = 0; s < stars.size(); s++)
	{
		stars[s].z = stars[s].z - v*dt;

		if (stars[s].z <= 0)
		{
			stars[s].z += 1;
		}
		if (stars[s].z > 1)
		{
			stars[s].z -= 1;
		}
	}
}
