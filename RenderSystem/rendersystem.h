#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <QtWidgets/QMainWindow>
#include "ui_rendersystem.h"
#include "d3dWidget.h"

class RenderSystem : public QMainWindow
{
	Q_OBJECT

public:
	RenderSystem(QWidget *parent = 0);
	~RenderSystem();

private:
	Ui::RenderSystemClass ui;
	byhj::D3DWidget *m_D3DWidget;
};

#endif // RENDERSYSTEM_H
