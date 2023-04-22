#include <vector>
#include <iostream>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159235
#endif

#include "LegoBrick.h"
#include "LegoBricks.h"


float compute_angle( Dir3D vector1, Dir3D vector2) {
    float angle;
    float dot_product = vector1*vector2;
    float magnitude1 = sqrt(vector1*vector1);
    float magnitude2 = sqrt(vector2*vector2);
    angle = acos(dot_product / (magnitude1 * magnitude2));
    return angle;
}

void funcToTest(){
    std::cout<<"Hello World ! \n";
}

Connector::Connector(
		Pos3D pos,
		Dir3D dir,
		ConnType type
	) : pos(pos), dir(dir),type(type) {}

Connector::Connector(const Connector& other) {
    pos = other.pos;
    dir = other.dir;
    type = other.type;
    inUse = other.inUse;
}

bool Connector::checkConnexion(Connector other){
    std::cout<<"Cannot check connexion with unspecified Connector\n";
    return false;
}

void Connector::showonscreen(){
    glPushMatrix();
        Dir3D current(0,1,0);
        glTranslatef(pos.x,pos.y,pos.z);

        Dir3D axis = current^this->dir;
        float angle = compute_angle(current,this->dir)*180/M_PI;
        glRotatef(angle,axis.x,axis.y,axis.z);
        
        glScalef(0.5,1.3,0.5);
        cylinder(0.2);
    glPopMatrix();
}

ConnectorOut::ConnectorOut(
		Pos3D pos,
		Dir3D dir,
		ConnType type
	) : Connector(pos, dir, type) {}

ConnectorIn::ConnectorIn(
		Pos3D pos,
		Dir3D dir,
		ConnType type
	) : Connector(pos, dir, type) {}

bool ConnectorIn::checkConnexion(ConnectorIn other){
    std::cout<<"cannot connect (Connectors in/in)\n";
    return false;
}

bool ConnectorIn::checkConnexion(ConnectorOut other){
    if(this->inUse || other.inUse){
        std::cout<<"cannot connect (already connected)\n";
        return false;
    }
    if(this->type==CROSS && other.type==CIRCLE){
        std::cout<<"cannot connect (Circles don't fit in crosses)\n";
        return false;
    }
    return true;
}

bool ConnectorOut::checkConnexion(ConnectorOut other){
    std::cout<<"cannot connect (Connectors out/out)\n";
    return false;
}

bool ConnectorOut::checkConnexion(ConnectorIn other){
    if(this->inUse || other.inUse){
        std::cout<<"cannot connect (already connected)\n";
        return false;
    }
    if(this->type==CIRCLE && other.type==CROSS){
        std::cout<<"cannot connect (Circles don't fit in crosses)\n";
        return false;
    }
    return false;
}

Brick::Brick(void (*brickFunc)()) : brickFunc(brickFunc){
    nextId = 0;
}

std::size_t Brick::addConnector(Connector& conn) {
    connectorList.push_back(conn);
    return nextId++;
}

Connector& Brick::operator[](std::size_t index) {
    return connectorList[index];
}



void Brick::connect(struct Connexion conn){
    Connector* myPin =&(this->operator[](conn.myPin));
    Connector* otherPin = &(conn.br[conn.otherPin]);
    bool res;
    
    ConnectorIn* conn1 = dynamic_cast<ConnectorIn*>(myPin);
    
    if (conn1) {
        ConnectorIn* conn2 = dynamic_cast<ConnectorIn*>(otherPin);
        if (conn2) {
            res = conn1->checkConnexion(*conn2);
        } else {
            ConnectorOut* conn2bis = dynamic_cast<ConnectorOut*>(otherPin);
            res = conn1->checkConnexion(*conn2bis);
        }
    }
    else {
        ConnectorOut* conn1bis = dynamic_cast<ConnectorOut*>(myPin);

        ConnectorIn* conn2 = dynamic_cast<ConnectorIn*>(otherPin);
        if (conn2) {
            res = conn1bis->checkConnexion(*conn2);
        } else {
            ConnectorOut* conn2bis = dynamic_cast<ConnectorOut*>(otherPin);
            res = conn1bis->checkConnexion(*conn2bis);
        }
    }

    if(!res)
        return;
    
    this->operator[](conn.myPin).inUse = true;
    conn.br[conn.otherPin].inUse = true;
    this->connexionList.push_back(conn);
    std::cout<<"Connected !\n";
}

void Brick::display(){
	brickFunc();
}

Brick brick6330960(){
    Brick br(axleAndPinConnectorPerpendicular3LWith2PinHoles_6330960);
    
    ConnType type = CROSS;
    Pos3D pos(0,0,0);
    Dir3D dir(0,1,0);
    
    ConnectorIn firstConn(pos,dir,type);
    br.addConnector(firstConn);

    type = CIRCLE;
    pos.update(1,0,0);
    dir.update(0,0,1);
    
    ConnectorIn secondConn(pos,dir,type);
    br.addConnector(secondConn);

    type = CIRCLE;
    pos.update(2,0,0);
    dir.update(0,0,1);
    
    ConnectorIn thirdConn(pos,dir,type);
    br.addConnector(thirdConn);

    return br;
}

Brick brick4163533(){
    Brick br(liftarmThin1x2AxleHoles_4163533);

    ConnType type = CROSS;
    Pos3D pos(0,0,0);
    Dir3D dir(0,1,0);
    
    ConnectorIn firstConn(pos,dir,type);
    br.addConnector(firstConn);

    type = CROSS;
    pos.update(1,0,0);
    dir.update(0,1,0);
    
    ConnectorIn secondConn(pos,dir,type);
    br.addConnector(secondConn);

    return br;
}

void construction(){
    Brick brick1 = brick6330960();
    Brick brick2 = brick4163533();
    brick1[0].showonscreen();
    brick1.display();

    glTranslatef(-1,-1,-1);
    brick2[0].showonscreen();
    brick2.display();
}

/*
int main() {
    Brick brick(funcToTest);

    
    Pos3D pos(0,0,0);
    Dir3D dir(1,0,0);
    ConnectorIn conn(pos, dir, CROSS);

    brick.addConnector(conn);

    brick.display();
    return 0;
}
*/