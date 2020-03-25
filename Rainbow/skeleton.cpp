// Introduction lab that covers:
// * C++
// * SDL
// * 2D graphics
// * Plotting pixels
// * Video memory
// * Color representation
// * Linear interpolation
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

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Surface* screen;

// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw();


void Interpolate( float a, float b, vector<float>& result )
/*
* A function which takes in two float numbers and a reference to a vector
* Interpolates the values in between.
*/
{
	float current = a;
	float diff = 0;
	if (result.size() != 1) {
		diff = (b - a) / (result.size() - 1);
	}
	result[0] = current;
	for (int i = 1; i < result.size(); i++) {
		result[i] = current + diff;
		current = result[i];
	}
}

void Interpolate( vec3 a, vec3 b, vector<vec3>& result )
/*
* A function which takes in two vec3 variables and a reference to a vector
* of vec3 and Interpolates the values in between.
*/
{
	vec3 current = a; // current is our starting value at te beginning.
	vec3 diff =  vec3 (0, 0, 0);  // Diffrece of zero.
	if (result.size() != 1) {    // In case our vector size is not 1 .
		for (int i = 0; i < 3; i++) { // we find the diffrence between each step.
			diff[i] = (b[i] - a[i]) / (result.size() - 1);
		} // The condition is there to make sure we do not devide by zero.
	}
	result[0] = current;  // We keep the first elemet as is.
	// Update the value of interpolation of the values in the vector.
	for (int i = 1; i < result.size(); i++) {
		for (int j = 0; j < 3; j++) { // declare the value of next...
			// ... element in the vector after adding the diffrence.
			result[i][j] = current[j] + diff[j];
		}
		current = result[i]; // Set our current to the new current value.
	}
}

// --------------------------------------------------------
// FUNCTION DEFINITIONS

int main( int argc, char* argv[] )
{
	//
	// vector<float> result( 10 ); // Create a vector width 10 floats
	// Interpolate( 5, 14, result ); // Fill it with interpolated values
	// for( int i=0; i<result.size(); ++i )
	// 	cout << result[i] << " "; // Print the result to the terminal
	// 	cout << " " << endl;
	//
	// vector<vec3> result_vec( 4 );
	// vec3 a(1,4,9.2);
	// vec3 b(4,1,9.8);
	// Interpolate( a, b, result_vec );
	// for( int i=0; i<result_vec.size(); ++i )
	// {
	// 	cout << "( "
	// 	<< result_vec[i].x << ", "
	// 	<< result_vec[i].y << ", "
	// 	<< result_vec[i].z << " ) " << endl;
	// }

	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
	while( NoQuitMessageSDL() )
	{
		Draw();
	}

	SDL_SaveBMP( screen, "screenshot.bmp" );
	return 0;

}

void Draw()
{

	vec3 topLeft(1,0,0); // red
	vec3 topRight(0,0,1); // blue
	vec3 bottomLeft(0,1,0); // green
	vec3 bottomRight(1,1,0); // yellow

	vector<vec3> leftSide( SCREEN_HEIGHT );
	vector<vec3> rightSide( SCREEN_HEIGHT );
	Interpolate( topLeft, bottomLeft, leftSide );
	Interpolate( topRight, bottomRight, rightSide );

	for( int y=0; y<SCREEN_HEIGHT; ++y )
	{
		vector<vec3> row(SCREEN_WIDTH);
		Interpolate( leftSide[y], rightSide[y], row );
		for( int x=0; x<SCREEN_WIDTH; ++x )
		{
			PutPixelSDL( screen, x, y, row[x] );
		}
	}

	if( SDL_MUSTLOCK(screen) )
		SDL_UnlockSurface(screen);

	SDL_UpdateRect( screen, 0, 0, 0, 0 );
}
