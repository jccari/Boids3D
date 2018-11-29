#ifndef BOIDS3D_VECTOR3DHASHER_H
#define BOIDS3D_VECTOR3DHASHER_H

#include <glob.h>
#include <iostream>
#include "Vector3D.h"

using namespace std;

#define SIZE 1000
#define GRIDSIZE 100

class Vector3DHasher{

public:
    Vector3D operator()(const Vector3D &vector) const{
        Vector3D pos = Vector3D();
        size_t xvalue = std::hash<int>()(vector.getX());
        size_t yvalue = std::hash<int>()(vector.getY());
        size_t zvalue = std::hash<int>()(vector.getZ());

        pos.setX(floor(vector.getX()/GRIDSIZE));
        pos.setY(floor(vector.getY()/GRIDSIZE));
        pos.setZ(floor(vector.getZ()/GRIDSIZE));

        /*
        cout << "Hasher" << endl;
        cout << pos.getX() << endl;
        cout << pos.getY() << endl;
        cout << pos.getZ() << endl;
        */
        return pos;
    }
};

#endif //BOIDS3D_VECTOR3DHASHER_H
