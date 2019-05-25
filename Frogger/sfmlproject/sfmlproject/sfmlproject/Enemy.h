#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Enemy : public sf::Drawable
{
public:
	Enemy();
	Enemy(std::string sImage, float xPos, float yPos, int iAmountOfSpr, bool LeftRight);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void Update(int iAmountOfSpr, float xPos, float yPos, bool LeftRight);
	bool CollisionWithPlayer(sf::Sprite &other, int iAmountOfSpr);

private:
	sf::Texture m_texture;
	sf::Sprite m_enemies[6];
	bool bLeftRight; //true is left, false is right
	//int iAmountOfSprites = 6;
};

