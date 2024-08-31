#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <GL/Vector_Matrix.h>


using namespace std;

typedef struct
{
	float xyzw[4];
	float rgba[4];
	float normal[4];
} Vertex;
//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
	// Mảng dữ liệu
Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 0, 1, 0 } },
	{ { -0.5f,	 0.5f,	0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 1.0f, 1.0f },{ 0, 0, 1, 0 } },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },
	{ {  0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
	{ { 0.5f,	-0.5f,   0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
	{ { 0.5f,	-0.5f,  -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
	{ { 0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
	{ { 0.5f,	 0.5f,   0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },

	// v0-v5-v6 (top)
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
	{ {  0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
	// v6-v1-v0
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
	{ { -0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },

	// v1-v6-v7 (left)
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
	// v7-v2-v1
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	 -0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
	// v3-v2-v7
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },

	// v4-v7-v6 (back)
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	{ {  0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	// Vertex[36]

			//Màu sàn nhà
			// Mặt dưới (sàn nhà)
		{ { -0.5f, -0.5f,  0.5f, 1.0 },{ 0.8f, 0.8f, 0.8f, 1.0f },{ 0, 0, 1, 0 } },
		{ {  0.5f, -0.5f,  0.5f, 1.0 },{ 0.8f, 0.8f, 0.8f, 1.0f },{ 0, 0, 1, 0 } },
		{ {  0.5f, -0.5f, -0.5f, 1.0 },{ 0.8f, 0.8f, 0.8f, 1.0f },{ 0, 0, 1, 0 } },

		{ {  0.5f, -0.5f, -0.5f, 1.0 },{ 0.8f, 0.8f, 0.8f, 1.0f },{ 0, 0, 1, 0 } },
		{ { -0.5f, -0.5f, -0.5f, 1.0 },{ 0.8f, 0.8f, 0.8f, 1.0f },{ 0, 0, 1, 0 } },
		{ { -0.5f, -0.5f,  0.5f, 1.0 },{ 0.8f, 0.8f, 0.8f, 1.0f },{ 0, 0, 1, 0 } },

		// Mặt trên
		{ { -0.5f,  0.5f,  0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 0, 1, 0, 0 } },
		{ {  0.5f,  0.5f,  0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 0, 1, 0, 0 } },
		{ {  0.5f,  0.5f, -0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 0, 1, 0, 0 } },

		{ {  0.5f,  0.5f, -0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 0, 1, 0, 0 } },
		{ { -0.5f,  0.5f, -0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 0, 1, 0, 0 } },
		{ { -0.5f,  0.5f,  0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 0, 1, 0, 0 } },

		// Mặt bên phải
		{ { 0.5f,  0.5f,  0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 1, 0, 0, 0 } },
		{ { 0.5f, -0.5f,  0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 1, 0, 0, 0 } },
		{ { 0.5f, -0.5f, -0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 1, 0, 0, 0 } },

		{ { 0.5f, -0.5f, -0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 1, 0, 0, 0 } },
		{ { 0.5f,  0.5f, -0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 1, 0, 0, 0 } },
		{ { 0.5f,  0.5f,  0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 1, 0, 0, 0 } },

		// Mặt bên trái
		{ { -0.5f,  0.5f,  0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ -1, 0, 0, 0 } },
		{ { -0.5f,  0.5f, -0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ -1, 0, 0, 0 } },
		{ { -0.5f, -0.5f, -0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ -1, 0, 0, 0 } },

		{ { -0.5f, -0.5f, -0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ -1, 0, 0, 0 } },
		{ { -0.5f, -0.5f,  0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ -1, 0, 0, 0 } },
		{ { -0.5f,  0.5f,  0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ -1, 0, 0, 0 } },

		// Mặt bên sau
		{ { -0.5f,  0.5f, -0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 0, 0, -1, 0 } },
		{ {  0.5f,  0.5f, -0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 0, 0, -1, 0 } },
		{ {  0.5f, -0.5f, -0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 0, 0, -1, 0 } },

		{ {  0.5f, -0.5f, -0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 0, 0, -1, 0 } },
		{ { -0.5f, -0.5f, -0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 0, 0, -1, 0 } },
		{ { -0.5f,  0.5f, -0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 0, 0, -1, 0 } },

		// Mặt bên trước
		{ { -0.5f, -0.5f,  0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 0, 0, 1, 0 } },
		{ {  0.5f, -0.5f,  0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 0, 0, 1, 0 } },
		{ {  0.5f,  0.5f,  0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 0, 0, 1, 0 } },

		{ {  0.5f,  0.5f,  0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 0, 0, 1, 0 } },
		{ { -0.5f,  0.5f,  0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 0, 0, 1, 0 } },
		{ { -0.5f, -0.5f,  0.5f, 1.0 },{ 0.6f, 0.3f, 0.1f, 1.0f },{ 0, 0, 1, 0 } },
		//Vertex[72]

			// Màu cánh cửa
			// v0-v1-v2 (front)
			{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 0.65f, 0.50f, 0.39f, 1.0f },{ 0, 0, 1, 0 } },
			{ { -0.5f,	 0.5f,	0.5f, 1.0 },{ 0.52f, 0.37f, 0.26f, 1.0f },{ 0, 0, 1, 0 } },
			{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 0.65f, 0.50f, 0.39f, 1.0f },{ 0, 0, 1, 0 } },
			// v2-v3-v0
			{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 0.52f, 0.37f, 0.26f, 1.0f },{ 0, 0, 1, 0 } },
			{ {  0.5f,	-0.5f,	0.5f, 1.0 },{ 0.65f, 0.50f, 0.39f, 1.0f },{ 0, 0, 1, 0 } },
			{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 0.52f, 0.37f, 0.26f, 1.0f },{ 0, 0, 1, 0 } },

			// v0-v3-v4 (right)
			{ { 0.5f,	 0.5f,	 0.5f, 1.0 },{ 0.65f, 0.50f, 0.39f, 1.0f },{ 1, 0, 0, 0 } },
			{ { 0.5f,	-0.5f,   0.5f, 1.0 },{ 0.52f, 0.37f, 0.26f, 1.0f },{ 1, 0, 0, 0 } },
			{ { 0.5f,	-0.5f,  -0.5f, 1.0 },{ 0.65f, 0.50f, 0.39f, 1.0f },{ 1, 0, 0, 0 } },
			// v4-v5-v0
			{ { 0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.52f, 0.37f, 0.26f, 1.0f },{ 1, 0, 0, 0 } },
			{ { 0.5f,	 0.5f,	-0.5f, 1.0 },{ 0.65f, 0.50f, 0.39f, 1.0f },{ 1, 0, 0, 0 } },
			{ { 0.5f,	 0.5f,   0.5f, 1.0 },{ 0.52f, 0.37f, 0.26f, 1.0f },{ 1, 0, 0, 0 } },

			// v0-v5-v6 (top)
			{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 0.65f, 0.50f, 0.39f, 1.0f },{ 0, 1, 0, 0 } },
			{ {  0.5f,	0.5f,	-0.5f, 1.0 },{ 0.52f, 0.37f, 0.26f, 1.0f },{ 0, 1, 0, 0 } },
			{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 0.65f, 0.50f, 0.39f, 1.0f },{ 0, 1, 0, 0 } },
			// v6-v1-v0
			{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 0.52f, 0.37f, 0.26f, 1.0f },{ 0, 1, 0, 0 } },
			{ { -0.5f,	0.5f,	 0.5f, 1.0 },{ 0.65f, 0.50f, 0.39f, 1.0f },{ 0, 1, 0, 0 } },
			{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 0.52f, 0.37f, 0.26f, 1.0f },{ 0, 1, 0, 0 } },

			// v1-v6-v7 (left)
			{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 0.65f, 0.50f, 0.39f, 1.0f },{ -1, 0, 0, 0 } },
			{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0.52f, 0.37f, 0.26f, 1.0f },{ -1, 0, 0, 0 } },
			{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.65f, 0.50f, 0.39f, 1.0f },{ -1, 0, 0, 0 } },
			// v7-v2-v1
			{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.52f, 0.37f, 0.26f, 1.0f },{ -1, 0, 0, 0 } },
			{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 0.65f, 0.50f, 0.39f, 1.0f },{ -1, 0, 0, 0 } },
			{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 0.52f, 0.37f, 0.26f, 1.0f },{ -1, 0, 0, 0 } },

			// v7-v4-v3 (bottom)
			{ { -0.5f,	 -0.5f,	-0.5f, 1.0 },{ 0.65f, 0.50f, 0.39f, 1.0f },{ 0,-1, 0, 0 } },
			{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.52f, 0.37f, 0.26f, 1.0f },{ 0,-1, 0, 0 } },
			{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 0.65f, 0.50f, 0.39f, 1.0f },{ 0,-1, 0, 0 } },
			// v3-v2-v7
			{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 0.52f, 0.37f, 0.26f, 1.0f },{ 0,-1, 0, 0 } },
			{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 0.65f, 0.50f, 0.39f, 1.0f },{ 0,-1, 0, 0 } },
			{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.52f, 0.37f, 0.26f, 1.0f },{ 0,-1, 0, 0 } },

			// v4-v7-v6 (back)
			{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.65f, 0.50f, 0.39f, 1.0f },{ 0, 0,-1, 0 } },
			{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.52f, 0.37f, 0.26f, 1.0f },{ 0, 0,-1, 0 } },
			{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0.65f, 0.50f, 0.39f, 1.0f },{ 0, 0,-1, 0 } },
			// v6-v5-v4
			{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0.52f, 0.37f, 0.26f, 1.0f },{ 0, 0,-1, 0 } },
			{ {  0.5f,	 0.5f,	-0.5f, 1.0 },{ 0.65f, 0.50f, 0.39f, 1.0f },{ 0, 0,-1, 0 } },
			{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.52f, 0.37f, 0.26f, 1.0f },{ 0, 0,-1, 0 } },
			//Vertex[108]

					// Đổi màu tường 
				{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 0, 1, 0 } },
				{ { -0.5f,	 0.5f,	0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 0, 1, 0 } },
				{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 0, 1, 0 } },
				// v2-v3-v0
				{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 0, 1, 0 } },
				{ {  0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 0, 1, 0 } },
				{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 0, 1, 0 } },

				// v0-v3-v4 (right)
				{ { 0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 1, 0, 0, 0 } },
				{ { 0.5f,	-0.5f,   0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 1, 0, 0, 0 } },
				{ { 0.5f,	-0.5f,  -0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 1, 0, 0, 0 } },
				// v4-v5-v0
				{ { 0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 1, 0, 0, 0 } },
				{ { 0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 1, 0, 0, 0 } },
				{ { 0.5f,	 0.5f,   0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 1, 0, 0, 0 } },

				// v0-v5-v6 (top)
				{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 1, 0, 0 } },
				{ {  0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 1, 0, 0 } },
				{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 1, 0, 0 } },
				// v6-v1-v0
				{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 1, 0, 0 } },
				{ { -0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 1, 0, 0 } },
				{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 1, 0, 0 } },

				// v1-v6-v7 (left)
				{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ -1, 0, 0, 0 } },
				{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ -1, 0, 0, 0 } },
				{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ -1, 0, 0, 0 } },
				// v7-v2-v1
				{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ -1, 0, 0, 0 } },
				{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ -1, 0, 0, 0 } },
				{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ -1, 0, 0, 0 } },

				// v7-v4-v3 (bottom)
				{ { -0.5f,	 -0.5f,	-0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, -1, 0, 0 } },
				{ {  0.5f,	 -0.5f,	-0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, -1, 0, 0 } },
				{ {  0.5f,	 -0.5f,	 0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, -1, 0, 0 } },
				// v3-v2-v7
				{ {  0.5f,	 -0.5f,	 0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, -1, 0, 0 } },
				{ { -0.5f,	 -0.5f,	 0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, -1, 0, 0 } },
				{ { -0.5f,	 -0.5f,	-0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, -1, 0, 0 } },

				// v4-v7-v6 (back)
				{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 0,-1, 0 } },
				{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.52f, 1.0f, 1.0f, 1.0f },{ 0, 0,-1, 0 } },
				{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.65f, 1.0f, 1.0f, 1.0f },{ 0, 0,-1, 0 } },
				// v6-v5-v4
				{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.52f, 1.0f, 1.0f, 1.0f },{ 0, 0,-1, 0 } },
				{ {  0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.65f, 1.0f, 1.0f, 1.0f },{ 0, 0,-1, 0 } },
				{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.52f, 1.0f, 1.0f, 1.0f },{ 0, 0,-1, 0 } },
				//Vertex[144]

					// Mặt trước của tường
					{ { -0.5f,  0.5f,  0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, 0, 1, 0 } },
					{ {  0.5f,  0.5f,  0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, 0, 1, 0 } },
					{ {  0.5f, -0.5f,  0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, 0, 1, 0 } },

					{ {  0.5f, -0.5f,  0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, 0, 1, 0 } },
					{ { -0.5f, -0.5f,  0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, 0, 1, 0 } },
					{ { -0.5f,  0.5f,  0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, 0, 1, 0 } },

					// Mặt sau của tường
				{ { -0.5f,  0.5f, -0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, 0, -1, 0 } },
				{ {  0.5f,  0.5f, -0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, 0, -1, 0 } },
				{ {  0.5f, -0.5f, -0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, 0, -1, 0 } },

				{ {  0.5f, -0.5f, -0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, 0, -1, 0 } },
				{ { -0.5f, -0.5f, -0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, 0, -1, 0 } },
				{ { -0.5f,  0.5f, -0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, 0, -1, 0 } },

				// Mặt bên trái của tường
				{ { -0.5f,  0.5f,  0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ -1, 0, 0, 0 } },
				{ { -0.5f,  0.5f, -0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ -1, 0, 0, 0 } },
				{ { -0.5f, -0.5f, -0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ -1, 0, 0, 0 } },

				{ { -0.5f, -0.5f, -0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ -1, 0, 0, 0 } },
				{ { -0.5f, -0.5f,  0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ -1, 0, 0, 0 } },
				{ { -0.5f,  0.5f,  0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ -1, 0, 0, 0 } },

				// Mặt bên phải của tường
				{ {  0.5f,  0.5f,  0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 1, 0, 0, 0 } },
				{ {  0.5f,  0.5f, -0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 1, 0, 0, 0 } },
				{ {  0.5f, -0.5f, -0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 1, 0, 0, 0 } },

				{ {  0.5f, -0.5f, -0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 1, 0, 0, 0 } },
				{ {  0.5f, -0.5f,  0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 1, 0, 0, 0 } },
				{ {  0.5f,  0.5f,  0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 1, 0, 0, 0 } },

				// Mặt trên của tường
				{ { -0.5f,  0.5f,  0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, 1, 0, 0 } },
				{ {  0.5f,  0.5f,  0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, 1, 0, 0 } },
				{ {  0.5f,  0.5f, -0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, 1, 0, 0 } },

				{ {  0.5f,  0.5f, -0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, 1, 0, 0 } },
				{ { -0.5f,  0.5f, -0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, 1, 0, 0 } },
				{ { -0.5f,  0.5f,  0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, 1, 0, 0 } },

				// Mặt dưới của tường
				{ { -0.5f, -0.5f,  0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, -1, 0, 0 } },
				{ {  0.5f, -0.5f,  0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, -1, 0, 0 } },
				{ {  0.5f, -0.5f, -0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, -1, 0, 0 } },

				{ {  0.5f, -0.5f, -0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, -1, 0, 0 } },
				{ { -0.5f, -0.5f, -0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, -1, 0, 0 } },
				{ { -0.5f, -0.5f,  0.05f, 1.0 },{ 0.9f, 0.6f, 0.4f, 0.5f },{ 0, -1, 0, 0 } },
				//Vertex[180]

					//Quat tran mau xa lanh

					{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },
					{ { -0.5f,	 0.5f,	0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },
					{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },
					// v2-v3-v0
					{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },
					{ {  0.5f,	-0.5f,	0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },
					{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },

					// v0-v3-v4 (right)
					{ { 0.5f,	 0.5f,	 0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
					{ { 0.5f,	-0.5f,   0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
					{ { 0.5f,	-0.5f,  -0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
					// v4-v5-v0
					{ { 0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
					{ { 0.5f,	 0.5f,	-0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
					{ { 0.5f,	 0.5f,   0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },

					// v0-v5-v6 (top)
					{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
					{ {  0.5f,	0.5f,	-0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
					{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
					// v6-v1-v0
					{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
					{ { -0.5f,	0.5f,	 0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
					{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },

					// v1-v6-v7 (left)
					{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
					{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
					{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
					// v7-v2-v1
					{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
					{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
					{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },

					// v7-v4-v3 (bottom)
					{ { -0.5f,	 -0.5f,	-0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
					{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
					{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
					// v3-v2-v7
					{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
					{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
					{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },

					// v4-v7-v6 (back)
					{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
					{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
					{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
					// v6-v5-v4
					{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
					{ {  0.5f,	 0.5f,	-0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
					{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
					//Vertex[216]

						//Tu ke Televison
						// v0-v1-v2 (front)
						{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 0, 1, 0 } },
						{ { -0.5f,	 0.5f,	0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },
						{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 1.0f, 1.0f },{ 0, 0, 1, 0 } },
						// v2-v3-v0
						{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },
						{ {  0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },
						{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },

						// v0-v3-v4 (right)
						{ { 0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
						{ { 0.5f,	-0.5f,   0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
						{ { 0.5f,	-0.5f,  -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
						// v4-v5-v0
						{ { 0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
						{ { 0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
						{ { 0.5f,	 0.5f,   0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },

						// v0-v5-v6 (top)
						{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
						{ {  0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
						{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
						// v6-v1-v0
						{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
						{ { -0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
						{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },

						// v1-v6-v7 (left)
						{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
						{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
						{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
						// v7-v2-v1
						{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
						{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
						{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },

						// v7-v4-v3 (bottom)
						{ { -0.5f,	 -0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
						{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
						{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
						// v3-v2-v7
						{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
						{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
						{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },

						// v4-v7-v6 (back)
						{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
						{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
						{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
						// v6-v5-v4
						{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
						{ {  0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
						{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
						// Vertex[252]

};
// ----------------------------------------

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].xyzw);
const size_t NormalOffset = sizeof(Vertices[0].xyzw) + sizeof(Vertices[1].rgba);

int CurrentWidth = 700,
CurrentHeight = 700;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

mat4
model_mat_cpp,
view_mat_cpp,
projection_mat_cpp;

int
model_mat_location,
view_mat_location,
projection_mat_location;

float
r[] = { 0.0f, 0.0f, 0.0f },
s[] = { 1.0f, 1.0f, 1.0f },
t[] = { 0.0f, 0.0f, 0.0f };

class MatrixStack {
	int    index;
	int    size;
	mat4* matrices;

public:
	MatrixStack(int numMatrices = 32) :index(0), size(numMatrices)
	{
		matrices = new mat4[numMatrices];
	}

	~MatrixStack()
	{
		delete[]matrices;
	}

	// phép toán đẩy vào
	mat4& push(const mat4& m) {
		assert(index + 1 < size);
		matrices[index++] = m;
		return matrices[index];
	}

	// phép toán lấy ra
	mat4& pop(void) {
		assert(index - 1 >= 0);
		index--;
		return matrices[index];
	}
};

MatrixStack  mvstack;

float alphat = 0.0f;

float alphap = 0.0f;

float alphaQuat = 0.0f;

float tTu1 = 0.0f, tTu2 = 0.0f, tTu3 = 0.0f;
bool
translated = false,
rotated = false,
scaled = false;

bool light1Enabled = false;
// ------------------------------------------
void MATSAN()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -3.0f, 0.0f)) * scale(vec3(24.0f, 0.02f, 20.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 36, 72);

	model_mat_cpp = mvstack.pop();
}
void tuongSAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, 1.99f, -10.75f)) * rotate_x(90) * scale(vec3(24.0f, 1.5f, 10.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 108, 144);

	model_mat_cpp = mvstack.pop();
}
void tuongPHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-12.75f, 1.99f, 0.0f)) * rotate_z(90) * scale(vec3(10.0f, 1.5f, 23.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 108, 144);

	model_mat_cpp = mvstack.pop();
}

void tuongTRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(12.75f, 1.99f, 0.0f)) * rotate_z(-90) * scale(vec3(10.0f, 1.5f, 23.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 108, 144);

	model_mat_cpp = mvstack.pop();
}
void tuongTRUOCPHAI() {
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(8.495f, 1.99f, 10.75f)) * scale(vec3(7.0f, 10.0f, 1.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 108, 144);

	model_mat_cpp = mvstack.pop();
}

void tuongTRUOCTRAI() {
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-8.495f, 1.99f, 10.75f)) * scale(vec3(7.0f, 10.0f, 1.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 108, 144);

	model_mat_cpp = mvstack.pop();
}
void canhPHAITRONG()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(3.0f, 8.0f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void canhPHAIMANHTREN()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, 4.5, 0.1)) * scale(vec3(5.0f, 1.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void canhPHAIMANHDUOI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, -4.5, 0.1)) * scale(vec3(5.0f, 1.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void canhPHAIMANHTRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-2.0, 0.0, 0.1)) * scale(vec3(1.0f, 8.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void canhPHAIMANHPHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(2.0, 0.0, 0.1)) * scale(vec3(1.0f, 8.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
//
void canhTRAITRONG()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(3.0f, 8.0f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void canhTRAIMANHTREN()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, 4.5, 0.1)) * scale(vec3(5.0f, 1.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void canhTRAIMANHDUOI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, -4.5, 0.1)) * scale(vec3(5.0f, 1.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void canhTRAIMANHTRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-2.0, 0.0, 0.1)) * scale(vec3(1.0f, 8.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void canhTRAIMANHPHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(2.0, 0.0, 0.1)) * scale(vec3(1.0f, 8.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void matdayNAMCUA()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(2.0, 0.0, 0.35)) * scale(vec3(0.4f, 2.0f, 0.1f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void thanNAMCUA()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(2.0, 0.0, 0.85)) * scale(vec3(0.4f, 0.4f, 1.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void tayNAMCUA()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(1.5, 0.0, 1.325)) * scale(vec3(1.0f, 0.4f, 0.05f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void matBAN()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, -0.89, 0.0)) * scale(vec3(3.0f, 0.2f, 6.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void chanTRAITRUOC()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(1.3, -1.99, 2.8)) * scale(vec3(0.4f, 2.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void chanTRAISAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-1.3, -1.99, 2.8)) * scale(vec3(0.4f, 2.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void chanPHAITRUOC()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(1.3, -1.99, -2.8)) * scale(vec3(0.4f, 2.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}

void chanPHAISAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-1.3, -1.99, -2.8)) * scale(vec3(0.4f, 2.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}

void TIVI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.9, 3.0, 0.0)) * scale(vec3(0.04f, 2.5f, 5.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}

void TRANH1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-11.98, 3.2, 0.0)) * scale(vec3(0.04f, 1.0f, 2.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}

void TRANH2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-11.98, 1.7, -1.5)) * scale(vec3(0.04f, 1.0f, 2.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}

void TRANH3()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-11.98, 1.7, 1.5)) * scale(vec3(0.04f, 1.0f, 2.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}

void matNGOI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-9.7, -1.99, 0.0)) * scale(vec3(3.0f, 2.0f, 6.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}

void duiQUAT()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(1.2f, 0.5f, 1.2f)) * translate(vec3(0.0, 13.9, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 180, 216);

	model_mat_cpp = mvstack.pop();
}

void trucQUAT()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(0.2f, 2.0f, 0.2f)) * translate(vec3(0.0, 3.0, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 180, 216);

	model_mat_cpp = mvstack.pop();
}

void tamQUAT()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(0.9f, 0.2f, 0.9f)) * translate(vec3(0.0, 24.5, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 180, 216);

	model_mat_cpp = mvstack.pop();
}

void canhQUATTRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(3.5f, 0.15f, 1.1f)) * translate(vec3(0.6, 32.5, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 180, 216);

	model_mat_cpp = mvstack.pop();
}

void canhQUATPHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(3.5f, 0.15f, 1.1f)) * translate(vec3(-0.6, 32.5, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 180, 216);

	model_mat_cpp = mvstack.pop();
}

void canhQUATTRUOC()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(1.1f, 0.15f, 7.5f)) * translate(vec3(0.0, 32.5, 0.0)) * rotate_y(90);

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 180, 216);

	model_mat_cpp = mvstack.pop();
}

void canhQUATSAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(1.1f, 0.15f, 7.5f)) * translate(vec3(0.0, 32.5, 0.0)) * rotate_y(-90);

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 180, 216);

	model_mat_cpp = mvstack.pop();
}

void tuCANHTRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.0, -1.5, 4.5)) * scale(vec3(1.5f, 3.0f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}

void tuCANHPHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.0, -1.5, -4.35)) * scale(vec3(1.5f, 3.0f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void tuCANHTREN()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.0, 0, 0)) * scale(vec3(1.7f, 0.3f, 9.05f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}

void tuCANHSAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.6, -1.15, 0)) * scale(vec3(0.2f, 2.5f, 9.05f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}

void tu1TRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.9, -1.3, 4.35)) * scale(vec3(1.4f, 2.5f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}

void tu1PHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.9, -1.3, 1.65)) * scale(vec3(1.4f, 2.5f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void tu2TRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.9, -1.3, 1.45)) * scale(vec3(1.4f, 2.5f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void tu2PHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.9, -1.3, -1.25)) * scale(vec3(1.4f, 2.5f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void tu3TRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.9, -1.3, -1.45)) * scale(vec3(1.4f, 2.5f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void tu3PHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.9, -1.3, -4.15)) * scale(vec3(1.4f, 2.5f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void tu1DUOI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.8, -2.5, 2.95)) * scale(vec3(1.4f, 0.2f, 2.9f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void tu2DUOI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.8, -2.5, 0.05)) * scale(vec3(1.4f, 0.2f, 2.9f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void tu3DUOI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.8, -2.5, -2.85)) * scale(vec3(1.4f, 0.2f, 2.9f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
void tu1TRUOC()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.1, -1.2, 3.0)) * scale(vec3(0.2f, 2.4f, 2.8f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}

void tu2TRUOC()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.1, -1.2, 0.1)) * scale(vec3(0.2f, 2.4f, 2.8f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}

void tu3TRUOC()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.1, -1.2, -2.8)) * scale(vec3(0.2f, 2.4f, 2.8f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}

void tu1SAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.6, -1.6, 3.0)) * scale(vec3(0.2f, 2.4f, 2.8f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}

void tu2SAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.6, -1.6, 0.1)) * scale(vec3(0.2f, 2.4f, 2.8f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}

void tu3SAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.6, -1.6, -2.8)) * scale(vec3(0.2f, 2.4f, 2.8f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}


void tu1TAYNAM()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(9.95, -0.9, 3.0)) * scale(vec3(0.2f, 0.3f, 0.6f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}


void tu2TAYNAM()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(9.95, -0.9, 0.0)) * scale(vec3(0.2f, 0.3f, 0.6f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}


void tu3TAYNAM()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(9.95, -0.9, -3.0)) * scale(vec3(0.2f, 0.3f, 0.6f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 72, 108);

	model_mat_cpp = mvstack.pop();
}
// ------------------------------------------
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}

// ------------------------------------------
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);	// position
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset); //color
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)NormalOffset); //normal

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}
// ------------------------------------------
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
}
// ------------------------------------------
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}
// ------------------------------------------

void DisplayFunc(void)
{
	model_mat_cpp = identity_mat4();
	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	if (translated)
	{
		model_mat_cpp = model_mat_cpp * translate(vec3(t[0], t[1], t[2]));
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}
	if (rotated)
	{
		model_mat_cpp = model_mat_cpp * rotate_x(r[0])
			* rotate_y(r[1])
			* rotate_z(r[2]);
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}
	if (scaled)
	{
		model_mat_cpp = model_mat_cpp * scale(vec3(s[0], s[1], s[2]));
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}

	vec3	eye(0.0f, 8.0f, 30.0f),
		at(0.0f, 0.0f, 0.0f),
		up(0.0f, 1.0f, 0.0f);

	view_mat_cpp = lookat(eye, at, up);
	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);

	float
		znear = 0.1f,
		zfar = 100.0f,
		fov = 90.0f,
		aspect = (float)CurrentWidth / CurrentHeight;
	projection_mat_cpp = perspective(fov, aspect, znear, zfar);
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection_mat_cpp.m);
	GLint light1Loc = glGetUniformLocation(ProgramId, "light1_enabled");
	glUniform1i(light1Loc, light1Enabled);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	MATSAN();

	mvstack.push(model_mat_cpp);
	tuongSAU();
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	tuongPHAI();
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	tuongTRAI();
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	tuongTRUOCPHAI();
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	tuongTRUOCTRAI();
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0f, 1.99f, 11.15f)) * translate(vec3(5.0f, 0.0, 0.0)) * rotate_y(alphap) * translate(vec3(-2.5, 0.0, 0.0));
	canhPHAITRONG();
	canhPHAIMANHTREN();
	canhPHAIMANHDUOI();
	canhPHAIMANHTRAI();
	canhPHAIMANHPHAI();
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0f, 1.99f, 11.15f)) * translate(vec3(-5.0, 0.0, 0.0)) * rotate_y(alphat) * translate(vec3(2.5, 0.0, 0.0));
	canhTRAITRONG();
	canhTRAIMANHTREN();
	canhTRAIMANHDUOI();
	canhTRAIMANHTRAI();
	canhTRAIMANHPHAI();
	matdayNAMCUA();
	thanNAMCUA();
	tayNAMCUA();
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-4.3, 0, 0));
	matBAN();
	chanTRAITRUOC();
	chanTRAISAU();
	chanPHAITRUOC();
	chanPHAISAU();
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	TIVI();
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	TRANH1();
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	TRANH2();
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	TRANH3();
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	matNGOI();
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-4.5, 0, 0));
	duiQUAT();
	trucQUAT();
	model_mat_cpp = model_mat_cpp * rotate_y(alphaQuat);
	tamQUAT();
	canhQUATTRAI();
	canhQUATPHAI();
	canhQUATTRUOC();
	canhQUATSAU();
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp;
	tuCANHTRAI();
	tuCANHPHAI();
	tuCANHTREN();
	tuCANHSAU();

	// Tu 1
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(tTu1, 0.0, 0.0));
	tu1TRAI();
	tu1PHAI();
	tu1DUOI();
	tu1TRUOC();
	tu1SAU();
	tu1TAYNAM();
	model_mat_cpp = mvstack.pop();
	//Tu 2
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(tTu2, 0.0, 0.0));
	tu2TRAI();
	tu2PHAI();
	tu2DUOI();
	tu2TRUOC();
	tu2SAU();
	tu2TAYNAM();
	model_mat_cpp = mvstack.pop();
	//Tu 3
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(tTu3, 0.0, 0.0));
	tu3TRAI();
	tu3PHAI();
	tu3DUOI();
	tu3TRUOC();
	tu3SAU();
	tu3TAYNAM();
	model_mat_cpp = mvstack.pop();

	model_mat_cpp = mvstack.pop();

	glutSwapBuffers();
}
// ------------------------------------------
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;

	glViewport(0, 0, CurrentWidth, CurrentHeight);
}
// ------------------------------------------
void IdleFunc(void)
{
	glutPostRedisplay();
}

void IdleFunc1(void)
{
	// tính toán góc quay
	alphaQuat += 0.1f;
	if (alphaQuat > 360.0f) {
		alphaQuat -= 360.0f;
	}

	// thiết lập cờ gọi hiển thị lại
	glutPostRedisplay();
}
void IdleFunc2(void)
{
	// tính toán góc quay
	alphaQuat += 0.25f;
	if (alphaQuat > 360.0f) {
		alphaQuat -= 360.0f;
	}

	// thiết lập cờ gọi hiển thị lại
	glutPostRedisplay();
}
void IdleFunc3(void)
{
	// tính toán góc quay
	alphaQuat += 0.35f;
	if (alphaQuat > 360.0f) {
		alphaQuat -= 360.0f;
	}

	// thiết lập cờ gọi hiển thị lại
	glutPostRedisplay();
}
// ------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		glutLeaveMainLoop();
		break;
	case 'x':
		r[0] -= 10.0f;
		rotated = true;
		break;
	case 'X':
		r[0] += 10.0f;
		rotated = true;
		break;

	case 'y':
		r[1] -= 10.0f;
		rotated = true;
		break;
	case 'Y':
		r[1] += 10.0f;
		rotated = true;
		break;

	case 'z':
		r[2] -= 10.0f;
		rotated = true;
		break;
	case 'Z':
		r[2] += 10.0f;
		rotated = true;
		break;

	case '=':
	case '+':
		s[0] *= 1.05f;
		s[1] *= 1.05f;
		s[2] *= 1.05f;
		scaled = true;
		break;

	case '-':
	case '_':
		s[0] /= 1.05f;
		s[1] /= 1.05f;
		s[2] /= 1.05f;
		scaled = true;
		break;

	case 'j':
		t[0] -= 0.05f;
		translated = true;
		break;
	case 'l':
		t[0] += 0.05f;
		translated = true;
		break;
	case 'i':
		t[1] += 0.05f;
		translated = true;
		break;
	case ',':
		t[1] -= 0.05f;
		translated = true;
		break;
	case 'g':
		t[2] -= 0.05f;
		translated = true;
		break;
	case 'h':
		t[2] += 0.05f;
		translated = true;
		break;
	case 'm':
		alphat = -90.0f;
		alphap = 90.0f;
		break;
	case 'd':
		alphat = 0.0f;
		alphap = 0.0f;
		break;
	case '1': // Bật tắt đèn
		light1Enabled = !light1Enabled;
		glutPostRedisplay();
		break;
	case '2':
		glutIdleFunc(IdleFunc1);
		break;
	case '3':
		glutIdleFunc(IdleFunc2);
		break;
	case '4':
		glutIdleFunc(IdleFunc3);
		break;
	case '5':
		glutIdleFunc(IdleFunc);
		break;
	case 'a':
		tTu1 = -1.2;
		break;
	case 'A':
		tTu1 = 0.0;
		break;
	case 'b':
		tTu2 = -1.2;
		break;
	case 'B':
		tTu2 = 0.0;
		break;
	case 'c':
		tTu3 = -1.2;
		break;
	case 'C':
		tTu3 = 0.0;
		break;
	}
}
// ----------------------------------------

	// Xử lý phím đặc biệt
void SpecialFunc(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_LEFT:
		t[0] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_RIGHT:
		t[0] += 0.05f;
		translated = true;
		break;
	case GLUT_KEY_UP:
		t[1] += 0.05f;
		translated = true;
		break;
	case GLUT_KEY_DOWN:
		t[1] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_ALT_R:
		t[2] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_CTRL_R:
		t[2] += 0.05f;
		translated = true;
		break;

	}
}
// ------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("A Modern Living Room");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);
	glutCloseFunc(CloseFunc);

	glutMainLoop();
	return 0;
}
