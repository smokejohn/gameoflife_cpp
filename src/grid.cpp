#include <iostream>
#include <grid.h>
#include <stdexcept>

Grid::Grid (int size_x, int size_y) : m_size_x{size_x}, m_size_y{size_y} {
    m_cells.resize(m_size_x * m_size_y, 0);
}

Grid::Grid(std::vector<std::vector<int>> grid) {
    m_size_y = grid.size();
    m_size_x = grid[0].size();

    for (int r = 0; r < grid.size(); r++) {
        for (int c = 0; c < grid[0].size(); c++) {
            m_cells.push_back(grid[r][c]);
        }
    }
}

Grid::Grid(std::vector<int> grid, int sizeX) {
    m_size_x = sizeX;
    m_size_y = grid.size() / sizeX;

    for (int i = 0; i < grid.size(); i++) {
        m_cells.push_back(grid[i]);
    }
}

/* 
 * Gets neighbors of the given cell in the grid
 *
 * @param cellIdx index of cell to get neighbors of
 * @return list of neighbors values as std::vector<int>
 */
std::vector<int> Grid::getNeighbors(const unsigned int cellIdx) {
    std::vector<int> neighbors;
    int topIdx = cellIdx - m_size_x;
    int bottomIdx = cellIdx + m_size_x;

    // check if we are on the border
    bool leftBorder = cellIdx % m_size_x == 0;
    bool rightBorder = cellIdx % m_size_x == m_size_x - 1;
    bool topBorder = cellIdx - m_size_x < 0;
    bool bottomBorder = cellIdx + m_size_x > m_cells.size();

    // top row
    if (!topBorder) {
        if (!leftBorder) 
            neighbors.push_back(m_cells[topIdx-1]);

        neighbors.push_back(m_cells[topIdx]);

        if (!rightBorder)
            neighbors.push_back(m_cells[topIdx+1]);
    }

    // mid row
    if (!leftBorder)
        neighbors.push_back(m_cells[cellIdx-1]);
    if (!rightBorder)
        neighbors.push_back(m_cells[cellIdx+1]);

    // bottom row
    if (!bottomBorder) {
        if (!leftBorder)
            neighbors.push_back(m_cells[bottomIdx-1]);

        neighbors.push_back(m_cells[bottomIdx]);

        if (!rightBorder)
            neighbors.push_back(m_cells[bottomIdx+1]);

    }

    return neighbors;
}

/*
 * Returns the number of alive neighboring cells
 *
 * @param cellIdx index of the cell to get the alive neighbors of
 * @return positive integer value of alive neighbors
 */
int Grid::numAliveNeighbors(const unsigned int cellIdx) {
    std::vector<int> neighbors = getNeighbors(cellIdx);
    int numAliveNeighbors = 0;
    for (const auto cell : neighbors) {
        if (cell == 1)
            numAliveNeighbors++;
    }
    return numAliveNeighbors;
}

int& Grid::cellAt(const unsigned int x, const unsigned int y) {
    if (x > m_size_x || y > m_size_y)
        throw std::invalid_argument("array out of bound exception");

    int index = x + m_size_x * y;;

    return m_cells[index];
}

/*
 * Sets a cell at position [x][y] to the given value (alive or dead => 1 or 0)
 *
 * @param x column index of cell in the grid
 * @param y row index of cell in the grid
 * @param alive value to write to cell => true for alive, false for dead
 */
void Grid::setCell(const unsigned int x, const unsigned int y, const bool alive) {
    int& cell = cellAt(x, y);
    if (alive)
        cell = 1;
    else
        cell = 0;
}

/*
 * Updates the internal cellgrid to the new state
 * according to conways game of life rules
 */
void Grid::update() {
    std::vector<int> updatedGrid (m_cells.begin(), m_cells.end());

    for (int i = 0; i < m_cells.size(); i++) {
        int aliveNeighbors = numAliveNeighbors(i);
        // alive cells
        if (m_cells[i] == 1) {
            if (aliveNeighbors < 2 || aliveNeighbors > 3)
                updatedGrid[i] = 0;
        }
        // dead cells that come to live
        if (m_cells[i] == 0 && aliveNeighbors == 3) {
            updatedGrid[i] = 1;
        }
    }

    m_cells = updatedGrid;
}

/*
 * Draws the current cellgrid with unicode characters in the console
 */
void Grid::draw() {
    for (int i = 0; i < m_cells.size(); i++) {
        if (m_cells[i] == 1) {
            std::cout << "\u2B1B";
        } else {
            std::cout << "\u2B1C";
        }
        if (i < m_cells.size() - 1) {
            if (i % m_size_x == m_size_x - 1)
                std::cout << "\n";
        }
    }
    std::cout << "\n";
}

/*
 * Prints the current cellgrid values to the console 
 */
void Grid::print() {
    std::cout << "{";
    for (int i = 0; i < m_cells.size(); i++) {
        std::cout << m_cells[i];
        if (i < m_cells.size() - 1) {
            if (i % m_size_x == m_size_x - 1)
                std::cout << "\n ";
            else
                std::cout << ",";
        }
    }
    std::cout << "}\n";
}

/*
 * Gives access to internal grids rowlength
 *
 * @return rowlength / Xsize of the cellgrid
 */
int Grid::sizeX() {
    return m_size_x;
}

/*
 * Gives access to internal grids columncount
 *
 * @return columncount / ysize of the cellgrid
 */
int Grid::sizeY() {
    return m_size_y;
}
