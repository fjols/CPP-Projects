#include "Endzone.h"



Endzone::Endzone(std::string sImage, float xPos, float yPos, int iAmountOfSpr)
{
	if (!m_texture.loadFromFile(sImage)) {
		std::cout << "Error" << std::endl;
	}
	else {
		for (int i = 0; i < iAmountOfSpr; i++) {
			m_sprite[i].setTexture(m_texture);
			m_sprite[i].setPosition(xPos += 64, yPos); //Add an offset to make the tiles spaced out.
		}
	}
}

void Endzone::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < 5; i++) {
		target.draw(m_sprite[i]);
	}
}


bool Endzone::CollisionWithPlayer(sf::Sprite &other, std::string sOtherImage, int iAmountOfSpr) 
{

	for (int i = 0; i < iAmountOfSpr; i++) {
		if (m_sprite[i].getGlobalBounds().intersects(other.getGlobalBounds())) {	//If the sprite and another sprite hit each other then set the other sprites position to numbers given.
			m_newTexture.loadFromFile(sOtherImage);
			m_sprite[i].setTexture(m_newTexture); //Set the end tile sprite to the frog sprite.
			other.setPosition(171.f, 784.f);
			iScore += 1;
			std::cout << iScore << ": SCORE" << std::endl;
			if (iScore == 5) //If score is 5 then the player wins
				std::cout << "WINNER" << std::endl;
			return true;
		}
	}
}
