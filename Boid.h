#ifndef BOIDS3D_BOID_H
#define BOIDS3D_BOID_H

#include <GL/glut.h>
#include "tools/Vector3D.h"

class Boid{
private:
    Vector3D position;
    Vector3D velocity;
public:
    Boid(){
        position = Vector3D();
        velocity = Vector3D(1,1,0.5);
    }

    float calculateDistance(Boid* other){
        return position.DistanceTo(other->getPosition());
    }

    const Vector3D &getPosition() const {
        return position;
    }

    void setPosition(const Vector3D &position) {
        this->position = position;
    }

    const Vector3D &getVelocity() const {
        return velocity;
    }

    void setVelocity(const Vector3D &velocity) {
        this->velocity = velocity;
        this->velocity = this->velocity.Normalized();
    }

    void printPosition(){
        cout << position.getX() << " " << position.getY() << " " << position.getZ() << "    " <<
                velocity.getX() << " " << velocity.getY() << " " << velocity.getZ() <<endl;
    }

    void draw(){
        //drawing function
        float b = 2;
        float h = 3;
        float x = position.getX();
        float y = position.getY();
        float z = position.getZ();
        glBegin(GL_QUADS);
            glVertex3f(x-b*0.5, y-b*0.5, z-b*0.5);
            glVertex3f(x+b*0.5, y-b*0.5, z-b*0.5);
            glVertex3f(x+b*0.5, y-b*0.5, z+b*0.5);
            glVertex3f(x-b*0.5, y-b*0.5, z+b*0.5);
        glEnd();
        glBegin(GL_TRIANGLES);
            glVertex3f(x-b*0.5, y-b*0.5, z-b*0.5);
            glVertex3f(x+b*0.5, y-b*0.5, z-b*0.5);
            glVertex3f(x, y+h*0.5, z);

            glVertex3f(x+b*0.5, y-b*0.5, z-b*0.5);
            glVertex3f(x+b*0.5, y-b*0.5, z+b*0.5);
            glVertex3f(x, y+h*0.5, z);

            glVertex3f(x+b*0.5, y-b*0.5, z+b*0.5);
            glVertex3f(x-b*0.5, y-b*0.5, z+b*0.5);
            glVertex3f(x, y+h*0.5, z);

            glVertex3f(x-b*0.5, y-b*0.5, z-b*0.5);
            glVertex3f(x-b*0.5, y-b*0.5, z+b*0.5);
            glVertex3f(x, y+h*0.5, z);
        glEnd();
    }
};

#endif //BOIDS3D_BOID_H
