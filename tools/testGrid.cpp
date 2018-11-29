//
// Created by jccari on 11/21/18.
//
#include <iostream>
#include "Grid.h"

using namespace std;

template <class Type>
bool testValidation(Grid<Type> &grid){
    bool validate = true;
    for (int i = 0; i < grid.getX() ; ++i) {
        for (int j = 0; j < grid.getY(); ++j) {
            for (int k = 0; k < grid.getZ() ; ++k) {
                validate = validate and grid.validateGrid(i,j,k);
            }
        }
    }
    return validate;
}

//template<class Type>
void printVector(vector<int>& v){
    for (int i = 0; i < v.size() ; ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
}

//template <class Type>
bool testNeighbors(Grid<int> &grid) {
    vector<int> tmp;

    tmp = grid.getNeighbors(0,2,2);
    cout <<"tam: " <<tmp.size() << endl;
    printVector(tmp);

    return true;
}

int main(){
    Grid<int> grid(5,5,5);

    //cout << testValidation<int>(grid) << endl;

    testNeighbors(grid);

    grid.insert(100,1,1,1);
    return 0;
}
