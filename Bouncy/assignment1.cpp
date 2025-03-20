#include "assignment1.h"

Display *Display::m_pInstance = 0;

//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Target
//	Function:	Draw
//	Inputs:		GLfloat x - target X position, 
//				GLfloat y - target Y position
//	Output:		None
//	Purpose:	Target Drawing Routine
//******************************************************************
void Target::Draw(GLfloat x, GLfloat y)
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x - 10.0f,y - 10.0f);
	glVertex2f(x + 10.0f,y - 10.0f);
	glVertex2f(x + 10.0f,y + 10.0f);
	glVertex2f(x - 10.0f,y + 10.0f);
	glEnd();
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Crosshair
//	Function:	Draw
//	Inputs:		GLfloat x - crosshair X position, 
//				GLfloat y - crosshair Y position
//	Output:		None
//	Purpose:	Crosshair Drawing Routine
//******************************************************************
void Crosshair::Draw(GLfloat x, GLfloat y)
{
	glColor3f(0.0,1.0,1.0);
	glBegin(GL_LINES);
	glVertex2f(x,y - 10.0f);
	glVertex2f(x,y + 10.0f);
	glVertex2f(x - 10.0f,y);
	glVertex2f(x + 10.0f,y);
	glEnd();
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Display
//	Function:	Draw
//	Inputs:		VisibleObject 
//	Output:		None
//	Purpose:	Drawing VisibleObjects like Target and Crosshair
//				Do any Display dependent routines here
//******************************************************************
void Display::Draw(VisibleObject &p_cVo)
{
	p_cVo.Draw(p_cVo.GetX(),ConvertY(p_cVo.GetY()));
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Display
//	Function:	DrawList
//	Inputs:		List of VisibleObjects 
//	Output:		None
//	Purpose:	Drawing list of VisibleObjects 
//				Do any Display dependent routines here for drawing a list of objects
//******************************************************************
void Display::DrawList(list<VisibleObject *> p_cVo)
{

	list<VisibleObject *>::iterator it;

	for (it = p_cVo.begin(); it != p_cVo.end(); it++)
	{
		if ((*it)->GetX() > iWidth)
			(*it)->SetX(GLfloat(iWidth));
		if ((*it)->GetY() > iHeight)
			(*it)->SetY(GLfloat(iHeight));

		(*it)->Draw((*it)->GetX(),ConvertY((*it)->GetY()));
	}
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Display
//	Function:	DrawMessage
//	Inputs:		message, message position 
//	Output:		None
//	Purpose:	Drawing text message
//				Do any display dependent conversions or routines here
//******************************************************************
void Display::DrawMessage(const char *message,GLfloat x, GLfloat y)
{

	GLfloat textX = x < 0 ? iWidth / 2 : x;
	GLfloat textY = ConvertY( y < 0 ? iHeight / 2 : y);

	
	glColor3f(1.0,0.0,0.0);
	glRasterPos2f(textX,textY);

	for (int ii = 0; message != 0 && message[ii] != '\0';ii++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,message[ii]);
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Display
//	Function:	InBoundaries
//	Inputs:		VisibleObject
//	Output:		return true if object in boundaries and false otherwise
//	Purpose:	checks if object is in display boundaries
//******************************************************************
bool	Display::InBoundaries(VisibleObject *p_vo) const
{
	if (p_vo == 0)
		return false;

	if (p_vo == 0 || (p_vo->GetX() - p_vo->GetSizeX()) < 0.0 ||
		(p_vo->GetX()  + p_vo->GetSizeX()) > GLfloat(iWidth) ||
		(p_vo->GetY()- p_vo->GetSizeY()) < 0.0 ||
		(p_vo->GetY() + p_vo->GetSizeY())> GLfloat(iHeight))
		return false;
	 
	return true;
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Assignment1
//	Function:	Assignment1 constructor
//	Inputs:		Number of targets, Display Width and Height
//	Output:		none
//	Purpose:	Setup of display dimensions and targets
//******************************************************************
Assignment1::Assignment1(int iNumTargets, int iDispWidth, int iDispHeight):Display(iDispWidth,iDispHeight),eState(Assignment1::INIT),dStepsize(0.1)
{
	srand(unsigned int(time (NULL)));
	
	for (int ii = 0; ii < iNumTargets;ii++)
	{

		Location cLoc( GLfloat(rand() % GetWidth()),GLfloat(rand() % GetHeight()));
		int iCourse		= rand() % 360;
		LimBoundaries(cLoc,10,10);
		target.push_back(new Target(cLoc.GetX(),cLoc.GetY(),10,10,GLfloat(iCourse)));
	}

	Location cLoc( GLfloat(rand() % GetWidth()),GLfloat(rand() % GetHeight()));
	LimBoundaries(cLoc,10,10);
	crosshair = new Crosshair(cLoc.GetX(),cLoc.GetY(),10,10);
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Assignment1
//	Function:	Create
//	Inputs:		number of targets, display width and height
//	Output:		none
//	Purpose:	This is function needs to be called to create Assignment1 instance
//******************************************************************
void Assignment1::Create(int iNumTargets, int iDispWidth, int iDispHeight)
{
	if (m_pInstance)
		;
	else
		m_pInstance = new Assignment1((iNumTargets < 1 || iNumTargets > 20 ? 1 :  iNumTargets), iDispWidth, iDispHeight);
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Assignment1
//	Function:	~Assignment1
//	Inputs:		none
//	Output:		none
//	Purpose:	Assignment1 destructor
//******************************************************************
Assignment1::~Assignment1()
{
	delete crosshair;

//	for (unsigned int ii = 0; ii < target.size(); ii++)
//		delete target[ii];
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Assignment1
//	Function:	LimBoundaries
//	Inputs:		object location, its lateral and vertical sizes
//	Output:		none
//	Purpose:	Helps to keep objects in Display range
//******************************************************************
void Assignment1::LimBoundaries(Location &cLoc, GLfloat sizeX, GLfloat sizeY)
{
		if (cLoc.GetX() < sizeX)
			cLoc.SetX(sizeX);
		if (cLoc.GetX() > (GetWidth() - sizeX))
			cLoc.SetX(GetWidth() - sizeX);
		if (cLoc.GetY() < sizeY)
			cLoc.SetY(sizeY);
		if (cLoc.GetY() > (GetWidth() - sizeY))
			cLoc.SetX(GetWidth() - sizeY);
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Assignment1
//	Function:	UpdateCrosshair
//	Inputs:		X and Y position for Crosshair
//	Output:		none
//	Purpose:	Updates Crosshair position when mouse moves
//******************************************************************
void Assignment1::UpdateCrosshair(GLfloat x, GLfloat y)
{
	if (crosshair)
		crosshair->SetLocation(x,y);
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Assignment1
//	Function:	Fire
//	Inputs:		X and Y position of Fire shot
//	Output:		none
//	Purpose:	Logic for firing and destroying targtes
//******************************************************************
void	Assignment1::Fire(GLfloat x, GLfloat y)
{
	list<VisibleObject *>::iterator it;

	for (it = target.begin(); it != target.end(); it++)	
	{
		if ((static_cast<Target *>(*it))->InBoundaries(x,y))
		{
			delete *it;
			target.erase(it);
			break;
		}
	}

	if (target.size() < 1)
		SetState(END);
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Assignment1
//	Function:	MoveTargets
//	Inputs:		none
//	Output:		none
//	Purpose:	Logic for moving and bouncing objects
//		******		MOTION MOMENTUM IS NOT CONSIDERED YET, UPDATE IF TIME ALLOWS ******
//******************************************************************
void	Assignment1::MoveTargets()
{
	list<VisibleObject *>::iterator it;

	for (it = target.begin(); it != target.end(); it++)	
	{
		Target *tgt = static_cast<Target *>(*it);

		if (!InBoundaries(tgt))
		{
			tgt->SetCourse(tgt->GetCourse() + GLfloat(90.0));
		}

		tgt->SetX(tgt->GetX() + GLfloat(dStepsize * cos(3.14 / 180.0 *tgt->GetCourse())));
		tgt->SetY(tgt->GetY() + GLfloat(dStepsize * sin(3.14 / 180.0 *tgt->GetCourse())));

		if (!InBoundaries(tgt))
		{
			Location loc = tgt->GetLocation();

			LimBoundaries(loc,10.0,10.0);
		}

	}
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Assignment1
//	Function:	UpdateSize
//	Inputs:		none
//	Output:		none
//	Purpose:	This function helps to keep objects in displayed area 
//				when window is resized...
//******************************************************************
void	Assignment1::UpdateSize(int x, int y)
{
	UpdateDims(x,y);

	list<VisibleObject *>::iterator it;

	for (it = target.begin(); it != target.end(); it++)
	{
		if ((*it)->GetX() -  (*it)->GetSizeX() < 0)
			(*it)->SetX(GLfloat(GetWidth()) +  (*it)->GetSizeX());
		if ((*it)->GetY() -  (*it)->GetSizeY() < 0)
			(*it)->SetY(GLfloat(GetHeight()) +  (*it)->GetSizeY());
		if ((*it)->GetX() +  (*it)->GetSizeX() > GetWidth())
			(*it)->SetX(GLfloat(GetWidth()) -  (*it)->GetSizeX());
		if ((*it)->GetY() +  (*it)->GetSizeY() > GetHeight())
			(*it)->SetY(GLfloat(GetHeight()) -  (*it)->GetSizeY());
	}
}



