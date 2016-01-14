
#ifndef OGLSHADER_H
#define OGLSHADER_H

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <GL/glew.h>

char *textFileRead(const char *fn);  

#define WINDOW_PLATFORM

namespace byhj
{
	namespace ogl
	{


class Shader {
public:
	Shader(){}
	~Shader(){}
	Shader(std::string shaderName):name(shaderName) {}
	void init();
	void attach(int type, char *filename);
	void linkAttach();
	void link();
	void interfaceInfo();
	void use(void) 
	{
		glUseProgram(program);
	}
	void end(void) 
	{
		glUseProgram(0);
	}

	GLuint GetProgram()
	{
        return program;
	}

private:
	std::vector<GLuint> handles; //shader handle
	GLuint program;   //shader program
	std::string name;   //shader class name
};

	}
}

#endif

