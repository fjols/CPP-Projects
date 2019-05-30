#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class CellManager
{
private:
	sf::Vector2f position; //!< A vector that holds the positional data.
	int m_iHeight; //!< Height of a cell.
	int m_iWidth; //!< Width of a cell.
	sf::RectangleShape cellRect; //!< A rectangle shape holding cells.
public:
	bool m_bCurrent = true; //!< Current cell.
	bool m_bNotRightPath = false; //!< Not the right path?
	bool m_bPath = true; //!< Path.
	CellManager(int x /** \param x position */,
				int y /** \param y position */,
				int height /** \param height of the cell */,
				int width /** \param width of the cell*/,
				int row /** \param rows */,
				int column /** \param columns */); //!< Constructor.
	void DrawCell(sf::RenderTarget &target /** \param target to draw a cell to.*/);
	int getX(); //!< Get the X value.
	int getY(); //!< Get the Y value.
	void setWall(); //!< Set wall.
	void setPath(); //!< Set the path.
	void setGoal(); //!< Set the goal.
	void setStart(); //!< Set the start node.
	void setOpen(); //!< Set open.
	void setClosed(); //!< Set closed. 
	void setCurrent(bool b /** \param is it current */); //!< Set the current.
	int lowerOutcome(const CellManager other /** \param the other cell */) const; //!< Lower outcome?
	float m_fCost; //!< Cost of a cell.
	float m_fDistCurrentToStart; //!< Distance of the current cell from the start cell.
	float m_fDistCurrentToGoal; // !< Distance of the current cell from the goal cell.
	int parent; //!< Parent cell.
	int score(float parentGeoScore /** \param parent cell's geographical score */,
			  float currentX /** \param current x position */,
			  float currentY /** \param current y position*/,
		      int goalX /** \param goal x position */,
		      int goalY /** \param goal y position*/); //!< The score of the cell.
	int m_iRow; //!< Row
	int m_iColumn; //!< Column.
	~CellManager(); //!< Destructor.
};