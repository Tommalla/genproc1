#include "pktnkju.hpp"

const QRgb c_ziemia = qRgb(123, 216, 69), c_woda = qRgb(0, 127, 255);
int starting_points, spread_chance, smooth_pow, smooth_area;
pkt a, b;
pkt_kju kolej;
bool land[WID * HEI];
int main(int argc, char *argv[])
{
	printf("Podaj ilosc punktow startowych: ");
// 	kolej.clear();
	scanf("%d", &starting_points);
	printf("Podaj prawdopodobieństwo poszerzenia ladu (0 - 10000): ");
	scanf("%d", &spread_chance);
	printf("Podaj pole (def 3) i sile wygladzenia (def 2): ");
	scanf("%d %d", &smooth_area, &smooth_pow);
	QImage image(WID, HEI, QImage::Format_RGB32);
	image.fill(c_woda);
	srand (time ( NULL ));
	for (int i = 0; i < starting_points; i++)
	{
		a.randum();
// 		printf("%d %d\n", a.x, a.y);
		kolej.add(a);
		land[a.conv()] = true;
		// 		printf("huehuehue\n");
// 		kolej.kju[qhead++] = a;
	}
// 	printf("uno\n");
	while (!kolej.empty())
	{
		a = kolej.pop();
// 		printf("1a\n");
 		//printf("lol %d %d\n", a.x, a.y);

// 		printf("2a\n");
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
			{
				b.make(a.x + i, a.y + j);
// 				printf("3a\n");
				if (!land[b.conv()] && b.x >= 0 && b.x < WID && b.y >= 0 && b.y < HEI && rand() % MAX < spread_chance)
				{
					land[b.conv()] = true;
// 					printf("habahaba\n");
					kolej.add(b);
				}
// 					kolej.kju[qhead++];
// 				printf("4a\n");
			}
	}
	smooth(land, smooth_area, smooth_pow, WID, HEI);
// 	printf("fcuk\n");
	for (int i = 0 ; i < WID; i++)
		for (int j = 0; j < HEI; j++)
		{
			a.make(i, j);
			image.setPixel(a.x, a.y, land[a.conv()] ? c_ziemia : c_woda);
		}
	image.save("world.png");
	return 0;
}