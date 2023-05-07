#ifndef BRICK_H
#define BRICK_H

#include <GL/gl.h>
#include <vector>

#include "coords.h"
#include "ObjetsGeometriques.h"
#include "LegoBricks.h"

enum ConnType{
	CIRCLE,CROSS
};

enum UsedConnection{
	FREE,
	USED_LEFT,
	USED_RIGHT,
	BOTH_USED
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
	
	virtual bool checkConnexion(Connector other, Link lk);
	
	void showonscreen();
	void printCharacteristics();
	
	Pos3D pos;
	Dir3D dir;
	ConnType type;
	UsedConnection inUse;
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

	bool checkConnexion(ConnectorIn conn, Link lk);
	bool checkConnexion(ConnectorOut conn, Link lk);
};

class ConnectorOut : public Connector {
public:
    ConnectorOut(
		Pos3D pos,
		Dir3D dir,
		ConnType type
	);
	ConnectorOut(const Connector& other);

	bool checkConnexion(ConnectorIn conn, Link lk);
	bool checkConnexion(ConnectorOut conn, Link lk);
};

class Brick {
public:
	Brick(void (*brickFunc)(),float* color);
	Brick(void (*brickFunc)());
    std::size_t addConnector(Connector& conn);
	void getCurrentMatrix();
	void setCurrentMatrix();
	Connector& operator[](std::size_t index);
	void connect(struct Link conn);
	void connect(int myPin, int otherPin, Brick& otherBrick,float angle, bool otherSide);
	void connect(int myPin, int otherPin, Brick& otherBrick,float angle, bool otherSide, UsedConnection firstShift, UsedConnection secondShift);
	void connect(int myPin, int otherPin, Brick& otherBrick,float angle);
	void connect(int myPin, int otherPin, Brick& otherBrick,float angle, UsedConnection firstShift, UsedConnection secondShift);
	void display();
	void printCharacteristics();
	void addConnectorsList(LiftArm& arm);
	std::vector<Connector> getConnectorList();

private:
	float *color; //float color[4];
	void (*brickFunc)();
	GLfloat currentMatrix[16];
	std::size_t nextId;
    std::vector<Connector> connectorList;
	std::vector<struct Link> connexionList;
};



struct Link{
	int myPin;
	int otherPin;
	Brick &br;
	float angle;
	bool otherSide;
	UsedConnection firstBrickUse;
	UsedConnection secondBrickUse;
};


// Nathan s'occupe de ces pièces
Brick brick6279875();
Brick brick6012451(); //ok
Brick brick4163533(); //ok
Brick brick4509897(); //ok
Brick brick4142865(); //ok
Brick brick4211815(); //ok
Brick brick370526(); //ok
Brick brick4666999(); //ok
Brick brick6159763(); //ok
Brick brick370726(); //ok
Brick brick370826(); //ok
Brick brick6332573(); //ok
Brick brick6330960(); //ok
Brick brick6276951(); //ok
Brick brick6261373(); //ok
Brick brick4512360(); //ok
Brick brick6089119(); //ok
Brick brick6209519(); //ok
Brick brick4206482(); //ok
Brick brick4177431(); //ok
Brick brick6299413(); //ok

// Quelqu'un d'autre s'occupe de celles ci
Brick brick6185471();
Brick brick4177444();
Brick brick6265135();
Brick brick6344864();
Brick brick6331723();
Brick brick6327548();
Brick brick6364749();
Brick brick4142135();
Brick brick4249021();
Brick brick6345239();
Brick brick4495935();
Brick brick6261643();
Brick brick6271156();
Brick brick6271825();
Brick brick6271810();
Brick brick4552347();
Brick brick6173003();
Brick brick6327162();
Brick brick6055519();

Brick brick6271810();
Brick brick6271164();
Brick brick6271163();
Brick brick4619323();

//jo done
Brick brick6282140();
Brick brick4211807();
Brick brick6321305();
Brick brick6275844();
Brick brick6271165();
Brick brick6276052();

//jo done but model unfinished
Brick brick6282158();

#endif
