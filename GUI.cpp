#include "GUI.h"


GUI::GUI(EntityStats &player, EntityStats &AI)
	: m_PlayerStats(player)
	, m_AIStats(AI)
{
}

GUI::~GUI()
{
}

bool GUI::initGUI(sf::Vector2f &windowSize)
{
	m_windowSize = &windowSize;
	if (!m_font.loadFromFile("Assets/DancingScript-Bold.ttf"))
	{
		std::cout << "Falied to load font!" << std::endl;
		return false;
	}

	/*HEALTH UPGARDE set-up*/
	m_HealthUpgrade.setFillColor(sf::Color::Magenta);
	m_HealthUpgrade.setSize(sf::Vector2f(220.f, 30.f));
	m_HealthUpgrade.setPosition(
		(windowSize.x / 4) * 1 - m_HealthUpgrade.getSize().x / 2,
		windowSize.y - (m_HealthUpgrade.getSize().y * 2));
		//TEXT
	m_HealthUpgradeText.setFont(m_font);
	m_HealthUpgradeText.setCharacterSize(20);
	m_HealthUpgradeText.setFillColor(sf::Color::White);
	m_HealthUpgradeText.setPosition(50.f,50.f);
	m_HealthUpgradeText.setString("UPGRADE HEALTH");
	m_HealthUpgradeText.setPosition(
		(m_HealthUpgrade.getPosition().x
		+ m_HealthUpgrade.getGlobalBounds().width/2.f
		- m_HealthUpgradeText.getGlobalBounds().width/2.f),
		m_HealthUpgrade.getPosition().y);


	/*DAMAGE UPGARDE set-up*/
	m_DamageUpgrade.setFillColor(sf::Color::Magenta);
	m_DamageUpgrade.setSize(sf::Vector2f(220.f, 30.f));
	m_DamageUpgrade.setPosition(
		(windowSize.x / 4) * 2 - m_DamageUpgrade.getSize().x / 2,
		windowSize.y - (m_DamageUpgrade.getSize().y * 2));
		//TEXT
	m_DamageUpgradeText.setFont(m_font);
	m_DamageUpgradeText.setCharacterSize(20);
	m_DamageUpgradeText.setFillColor(sf::Color::White);
	m_DamageUpgradeText.setString("UPGRADE DAMAGE");
	m_DamageUpgradeText.setPosition(
		(m_DamageUpgrade.getPosition().x
		+ m_DamageUpgrade.getGlobalBounds().width/2.f
		- m_DamageUpgradeText.getGlobalBounds().width/2.f),
		m_DamageUpgrade.getPosition().y);

	/*COOLDOWN UPGARDE set-up*/
	m_CooldownUpgrade.setFillColor(sf::Color::Magenta);
	m_CooldownUpgrade.setSize(sf::Vector2f(220.f, 30.f));
	m_CooldownUpgrade.setPosition(
		(windowSize.x / 4) * 3 - m_CooldownUpgrade.getSize().x / 2,
		windowSize.y - (m_CooldownUpgrade.getSize().y * 2));
		//TEXT
	m_CooldownUpgradeText.setFont(m_font);
	m_CooldownUpgradeText.setCharacterSize(20);
	m_CooldownUpgradeText.setFillColor(sf::Color::White);
	m_CooldownUpgradeText.setString("UPGRADE COOLDOWN");
	m_CooldownUpgradeText.setPosition(
		(m_CooldownUpgrade.getPosition().x
		+ m_CooldownUpgrade.getGlobalBounds().width/2.f
		- m_CooldownUpgradeText.getGlobalBounds().width/2.f),
		m_CooldownUpgrade.getPosition().y);

	//Player stats
	m_maxMinHealth.setFont(m_font);
	m_maxMinHealth.setCharacterSize(20);
	m_maxMinHealth.setFillColor(sf::Color::White);
	m_maxMinHealth.setString("HEALTH: 1-10");
	m_maxMinHealth.setPosition(0.f,0.f);

	m_maxMInDamage.setFont(m_font);
	m_maxMInDamage.setCharacterSize(20);
	m_maxMInDamage.setFillColor(sf::Color::White);
	m_maxMInDamage.setString("DAMAGE: 1-10");
	m_maxMInDamage.setPosition(0.f,20.f);

	m_maxMInCooldown.setFont(m_font);
	m_maxMInCooldown.setCharacterSize(20);
	m_maxMInCooldown.setFillColor(sf::Color::White);
	m_maxMInCooldown.setString("COOLDOWN: 1-10");
	m_maxMInCooldown.setPosition(0.f,40.f);


	//AI stats
	m_AImaxMinHealth.setFont(m_font);
	m_AImaxMinHealth.setCharacterSize(20);
	m_AImaxMinHealth.setFillColor(sf::Color::White);
	m_AImaxMinHealth.setString("1-10 :HEALTH");
	m_AImaxMinHealth.setPosition(
		windowSize.x - m_AImaxMinHealth.getGlobalBounds().width - 5.f,0.f);

	m_AImaxMInDamage.setFont(m_font);
	m_AImaxMInDamage.setCharacterSize(20);
	m_AImaxMInDamage.setFillColor(sf::Color::White);
	m_AImaxMInDamage.setString("1-10 :DAMAGE");
	m_AImaxMInDamage.setPosition(
		windowSize.x - m_AImaxMinHealth.getGlobalBounds().width - 5.f, 20.f);

	m_AImaxMInCooldown.setFont(m_font);
	m_AImaxMInCooldown.setCharacterSize(20);
	m_AImaxMInCooldown.setFillColor(sf::Color::White);
	m_AImaxMInCooldown.setString("1-10 :COOLDOWN");
	m_AImaxMInCooldown.setPosition(
		windowSize.x - m_AImaxMinHealth.getGlobalBounds().width - 5.f, 40.f);
	
	return true;
}

bool GUI::pressedHealthUp(const sf::Vector2i &mousePos)
{
	if(m_HealthUpgrade.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
		return (true);
	return (false);
}

bool GUI::pressedDamageUp(const sf::Vector2i &mousePos)
{
	if(m_DamageUpgrade.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
		return (true);
	return (false);
}

bool GUI::pressedCooldownUP(const sf::Vector2i &mousePos)
{
	if(m_CooldownUpgrade.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
		return (true);
	return (false);
}

void GUI::update(const float &dt)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2);

	//Player stats update
	ss << "HEALTH: "
		<< m_PlayerStats.MIN_HEALTH_POSSIBLE
		<< "-" << m_PlayerStats.MAX_HEALTH_POSSIBLE;
	m_maxMinHealth.setString(ss.str());
	ss.str(std::string());
	ss.clear();

	ss << "DAMAGE: "
		<< m_PlayerStats.MIN_DAMAGE_POSSIBLE
		<< "-" << m_PlayerStats.MAX_DAMAGE_POSSIBLE;
	m_maxMInDamage.setString(ss.str());
	ss.str(std::string());
	ss.clear();

	ss << "COOLDOWN: "
		<< m_PlayerStats.MIN_ATTACK_COOLDOWN_POSSIBLE
		<< "-" << m_PlayerStats.MAX_ATTACK_COOLDOWN_POSSIBLE;
	m_maxMInCooldown.setString(ss.str());
	ss.str(std::string());
	ss.clear();

	//AI stats update / BTW we reset the postion for AI text! to keep it aligned right
	ss << "HEALTH: "
		<< m_AIStats.MIN_HEALTH_POSSIBLE
		<< "-" << m_AIStats.MAX_HEALTH_POSSIBLE;
	m_AImaxMinHealth.setString(ss.str());
	m_AImaxMinHealth.setPosition(
		m_windowSize->x - m_AImaxMinHealth.getGlobalBounds().width - 5.f,0.f);
	ss.str(std::string());
	ss.clear();

	ss << "DAMAGE: "
		<< m_AIStats.MIN_DAMAGE_POSSIBLE
		<< "-" << m_AIStats.MAX_DAMAGE_POSSIBLE;
	m_AImaxMInDamage.setString(ss.str());
	m_AImaxMInDamage.setPosition(
		m_windowSize->x - m_AImaxMInDamage.getGlobalBounds().width - 5.f,20.f);
	ss.str(std::string());
	ss.clear();

	ss << "COOLDOWN: "
		<< m_AIStats.MIN_ATTACK_COOLDOWN_POSSIBLE
		<< "-" << m_AIStats.MAX_ATTACK_COOLDOWN_POSSIBLE;
	m_AImaxMInCooldown.setString(ss.str());
	m_AImaxMInCooldown.setPosition(
		m_windowSize->x - m_AImaxMInCooldown.getGlobalBounds().width - 5.f,40.f);

}

void GUI::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_HealthUpgrade);
	target.draw(m_HealthUpgradeText);

	target.draw(m_DamageUpgrade);
	target.draw(m_DamageUpgradeText);

	target.draw(m_CooldownUpgrade);
	target.draw(m_CooldownUpgradeText);

	target.draw(m_maxMinHealth);
	target.draw(m_maxMInDamage);
	target.draw(m_maxMInCooldown);

	target.draw(m_AImaxMinHealth);
	target.draw(m_AImaxMInDamage);
	target.draw(m_AImaxMInCooldown);


}
