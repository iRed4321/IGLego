#ifndef BRICK_H
#define BRICK_H

#include <vector>
#include "coords.h"

enum ConnType{
	CIRCLE,CROSS
};

class Brick;
struct Link;
class Connector;
class ConnectorIn;
class ConnectorOut;


class Connector {
public:
    Connector(
		Pos3D pos,
		Dir3D dir,
		ConnType type,
		bool input
	);
	Connector(const Connector& other);
	
	virtual bool checkConnexion(Connector other);
	
	void showonscreen();
	void printCharacteristics();
	
	Pos3D pos;
	Dir3D dir;
	ConnType type;
	bool inUse;
	bool input;
};

class ConnectorIn : public Connector {
public:
    ConnectorIn(
		Pos3D pos,
		Dir3D dir,
		ConnType type
	);
	ConnectorIn(const Connector& other);

	bool checkConnexion(ConnectorIn conn);
	bool checkConnexion(ConnectorOut conn);
};

class ConnectorOut : public Connector {
public:
    ConnectorOut(
		Pos3D pos,
		Dir3D dir,
		ConnType type
	);
	ConnectorOut(const Connector& other);

	bool checkConnexion(ConnectorIn conn);
	bool checkConnexion(ConnectorOut conn);
};

class Brick {
public:
	Brick(void (*brickFunc)());
    std::size_t addConnector(Connector& conn);
	Connector& operator[](std::size_t index);
	void connect(struct Link conn);
	void connect(int myPin, int otherPin, Brick& otherBrick,float angle);
	void display();
	void printCharacteristics();

private:
	void (*brickFunc)();
	std::size_t nextId;
    std::vector<Connector> connectorList;
	std::vector<struct Link> connexionList;
};

struct Link{
	int myPin;
	int otherPin;
	Brick &br;
	float angle;
};

//builds the construction at the current position on the scene
void construction();

#endif
