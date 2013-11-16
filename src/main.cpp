#include <QImage>
#include <QApplication>
#include "MainWindow.hpp"


const QRgb c_ziemia = qRgb(123, 216, 69), c_woda = qRgb(0, 127, 255);
//int starting_points, spread_chance, smooth_pow, smooth_area;
//Point a, b;
//pkt_kju kolej;
//bool land[WID * HEI];

int params[5];
const int DEFAULTS[] = {25, 2500, 3, 2, 3};

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);
	srand (time ( NULL ));

	MainWindow mainWindow;
	mainWindow.show();

	//generate(land, params[0], params[1]);
	//removePointlessWater(land, params[4]);
	//smooth(land, params[2], params[3], WID, HEI);

	//QImage image(WID, HEI, QImage::Format_RGB32);
	//image.fill(c_woda);

	//for (int i = 0 ; i < WID; i++)
	//	for (int j = 0; j < HEI; j++)
	//	{
	//		a = pkt(i, j);
	//		image.setPixel(a.x, a.y, land[a.conv()] ? c_ziemia : c_woda);
	//	}

	//image.save(argv[1]);
	return application.exec();
}