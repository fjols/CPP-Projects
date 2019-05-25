#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Endzone : public sf::Drawable
{
public:
	Endzone(std::string sImage, float xPos, float yPos, int iAmountOfSpr);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	bool CollisionWithPlayer(sf::Sprite &other, std::string sOtherSprite, int iAmountOfSpr);
	int iScore = 0;
private:
	sf::Sprite m_sprite[5];
	sf::Texture m_newTexture;
	sf::Texture m_texture;
};

