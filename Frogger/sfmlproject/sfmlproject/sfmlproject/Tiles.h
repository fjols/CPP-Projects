#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Tiles : public sf::Drawable
{
public:
	Tiles(std::string sImage, float xPos, float yPos); //Constructor
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //Drawable draw function
	bool CollisionWithPlayer(sf::Sprite &other); //Check for collision with the player.
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

/*
The tiles class is for laying down sprites that are just for decoration.
I chose to include the water in this class as the only thing it does is reset players position. It wouldn't be worth having a whole other class for it.
*/

