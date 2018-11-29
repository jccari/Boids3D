#ifndef BOIDS3D_GRID_H
#define BOIDS3D_GRID_H

#include <vector>
#include <iostream>
#include <initializer_list>

#include "../Boid.h"

using namespace std;

template <class TypeItem, class Item>
class Grid{
private:
    vector<vector<vector<TypeItem>>> grid; // 3D vector
    int x;
    int y;
    int z;

    typedef vector<Item> ListTypeItem;
public:
    Grid(int nx, int ny, int nz){
        x = nx;
        y = nx;
        z = nz;
        initGrid(x, y, z);
    }

    void initGrid(int x, int y, int z){
        grid.resize(x);
        for (int i = 0; i < x; ++i){
            grid[i].resize(y);
            for (int j = 0; j < y ; ++j)
                grid[i][j].resize(z);
        }
    }
    /*
    TypeItem& operator[](int nx, int ny, int nz) const {
        if( ny < 0 and ny >= y and nx < 0 and nx >= x and nz < 0 and nz >= z) { //out of bounds
            std::cout << "[ERROR] Indices fuera de rango" << endl;
            return nullptr;
        }
        return grid[nx][ny][nz];
    }
    */

    bool insert(Boid* data, int nx, int ny, int nz ){
        grid[nx][ny][nz].push_back(data);
        return true;
    }

    ListTypeItem getNeighborGrids(int nx, int ny, int nz){
        vector<TypeItem> neighTemp;
        ListTypeItem neighbors;
        if( validateGrid(nx, ny, nz-1) )
            neighTemp.push_back(grid[nx][ny][nz-1]);
        if( validateGrid(nx, ny+1, nz-1) )
            neighTemp.push_back(grid[nx][ny+1][nz-1]);
        if( validateGrid(nx-1, ny+1, nz-1) )
            neighTemp.push_back(grid[nx-1][ny+1][nz-1]);
        if( validateGrid(nx-1, ny, nz-1) )
            neighTemp.push_back(grid[nx-1][ny][nz-1]);
        if( validateGrid(nx-1, ny-1, nz-1) )
            neighTemp.push_back(grid[nx-1][ny-1][nz-1]);
        if( validateGrid(nx, ny-1, nz-1) )
            neighTemp.push_back(grid[nx][ny-1][nz-1]);
        if( validateGrid(nx+1, ny-1, nz-1) )
            neighTemp.push_back(grid[nx+1][ny-1][nz-1]);
        if( validateGrid(nx+1, ny, nz-1) )
            neighTemp.push_back(grid[nx+1][ny][nz-1]);
        if( validateGrid(nx+1, ny+1, nz-1) )
            neighTemp.push_back(grid[nx+1][ny+1][nz-1]);

        if( validateGrid(nx, ny, nz) )
            neighTemp.push_back(grid[nx][ny][nz]);
        if( validateGrid(nx, ny+1, nz) )
            neighTemp.push_back(grid[nx][ny+1][nz]);
        if( validateGrid(nx-1, ny+1, nz) )
            neighTemp.push_back(grid[nx-1][ny+1][nz]);
        if( validateGrid(nx-1, ny, nz) )
            neighTemp.push_back(grid[nx-1][ny][nz]);
        if( validateGrid(nx-1, ny-1, nz) )
            neighTemp.push_back(grid[nx-1][ny-1][nz]);
        if( validateGrid(nx, ny-1, nz) )
            neighTemp.push_back(grid[nx][ny-1][nz]);
        if( validateGrid(nx+1, ny-1, nz) )
            neighTemp.push_back(grid[nx+1][ny-1][nz]);
        if( validateGrid(nx+1, ny, nz) )
            neighTemp.push_back(grid[nx+1][ny][nz]);
        if( validateGrid(nx+1, ny+1, nz) )
            neighTemp.push_back(grid[nx+1][ny+1][nz]);

        if( validateGrid(nx, ny, nz+1) )
            neighTemp.push_back(grid[nx][ny][nz+1]);
        if( validateGrid(nx, ny+1, nz+1) )
            neighTemp.push_back(grid[nx][ny+1][nz+1]);
        if( validateGrid(nx-1, ny+1, nz+1) )
            neighTemp.push_back(grid[nx-1][ny+1][nz+1]);
        if( validateGrid(nx-1, ny, nz+1) )
            neighTemp.push_back(grid[nx-1][ny][nz+1]);
        if( validateGrid(nx-1, ny-1, nz+1) )
            neighTemp.push_back(grid[nx-1][ny-1][nz+1]);
        if( validateGrid(nx, ny-1, nz+1) )
            neighTemp.push_back(grid[nx][ny-1][nz+1]);
        if( validateGrid(nx+1, ny-1, nz+1) )
            neighTemp.push_back(grid[nx+1][ny-1][nz+1]);
        if( validateGrid(nx+1, ny, nz+1) )
            neighTemp.push_back(grid[nx+1][ny][nz+1]);
        if( validateGrid(nx+1, ny+1, nz+1) )
            neighTemp.push_back(grid[nx+1][ny+1][nz+1]);

        for (int i = 0; i < neighTemp.size() ; ++i) {
            neighbors.insert(neighbors.begin(), neighTemp[i].begin(), neighTemp[i].end());
        }

        return std::move(neighbors) ;
    }

    bool validateGrid(int nx, int ny, int nz){
        if(nx >= 0 and nx < x and ny >= 0 and ny < y and nz >= 0 and nz < z)
            return true;
        return false;
    }

    int getX() const { return x; }

    int getY() const { return y; }

    int getZ() const { return z; }

};

/*
template<class TypeItem>
void Grid<TypeItem>::initGrid( int x, int y, int z) {
    grid.resize(x);
    for (int i = 0; i < x; ++i){
        grid[i].resize(y);
        for (int j = 0; j < y ; ++j)
            grid[i][j].resize(z);
    }
}

template<class TypeItem>
TypeItem& Grid<TypeItem>::operator[](int nx, int ny, int nz){
    if( ny < 0 and ny >= y and nx < 0 and nx >= x and nz < 0 and nz >= z) { //out of bounds
        std::cout << "[ERROR] Indices fuera de rango" << endl;
        return nullptr;
    }
    return grid[nx][ny][nz];
}

template<class TypeItem>
vector<TypeItem&> Grid<TypeItem>::getNeighbors(int nx, int ny, int nz){
    vector<TypeItem &> neighbors;
    if( validateGrid(nx, ny, nz-1) )
        neighbors.emplace_back(nx, ny, nz-1);
    if( validateGrid(nx, ny+1, nz-1) )
        neighbors.emplace_back(nx, ny+1, nz-1);
    if( validateGrid(nx-1, ny+1, nz-1) )
        neighbors.emplace_back(nx-1, ny+1, nz-1);
    if( validateGrid(nx-1, ny, nz-1) )
        neighbors.emplace_back(nx-1, ny, nz-1);
    if( validateGrid(nx-1, ny-1, nz-1) )
        neighbors.emplace_back(nx-1, ny-1, nz-1);
    if( validateGrid(nx, ny-1, nz-1) )
        neighbors.emplace_back(nx, ny-1, nz-1);
    if( validateGrid(nx+1, ny-1, nz-1) )
        neighbors.emplace_back(nx+1, ny-1, nz-1);
    if( validateGrid(nx+1, ny, nz-1) )
        neighbors.emplace_back(nx+1, ny, nz-1);
    if( validateGrid(nx+1, ny+1, nz-1) )
        neighbors.emplace_back(nx+1, ny+1, nz-1);

    if( validateGrid(nx, ny, nz) )
        neighbors.emplace_back(nx, ny, nz);
    if( validateGrid(nx, ny+1, nz) )
        neighbors.emplace_back(nx, ny+1, nz);
    if( validateGrid(nx-1, ny+1, nz) )
        neighbors.emplace_back(nx-1, ny+1, nz);
    if( validateGrid(nx-1, ny, nz) )
        neighbors.emplace_back(nx-1, ny, nz);
    if( validateGrid(nx-1, ny-1, nz) )
        neighbors.emplace_back(nx-1, ny-1, nz);
    if( validateGrid(nx, ny-1, nz) )
        neighbors.emplace_back(nx, ny-1, nz);
    if( validateGrid(nx+1, ny-1, nz) )
        neighbors.emplace_back(nx+1, ny-1, nz);
    if( validateGrid(nx+1, ny, nz) )
        neighbors.emplace_back(nx+1, ny, nz);
    if( validateGrid(nx+1, ny+1, nz) )
        neighbors.emplace_back(nx+1, ny+1, nz);

    if( validateGrid(nx, ny, nz+1) )
        neighbors.emplace_back(nx, ny, nz+1);
    if( validateGrid(nx, ny+1, nz+1) )
        neighbors.emplace_back(nx, ny+1, nz+1);
    if( validateGrid(nx-1, ny+1, nz+1) )
        neighbors.emplace_back(nx-1, ny+1, nz+1);
    if( validateGrid(nx-1, ny, nz+1) )
        neighbors.emplace_back(nx-1, ny, nz+1);
    if( validateGrid(nx-1, ny-1, nz+1) )
        neighbors.emplace_back(nx-1, ny-1, nz+1);
    if( validateGrid(nx, ny-1, nz+1) )
        neighbors.emplace_back(nx, ny-1, nz+1);
    if( validateGrid(nx+1, ny-1, nz+1) )
        neighbors.emplace_back(nx+1, ny-1, nz+1);
    if( validateGrid(nx+1, ny, nz+1) )
        neighbors.emplace_back(nx+1, ny, nz+1);
    if( validateGrid(nx+1, ny+1, nz+1) )
        neighbors.emplace_back(nx+1, ny+1, nz+1);
    return neighbors;
}

template<class TypeItem>
bool Grid<TypeItem>::validateGrid(int nx, int ny, int nz){
    if(nx >= 0 and nx < x and ny >= 0 and ny < y and nz >= 0 and nz < z)
        return true;
    return false;
}


template<class TypeItem>
int Grid<TypeItem>::getX() const {
    return x;
}

template<class TypeItem>
int Grid<TypeItem>::getY() const {
    return y;
}

template<class TypeItem>
int Grid<TypeItem>::getZ() const {
    return z;
}
*/
#endif //BOIDS3D_GRID_H
