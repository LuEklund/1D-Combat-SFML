#include "Menu.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

//inits
bool Menu::initMenu(sf::Vector2f windowSize)
{
	if (!m_font.loadFromFile("Assets/DancingScript-Regular.ttf"))
	{
		std::cout << "Falied to load font!" << std::endl;
		return false;
	}

	//gives each option in the menu default values
	for (int i = 0; i < MAX_ELEMENTS; i++)
	{
		m_menu[i].setFont(m_font);
		m_menu[i].setFillColor(sf::Color::White);
		m_menu[i].setCharacterSize(40);
		//segments them out evenly
		m_menu[i].setPosition(sf::Vector2f(windowSize.x/2, windowSize.y/(MAX_ELEMENTS + 1) * (i + 1)));
	}
	//gives text to each option
	m_menu[0].setString("PLAY!");
	m_menu[1].setString("Options");
	m_menu[2].setString("Exit");

	//highlight the first option index 0 (Play)
	m_menuSelect = 0;
	m_menu[m_menuSelect].setFillColor(sf::Color::Red);

	return true;
}

//Accesors
int Menu::getSelected()
{
	return (m_menuSelect);
}

bool Menu::getMousePlay(const sf::Vector2i &mousePos)
{
	if(m_menu[0].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
		return(true);
	return false;
}

bool Menu::getMouseOptions(const sf::Vector2i &mousePos)
{
	if(m_menu[1].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
		return(true);
	return false;
}

bool Menu::getMouseExit(const sf::Vector2i &mousePos)
{
	if(m_menu[2].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
		return(true);
	return false;
}

//Functions
void Menu::moveUp()
{
	m_menu[m_menuSelect].setFillColor(sf::Color::White);
	m_menuSelect--;
	if (m_menuSelect < 0)
		m_menuSelect = MAX_ELEMENTS - 1;
	m_menu[m_menuSelect].setFillColor(sf::Color::Red);
}

void Menu::update(const sf::Vector2i &mousePos)
{
	if (getMousePlay(mousePos))
	{
		m_menu[m_menuSelect].setFillColor(sf::Color::White);
		m_menuSelect = 0;
		m_menu[m_menuSelect].setFillColor(sf::Color::Red);
	}
	else if (getMouseOptions(mousePos))
	{
		m_menu[m_menuSelect].setFillColor(sf::Color::White);
		m_menuSelect = 1;
		m_menu[m_menuSelect].setFillColor(sf::Color::Red);
	}
	else if (getMouseExit(mousePos))
	{
		m_menu[m_menuSelect].setFillColor(sf::Color::White);
		m_menuSelect = 2;
		m_menu[m_menuSelect].setFillColor(sf::Color::Red);
	}
}

void Menu::moveDown()
{
	m_menu[m_menuSelect].setFillColor(sf::Color::White);
	m_menuSelect++;
	if (m_menuSelect > MAX_ELEMENTS - 1)
		m_menuSelect = 0;
	m_menu[m_menuSelect].setFillColor(sf::Color::Red);
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (int i = 0; i < MAX_ELEMENTS; i++)
	{
		target.draw(m_menu[i]);
	}
}
