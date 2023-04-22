#ifndef __LEGO_BRICK__
#define __LEGO_BRICK__

#include <vector>
#include "LegoBricks.h"
#include "coords.h"

/*
	Utility classes that should be used to wrap the raw openGL functions 
	of the LegoBricks.h file. This classes should allow to manipulate
	the bricks together in an easier way.

	Instead of having to calculate every time which geometric 
	transformations to do to put the lego bricks together, we'll have an 
	object associated to each lego piece.

	this way, plugging two pieces should be just something like :

		brick1.getConnector(idofthepintoconnect)
			  .linkTo(brick2, idoftheotherpintoconnect, angle in degrees);
		brick1.display();

	instead of :

		glPushMatrix();
		brick1();
		glTranslatefv(positionVectorOfTheOtherBrick); // position that could be tricky to calculate
		glRotatef(orientationVectorOfTheOtherBrick); // orientation that could be tricky to calculate too
		brick2();
		glPopMatrix();

	But this will not be the only advantage of using this class... 
*/


class Brick;

class Link{
	public:
		//attributes
		float angle;
		Brick &br;
		int ConnId;

		//constructors/destructors
		Link(float angle,Brick *br, int ConnId);
		~Link();

		//methods
		void rotate(float angle);
};

enum ConnType{
	CIRCLE,CROSS
};

class Connector{
	public:
		//attributes
		int idOnBrick;
		Pos3D posOnBrick;
		Dir3D orientation;
		ConnType type;
		bool inUse;
		Link lk;
		Brick &br;

	protected:
		//constructors/destructors
		Connector(int idOnBrick, Pos3D posOnBrick, Dir3D orientation, ConnType type);
		~Connector();
};

class ConnectorIn:public Connector{
	public:
		//constructors/destructors
		ConnectorIn(int idOnBrick, Pos3D posOnBrick, Dir3D orientation, ConnType type);
		~ConnectorIn();

		//methods

		/* Connects this input connector to an OUTPUT ConnectorOut */
		void linkTo(Brick br, int connId, float angle);

		/* returns the link that has been connected to this */
		Link getLink();
};

class ConnectorOut:public Connector{
	public:
		//constructors/destructors
		ConnectorOut(int idOnBrick, Pos3D posOnBrick, Dir3D orientation, ConnType type);
		~ConnectorOut();

		//methods

		/* Connects this output connector to an INPUT ConnectorIn */
		void linkTo(Brick br, int connId, float angle);
		
		/* returns the link that has been connected to this */
		Link getLink();
};


class Brick{

	private:
		//attributes
		void (*brickFunc)(); //the raw function that adds the 3D fig to an openGL scene

	public:
		//attributes
		std::vector<Connector> connList;

		//constructor/destructor
		Brick(void (*brickFunc)());
		~Brick();

		//methods
		
		/* adds the connector in parameter to this brick */
		/* returns the id of the newly added connector */
		int addNewConnector(Connector conn);

		/* returns the connector associated to the id in parameter*/
		Connector getConnector(int connId);

		/* displays the brick in the scene 	*/
		/* calls the display methods of		*/
		/* all the bricks that 				*/
		/* have been connected to it via	*/
		/* the Connector.linkTo() method	*/
		/* of its connList					*/
		void display();

};

#endif