#include "..\include\CellMap.h"
#include <algorithm>
#include <functional>

CellMap::CellMap()
{
	for (int i = 0; i < m_kiRows; i++)
	{
		for (int j = 0; j < m_kiColumns; j++)
		{
			cell = new CellManager(m_iXBuffer + m_iWidth * j, m_iYBuffer + m_iHeight * i, m_iWidth, m_iHeight, i, j); // Create the cells to populate the map.
			mapArray[i][j] = cell; // Set the cells.
		}
	}
}

void CellMap::DrawMap(sf::RenderTarget & target)
{
	for (int i = 0; i < m_kiRows; i++)
	{
		for (int j = 0; j < m_kiColumns; j++)
		{
			mapArray[j][i]->DrawCell(target); // Draw the cell to the screen using a specified render target.
		}
	}
}

void CellMap::notPath(sf::Vector2f pos)
{
	for (int i = 0; i < m_kiRows; i++)
	{
		for (int j = 0; j < m_kiColumns; j++)
		{
			if (pos.x < (mapArray[i][j]->getX() - 35 / 2) + 35 && // If the pos.x is less than the map's x - 35 / 2 + 35.
				pos.x + 50 > mapArray[i][j]->getX() - 35 / 2 &&   // AND the pos.x + 50 is greater than map's x - 35 / 2.
				pos.y <(mapArray[i][j]->getY() - 35 / 2) + 35 && // If pos.y is less than map's y - 35 / 2 + 35.
				50 + pos.y > mapArray[i][j]->getY() - 35 / 2)   // AND pos.y + 50 is greater than map's y - 35 / 2.
			{
				mapArray[i][j]->setWall(); // Set wall.
				mapArray[i][j]->m_bPath = false; // Path is false.
			}
		}
	}
}

void CellMap::setPath(sf::Vector2f pos)
{
}

std::vector<CellManager*> CellMap::getCellNeighbours(CellManager * cell)
{
	int row = cell->m_iRow; // Get the rows.
	int column = cell->m_iColumn; // Get the columns.
	float diagonalCost = 1.414; // The cost diagonally.
	int normalCost = 1; // Regular cost for a cell.

	int ne[8][3] = {
		{row, column + 1, 0},
		{row, column - 1, 0},
		{row + 1, column, 0},
		{row - 1, column, 0},
		{row + 1, column + 1, 0},
		{row + 1, column - 1, 0},
		{row - 1, column - 1, 0},
		{row - 1, column + 1, 0}
	};
	
	std::vector<CellManager*>neighbours; // Vector containing the neighbours of the cell.
	std::vector<bool>diagonals; // Is the cell diagonal.
	for (int j = 0; j < 8; j++)
	{
		if (ne[j][0] < 16 && ne[j][1] < 22)
		{
			if (mapArray[ne[j][0]][ne[j][1]]->m_bPath == true)
			{
				neighbours.push_back(mapArray[ne[j][0]][ne[j][1]]); // Push the neighbours to the vector.
				diagonals.push_back(ne[j][2]); // Push the diagonals to the vector.
			}
		}
	}

	for (int i = 0; i < neighbours.size(); i++)
	{
		if (diagonals[i]) // If the neighbour is diagonal from the current node.
		{
			neighbours[i]->m_fDistCurrentToStart = cell->m_fDistCurrentToStart + diagonalCost; // Add the distance from the current node to start and the diagonal cost together.
		}
		else { // If its not
			neighbours[i]->m_fDistCurrentToStart = cell->m_fDistCurrentToStart + normalCost; // Add the normal cost instead.
			neighbours[i]->parent = cell->parent; // Set the parent cell.
		}
	}

	return neighbours; // Return the neighbours vector.
}

bool CellMap::AStar(std::list<CellManager>& path, CellManager start, CellManager goal)
{
	std::list<CellManager> open; // The open list.
	std::list<CellManager> closed; // The closed list.
	closed.empty(); // Is the closed list empty?
	CellManager currentNode = start; // What the start node is.
	CellManager goalNode = goal; // What the end node is.
	currentNode.parent = -1;
	currentNode.m_fDistCurrentToStart = 0; // Distance from the current cell to the start cell. (Geographical Score).
	currentNode.m_fCost = currentNode.m_fDistCurrentToStart + currentNode.score(currentNode.m_fDistCurrentToStart, currentNode.getX(), currentNode.getY(), goal.getX(), goal.getY()); // Calculating the cost of the cell.
	//The cost is calculated by getting the current nodes distance to the start node and adding the score of the node.
	// F(n) = G(n) + H(n).
	open.push_back(currentNode); // Push the node to the list.
	while (!open.empty()) {
		std::stable_sort(open.begin(), open.end(), std::mem_fun_ref(&CellManager::lowerOutcome));
		if (currentNode.m_iRow == goal.m_iRow && currentNode.m_iColumn == goal.m_iColumn)
		{
			path = construct_path(path, closed, &goal);
			return true;
		}

		currentNode = open.front(); // Set the current node the front of the open list.
		open.pop_front(); // Remove the node at the front of the open list.
		closed.push_back(currentNode); // Push the current node to the back of the closed list.
		mapArray[currentNode.m_iRow][currentNode.m_iColumn]->setGoal(); // Set the goal node on the map.

		//Iterators for the lists.
		std::list<CellManager>::iterator l_closedIterator; // Iterator for the closed list.
		std::list<CellManager>::iterator l_openIterator; // Iterator for the open list.

		for (auto &neighbour : getCellNeighbours(&currentNode)) // Get the neighbours of the node.
		{
			bool bFoundClosed = false; // Not found
			for (l_closedIterator = closed.begin(); l_closedIterator != closed.end(); ++l_closedIterator)
			{
				if (neighbour->m_iRow == l_closedIterator->m_iRow && neighbour->m_iColumn == l_closedIterator->m_iColumn)
				{
					bFoundClosed = true; // Found
				}
			}
			if (!bFoundClosed)
			{
				neighbour->m_fCost = neighbour->m_fDistCurrentToStart + neighbour->score(neighbour->m_fDistCurrentToStart, neighbour->getX(), neighbour->getY(), goal.getX(), goal.getY()); // Score the current node.
				bool foundOpen = false; // Not found
				for (l_openIterator = open.begin(); l_openIterator != open.end(); ++l_openIterator)
				{
					if (neighbour->m_iRow == l_openIterator->m_iRow && neighbour->m_iColumn == l_openIterator->m_iColumn)
					{
						foundOpen = true; // Found open
					}
				}
				if (!foundOpen)
				{
					open.push_back(*neighbour); // Push the neighbour node to the open list.
					mapArray[neighbour->m_iRow][neighbour->m_iColumn]->setClosed();
				}
				else {
					CellManager* openNeighbour = neighbour; // Set the neighbour to be the open neighbour.
					if (neighbour->m_fDistCurrentToStart < openNeighbour->m_fDistCurrentToStart) {
						openNeighbour->m_fDistCurrentToStart = neighbour->m_fDistCurrentToStart; // Set the distance of the current to start node from the neighbour node to the open neighbour distance to start.
						openNeighbour->parent = neighbour->parent; // Set the parent of the neighbour node to the open neighbour parent.
					}
				}
			}
		}

	}
	return false;
}

std::list<CellManager> CellMap::construct_path(std::list<CellManager>& path, std::list<CellManager>& closed, CellManager * cell)
{
	int parent; // The parent cell.
	std::list<CellManager>::iterator listIter; // The list iterator.
	CellManager * currentNode = cell; // The current cell is the cell given in the parameters.
	parent = currentNode->parent; // Set the parent to the current nodes parent.
	path.push_front(*currentNode); // Push the current node to the front of the path.
	closed.pop_back(); // Pop the back element of the closed list.
	for (listIter = closed.end(), listIter--; listIter != closed.begin(); --listIter)
	{
		path.push_front(*listIter); // Add to the path.
		closed.erase(listIter); // Remove node from the list.
		listIter = closed.end(); //Work backwards throughout the list from the end.
	}
	return path; // Return the path list.
}

CellMap::~CellMap()
{
}
