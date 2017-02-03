#pragma once

#include "opengl-wrapper\GLEW\include\GL\glew.h"
#include "Vector3.h"
#include "Mat4.h"

class ShaderProgram
{
public:
	int shader_program;

	ShaderProgram();
	~ShaderProgram();

	void compileShader(char* file_vertex, char* file_geo, char* file_fragment);
	void use();
	void checkCompileErrors(int shader);
	void checkLinkErrors(int shader);
	const char * getShaderSource(char* filename);

	void loadInteger(char* location, int value);
	void loadFloat(char* location, float value);
	void loadVector3(char* location, Vector3 v);
	void loadMat4(char* location, Mat4 *mat);
	void loadSampler(char* location, int i);

};