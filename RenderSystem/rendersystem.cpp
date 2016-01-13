#include "rendersystem.h"
#include "d3dWidget.h"

RenderSystem::RenderSystem(QWidget *parent)
	: QMainWindow(parent)
{ 
	ui.setupUi(this);
	m_D3DWidget = new byhj::D3DWidget(this);
	m_D3DWidget->init(this->width(), this->height());
	setCentralWidget(m_D3DWidget);

}

RenderSystem::~RenderSystem()
{

}
