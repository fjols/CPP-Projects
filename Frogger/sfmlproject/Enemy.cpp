#include "Enemy.h"



Enemy::Enemy(std::string sImage, float xPos, float yPos, int iAmountOfSpr, bool LeftRight)
{
	if (!m_texture.loadFromFile(sImage)) {
		std::cout << "ERROR" << std::endl;
	}
	else {
		for (int i = 0; i < iAmountOfSpr; i++) {
			if (LeftRight)
			{
				m_enemies[i].setTexture(m_texture);
				m_enemies[i].setPosition(xPos += 160.f, yPos); //Position each of the sprites slightly further back than the last.
				m_enemies[i].setOrigin(16.f, 16.f);
				std::cout << "SPAWNED: X: " << xPos << " Y: " << yPos << std::endl;
			}
			if (LeftRight == false)
			{
				m_enemies[i].setTexture(m_texture);
				m_enemies[i].setPosition(xPos -= 160.f, yPos);
				m_enemies[i].setOrigin(16.f, 16.f);
				std::cout << "SPAWNED: X: " << xPos << " Y: " << yPos << std::endl;
			}
		}
	}
}

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (int i = 0; i < 6; i++) {
		target.draw(m_enemies[i]); //Draw each sprite
	}
}


void Enemy::Update(int iAmountOfSpr, float xPos, float yPos, bool LeftRight)
{
	for (int i = 0; i < iAmountOfSpr; i++) {
		if (LeftRight)
		{
			m_enemies[i].move(-0.050, 0); //Move each sprite
			if (m_enemies[i].getPosition().x <= 0) { //When the enemy hits right side of screen it resets position
				m_enemies[i].setPosition(xPos, yPos);
			}
		}
		if (!LeftRight)
		{
			m_enemies[i].move(0.050, 0); //Move each sprite
			m_enemies[i].setScale(-1.0f, 1.0); //Flip the sprite
			if (m_enemies[i].getPosition().x >= 384) { //When the enemy hits left side of screen it resets position
				m_enemies[i].setPosition(xPos, yPos);
			}
		}
	}
}

bool Enemy::CollisionWithPlayer(sf::Sprite &other, int iAmountOfSpr)
{
	for (int i = 0; i < iAmountOfSpr; i++) {
		if (m_enemies[i].getGlobalBounds().intersects(other.getGlobalBounds()) == true) { //If the sprite and another sprite hit each other then set the other sprites position to numbers given.
			std::cout << "[CAR] COLLISION" << std::endl;
 			other.setPosition(171.f, 784.f);
			return true;
		}
	}
}
