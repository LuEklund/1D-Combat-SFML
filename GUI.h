#pragma once

#include "SFML/Graphics.hpp"
#include "Entity.h"
#include <iostream>
#include <sstream>
#include <iomanip>

class EntityStats;
class GUI : public sf::Drawable
{
private:
	sf::Vector2f		*m_windowSize;
	sf::Font			m_font;
	EntityStats			&m_PlayerStats;
	EntityStats			&m_AIStats;

	/*UPGRADE BUTTONS*/
	sf::RectangleShape	m_HealthUpgrade;
	sf::RectangleShape	m_DamageUpgrade;
	sf::RectangleShape	m_CooldownUpgrade;
	sf::Text			m_HealthUpgradeText;
	sf::Text			m_DamageUpgradeText;
	sf::Text			m_CooldownUpgradeText;

	/*STATS DISPLAY*/
	/*Player*/
	sf::Text			m_maxMinHealth;
	sf::Text			m_maxMInDamage;
	sf::Text			m_maxMInCooldown;

	/*STATS DISPLAY*/
	/*AI*/
	sf::Text			m_AImaxMinHealth;
	sf::Text			m_AImaxMInDamage;
	sf::Text			m_AImaxMInCooldown;

	
public:
	GUI(EntityStats &player, EntityStats &AI);
	~GUI();

	//inits
	bool	initGUI(sf::Vector2f &windowSize);

	//accessors
	bool	pressedHealthUp(const sf::Vector2i &mousePos);
	bool	pressedDamageUp(const sf::Vector2i &mousePos);
	bool	pressedCooldownUP(const sf::Vector2i &mousePos);

	//Functions
	void	update(const float &dt);
	void	draw(sf::RenderTarget &target, sf::RenderStates states) const;

};



