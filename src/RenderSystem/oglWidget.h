#ifndef oglWidget_H
#define oglWidget_H

#include <gl/glew.h>

#include <QOpenGLWidget>
#include <QTime>
#include <QMouseEvent>
#include "cube.h"
#include "camera.h"


namespace byhj
{
	class OGLWidget : public QOpenGLWidget
	{
		Q_OBJECT

	public:
		OGLWidget(QWidget *parent = nullptr);
		~OGLWidget();

		QSize minimumSizeHint() const Q_DECL_OVERRIDE;
		QSize sizeHint() const Q_DECL_OVERRIDE;

	protected:
		void initializeGL() Q_DECL_OVERRIDE;
		void paintGL() Q_DECL_OVERRIDE;
		void resizeGL(int width, int height) Q_DECL_OVERRIDE;
	
		void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
		void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
		void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
	
	private:
		QTime time;
		Cube cube;
		Camera m_Camera;

		float m_aspect;

		glm::mat4 m_Model;
		glm::mat4 m_View;
		glm::mat4 m_Proj;
	};
}
#endif