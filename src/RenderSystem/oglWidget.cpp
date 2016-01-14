#include "oglWidget.h"

#include <iostream>
#include <QPainter>

namespace byhj
{

OGLWidget::OGLWidget(QWidget *parent)
: QOpenGLWidget(parent),
m_aspect(1.0f)
{
	
	m_Model = glm::mat4(1.0f);
	m_View  = glm::mat4(1.0f);
	m_Proj  = glm::mat4(1.0f);
}

OGLWidget::~OGLWidget()
{
	makeCurrent();
	doneCurrent();
}


QSize OGLWidget::minimumSizeHint() const
{
	return QSize(100, 100);
}

QSize OGLWidget::sizeHint() const
{
	return QSize(1000, 800);
}

void OGLWidget::initializeGL()
{
	GLenum result = glewInit();
	if ( result!=GLEW_OK )
		std::cout<<"Init glew Error:"<<glGetString(result)<<std::endl;

	cube.init();

	glEnable(GL_CULL_FACE);
}


void OGLWidget::paintGL()
{
	QPainter painter;
	painter.begin(this);

	painter.beginNativePainting();

	static const GLfloat black[] ={0.2, 0.3, 0.4, 1.0f};
	static const GLfloat one[] ={1.0f};
	glClearBufferfv(GL_COLOR, 0, black);
	glClearBufferfv(GL_DEPTH, 0, one);

	m_Camera.update();

	m_Model = glm::rotate(glm::mat4(1.0f), 30.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	m_View  = m_Camera.GetView();
	m_Proj  = m_Camera.GetProj();

	cube.render(m_Model, m_View, m_Proj);


	painter.endNativePainting();


	static bool startFlag = true;
	if ( startFlag )
	{
		time.start();
		startFlag = false;
	}
	static int frame = 0;
	static float lastTime = 0.0f;
	float currentTime = time.elapsed()/1000.0f;
	static int cnt = 0;
	std::cout<<currentTime<<std::endl;

	if ( currentTime-lastTime>1.0f )
	{
		lastTime = currentTime;
		cnt = frame;
		frame = 0;
	}
	else
	{
		++frame;
	}

	QString fps  = QString::number(cnt);
	painter.setPen(Qt::white);
	painter.drawText(50.0, 50.0, QString("FPS:"+fps));

	painter.end();

	update();
}

void OGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	m_aspect = static_cast< float >( w )/static_cast< float >( h );
	m_Camera.init(m_aspect, 5.0f);

}

void OGLWidget::mousePressEvent(QMouseEvent *event)
{
	m_Camera.OnMouseDown(event);
}

void OGLWidget::mouseMoveEvent(QMouseEvent *event)
{
	m_Camera.OnMouseMove(event);
}

void OGLWidget::wheelEvent(QWheelEvent *event)
{
	m_Camera.OnMouseWheel(event);
}

}