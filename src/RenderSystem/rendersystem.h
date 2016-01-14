#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <QtWidgets/QMainWindow>
#include "ui_rendersystem.h"
#include "d3dWidget.h"
#include <QPainter>

class RenderSystem : public QMainWindow
{
	Q_OBJECT

public:
	RenderSystem(QWidget *parent = 0);
	~RenderSystem();

protected:
	//void painEvent(QPaintEvent*)
	//{
	//	QPainter p(this);
	//	p.setCompositionMode(QPainter::CompositionMode_Clear);
	//	p.fillRect(10, 10, 300, 300, Qt::SolidPattern);
	//}
private:
	Ui::RenderSystemClass ui;
	byhj::D3DWidget *m_D3DWidget;
};

#endif // RENDERSYSTEM_H
