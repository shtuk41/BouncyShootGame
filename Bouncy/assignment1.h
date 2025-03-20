

#ifndef __ASSIGNMENT_1_H
#define __ASSIGNMENT_1_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <math.h>



const int		k_iNumberOfTargets	= 10;

using namespace std;
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Location
//	Purpose:	Holder for object location on screen		
//******************************************************************
class	Location
{
public:
	Location(GLfloat x, GLfloat y):dX(x),dY(y) {}


	void	SetX(GLfloat x) {dX = x;}
	void	SetY(GLfloat y) {dY = y;}
	GLfloat	GetX() const {return dX;}
	GLfloat	GetY() const {return dY;}
private:
	GLfloat dX;
	GLfloat dY;
};
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		VisibleObject
//	Purpose:	Abstracted class for objects that is visible on display		
//******************************************************************
class	VisibleObject
{
public:
	VisibleObject(GLfloat x, GLfloat y, GLfloat sizeX, GLfloat sizeY) : cLoc(x,y),dSizeX(sizeX),dSizeY(sizeY){}

	virtual void Draw(GLfloat x, GLfloat y) = 0;

	void	SetX(GLfloat x) {cLoc.SetX(x);}
	void	SetY(GLfloat y) {cLoc.SetY(y);}
	GLfloat	GetX() const {return cLoc.GetX();}
	GLfloat	GetY() const {return cLoc.GetY();}
	void	SetLocation(GLfloat x, GLfloat y) {cLoc.SetX(x);cLoc.SetY(y);}
	GLfloat GetSizeX() const {return dSizeX;}
	GLfloat GetSizeY() const {return dSizeY;}
	Location GetLocation() const {return cLoc;}

protected:
	Location	cLoc;
	GLfloat dSizeX;
	GLfloat dSizeY;

};
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Target
//	Purpose:	This is a Target object	
//******************************************************************
class	Target : public VisibleObject
{
public:
	Target(GLfloat x, GLfloat y,GLfloat sizeX, GLfloat sizeY,GLfloat course) :VisibleObject(x,y,sizeX,sizeY),dCrs(course) { }
	void Draw(GLfloat x, GLfloat y);
	bool InBoundaries(GLfloat x, GLfloat y) const {return x > GetX() - GetSizeX() && x < GetX() + GetSizeX() && y > GetY() - GetSizeY() && y < GetY() + GetSizeY();}
	GLfloat GetCourse() const {return dCrs;}
	void SetCourse(GLfloat dNewCourse) {dCrs = static_cast<GLfloat>(fmod(double(dNewCourse),360.0));}
private:
	GLfloat dCrs;
};
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Crosshair
//	Purpose:	This is a Crosshair object
//******************************************************************
class	Crosshair : public VisibleObject
{
public:
	Crosshair(GLfloat x, GLfloat y,GLfloat sizeX, GLfloat sizeY):VisibleObject(x,y,sizeX,sizeY) {}
	void Draw(GLfloat x, GLfloat y);
};
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Display
//	Purpose:	This is a Display, it is responsibile for managing objects on screen, 
//				and provide Assignment1 with all information related to display
//******************************************************************
class	Display
{
public:
	GLfloat ConvertY(GLfloat y) {return static_cast<GLfloat>(iHeight) - y;}
	void UpdateDims(int x, int y) {iWidth = x; iHeight = y;}
	void UpdateWidth(int x) {iWidth = x;}
	void UpdateHeight(int y) {iHeight = y;}

	static Display * instance(int width = 0, int height = 0) { if (m_pInstance == 0) return m_pInstance = new Display(width,height); else return m_pInstance;}

	void Draw(VisibleObject &);
	void DrawList(list<VisibleObject *>); 
	void DrawMessage(const char *,GLfloat =-1, GLfloat =-1);
	int		GetWidth() const { return iWidth;};
	int		GetHeight() const { return iHeight;};
	bool	InBoundaries(VisibleObject * ) const;
protected:
	Display(int width, int height):iWidth(width),iHeight(height) {}
	static Display *m_pInstance;

private:
	int iWidth;
	int iHeight;
};
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Assignment1
//	Purpose:	Handles all logic
//******************************************************************
class Assignment1 : public Display
{
public:
	enum STATE {INIT = 0, RUNNING, PAUSE, END};

	

	Assignment1(int iNumTargets, int iDispWidth, int iDispHeight);
	static void Create(int iNumTargets, int iDispWidth, int iDispHeight);
	void DrawObjects() {DrawList(target);Draw(*crosshair);}
	static Assignment1* locInstance() { return (Assignment1*)(instance());}
	void	LimBoundaries(Location &,GLfloat, GLfloat);
	void	UpdateCrosshair(GLfloat x, GLfloat y);
	void	Fire(GLfloat, GLfloat);
	void	SetState(STATE e) {eState = e;}
	STATE	GetState()const { return eState;}
	Location GetCrosshairLocation() const { return crosshair->GetLocation();}
	void	MoveTargets();
	void	UpdateSize(int x, int y);
	void	SetStepsize(double d) {dStepsize = d;}
	double	GetStepsize() const {return dStepsize;}
	

protected:
	~Assignment1();
private:

	list<VisibleObject *> target;
	Crosshair *crosshair;
	STATE	eState;
	double	dStepsize;
};


#endif
