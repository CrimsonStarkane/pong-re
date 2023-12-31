#include "World.h"
#include "Hud.h"
#include "Constants.h"

void World::init()
{
	m_LeftPaddle.init(Paddle::Side::LEFT, *this);
	m_LeftPaddle.setPosition(Paddle::GUTTER, VIRTUAL_SIZE.y - m_LeftPaddle.getSize().y - Paddle::V_GAP);

	m_RightPaddle.init(Paddle::Side::RIGHT, *this);
	m_RightPaddle.setPosition(VIRTUAL_SIZE.x - Paddle::GUTTER - m_RightPaddle.getSize().x, Paddle::V_GAP);

	m_Ball.init(sf::Vector2f(40, 40), *this);
	m_Ball.setPosition(
		VIRTUAL_SIZE.x / 2 - m_Ball.getSize().x / 2,
		VIRTUAL_SIZE.y / 2 - m_Ball.getSize().y / 2
	);
}

void World::process(const sf::Event event)
{
	m_LeftPaddle.process(event);
	m_RightPaddle.process(event);
}

void World::update(const sf::Time& dt, Hud& hud)
{
	if (state == PLAY || state == SCORED)
	{
		m_LeftPaddle.update(dt, m_Ball);
		m_RightPaddle.update(dt, m_Ball);
	}

	if (state == PLAY) m_Ball.update(dt, hud);
}

void World::render(sf::RenderWindow& window)
{
	window.draw(m_LeftPaddle);
	window.draw(m_RightPaddle);
	if (state != MENU && state != GAME_OVER && state != SCORED) window.draw(m_Ball);
}

void World::resetPaddles()
{
	m_LeftPaddle.setPosition(Paddle::GUTTER, VIRTUAL_SIZE.y - m_LeftPaddle.getSize().y - Paddle::V_GAP);
	m_RightPaddle.setPosition(VIRTUAL_SIZE.x - Paddle::GUTTER - m_RightPaddle.getSize().x, Paddle::V_GAP);
}