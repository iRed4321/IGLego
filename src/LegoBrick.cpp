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
		ConnType type,
        bool input
	) : pos(pos), dir(dir),type(type),inUse(false), input(input) {}

Connector::Connector(const Connector& other) {
    pos = other.pos;
    dir = other.dir;
    type = other.type;
    inUse = other.inUse;
    input = other.input;
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
	) : Connector(pos, dir, type, false) {}

ConnectorOut::ConnectorOut(const Connector& other) : Connector(other) {}

ConnectorIn::ConnectorIn(
		Pos3D pos,
		Dir3D dir,
		ConnType type
	) : Connector(pos, dir, type, true) {}

ConnectorIn::ConnectorIn(const Connector& other) : Connector(other) {}

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
    return true;
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



void Brick::connect(struct Link lk){
    Connector myConn = this->operator[](lk.myPin);
    Connector otherConn = lk.br[lk.otherPin];
    bool res;
    
    if (myConn.input) {
        ConnectorIn conn1(myConn);
        if (otherConn.input) {
            ConnectorIn conn2(otherConn);
            res = conn1.checkConnexion(conn2);
        } else {
            ConnectorOut conn2(otherConn);
            res = conn1.checkConnexion(conn2);
        }
    } else {
        ConnectorOut conn1(myConn);
        if (otherConn.input) {
            ConnectorIn conn2(otherConn);
            res = conn1.checkConnexion(conn2);
        } else {
            ConnectorOut conn2(otherConn);
            res = conn1.checkConnexion(conn2);
        }
    }
    if(!res)
        return;
    
    this->operator[](lk.myPin).inUse = true;
    lk.br[lk.otherPin].inUse = true;
    this->printCharacteristics();
    lk.br.printCharacteristics();

    this->connexionList.push_back(lk);
    std::cout<<"Connected !\n";
}

void Brick::connect(int myPin, int otherPin, Brick& br,float angle){
    struct Link lk = {myPin,otherPin,br,angle};
    this->connect(lk);
}

void Brick::display(){
	brickFunc();
}

void Brick::printCharacteristics(){
    std::cout<<"--------Connectors--------"<<std::endl;
    for (size_t i = 0; i<nextId;++i){
        std::cout<<"connector n°" <<i <<" :" <<std::endl;
        Connector c = this->operator[](i);
        std::cout<<"\tx : "<<c.pos.x<<std::endl;
        std::cout<<"\ty : "<<c.pos.y<<std::endl;
        std::cout<<"\tz : "<<c.pos.z<<std::endl;
        std::cout<<"\txdir : "<<c.dir.x<<std::endl;
        std::cout<<"\tydir : "<<c.dir.y<<std::endl;
        std::cout<<"\tzdir : "<<c.dir.z<<std::endl;
        std::cout<<"\t";
        c.type == CROSS ? std::cout<<"cross\n" : std::cout<<"circle\n";
        std::cout<<"\t";
        c.input ? std::cout<<"input connector\n" : std::cout<<"output connector\n";
        std::cout<<"\t";
        c.inUse ? std::cout<<"in use\n" : std::cout<<"not in use\n";
        std::cout<<"\n";
    }
    std::cout<<"--------Connexions--------"<<std::endl;
    std::cout<<"number of connexions : "<<connexionList.size()<<std::endl;
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

Brick brick4666999(){
    Brick br(axle4WithCenterStop_4666999);

    ConnType type = CROSS;
    Pos3D pos(0,-1.5,0);
    Dir3D dir(0,1,0);
    
    ConnectorOut firstConn(pos,dir,type);
    br.addConnector(firstConn);

    type = CROSS;
    pos.update(0,0.5,0);
    dir.update(0,1,0);
    
    ConnectorOut secondConn(pos,dir,type);
    br.addConnector(secondConn);

    type = CROSS;
    pos.update(0,1.5,0);
    dir.update(0,1,0);
    
    ConnectorOut thirdConn(pos,dir,type);
    br.addConnector(thirdConn);

    return br;
}

void construction(){
    Brick brick1 = brick6330960();
    Brick brick2 = brick4666999();
    Brick brick3 = brick4163533();
    
    //brick1.display();
    struct Link lk = {0,0,brick2,0};
    // brick1.connect(0,0,brick2,0);
    brick1.connect(lk);

}


int main() {
    Brick brick1 = brick6330960();
    Brick brick2 = brick4666999();
    Brick brick3 = brick4163533();
    
    //brick1.display();
    std::cout<<"-_-_-_-_-_-_-_-_-_-_-_-"<<std::endl;
    brick2.printCharacteristics();
    std::cout<<"-_-_-_-_-_-_-_-_-_-_-_-"<<std::endl;

    brick1.connect(0,0,brick2,0);

    std::cout<<"-_-_-_-_-_-_-_-_-_-_-_-"<<std::endl;
    brick2.printCharacteristics();
    std::cout<<"-_-_-_-_-_-_-_-_-_-_-_-"<<std::endl;

    brick2.connect(1,0,brick3,0);

    std::cout<<"-_-_-_-_-_-_-_-_-_-_-_-"<<std::endl;
    brick2.printCharacteristics();
    std::cout<<"-_-_-_-_-_-_-_-_-_-_-_-"<<std::endl;

    return 0;
}