#include <vector>
#include <iostream>

#include "LegoBrick.h"
#include "LegoBricks.h"

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

bool Connector::checkConnexion(Connector other){
    std::cout<<"Cannot check connexion with unspecified Connector\n";
    return false;
}

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

void construction(){
    Brick br(axleAndPinConnectorPerpendicular3LWith2PinHoles_6330960);
    br.display();
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