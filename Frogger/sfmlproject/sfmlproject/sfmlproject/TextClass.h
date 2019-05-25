#pragma once
#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"

class TextClass : public sf::Drawable
{
public:
	TextClass(std::string sfFont); //Constructor
	std::string NormalText(std::string sString, float xPos, float yPos); //This function handles text that is not dynamic. This is just normal text that doesn't change.
	std::string NumberText(int &iScore, float xPos, float yPos); //Number text handles scores and lives, values that will change.
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //Drawable draw function
private:
	sf::Font sfFont;
	sf::Text sfText;
};

//This class handles text