#include "assignment1.h"

#define rate 0.01

//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	myMouseEvent
//	Inputs:		mouse button, state, position
//	Output:		none
//	Purpose:	Callback that handles mouse events
//******************************************************************
void myMouseEvent(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && button == GLUT_DOWN)
	{
		Assignment1::locInstance()->Fire(Assignment1::locInstance()->GetCrosshairLocation().GetX(),Assignment1::locInstance()->GetCrosshairLocation().GetY());
	}
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	myMouseMotion
//	Inputs:		position
//	Output:		none
//	Purpose:	Callback that handles mouse motion when button is pushed
//******************************************************************
void myMouseMotion(int x, int y)
{
	Assignment1::locInstance()->UpdateCrosshair(GLfloat(x),GLfloat(y));
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	myMousePassiveMotion
//	Inputs:		position
//	Output:		none
//	Purpose:	Callback that handles mouse motion when button is not pushed
//******************************************************************
void myMousePassiveMotion(int x,int y)
{
	Assignment1::locInstance()->UpdateCrosshair(GLfloat(x),GLfloat(y));
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	myMouseEntryEvent
//	Inputs:		position
//	Output:		none
//	Purpose:	Callback that handles mouse leaving and entering display window
//******************************************************************
void myMouseEntryEvent(int)
{
		
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	myKeyboard
//	Inputs:		key and mouse position
//	Output:		none
//	Purpose:	Callback that handles keyboard
//******************************************************************
void myKeyboard(unsigned char key,int x, int y)
{
	if (Assignment1::locInstance()->GetState() == Assignment1::RUNNING && (key == 'm' || key == 'M'))
		Assignment1::locInstance()->SetState(Assignment1::PAUSE); 
	else if (Assignment1::locInstance()->GetState() == Assignment1::PAUSE && (key == 'm' || key == 'M'))
		Assignment1::locInstance()->SetState(Assignment1::RUNNING);
	else if (Assignment1::locInstance()->GetState() == Assignment1::RUNNING && (key == ' '))
		Assignment1::locInstance()->Fire(Assignment1::locInstance()->GetCrosshairLocation().GetX(),Assignment1::locInstance()->GetCrosshairLocation().GetY());

	if (key == '0')
		Assignment1::locInstance()->SetStepsize(1.0 * rate);
	else if (key == '1')
		Assignment1::locInstance()->SetStepsize(2.0 * rate);
	else if (key == '2')
		Assignment1::locInstance()->SetStepsize(3.0 * rate);
	else if (key == '3')
		Assignment1::locInstance()->SetStepsize(4.0 * rate);
	else if (key == '4')
		Assignment1::locInstance()->SetStepsize(5.0 * rate);
	else if (key == '5')
		Assignment1::locInstance()->SetStepsize(6.0 * rate);
	else if (key == '6')
		Assignment1::locInstance()->SetStepsize(7.0 * rate);
	else if (key == '7')
		Assignment1::locInstance()->SetStepsize(8.0 * rate);
	else if (key == '8')
		Assignment1::locInstance()->SetStepsize(9.0 * rate);
	else if (key == '9')
		Assignment1::locInstance()->SetStepsize(10.0 * rate);
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	mySpecial
//	Inputs:		key and mouse position
//	Output:		none
//	Purpose:	Callback that handles special keys
//******************************************************************
void mySpecial(int key ,int x,int y)
{
	if (Assignment1::locInstance()->GetState() == Assignment1::INIT && (key == GLUT_KEY_F2))
		Assignment1::locInstance()->SetState(Assignment1::RUNNING);
}
