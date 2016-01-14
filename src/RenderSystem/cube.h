#ifndef CUBE_H
#define CUBE_H

#include "oglShader.h"
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Cube
{

public:
	Cube();
	~Cube();

public:

    void init();

	void render(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &proj)
	{
		glUseProgram(program);
		glBindVertexArray(vao);  

		glm::mat4 mvp = proj * view * model;
		glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, &mvp[0][0]);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glUseProgram(0);
		glBindVertexArray(0);
	}

	void init_buffer();
	void init_shader();
	void init_vertexArray();

private:
	GLuint program;
	GLuint vao, vbo, ibo;
	byhj::ogl::Shader cubeShader;
	GLuint mvp_loc;
};

#endif