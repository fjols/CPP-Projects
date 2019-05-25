#include "TextClass.h"



TextClass::TextClass(std::string sFont) //Give constructor a font to use.
{
	if (!sfFont.loadFromFile(sFont)) {	//If it can't find the font display an error.
		std::cout << "Error" << std::endl;
	}
	else {
		sfText.setFont(sfFont); //Similar to setting a texture to a sprite. But with text and fonts instead
	}
}

std::string TextClass::NormalText(std::string sString, float xPos, float yPos)	//This function if for generic text. No changing numbers involved.
{
	sfText.setString(sString); //Set the text to a given string
	sfText.setPosition(xPos, yPos); //Set the position of the text
	sfText.setCharacterSize(24); //Set the size
	return sString;
}

std::string TextClass::NumberText(int &iScore, float xPos, float yPos)	//This is for changing number text.
{
	sfText.setString(std::to_string(iScore));	//Convert the integer value to a string.
	sfText.setPosition(xPos, yPos);
	sfText.setCharacterSize(24);	//Set size of text
	return std::string();
}

void TextClass::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sfText);
}


