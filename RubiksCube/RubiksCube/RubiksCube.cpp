#include <iostream>
#include <fstream>
#include "rubiks_cube.h"
#include "big_cube.h"
using namespace std;

BigCube cube;
RubiksCube rubiks_cube;
const double cube_size = 13;
double translateZ = -35.0;
const int TIMER = 10;
int xRot = 25, yRot = -35;
int rotatingY = 0;
int direction = 1;
bool doing = false;
ofstream fout;
bool writing = false;
int x = 5;
std::string str[5];
int index = 0;
bool left_button = false;

void display();

void drawText(const char *text, int length, int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 400, 0, 400, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);

}

void make_state(int num) {
	if ((num == 0) && (direction == 1))
		fout << "U' ";
	else if ((num == 0) && (direction == -1))
		fout << "U ";
	else if ((num == 1) && (direction == 1))
		fout << "D ";
	else if ((num == 1) && (direction == -1))
		fout << "D' ";
	else if ((num == 2) && (direction == 1))
		fout << "F' ";
	else if ((num == 2) && (direction == -1))
		fout << "F ";
	else if ((num == 3) && (direction == 1))
		fout << "B ";
	else if ((num == 3) && (direction == -1))
		fout << "B' ";
	else if ((num == 4) && (direction == 1))
		fout << "L ";
	else if ((num == 4) && (direction == -1))
		fout << "L' ";
	else if ((num == 5) && (direction == 1))
		fout << "R' ";
	else if ((num == 5) && (direction == -1))
		fout << "R ";
}

void rotating() {
	if (cube.cur == -1) {
		std::string front = rubiks_cube.rotations.front();
		if (front == "R") {
			direction = -1;
			cube.cur = 5;
		}
		else if (front == "R'") {
			direction = 1;
			cube.cur = 5;
		}
		else if (front == "L") {
			direction = 1;
			cube.cur = 4;
		}
		else if (front == "L'") {
			direction = -1;
			cube.cur = 4;
		}
		else if (front == "F") {
			direction = -1;
			cube.cur = 2;
		}
		else if (front == "F'") {
			direction = 1;
			cube.cur = 2;
		}
		else if (front == "B") {
			direction = 1;
			cube.cur = 3;
		}
		else if (front == "B'") {
			direction = -1;
			cube.cur = 3;
		}
		else if (front == "U") {
			direction = -1;
			cube.cur = 0;
		}
		else if (front == "U'") {
			direction = 1;
			cube.cur = 0;
		}
		else if (front == "D") {
			direction = 1;
			cube.cur = 1;
		}
		else if (front == "D'") {
			direction = -1;
			cube.cur = 1;
		}
		else if (front == "y")
			cube.rotateY(-7);
		if (str[index].size() > 160)
			index++;
		str[index] += front + ' ';
		rubiks_cube.rotations.pop();
	}
}

void display()
{
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTranslatef(0, 0, translateZ);
	glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot + cube.rotate_y, 0, 1, 0);
	glTranslatef(cube_size / -2.0, cube_size / -2.0, cube_size / -2.0);
	cube.draw();
	//if(writing) {
		glColor3f(0, 0, 0);
		for (int i = 0; i < 5; i++)
			drawText(str[i].data(), str[i].size(), 5, 70 - 10 * i);
	//}
	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat fAspect = (GLfloat)w / (GLfloat)h;
	gluPerspective(60, fAspect, 1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init()
{
	glClearColor(1.0, 228 / 255.0, 225 / 255.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	cube = BigCube(cube_size);
	fout.open("input.txt");
}

void user_scramble() {
	fout.close();
	ifstream fin("input.txt");
	rubiks_cube.use_queue = false;
	rubiks_cube.scramble(fin);
	rubiks_cube.use_queue = true;
	fin.close();
	fout.open("input.txt");
}

void clear_str() {
	index = 0;
	for (int i = 0; i < 5; i++)
		str[i] = "";
}

void keys(unsigned char key, int, int)
{
	if ((!doing) && (key == 's')) {
		ifstream scramble("scramble.txt");
		rubiks_cube.scramble(scramble);
		scramble.close();
	}
	if ((cube.cur == -1) && (key >= '0' && key < '6') && (!doing)) 
	{
		make_state(key - '0');
		cube.Rotate(key - '0', direction * 9);
		display();
	}
	if ((!doing) && ((key == 113) || (key == 233) || (key == 201) || (key == 81)) && (cube.cur == -1)) {
		clear_str();
		doing = true;
		user_scramble();
		rubiks_cube.generate_state();
		//writing = false;
	}
	if ((key == ' ') && (cube.cur == -1)) {
		doing = true;
		user_scramble();
		rubiks_cube.solve();
		clear_str();
		//writing = false;
	}
	if ((!doing) && (key == '-'))
		direction *= -1;
	if (key == 'e')
	{
		cube.start(cube_size);
		clear_str();
		rubiks_cube.use_queue = false;
		rubiks_cube.solve();
		rubiks_cube.use_queue = true;
		glutPostRedisplay();
	}
}

int x_last, y_last;
void mouse(int key, int state, int x, int y)
{
	if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		x_last = x;
		y_last = y;
		left_button = true;
	}
	else if (key == GLUT_LEFT_BUTTON)
		left_button = false;
}

void mouseMove(int x, int y) {
	if (left_button) {
		xRot += (y - y_last) / 2;
		yRot += (x - x_last) / 2;
		x_last = x;
		y_last = y;
	}
}

void timer(int)
{
	glutTimerFunc(TIMER, timer, 0);
	if ((cube.cur == -1) && (!rubiks_cube.rotations.empty()) && (cube.rotate_y == 0))
		rotating();
	else if (rubiks_cube.rotations.empty()) {
		doing = false;
		//writing = true;
	}
	if ((cube.cur != -1) && (cube.rotate_y == 0))
		cube.Rotate(cube.cur, direction * 9);
	if (cube.rotate_y != 0)
		cube.rotateY(-7);
	display();
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 700);
	glutInitWindowPosition(350, 100);
	glutCreateWindow("Cube");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keys);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);
	glutTimerFunc(TIMER, timer, 0);
	glutMainLoop();
	fout.close();
	return 0;

}