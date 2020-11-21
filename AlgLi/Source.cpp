
#include "Header.h"


using namespace std;
using namespace sf;

int main()
{
	int up = 0;
	sf::RenderWindow window(sf::VideoMode(400, 400), "Labirint", Style::Fullscreen);
	view.reset(FloatRect(0, 0, 600, 600));
	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("",font, 20);
	//text.setColor(Color(255,0,0));
	text.setStyle(Text::Bold);

	Clock clock;
	int iS = 1, jS = 1;
	int iE = 5, jE = 8;
	const int sizeX = 8; const int sizeY = 10;
	int Arr[sizeX][sizeY] = {
	{-2,-2,-2,-2,-2,-1,-1,-2,-2,-2},
	{-2, 0,-1,-2,-2,-1,-2,-2,-2,-2},
	{-1,-2,-2,-2,-1,-1,-2,-2,-1,-2},
	{-2,-2,-2,-2,-2,-2,-2,-2,-2,-2},
	{-2,-1,-2,-2,-1,-2,-1,-2,-2,-2},
	{-2,-1,-1,-2,-2,-2,-2,-1,-3,-2},
	{-2,-2,-2,-2,-2,-2,-2,-2,-2,-2},
	{-2,-2,-2,-2,-2,-1,-2,-2,-2,-2}};
	bool stop = true;
	int step = 1;
	int di[4] = { 1,0,-1,0 };
	int dj[4] = { 0,1,0,-1 };
	if (Arr[iS][jS] == -1 || Arr[iE][jE] == -1) {
		up = -1;
		//return 1;
	}
	
	Image map_image;//объект изображения для карты
	map_image.loadFromFile("map.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

	while (window.isOpen()) {
		
		window.setView(view); // BAG
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
		if (up == -1) {
			text.setString("End Game");
			text.setPosition(view.getCenter().x - 165, view.getCenter().y - 200);//задаем позицию текста, отступая от центра камеры
			window.draw(text);
		}
		else {
			if (Keyboard::isKeyPressed(Keyboard::G)) {
				up++;
				if (up == 1) {
					do {
						stop = true;
						for (int i = 0; i < 8; i++)
						{
							for (int j = 0; j < 10; j++) {
								if (Arr[i][j] == step - 1) {
									for (int k = 0; k < 4; k++)
									{
										int Ai = i + di[k];
										int Aj = j + dj[k];
										if (Ai >= 0 && Ai < 8 && Aj >= 0 && Aj < 10 && (Arr[Ai][Aj] == -2 || Arr[Ai][Aj] == -3)) {
											Arr[Ai][Aj] = step;
											stop = false;
										}

									}
								}
							}
						}
						step++;
					} while (!stop && Arr[iE][jE] == -3);
					step = Arr[iE][jE];
					Arr[iE][jE] = -4;
				}
				if (up == 2) {
					int x = iE;
					int y = jE;
					do {
						for (int k = 0; k < 4; k++) {
							int Ai = x + di[k];
							int Aj = y + dj[k];
							if (Arr[Ai][Aj] == step - 1) {
								Arr[Ai][Aj] = 0;
								x = x + di[k];
								y = y + dj[k];
								break;
							}
						}
						step--;
					} while (step != 0);
				}
			}
		}
		changeview();
		viewmap(time);
		if (Keyboard::isKeyPressed(Keyboard::C)) window.clear();
		
		int i, j;
		for (i = 0; i < sizeX; i++) {
			for (j = 0; j < sizeY; j++)
			{
				if (Arr[i][j] == -1)  s_map.setTextureRect(IntRect(0, 21, 18, 18));
				else if (Arr[i][j] == 0) s_map.setTextureRect(IntRect(160, 321, 18, 18));
				else if (Arr[i][j] == -3) s_map.setTextureRect(IntRect(500, 61, 18, 18));
				else if (Arr[i][j] == -4) s_map.setTextureRect(IntRect(60, 221, 18, 18));
				else s_map.setTextureRect(IntRect(0, 1, 18, 18));
				s_map.setPosition(j * 20, i * 20);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
				window.draw(s_map);//рисуем квадратики на экран
				window.display();
			}
			
			
			cout << endl;
		}
		
	}
	window.clear();
	return 0;
}
