
#pragma comment(lib, "glew32.lib")


#include "assignment1.h"

void init();
void myDisplay();
void myIdle();
void myReshape(int width, int height);
void myMouseEvent(int,int,int,int);
void myMouseMotion(int, int);
void myMousePassiveMotion(int,int);
void myMouseEntryEvent(int);
void myKeyboard(unsigned char,int,int);
void mySpecial(int,int,int);


//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	main
//	Inputs:		none
//	Output:		none
//	Purpose:	main function
//******************************************************************
int main(int argc, char** argv)
{
	//init
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Assignment1 Aleksander Shtuk");
	glewInit();
	init();

	//display
	glutDisplayFunc(myDisplay);

	//idle
	glutIdleFunc(myIdle);

	//input
	glutMouseFunc(myMouseEvent);
	glutMotionFunc(myMouseMotion);
	glutPassiveMotionFunc(myMousePassiveMotion);
	glutEntryFunc(myMouseEntryEvent);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecial);

	//reshape
	glutReshapeFunc(myReshape);	

	glutMainLoop();

	return 0;
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	Init
//	Inputs:		none
//	Output:		none
//	Purpose:	all objects must be initilialized here
//******************************************************************
void init()
{
	glClearColor(0.0,0.0,0.0,0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,500.0,0.0,500.0,-1.0,1.0);

	Assignment1::Create(k_iNumberOfTargets,500,500);

}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	myDisplay
//	Inputs:		none
//	Output:		none
//	Purpose:	Callback that handles display
//******************************************************************
void myDisplay()
{
	glClear (GL_COLOR_BUFFER_BIT);

	if (Assignment1::locInstance()->GetState() == Assignment1::INIT)
	{
		Assignment1::instance()->DrawMessage("START GAME  : F2",(GLfloat)Assignment1::instance()->GetWidth()/2 -100, (GLfloat)Assignment1::instance()->GetHeight()/2 - 15);	
		Assignment1::instance()->DrawMessage("PAUSE GAME  : M/m",(GLfloat)Assignment1::instance()->GetWidth()/2 - 100, (GLfloat)Assignment1::instance()->GetHeight()/2);
		Assignment1::instance()->DrawMessage("FIRE        : L MOUSE or SPACE",(GLfloat)Assignment1::instance()->GetWidth()/2 - 100, (GLfloat)Assignment1::instance()->GetHeight()/2 + 15);	
		Assignment1::instance()->DrawMessage("SELECT LEVEL: 0-9",(GLfloat)Assignment1::instance()->GetWidth()/2 - 100, (GLfloat)Assignment1::instance()->GetHeight()/2 + 30);	
	}
	else if (Assignment1::locInstance()->GetState() == Assignment1::END)
		Assignment1::instance()->DrawMessage("YOU WON!");	
	else
		Assignment1::locInstance()->DrawObjects();

	glutSwapBuffers();
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	myIdle
//	Inputs:		none
//	Output:		none
//	Purpose:	Do targets moving in here
//******************************************************************
void myIdle()
{
	if (Assignment1::locInstance()->GetState() == Assignment1::RUNNING)
		Assignment1::locInstance()->MoveTargets();

	glutPostRedisplay();
}
//****************************************************************
//	Date:		02/19/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		none
//	Function:	myReshape
//	Inputs:		none
//	Output:		none
//	Purpose:	Callback that handles window reshaping			
//******************************************************************

void myReshape(int width, int height)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,width,0.0,height,-1.0,0.0);
	glViewport(0,0,width,height);
	glMatrixMode(GL_MODELVIEW);

	Assignment1::locInstance()->UpdateSize(width,height);

	glutPostRedisplay();
}