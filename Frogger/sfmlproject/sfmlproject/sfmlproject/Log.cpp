#include "Log.h"



Log::Log(std::string sImage, float xPos, float yPos, int iAmountOfSpr)
{
	if (!m_texture.loadFromFile(sImage)) {
		std::cout << "Error" << std::endl;
	}
	else {
		for (int i = 0; i < iAmountOfSpr; i++) {
			m_logs[i].setTexture(m_texture);
			m_logs[i].setPosition(xPos += 128.f, yPos); //Position each of the sprites slightly further back than the last.
			m_logs[i].setOrigin(16.f, 16.f);
			std::cout << "[LOG] SPAWNED: X: " << xPos << " Y: " << yPos << std::endl;
		}
	}
}

void Log::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < 2; i++) {
		target.draw(m_logs[i]); //Draw each of the logs
	}
}


void Log::Update(int iAmountOfSpr, float xPos, float yPos, bool bDirection)
{
	for (int i = 0; i < iAmountOfSpr; i++) { //This makes the logs go right to left
		if (bDirection) {
			m_logs[i].move(-0.050f, 0.f);
			if (m_logs[i].getPosition().x <= 0) { //When the enemy hits right side of screen it resets position
				m_logs[i].setPosition(xPos, yPos);
			}
		}
		if (bDirection == false) { //this makes the logs go left to right
			m_logs[i].move(0.050f, 0.f);
			if (m_logs[i].getPosition().x >= 384) {
				m_logs[i].setPosition(xPos, yPos);
			}
		}
	}
}
//Doesnt work because i am not intersecting with every log so it thinks im in water

bool Log::CollisionWithPlayer(sf::Sprite &other, int iAmountOfSpr, bool bDirection) //bDirection | Right = false, Left = true
{
	for (int i = 0; i < iAmountOfSpr; i++) {	//For loop to iterate through all the logs
		
		//INSANELY UGLY SOLUTION
		//Iterate through EVERY log in the lane. I had to do this as my other solution would check if the player was on every log, however it wasnt so it would always return false and kill the player.
		//bDirection determines the direction of each lane.
			if (m_logs[0].getGlobalBounds().intersects(other.getGlobalBounds()) && bDirection || m_logs[1].getGlobalBounds().intersects(other.getGlobalBounds()) && bDirection
				|| m_logs[2].getGlobalBounds().intersects(other.getGlobalBounds()) && bDirection) { //if player and log intersect
				other.move(-0.050f, 0);	//move player to the left
				return true;	//return true;
			}
			else if (!m_logs[0].getGlobalBounds().intersects(other.getGlobalBounds()) && bDirection || !m_logs[1].getGlobalBounds().intersects(other.getGlobalBounds()) && bDirection
				|| !m_logs[1].getGlobalBounds().intersects(other.getGlobalBounds()) && bDirection) { //if player and log do not intersect
				return false;	//return false
			}
			

			if (m_logs[0].getGlobalBounds().intersects(other.getGlobalBounds()) && !bDirection || m_logs[1].getGlobalBounds().intersects(other.getGlobalBounds()) && !bDirection ||
				m_logs[2].getGlobalBounds().intersects(other.getGlobalBounds()) && !bDirection) { //if player and log intersect
				other.move(0.050f, 0); //move player right
				return true; //return true;
			}
			else if (!m_logs[0].getGlobalBounds().intersects(other.getGlobalBounds()) && !bDirection || !m_logs[1].getGlobalBounds().intersects(other.getGlobalBounds()) && !bDirection
				|| !m_logs[2].getGlobalBounds().intersects(other.getGlobalBounds()) && !bDirection) { //if player and log do not intersect
				return false;	//return false
			}
			

	}
}



