#include <qapplication.h>
#include <qsplashscreen.h>
#include "MainWindow.h"

using namespace DirectLook;

int main( int argc, char* argv[] )
{
	QApplication app( argc, argv );
	MainWindow* pMainWindow = new MainWindow();
	pMainWindow->setWindowFlags( Qt::WindowMinimizeButtonHint );
	pMainWindow->layout()->setSizeConstraint( QLayout::SetFixedSize );
	pMainWindow->show();
	return app.exec();
}
