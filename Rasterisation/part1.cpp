#include <iostream>
#include <glm/glm.hpp>
#include <SDL.h>
#include "SDLauxiliary.h"
#include "TestModel.h"

using namespace std;
using glm::vec3;
using glm::ivec2;
using glm::mat3;
using glm::vec2;


// ----------------------------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;
SDL_Surface* screen;
int t;
vector<Triangle> triangles;
vec3 currentColor;

// CAMERA VARIABLES
vec3 cameraPos( 0, 0, -3.001 );
float focalLength = SCREEN_HEIGHT;
float yaw;
float pitch;
float spin;
mat3 RX;
mat3 RY;
mat3 RZ;

// ----------------------------------------------------------------------------
// FUNCTIONS

void Update();
void Draw();
void VertexShader( const vec3& v, ivec2& p );
void Interpolate( ivec2 a, ivec2 b, vector<ivec2>& result );
void DrawLineSDL(SDL_Surface* surface, ivec2 a, ivec2 b, vec3 color);
void DrawPolygonEdges( const vector<vec3>& vertices );
void RotateCameraAboutX();
void RotateCameraAboutY();
void RotateCameraAboutZ();
void ComputePolygonRows(const vector<ivec2>& vertexPixels, vector<ivec2>& leftPixels,
vector<ivec2>& rightPixels );
void DrawPolygonRows(vector<ivec2>leftPixels, vector<ivec2>rightPixels);
void DrawPolygon( const vector<vec3>& vertices );


int main( int argc, char* argv[] )
{
	LoadTestModel( triangles );
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

void Update()
{
	// Compute frame time:
	int t2 = SDL_GetTicks();
	float dt = float(t2-t);
	t = t2;
	cout << "Render time: " << dt << " ms." << endl;

	Uint8* keystate = SDL_GetKeyState(0);

	if( keystate[SDLK_UP] )
	{
		pitch = pitch - 0.001f;
		RotateCameraAboutX();
	}

	if( keystate[SDLK_DOWN] )
	{
		pitch = pitch + 0.001f;
		RotateCameraAboutX();
	}

	if( keystate[SDLK_RIGHT] )
	{
		yaw = yaw - 0.001f;
		RotateCameraAboutY();
	}

	if( keystate[SDLK_LEFT] )
	{
		yaw = yaw + 0.001f;
		RotateCameraAboutY();
	}

	if( keystate[SDLK_RSHIFT] )
	{
		spin = spin - 0.001f;
		RotateCameraAboutZ();
	}

	if( keystate[SDLK_RCTRL] )
	{
		spin = spin + 0.001f;
		RotateCameraAboutZ();
	}

	if (keystate[SDLK_w])
		cameraPos.y -= 0.01;

	if (keystate[SDLK_s])
		cameraPos.y += 0.01;

	if (keystate[SDLK_d])
		cameraPos.x += 0.01;

	if (keystate[SDLK_a])
		cameraPos.x -= 0.01;

	if (keystate[SDLK_e])
		cameraPos.z += 0.01;

	if (keystate[SDLK_q])
		cameraPos.z -= 0.01;

	if (keystate[SDLK_SPACE])
	{
		yaw = pitch = spin = 0.0f;
		RotateCameraAboutX();
		RotateCameraAboutY();
		RotateCameraAboutZ();
		cameraPos = vec3( 0, 0, -3.001 );

	}

}

void Draw()
{
	SDL_FillRect( screen, 0, 0 );

	if( SDL_MUSTLOCK(screen) )
		SDL_LockSurface(screen);

	for( int i=0; i<triangles.size(); ++i )
	{
		vector<vec3> vertices(3);

		vertices[0] = triangles[i].v0;
		vertices[1] = triangles[i].v1;
		vertices[2] = triangles[i].v2;

		currentColor = triangles[i].color;
		// Add drawing
		// for(int v=0; v<3; ++v)
		// {
		// 	ivec2 projPos;
		// 	VertexShader( vertices[v], projPos );
		// 	vec3 color(1,1,1);
		// 	PutPixelSDL( screen, projPos.x, projPos.y, color );
		// }
		DrawPolygon(vertices );
	}

	if ( SDL_MUSTLOCK(screen) )
		SDL_UnlockSurface(screen);

	SDL_UpdateRect( screen, 0, 0, 0, 0 );
}

void VertexShader( const vec3& v, ivec2& p )
{
	vec3 pos = (v - cameraPos) * RX * RY * RZ;
 	p.x = (focalLength * (pos.x / pos.z)) + SCREEN_WIDTH / 2;
	p.y = (focalLength * (pos.y / pos.z)) + SCREEN_HEIGHT / 2;
}


void Interpolate( ivec2 a, ivec2 b, vector<ivec2>& result )
{
	int N = result.size();
	vec2 step = vec2(b-a) / float(max(N-1,1));
	vec2 current( a );
	for( int i=0; i<N; ++i )
	{
		result[i] = current;
		current += step;
	}
}

void DrawLineSDL(SDL_Surface* surface, ivec2 a, ivec2 b, vec3 color)
{
	ivec2 delta = glm::abs( a - b );
	int pixels = glm::max( delta.x, delta.y ) + 1;

	vector<ivec2> line( pixels );
	Interpolate( a, b, line );

	for (int i = 0; i < line.size(); i++) {
		PutPixelSDL(screen, line[i].x, line[i].y, color);
	}
}

void DrawPolygonEdges( const vector<vec3>& vertices )
{
	int V = vertices.size();
	// Transform each vertex from 3D world position to 2D image position:
	vector<ivec2> projectedVertices( V );
	for( int i=0; i<V; ++i )
	{
		VertexShader( vertices[i], projectedVertices[i] );
	}
	// Loop over all vertices and draw the edge from it to the next vertex:
	for( int i=0; i<V; ++i )
	{
		int j = (i+1)%V; // The next vertex
		vec3 color( 1, 1, 1 );
		DrawLineSDL( screen, projectedVertices[i], projectedVertices[j], color );
	}
}

void RotateCameraAboutX(){
	vec3 row1(1, 0, 0);
	vec3 row2(0, cos(pitch), -sin(pitch));
	vec3 row3(0, sin(pitch), cos(pitch));
	RX = mat3(row1, row2, row3);
}

void RotateCameraAboutY(){
	vec3 row1(cos(yaw), 0, sin(yaw));
	vec3 row2(0, 1, 0);
	vec3 row3(-sin(yaw), 0, cos(yaw));
	RY = mat3(row1, row2, row3);
}

void RotateCameraAboutZ(){
	vec3 row1(cos(spin), -sin(spin), 0);
	vec3 row2(sin(spin), cos(spin), 0);
	vec3 row3(0, 0, 1);
	RY = mat3(row1, row2, row3);
}

void ComputePolygonRows(const vector<ivec2>& vertexPixels, vector<ivec2>& leftPixels,
vector<ivec2>& rightPixels )
{
	// 1. Find max and min y-value of the polygon
	// and compute the number of rows it occupies.
	int maxY = vertexPixels[0].y;
	int minY = vertexPixels[0].y;

	for (int i=0; i<vertexPixels.size(); ++i)
	{
		maxY = glm::max(vertexPixels[i].y, maxY);
		minY = glm::min(vertexPixels[i].y, minY);
	}

	int numberOfRows = maxY - minY + 1;

	// 2. Resize leftPixels and rightPixels
	// so that they have an element for each row.
	leftPixels.resize(numberOfRows);
	rightPixels.resize(numberOfRows);

	// 3. Initialize the x-coordinates in leftPixels
	// to some really large value and the x-coordinates
	// in rightPixels to some really small value.
	for (int i = 0; i < numberOfRows; ++i)
	{
		leftPixels[i].x = +numeric_limits<int>::max();
		rightPixels[i].x = -numeric_limits<int>::max();

		leftPixels[i].y = i + minY;
		rightPixels[i].y = i + minY;
	}

	// 4. Loop through all edges of the polygon and use
	// linear interpolation to find the x-coordinate for
	// each row it occupies. Update the corresponding
	// values in rightPixels and leftPixels.
	int V = vertexPixels.size();
	for (int i = 0; i<V; ++i)
	{
		ivec2 firstV = vertexPixels[i];
		ivec2 nextV = vertexPixels[(i+1)%V];

		int pixels = glm::abs(firstV.y - nextV.y) + 1;
		vector<ivec2> line(pixels);
		Interpolate(firstV, nextV, line);

		for (int j = 0; j<line.size(); ++j )
		{
			ivec2 p = line[j];
			int rowIndex = p.y - minY;

			if (p.x < leftPixels[rowIndex].x)
			{
				leftPixels[rowIndex].x = p.x;
			}
			if (p.x >= rightPixels[rowIndex].x)
			{
				rightPixels[rowIndex].x = p.x;
			}
		}

	}
}

void DrawPolygonRows(vector<ivec2>leftPixels, vector<ivec2>rightPixels)
{
	for (int i = 0; i < leftPixels.size(); i++)
	{
		DrawLineSDL(screen, leftPixels[i], rightPixels[i], currentColor);
	}
}

void DrawPolygon( const vector<vec3>& vertices )
{
	int V = vertices.size();
	vector<ivec2> vertexPixels( V );

	for( int i=0; i<V; ++i )
	{
		VertexShader( vertices[i], vertexPixels[i] );
	}

	vector<ivec2> leftPixels;
	vector<ivec2> rightPixels;
	ComputePolygonRows( vertexPixels, leftPixels, rightPixels );
	DrawPolygonRows( leftPixels, rightPixels );
}
