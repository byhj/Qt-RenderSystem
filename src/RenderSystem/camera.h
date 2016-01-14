#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <QMouseEvent>

const float Pi = 3.1415926f;

class Camera 
{
public:
	Camera()
	{
		m_Theta  = 1.5f * Pi;
		m_Phi    = 0.45f * Pi;
		m_Radius = 5.0f;
		m_LastMousePos.x = 0;
		m_LastMousePos.y = 0;
		m_World = glm::mat4(1.0f);
		m_View  = glm::mat4(1.0f);
		m_Proj  = glm::mat4(1.0f);
		m_Aspect  = 1.0f;
		zoom = 45.0f;
	}
	~Camera(){}

public:
	void update();
	void init(float aspect, float radius);
	glm::mat4 GetView() const; 
	glm::mat4 GetProj() const;
	glm::vec3 GetPos() const;

	void OnMouseDown(QMouseEvent *event);
	void OnMouseMove(QMouseEvent *event);
	void OnMouseUp(QMouseEvent *event);
	void OnMouseWheel(QWheelEvent *event);

private:
	float m_Theta;
	float m_Phi;
	float m_Radius;

	glm::vec2 m_LastMousePos;
	glm::mat4 m_World;
	glm::mat4 m_View;
	glm::mat4 m_Proj;
	glm::vec3 pos;
	glm::vec3 target;

	float m_Aspect;
	float zoom;
};
#endif