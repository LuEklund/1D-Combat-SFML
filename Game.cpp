#include "Game.h"


//internal functions
int Game::upgradeHealth(EntityStats &stats)
{
	stats.MAX_HEALTH_POSSIBLE += 4;
	stats.MIN_HEALTH_POSSIBLE += 2;
	return 0;
}

int Game::upgardeAttack(EntityStats &stats)
{
	stats.MAX_DAMAGE_POSSIBLE += 2;
	stats.MIN_DAMAGE_POSSIBLE += 1;
	return 0;
}

int Game::upgardeAttackCooldown(EntityStats &stats)
{
	stats.MAX_ATTACK_COOLDOWN_POSSIBLE /= 1.02;
	stats.MIN_ATTACK_COOLDOWN_POSSIBLE /= 1.05;
	return 0;
}

Game::Game(sf::RenderWindow *window)
	: m_pMenu(std::make_unique<Menu>())
	, m_pGUI(std::make_unique<GUI>(m_statsPlayer, m_statsAI))
	, m_displayGUITimer(0)
	, m_state(State::PAUSED)
	, m_pwindow(window)
	, m_windowsSize(window->getSize())
	, m_AICooldownSpawn(0.f)
	, m_AICooldownUpgrade(0.f)
{
}

Game::~Game()
{
}

bool Game::initGame()
{
	if (!m_font.loadFromFile("Assets/DancingScript-Regular.ttf"))
		return false;
	if (!m_pMenu->initMenu(m_windowsSize))
		return false;
	if (!m_pGUI->initGUI(m_windowsSize))
		return false;
	
	m_gameOverText.setFont(m_font);
	m_gameOverText.setFillColor(sf::Color::Red);
	m_gameOverText.setString("GAME OVER!");
	m_gameOverText.setCharacterSize(80);
	m_gameOverText.setOrigin(m_gameOverText.getGlobalBounds().getSize() / 2.f);
	m_gameOverText.setPosition(m_windowsSize/2.f);
	return (true);
}

void Game::onKeyReleased(sf::Keyboard::Key key)
{
	if (m_state == State::PAUSED)
	{
		switch (key)
		{
		case sf::Keyboard::Up:
			m_pMenu->moveUp();
			break;
		case sf::Keyboard::Down:
			m_pMenu->moveDown();
			break;
		case sf::Keyboard::Enter:
			switch (m_pMenu->getSelected())
			{
			case 0:
				m_state = State::PLAYING;
				clock.restart();
				break;
			case 1:
				// m_state = State::PLAYING;
				break;
			case 2:
				m_pwindow->close();
				break;
			};
		}
	}
	else
	{
		switch (key)
		{
		case sf::Keyboard::Escape:
			m_state = State::PAUSED;
			break;
		case sf::Keyboard::A:
			m_pEntitysPlayer.push_back(std::make_unique<Entity>(m_statsPlayer));
			m_pEntitysPlayer[m_pEntitysPlayer.size()-1]->initEntity(m_windowsSize, 0);
			break;
		case sf::Keyboard::D:
			m_pEntityAI.push_back(std::make_unique<Entity>(m_statsAI));
			m_pEntityAI[m_pEntityAI.size()-1]->initEntity(m_windowsSize, 1);
			break;
		}
	}
}

void Game::onMouseButtonReleased(sf::Mouse::Button button)
{
	if (m_state == State::PAUSED)
	{
		if(button == sf::Mouse::Left)
		{
			if (m_pMenu->getMousePlay(sf::Mouse::getPosition(*m_pwindow)))
				m_state = State::PLAYING;
			else if (m_pMenu->getMouseOptions(sf::Mouse::getPosition(*m_pwindow)))
				std::cout << "we no have yet" << std::endl;
			else if (m_pMenu->getMouseExit(sf::Mouse::getPosition(*m_pwindow)))
				m_pwindow->close();
		}
	}
	else
	{
		if(button == sf::Mouse::Left)
		{
			if (m_pGUI->pressedHealthUp(sf::Mouse::getPosition(*m_pwindow)))
				upgradeHealth(m_statsPlayer);
			else if(m_pGUI->pressedDamageUp(sf::Mouse::getPosition(*m_pwindow)))
				upgardeAttack(m_statsPlayer);
			else if(m_pGUI->pressedCooldownUP(sf::Mouse::getPosition(*m_pwindow)))
				upgardeAttackCooldown(m_statsPlayer);
		}
	}
}


void Game::update()
{
	if (m_state == State::PLAYING)
	{
		if(m_AICooldownSpawn >= 3.f)
		{
			m_pEntityAI.push_back(std::make_unique<Entity>(m_statsAI));
			m_pEntityAI[m_pEntityAI.size()-1]->initEntity(m_windowsSize, 1);
			m_AICooldownSpawn = 0.f;
		}
		else
			m_AICooldownSpawn += dt;
		if (m_AICooldownUpgrade >= 1.f)
		{
			static std::default_random_engine gen(time(NULL)); 
			std::uniform_int_distribution<int> randomUp(0,2);
			int value = randomUp(gen);
			std::cout << "AI upgrade: " << value << std::endl;
			switch (value)
			{
			case 0:
				upgradeHealth(m_statsAI);
				break;
			case 1:
				upgardeAttack(m_statsAI);
				break;
			case 2:
				upgardeAttackCooldown(m_statsAI);
				break;
			}
			m_AICooldownUpgrade = 0.f;
		}
		else
			m_AICooldownUpgrade += dt;

		//iterate trough all player entities an attack if can else move
		for (auto itPlayer = m_pEntitysPlayer.begin(); itPlayer != m_pEntitysPlayer.end();)
		{
			if ((*itPlayer)->getAlive())
			{
				(*itPlayer)->setAttacked(false);
				for (auto itAI = m_pEntityAI.begin(); itAI != m_pEntityAI.end();)
				{
					if ((*itAI)->getAlive())
					{
						if ((*itPlayer)->getShape().getGlobalBounds().intersects(
							(*itAI)->getShape().getGlobalBounds()))
						{
							(*itPlayer)->attack(*(*itAI).get(), dt);
							(*itPlayer)->setAttacked(true);
							break ;
						}
						itAI++;
					}
					else
						itAI = m_pEntityAI.erase(itAI);
				}
				if ((*itPlayer)->getAttacked() == false)
				{
					for (auto itPlayerFriend = m_pEntitysPlayer.begin(); itPlayerFriend != m_pEntitysPlayer.end(); itPlayerFriend++)
					{
						if (itPlayerFriend == itPlayer)
							continue;
						if ((*itPlayer)->getShape().getGlobalBounds().intersects(
							(*itPlayerFriend)->getShape().getGlobalBounds())
							&& (*itPlayer)->getShape().getPosition().x < (*itPlayerFriend)->getShape().getPosition().x)
						{
							(*itPlayer)->setAttacked(true);
							break ;
						}
					}
					if ((*itPlayer)->getAttacked() == false)
					{
						(*itPlayer)->move(dt);
						if ((*itPlayer)->getShape().getPosition().x >
							m_windowsSize.x - (*itPlayer)->getShape().getSize().x)
							m_state = State::GAMEOVER;
					}
				}
				itPlayer++;
			}
			else
				itPlayer = m_pEntitysPlayer.erase(itPlayer);
		}
		//iterate trough all AI entities an attack if can else move
		for (auto itAI = m_pEntityAI.begin(); itAI != m_pEntityAI.end();)
		{
			if ((*itAI)->getAlive())
			{
				(*itAI)->setAttacked(false);
				for (auto itPlayer = m_pEntitysPlayer.begin(); itPlayer != m_pEntitysPlayer.end();)
				{
					if ((*itPlayer)->getAlive())
					{
						if ((*itAI)->getShape().getGlobalBounds().intersects(
							(*itPlayer)->getShape().getGlobalBounds()))
						{
							(*itAI)->attack(*(*itPlayer).get(), dt);
							(*itAI)->setAttacked(true);
							break ;
						}
						itPlayer++;
					}
					else
						itPlayer = m_pEntitysPlayer.erase(itPlayer);
				}
				if ((*itAI)->getAttacked() == false)
				{
					for (auto itAIFriend = m_pEntityAI.begin(); itAIFriend != m_pEntityAI.end(); itAIFriend++)
					{
						if (itAIFriend == itAI)
							continue;
						if ((*itAI)->getShape().getGlobalBounds().intersects(
							(*itAIFriend)->getShape().getGlobalBounds())
							&& (*itAI)->getShape().getPosition().x > (*itAIFriend)->getShape().getPosition().x)
						{
							(*itAI)->setAttacked(true);
							break ;
						}
					}
					if ((*itAI)->getAttacked() == false)
					{
						(*itAI)->move(dt);
						if ((*itAI)->getShape().getPosition().x < 0)
							m_state = State::GAMEOVER;
					}
				}
				itAI++;
			}
			else
				itAI = m_pEntityAI.erase(itAI);
		}
		if (m_displayGUITimer > 1.f)
		{
			m_pGUI->update(dt);
			m_displayGUITimer = 0;
		}
		else
			m_displayGUITimer += dt;
	}
	else if (m_state == State::PAUSED)
	{
		m_pMenu->update(sf::Mouse::getPosition(*m_pwindow));
	}
	dt = clock.restart().asSeconds();
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	switch (m_state)
	{
	case State::PAUSED:
		target.draw(*m_pMenu.get());
		break;
	case State::PLAYING:
		for (auto &ent : m_pEntitysPlayer)
		{
			target.draw(*ent.get());
		}
		for (auto &ent : m_pEntityAI)
		{
			target.draw(*ent.get());
		}
		target.draw(*m_pGUI.get());
		break;
	case State::GAMEOVER:
		target.draw(m_gameOverText);
	break;
	}
}
