#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Player : public sf::Drawable
{
public:
	Player(std::string sImage);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//MOVEMENT METHODS------
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	//----------------------
	float getPositionX(); //Returns the players x position
	float getPositionY(); //Returns the players y position
	void setPosition(float fX, float fY); //Sets the position of the player.

	int LoseLife(sf::RenderWindow &window); //Makes the player lose a life
	int returnLife(); //Returns the amount of lifes left
	sf::Sprite m_sprite;
	int iLives = 3; //amount of lives


private:
	sf::Texture m_texture;
	float fSpeed = 32.f;
};

