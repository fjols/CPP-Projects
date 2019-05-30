#pragma once
#include "CellManager.h"
#include <iostream>
#include <vector>
#include <list>

class CellMap
{
private:
	CellManager * cell; //!< A cell.
	static const short unsigned m_kiRows = 16; //!< Rows in the map.
	static const short unsigned m_kiColumns = 22; //!< Columns in the map.
	int m_iWidth = 35; //!< The height of the map. 
	int m_iHeight = 35; //!< The width of the map.
	static const short unsigned m_kiWidth = 780; //!< Width.
	static const short unsigned m_kiHeight = 570; //!< Height.
	int m_iXBuffer = 15; //!< X buffer.
	int m_iYBuffer = 10; //!< Y buffer.

public:
	CellManager * mapArray[16][22]; //!< The map array, the size of it reflects the rows and columns.
	CellMap(); //!< Constructor.
	void DrawMap(sf::RenderTarget &target /** \param target to draw the cell to*/); //!< Draw the map.
	void notPath(sf::Vector2f pos /** \param position*/); //!< Not the path.
	void setPath(sf::Vector2f pos /** \param position*/); //!< Set the path.
	static const unsigned cells = m_kiRows * m_kiColumns; //!< Cells in map.
	std::vector<CellManager*> getCellNeighbours(CellManager* cell /** \param A cell.*/); //!< Vector containing the current cells neighbours.
	bool CellMap::AStar(std::list<CellManager> &path /** \param The path list */,
						CellManager start /** \param Starting cell */, 
						CellManager goal /** \param End cell */); //!< A* algorithm.
	std::list<CellManager> CellMap::construct_path(std::list<CellManager>& path /** \param The path list */,
						std::list<CellManager>& closed /** \param Closed List*/,
						CellManager* cell /** \param A cell*/); //!< Constuct a path.
	~CellMap(); //!< Destructor.
};