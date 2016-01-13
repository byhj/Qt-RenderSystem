#include "rendersystem.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RenderSystem w;
	w.show();
	return a.exec();
}
