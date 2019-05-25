#include "Tiles.h"



Tiles::Tiles(std::string sImage, float xPos, float yPos)
{
	if (!m_texture.loadFromFile(sImage)) {	//If texture can't be found then display error to user.
		std::cout << "ERROR" << std::endl;
	}
	else {
		m_sprite.setTexture(m_texture);
		m_sprite.setPosition(xPos, yPos); //Set the position as two floats given in the initialisation of class.
	}
}

void Tiles::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

bool Tiles::CollisionWithPlayer(sf::Sprite &other)
{
	if (m_sprite.getGlobalBounds().intersects(other.getGlobalBounds())) {	//If the sprite and another sprite hit each other then set the other sprites position to numbers given.
		return true;
	}
	else if (!m_sprite.getGlobalBounds().intersects(other.getGlobalBounds()))
	{
		return false;
	}
}
