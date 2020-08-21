#ifndef _SMALL_CUBE_H
#define _SMALL_CUBE_H

#include "glut.h"
#include <cstring>
#include <vector>

class SmallCube {
public:
	double size;
	SmallCube() {
		size = 0;
		color.resize(6, -1);
	}
	void set_color(int i, int col) {
		color[i] = col;
	}
	void make_color(int ind) {
		switch (color[ind]) {
		case -1:
			glColor3f(0, 0, 0);
			break;
		case 0:
			glColor3f(1, 1, 0);
			break;
		case 1:
			glColor3f(1, 0, 0);
			break;
		case 2:
			glColor3f(0, 0, 1);
			break;
		case 3:
			glColor3f(0, 1, 0);
			break;
		case 4:
			glColor3f(1, 0.5, 0);
			break;
		case 5:
			glColor3f(1, 1, 1);
		}
	}
	void draw() {
		glPushMatrix();
		glBegin(GL_QUADS);

		// up
		make_color(0);
		glVertex3f(size, size, size);
		glVertex3f(0, size, size);
		glVertex3f(0, size, 0);
		glVertex3f(size, size, 0);

		// down
		make_color(1);
		glVertex3f(size, 0, size);
		glVertex3f(0, 0, size);
		glVertex3f(0, 0, 0);
		glVertex3f(size, 0, 0);

		// front
		make_color(2);
		glVertex3f(size, size, size);
		glVertex3f(0, size, size);
		glVertex3f(0, 0, size);
		glVertex3f(size, 0, size);

		// back
		make_color(3);
		glVertex3f(size, size, 0);
		glVertex3f(0, size, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(size, 0, 0);

		// left
		make_color(4);
		glVertex3f(0, size, size);
		glVertex3f(0, size, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, size);

		// right
		make_color(5);
		glVertex3f(size, size, 0);
		glVertex3f(size, size, size);
		glVertex3f(size, 0, size);
		glVertex3f(size, 0, 0);

		glEnd();
		glPopMatrix();
	}
	void draw(double x, double y, double z) {
		glPushMatrix();
		glTranslated(x, y, z);
		draw();
		glPopMatrix();
	}
	void rotateY()
	{
		int tmp = color[5];
		color[5] = color[3];
		color[3] = color[4];
		color[4] = color[2];
		color[2] = tmp;
	}

	void rotateX()
	{
		int tmp = color[2];
		color[2] = color[1];
		color[1] = color[3];
		color[3] = color[0];
		color[0] = tmp;
	}

	void rotateZ()
	{
		int tmp = color[0];
		color[0] = color[4];
		color[4] = color[1];
		color[1] = color[5];
		color[5] = tmp;
	}
private:
	std::vector<int> color;
};

#endif