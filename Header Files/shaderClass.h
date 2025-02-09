#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <iostream>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <cerrno>
#include<string>

std::string get_file_contents(const char* filename);

class Shader {
	public:
		GLuint ID;

		Shader(const char* vertexFile, const char* shaderFile);

		void Activate();
		void Delete();
};

#endif