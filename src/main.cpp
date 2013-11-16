#include <QApplication>
#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);
	srand (time ( NULL ));

	MainWindow mainWindow;
	mainWindow.show();
	return application.exec();
}