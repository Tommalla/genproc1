#include <QImage>
#include "pkt.hpp"
#include "calc.hpp"


const QRgb c_ziemia = qRgb(123, 216, 69), c_woda = qRgb(0, 127, 255);
//int starting_points, spread_chance, smooth_pow, smooth_area;
pkt a, b;
//pkt_kju kolej;
bool land[WID * HEI];

int params[5];
const int DEFAULTS[] = {25, 2500, 3, 2, 3};

int main(int argc, char *argv[])
{
	if (argc < 2 || argc > 7) {
		printf("Składnia: WORLD <plik wynikowy> [<ilość punktów startowych> [<prawdopodobieństwo poszerzenia lądu (0-10000)>] [<pole wygładzania>] [<siła wygładzania> [<pointless water size>]]]]\n");
		return 1;
	}

	for (int i = 0; i < 5; ++i)
		params[i] = (argc >= i + 3) ? atoi(argv[i + 2]) : DEFAULTS[i];

	srand (time ( NULL ));

	generate(land, params[0], params[1]);
	removePointlessWater(land, params[4]);
	smooth(land, params[2], params[3], WID, HEI);

	QImage image(WID, HEI, QImage::Format_RGB32);
	image.fill(c_woda);

	for (int i = 0 ; i < WID; i++)
		for (int j = 0; j < HEI; j++)
		{
			a = pkt(i, j);
			image.setPixel(a.x, a.y, land[a.conv()] ? c_ziemia : c_woda);
		}

	image.save(argv[1]);
	return 0;
}