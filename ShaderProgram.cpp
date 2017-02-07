#include "ShaderProgram.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>



ShaderProgram::ShaderProgram()
{
}

void ShaderProgram::compileShader(char * file_vertex, char * file_geo, char * file_fragment)
{

	shader_program = glCreateProgram();

	int shader_vertex = glCreateShader(GL_VERTEX_SHADER);
	const char* source_vertex = getShaderSource(file_vertex);
	glShaderSource(shader_vertex, 1, &source_vertex, 0);
	glCompileShader(shader_vertex);
	glAttachShader(shader_program, shader_vertex);
	delete[] source_vertex;

	if (file_geo != NULL) {
		int shader_geometry = glCreateShader(GL_GEOMETRY_SHADER);
		const char* source_geometry = getShaderSource(file_geo);
		glShaderSource(shader_geometry, 1, &source_geometry, 0);
		glCompileShader(shader_geometry);
		glAttachShader(shader_program, shader_geometry);

		checkCompileErrors(shader_geometry);
		delete[] source_geometry;
	}


	int shader_fragment = glCreateShader(GL_FRAGMENT_SHADER);
	const char* source_fragment = getShaderSource(file_fragment);
	glShaderSource(shader_fragment, 1, &source_fragment, 0);
	glCompileShader(shader_fragment);
	glAttachShader(shader_program, shader_fragment);
	delete[] source_fragment;


	checkCompileErrors(shader_vertex);
	checkCompileErrors(shader_fragment);


	glLinkProgram(shader_program);
	checkLinkErrors(shader_program);
	glUseProgram(shader_program);

}

void ShaderProgram::use()
{
	glUseProgram(this->shader_program);
}

void ShaderProgram::checkCompileErrors(int shader)
{
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		char infolog[2048];
		glGetShaderInfoLog(shader, 2048, 0, infolog);
		std::cout << infolog << std::endl;
	}

}

void ShaderProgram::checkLinkErrors(int program)
{
	int success;
	glGetShaderiv(program, GL_LINK_STATUS, &success);

	if (!success) {
		char infolog[2048];
		glGetShaderInfoLog(program, 2048, 0, infolog);
		std::cout << infolog << std::endl;
	}

}

const char* ShaderProgram::getShaderSource(char * filename)
{

	std::ifstream file;
	file.open(filename, file.binary | file.in);

	char *buffer;
	int size;

	file.seekg(0, file.end);
	size = file.tellg();
	file.seekg(0, file.beg);

	buffer = new char[size + 1];
	file.read(buffer, size);

	buffer[size] = '\0';

	return buffer;

}

void ShaderProgram::loadInteger(char * location, int value) {
	use();
	glUniform1i(glGetUniformLocation(this->shader_program, location), value);
}

void ShaderProgram::loadFloat(char * location, float value) {
	use();
	glUniform1f(glGetUniformLocation(this->shader_program, location), value);
}

void ShaderProgram::loadVector3(char * location, Vector3 v) {
	use();
	glUniform3f(glGetUniformLocation(this->shader_program, location), v.x, v.y, v.z);
}

void ShaderProgram::loadMat4(char * location, Mat4 *mat) {
	use();
	glUniformMatrix4fv(glGetUniformLocation(this->shader_program, location), 1, true, mat->mat);
}

void ShaderProgram::loadSampler(char * location, int i) {
	use();
	glUniform1i(glGetUniformLocation(this->shader_program, location), i);
}

ShaderProgram::~ShaderProgram()
{
}

