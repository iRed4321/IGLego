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
static float beige[4] = { 0.4F,3.0F,3.0F,0.5F };
static float noir[4] = { 0.1F,0.1F,0.1F,0.5F };
static float gris[4] = { 0.5F,0.5F,0.5F,0.5F };
static float bleuclair[4] = { 3.0F,3.0F,1.0F,0.5F };
static float bleufonce[4] = { 0.0F,0.0F,5.0F,0.5F };


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
	) : pos(pos), dir(dir),type(type),inUse(UsedConnection::Free), input(input) {}

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
    nextId = 0;
}

Brick::Brick(void (*brickFunc)()) : color(vert),brickFunc(brickFunc){
    nextId = 0;
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
    return nextId++;
}

Connector& Brick::operator[](std::size_t index) {
    return connectorList[index];
}

void Brick::connect(struct Link lk){
    Connector myConn(this->operator[](lk.myPin));
    Connector otherConn(lk.br[lk.otherPin]);
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
    
    // th
    // this->operator[](lk.myPin).inUse = true;
    // lk.br[lk.otherPin].inUse = true;

    this->connexionList.push_back(lk);
    //std::cout<<"Connected !\n";
}

void Brick::connect(int myPin, int otherPin, Brick& br,float angle, bool otherSide){
    struct Link lk = {myPin,otherPin,br,angle,otherSide,Shift::FullSize};
    this->connect(lk);
}

void Brick::connect(int myPin, int otherPin, Brick& br,float angle,bool otherSide, Shift shift){
    struct Link lk = {myPin,otherPin,br,angle,otherSide,shift};
    this->connect(lk);
}

void Brick::connect(int myPin, int otherPin, Brick& br,float angle){
    struct Link lk = {myPin,otherPin,br,angle,false,Shift::FullSize};
    this->connect(lk);
}

void Brick::connect(int myPin, int otherPin, Brick& br,float angle, Shift shift){
    struct Link lk = {myPin,otherPin,br,angle,false,shift};
    this->connect(lk);
}

void Brick::display(){

    glMaterialfv(GL_FRONT,GL_DIFFUSE,this->color);
	brickFunc();
    size_t nblinks = connexionList.size();

    getCurrentMatrix();
    Pos3D zero(0,0,0);

    for(size_t i = 0; i<nblinks; ++i){
        setCurrentMatrix();
        Link lk = connexionList[i];
        Connector myConn(this->operator[](lk.myPin));
        Connector otherConn(lk.br[lk.otherPin]);
        
        glTranslatef(myConn.pos.x, myConn.pos.y, myConn.pos.z);

        Dir3D vertic(0,1,0);
        Dir3D axis = vertic^myConn.dir;
        float angle = compute_angle(vertic,myConn.dir)*180/M_PI;
        glRotatef(angle,axis.x,axis.y,axis.z);
        

        glRotatef(lk.angle,0,1,0);
        if(lk.otherSide){
            glRotatef(180,1,0,0);
        }

        axis = vertic^otherConn.dir;
        angle = compute_angle(vertic,otherConn.dir)*180/M_PI;
        glRotatef(-angle,axis.x,axis.y,axis.z);
        
        Pos3D nextPos = zero - otherConn.pos;
        glTranslatef(nextPos.x,nextPos.y,nextPos.z);

        printf("myConn.dir : %f %f %f\n",myConn.dir.x,myConn.dir.y,myConn.dir.z);
        printf("otherConn.dir : %f %f %f\n",otherConn.dir.x,otherConn.dir.y,otherConn.dir.z);


        Dir3D shift;

        shift.x = otherConn.dir.x == 0 ? 0 : 0.25;
        shift.y = otherConn.dir.y == 0 ? 0 : 0.25;
        shift.z = otherConn.dir.z == 0 ? 0 : 0.25;

        //printf("shift : %f %f %f\n",shift.x,shift.y,shift.z);

        if (lk.shift == Shift::HalfLeft) {
            glTranslatef(-shift.x,-shift.y,-shift.z);
        } else if (lk.shift == Shift::HalfRight) {
            glTranslatef(shift.x,shift.y,shift.z);
        }
        lk.br.getCurrentMatrix();
        lk.br.display();

    }
}

void Brick::addConnectorsList(LiftArm &arm){
    nextId = 0;
    for(auto [pos, part] : arm.model){
        nextId++;
        Pos3D pos1 = Pos3D(pos.x,pos.z,pos.y);

        Dir3D dir = Dir3D(0,0,1);

        switch (part.orientation){

            case Front:
            case Right:
                dir = Dir3D(0,0,1);
                break;

            case Back:
            case Left:
                dir = Dir3D(0,0,-1);
                break;

            default:
                break;
        }

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
                nextId--;
                break;
        }
    }
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

//**********************************************************************************
//________________________________________Wrapping the lego pieces__________________
//**********************************************************************************

Brick brick6012451(){
    Brick br(gear8ToothType2_6012451, noir);
    ConnType type = CROSS;
    Pos3D pos(0,0,0);
    Dir3D dir(0,1,0);
    
    ConnectorIn firstConn(pos,dir,type);
    br.addConnector(firstConn);
    return br;
}

Brick brick4163533(){
    Brick br(liftarmThin1x2AxleHoles_4163533,blanc);

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

Brick brick6330960(){
    Brick br(axleAndPinConnectorPerpendicular3LWith2PinHoles_6330960,blanc);
    
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
    ConnType type = CROSS;
    Pos3D pos(0,0,0);
    Dir3D dir(0,1,0);

    ConnectorIn conn1(pos,dir,type);
    br.addConnector(conn1); 
    return br;
}


Brick brick4666999(){
    Brick br(axle4WithCenterStop_4666999, beige);

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

Brick brick6159763(){
    Brick br(axle5WithStop_6159763, noir);
    
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
    LiftArm arm = liftArm4177444();
    br.addConnectorsList(arm);
    return br;
}

Brick brick6344864(){
    Brick br(liftarm1x2ThickWithPinHoleAndAxleHole_6344864, gris);
    LiftArm arm = liftArm6344864();
    br.addConnectorsList(arm);
    return br;
}

Brick brick6331723(){
    Brick br(liftarm1x3Thin_6331723, noir);
    LiftArm arm = liftArm6331723();
    br.addConnectorsList(arm);
    return br;
}

Brick brick6327548(){
    Brick br(liftarm1x4Thin_6327548, noir);
    LiftArm arm = liftArm6327548();
    br.addConnectorsList(arm);
    return br;
}

Brick brick6364749(){
    Brick br(liftarm1x4Thin_6364749, bleuclair);
    LiftArm arm = liftArm6364749();
    br.addConnectorsList(arm);
    return br;
}

Brick brick4142135(){
    Brick br(liftarm1x5Thick_4142135,noir);
    LiftArm arm = liftArm4142135();
    br.addConnectorsList(arm);
    return br;
}

Brick brick4249021(){
    Brick br(liftarm1x5Thick_4249021, blanc);
    LiftArm arm = liftArm4249021();
    br.addConnectorsList(arm);
    return br;
}

Brick brick6345239(){
    Brick br(liftarm1x6Thin_6345239, blanc);
    LiftArm arm = liftArm6345239();
    br.addConnectorsList(arm);
    return br;
}

Brick brick4495935(){
    Brick br(liftarm1x7Thick_4495935, noir);
    LiftArm arm = liftArm4495935();
    br.addConnectorsList(arm);
    return br;
}

Brick brick6261643(){
    Brick br(liftarm1x13Thick_6261643, bleuclair);
    LiftArm arm = liftArm6261643();
    br.addConnectorsList(arm);
    return br;
}

Brick brick6271825(){
    Brick br(liftarm2x4LShapeThick_6271825, noir);
    LiftArm arm = liftArm6271825();
    br.addConnectorsList(arm);
    return br;
}

Brick brick6271810(){
    Brick br(liftarm3x3LShapeThin_6271810, noir);
    LiftArm arm = liftArm6271810();
    br.addConnectorsList(arm);
    return br;
}

Brick brick4552347(){
    Brick br(liftarm3x3TShapeThick_4552347, noir);
    LiftArm arm = liftArm4552347();
    br.addConnectorsList(arm);
    return br;
}

Brick brick6173003(){
    Brick br(liftarm3x5LShapeThick_6173003,bleuclair);
    LiftArm arm = liftArm6173003();
    br.addConnectorsList(arm);
    return br;
}

Brick brick6271156(){
    Brick br(liftarm1x115DoubleBentThick_6271156,gris);

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
    conn = ConnectorIn(Pos3D(8.12,4.12,0), Dir3D(0,0,1), CROSS);
    br.addConnector(conn);

    return br;
}

Brick brick6055519(){
    Brick br(liftarm3X5PerpendicularHShapeThick_6055519,gris);
    
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
    
    ConnType type = CIRCLE;
    Pos3D pos(0,0,0);
    Dir3D dir(0,1,0);

    ConnectorOut conn1(pos,dir,type);
    br.addConnector(conn1); 

    pos.update(0,1.5,0);
    dir.update(1,0,0);

    ConnectorIn conn2(pos,dir,type);
    br.addConnector(conn2);
    
    return br;
}

Brick brick4211807(){
    Brick br(pinWithoutFrictionRidgesLengthwise_4211807,gris);

    ConnType type = CIRCLE;
    Pos3D pos(0,0.5,0);
    Dir3D dir(0,1,0);

    ConnectorOut conn1(pos,dir,type);
    br.addConnector(conn1); 

    pos.update(0,-0.5,0);
    dir.update(0,-1,0);
    ConnectorIn conn2(pos,dir,type);
    br.addConnector(conn2);

    return br;
}

Brick brick6321305(){
    Brick br(pinLongWithoutFrictionRidgesLengthwise_6321305,beige);

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