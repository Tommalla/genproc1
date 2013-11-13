#include <QQueue>
#include "pktnkju.hpp"

const QRgb c_ziemia = qRgb(123, 216, 69), c_woda = qRgb(0, 127, 255);
//int starting_points, spread_chance, smooth_pow, smooth_area;
pkt a, b;
//pkt_kju kolej;
QQueue<pkt> kolej;
bool land[WID * HEI];

int params[4];
const int DEFAULTS[] = {25, 2500, 3, 2};

int main(int argc, char *argv[])
{
	if (argc < 2 || argc > 6) {
		printf("Składnia: WORLD <plik wynikowy> [<ilość punktów startowych> [<prawdopodobieństwo poszerzenia lądu (0-10000)>] [<pole wygładzania>] [<siła wygładzania>]]]\n");
		return 1;
	}

	for (int i = 0; i < 4; ++i)
		params[i] = (argc >= i + 3) ? atoi(argv[i + 2]) : DEFAULTS[i];

	QImage image(WID, HEI, QImage::Format_RGB32);
	image.fill(c_woda);
	srand (time ( NULL ));
	for (int i = 0; i < params[0]; i++)
	{
		a.randum();
		kolej.push_back(a);
		land[a.conv()] = true;
	}

	while (!kolej.empty())
	{
		a = kolej.front();
		kolej.pop_front();
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
			{
				b.make(a.x + i, a.y + j);
				if (!land[b.conv()] && b.x >= 0 && b.x < WID && b.y >= 0 && b.y < HEI && rand() % MAX < params[1])
				{
					land[b.conv()] = true;
					kolej.push_back(b);
				}
			}
	}
	//smooth(land, params[2], params[3], WID, HEI);

	for (int i = 0 ; i < WID; i++)
		for (int j = 0; j < HEI; j++)
		{
			a.make(i, j);
			image.setPixel(a.x, a.y, land[a.conv()] ? c_ziemia : c_woda);
		}

	image.save(argv[1]);
	return 0;
}