#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>


class EntityStats
{
public:
	//MAX
	float 	MAX_HEALTH_POSSIBLE = 10.f;
	float	MAX_DAMAGE_POSSIBLE = 10.f;
	float	MAX_ATTACK_COOLDOWN_POSSIBLE = 1.f;
	//MIN
	float 	MIN_HEALTH_POSSIBLE = 10.f;
	float	MIN_DAMAGE_POSSIBLE = 1.f;
	float	MIN_ATTACK_COOLDOWN_POSSIBLE = 0.5f;
};


class Entity : public sf::Drawable
{
private:
	/*RANDOM VALUES MIN AND MAX*/
	std::default_random_engine gen;
	
	EntityStats				&m_stats;
	
	//atributes
	float					m_health;
	float					m_damage;
	float					attackCooldownSeconds;
	float					ATTACK_COOLDOWN;
	float					HEALTH;

	//entity info
	int					m_side;
	sf::RectangleShape	m_shape;
	sf::RectangleShape	m_healthbar;

	//states
	bool					m_alive;
	bool					m_Attacked;
public:
	Entity(EntityStats &stats);
	~Entity();

	//inits
	bool	initEntity(sf::Vector2f windowSize, int side);

	//modifiers
	void	setAttacked(bool setState);

	//Accesors
	const bool					&getAttacked();
	const bool					&getAlive();
	const sf::RectangleShape	&getShape();

	//Functions
	void	move(const float &dt);
	void	attack(Entity &attackTarget, const float &dt);
	void	hit(int damage);



	
	void	draw(sf::RenderTarget &target, sf::RenderStates states) const;

};

