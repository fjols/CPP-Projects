#include "..\include\CellManager.h"

CellManager::CellManager(int x, int y, int height, int width, int row, int column)
{
	position.x = x; // Position x.
	position.y = y; // Position y.
	m_iRow = row; // Row.
	m_iColumn = column; // Column.
	m_iHeight = height; // Height.
	m_iWidth = width; // Width.
	m_bCurrent = false; // The current node.
	cellRect.setSize(sf::Vector2f(width, height)); // Set the size of the cell rect.
	cellRect.setSize(sf::Vector2f(position.x, position.y)); // Set the size of the cell rect.
	cellRect.setFillColor(sf::Color(255,255,255,50)); // Set colour.
	cellRect.setOutlineThickness(1); // Set the outline thickness
	cellRect.setOutlineColor(sf::Color(255,255,255,50)); // Set outline colour.
}

void CellManager::DrawCell(sf::RenderTarget & target)
{
	target.draw(cellRect); // Draw the cell rectangle.
}

int CellManager::getX()
{
	return position.x + m_iWidth/2; // Return the X value.
}

int CellManager::getY()
{
	return position.y + m_iHeight/2; // Return the Y value.
}

void CellManager::setWall()
{
	m_bPath == false; // Path is equal to false.
	cellRect.setFillColor(sf::Color(255,255,255,50)); // Set colour.
}

void CellManager::setPath()
{
	m_bPath == false; // Path is equal to false.
	cellRect.setFillColor(sf::Color(0, 0, 0, 100)); // Set colour.
}

void CellManager::setGoal()
{
	cellRect.setFillColor(sf::Color(255,0,0,100)); // Set colour.
}

void CellManager::setStart()
{
	cellRect.setFillColor(sf::Color(0, 255, 0, 100)); // Set colour.
}

void CellManager::setOpen()
{
	cellRect.setFillColor(sf::Color(255,255,255,100)); // Set colour.
}

void CellManager::setClosed()
{
	cellRect.setFillColor(sf::Color(255,255,0,100)); // Set colour.
}

void CellManager::setCurrent(bool b)
{
	if (!m_bCurrent && b)
	{
		cellRect.setFillColor(sf::Color(255,0,255, 150)); // Set colour.
		m_bCurrent = true; // The current node.
	}
	else if (m_bCurrent && !b)
	{
		cellRect.setFillColor(sf::Color(255,255,255,50)); // Set colour.
		m_bCurrent = false; // Not the current node.
	}
}

int CellManager::lowerOutcome(const CellManager other) const
{
	return m_fCost < other.m_fCost; // Cost less the other cell cost.
}

int CellManager::score(float parentGeoScore, float currentX, float currentY, int goalX, int goalY)
{
	float dx, dy; // Delta variables.
	m_fDistCurrentToStart = parentGeoScore + 1.0f; // Geographical score + 1.
	dx = (float)(goalX - currentX); // Delta X is the goal X minus the current X.
	dy = (float)(goalY - currentY); // Delta Y is the goal Y minus the current Y.
	m_fDistCurrentToGoal = sqrt(dx * dx + dy * dy); // The distance to the goal is the square root of the delta x squared + delta y squared.
	return m_fDistCurrentToGoal; // Return the distance of current to goal.
}

CellManager::~CellManager()
{
}
