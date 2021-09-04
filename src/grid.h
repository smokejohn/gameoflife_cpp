#ifndef GRID_H
#define GRID_H

#include <vector>

class Grid {
    private:
        std::vector<int> m_cells;

        int m_size_x;
        int m_size_y;

    public:
        Grid(int size_x, int size_y);
        Grid(std::vector<std::vector<int>> grid);
        Grid(std::vector<int> grid, int sizeX);

        std::vector<int> getNeighbors(unsigned int cellIdx);
        int numAliveNeighbors(unsigned int cellIdx);

        int& cellAt(unsigned int x, unsigned int y);
        void setCell(unsigned int x, unsigned int y, bool alive);

        void update();
        void draw();
        void print();

        int sizeX();
        int sizeY();

};

#endif //GRID_H
