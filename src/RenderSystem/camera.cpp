#include "Camera.h"


void Camera::init(float aspect, float radius)
{
	m_Aspect = aspect;
	m_Radius = radius;
}

glm::mat4 Camera::GetView() const 
{
	return m_View;
}

glm::mat4 Camera::GetProj() const
{
	return m_Proj;
}

glm::vec3 Camera::GetPos() const
{
	return pos;
}

void Camera::update()
{
	// Convert Spherical to Cartesian coordinates.
	float x = m_Radius * sinf(m_Phi) * cosf(m_Theta);
	float z = m_Radius * sinf(m_Phi) * sinf(m_Theta);
	float y = m_Radius * cosf(m_Phi);

	// Build the view matrix.
	glm::vec3 pos    = glm::vec3(x, y, z);
	glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up     = glm::vec3(0.0f, 1.0f, 0.0f);

	m_View = glm::lookAt(pos, target, up);
	m_Proj = glm::perspective(glm::radians(zoom), m_Aspect,  0.1f, 1000.0f);
}

void Camera::OnMouseWheel(QWheelEvent *event)
{
	QPoint numDegreesA = event->angleDelta() / 8;

	if (!numDegreesA.isNull())
	{
		int numDegrees = event->delta() / 8;
		int numSteps = numDegrees / 15;
		zoom += zoom * numSteps * 0.1f;
	}
	event->accept();
}

void Camera::OnMouseDown(QMouseEvent *event)
{	
	m_LastMousePos.x = event->x();
	m_LastMousePos.y = event->y();
}

void Camera::OnMouseUp(QMouseEvent *event)
{
}

void Camera::OnMouseMove(QMouseEvent *event)
{
	int x = event->x();
	int y = event->y();

	if (event->buttons() & Qt::LeftButton) 
	{
		// Make each pixel correspond to a quarter of a degree.
		float dx = glm::radians(0.45f * static_cast<float>(x - m_LastMousePos.x) );
		float dy = glm::radians(0.45f * static_cast<float>(y - m_LastMousePos.y) );

		// Update angles based on input to orbit Camera around box.
		m_Theta += dx;
		m_Phi   += dy;

		// Restrict the angle mPhi.
		m_Phi = glm::clamp(m_Phi, 0.1f, Pi - 0.1f);
	}

	m_LastMousePos.x = x;
	m_LastMousePos.y = y;
}

