#ifndef BOIDS3D_FLOCK_H
#define BOIDS3D_FLOCK_H

#include "tools/Grid.h"
#include "tools/Vector3DHasher.h"
#include "Boid.h"

class Flock{
private:
    typedef vector<Boid*> ListBoids;

    Grid<ListBoids, Boid*>* grid;
    ListBoids allBoidsList;
    int numBoids;
    Vector3DHasher hasher;

    // temporal Variable for test
    int ratio = 10;
    float separationDist = 5;
    float maxVelocity = 10;
public:
    Flock(int num){
        grid = new Grid<ListBoids, Boid*>(10,10,10);
        numBoids = num;

        createFlock();
    }

    void draw(){
        for(auto boid: allBoidsList)
            boid->draw();
    }

    void createFlock(){
        for (int i = 0; i < numBoids ; ++i) {
            Boid* boid = new Boid();
            Vector3D gridPos = hasher(boid->getPosition());
            saveBoid(boid, gridPos);
        }
    }

    void init(){
        while(true){
        //for(int i=0; i<10; i++){
            for( Boid* boid: allBoidsList){

                //boid->draw();

                Vector3D gridPosition = hasher(boid->getPosition());

                ListBoids neighborGrids = grid->getNeighborGrids(gridPosition.getX(), gridPosition.getY(), gridPosition.getZ());

                moveBoid(boid, neighborGrids);

                boid->printPosition();

            }
            cout << endl;
        }
    }

    void saveBoid(Boid* boid, Vector3D position){
        grid->insert(boid, (int)position.getX(), (int)position.getY(), (int)position.getZ());
        allBoidsList.push_back(boid);
    }

    /**
     * Apply rules
     */
    void moveBoid(Boid* boid, ListBoids neighGrids){
        Vector3D v1, v2, v3;

        ListBoids filteredBoids = filter(boid, neighGrids);

        for (Boid* other: filteredBoids){
            v1 = cohesion(boid, filteredBoids);
            v2 = separation(boid, filteredBoids);
            v3 = aligment(boid, filteredBoids);

            boid->setVelocity( boid->getVelocity() + v1 + v2 + v3 );
            boid->setPosition( boid->getVelocity() + boid->getVelocity() );
            //boid->setVelocity( boid->getVelocity().ClampLength(maxVelocity) );
        }
    }

    // RULE 1
    Vector3D cohesion(Boid* boid, ListBoids neighbords){
        Vector3D result;
        for(Boid* other: neighbords)
            result += other->getPosition();
        result = result / neighbords.size();
        return (result- boid->getPosition())/100;
    }

    // RULE 2
    Vector3D separation(Boid* boid, ListBoids neighbords){
        Vector3D result;
        for(Boid* other: neighbords){
            if( boid->calculateDistance(other) < separationDist )
                result = result - ( other->getPosition() - boid->getPosition() );
        }
        return result;
    }

    // RULE 3
    Vector3D aligment(Boid* boid, ListBoids neighbords){
        Vector3D result;
        for(Boid* other: neighbords)
            result += other->getVelocity();

        result = result /neighbords.size();
        return (boid->getVelocity()- result)/ 8;
    }


    ListBoids filter(Boid* targetBoid, ListBoids listGridBoids){
        ListBoids listBoids;
        for (Boid* other : listGridBoids) {
            if ( targetBoid != other and isInVisionAngle(targetBoid, other) )
                listBoids.push_back(other);
        }
        return listBoids;
    }

    bool isInVisionAngle(Boid* targetBoid, Boid* other){
        if(targetBoid->calculateDistance(other) <= ratio){
            return true;
        }
        return false;
    }
};

#endif //BOIDS3D_FLOCK_H
