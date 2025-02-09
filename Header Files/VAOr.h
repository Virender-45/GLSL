#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include "../Header Files/VBO.h"

class VAO {
	public:

		GLuint ID;
		VAO();

		void LinkVBO(VBO VBO, GLuint layout);
		void Bind();
		void unbind();
		void Delete();
};

#endif