#include <iostream>
#include <glm/glm.hpp>
#include <SDL.h>
#include "SDLauxiliary.h"
#include "TestModel.h"

using namespace std;
using glm::vec3;
using glm::mat3;



//---------------------------------------------------------------------------
// structures
struct Intersection
{
	vec3 position;
	float distance;
	int triangleIndex;
};

// ----------------------------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;
SDL_Surface* screen;
int t;
vector<Triangle> triangles;
void LoadTestModel( vector<Triangle>& triangles );

// Camera GLOBAL VARIABLES
float focalLength;
vec3 cameraPos;
vec3 StartingCameraPos;
float yaw;

// Lights GLOBAL VARIABELS
vec3 lightPos( 0, -0.5, -0.7 );
vec3 lightColor = 14.f * vec3( 1, 1, 1 );
float lightMovement = 0.2;
vec3 indirectLight = 0.5f*vec3( 1, 1, 1 );
// ----------------------------------------------------------------------------
// FUNCTIONS

bool ClosestIntersection(
	vec3 start,
	vec3 dir,
	const vector<Triangle>& triangles,
	Intersection& closestIntersection
);

void RotateCameraAboutY(vec3& pos);

vec3 DirectLight( const Intersection& i );

void Update();
void Draw();

int main( int argc, char* argv[] )
{
	LoadTestModel(triangles);

	cameraPos = vec3(0, 0, -2);
	StartingCameraPos = vec3(0, 0, -2);
	focalLength = SCREEN_WIDTH / 2;

	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
	t = SDL_GetTicks();	// Set start value for timer.

	while( NoQuitMessageSDL() )
	{
		Update();
		Draw();
	}

	SDL_SaveBMP( screen, "screenshot.bmp" );
	return 0;
}

vec3 ComputeIntersection(vec3 start, vec3 dir, Triangle triangle)
{
	// e1 is a vector that is parallel to the edge of the triangle between v0 and v1.
	vec3 e1 = triangle.v1 - triangle.v0;
	// e2 is a vector that is parallel to the edge of the triangle between v0 and v2.
	vec3 e2 = triangle.v2 - triangle.v0;
	vec3 b = start - triangle.v0;           // Our right hand side vector.
	mat3 A(-dir, e1, e2);                  // Our 3x3 matrix.
	vec3 x = glm::inverse(A) * b;        // our point of Intersection.
	return x;                           // Points t,u,v
}

bool IsOnPlane(vec3 point)
{
	// PointOnPlane = v0 + ue1 +ve2
	float t = point.x;
	float u = point.y;
	float v = point.z;

	if ((v + u) <= 1 && v >= 0 && u >= 0 && t > 0) {
		return true;
	}

	return false;
}

bool ClosestIntersection(vec3 start, vec3 dir, const vector<Triangle>& triangles, Intersection& closestIntersection)
{
	float closestValue;  // The value where the closest Intersection happens.
	bool ClosestFound = false; // Was the closest found.
	int Index;                 // The index of the triangle which the intersection was found on.
	for (int i = 0; i<triangles.size(); ++i){
		// Findind the intersection of the ray by the plane.
		vec3 IntersectionPoint = ComputeIntersection(start, dir, triangles[i]);
		float t = IntersectionPoint.x; // The distance of the found intersected point.

		if ( IsOnPlane(IntersectionPoint) ) {
			if (!ClosestFound || t < closestValue) {
				ClosestFound = true; // If a point was found.
				Index = i;
				closestValue = t;
			}
		}
	}

	if (ClosestFound) {
		closestIntersection.triangleIndex = Index;
		closestIntersection.distance = closestValue;
		closestIntersection.position = start + closestValue * dir; // r = s + td
		return true;
	} else {
		return false;
	}
}

void Update()
	{
	// Compute frame time:
	int t2 = SDL_GetTicks();
	float dt = float(t2-t);
	t = t2;
	cout << "Render time: " << dt << " ms." << endl;
	Uint8* keystate = SDL_GetKeyState( 0 );
	if( keystate[SDLK_UP] )
	{
		focalLength = focalLength + 10;
	}
	if( keystate[SDLK_DOWN] )
	{
		focalLength = focalLength - 10;
	}
	if( keystate[SDLK_LEFT] )
	{
		yaw = yaw + 0.1;
		cameraPos = StartingCameraPos;
		RotateCameraAboutY(cameraPos);
	}
	if( keystate[SDLK_RIGHT] )
	{
		yaw = yaw - 0.1;
		cameraPos = StartingCameraPos;
		RotateCameraAboutY(cameraPos);
	}

	if (keystate[SDLK_w]) {
        lightPos.z = lightPos.z + lightMovement;
    }

    if (keystate[SDLK_s]) {
		lightPos.z = lightPos.z - lightMovement;
    }

    if (keystate[SDLK_a]) {
		lightPos.x = lightPos.x - lightMovement;
    }

    if (keystate[SDLK_d]) {
        lightPos.x = lightPos.x + lightMovement;
    }

    if (keystate[SDLK_q]) {
        lightPos.y = lightPos.y - lightMovement;
    }

    if (keystate[SDLK_e]) {
        lightPos.y = lightPos.y + lightMovement;
    }
}


void Draw()
{
	if( SDL_MUSTLOCK(screen) )
		SDL_LockSurface(screen);
	Intersection i;

	for( int y=0; y<SCREEN_HEIGHT; ++y )
	{
		for( int x=0; x<SCREEN_WIDTH; ++x )
		{
			// The vector holding the direction of the ray.
			vec3 dir(x - (SCREEN_WIDTH / 2), y - (SCREEN_HEIGHT / 2), focalLength);
			RotateCameraAboutY(dir);
			// Find out if there was an intersection and give us the information about
			// The closest intersection point.
			// Draw the pixel using the closest intersections color if it was found.
			if (ClosestIntersection(cameraPos, dir, triangles, i))
			{
				vec3 color = triangles[i.triangleIndex].color * (DirectLight(i) + indirectLight);
				PutPixelSDL(screen, x, y, color);
			} else {
				PutPixelSDL(screen, x, y, vec3(0,0,0)); // Otherwise draw a black pixel.
			}
		}
	}

	if( SDL_MUSTLOCK(screen) )
		SDL_UnlockSurface(screen);

	SDL_UpdateRect( screen, 0, 0, 0, 0 );
}

void RotateCameraAboutY(vec3& pos) {
	mat3 RotationMatrixAboutY = mat3(vec3(cos(yaw), 0, sin(yaw)),
	 								vec3(0,1,0),
									vec3(-sin(yaw), 0, cos(yaw)));

	pos = RotationMatrixAboutY * pos;

}

vec3 DirectLight( const Intersection& i )
{
	vec3 normal = triangles[i.triangleIndex].normal; // The normal of the intersecting triangle.
	vec3 r = lightPos - i.position;      // The direction from surface to the light source.
	float distance = glm::distance(i.position, lightPos); // The distance between them.


	// 	we return black if the light source intersects with another surface on the way.
	Intersection si;
	vec3 dir = glm::normalize(i.position - lightPos);
	if(ClosestIntersection(lightPos, dir, triangles, si)){
		// Compensate for rounding error
		if(si.distance < distance - 0.00001f){
			// There is a surface blocking the point from the light.
			return vec3(0,0,0);
		}
	}

	vec3 B = lightColor / (4 * 3.1416f * distance * distance);

	return B * std::max(glm::dot(normal, r), 0.0f);
}
