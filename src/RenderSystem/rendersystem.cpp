#include "rendersystem.h"
#include "d3dWidget.h"
#include "oglWidget.h"
RenderSystem::RenderSystem(QWidget *parent)
	: QMainWindow(parent)
{ 

	ui.setupUi(this);
	this->setStyleSheet("background:transparent");
	//m_D3DWidget = new byhj::D3DWidget(this);
	//m_D3DWidget->init(this->width(), this->height());
	//setWindowFlags(Qt::FramelessWindowHint);
	//setWindowOpacity(0.25);
	//setAttribute(Qt::WA_TranslucentBackground, true);
	setStyleSheet("border:2px groove gray; border-radius:10px; padding:2px 3px; opacity: 0.5;");
	byhj::OGLWidget *widget = new byhj::OGLWidget(this);
	setCentralWidget(widget);

}

RenderSystem::~RenderSystem()
{

}
