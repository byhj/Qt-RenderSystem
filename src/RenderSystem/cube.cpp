#include "Cube.h"

Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::init()
{
	init_buffer();
	init_vertexArray();
	init_shader();
}

static const GLfloat VertexData[] = 
{  
	//Front
	-0.5f, -0.5f,  0.5f, 
	 0.5f, -0.5f,  0.5f, 
	 0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f,  0.5f, 

	//Back		   
	-0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f, -0.5f, 
	 0.5f,  0.5f, -0.5f, 
	-0.5f,  0.5f, -0.5f, 
};
static const GLsizei VertexSize = sizeof(VertexData);

static const GLuint IndexData[] = 
{
	//Front
	0, 1, 2,
	2, 3, 0,

	//Left
	0, 3, 7,
	7, 4, 0,

	//back
	4, 7, 6,
	6, 5, 4,

	//right
	5, 6, 2,
	2, 1, 5,

	//top
	3, 2, 6,
	6, 7, 3,

	//bottom
	5, 1, 0,
	0, 4, 5,
};
static const GLsizei IndexSize = sizeof(IndexData);

void Cube::init_buffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexData), IndexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Cube::init_vertexArray()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
    
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

 	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
}

void Cube::init_shader()
{
	cubeShader.init();
	cubeShader.attach(GL_VERTEX_SHADER, "cube.vert");
	cubeShader.attach(GL_FRAGMENT_SHADER, "cube.frag");
	cubeShader.link();
	program = cubeShader.GetProgram();

	mvp_loc = glGetUniformLocation(program, "mvp");
}


