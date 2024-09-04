﻿#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <GL/vector_matrix.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

typedef struct
{
	float xyzw[4];
	float rgba[4];
	float normal[4];
	float texcoord[2];
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
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 0, 1, 0 },{ 1.0f, 1.0f } },
	{ { -0.5f,	 0.5f,	0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 0.0f, 1.0f } },
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 1.0f, 1.0f },{ 0, 0, 1, 0 },{ 0.0f, 0.0f } },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 0.0f, 0.0f } },
	{ {  0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 1.0f, 0.0f } },
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 1.0f, 1.0f } },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 1.0f, 1.0f } },
	{ { 0.5f,	-0.5f,   0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 1.0f, 0.0f } },
	{ { 0.5f,	-0.5f,  -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 0.0f, 0.0f } },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 0.0f, 0.0f } },
	{ { 0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 0.0f, 1.0f } },
	{ { 0.5f,	 0.5f,   0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 1.0f, 1.0f } },

	// v0-v5-v6 (top)
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 1.0f, 1.0f } },
	{ {  0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 1.0f, 0.0f } },
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 0.0f, 0.0f } },
	// v6-v1-v0
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 0.0f, 0.0f } },
	{ { -0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 0.0f, 1.0f } },
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 1.0f, 1.0f } },

	// v1-v6-v7 (left)
   { { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 0.0f, 1.0f } },
   { { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 1.0f, 1.0f } },
   { { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 1.0f, 0.0f } },
   // v7-v2-v1
   { { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 1.0f, 0.0f } },
   { { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 0.0f, 0.0f } },
   { { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 0.0f, 1.0f } },


   // v7-v4-v3 (bottom)
   { { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, -1, 0, 0 },{ 0.0f, 0.0f } },
   { { 0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, -1, 0, 0 },{ 1.0f, 0.0f } },
   { { 0.5f,	-0.5f,   0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, -1, 0, 0 },{ 1.0f, 1.0f } },
   // v3-v2-v7
   { { 0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, -1, 0, 0 },{ 1.0f, 1.0f } },
   { { -0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, -1, 0, 0 },{ 0.0f, 1.0f } },
   { { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, -1, 0, 0 },{ 0.0f, 0.0f } },

   // v4-v7-v6 (back)
   { {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, -1, 0, 0 },{ 1.0f, 0.0f } },
   { { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, -1, 0, 0 },{ 0.0f, 0.0f } },
   { { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, -1, 0, 0 },{ 0.0f, 1.0f } },
   // v6-v5-v4
   { { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, -1, 0, 0 },{ 0.0f, 1.0f } },
   { {  0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, -1, 0, 0 },{ 1.0f, 1.0f } },
   { {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, -1, 0, 0 },{ 1.0f, 0.0f } }


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


bool
translated = false,
rotated = false,
scaled = false;

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

float alphasop = 0.0f;

float alphasot = 0.0f;

float ktb = 0.0f;

float cameraSpeed = 0.2f;

vec3	eye(0.0f, 5.0f, 30.0f),
at(0.0f, 0.0f, 0.0f),
up(0.0f, 1.0f, 0.0f);

bool light1Enabled = false;

int tivichanels = 0;
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
GLuint
TextureId0,// sàn gỗ
TextureId1,// tường sơn trắng
TextureId2,// mặt kính
TextureId3,// vân gỗ sồi
TextureId4,// kim loại sắt ánh kim
TextureId5,// nhựa đen ti vi
TextureId6,// quạt
TextureId7,//kệnh ti vi 1
TextureId8,//Kênh ti vi 2
TextureId9,//no signal
TextureId10,//viền gỗ khung tranh
TextureId11,//tranh to
TextureId12,//tranh bé
TextureId13;

GLuint LoadTexture(const char* filename)
{
	GLuint textureID;
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data);
	return textureID;
}
void InitTextures()
{
	TextureId0 = LoadTexture("textures/sango.jpg");
	TextureId1 = LoadTexture("textures/tuongsontrang.png");
	TextureId2 = LoadTexture("textures/matkinh.jpg");
	TextureId3 = LoadTexture("textures/vangocua.jpg");
	TextureId4 = LoadTexture("textures/kimloai.jpg");
	TextureId5 = LoadTexture("textures/nhuaden.jpg");
	TextureId6 = LoadTexture("textures/kimloaigreenlight.jpg");
	TextureId7 = LoadTexture("textures/chanel1.jpg");
	TextureId8 = LoadTexture("textures/chanel2.jpg");
	TextureId9 = LoadTexture("textures/nosignal.jpg");
	TextureId10 = LoadTexture("textures/gocongnghiep.jpg");
	TextureId11 = LoadTexture("textures/tranh.jpg");
	TextureId12 = LoadTexture("textures/tranhbe.jpg");
	TextureId13 = LoadTexture("textures/nhuatrang.jpg");
}
// ------------------------------------------
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);    // position
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset); //color
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)NormalOffset); //normal
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)(sizeof(float) * 12)); // texture coords

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
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
void MATSAN()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -3.0f, 0.0f)) * scale(vec3(24.0f, 0.02f, 20.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId0);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
//tường sau
void tuongSAUM1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(5.0f, 0.0f, 0.5f)) * scale(vec3(14.0f, 10.0f, 1.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId1);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void tuongSAUM2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-6.5f, 4.75f, 0.5f)) * scale(vec3(9.0f, 0.5f, 1.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId1);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void tuongSAUM3()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-6.5f, -4.35f, 0.5f)) * scale(vec3(9.0f, 1.3f, 1.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId1);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void tuongSAUM4()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-11.5f, 0.0f, 0.5f)) * scale(vec3(1.0f, 10.0f, 1.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId1);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
// Cửa sổ
void khungSOTRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(4.25f, 0.4f, 0.5f)) * scale(vec3(0.5f, 8.2f, 1.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void khungSOPHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-4.25f, 0.4f, 0.5f)) * scale(vec3(0.5f, 8.2f, 1.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void khungSOTREN1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 4.45f, 0.5f)) * scale(vec3(8.0f, 0.1f, 1.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void khungSOTREN2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 3.5f, 0.5f)) * scale(vec3(8.0f, 0.1f, 1.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void khungSOTRENCHIA()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 3.95f, 0.5f)) * scale(vec3(0.5f, 0.9f, 1.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void khungSODUOI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -3.6f, 0.5f)) * scale(vec3(8.0f, 0.2f, 1.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void matKINHTRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(2.125f, 3.95f, -0.15f)) * scale(vec3(3.75f, 0.9f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId2);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void matKINHPHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-2.125f, 3.95f, -0.15f)) * scale(vec3(3.75f, 0.9f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId2);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
// ------------------------------------------
void chansongCOT1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 0.0f, 0.6f)) * scale(vec3(0.25f, 7.0f, 0.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chansongCOT2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(2.0f, 0.0f, 0.6f)) * scale(vec3(0.25f, 7.0f, 0.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chansongCOT3()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-2.0f, 0.0f, 0.6f)) * scale(vec3(0.25f, 7.0f, 0.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chansongNGANG1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 1.0f, 0.6f)) * scale(vec3(8.0f, 0.25f, 0.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chansongNGANG2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -1.0f, 0.6f)) * scale(vec3(8.0f, 0.25f, 0.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
// ------------------------------------------
void soTRAIGIUA01()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(2.0f, 1.0f, 0.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void mongTRAITRENO1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -0.625f, 0.0f)) * scale(vec3(1.5f, 0.25f, 0.25f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void soTRAIO01()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -1.5f, 0.0f)) * scale(vec3(1.5f, 1.5f, 0.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void mongTRAITRAIO1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.875f, -1.5f, 0.0f)) * scale(vec3(0.25f, 2.0f, 0.25f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void mongTRAIPHAIO1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.875f, -1.5f, 0.0f)) * scale(vec3(0.25f, 2.0f, 0.25f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void mongTRAIDUOIO1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -2.375f, 0.0f)) * scale(vec3(1.5f, 0.25f, 0.25f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void soTRAIDUOI01()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -3.0f, 0.0f)) * scale(vec3(2.0f, 1.0f, 0.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void mongTRAIDUOIO2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 0.625f, 0.0f)) * scale(vec3(1.5f, 0.25f, 0.25f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void soTRAIO02()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 1.5f, 0.0f)) * scale(vec3(1.5f, 1.5f, 0.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void mongTRAITRAIO2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.875f, 1.5f, 0.0f)) * scale(vec3(0.25f, 2.0f, 0.25f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void mongTRAIPHAIO2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.875f, 1.5f, 0.0f)) * scale(vec3(0.25f, 2.0f, 0.25f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void mongTRAITRENO2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 2.375f, 0.0f)) * scale(vec3(1.5f, 0.25f, 0.25f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void soTRAITREN01()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 3.0f, 0.0f)) * scale(vec3(2.0f, 1.0f, 0.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void soTRAITRAI01()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(1.5f, 0.0f, 0.0f)) * scale(vec3(1.0f, 7.0f, 0.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void soTRAIPHAI01()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-1.5f, 0.0f, 0.0f)) * scale(vec3(1.0f, 7.0f, 0.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
//-------------------------------------------
void soPHAIGIUA02()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(2.0f, 1.0f, 0.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void mongPHAITRENO1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -0.625f, 0.0f)) * scale(vec3(1.5f, 0.25f, 0.25f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void soPHAIO01()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -1.5f, 0.0f)) * scale(vec3(1.5f, 1.5f, 0.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void mongPHAITRAIO1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.875f, -1.5f, 0.0f)) * scale(vec3(0.25f, 2.0f, 0.25f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void mongPHAIPHAIO1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.875f, -1.5f, 0.0f)) * scale(vec3(0.25f, 2.0f, 0.25f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void mongPHAIDUOIO1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -2.375f, 0.0f)) * scale(vec3(1.5f, 0.25f, 0.25f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void soPHAIDUOI02()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, -3.0f, 0.0f)) * scale(vec3(2.0f, 1.0f, 0.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void mongPHAIDUOIO2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 0.625f, 0.0f)) * scale(vec3(1.5f, 0.25f, 0.25f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void soPHAIO02()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 1.5f, 0.0f)) * scale(vec3(1.5f, 1.5f, 0.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void mongPHAITRAIO2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.875f, 1.5f, 0.0f)) * scale(vec3(0.25f, 2.0f, 0.25f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void mongPHAIPHAIO2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.875f, 1.5f, 0.0f)) * scale(vec3(0.25f, 2.0f, 0.25f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void mongPHAITRENO2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 2.375f, 0.0f)) * scale(vec3(1.5f, 0.25f, 0.25f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void soPHAITREN02()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 3.0f, 0.0f)) * scale(vec3(2.0f, 1.0f, 0.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void soPHAITRAI02()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(1.5f, 0.0f, 0.0f)) * scale(vec3(1.0f, 7.0f, 0.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void soPHAIPHAI02()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-1.5f, 0.0f, 0.0f)) * scale(vec3(1.0f, 7.0f, 0.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
//-----------------------------------------------------------------------------------
void tuongPHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-12.75f, 1.99f, 0.0f)) * rotate_z(90) * scale(vec3(10.0f, 1.5f, 23.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId1);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void tuongTRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(12.75f, 1.99f, 0.0f)) * rotate_z(-90) * scale(vec3(10.0f, 1.5f, 23.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId1);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void tuongTREN()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 7.75f, 0.0f)) * scale(vec3(27.0f, 1.5f, 23.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId1);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void tuongTRUOCPHAI() {
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(8.495f, 1.99f, 10.75f)) * scale(vec3(7.0f, 10.0f, 1.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId1);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void tuongTRUOCTRAI() {
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-8.495f, 1.99f, 10.75f)) * scale(vec3(7.0f, 10.0f, 1.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId1);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
//---------------------------------------------------------------------------------------
void khungtren() {
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 6.75f, 10.75f)) * scale(vec3(10.0f, 0.5f, 1.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void khungduoi() {
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 5.25f, 10.75f)) * scale(vec3(10.0f, 0.5f, 1.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void cot1() {
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 6.0f, 10.75f)) * scale(vec3(0.5f, 1.0f, 1.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void cot2() {
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(4.75f, 6.0f, 10.75f)) * scale(vec3(0.5f, 1.0f, 1.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void cot3() {
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-4.75f, 6.0f, 10.75f)) * scale(vec3(0.5f, 1.0f, 1.5f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void matkinhT() {
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(2.45f, 5.95f, 11.4f)) * scale(vec3(4.5f, 1.1f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId2);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void matkinhP() {
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-2.45f, 5.95f, 11.4f)) * scale(vec3(4.5f, 1.1f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId2);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void canhPHAITRONG()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(3.0f, 6.0f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void canhPHAIMANHTREN()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, 3.5, 0.1)) * scale(vec3(5.0f, 1.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void canhPHAIMANHDUOI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, -3.5, 0.1)) * scale(vec3(5.0f, 1.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void canhPHAIMANHTRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-2.0, 0.0, 0.1)) * scale(vec3(1.0f, 6.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void canhPHAIMANHPHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(2.0, 0.0, 0.1)) * scale(vec3(1.0f, 6.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
//
void canhTRAITRONG()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(3.0f, 6.0f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void canhTRAIMANHTREN()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, 3.5, 0.1)) * scale(vec3(5.0f, 1.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void canhTRAIMANHDUOI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, -3.5, 0.1)) * scale(vec3(5.0f, 1.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void canhTRAIMANHTRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-2.0, 0.0, 0.1)) * scale(vec3(1.0f, 6.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void canhTRAIMANHPHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(2.0, 0.0, 0.1)) * scale(vec3(1.0f, 6.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void matdayNAMCUA()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(2.0, 0.0, 0.35)) * scale(vec3(0.4f, 2.0f, 0.1f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId4);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void thanNAMCUA()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(2.0, 0.0, 0.85)) * scale(vec3(0.4f, 0.4f, 1.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId4);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void tayNAMCUA()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(1.5, 0.0, 1.325)) * scale(vec3(1.0f, 0.4f, 0.05f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId4);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
//----------------------------------------------------------------------------------
void matBAN()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, -0.89, 0.0)) * scale(vec3(3.0f, 0.2f, 6.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chanTRAITRUOC()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(1.3, -1.99, 2.8)) * scale(vec3(0.4f, 2.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chanTRAISAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-1.3, -1.99, 2.8)) * scale(vec3(0.4f, 2.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chanPHAITRUOC()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(1.3, -1.99, -2.8)) * scale(vec3(0.4f, 2.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void chanPHAISAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-1.3, -1.99, -2.8)) * scale(vec3(0.4f, 2.0f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
//----------------------------------------------------------------------------------
void matGHE()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, -1.4, 0.0)) * scale(vec3(4.0f, 0.2f, 7.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chanGHETRAITRUOC()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(1.8f, -2.25f, 3.3f)) * scale(vec3(0.4f, 1.5f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chanGHETRAISAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-1.8f, -2.25f, 3.3f)) * scale(vec3(0.4f, 1.5f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chanGHEPHAISAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-1.8f, -2.25f, -3.3f)) * scale(vec3(0.4f, 1.5f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chanGHEPHAITRUOC()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(1.8f, -2.25f, -3.3f)) * scale(vec3(0.4f, 1.5f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void taynamPHAIGHE()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, -0.7, 3.0)) * scale(vec3(4.0f, 0.2f, 1.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chantaynamPHAIGHE1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(1.9, -1.05, 3.0)) * scale(vec3(0.2f, 0.7f, 1.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chantaynamPHAIGHE2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-1.9, -1.05, 3.0)) * scale(vec3(0.2f, 0.7f, 1.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void taynamTRAIGHE()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, -0.7, -3.0)) * scale(vec3(4.0f, 0.2f, 1.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chantaynamTRAIGHE1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(1.9, -1.05, -3.0)) * scale(vec3(0.2f, 0.7f, 1.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chantaynamTRAIGHE2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-1.9, -1.05, -3.0)) * scale(vec3(0.2f, 0.7f, 1.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void matTUA()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-1.9, -0.3, 0.0)) * scale(vec3(0.2f, 2.0f, 5.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void matGHENGAN()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, -1.4, 0.0)) * scale(vec3(4.0f, 0.2f, 3.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chanGHENGANTRAITRUOC()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(1.8f, -2.25f, 1.3f)) * scale(vec3(0.4f, 1.5f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chanGHENGANTRAISAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(1.8f, -2.25f, -1.3f)) * scale(vec3(0.4f, 1.5f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chanGHENGANPHAISAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-1.8f, -2.25f, -1.3f)) * scale(vec3(0.4f, 1.5f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chanGHENGANPHAITRUOC()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-1.8f, -2.25f, 1.3f)) * scale(vec3(0.4f, 1.5f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void taynamPHAIGHENGAN()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, -0.7, 1.3)) * scale(vec3(4.0f, 0.2f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chantaynamPHAIGHENGAN1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(1.9, -1.05, 1.3)) * scale(vec3(0.2f, 0.7f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chantaynamPHAIGHENGAN2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-1.9, -1.05, 1.3)) * scale(vec3(0.2f, 0.7f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void taynamTRAIGHENGAN()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, -0.7, -1.3)) * scale(vec3(4.0f, 0.2f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chantaynamTRAIGHENGAN1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(1.9, -1.05, -1.3)) * scale(vec3(0.2f, 0.7f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void chantaynamTRAIGHENGAN2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-1.9, -1.05, -1.3)) * scale(vec3(0.2f, 0.7f, 0.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void matTUAGHENGAN()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(1.9, -0.3, 0.0)) * scale(vec3(0.2f, 2.0f, 2.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
//----------------------------------------------------------------------------------
void TIVI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.98, 3.0, 0.0)) * rotate_x(180) * scale(vec3(0.04f, 3.5f, 8.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	switch (tivichanels)
	{
	case 0:
		glBindTexture(GL_TEXTURE_2D, TextureId5);
		break;
	case 1:
		glBindTexture(GL_TEXTURE_2D, TextureId7);
		break;
	case 2:
		glBindTexture(GL_TEXTURE_2D, TextureId8);
		break;
	default:
		glBindTexture(GL_TEXTURE_2D, TextureId9);
		break;
	}
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void KhungTraiTIVI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.96, 3.0, 4.05)) * scale(vec3(0.08f, 3.7f, 0.1f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId5);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void KhungPhaiTIVI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.96, 3.0, -4.05)) * scale(vec3(0.08f, 3.7f, 0.1f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId5);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void KhungTrenTIVI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.96, 4.8, 0.0)) * scale(vec3(0.08f, 0.1f, 8.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId5);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void KhungDuoiTIVI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.96, 1.2, 0.0)) * scale(vec3(0.08f, 0.1f, 8.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId5);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
// Pictures
void TRANH()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-11.98, 2.6, 0.0)) * rotate_x(180) * scale(vec3(0.04f, 3.0f, 6.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId11);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void KhungTraiTRANH()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-11.85, 2.7, -3.07)) * scale(vec3(0.2f, 3.2f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId10);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void KhungPhaiTRANH()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-11.85, 2.7, 3.07)) * scale(vec3(0.2f, 3.2f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId10);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void KhungTrenTRANH()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-11.85, 4.2, 0.0)) * scale(vec3(0.2f, 0.2f, 6.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId10);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void KhungDuoiTRANH()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(-11.85, 1.0, 0.0)) * scale(vec3(0.2f, 0.2f, 6.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId10);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void TRANH2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(5.5, 3.6, -10.0)) * rotate_z(180) * scale(vec3(4.0f, 2.0f, 0.04f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId12);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void KhungTraiTRANH2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(3.43, 3.6, -10.0)) * scale(vec3(0.2f, 2.2f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId10);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void KhungPhaiTRANH2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(7.53, 3.6, -10.0)) * scale(vec3(0.2f, 2.2f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId10);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void KhungTrenTRANH2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(5.54, 4.7, -10.0)) * scale(vec3(4.2f, 0.2f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId10);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void KhungDuoiTRANH2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(5.54, 2.6, -10.0)) * scale(vec3(4.2f, 0.2f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId10);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

// Loa

void keLoa()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.3, 3.6, -9.3)) * scale(vec3(2.2f, 0.2f, 2.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void loa()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3( 11.1, 4.75, -9.15)) * scale(vec3(1.4f, 2.3f, 1.4f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId5);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
// Quat
void duiQUAT()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(1.2f, 0.5f, 1.2f)) * translate(vec3(0.0, 13.9, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId6);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void trucQUAT()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(0.2f, 2.0f, 0.2f)) * translate(vec3(0.0, 3.0, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId6);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void tamQUAT()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(0.9f, 0.2f, 0.9f)) * translate(vec3(0.0, 24.5, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId6);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void canhQUATTRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(3.5f, 0.15f, 1.1f)) * translate(vec3(0.6, 32.5, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId6);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void canhQUATPHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(3.5f, 0.15f, 1.1f)) * translate(vec3(-0.6, 32.5, 0.0));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId6);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void canhQUATTRUOC()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(1.1f, 0.15f, 7.5f)) * translate(vec3(0.0, 32.5, 0.0)) * rotate_y(90);

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId6);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void canhQUATSAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(1.1f, 0.15f, 7.5f)) * translate(vec3(0.0, 32.5, 0.0)) * rotate_y(-90);

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId6);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
//tủ
void tuCANHTRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.0, -1.5, 4.5)) * scale(vec3(1.5f, 3.0f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void tuCANHPHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.0, -1.5, -4.35)) * scale(vec3(1.5f, 3.0f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void tuCANHTREN()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.0, 0, 0)) * scale(vec3(1.7f, 0.3f, 9.05f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void tuCANHSAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.6, -1.15, 0)) * scale(vec3(0.2f, 2.5f, 9.05f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void tu1TRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.9, -1.3, 4.35)) * scale(vec3(1.4f, 2.5f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void tu1PHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.9, -1.3, 1.65)) * scale(vec3(1.4f, 2.5f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void tu2TRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.9, -1.3, 1.45)) * scale(vec3(1.4f, 2.5f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void tu2PHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.9, -1.3, -1.25)) * scale(vec3(1.4f, 2.5f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void tu3TRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.9, -1.3, -1.45)) * scale(vec3(1.4f, 2.5f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void tu3PHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.9, -1.3, -4.15)) * scale(vec3(1.4f, 2.5f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void tu1DUOI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.8, -2.5, 2.95)) * scale(vec3(1.4f, 0.2f, 2.9f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void tu2DUOI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.8, -2.5, 0.05)) * scale(vec3(1.4f, 0.2f, 2.9f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void tu3DUOI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.8, -2.5, -2.85)) * scale(vec3(1.4f, 0.2f, 2.9f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void tu1TRUOC()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.1, -1.2, 3.0)) * scale(vec3(0.2f, 2.4f, 2.8f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void tu2TRUOC()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.1, -1.2, 0.1)) * scale(vec3(0.2f, 2.4f, 2.8f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void tu3TRUOC()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.1, -1.2, -2.8)) * scale(vec3(0.2f, 2.4f, 2.8f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void tu1SAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.6, -1.6, 3.0)) * scale(vec3(0.2f, 2.4f, 2.8f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void tu2SAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.6, -1.6, 0.1)) * scale(vec3(0.2f, 2.4f, 2.8f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void tu3SAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.6, -1.6, -2.8)) * scale(vec3(0.2f, 2.4f, 2.8f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}


void tu1TAYNAM()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(9.95, -0.9, 3.0)) * scale(vec3(0.2f, 0.3f, 0.6f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}


void tu2TAYNAM()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(9.95, -0.9, 0.0)) * scale(vec3(0.2f, 0.3f, 0.6f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}


void tu3TAYNAM()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(9.95, -0.9, -3.0)) * scale(vec3(0.2f, 0.3f, 0.6f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
}

void dauDVD()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.0, 0.35, 0.2)) * scale(vec3(0.5f, 0.3f, 2.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId5);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void wifi()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.9, 0.35, -3.0)) * scale(vec3(1.0f, 0.25f, 1.8f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId13);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void rauWifi1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.17, 1.0, -2.21)) * scale(vec3(0.15f, 1.3f, 0.15f)) ;

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId13);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void rauWifi2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.17, 1.0, -3.77)) * scale(vec3(0.15f, 1.3f, 0.15f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId13);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

// Ke trung bay
void ktbCANHTRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.0, 1.55, 9.4)) * scale(vec3(1.5f, 8.7f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void ktbCANHPHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.0, 1.55, 6.0)) * scale(vec3(1.5f, 8.7f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void ktbCANHTREN()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.18, 6.0, 7.75)) * scale(vec3(1.5f, 0.2f, 3.55f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void ktbNgang1()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.1, 4.0, 7.6)) * scale(vec3(1.5f, 0.2f, 3.45f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void ktbNgang2()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.1, 2.0, 7.6)) * scale(vec3(1.5f, 0.2f, 3.45f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void ktbNgang3()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.1, 0.0, 7.6)) * scale(vec3(1.5f, 0.2f, 3.45f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void ktbTRAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.9, -1.3, 4.35)) * scale(vec3(1.4f, 2.5f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void ktbPHAI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.9, -1.3, 1.45)) * scale(vec3(1.4f, 2.5f, 0.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void ktbDUOI()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.8, -2.5, 2.95)) * scale(vec3(1.4f, 0.2f, 3.2f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void ktbTRUOC()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(10.1, -1.3, 3.0)) * scale(vec3(0.2f, 2.4f, 3.1f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void ktbSAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(11.7, -1.4, 3.0)) * scale(vec3(0.2f, 2.4f, 3.1f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void ktbTAYNAM()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(9.95, -0.9, 3.0)) * scale(vec3(0.2f, 0.3f, 0.75f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId3);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
void DENTRAN()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, 6.5f, 0.0f)) * scale(vec3(5.0f, 1.0f, 5.0f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glBindTexture(GL_TEXTURE_2D, TextureId13);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
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

	glClearColor(0.0, 0.0, 0.0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);

	// Set shader texture uniform
	int textureLocation = glGetUniformLocation(ProgramId, "textureSampler");
	glUniform1i(textureLocation, 0);
	// vẽ
	MATSAN();
	//Tường sau
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0f, 1.99f, -11.25f));
	tuongSAUM1();
	tuongSAUM2();
	tuongSAUM3();
	tuongSAUM4();
	//khungcuaso
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-6.5f, 0.0f, 0.0f));
	khungSOTRAI();
	khungSOPHAI();
	khungSOTREN1();
	khungSOTREN2();
	khungSOTRENCHIA();
	matKINHTRAI();
	matKINHPHAI();
	khungSODUOI();
	//chấn song
	chansongCOT1();
	chansongCOT2();
	chansongCOT3();
	chansongNGANG1();
	chansongNGANG2();
	//cánh trái
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(4.0f, 0.0f, -0.25f)) * rotate_y(alphasot) * translate(vec3(-2.0f, 0.0f, 0.25f));
	soTRAIGIUA01();
	mongTRAITRENO1();
	soTRAIO01();
	mongTRAITRAIO1();
	mongTRAIPHAIO1();
	mongTRAIDUOIO1();
	soTRAIDUOI01();
	mongTRAIDUOIO2();
	soTRAIO02();
	mongTRAITRAIO2();
	mongTRAIPHAIO2();
	mongTRAITRENO2();
	soTRAITREN01();
	soTRAITRAI01();
	soTRAIPHAI01();
	model_mat_cpp = mvstack.pop();
	// cánh phải
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-4.0, 0.0, -0.25)) * rotate_y(alphasop) * translate(vec3(2.0f, 0.0f, 0.25f));
	soPHAIGIUA02();
	mongPHAITRENO1();
	soPHAIO01();
	mongPHAITRAIO1();
	mongPHAIPHAIO1();
	mongPHAIDUOIO1();
	soPHAIDUOI02();
	mongPHAIDUOIO2();
	soPHAIO02();
	mongPHAITRAIO2();
	mongPHAIPHAIO2();
	mongPHAITRENO2();
	soPHAITREN02();
	soPHAITRAI02();
	soPHAIPHAI02();
	model_mat_cpp = mvstack.pop();
	model_mat_cpp = mvstack.pop();
	model_mat_cpp = mvstack.pop();
	//tường phải
	mvstack.push(model_mat_cpp);
	tuongPHAI();
	model_mat_cpp = mvstack.pop();
	//tường trái
	mvstack.push(model_mat_cpp);
	tuongTRAI();
	model_mat_cpp = mvstack.pop();
	// tường trên
	mvstack.push(model_mat_cpp);
	tuongTREN();
	model_mat_cpp = mvstack.pop();
	//tường trươc
	mvstack.push(model_mat_cpp);
	tuongTRUOCPHAI();
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	tuongTRUOCTRAI();
	model_mat_cpp = mvstack.pop();
	//khung cửa chính
	mvstack.push(model_mat_cpp);
	khungtren();
	khungduoi();
	cot1();
	cot2();
	cot3();
	matkinhT();
	matkinhP();
	model_mat_cpp = mvstack.pop();
	//cánh phải
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0f, 0.99f, 11.15f)) * translate(vec3(5.0f, 0.0, 0.0)) * rotate_y(alphap) * translate(vec3(-2.5, 0.0, 0.0));
	canhPHAITRONG();
	canhPHAIMANHTREN();
	canhPHAIMANHDUOI();
	canhPHAIMANHTRAI();
	canhPHAIMANHPHAI();
	model_mat_cpp = mvstack.pop();
	//cánh trái
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0f, 0.99f, 11.15f)) * translate(vec3(-5.0, 0.0, 0.0)) * rotate_y(alphat) * translate(vec3(2.5, 0.0, 0.0));
	canhTRAITRONG();
	canhTRAIMANHTREN();
	canhTRAIMANHDUOI();
	canhTRAIMANHTRAI();
	canhTRAIMANHPHAI();
	matdayNAMCUA();
	thanNAMCUA();
	tayNAMCUA();
	model_mat_cpp = mvstack.pop();
	//bàn
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-4.3, 0, 0));
	matBAN();
	chanTRAITRUOC();
	chanTRAISAU();
	chanPHAITRUOC();
	chanPHAISAU();
	model_mat_cpp = mvstack.pop();
	//ghế dài
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3( -9.0f, 0.0f, 0.0f));
	matGHE();
	chanGHETRAITRUOC();
	chanGHEPHAITRUOC();
	chanGHEPHAISAU();
	chanGHETRAISAU();
	taynamPHAIGHE();
	chantaynamPHAIGHE1();
	chantaynamPHAIGHE2();
	taynamTRAIGHE();
	chantaynamTRAIGHE1();
	chantaynamTRAIGHE2();
	matTUA();
	model_mat_cpp = mvstack.pop();
	//ghế ngắn
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0, 0.0, -1.5));
	matGHENGAN();
	chanGHENGANPHAISAU();
	chanGHENGANPHAITRUOC();
	chanGHENGANTRAISAU();
	chanGHENGANTRAITRUOC();
	taynamPHAIGHENGAN();
	taynamTRAIGHENGAN();
	chantaynamPHAIGHENGAN1();
	chantaynamPHAIGHENGAN2();
	chantaynamTRAIGHENGAN1();
	chantaynamTRAIGHENGAN2();
	matTUAGHENGAN();
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0, 0.0, 1.5));
	matGHENGAN();
	chanGHENGANPHAISAU();
	chanGHENGANPHAITRUOC();
	chanGHENGANTRAISAU();
	chanGHENGANTRAITRUOC();
	taynamPHAIGHENGAN();
	taynamTRAIGHENGAN();
	chantaynamPHAIGHENGAN1();
	chantaynamPHAIGHENGAN2();
	chantaynamTRAIGHENGAN1();
	chantaynamTRAIGHENGAN2();
	matTUAGHENGAN();
	model_mat_cpp = mvstack.pop();
	//tivi
	mvstack.push(model_mat_cpp);
	TIVI();
	KhungPhaiTIVI();
	KhungTraiTIVI();
	KhungTrenTIVI();
	KhungDuoiTIVI();
	model_mat_cpp = mvstack.pop();
	// Tranh
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0, 1.5, 0.0));
	TRANH();
	KhungTraiTRANH();
	KhungPhaiTRANH();
	KhungTrenTRANH();
	KhungDuoiTRANH();
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	TRANH2();
	KhungTraiTRANH2();
	KhungPhaiTRANH2();
	KhungTrenTRANH2();
	KhungDuoiTRANH2();
	model_mat_cpp = mvstack.pop();
	//quạt
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
	// Tu tivi
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.1, 0, 0));
	tuCANHTRAI();
	tuCANHPHAI();
	tuCANHTREN();
	tuCANHSAU();
	dauDVD();
		//Wifi
		mvstack.push(model_mat_cpp);
		wifi();
		rauWifi1();
		rauWifi2();
		model_mat_cpp = mvstack.pop();

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
	// Ke trung bay
	mvstack.push(model_mat_cpp);
	ktbCANHTRAI();
	ktbCANHPHAI();
	ktbCANHTREN();
	ktbNgang1();
	ktbNgang2();
	ktbNgang3();
	model_mat_cpp = model_mat_cpp * translate(vec3(ktb, 0.0, 0.0));
	model_mat_cpp = model_mat_cpp * translate(vec3(0, 0.05, 4.7));
	ktbPHAI();
	ktbTRAI();
	ktbDUOI();
	ktbSAU();
	ktbTRUOC();
	ktbTAYNAM();
	model_mat_cpp = mvstack.pop();
//Loa
	mvstack.push(model_mat_cpp);
	keLoa();
	loa();
	model_mat_cpp = mvstack.pop();

	//đèn trần
	mvstack.push(model_mat_cpp);
	DENTRAN();
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
	case 'M':
		alphat = 0.0f;
		alphap = 0.0f;
		break;
	case '1': // Bật tắt đèn
		light1Enabled = !light1Enabled;
		glutPostRedisplay();
		break;
	case '2':///quạt số 1
		glutIdleFunc(IdleFunc1);
		break;
	case '3':///quạt số 2
		glutIdleFunc(IdleFunc2);
		break;
	case '4':// quạt số 3
		glutIdleFunc(IdleFunc3);
		break;
	case '5'://tắt quạt
		glutIdleFunc(IdleFunc);
		break;
	case '6'://mở cửa sổ
		alphasop = 90.0f;
		alphasot = -90.0f;
		break;
	case '7'://đóng cửa sổ
		alphasop = 0.0f;
		alphasot = 0.0f;
		break;
		//tủ ti vi
	case 'c':
		tTu1 = -1.2;
		break;
	case 'C':
		tTu1 = 0.0;
		break;
	case 'v':
		tTu2 = -1.2;
		break;
	case 'V':
		tTu2 = 0.0;
		break;
	case 'b':
		tTu3 = -1.2;
		break;
	case 'B':
		tTu3 = 0.0;
		break;
		//tủ kệ trưng bày
	case 'n':
		ktb = -1.2;
		break;
	case 'N':
		ktb = 0.0;
		break;
	case 'a':// nhìn sang trái
		eye = eye + normalize(cross(vec3(0.0, 0.0, -1.0), up)) * cameraSpeed;
		break;
	case 'd'://nhìn từ phải sang
		eye = eye - normalize(cross(vec3(0.0, 0.0, -1.0), up)) * cameraSpeed;
		break;
	case 'w'://lại gần
		eye = eye + cameraSpeed * vec3(0.0f, 0.0f, -1.0f);
		break;
	case 's'://ra xa
		eye = eye - cameraSpeed * vec3(0.0f, 0.0f, -1.0f);
		break;
	case 'q'://lên trên
		eye = eye + vec3(0.0f, 1.0f, 0.0f) * cameraSpeed;
		break;
	case 'e'://xuống dưới
		eye = eye - vec3(0.0f, 1.0f, 0.0f) * cameraSpeed;
		break;
	case '8':
		tivichanels++;
		glutPostRedisplay();
		break;
	case '9':
		tivichanels--;
		glutPostRedisplay();
		break;
	case '0':
		tivichanels = 0;
		glutPostRedisplay();
		break;
	}
}
// ----------------------------------------

	// Xử lý phím đặc biệt
void SpecialFunc(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_LEFT:// nhìn sang trái
		eye = eye + normalize(cross(vec3(0.0, 0.0, -1.0), up)) * cameraSpeed;
		break;
	case GLUT_KEY_RIGHT://nhìn từ phải sang
		eye = eye - normalize(cross(vec3(0.0, 0.0, -1.0), up)) * cameraSpeed;
		break;
	case GLUT_KEY_UP://lại gần
		eye = eye + cameraSpeed * vec3(0.0f, 0.0f, -1.0f);
		break;
	case GLUT_KEY_DOWN://ra xa
		eye = eye - cameraSpeed * vec3(0.0f, 0.0f, -1.0f);
		break;
	case GLUT_KEY_ALT_R://lên trên
		eye = eye + vec3(0.0f, 1.0f, 0.0f) * cameraSpeed;
		break;
	case GLUT_KEY_CTRL_R://xuống dưới
		eye = eye - vec3(0.0f, 1.0f, 0.0f) * cameraSpeed;
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
	glutCreateWindow("A Living Room");

	glewExperimental = GL_TRUE;
	glewInit();
	InitTextures();
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
