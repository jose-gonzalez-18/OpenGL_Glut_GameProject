// Developer: Jose Gonzalez
//Start date: 5/17/2021
//SharkEat.cpp

//Game name - Shark Eat
//Description: Eat fish, grow, fight larger animals.

#include <iostream>
#include <string>
#include <ctime>
#include <GL/glut.h>
using namespace std;

// global GAME SETTINGS
const int SCREEN_HEIGHT = 800;	
const int SCREEN_WIDTH = 800;

// screen max and min - left, right
const int LEFT_SIDE = 200;
const int RIGHT_SIDE = 400;

// screen max and min - up,down
const int TOP_SIDE = 350;
const int	BOTTOM_SIDE = 380;

// health
int sharkHealth = 10;
// moster health
int monsterHealth = 8;

// shark spawn position
float sharkPosX = SCREEN_HEIGHT / 4 , sharkPosY = SCREEN_WIDTH / 4;   
// fish spawn positions
float fishPosX = RIGHT_SIDE, fishPosY = LEFT_SIDE;
// food spawn position
float foodPosX = BOTTOM_SIDE / 2, foodPosY = TOP_SIDE / 1.2;
// score static position
float scorePosX = 0, scorePosY = TOP_SIDE + 25;
// move speed: Move()
float move_unit = 8.0f;										

// load textures : todo

// load food & settings
void loadFood()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
			 // x, y
	glBegin(GL_QUADS);
	glVertex2f(12.5 + foodPosX, 6.25 + foodPosY); 
	glVertex2f(18.75 + foodPosX, 6.25 + foodPosY);
	glVertex2f(18.75 + foodPosX, 12.5 + foodPosY);
	glVertex2f(12.5 + foodPosX, 12.5 + foodPosY);
	glEnd();

	glFlush();
	glutPostRedisplay();
}

// load food & settings
void loadScore()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.5, 0.0);
	// x, y
	glBegin(GL_QUADS);
	glVertex2f(12.5 + scorePosX, 6.25 + scorePosY); // top left
	glVertex2f(100 + scorePosX, 6.25 + scorePosY);// top right
	glVertex2f(100 + scorePosX, 20 + scorePosY);// bottom right
	glVertex2f(12.5 + scorePosX, 20 + scorePosY); // bottom left
	glEnd();

	glFlush();
	glutPostRedisplay();
}

// load fish & settings
void loadFish()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 1.0);
			// x, y
	glBegin(GL_QUADS);
	glVertex2f(12.5 + fishPosX, 6.25 + fishPosY);
	glVertex2f(18.75 + fishPosX, 6.25 + fishPosY);
	glVertex2f(18.75 + fishPosX, 12.5 + fishPosY);
	glVertex2f(12.5 + fishPosX, 12.5 + fishPosY);
	glEnd();

	glFlush();
	glutPostRedisplay();
}

// load shark & settings
void loadShark() 
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
			 // x, y
	glBegin(GL_QUADS);
	glVertex2f(50 + sharkPosX, 25 + sharkPosY);
	glVertex2f(75 + sharkPosX, 25 + sharkPosY);
	glVertex2f(75 + sharkPosX, 50 + sharkPosY);
	glVertex2f(50 + sharkPosX, 50 + sharkPosY);
	glEnd();

	glFlush();
	glutPostRedisplay();
}

// load plants & settings
void loadPlant()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 1.0, 0.0);

	         // x, y
	glBegin(GL_QUADS);
	glVertex2f(15, 50);   // top left
	glVertex2f(15, 50);   // top right
	glVertex2f(20, 5);    // bottom right
	glVertex2f(10, 5);    // bottom lef t
	glEnd();

	         // x, y
	glBegin(GL_QUADS);
	glVertex2f(75, 70);  // top left
	glVertex2f(75, 70);  // top right
	glVertex2f(80, 5);   // bottom right
	glVertex2f(70, 5);   // bottom left
	glEnd();

	         // x, y
	glBegin(GL_QUADS);
	glVertex2f(175, 50);  // top left
	glVertex2f(175, 50);  // top right
	glVertex2f(180, 5);   // bottom right
	glVertex2f(170, 5);   // bottom left
	glEnd();

	// x, y
	glBegin(GL_QUADS);
	glVertex2f(300, 50);  // top left
	glVertex2f(300, 50);  // top right
	glVertex2f(305, 5);   // bottom right
	glVertex2f(295, 5);   // bottom left
	glEnd();

	glFlush();
	glutPostRedisplay();
}

// load water & settings
void loadWater()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
			// x, y
	glBegin(GL_QUADS);
	glVertex2f(0, 300);    // top left
	glVertex2f(400, 300);  // top right
	glVertex2f(400, 0);    // bottom right
	glVertex2f(0, 0);      // bottom left
	glEnd();

	glFlush();
	glutPostRedisplay();
}

// load water & settings
void loadSand()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
			 // x, y
	glBegin(GL_QUADS);
	glVertex2f(0, 20);    // top left
	glVertex2f(400, 20);  // top right
	glVertex2f(400, 0);    // bottom right
	glVertex2f(0, 0);      // bottom left
	glEnd();

	glFlush();
	glutPostRedisplay();
}

// load several objects at once
void loadGameObjects() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	loadWater(); // background
	loadSand();
	loadShark();
	loadPlant();
	loadFish();
	loadFood();
	loadScore();
	sharkPosY = sharkPosY - 0.02; // gravity for shark, speed. 
	//sharkPosX = sharkPosX - 0.02; // gravity for shark, speed. 

	// fish movement left -> right
	if (fishPosX < 350)
		fishPosX = fishPosX + 0.05;
	else if (fishPosX > 0)
		fishPosX = 0;

	// food moevement top -> bottom 
	if (foodPosY > 0)
		foodPosY = foodPosY - 0.05;
	else if (foodPosY < 0)
		foodPosY = 290;

	// eat
	if (foodPosX == sharkPosX && foodPosY == sharkPosY) 
	{
		foodPosY = 290;
	}

	glutSwapBuffers();
}

static bool paused = false;
// move objects / exapmle: shark
void keyboardInput(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_RIGHT:
		//cout << "right" << endl;
		sharkPosX = sharkPosX + move_unit;
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
		//cout << "left" << endl;
		sharkPosX = sharkPosX - move_unit;
		glutPostRedisplay();
		break;

	case GLUT_KEY_UP:
		//cout << "up" << endl;
		sharkPosY = sharkPosY + move_unit;
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		//cout << "down" << endl;
		sharkPosY = sharkPosY - move_unit;
		glutPostRedisplay();
		break;
	}
}

// load init settings
void initialize()
{
	glClearColor(0.0, 1.0, 1.0, 1.0);
	gluOrtho2D(0.0, 400, 0.0, 400);
}

// non resizable
void sizableFalse(int width, int height) {
	glutReshapeWindow(SCREEN_HEIGHT, SCREEN_WIDTH);
}
// todo: implement sizable
// main
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(600, 50);
	glutCreateWindow("Shark Eat");

	// display call back function
	glutDisplayFunc(loadGameObjects);
	// init settings, call move func, loop main.
	initialize();
	glutReshapeFunc(sizableFalse);
	glutSpecialFunc(keyboardInput);
	glutMainLoop();

	return 0;
}
