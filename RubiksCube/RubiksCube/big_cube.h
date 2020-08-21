#ifndef _BIG_CUBE_H
#define _BIG_CUBE_H

#include "small_cube.h"
#include <cmath>
#define _USE_MATH_DEFINES

class BigCube {
public:
	int cur;
	int rotate_y;
	BigCube() = default;
	BigCube(double size_)
	{
		start(size_);
	}
	void start(double size_) {
		rotate = std::vector<int>(6, 0);
		rotate_y = 0;
		size = size_;
		cur = -1;
		// up
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				cubes[i][2][j].set_color(0, 0);
		// down
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				cubes[i][0][j].set_color(1, 5);
		// front
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				cubes[i][j][2].set_color(2, 3);
		// back
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				cubes[i][j][0].set_color(3, 2);
		// left
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				cubes[0][i][j].set_color(4, 1);
		// right
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				cubes[2][i][j].set_color(5, 4);
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					cubes[i][j][k].size = (size / 3.0) * 0.96;
	}
	void draw() {
		const double K = 0.65;
		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(((1.0 - K) / 2) * size + K * size / 2, ((1.0 - K) / 2) * size + K * size / 2, ((1.0 - K) / 2) * size + K * size / 2);
		glutSolidCube(size * K);
		glPopMatrix();
		stop = std::vector<std::vector<std::vector<bool> > >(3, std::vector<std::vector<bool> >(3, std::vector<bool>(3, true)));
		if (cur != -1) {
			glPushMatrix();
			int k;
			if ((cur == 0) || (cur == 1)) { // 0 - up, 1 - down
				k = cur == 1 ? 0 : 2;
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						stop[i][k][j] = false;
				glTranslated(size / 2, 0, size / 2);
				glRotatef(rotate[cur], 0, 1, 0);
				glTranslated(-size / 2, 0, -size / 2);
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						cubes[i][k][j].draw(size / 3.0 * i, size / 3.0 * k, size / 3.0 * j);
			}
			else if ((cur == 2) || (cur == 3)) { // 2 - front, 3 - back
				k = cur == 2 ? 2 : 0;
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						stop[i][j][k] = false;
				glTranslated(size / 2, size / 2, 0);
				glRotatef(rotate[cur], 0, 0, 1);
				glTranslated(-size / 2, -size / 2, 0);
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						cubes[i][j][k].draw(size / 3.0 * i, size / 3.0 * j, size / 3.0 * k);
			}
			else if ((cur == 4) || (cur == 5)) { // 4 - left, 5 - right
				k = cur == 4 ? 0 : 2;
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						stop[k][i][j] = false;
				glTranslated(0, size / 2, size / 2);
				glRotatef(rotate[cur], 1, 0, 0);
				glTranslated(0, -size / 2, -size / 2);
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						cubes[k][i][j].draw(size / 3.0 * k, size / 3.0 * i, size / 3.0 * j);
			}
			glPopMatrix();
		}
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					if (stop[i][j][k])
						cubes[i][j][k].draw(size / 3.0 * i, size / 3.0 * j, size / 3.0 * k);
	}
	void rotate90(int flag, int num) { // 1 - clock wise, -1 - counter clock wise
		if (flag == -1)
			flag = 3;
		int k;
		while (flag > 0) {
			if ((num == 0) || (num == 1)) { // 0 - up, 1 - down
				k = num == 1 ? 0 : 2;
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						tmp[i][2 - j] = cubes[i][k][j];
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++) {
						tmp[j][i].rotateY();
						cubes[i][k][j] = tmp[j][i];
					}
			}
			if ((num == 2) || (num == 3)) { // 2 - front, 3 - back
				k = num == 2 ? 2 : 0;
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						tmp[i][j] = cubes[i][j][k];
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++) {
						tmp[2 - j][i].rotateZ();
						cubes[i][j][k] = tmp[2 - j][i];
					}
			}
			if ((num == 4) || (num == 5)) { // 4 - left, 5 - right
				k = num == 4 ? 0 : 2;
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						tmp[2 - j][i] = cubes[k][i][j];
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++) {
						tmp[2 - i][2 - j].rotateX();
						cubes[k][i][j] = tmp[2 - i][2 - j];
					}
			}
			flag--;
		}
	}
	void Rotate(int num, int angle) {
		if ((cur == -1) || (cur == num)) {
			rotate[num] += angle;
			if ((int)std::abs(rotate[num]) % 90 != 0)
				cur = num;
			else {
				if (rotate[num] < 0)
					rotate90(1, num);
				else
					rotate90(-1, num);
				rotate[num] = 0;
				cur = -1;
			}
		}
	}
	void rotateY(int angle) {
		rotate_y += angle;
		if (std::abs(rotate_y) >= 90) {
			SmallCube tmp1[3];
			rotate_y = 0;
			for (int i = 0; i < 3; i++) {
				tmp1[2 - i] = cubes[2][i][1];
				cubes[2][i][1] = cubes[1][i][0];
				cubes[1][i][0] = cubes[0][i][1];
				cubes[0][i][1] = cubes[1][i][2];
				cubes[1][i][2] = tmp1[2 - i];
			}
			for (int i = 0; i < 3; i++) {
				tmp1[2 - i] = cubes[2][i][0];
				cubes[2][i][0] = cubes[0][i][0];
				cubes[0][i][0] = cubes[0][i][2];
				cubes[0][i][2] = cubes[2][i][2];
				cubes[2][i][2] = tmp1[2 - i];
			}
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
						cubes[i][j][k].rotateY();
		}
	}
private:
	SmallCube cubes[3][3][3];
	double size;
	std::vector<int> rotate;
	std::vector<std::vector<std::vector<bool> > > stop;
	SmallCube tmp[3][3];
};

#endif
