#pragma once
#include "Menu.h"
#include "Entity.h"
#include <vector>
#include "GUI.h"



class Game : public sf::Drawable
{
enum class State
{
	PAUSED,
	PLAYING,
	GAMEOVER
};
private:
	//MENU while paused
	std::unique_ptr<Menu>	m_pMenu;
	//GUI while playing
	std::unique_ptr<GUI>	m_pGUI;
	float					m_displayGUITimer;

	//Entities
	std::vector<std::unique_ptr<Entity>>	m_pEntitysPlayer;
	std::vector<std::unique_ptr<Entity>>	m_pEntityAI;
	EntityStats								m_statsPlayer;
	EntityStats								m_statsAI;

	//AI
	float	m_AICooldownSpawn;
	float	m_AICooldownUpgrade;

	//TO be implemneted
	int						m_money;

	//sate of the game (enum class above)
	State					m_state;
	sf::Font				m_font;
	sf::Text				m_gameOverText;

	//essentials
	sf::RenderWindow		*m_pwindow;
	sf::Vector2f			m_windowsSize;
	sf::Clock				clock;
	float					dt;

	//internal functions
	int		upgradeHealth(EntityStats &stats);
	int		upgardeAttack(EntityStats &stats);
	int		upgardeAttackCooldown(EntityStats &stats);


public:
	Game(sf::RenderWindow *window);
	~Game();

	//inits
	bool	initGame();

	//functions
	void	onKeyReleased(sf::Keyboard::Key key);
	void	onMouseButtonReleased(sf::Mouse::Button button);

	void	update();
	void	draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

