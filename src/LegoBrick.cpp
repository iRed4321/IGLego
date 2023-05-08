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

//different colors of the bricks
static float rouge[4] = { 1.0F,0.0F,0.0F,0.5F };
static float vert[4] = { 0.0F,1.0F,0.0F,0.5F };
static float bleu[4] = { 0.0F,0.0F,1.0F,0.5F };
static float blanc[4] = { 0.9F,0.9F,0.9F,0.5F };
static float beige[4] = { 0.8F,0.6F,0.4F,0.5F };
static float noir[4] = { 0.1F,0.1F,0.1F,0.5F };
static float bleufonce[4] = { 34.0F/255.0F, 104.0F/255.0F, 192.0F/255.0F,0.5F };
static float gris[4] = { 0.5F,0.5F,0.5F,0.5F };
static float marron[4] = { 155.0F/255.0F, 138.0F/255.0F, 112.0F/255.0F,0.5F };
static float bleuclair[4] = { 110.0F/255.0F, 182.0F/255.0F, 209.0F/255.0F,0.5F };

//useful functions



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

//************************************************************************************
//----------------------------------Defining the classes to work with-----------------
//************************************************************************************


Connector::Connector(
		Pos3D pos,
		Dir3D dir,
		ConnType type,
        bool input
	) : pos(pos), dir(dir),type(type),inUse(UsedConnection::FREE), input(input) {}

Connector::Connector(const Connector& other) {
    pos = other.pos;
    dir = other.dir;
    type = other.type;
    inUse = other.inUse;
    input = other.input;
}

bool Connector::checkConnexion(Connector other, Link lk){
    // if(this->inUse==UsedConnection::BOTH_USED){
    //     std::cout<<"cannot connect (first brick already connected (both))\n";
    //     return false;
    // }
    // if(
    //     (this->inUse==UsedConnection::USED_LEFT && lk.firstBrickUse==UsedConnection::USED_LEFT) ||
    //     (this->inUse==UsedConnection::USED_LEFT && lk.firstBrickUse==UsedConnection::BOTH_USED)
    // ){
    //     std::cout<<"cannot connect (first brick already connected(left))\n";
    //     return false;
    // }
    // if(
    //     (this->inUse==UsedConnection::USED_RIGHT && lk.firstBrickUse==UsedConnection::USED_RIGHT) ||
    //     (this->inUse==UsedConnection::USED_RIGHT && lk.firstBrickUse==UsedConnection::BOTH_USED)
    // ){
    //     std::cout<<"cannot connect (first brick already connected (right))\n";
    //     return false;
    // }

    // if(other.inUse==UsedConnection::BOTH_USED){
    //     std::cout<<"cannot connect (second brick already connected(both))\n";
    //     return false;
    // }
    // if(
    //     (other.inUse==UsedConnection::USED_LEFT && lk.secondBrickUse==UsedConnection::USED_LEFT) ||
    //     (other.inUse==UsedConnection::USED_LEFT && lk.secondBrickUse==UsedConnection::BOTH_USED)
    // ){
    //     std::cout<<"cannot connect (second brick already connected(left))\n";
    //     return false;
    // }
    // if(
    //     (other.inUse==UsedConnection::USED_RIGHT && lk.secondBrickUse==UsedConnection::USED_RIGHT) ||
    //     (other.inUse==UsedConnection::USED_RIGHT && lk.secondBrickUse==UsedConnection::BOTH_USED)
    // ){
    //     std::cout<<"cannot connect (second brick already connected(right))\n";
    //     return false;
    // }
    return true;
}

void Connector::showonscreen(){
    glPushMatrix();
        Dir3D current(0,1,0);
        glTranslatef(pos.x,pos.y,pos.z);

        Dir3D axis = current^this->dir;
        float angle = compute_angle(current,this->dir)*180/M_PI;
        glRotatef(angle,axis.x,axis.y,axis.z);
        
        glScalef(0.5,1.3,0.5);

        if (this->type == CROSS)
            mySolidCross(0.2);
        else if (this->type == CIRCLE)
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

bool ConnectorIn::checkConnexion(ConnectorIn other, Link lk){
    std::cout<<"cannot connect (Connectors in/in)\n";
    return false;
}

bool ConnectorIn::checkConnexion(ConnectorOut other, Link lk){
    if(!Connector::checkConnexion(other,lk)){
        return false;
    }
    
    if(this->type==CROSS && other.type==CIRCLE){
        std::cout<<"cannot connect (Circles don't fit in crosses)\n";
        return false;
    }
    return true;
}

bool ConnectorOut::checkConnexion(ConnectorOut other,Link lk){
    std::cout<<"cannot connect (Connectors out/out)\n";
    return false;
}

bool ConnectorOut::checkConnexion(ConnectorIn other, Link lk){
    if(!Connector::checkConnexion(other,lk)){
        return false;
    }

    if(this->type==CIRCLE && other.type==CROSS){
        std::cout<<"cannot connect (Circles don't fit in crosses)\n";
        return false;
    }
    return true;
}

void Connector::printCharacteristics(){
    std::cout<<"x : "<<this->pos.x<<std::endl;
    std::cout<<"y : "<<this->pos.y<<std::endl;
    std::cout<<"z : "<<this->pos.z<<std::endl;
    std::cout<<"xdir : "<<this->dir.x<<std::endl;
    std::cout<<"ydir : "<<this->dir.y<<std::endl;
    std::cout<<"zdir : "<<this->dir.z<<std::endl;
    this->type == CROSS ? std::cout<<"cross\n" : std::cout<<"circle\n";
    this->input ? std::cout<<"input connector\n" : std::cout<<"output connector\n";
    this->inUse ? std::cout<<"in use\n" : std::cout<<"not in use\n";
    std::cout<<"\n";
}

Brick::Brick(void (*brickFunc)(), float* color) : color(color),brickFunc(brickFunc){
    nextConnectorId = 0;
    Brick::brickList.push_back(this);
    this->id = Brick::class_id++;
}

Brick::Brick(void (*brickFunc)()) : color(vert),brickFunc(brickFunc){
    nextConnectorId = 0;
    Brick::brickList.push_back(this);
    this->id = Brick::class_id++;
}

Brick& Brick::getBrick(int id){
    return *brickList[id];
}


bool Brick::operator==(Brick br){
    return id==br.id;
}

void Brick::getCurrentMatrix(){
    glGetFloatv(GL_MODELVIEW_MATRIX, this->currentMatrix); // retrieve the current modelview matrix and save it to currentMatrix
}

void Brick::setCurrentMatrix(){
    glLoadIdentity();
    glMultMatrixf(this->currentMatrix);
}

std::vector<Connector> Brick::getConnectorList(){
    return this->connectorList;
}

std::size_t Brick::addConnector(Connector& conn) {
    connectorList.push_back(conn);
    return nextConnectorId++;
}

Connector& Brick::operator[](std::size_t index) {
    return connectorList[index];
}

void Brick::connect(struct Link lk){
    Connector myConn(this->operator[](lk.fromPin));
    
    Brick temp = Brick::getBrick(lk.otherBr);
    Connector otherConn(temp[lk.otherPin]);
    bool res;
    if (myConn.input) {
        ConnectorIn conn1(myConn);
        if (otherConn.input) {
            ConnectorIn conn2(otherConn);
            res = conn1.checkConnexion(conn2, lk);
        } else {
            ConnectorOut conn2(otherConn);
            res = conn1.checkConnexion(conn2, lk);
        }
    } else {
        ConnectorOut conn1(myConn);
        if (otherConn.input) {
            ConnectorIn conn2(otherConn);
            res = conn1.checkConnexion(conn2, lk);
        } else {
            ConnectorOut conn2(otherConn);
            res = conn1.checkConnexion(conn2, lk);
        }
    }
    if(!res)
        return;
    
    if(this->operator[](lk.fromPin).inUse==UsedConnection::FREE){
        this->operator[](lk.fromPin).inUse = lk.firstBrickUse;
    }else{
        this->operator[](lk.fromPin).inUse = UsedConnection::BOTH_USED;
    }
     
    if(Brick::getBrick(lk.otherBr)[lk.otherPin].inUse==UsedConnection::FREE){
        Brick::getBrick(lk.otherBr)[lk.otherPin].inUse = lk.secondBrickUse;
    }else{
        Brick::getBrick(lk.otherBr)[lk.otherPin].inUse = UsedConnection::BOTH_USED;
    }
    

    this->connexionList.push_back(lk);
    //std::cout<<"Connected !\n";
    
}

std::vector<struct Link> Brick::pathTo(Brick br){
    std::vector<struct Link> emptyConnexionList;

    if(*this==br){
        std::cout<<"I am already what you are looking for !"<<std::endl;
        return emptyConnexionList;
    }
    std::vector<struct Link> path = this->pathTo(br,emptyConnexionList);
    return path;
}

std::vector<struct Link> Brick::pathTo(Brick br,std::vector<struct Link> &list){
    
    for(size_t i =0; i<connexionList.size();++i){
        list.push_back(connexionList[i]);
        list = Brick::getBrick(connexionList[i].otherBr).pathTo(br, list);
        if(Brick::getBrick(list.back().otherBr)==br){
            return list;
        }
        list.pop_back();
    }
    return list;
}

void Brick::reset_class_id(){
    Brick::class_id=0;
}


void printLink(struct Link lk){
    std::cout<<"\tfromBr : " <<Brick::getBrick(lk.fromBr).name << lk.fromBr <<std::endl;
    std::cout<<"\totherBr : " <<Brick::getBrick(lk.otherBr).name <<lk.otherBr <<std::endl<<std::endl;
    std::cout<<"\tfromPin : " <<lk.fromPin <<std::endl;
    std::cout<<"\totherPin : " <<lk.otherPin <<std::endl<<std::endl;
}
void printLinkList(std::vector<struct Link> list){
    for(size_t i = 0; i < list.size(); ++i){
        std::cout<<"Element " <<i <<std::endl;
        printLink(list[i]);
    }
}

std::vector<struct Link>& Brick::getConnexionList(){
    return connexionList;
}

void Brick::disconnect(struct Link lk){
    

    // REMOVING CONNEXION FROM THE FROM-BRICK
    bool flag = false;
    for (size_t i = 0; i< connexionList.size(); ++i){
        if(Brick::getBrick(connexionList[i].otherBr) == *brickList[lk.otherBr] && i < connexionList.size()-1){
            flag = true;
            struct Link lkk = connexionList[i];
            assign(&(connexionList[i]),&(connexionList[i+1]));
            assign(&(connexionList[i+1]),&lkk);
        }
    }
    if(flag){
        connexionList.pop_back();

        //retrait du point de connexion sur le connecteur from
        if(lk.firstBrickUse==BOTH_USED){
            this->operator[](lk.fromPin).inUse = FREE;
        }
        if(lk.firstBrickUse==USED_LEFT && this->operator[](lk.fromPin).inUse==USED_LEFT){
            this->operator[](lk.fromPin).inUse = FREE;
        }
        if(lk.firstBrickUse==USED_LEFT && this->operator[](lk.fromPin).inUse==BOTH_USED){
            this->operator[](lk.fromPin).inUse = USED_RIGHT;
        }
        if(lk.firstBrickUse==USED_RIGHT && this->operator[](lk.fromPin).inUse==USED_RIGHT){
            this->operator[](lk.fromPin).inUse = FREE;
        }
        if(lk.firstBrickUse==USED_RIGHT && this->operator[](lk.fromPin).inUse==BOTH_USED){
            this->operator[](lk.fromPin).inUse = USED_LEFT;
        }

        //retrait du point de connexion sur le connecteur other
        if(lk.secondBrickUse==BOTH_USED){
            Brick::getBrick(lk.otherBr)[lk.otherPin].inUse = FREE;
            return;
        }
        if(lk.secondBrickUse==USED_LEFT && Brick::getBrick(lk.otherBr)[lk.otherPin].inUse==USED_LEFT){
            Brick::getBrick(lk.otherBr)[lk.otherPin].inUse = FREE;
            return;
        }
        if(lk.secondBrickUse==USED_LEFT && Brick::getBrick(lk.otherBr)[lk.otherPin].inUse==BOTH_USED){
            Brick::getBrick(lk.otherBr)[lk.otherPin].inUse = USED_RIGHT;
            return;
        }

        if(lk.secondBrickUse==USED_RIGHT && Brick::getBrick(lk.otherBr)[lk.otherPin].inUse==USED_RIGHT){
            Brick::getBrick(lk.otherBr)[lk.otherPin].inUse = FREE;
            return;
        }
        if(lk.secondBrickUse==USED_RIGHT && Brick::getBrick(lk.otherBr)[lk.otherPin].inUse==BOTH_USED){
            Brick::getBrick(lk.otherBr)[lk.otherPin].inUse = USED_LEFT;
            return;
        }
            
    }
}

Brick Brick::operator=(Brick& br){
    this->brickFunc = br.brickFunc;
    this->color = br.color;
    this->name = br.name;
    this->nextConnectorId = br.nextConnectorId;
    this->id = br.id;
    this->connectorList = br.connectorList;
    this->connexionList = br.connexionList; 
    return *this;
}

int Brick::getId(){
    return id;
}

void assign(struct Link *lk, struct Link *lkk){
    lk->fromBr = lkk->fromBr;
	lk->fromPin = lkk->fromPin;
	lk->otherPin = lkk->otherPin;
	lk->otherBr = lkk->otherBr;
	lk->angle=lkk->angle;
	lk->otherSide = lkk->otherSide;
	lk->firstBrickUse = lkk->firstBrickUse;
	lk->secondBrickUse = lkk->secondBrickUse;
}

void reverseLink(struct Link lk){

    // REMOVING CONNEXION FROM THE FROM-BRICK
    Brick::getBrick(lk.fromBr).disconnect(lk);
    
    Link lkk = 
    {
        Brick::getBrick(lk.otherBr).getId(),
        lk.otherPin,
        lk.fromPin,
        Brick::getBrick(lk.fromBr).getId(),
        -lk.angle,
        lk.otherSide,
        lk.secondBrickUse == BOTH_USED ? lk.secondBrickUse : (lk.secondBrickUse == USED_LEFT ? USED_RIGHT : USED_LEFT),
        lk.firstBrickUse == BOTH_USED ? lk.firstBrickUse : (lk.firstBrickUse == USED_LEFT ? USED_RIGHT : USED_LEFT),
        
    };

    ////// ADDING REVERSED CONNEXION TO THE OTHER BRICK
    //Brick::getBrick(lk.otherBr).printCharacteristics();
    Brick::getBrick(lk.otherBr).connect(lkk);

}

void reverseLinks(std::vector<struct Link> list){
    for(auto& elem : list){
        reverseLink(elem);
    }
}

void Brick::connect(int myPin, int otherPin, Brick& br,float angle, bool otherSide){
    struct Link lk = 
    {
        this->id,
        myPin,
        otherPin,
        br.id,
        angle,
        otherSide,
        UsedConnection::BOTH_USED,
        UsedConnection::BOTH_USED
    };
    this->connect(lk);
}

void Brick::connect(int myPin, int otherPin, Brick& br,float angle, bool otherSide, UsedConnection firstShift, UsedConnection secondShift){
    struct Link lk = 
    {
        this->id,
        myPin,
        otherPin,
        br.id,
        angle,
        otherSide,
        firstShift,
        secondShift
    };
    this->connect(lk);
}

void Brick::connect(int myPin, int otherPin, Brick& br,float angle){
    struct Link lk = 
    {
        this->id,
        myPin,
        otherPin,
        br.id,
        angle,
        false,
        UsedConnection::BOTH_USED,
        UsedConnection::BOTH_USED
    };
    this->connect(lk);
}

void Brick::connect(int myPin, int otherPin, Brick& br,float angle, UsedConnection firstShift, UsedConnection secondShift){
    struct Link lk = 
    {
        this->id,
        myPin,
        otherPin,
        br.id,
        angle,
        false,
        firstShift,
        secondShift
    };
    this->connect(lk);
}

void BrickUseShift(UsedConnection shift){
    switch(shift){
            case UsedConnection::BOTH_USED :
                //do nothing, the block is well placed
                break;
            case UsedConnection::USED_LEFT :
                glTranslatef(0,0.25,0);
                break;
            case UsedConnection::USED_RIGHT :
                glTranslatef(0,-0.25,0);
                break;
            default :
                std::cout<<"Unusable shift value\n";
        }
}

void Brick::display(){
    
    glMaterialfv(GL_FRONT,GL_DIFFUSE,this->color);
	brickFunc();
    size_t nblinks = connexionList.size();

    getCurrentMatrix();
    Pos3D zero(0,0,0);

    for(size_t i = 0; i<nblinks; ++i){
        //replace ourself at the position of the origin of the current brick
        setCurrentMatrix();

        //retrieve the values of the connections to use
        Link lk = connexionList[i];
        Connector myConn(this->operator[](lk.fromPin));
        Connector otherConn(Brick::getBrick(lk.otherBr)[lk.otherPin]);
        
        //move to the position of the first connector
        glTranslatef(myConn.pos.x, myConn.pos.y, myConn.pos.z);

        //rotate to align ourself with the connector
        Dir3D vertic(0,1,0);
        Dir3D axis = vertic^myConn.dir;
        float angle = compute_angle(vertic,myConn.dir)*180/M_PI;
        glRotatef(angle,axis.x,axis.y,axis.z);
        
        //shift following the way the first connector is used
        BrickUseShift(lk.firstBrickUse);

        //make a U turn if the connection is on the otherside
        glRotatef(lk.angle,0,1,0);
        if(lk.otherSide){
            glRotatef(180,1,0,0);
        }

        //shift following the way the second connector is used
        BrickUseShift(lk.secondBrickUse);


        //rotate to align the second brick to the connection
        axis = vertic^otherConn.dir;
        angle = compute_angle(vertic,otherConn.dir)*180/M_PI;
        glRotatef(-angle,axis.x,axis.y,axis.z);
        
        //move backward to put the second brick relatively to the first brick 
        Pos3D nextPos = zero - otherConn.pos;
        glTranslatef(nextPos.x,nextPos.y,nextPos.z);

        //saving the current position into the brick
        Brick::getBrick(lk.otherBr).getCurrentMatrix();
        
        //displaying the brick we just placed
        Brick::getBrick(lk.otherBr).display();
    }
    //going back to the position of the current piece
    setCurrentMatrix();
}

void Brick::setRoot(Brick& br){
    std::vector<struct Link> vec = pathTo(br);
    reverseLinks(vec);
}

void Brick::addConnectorsList(LiftArm &arm){
    nextConnectorId = 0;

    for (auto model : arm.models){
        for(auto [pos, part] : model){
            nextConnectorId++;
            Pos3D pos1 = Pos3D(pos.x,pos.z,pos.y);

            Dir3D dir = Dir3D(0,0,1);

            // switch (part.orientation){

            //     case Front:
            //     case Right:
            //     case Top:
            //         dir = Dir3D(0,0,1);
            //         break;

            //     case Back:
            //     case Left:
            //     case Bottom:
            //         dir = Dir3D(0,0,-1);
            //         break;

            //     default:
            //         break;
            // }

            switch (part.kind){
                case ArmWithCross:
                case ArmAngleWithCross:
                case ArmEndWithCross:
                {
                    ConnectorIn conn1(pos1,dir,CROSS);
                    connectorList.push_back(conn1);
                    break;
                }

                case ArmEnd:
                case ArmAngle:
                case Arm:{
                    ConnectorIn conn1(pos1,dir,CIRCLE);
                    connectorList.push_back(conn1);
                    break;
                }

                default:
                    std::cout<<"error : part not found\n";
                    nextConnectorId--;
                    break;
            }
        }
    }

}

void Brick::printCharacteristics(){
    std::cout<<"--------Connectors--------"<<std::endl;
    for (size_t i = 0; i<nextConnectorId;++i){
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

//**********************************************************************************
//________________________________________Wrapping the lego pieces__________________
//**********************************************************************************

Brick brick6279875(){
    Brick br(batonnetNoir_6279875,noir);
    br.name = "batonnet noir";
    ConnType type = CIRCLE;
    Pos3D pos(0,-0.5,0);
    Dir3D dir(0,1,0);
    
    ConnectorOut firstConn(pos,dir,type);
    br.addConnector(firstConn);

    pos.update(0,0.5,0);
    dir.update(0,1,0);
    
    ConnectorOut secondConn(pos,dir,type);
    br.addConnector(secondConn);

    return br;
}

Brick brick370726(){
    Brick br(axle8_370726, noir);
    br.name = "moyen baton noir";
    float posy = -3.5;

    ConnType type = CROSS;
    Pos3D pos(0,posy,0);
    Dir3D dir(0,1,0);

    for(int i = 0; i<8;++i){
        pos.update(0,posy+i,0);
        
        ConnectorOut conn(pos,dir,type);
        br.addConnector(conn);
    }

    return br;
}

Brick brick370826(){
    Brick br(axle12_370826, noir);
    br.name = "grand baton noir";
    float posy = -5.5;

    ConnType type = CROSS;
    Pos3D pos(0,posy,0);
    Dir3D dir(0,1,0);

    for(int i = 0; i<12;++i){
        pos.update(0,posy+i,0);
        
        ConnectorOut conn(pos,dir,type);
        br.addConnector(conn);
    }

    return br;
}

Brick brick4211815(){
    Brick br(axle3_4211815, gris);
    br.name = "batonnet gris";

    float posy = -1;

    ConnType type = CROSS;
    Pos3D pos(0,posy,0);
    Dir3D dir(0,1,0);

    for(int i = 0; i<3;++i){
        pos.update(0,posy+i,0);
        
        ConnectorOut conn(pos,dir,type);
        br.addConnector(conn);
    }

    return br;
}

Brick brick6332573(){
    Brick br(axleAndPinConnector1_6332573,blanc);
    br.name = "cylindre et croix creux blanc perpendic";

    ConnType type = CIRCLE;
    Pos3D pos(0,0,0);
    Dir3D dir(0,1,0);
    
    ConnectorIn firstConn(pos,dir,type);
    br.addConnector(firstConn);

    type = CROSS;
    pos.update(1,0,0);
    dir.update(1,0,0);
    
    ConnectorIn secondConn(pos,dir,type);
    br.addConnector(secondConn);

    return br;
}

Brick brick6265135(){
    Brick br(liftarm1x2ThickWithPinHoleAndAxleHole_6265135,blanc);
    br.name = "cylindre et croix creux blanc meme sens";

    ConnType type = CROSS;
    Pos3D pos(0,0,0);
    Dir3D dir(0,1,0);
    
    ConnectorIn firstConn(pos,dir,type);
    br.addConnector(firstConn);

    type = CIRCLE;
    pos.update(1,0,0);
    dir.update(0,1,0);
    
    ConnectorIn secondConn(pos,dir,type);
    br.addConnector(secondConn);

    return br;
}

Brick brick6012451(){
    Brick br(gear8ToothType2_6012451, noir);
    br.name = "roue crantée 8 dents";

    ConnType type = CROSS;
    Pos3D pos(0,0,0);
    Dir3D dir(0,1,0);
    
    ConnectorIn firstConn(pos,dir,type);
    br.addConnector(firstConn);
    return br;
}

Brick brick4163533(){
    Brick br(liftarmThin1x2AxleHoles_4163533,blanc);
    br.name = "truc plat blanc 2 trous en croix";


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

Brick brick4142865(){
    Brick br(axle2Notched_4142865);
    br.name = "batonnet rouge tout nul";

    ConnType type = CROSS;
    Pos3D pos(0,-0.5,0);
    Dir3D dir(0,1,0);
    
    ConnectorOut firstConn(pos,dir,type);
    br.addConnector(firstConn);

    type = CROSS;
    pos.update(0,0.5,0);
    dir.update(0,1,0);
    
    ConnectorOut secondConn(pos,dir,type);
    br.addConnector(secondConn);

    return br;
}

Brick brick6330960(){
    Brick br(axleAndPinConnectorPerpendicular3LWith2PinHoles_6330960,blanc);
    br.name = "deux cylindre et croix en trous perpendic blancs";
    
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

Brick brick4509897(){
    Brick br(plate4x8_4509897,beige);
    br.name = "grande plaque";
    
    ConnType type = CIRCLE;
    Pos3D pos(0,0,0);
    Dir3D dir(0,1,0);
    
    ConnectorIn firstConn(pos,dir,type);
    br.addConnector(firstConn);

    type = CIRCLE;
    pos.update(1,0,0);
    dir.update(1,0,0);

    ConnectorIn conn2(pos,dir,type);
    br.addConnector(conn2); 
    return br;
}

Brick brick6276951(){
    Brick br(axleAndPinConnectorPerpendicular3LWithCenterPinHole_6276951,noir);
    br.name = "deux trous croix au bords et cylindre perpendic au centre noir";

    ConnType type = CIRCLE;
    Pos3D pos(0,0,0);
    Dir3D dir(0,1,0);

    ConnectorIn conn1(pos,dir,type);
    br.addConnector(conn1); 

    type = CROSS;
    pos.update(1,0,0);
    dir.update(0,0,1);

    ConnectorIn conn2(pos,dir,type);
    br.addConnector(conn2);

    type = CROSS;
    pos.update(-1,0,0);
    dir.update(0,0,1);

    ConnectorIn conn3(pos,dir,type);
    br.addConnector(conn3);

    return br;
}

Brick brick6261373(){
    Brick br(axleAndPinConnectorPerpendicular_6261373,rouge); 
    br.name = "trous cylindre et croix perpendic rouge";
    
    ConnType type = CROSS;
    Pos3D pos(0,0,0);
    Dir3D dir(0,1,0);

    ConnectorIn conn1(pos,dir,type);
    br.addConnector(conn1); 

    type = CIRCLE;
    pos.update(1,0,0);
    dir.update(0,0,1);

    ConnectorIn conn2(pos,dir,type);
    br.addConnector(conn2);


    return br;
}

Brick brick4512360(){
    Brick br(axleConnectorSmoothWithXHoleOrientation_4512360,gris);
    br.name = "connecteur a 2 batons croix alignés";

    ConnType type = CROSS;
    Pos3D pos(0,-0.5,0);
    Dir3D dir(0,1,0);

    ConnectorIn conn1(pos,dir,type);
    br.addConnector(conn1); 

    type = CROSS;
    pos.update(0,0.5,0);
    dir.update(0,1,0);

    ConnectorIn conn2(pos,dir,type);
    br.addConnector(conn2);
    
    return br;
}

Brick brick6089119(){
    Brick br(axlePin3LWithFrictionRidgesLengthwiseAnd2LAxle_6089119,noir); 
    br.name = "baton croix noir et embout circulaire";

    ConnType type = CIRCLE;
    Pos3D pos(0,0,0);
    Dir3D dir(0,1,0);

    ConnectorOut conn1(pos,dir,type);
    br.addConnector(conn1); 

    type = CROSS;
    pos.update(0,1,0);
    dir.update(0,1,0);

    ConnectorOut conn2(pos,dir,type);
    br.addConnector(conn2);

    type = CROSS;
    pos.update(0,2,0);
    dir.update(0,1,0);

    ConnectorOut conn3(pos,dir,type);
    br.addConnector(conn3);

    return br;
}

Brick brick6209519(){
    Brick br(axlePin3LWithFrictionRidgesLengthwise_6209519,rouge); 
    br.name = "baton circulaire rouge et embout croix";
    
    ConnType type = CROSS;
    Pos3D pos(0,0,0);
    Dir3D dir(0,1,0);

    ConnectorOut conn1(pos,dir,type);
    br.addConnector(conn1); 

    type = CIRCLE;
    pos.update(0,1,0);
    dir.update(0,1,0);

    ConnectorOut conn2(pos,dir,type);
    br.addConnector(conn2);

    type = CIRCLE;
    pos.update(0,2,0);
    dir.update(0,1,0);

    ConnectorOut conn3(pos,dir,type);
    br.addConnector(conn3);
    
    return br;
}

Brick brick4206482(){
    Brick br(axlePinWithFrictionRidgesLengthwise_4206482,bleufonce); 
    br.name = "bleu baton croix";

    ConnType type = CROSS;
    Pos3D pos(0,0,0);
    Dir3D dir(0,1,0);

    ConnectorOut conn1(pos,dir,type);
    br.addConnector(conn1); 

    type = CIRCLE;
    pos.update(0,1,0);
    dir.update(0,1,0);

    ConnectorOut conn2(pos,dir,type);
    br.addConnector(conn2);

    return br;
}
Brick brick4177431(){
    Brick br(gear12ToothDoubleBevel_4177431,noir);
    br.name = "roue crantee 12 dents";

    ConnType type = CROSS;
    Pos3D pos(0,0,0);
    Dir3D dir(0,1,0);

    ConnectorIn conn1(pos,dir,type);
    br.addConnector(conn1); 
    return br;
}


Brick brick4666999(){
    Brick br(axle4WithCenterStop_4666999, beige);
    br.name = "baton beige chelou";

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

    type = CIRCLE;
    pos.update(0,-0.5,0);
    dir.update(0,1,0);
    
    ConnectorOut fourthConn(pos,dir,type);
    br.addConnector(fourthConn);

    return br;
}

Brick brick6185471(){
    Brick br(gearWormScrew_6185471,beige);
    br.name = "piece trop stylee";

    ConnType type = CROSS;
    Pos3D pos(0,-0.5,0);
    Dir3D dir(0,1,0);
    
    ConnectorIn firstConn(pos,dir,type);
    br.addConnector(firstConn);

    type = CROSS;
    pos.update(0,0.5,0);
    dir.update(0,1,0);
    
    ConnectorIn secondConn(pos,dir,type);
    br.addConnector(secondConn);    

    return br;
}

Brick brick6159763(){
    Brick br(axle5WithStop_6159763, noir);
    br.name = "baton noir avec stop";

    
    ConnType type = CROSS;
    Pos3D pos(0,-2,0);
    Dir3D dir(0,1,0);
    
    ConnectorOut firstConn(pos,dir,type);
    br.addConnector(firstConn);

    type = CROSS;
    pos.update(0,-1,0);
    dir.update(0,1,0);
    
    ConnectorOut secondConn(pos,dir,type);
    br.addConnector(secondConn);

    type = CROSS;
    pos.update(0,0,0);
    dir.update(0,1,0);
    
    ConnectorOut thirdConn(pos,dir,type);
    br.addConnector(thirdConn);

    type = CROSS;
    pos.update(0,1,0);
    dir.update(0,1,0);
    
    ConnectorOut fourthConn(pos,dir,type);
    br.addConnector(fourthConn);

    type = CROSS;
    pos.update(0,2,0);
    dir.update(0,1,0);
    
    ConnectorOut fifthConn(pos,dir,type);
    br.addConnector(fifthConn);

    return br;
}

Brick brick6299413(){
    Brick br(pinLongWithFrictionRidgesLengthwise_6299413,bleufonce);
    br.name = "long connecteur bleu fonce circulaire";

    ConnType type = CIRCLE;
    Pos3D pos(0,-1,0);
    Dir3D dir(0,1,0);

    ConnectorOut conn1(pos,dir,type);
    br.addConnector(conn1); 

    type = CIRCLE;
    pos.update(0,0,0);
    dir.update(0,1,0);

    ConnectorOut conn2(pos,dir,type);
    br.addConnector(conn2);

    type = CIRCLE;
    pos.update(0,1,0);
    dir.update(0,1,0);

    ConnectorOut conn3(pos,dir,type);
    br.addConnector(conn3);

    return br;
}

Brick brick4177444(){
    Brick br(liftarm1x2Thick_4177444, noir);
    br.name = "deux cylindres noirs";

    LiftArm arm = liftArm4177444();
    br.addConnectorsList(arm);
    return br;
}

Brick brick6344864(){
    Brick br(liftarm1x2ThickWithPinHoleAndAxleHole_6344864, marron);
    br.name = "trous cylindre et croix a cote thick";

    LiftArm arm = liftArm6344864();
    br.addConnectorsList(arm);
    return br;
}

Brick brick6331723(){
    Brick br(liftarm1x3Thin_6331723, noir);
    br.name = "fin noir croix au bouts noir 3";

    LiftArm arm = liftArm6331723();
    br.addConnectorsList(arm);
    return br;
}

Brick brick6327548(){
    Brick br(liftarm1x4Thin_6327548, noir);
    br.name = "fin noir croix au bouts noir 4";


    LiftArm arm = liftArm6327548();
    br.addConnectorsList(arm);
    return br;
}

Brick brick6364749(){
    Brick br(liftarm1x4Thin_6364749, bleuclair);
    br.name = "fin noir croix au bouts bleuclair 4";

    LiftArm arm = liftArm6364749();
    br.addConnectorsList(arm);
    return br;
}

Brick brick4142135(){
    Brick br(liftarm1x5Thick_4142135,noir);
    br.name = "epais cylindres noir 5";

    LiftArm arm = liftArm4142135();
    br.addConnectorsList(arm);
    return br;
}

Brick brick4249021(){
    Brick br(liftarm1x5Thick_4249021, blanc);
    br.name = "epais cylindres blanc";

    LiftArm arm = liftArm4249021();
    br.addConnectorsList(arm);
    return br;
}

Brick brick6345239(){
    Brick br(liftarm1x6Thin_6345239, blanc);
    br.name = "fin blanc croix au bouts 6";

    LiftArm arm = liftArm6345239();
    br.addConnectorsList(arm);
    return br;
}

Brick brick4495935(){
    Brick br(liftarm1x7Thick_4495935, noir);
    br.name = "baton cylindres noir 7";

    LiftArm arm = liftArm4495935();
    br.addConnectorsList(arm);
    return br;
}

Brick brick6261643(){
    Brick br(liftarm1x13Thick_6261643, bleuclair);
    br.name = "GROS BATON EPAIS BLEU CLAIR 13 COMME L'ENFER";

    LiftArm arm = liftArm6261643();
    br.addConnectorsList(arm);
    return br;
}

Brick brick6271825(){
    Brick br(liftarm2x4LShapeThick_6271825, noir);
    br.name = "machin epais noir 2x4";

    LiftArm arm = liftArm6271825();
    br.addConnectorsList(arm);
    return br;
}

Brick brick6271810(){
    Brick br(liftarm3x3LShapeThin_6271810, noir);
    br.name = "truc en L 3x3 fin noir";

    LiftArm arm = liftArm6271810();
    br.addConnectorsList(arm);
    return br;
}

Brick brick4552347(){
    Brick br(liftarm3x3TShapeThick_4552347, noir);
    br.name = "T 3x3 epais noir";

    LiftArm arm = liftArm4552347();
    br.addConnectorsList(arm);
    return br;
}

Brick brick6173003(){
    Brick br(liftarm3x5LShapeThick_6173003,bleuclair);
    br.name = "truc en L 3x5 epais bleu clair";

    LiftArm arm = liftArm6173003();
    br.addConnectorsList(arm);
    return br;
}

Brick brick6271156(){
    Brick br(liftarm1x115DoubleBentThick_6271156,gris);
    br.name = "double amel bent lol thick";


	Model m = Model();

	m[Pos3d{0,0,0}] = LegoPart{Front, ArmEndWithCross};
	m[Pos3d{1,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{2,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{3,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{4,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{5,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{6,0,0}] = LegoPart{Back, ArmEnd};

	LiftArm arm = LiftArm(THICK, m);
    br.addConnectorsList(arm);

    ConnectorIn conn = ConnectorIn(Pos3D(8.12,2.12,0), Dir3D(0,0,1), CIRCLE);
    br.addConnector(conn);
    conn = ConnectorIn(Pos3D(8.12,3.12,0), Dir3D(0,0,1), CIRCLE);
    br.addConnector(conn);
    conn = ConnectorIn(Pos3D(8.12,4.12,0), Dir3D(0,0,-1), CROSS);
    br.addConnector(conn);

    return br;
}

Brick brick6055519(){
    Brick br(liftarm3X5PerpendicularHShapeThick_6055519,gris);
    br.name = "truc en H 3x5 gris";

    
    ConnType type = CIRCLE;
    Pos3D pos(0,0,0);
    Dir3D dir(0,0,1);

    ConnectorIn conn1(pos,dir,type);
    br.addConnector(conn1);

    type = CIRCLE;
    pos.update(1,0,0);
    dir.update(0,0,1);

    ConnectorIn conn2(pos,dir,type);
    br.addConnector(conn2);

     type = CIRCLE;
    pos.update(2,0,0);
    dir.update(0,0,1);

    ConnectorIn conn3(pos,dir,type);
    br.addConnector(conn3);

     type = CIRCLE;
    pos.update(1,1,0);
    dir.update(1,0,0);

    ConnectorIn conn4(pos,dir,type);
    br.addConnector(conn4);

    type = CIRCLE;
    pos.update(1,2,0);
    dir.update(1,0,0);

    ConnectorIn conn5(pos,dir,type);
    br.addConnector(conn5);

    type = CIRCLE;
    pos.update(1,3,0);
    dir.update(1,0,0);

    ConnectorIn conn6(pos,dir,type);
    br.addConnector(conn6);

    type = CIRCLE;
    pos.update(0,4,0);
    dir.update(0,0,1);

    ConnectorIn conn7(pos,dir,type);
    br.addConnector(conn7);

    type = CIRCLE;
    pos.update(1,4,0);
    dir.update(0,0,1);

    ConnectorIn conn8(pos,dir,type);
    br.addConnector(conn8);

    type = CIRCLE;
    pos.update(2,4,0);
    dir.update(0,0,1);

    ConnectorIn conn9(pos,dir,type);
    br.addConnector(conn9);
    
    return br;
}

Brick brick6282140(){
    Brick br(pinWithFrictionRidgesLengthwiseAndPinHole_6282140,noir);
    br.name = "Bitoniau noir";
    
    ConnType type = CIRCLE;
    Pos3D pos(0,0,0);
    Dir3D dir(0,1,0);

    ConnectorOut conn1(pos,dir,type);
    br.addConnector(conn1); 

    pos.update(0,1,0);
    dir.update(1,0,0);

    ConnectorIn conn2(pos,dir,type);
    br.addConnector(conn2);
    
    return br;
}

Brick brick4211807(){
    Brick br(pinWithoutFrictionRidgesLengthwise_4211807,gris);
    br.name = "pin gris j'en sais pas plus";

    ConnType type = CIRCLE;
    Pos3D pos(0,0.5,0);
    Dir3D dir(0,1,0);

    ConnectorOut conn1(pos,dir,type);
    br.addConnector(conn1); 

    pos.update(0,-0.5,0);
    dir.update(0,-1,0);
    ConnectorOut conn2(pos,dir,type);
    br.addConnector(conn2);

    return br;
}

Brick brick6321305(){
    Brick br(pinLongWithoutFrictionRidgesLengthwise_6321305,beige);
    br.name = "pin long beige qui glisse";

    ConnType type = CIRCLE;
    Pos3D pos(0,-1,0);
    Dir3D dir(0,1,0);

    ConnectorOut conn1(pos,dir,type);
    br.addConnector(conn1); 

    type = CIRCLE;
    pos.update(0,0,0);
    dir.update(0,1,0);

    ConnectorOut conn2(pos,dir,type);
    br.addConnector(conn2);

    type = CIRCLE;
    pos.update(0,1,0);
    dir.update(0,1,0);

    ConnectorOut conn3(pos,dir,type);
    br.addConnector(conn3);

    return br;
}

Brick brick6275844(){
    Brick br(bush_6275844,gris);
    br.name = "bush ? ah ! entretoise";


    ConnType type = CROSS;
    Pos3D pos(0,0,0);
    Dir3D dir(0,1,0);

    ConnectorIn conn1(pos,dir,type);
    br.addConnector(conn1); 

    return br;
}

Brick brick6271165(){
    Brick br(bush1By2Smooth_6271165,gris);
    br.name = "DEMI entretoise";
    

    ConnType type = CROSS;
    Pos3D pos(0,0,0);
    Dir3D dir(0,1,0);

    ConnectorIn conn1(pos,dir,type);
    br.addConnector(conn1); 

    return br;
}

Brick brick6276052(){
    Brick br(drivingRingConnector_6276052,blanc);
    br.name = "gros connecteur a batons blanc";


    ConnType type = CROSS;
    Pos3D pos(0,-0.5,0);
    Dir3D dir(0,1,0);

    ConnectorIn conn1(pos,dir,type);
    br.addConnector(conn1); 

    pos.update(0,0.5,0);
    dir.update(0,1,0);

    ConnectorIn conn2(pos,dir,type);
    br.addConnector(conn2);

    return br;
}

Brick brick6282158(){
    Brick br(pinConnectorPerpendicular3LWith4Pins_6282158,gris);
    br.name = "pinConnectorPerpendicular3LWith4Pins_6282158";
    
    ConnType type = CIRCLE;
    Pos3D pos(0,0,0);
    Dir3D dir(0,1,0);

    ConnectorIn conn1(pos,dir,type);
    br.addConnector(conn1); 

    pos.update(1,0,0);
    dir.update(0,0,1);

    ConnectorIn conn2(pos,dir,type);
    br.addConnector(conn2);

    pos.update(-1,0,0);
    dir.update(0,0,1);

    ConnectorIn conn3(pos,dir,type);
    br.addConnector(conn3);

    pos.update(-1,1,0);
    dir.update(0,1,0);

    ConnectorOut conn4(pos,dir,type);
    br.addConnector(conn4);

    pos.update(-1,-1,0);

    ConnectorOut conn5(pos,dir,type);
    br.addConnector(conn5);

    pos.update(1,1,0);

    ConnectorOut conn6(pos,dir,type);
    br.addConnector(conn6);

    pos.update(1,-1,0);

    ConnectorOut conn7(pos,dir,type);
    br.addConnector(conn7);

    return br;
}

Brick brick4619323(){
    Brick br(tire304x14OffsetTreadBandAroundCenterOfTread_4619323,noir);
    br.name = "PNEUUUUUU";

    ConnType type = CIRCLE;
    Pos3D pos(0,0,0);
    Dir3D dir(0,0,1);

    ConnectorIn conn1(pos,dir,type);
    br.addConnector(conn1); 

    return br;
}

Brick brick6327162(){
    Brick br(liftarm3x5LShapeWithQuarterEllipseThin_6327162,noir);
    LiftArm arm = liftArm6327162();
    br.addConnectorsList(arm);
    return br;
}