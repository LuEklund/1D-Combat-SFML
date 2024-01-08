#include "Entity.h"
Entity::Entity(EntityStats &stats)
	: m_stats(stats)
{
}

Entity::~Entity()
{
}

bool Entity::initEntity(sf::Vector2f windowSize, int side)
{
	//inits our RNG generator
	std::default_random_engine gen(time(NULL)); 

	//init the entity health between MIN_HEALTH and MAX_HEALTH
	std::uniform_real_distribution<float> health_val(
		m_stats.MIN_HEALTH_POSSIBLE,
		m_stats.MAX_HEALTH_POSSIBLE); 
	m_health = static_cast<float>(static_cast<int>(health_val(gen)));
	HEALTH = m_health;

	//init the entity damage between MIN_DAMAGE and MAX_DAMAGE
	std::uniform_real_distribution<float> distribution(
		m_stats.MIN_DAMAGE_POSSIBLE,
		m_stats.MAX_DAMAGE_POSSIBLE);
	m_damage = static_cast<float>(static_cast<int>(distribution(gen)));

	//init the entity damage between MIN_DAMAGE and MAX_DAMAGE
	std::uniform_real_distribution<float> distributio1n(
		m_stats.MIN_ATTACK_COOLDOWN_POSSIBLE,
		m_stats.MAX_ATTACK_COOLDOWN_POSSIBLE);
	attackCooldownSeconds = distributio1n(gen);
	ATTACK_COOLDOWN = attackCooldownSeconds;



	m_side = side;

	std::cout << "spawne an entity with values HP: " << m_health
	<< ", Damage: " << m_damage
	<< ", ACD: " << attackCooldownSeconds << std::endl;


	m_alive = true;
	m_Attacked = false;
	m_shape.setFillColor(sf::Color::White);
	m_shape.setSize(sf::Vector2f(50.f,50.f));
	m_shape.setOutlineColor(sf::Color::Green);
	m_shape.setOutlineThickness(1.f);

	m_healthbar.setSize(sf::Vector2f(50.f,5.f));


	if (side)
		m_shape.setPosition(windowSize.x - m_shape.getSize().x, windowSize.y/2);
	else
		m_shape.setPosition(0.f, windowSize.y/2);
	m_healthbar.setPosition(m_shape.getPosition().x, (m_shape.getPosition().y -10.f));
	return (true);
}

//modifiers
void Entity::setAttacked(bool setState)
{
	m_Attacked = setState;
}

const bool &Entity::getAttacked()
{
	return (m_Attacked);
}

const bool &Entity::getAlive()
{
	return(m_alive);
}

const sf::RectangleShape &Entity::getShape()
{
	return(m_shape);
}

void Entity::move(const float &dt)
{
	if (m_side)
		m_shape.move(-100.f * dt, 0.f);
	else
		m_shape.move(100.f * dt, 0.f);
	m_healthbar.setPosition(m_shape.getPosition().x, (m_shape.getPosition().y - 10.f));
}

void Entity::attack(Entity &attackTarget, const float &dt)
{
	if (attackCooldownSeconds <= 0)
	{
		if(m_alive)
			attackTarget.hit(m_damage);
		attackCooldownSeconds = ATTACK_COOLDOWN;
	}
	else
		attackCooldownSeconds -= dt;

}

void Entity::hit(int damage)
{
	m_health -= damage;
	m_healthbar.setScale((m_health/HEALTH), 1.f);
	if (m_health <= 0)
		m_alive = false;

}



void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (m_alive)
	{
		target.draw(m_shape);
		target.draw(m_healthbar);
	}
}
