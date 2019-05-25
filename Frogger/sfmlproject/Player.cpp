#include "Player.h"



Player::Player(std::string sImage)
{
	if (!m_texture.loadFromFile(sImage)) {	//If texture can't be found then display the error.
		std::cout << "ERROR" << std::endl;
	}
	else {
		m_sprite.setTexture(m_texture);	//Set the player texture as the texture just set.
		m_sprite.setPosition(171.f, 784.f); //Set the sprite position
		m_sprite.setOrigin(16.f, 16.f); //Set the origin, this is the point of rotation.
	}
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

void Player::MoveUp()
{
	m_sprite.move(0.f, -fSpeed);
	m_sprite.setRotation(0.f);
}

void Player::MoveDown()
{
	m_sprite.move(0.f, fSpeed);
	m_sprite.setRotation(180.f);
}

void Player::MoveLeft()
{
	m_sprite.move(-fSpeed, 0.f);
	m_sprite.setRotation(270.f);
}

void Player::MoveRight()
{
	m_sprite.move(fSpeed, 0.f);
	m_sprite.setRotation(90.f);
}


float Player::getPositionX()
{
	return m_sprite.getPosition().x;
}

float Player::getPositionY()
{
	return m_sprite.getPosition().y;
}

void Player::setPosition(float fX, float fY)
{
	m_sprite.setPosition(fX, fY);
}



int Player::LoseLife(sf::RenderWindow &window)
{
	if (iLives > 0) //Only run this code whilst the lives count is greater than 0.
	{
		iLives -= 1; //Subtract a life from the count
		if (iLives <= 0) {	//If the lives go below 0
			std::cout << "GAME OVER" << std::endl;
			window.close();//Close window when player is out of lives.
		}
		std::cout << iLives << std::endl;
	}
	return iLives;
}

int Player::returnLife()
{
	return iLives;
}
