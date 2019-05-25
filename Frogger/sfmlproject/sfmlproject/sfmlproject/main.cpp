#include <iostream>
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Tiles.h"
#include "Enemy.h"
#include "Log.h"
#include "Endzone.h"
#include "TextClass.h"
#include "AudioClass.h"

int main() {

	sf::RenderWindow window(sf::VideoMode(384, 800), "F R O G G E R"); //Window creation.
	//--------------------------------------------
	Player player("frogSprite.png");
	//-------------------------------------------- String is the file, x position and y position.
	//Constructors are used for setting the start position and file to used for an object.
	Tiles startArea("pavement.jpg", 0.f, 768.f);
	Tiles roadOne("road.jpg", 0.f, 704.f);
	Tiles restArea("pavement.jpg", 0.f, 672.f);
	Tiles roadTwo("road.jpg", 0.f, 608.f);
	Tiles restAreaTwo("pavement.jpg", 0.f, 576.f);
	Tiles water("water.jpg", 0.f, 448.f);
	Tiles grass("grass.jpg", 0.f, 416.f);
	//--------------------------------------------
	Enemy carsOne("carYellow.png", 416.f, 752.f, 6, true);
	Enemy carsTwo("carYellow.png", -32.f, 720.f, 6, false);
	Enemy carsThree("carYellow.png", 416.f, 654.f, 6, true);
	Enemy carsFour("carYellow.png", -32.f, 622.f, 6, false);
	//--------------------------------------------
	Log logOne("log.png", 416.f, 560.f, 2);
	Log logTwo("log.png", -32.f, 528.f, 2);
	Log logThree("log.png", 416.f, 496.f, 2);
	Log logFour("log.png ", -32.f, 464.f, 2);
	//--------------------------------------------
	Endzone endTiles("endzone.png", 32.f, 416.f, 5);
	//--------------------------------------------
	TextClass scoreText(".\\finurlig-demo\\finurlig DEMO.otf");
	TextClass scoreNumber(".\\finurlig-demo\\finurlig DEMO.otf");
	TextClass instructions(".\\finurlig-demo\\finurlig DEMO.otf");
	TextClass livesRemaining(".\\finurlig-demo\\finurlig DEMO.otf");
	TextClass livesNumber(".\\finurlig-demo\\finurlig DEMO.otf");
	//--------------------------------------------
	AudioClass jumpAudio(".\\Audio\\jump.wav");
	AudioClass loseLifeAudio(".\\Audio\\loselife.wav");
	AudioClass winAudio(".\\Audio\\win.wav");
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) { //If event is of the type keyboard
				switch (event.key.code) { //Check to see which key is pressed.
				case sf::Keyboard::Key::W: //Forward
					player.MoveUp();
					jumpAudio.PlaySound(); //Play the movement audio when key is pressed.
					if (player.getPositionY() < 416.f) { //If player is at the top of the screen turn it around.
						player.MoveDown();
					}
					break;
				case sf::Keyboard::Key::S: //Down
					player.MoveDown();
					jumpAudio.PlaySound(); //Play the movement audio when key is pressed.
					if (player.getPositionY() > 800.f) { //If the player is at the bottom of the screen turn it around.
						player.MoveUp();
					}
					break;
				case sf::Keyboard::Key::A: //Left
					player.MoveLeft();
					jumpAudio.PlaySound(); //Play the movement audio when key is pressed.
					if (player.getPositionX() < 0.f) { //If the player is at the leftmost of the screen turn it around.
						player.MoveRight();
					}
					break;
				case sf::Keyboard::Key::D: //Right
					player.MoveRight();
					jumpAudio.PlaySound(); //Play the movement audio when key is pressed.
					if (player.getPositionX() > 384.f) { //If the player is at the rightmost of the screen turn it around.
						player.MoveLeft();
					}
					break;
				}
			}
			
		}

		//----------CAR UPDATES----------- |Direction of Sprite|Right = false, Left = true|
		carsOne.Update(6, 416.f, 752.f, true);
		carsTwo.Update(6, -32.f, 720.f, false);
		carsThree.Update(6, 416.f, 654.f, true);
		carsFour.Update(6, -32.f, 622.f, false);
		//-----------CAR COLLISIONS-----------
		
		if (carsOne.CollisionWithPlayer(player.m_sprite, 6) == true) {
			player.LoseLife(window);	//When the player collides with a car, make it lose a life.
			loseLifeAudio.PlaySound();	//Play the audio file.
			livesNumber.NumberText(player.iLives, 360.f, 378.f);
		}
		if (carsTwo.CollisionWithPlayer(player.m_sprite, 6) == true) {
			player.LoseLife(window);
			loseLifeAudio.PlaySound();
			livesNumber.NumberText(player.iLives, 360.f, 378.f);
		}
		if (carsThree.CollisionWithPlayer(player.m_sprite, 6) == true) {
			player.LoseLife(window);
			loseLifeAudio.PlaySound();
			livesNumber.NumberText(player.iLives, 360.f, 378.f);
		}
		if (carsFour.CollisionWithPlayer(player.m_sprite, 6) == true) {
			player.LoseLife(window);
			loseLifeAudio.PlaySound();
			livesNumber.NumberText(player.iLives, 360.f, 378.f);
		}
		//---------LOG UPDATES-----------
		logOne.Update(2, 416, 560, true);
		logTwo.Update(2, -32.f, 528.f, false);
		logThree.Update(2, 416.f, 496.f, true);
		logFour.Update(2, -32.f, 464.f, false);

		
		if (water.CollisionWithPlayer(player.m_sprite) && logOne.CollisionWithPlayer(player.m_sprite, 2, true)	//If the player is colliding with a log and the water then nothing should happen
			|| water.CollisionWithPlayer(player.m_sprite) && logTwo.CollisionWithPlayer(player.m_sprite, 2, false)
			|| water.CollisionWithPlayer(player.m_sprite) && logThree.CollisionWithPlayer(player.m_sprite, 2, true)
			|| water.CollisionWithPlayer(player.m_sprite) && logFour.CollisionWithPlayer(player.m_sprite, 2, false)) {
			//do nothing
		}
	    else if (water.CollisionWithPlayer(player.m_sprite) && !logOne.CollisionWithPlayer(player.m_sprite, 2, true) //If the player is only colliding with the water then kill the player.
			|| water.CollisionWithPlayer(player.m_sprite) && !logTwo.CollisionWithPlayer(player.m_sprite, 2, false)
			|| water.CollisionWithPlayer(player.m_sprite) && !logThree.CollisionWithPlayer(player.m_sprite, 2, true)
			|| water.CollisionWithPlayer(player.m_sprite) && !logFour.CollisionWithPlayer(player.m_sprite, 2, false)) {
			player.setPosition(171.f, 784.f);
			livesNumber.NumberText(player.iLives, 360.f, 378.f); //
			player.LoseLife(window); //Make the player lose a life.
		}


		


		if (endTiles.CollisionWithPlayer(player.m_sprite, "frogSprite.png", 5) == true) {
			scoreNumber.NumberText(endTiles.iScore, 90.f, 378.f); //update score text
			winAudio.PlaySound(); //play the sound
		}

		scoreText.NormalText("Score", 32.f, 378.f);
		livesRemaining.NormalText("Lives Remaining: ", 200.f, 378.f);
		instructions.NormalText("MOVEMENT: \n W - FORWARD \n A - LEFT \n S - Down \n D - Right \n Code by Charlie Jenkinson \n P17178401", 32.f, 100.f);


		window.clear();
		//Road draw
		window.draw(startArea);
		window.draw(roadOne);
		window.draw(restArea);
		window.draw(roadTwo);
		window.draw(restAreaTwo);
		//Water draw
		window.draw(water);
		//Grass draw
		window.draw(grass);
		//Log draw
		window.draw(logOne);
		window.draw(logTwo);
		window.draw(logThree);
		window.draw(logFour);

		//Endzones
		window.draw(endTiles);
		//Player draw
		window.draw(player);
		//Cars draw
		window.draw(carsOne);
		window.draw(carsTwo);
		window.draw(carsThree);
		window.draw(carsFour);

		window.draw(scoreText);
		window.draw(scoreNumber);
		window.draw(instructions);
		window.draw(livesRemaining);
		window.draw(livesNumber);
		

		window.display();
	}

	return 0;
}