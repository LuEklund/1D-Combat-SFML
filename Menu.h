#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class Menu : public sf::Drawable
{

private:
	static const int	MAX_ELEMENTS = 3;
	int					m_menuSelect;
	sf::Font			m_font;
	sf::Text			m_menu[MAX_ELEMENTS];

public:
	Menu();
	~Menu();

	//inits
	bool	initMenu(sf::Vector2f windowSize);

	//Accesors
	int		getSelected();
	bool	getMousePlay(const sf::Vector2i &mousePos);
	bool	getMouseOptions(const sf::Vector2i &mousePos);
	bool	getMouseExit(const sf::Vector2i &mousePos);

	//Functions
	void	update(const sf::Vector2i &mousePos);
	void	moveDown();
	void	moveUp();

	void	draw(sf::RenderTarget &target, sf::RenderStates states) const;

};

