#pragma once
#include "aitank.h"
#include <iostream>
#include "CellManager.h"
#include "CellMap.h"
#include <algorithm>

class CWTank : public AITank
{
private:
	int m_iTimer = 100; //!< Timer.
	int m_iTimeElapsed = 0; //!< How much time has elapsed.
	bool m_bHasCollided; //!< Has the tank collided with anything.
	bool m_bEnemySeen = false; //!< Has the enemy been seen.
	bool m_bBaseSeen = false; //!< Has the base been seen.
	bool m_bFriendlyBaseSeen = false; //!< Has a friendly base been seen.
	bool m_bFire = false; //!< Has a shell been fired?
	bool m_bLOS = false; //!< Line of Sight
	int m_iAngleOfTurret = 0; //!< The angle of the turret on the tank.
	int m_iBaseAngle = 0; //!< The base angle.
	int m_iAngleDegrees = 0; //!< The turret angle in degrees.
	int m_iBaseAngleDegrees = 0; //!< The base turret angle in degrees.
	bool m_bFlag = false; //!< Flag.
	std::list<CellManager> path; //!< List of cells.
	int m_iScannedAmount = 0; //!< Amount scanned.
	std::vector<int> aiBases; //!< Enemy bases.
	int m_iDistance = 0; //!< Distance.
	int m_iXPos; //!< X position.
	sf::RectangleShape rect; //!< Rectangle.
	CellManager* currentCell; //!< Current cell.
	CellManager* targetCell; //!< Target cell/
	float m_fGetEnemyDistance = 1000; //!< Enemy distance.
public:
	CWTank(); //!< Constructor.
	~CWTank(); //!< Destructor.
	int m_iBuildingsRemain = 10; //!< How many buildings remain.
	void move(); //!< Move the tank.
	void reset(); //!< Reset the tank.
	void collided(); //!< Has the tank collided with anything.
	void turretMachine(); //!< Turret state machine.
	void moveMachine(); //!< Movement state machine.
	void aimMachine(); //!< Aiming state machine.
	void navMachine(); //!< Navigation state machine.
	void markTarget(Position p /** \param position*/); //!< Mark a target.
	void markEnemy(Position p /** \param position*/); //!< Mark an enemy.
	void markBase(Position p /** \param position*/); //!< Mark a base.
	void markShell(Position p /** \param position*/); //!< Mark a shell.
	bool isFiring(); //!< Is the tank firing?
	void score(int thisScore /** \param player Score*/,
			   int enemyScore /** \param enemy Score*/); //!< Score.
	void DrawNode(sf::RenderTarget &target /** \param target to draw the cell to*/); //!< Draw the cell.
	void setCurrentCell(); //!< Set the current cell.
	sf::RectangleShape drawRange() const { return rect; } //!< Draw the range.
	CellManager* cell; //!< Cell.
	CellMap * map; //!< Map.

};