
#include "Game.h"

int main()
{
	srand(time(NULL));
	//init default SFML stuff
    sf::RenderWindow	window(sf::VideoMode(800, 600), "test");
    sf::Event			event;
	

	//put game manager
	Game game(&window);

	//stop the program if our cool game manager fails ]:
	if (!game.initGame())
		return (-1);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyReleased:
				game.onKeyReleased(event.key.code);
				break;
			case sf::Event::MouseButtonReleased:
				game.onMouseButtonReleased(event.mouseButton.button);
				break;
			}
        }
		game.update();
		window.clear();
		window.draw(game);
		window.display();

    }
}
