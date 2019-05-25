#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Log : public sf::Drawable
{
public:
	Log(std::string sImage, float xPos, float yPos, int iAmountOfSpr); //Constructor
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //Drawable draw function
	void Update(int iAmountOfSpr, float xPos, float yPos, bool bDirection); //Update function - makes logs move
	bool CollisionWithPlayer(sf::Sprite &other, int iAmountOfSpr, bool bDirection); //Checks for collision with another sprite. In this case its always going to be player.
private:
	sf::Texture m_texture;
	sf::Sprite m_logs[2]; //Array of logs. Number in array is how many logs will spawn.
};

//Log will move player along with it