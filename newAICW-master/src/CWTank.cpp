#include "..\include\CWTank.h"

CWTank::CWTank()
{
	map = new CellMap(); // Make a new map.
	clearMovement(); // Clear the movement.
}

CWTank::~CWTank()
{
}

//! Function to check for movement
/*!
\param  Set the size of the rectangle.
\param  Set the position of the rectangle.
\param  Set the colour.
\param If a friendly base has been seen then set the colour.
\param Set the rotation
\param  Run the state machines.

*/
void CWTank::move()
{
	rect.setSize(sf::Vector2f(200, 10)); 
	rect.setPosition(sf::Vector2f(getX(), getY()));
	rect.setFillColor(sf::Color(0, 255, 0, 50)); 
	if (m_bFriendlyBaseSeen == true) rect.setFillColor(sf::Color(255, 0, 0, 50)); 
	rect.setRotation(turretTh); 
	setCurrentCell(); 
	

	turretMachine(); 
	aimMachine(); 
	navMachine();
	moveMachine(); 
}


//! Function to check for movement
/*!
\param  Clear the path.
\param  Set the position of the rectangle.
\param  Set the colour.
\param If a friendly base has been seen then set the colour.
\param Set the rotation
\param  Run the state machines.

*/

void CWTank::reset()
{
	path.clear(); // Clear the path.
	m_bFlag = false; // Flag is false.
}

void CWTank::collided()
{
}

void CWTank::turretMachine()
{
	// State machine values.
	const int IDLE = 0;
	const int FIRING = 1;
	int state = IDLE; // Original state is idle.

	// If the enemy has been seen or the base has been seen and the tank has ammo and has a line of sight and can't see a friendly base.
	if ((m_bEnemySeen == true || m_bBaseSeen == true) && hasAmmo() && m_bLOS == true && m_bFriendlyBaseSeen == false)
	{
		state = FIRING; // Fire the shell.
	}
	else {
		m_bFire = false; // Not firing.
		state = IDLE; // Idle.
	}
	switch (state)
	{
	case IDLE: return; break;
	case FIRING: {
		m_iScannedAmount = 0; // Get the scanned amount.
		m_bFire = true; // Firing is true.
		m_bEnemySeen = false; // Cannot see an enemy.
		m_bBaseSeen = false; // Cannot see a base.
		m_bLOS = false; // Does not have a line of sight.
	} break;
	}
}

void CWTank::moveMachine()
{
	// State machine values.
	const int IDLE = 0;
	const int MOVE = 1;
	const int ROTATE = 2;
	int state = IDLE; // Original state is Idle.

	std::string states[3] = { // An array that holds the states availible.
		"IDLE",
		"MOVE",
		"ROTATE"
	};

	if (path.size() != 0) // If the path size isn't 0.
	{
		targetCell = &path.front(); // Target cell set to the front of the path list.
		// If the target call column is equal to the current cell column AND the target cell row is equal to the current cells row.
		if (targetCell->m_iColumn == currentCell->m_iColumn && targetCell->m_iRow == currentCell->m_iRow) {
			path.pop_front(); // Pop the front off the path list.
			if (path.size() != 0) { // If the path size isn't 0.
				targetCell = &path.front(); // Target cell is the front of the path list.
			}
		}
	}

	float fDeltaX = getX() - targetCell->getX(); // Delta X is the X value subtracted by the target cell's X value.
	float fDeltaY = getY() - targetCell->getY(); // Delta Y is the Y value subtracted by the target cell's Y value.
	m_iAngleDegrees = atan2(fDeltaY, fDeltaX) * 180 / PI; // The angle in degrees is atan2 of the delta values * 180 and divided by PI.
	float fNeededAngle = m_iAngleDegrees + 180; // The needed angle is the angle + 180.
	float fRotation = pos.getTh(); // The rotation is the position theta.
	float fDeltaR = fRotation - fNeededAngle; // The delta rotation is the rotation minus the needed angle.

	int distanceThreshold = 5; // Distance Threshold.
	int directionThreshold = 5; // Direction Threshold.
	bool facingDir = (fDeltaR < directionThreshold && fDeltaR > -directionThreshold); // The direction facing should be the delta rotation less than the dir threshold and the delta rotation greater than the inverse value of the dir threshold.
	bool atLocation = (path.size() == 0); // The location should be the size of the path equal to 0.
	int dir; // Direction.

	if (state == IDLE) { // If the state is idle
		if (facingDir && !atLocation) // If the facing direction is true and the location isn't true.
			state = MOVE; // Set the state to move.
		else if (!facingDir && !atLocation) // If the facing direction isn't true and the location isn't true.
			state = ROTATE; // Set the state to rotate.
		else
			m_iScannedAmount++; // Increment the scanned amount.
	}
	else if (state == MOVE) { // If the state is set to move
		if (atLocation) // If the location is true.
			state = IDLE; // Set the state to idle.
	}
	else if (state == ROTATE) // If the state is set to rotate.
	{
		if (facingDir) // If the facing direction is true.
			state = MOVE; // Set the state to move.
	}

	switch (state)
	{
	case IDLE: {stop(); } break;
	case MOVE: goForward(); break; // Go forward.
	case ROTATE: {
		if (fDeltaR > 1 && fDeltaR < 180) // If the delta rotation is greater than 1 and less than 180.
			goLeft(); // Rotate left.
		else if (fDeltaR < -1 && fDeltaR > -180) // If the delta rotation is less than -1 and greater than -180.
			goRight(); // Rotate right.
		else if (fDeltaR > 180) // If the delta rotation is greater than 180.
			goRight(); // Rotate right.
		else if (fDeltaR < -180) // If the delta rotation is less than -180.
			goLeft(); // Rotate left.
	}break;
	} 

}

void CWTank::aimMachine()
{
	// State machine values.
	const int SCAN = 0;
	const int AIM = 1;
	int scanningState = SCAN; // Original state is scan.

	if (scanningState == SCAN && m_bFriendlyBaseSeen == false) { // If the state is scan and the friendly base has been seen.
		if (m_bEnemySeen == true) { // If the enemy base has been seen.
			scanningState = AIM; // State is set to aim.
		}
		else if (m_bBaseSeen == true) // If the base has been seen.
		{
			scanningState = AIM; // State is set to aim.
		}
	}
	// If the state is Aim and the enemy hasnt been seen and the base seen is false and the friendly base has been seen.
	if (scanningState == AIM && (m_bEnemySeen == false || m_bBaseSeen == false) && m_bFriendlyBaseSeen == true) {
		scanningState == SCAN; // Set the state to scan.
	}
	if (scanningState == AIM && m_bFriendlyBaseSeen == true) // If the state is aim and the friendly base has been seen.
	{
		scanningState == SCAN; // State is set to scan.
	}

	switch (scanningState)
	{
	case SCAN: {
		turretGoRight(); // Rotate the turret right.
	} break;
	case AIM:
	{
		if (m_bFriendlyBaseSeen == false) {
			float deltaR = turretTh - m_iAngleOfTurret;
			if (deltaR > 1 && deltaR < 180) // If the delta rotation is greater than 1 and less than 180.
			{
				turretGoLeft(); // Rotate the turret left.
			}
			else if (deltaR < -1 && deltaR < -180) {
				turretGoRight(); // Rotate the turret right.
			}
			else if (deltaR > 180) // If the delta rotation is greater than 180
			{
				turretGoRight(); // Rotate the turret right.
			}
			else if (deltaR < -180) // If the delta rotation is less than -180.
			{
				turretGoLeft(); // Rotate the turret left.
			}
			else {
				m_bLOS = true; // Has a line of sight.
				stopTurret(); // Stop rotating the turret.
				clearMovement(); // Clear the movement.
			}
		}
	} break;
	}




}

void CWTank::navMachine()
{
	while (!m_bFlag) // While the flag is false.
	{
		int l_iRandomXLocation = rand() % 13 + 2; // The random x location.
		int l_iRandomYLocation = rand() % 5 + 2; // The random y location.
		// If the map random x and y path is true.
		if (map->mapArray[l_iRandomXLocation][l_iRandomYLocation]->m_bPath == true) {
			map->AStar(path, *currentCell, *map->mapArray[l_iRandomXLocation][l_iRandomYLocation]); // Do Astar algorithm with these values.
			m_bFlag = true; // Set the flag.
		}
	}

	//State machine values.
	const int IDLE = 0;
	const int MOVE_RANDOM = 1;
	const int MOVE_AWAY = 2;
	const int MOVE_CENTRE = 3;
	int state = IDLE; // Original state is idle.
	int l_iEnemyDistThreshold = 100; // Enemy distance threshold.
	int l_iWallDistThreshold = 5; // The wall distance threshold.

	if (state == IDLE) // If the state is idle.
	{
		// If the enemy distance is less than the enemy threshold OR the enemy has been seen and the no. of shell is greater than the buildings remaining.
		if (m_fGetEnemyDistance < l_iEnemyDistThreshold || (m_bEnemySeen == true && numberOfShells > m_iBuildingsRemain)) {
			state = MOVE_AWAY; // Set the state to move away.
		}
		else if (m_iScannedAmount > 300 && m_bBaseSeen == false) { // If the scanned amount is greater than 300 and the base has been seen.
			m_bFlag = false; // Set the flag to false.
			state = MOVE_RANDOM; // Set the state to move random.
		}
	}
	else if (state == MOVE_RANDOM) { // If the state is move random.
		// If the enemy distance is greater than the enemy threshold OR the enemy has been seen and the no. of shells is greater than the buildings remaining.
		if (m_fGetEnemyDistance < l_iEnemyDistThreshold || m_bEnemySeen == true && numberOfShells > m_iBuildingsRemain) {
			clearMovement(); // Clear the movement.
		}
		else {state = IDLE;} // Set the state to IDLE.
	}
	else if (state == MOVE_AWAY) { // If the state is move away.
		if (m_fGetEnemyDistance > l_iEnemyDistThreshold) { // The enemy distance is greater than the enemy distance threshold.
			state = IDLE; // The state is idle.
		}
		// If the x is less than 10 OR the x is greater than 770 OR the y is less than 10 OR the y is greater than 560.
		else if (getX() < 10 || getX() > 770 || getY() < 10 || getY() > 560) {
			m_bFlag = false; // The flag is set to false.
			state = MOVE_CENTRE; // Set the state to move to centre.
		}
	}
	switch (state) {
	case IDLE: {
		clearMovement(); // Clear the movement.
	}break;
	case MOVE_RANDOM: {
		m_iScannedAmount = 0; // Set the scanned amount.
		int l_iRandomXLocation; // Random X.
		int l_iRandomYLocation; // Random Y.
		while (!m_bFlag) // Whilethe flag is false
		{
			// If the current cell row is less than or equal to 8 AND the current cell column is less than or equal to 11.
			if (currentCell->m_iRow <= 8 && currentCell->m_iColumn <= 11) {
				l_iRandomXLocation = rand() % 14 + 8; // Set the random X.
				l_iRandomYLocation = rand() % 20 + 11; // Set the random Y.
			}
			// If the current cell row is less than or equal to 8 AND the current cell column is greater than or equal to 12.
			if (currentCell->m_iRow <= 8 && currentCell->m_iColumn >= 12) {
				l_iRandomXLocation = rand() % 14 + 8; // Set the random X.
				l_iRandomYLocation = rand() % 11 + 2; // Set the random Y.
			}
			// If the current cell row is greater than or equal to 9 AND the current cell column is less than or equal to 11.
			if (currentCell->m_iRow >= 9 && currentCell->m_iColumn <= 11) {
				l_iRandomXLocation = rand() % 9 + 2; // Set the random X.
				l_iRandomYLocation = rand() % 11 + 2; // Set the random Y.
			}
			// If the current cell row is greater than or equal to 9 AND the current cell column is greater than or equal to 12.
			if (currentCell->m_iRow >= 9 && currentCell->m_iColumn >= 12) {
				l_iRandomXLocation = rand() % 9 + 2; // Set the random X.
				l_iRandomYLocation = rand() % 11 + 2; // Set the random Y.
			}
			// If the map random X and Y path is true
			if (map->mapArray[l_iRandomXLocation][l_iRandomYLocation]->m_bPath == true) {
				map->AStar(path, *currentCell, *map->mapArray[l_iRandomXLocation][l_iRandomYLocation]); // Do A* with these values.
				m_bFlag = true; // Set the flag to true.
			}
		}
	} break;
	case MOVE_AWAY:{
		int l_iMoveTo = currentCell->m_iRow;
		while (!m_bFlag) {
			if (m_iAngleOfTurret <= 180) {
				l_iMoveTo = l_iMoveTo + 1;
			}
			if (m_iAngleOfTurret > 180) { l_iMoveTo = l_iMoveTo + 1; } // If the ange of the turret is greater than 180 add 1 to the value of the move to variable.
			// If the map move to value and the column value path is true.
			if (map->mapArray[l_iMoveTo][currentCell->m_iColumn]->m_bPath == true) {
				map->AStar(path, *currentCell, *map->mapArray[l_iMoveTo][currentCell->m_iColumn]); // Do A* with these values.
				m_bFlag = true; // Set the flag to true.
			}
		}
	} break;
	case MOVE_CENTRE: {
		int l_iCentreX = 8; // Centre X.
		int l_iCentreY = 10; // Centre Y.
		while (!m_bFlag) { // While the flag is false.
			// If the map centre X and Y value path is true.
			if (map->mapArray[l_iCentreX][l_iCentreY]->m_bPath == true) {
				map->AStar(path, *currentCell, *map->mapArray[l_iCentreX][l_iCentreY]); // Do A* with these values.
				m_bFlag = true; // Set the flag to true.
			}
			l_iCentreX++; // Increment the centre X.
			l_iCentreY++; // Increment the centre Y.
		}
	}break;
	}

}

void CWTank::markTarget(Position p)
{
	m_bBaseSeen = true; // The base has been seen.
	float deltaX = getX() - p.getX(); // The delta x is the x - p x value.
	float deltaY = getY() - p.getY(); // The delta y is the x - p y value.
	m_iAngleDegrees = atan2(deltaY, deltaX) * 180 / PI; // The atan2 value is the delta values * 180 divided by PI.
	m_iAngleOfTurret = m_iAngleDegrees + 180; // The angle of the turret is the angle in degrees + 180.
}

void CWTank::markEnemy(Position p)
{
	m_bEnemySeen = true; // The enemy has been seen.
	m_iXPos = p.getX(); // The X position is the p x value.
	float deltaX = getX() - p.getX(); // The delta X is the x value - p x value.
	float deltaY = getY() - p.getY(); // The delta y is the y value - p y value.
	m_iAngleDegrees = atan2(deltaY, deltaX) * 180 / PI; // The angle in degrees is the atan2 of the delta values * 180 divided by PI.
	m_iAngleOfTurret = m_iAngleDegrees + 180; // The angle of the turret is the angle in degrees + 180.
	float dx = (float)(p.getX() - getX()); // p x value - x value.
	float dy = (float)(p.getY() - getY()); // p y value - y value.
	//m_fGetEnemyDistance = sqrt(dx * dx + dy * dy); // The enemy distance is the square root of the dx squared + the dy squared. (Euclidean Heuristic).
	//m_fGetEnemyDistance = 1 * (abs(dx) + abs(dy)); // Manhattan Heuristic.
	m_fGetEnemyDistance = 1.414 * std::max(abs(dx), abs(dy)); // Diagonal Heuristic
}

void CWTank::markBase(Position p)
{
	float deltaX = getX() - p.getX(); // The delta x is the x value - the p x value.
	float deltaY = getY() - p.getY(); // The delta y is the y value - the p y value.
	m_iBaseAngleDegrees = atan2(deltaY, deltaX) * 180 / PI; // The base angle in degrees the atan2 of the delta values * 180 / PI.
	m_iBaseAngle = m_iBaseAngleDegrees + 180; // The base angle is the base the base angle in degrees + 180.
	float l_fFirstPair = (p.getX() - getX()) * (p.getX() - getX()); // The first pair is the p X value - the x value multiplied by the p X value - X value.
	float l_fSecondPair = (p.getY() - getY()) * (p.getY() - getY()); // The second pair is the p Y value - the y value multiplied by the p Y value - Y value.
	float l_fDistance;
	//l_fDistance = sqrt(l_fFirstPair + l_fSecondPair); // Euclidean Heuristic.
	//l_fDistance = 1 * (abs(deltaX) + abs(deltaY)); // Manhattan Heuristic.
	l_fDistance = 1.414 * std::max(abs(deltaX), abs(deltaY)); // Diagonal Heuristic.
	float l_fRange = 0; // The range.
	if (l_fDistance <= 50) l_fRange = 50; // If the distance is less than or equal to 50, set the range to 50.
	if (l_fDistance > 50 && l_fDistance <= 100) l_fRange = 25; // If the distance is greater than 50 AND the distance is less than or equal to 100, set the range to 25.
	if (l_fDistance > 100) l_fRange = 12.5; // If the distance is greater than 100, set the range to 12.5.
}

void CWTank::markShell(Position p)
{
}

bool CWTank::isFiring()
{
	return m_bFire; // Returning the firing value.
}

void CWTank::score(int thisScore, int enemyScore)
{
	std::cout << "Player Score: " << thisScore << "\tEnemy Score: " << enemyScore << std::endl; // Score.
}

void CWTank::DrawNode(sf::RenderTarget & target)
{
}

void CWTank::setCurrentCell()
{
	const int iXWidth = 780; // X width.
	const int iXHeight = 570; // X height.
	float x = getX() - 17.5f; // X value is the x value - 17.5.
	float y = getY() - 17.5f; // Y value is the y value - 17.5.
	int nodeSize = 780 / 22; // The node size is 780 / 22.
	int mx = (x / 35); // The mx is x divided by 35.
	int my = (y / 35); // The my is the y divided by 35.

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 22; j++)
		{
			map->mapArray[i][j]->setCurrent(false); // Set the map current node to false.
		}
	}
	map->mapArray[my][mx]->setCurrent(true); // Set the map current node to true.
	currentCell = map->mapArray[my][mx]; // Set the current cell the mx and my of the map.

}
