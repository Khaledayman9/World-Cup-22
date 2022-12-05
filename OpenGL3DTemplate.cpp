#include<iostream>
#include <Windows.h>
#include <glut.h>
#include <Mmsystem.h>
#include <playsoundapi.h>
#include <dsound.h>
#include <string>
#include <stdio.h>

#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)


int wWidth = 640;
int wHeight = 480;
int cameraZoom = 0;

GLfloat moveX = 0;
GLfloat moveZ = 0;
GLfloat rotPlayer = 0;
GLfloat rotX = 0;
GLfloat rotY = 0;
GLfloat rotZ = 0;

GLfloat d = 0.05;
GLfloat yy = 0.01;

GLfloat ballZ = 0;

GLfloat bXmin = -2.35;
GLfloat bXmax = 0.49;
GLfloat bZmin = -2.78;
GLfloat bZmax = 1.09;

GLboolean endOfGame = false;
GLboolean timeOver = false;
GLboolean defeat = false;
GLboolean victory = false;
int footShoot = 0;
int timer = 0;

class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

Vector3f Eye(2.5, 2.5, 2.5);
Vector3f Center(0.0, 0.0, 0.0);
Vector3f Up(0, 1, 0);

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 4.5f, float eyeY = 4.5f, float eyeZ = 4.5f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

Camera camera;

void drawGround(double thickness) {
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslated(-0.5, 0.5 * thickness, -0.5);
	glScaled(3, thickness * 0.05, 4);
	glutSolidCube(1);
	glPopMatrix();
}


void drawSurrounding() {
	glPushMatrix();
	glColor3f(0.2, 0.3, 0.7);
	glTranslated(-0.5, 0.08, -0.5);
	glScaled(12, 0.01, 12);
	glutSolidCube(1);
	glPopMatrix();
}


void drawSingleBin(GLfloat xTrans, GLfloat yTrans, GLfloat zTrans, GLfloat xwidth, GLfloat height, GLfloat zwidth) {
	glPushMatrix();
	glColor3f(0.5, 0.5f, 0.5f);
	glTranslated(xTrans, yTrans, zTrans);
	glScaled(xwidth, height, zwidth);
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawString(GLfloat xTrans, GLfloat yTrans, GLfloat zTrans, GLfloat xwidth, GLfloat height, GLfloat zwidth) {
	glPushMatrix();
	glColor3f(1, 1, 1);
	//0.15
	glTranslated(xTrans, yTrans, zTrans);
	//0.02, 0.3,0.02
	glScaled(xwidth, height, zwidth);
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawFirstGoalNet() {
	glPushMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-0.2, 0.48, -2.2);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	//glRotated(30, 0, 0, 1);
	GLUquadricObj* quadraticObj1 = gluNewQuadric();
	gluCylinder(quadraticObj1, 0.01, 0.005, 0.11, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-0.2, 0.48, -2);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	//glRotated(30, 0, 0, 1);
	GLUquadricObj* quadraticObj2 = gluNewQuadric();
	gluCylinder(quadraticObj2, 0.01, 0.005, 0.11, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-0.6, 0.48, -2.2);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	//glRotated(30, 0, 0, 1);
	GLUquadricObj* quadraticObj3 = gluNewQuadric();
	gluCylinder(quadraticObj3, 0.01, 0.005, 0.11, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-0.6, 0.48, -2);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	//glRotated(30, 0, 0, 1);
	GLUquadricObj* quadraticObj4 = gluNewQuadric();
	gluCylinder(quadraticObj4, 0.01, 0.005, 0.11, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-0.2, 0.48, -2.2);
	glutSolidSphere(0.008, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-0.2, 0.48, -2);
	glutSolidSphere(0.008, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-0.6, 0.48, -2.2);
	glutSolidSphere(0.008, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-0.6, 0.48, -2);
	glutSolidSphere(0.008, 20, 20);
	glPopMatrix();

	//back bins
	drawSingleBin(-0.2, 0.27, -2.2, 0.02, 0.35, 0.02);
	drawSingleBin(-0.6, 0.27, -2.2, 0.02, 0.35, 0.02);

	drawString(-0.25, 0.27, -2.2, 0.005, 0.35, 0.005);
	drawString(-0.3, 0.27, -2.2, 0.005, 0.35, 0.005);
	drawString(-0.35, 0.27, -2.2, 0.005, 0.35, 0.005);
	drawString(-0.4, 0.27, -2.2, 0.005, 0.35, 0.005);
	drawString(-0.45, 0.27, -2.2, 0.005, 0.35, 0.005);
	drawString(-0.5, 0.27, -2.2, 0.005, 0.35, 0.005);
	drawString(-0.55, 0.27, -2.2, 0.005, 0.35, 0.005);

	drawString(-0.4, 0.20, -2.2, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.25, -2.2, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.30, -2.2, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.35, -2.2, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.40, -2.2, 0.42, 0.005, 0.005);

	//front bins
	drawSingleBin(-0.2, 0.27, -2, 0.02, 0.35, 0.02);
	drawSingleBin(-0.6, 0.27, -2, 0.02, 0.35, 0.02);

	//up ones
	drawSingleBin(-0.4, 0.45, -2, 0.42, 0.05, 0.02);
	drawSingleBin(-0.4, 0.45, -2.2, 0.42, 0.05, 0.02);

	drawString(-0.4, 0.45, -2.02, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.45, -2.04, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.45, -2.06, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.45, -2.08, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.45, -2.1, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.45, -2.12, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.45, -2.14, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.45, -2.16, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.45, -2.18, 0.42, 0.005, 0.005);


	drawString(-0.25, 0.45, -2.1, 0.005, 0.005, 0.22);
	drawString(-0.3, 0.45, -2.1, 0.005, 0.005, 0.22);
	drawString(-0.35, 0.45, -2.1, 0.005, 0.005, 0.22);
	drawString(-0.4, 0.45, -2.1, 0.005, 0.005, 0.22);
	drawString(-0.45, 0.45, -2.1, 0.005, 0.005, 0.22);
	drawString(-0.5, 0.45, -2.1, 0.005, 0.005, 0.22);
	drawString(-0.55, 0.45, -2.1, 0.005, 0.005, 0.22);

	//between ones
	drawSingleBin(-0.2, 0.45, -2.1, 0.02, 0.05, 0.22);
	drawSingleBin(-0.6, 0.45, -2.1, 0.02, 0.05, 0.22);

	drawString(-0.2, 0.20, -2.1, 0.005, 0.005, 0.22);
	drawString(-0.2, 0.25, -2.1, 0.005, 0.005, 0.22);
	drawString(-0.2, 0.30, -2.1, 0.005, 0.005, 0.22);
	drawString(-0.2, 0.35, -2.1, 0.005, 0.005, 0.22);
	drawString(-0.2, 0.40, -2.1, 0.005, 0.005, 0.22);

	drawString(-0.2, 0.27, -2.02, 0.005, 0.35, 0.005);
	drawString(-0.2, 0.27, -2.04, 0.005, 0.35, 0.005);
	drawString(-0.2, 0.27, -2.06, 0.005, 0.35, 0.005);
	drawString(-0.2, 0.27, -2.08, 0.005, 0.35, 0.005);
	drawString(-0.2, 0.27, -2.1, 0.005, 0.35, 0.005);
	drawString(-0.2, 0.27, -2.12, 0.005, 0.35, 0.005);
	drawString(-0.2, 0.27, -2.14, 0.005, 0.35, 0.005);
	drawString(-0.2, 0.27, -2.16, 0.005, 0.35, 0.005);
	drawString(-0.2, 0.27, -2.18, 0.005, 0.35, 0.005);

	drawString(-0.6, 0.20, -2.1, 0.005, 0.005, 0.22);
	drawString(-0.6, 0.25, -2.1, 0.005, 0.005, 0.22);
	drawString(-0.6, 0.30, -2.1, 0.005, 0.005, 0.22);
	drawString(-0.6, 0.35, -2.1, 0.005, 0.005, 0.22);
	drawString(-0.6, 0.40, -2.1, 0.005, 0.005, 0.22);

	drawString(-0.6, 0.27, -2.02, 0.005, 0.35, 0.005);
	drawString(-0.6, 0.27, -2.04, 0.005, 0.35, 0.005);
	drawString(-0.6, 0.27, -2.06, 0.005, 0.35, 0.005);
	drawString(-0.6, 0.27, -2.08, 0.005, 0.35, 0.005);
	drawString(-0.6, 0.27, -2.1, 0.005, 0.35, 0.005);
	drawString(-0.6, 0.27, -2.12, 0.005, 0.35, 0.005);
	drawString(-0.6, 0.27, -2.14, 0.005, 0.35, 0.005);
	drawString(-0.6, 0.27, -2.16, 0.005, 0.35, 0.005);
	drawString(-0.6, 0.27, -2.18, 0.005, 0.35, 0.005);

	//below ones
	drawSingleBin(-0.2, 0.13, -2.1, 0.02, 0.05, 0.22);
	drawSingleBin(-0.6, 0.13, -2.1, 0.02, 0.05, 0.22);
	drawSingleBin(-0.4, 0.13, -2.2, 0.42, 0.05, 0.02);
	glPopMatrix();
}

void drawSecondGoalNet() {
	glPushMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-0.2, 0.48, 1.2);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	//glRotated(30, 0, 0, 1);
	GLUquadricObj* quadraticObj1 = gluNewQuadric();
	gluCylinder(quadraticObj1, 0.01, 0.005, 0.11, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-0.2, 0.48, 1);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	//glRotated(30, 0, 0, 1);
	GLUquadricObj* quadraticObj2 = gluNewQuadric();
	gluCylinder(quadraticObj2, 0.01, 0.005, 0.11, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-0.6, 0.48, 1);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	//glRotated(30, 0, 0, 1);
	GLUquadricObj* quadraticObj3 = gluNewQuadric();
	gluCylinder(quadraticObj3, 0.01, 0.005, 0.11, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-0.6, 0.48, 1.2);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	//glRotated(30, 0, 0, 1);
	GLUquadricObj* quadraticObj4 = gluNewQuadric();
	gluCylinder(quadraticObj4, 0.01, 0.005, 0.11, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-0.2, 0.48, 1.2);
	glutSolidSphere(0.008, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-0.2, 0.48, 1);
	glutSolidSphere(0.008, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-0.6, 0.48, 1);
	glutSolidSphere(0.008, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-0.6, 0.48, 1.2);
	glutSolidSphere(0.008, 20, 20);
	glPopMatrix();

	//back bins

	drawSingleBin(-0.2, 0.27, 1.2, 0.02, 0.35, 0.02);
	drawSingleBin(-0.6, 0.27, 1.2, 0.02, 0.35, 0.02);

	drawString(-0.25, 0.27, 1.2, 0.005, 0.35, 0.005);
	drawString(-0.3, 0.27, 1.2, 0.005, 0.35, 0.005);
	drawString(-0.35, 0.27, 1.2, 0.005, 0.35, 0.005);
	drawString(-0.4, 0.27, 1.2, 0.005, 0.35, 0.005);
	drawString(-0.45, 0.27, 1.2, 0.005, 0.35, 0.005);
	drawString(-0.5, 0.27, 1.2, 0.005, 0.35, 0.005);
	drawString(-0.55, 0.27, 1.2, 0.005, 0.35, 0.005);


	drawString(-0.4, 0.20, 1.2, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.25, 1.2, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.30, 1.2, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.35, 1.2, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.40, 1.2, 0.42, 0.005, 0.005);


	//drawString(-0.3, 0.27, 1.2, 0.005, 0.35, 0.005);

	//front bins
	drawSingleBin(-0.2, 0.27, 1, 0.02, 0.35, 0.02);
	drawSingleBin(-0.6, 0.27, 1, 0.02, 0.35, 0.02);

	//up ones
	drawSingleBin(-0.4, 0.45, 1, 0.42, 0.05, 0.02);
	drawSingleBin(-0.4, 0.45, 1.2, 0.42, 0.05, 0.02);

	drawString(-0.4, 0.45, 1.02, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.45, 1.04, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.45, 1.06, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.45, 1.08, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.45, 1.1, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.45, 1.12, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.45, 1.14, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.45, 1.16, 0.42, 0.005, 0.005);
	drawString(-0.4, 0.45, 1.18, 0.42, 0.005, 0.005);


	drawString(-0.25, 0.45, 1.1, 0.005, 0.005, 0.22);
	drawString(-0.3, 0.45, 1.1, 0.005, 0.005, 0.22);
	drawString(-0.35, 0.45, 1.1, 0.005, 0.005, 0.22);
	drawString(-0.4, 0.45, 1.1, 0.005, 0.005, 0.22);
	drawString(-0.45, 0.45, 1.1, 0.005, 0.005, 0.22);
	drawString(-0.5, 0.45, 1.1, 0.005, 0.005, 0.22);
	drawString(-0.55, 0.45, 1.1, 0.005, 0.005, 0.22);


	//between ones
	drawSingleBin(-0.2, 0.45, 1.1, 0.02, 0.05, 0.22);
	drawSingleBin(-0.6, 0.45, 1.1, 0.02, 0.05, 0.22);

	drawString(-0.2, 0.20, 1.1, 0.005, 0.005, 0.22);
	drawString(-0.2, 0.25, 1.1, 0.005, 0.005, 0.22);
	drawString(-0.2, 0.30, 1.1, 0.005, 0.005, 0.22);
	drawString(-0.2, 0.35, 1.1, 0.005, 0.005, 0.22);
	drawString(-0.2, 0.40, 1.1, 0.005, 0.005, 0.22);

	drawString(-0.2, 0.27, 1.02, 0.005, 0.35, 0.005);
	drawString(-0.2, 0.27, 1.04, 0.005, 0.35, 0.005);
	drawString(-0.2, 0.27, 1.06, 0.005, 0.35, 0.005);
	drawString(-0.2, 0.27, 1.08, 0.005, 0.35, 0.005);
	drawString(-0.2, 0.27, 1.1, 0.005, 0.35, 0.005);
	drawString(-0.2, 0.27, 1.12, 0.005, 0.35, 0.005);
	drawString(-0.2, 0.27, 1.14, 0.005, 0.35, 0.005);
	drawString(-0.2, 0.27, 1.16, 0.005, 0.35, 0.005);
	drawString(-0.2, 0.27, 1.18, 0.005, 0.35, 0.005);


	drawString(-0.6, 0.20, 1.1, 0.005, 0.005, 0.22);
	drawString(-0.6, 0.25, 1.1, 0.005, 0.005, 0.22);
	drawString(-0.6, 0.30, 1.1, 0.005, 0.005, 0.22);
	drawString(-0.6, 0.35, 1.1, 0.005, 0.005, 0.22);
	drawString(-0.6, 0.40, 1.1, 0.005, 0.005, 0.22);

	drawString(-0.6, 0.27, 1.02, 0.005, 0.35, 0.005);
	drawString(-0.6, 0.27, 1.04, 0.005, 0.35, 0.005);
	drawString(-0.6, 0.27, 1.06, 0.005, 0.35, 0.005);
	drawString(-0.6, 0.27, 1.08, 0.005, 0.35, 0.005);
	drawString(-0.6, 0.27, 1.1, 0.005, 0.35, 0.005);
	drawString(-0.6, 0.27, 1.12, 0.005, 0.35, 0.005);
	drawString(-0.6, 0.27, 1.14, 0.005, 0.35, 0.005);
	drawString(-0.6, 0.27, 1.16, 0.005, 0.35, 0.005);
	drawString(-0.6, 0.27, 1.18, 0.005, 0.35, 0.005);

	//below ones
	drawSingleBin(-0.2, 0.13, 1.1, 0.02, 0.05, 0.22);
	drawSingleBin(-0.6, 0.13, 1.1, 0.02, 0.05, 0.22);
	drawSingleBin(-0.4, 0.13, 1.2, 0.42, 0.05, 0.02);
	glPopMatrix();
}



void drawPlayer() {

	glPushMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.7, 0.6);
	glTranslated(0.45, 0.59, 0.35);
	glutSolidSphere(0.05, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(0.495, 0.6, 0.335);
	glutSolidSphere(0.0065, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(0.495, 0.6, 0.365);
	glutSolidSphere(0.0065, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.5, 0.6, 0.365);
	glutSolidSphere(0.003, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.5, 0.6, 0.335);
	glutSolidSphere(0.003, 20, 20);
	glPopMatrix();

	//here
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.46, 0.62, 0.335);
	glutSolidTorus(0.011, 0.02, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.46, 0.62, 0.340);
	glutSolidTorus(0.011, 0.02, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.46, 0.62, 0.345);
	glutSolidTorus(0.011, 0.02, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.46, 0.62, 0.350);
	glutSolidTorus(0.011, 0.02, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.46, 0.62, 0.355);
	glutSolidTorus(0.011, 0.02, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.46, 0.62, 0.360);
	glutSolidTorus(0.011, 0.02, 20, 20);
	glPopMatrix();
	glPushMatrix();

	glColor3f(0, 0, 0);
	glTranslated(0.46, 0.62, 0.365);
	glutSolidTorus(0.011, 0.02, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0.6, 0.3);
	glTranslated(0.494, 0.575, 0.350);
	glScaled(0.01, 0.008, 0.008);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.7, 0.6);
	glTranslated(0.45, 0.62, 0.35);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	//glRotated(30, 0, 0, 1);
	GLUquadricObj* quadraticObj = gluNewQuadric();
	gluCylinder(quadraticObj, 0.02, 0.01, 0.1, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0, 0.7);
	glTranslated(0.45, 0.42, 0.348);
	glScaled(0.06, 0.2, 0.115);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0, 0.7);
	glTranslated(0.45, 0.45, 0.43);
	glScaled(0.06, 0.09, 0.05);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0, 0.7);
	glTranslated(0.45, 0.45, 0.27);
	glScaled(0.06, 0.09, 0.05);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.7, 0.6);
	glTranslated(0.45, 0.62, 0.35);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	//glRotated(30, 0, 0, 1);
	GLUquadricObj* quadraticObj1 = gluNewQuadric();
	gluCylinder(quadraticObj, 0.03, 0.02, 0.2, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.7, 0.6);
	glTranslated(0.45, 0.42, 0.43);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	//glRotated(30, 0, 0, 1);
	GLUquadricObj* quadraticObj2 = gluNewQuadric();
	gluCylinder(quadraticObj2, 0.025, 0.015, 0.1, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.7, 0.6);
	glTranslated(0.45, 0.42, 0.27);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	//glRotated(30, 0, 0, 1);
	GLUquadricObj* quadraticObj3 = gluNewQuadric();
	gluCylinder(quadraticObj3, 0.025, 0.015, 0.1, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(0.45, 0.35, 0.372);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	//glRotated(30, 0, 0, 1);
	GLUquadricObj* quadraticObj4 = gluNewQuadric();
	gluCylinder(quadraticObj4, 0.028, 0.028, 0.1, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(0.45, 0.35, 0.32);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	//glRotated(30, 0, 0, 1);
	GLUquadricObj* quadraticObj5 = gluNewQuadric();
	gluCylinder(quadraticObj5, 0.028, 0.028, 0.1, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.7, 0.6);
	glTranslated(0.45, 0.35, 0.372);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	//glRotated(30, 0, 0, 1);
	GLUquadricObj* quadraticObj6 = gluNewQuadric();
	gluCylinder(quadraticObj6, 0.023, 0.014, 0.2, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.7, 0.6);
	glTranslated(0.45, 0.35, 0.32);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	//glRotated(30, 0, 0, 1);
	GLUquadricObj* quadraticObj7 = gluNewQuadric();
	gluCylinder(quadraticObj7, 0.023, 0.014, 0.2, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.462, 0.125, 0.32);
	glScaled(0.05, 0.051, 0.03);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.462, 0.125, 0.372);
	glScaled(0.05, 0.051, 0.03);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
}


void drawFootball(GLfloat x, GLfloat y, GLfloat z, GLfloat r) {
	glPushMatrix();
	glColor3f(0.7, 1, 1);
	glTranslated(x, y, z);
	glutSolidSphere(r, 20, 20);
	glPopMatrix();
}

void drawGermanFlag() {

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-1.9, 0.53, 0);
	glScaled(0.005, 0.85, 0.005);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(-1.9, 0.9, -0.15);
	glScaled(0.005, 0.1, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(-1.9, 0.8, -0.15);
	glScaled(0.005, 0.1, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0.8, 0);
	glTranslated(-1.9, 0.7, -0.15);
	glScaled(0.005, 0.1, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glRotated(90, 0, 1, 0);
	glRotated(-90, 1, 0, 0);
	glTranslated(0, 1.9, 0.1);
	glutSolidCone(0.02, 0.02, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-1.9, 0.95, 0);
	glutSolidSphere(0.01, 20, 20);
	glPopMatrix();
}


void drawFrenchFlag() {

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-1.9, 0.53, -0.35);
	glScaled(0.005, 0.85, 0.005);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslated(-1.9, 0.8, -0.4);
	glScaled(0.005, 0.3, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(-1.9, 0.8, -0.5);
	glScaled(0.005, 0.3, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(-1.9, 0.8, -0.6);
	glScaled(0.005, 0.3, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glRotated(90, 0, 1, 0);
	glRotated(-90, 1, 0, 0);
	glTranslated(0.35, 1.9, 0.1);
	glutSolidCone(0.02, 0.02, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-1.9, 0.95, -0.35);
	glutSolidSphere(0.01, 20, 20);
	glPopMatrix();
}


void drawItalianFlag() {

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-1.9, 0.53, 0.35);
	glScaled(0.005, 0.85, 0.005);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.6, 0.2);
	glTranslated(-1.9, 0.8, 0.3);
	glScaled(0.005, 0.3, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(-1.9, 0.8, 0.2);
	glScaled(0.005, 0.3, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(-1.9, 0.8, 0.1);
	glScaled(0.005, 0.3, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glRotated(90, 0, 1, 0);
	glRotated(-90, 1, 0, 0);
	glTranslated(-0.35, 1.9, 0.1);
	glutSolidCone(0.02, 0.02, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslated(-1.9, 0.95, 0.35);
	glutSolidSphere(0.01, 20, 20);
	glPopMatrix();
}

void drawScoreBoard() {
	glPushMatrix();
	glTranslated(0.8, 0, 2.3);
	glRotated(25, 0, 1, 0);
	glPushMatrix();
	glColor3f(0.7, 0.7, 0.7);
	glTranslated(-1.9, 1.1, -2.2);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	//glRotated(30, 0, 0, 1);
	GLUquadricObj* quadraticObj = gluNewQuadric();
	gluCylinder(quadraticObj, 0.04, 0.04, 1, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.7, 0.7, 0.7);
	glTranslated(-1.9, 1.51, -2.2);
	glScaled(0.1, 0.85, 0.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(-1.85, 1.5, -2.2);
	glScaled(0.06, 0.75, 0.42);
	glutSolidCube(1);
	glPopMatrix();


	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(-1.82, 1.5, -2.05);
	glScaled(0.04, 0.4, 0.04);
	glutSolidCube(1);
	glPopMatrix();

	if (victory && !timeOver) {
		glPushMatrix();
		glColor3f(1, 1, 0);
		glTranslated(-1.82, 1.5, -2.3);
		glScaled(0.04, 0.4, 0.04);
		glutSolidCube(1);
		glPopMatrix();
	}
	else {
		glPushMatrix();
		glColor3f(1, 1, 0);
		glTranslated(-1.85, 1.5, -2.3);
		glRotated(90, 0, 0, 1);
		glRotated(90, 1, 0, 0);
		glutSolidTorus(0.055, 0.055, 20, 20);
		glPopMatrix();
	}


	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(-1.85, 1.4, -2.15);
	glutSolidTorus(0.02, 0.02, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(-1.85, 1.6, -2.15);
	glutSolidTorus(0.02, 0.02, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glRotated(90, 0, 1, 0);
	glRotated(-90, 1, 0, 0);
	glTranslated(2.197, 1.9, 0.1);
	glutSolidCone(0.08, 0.08, 20, 20);
	glPopMatrix();


	glPopMatrix();
}


void drawBench() {
	glPushMatrix();
	glColor3f(0.7, 0.4, 0.1);
	glTranslated(0.9, 0.3, 0.28);
	glScaled(0.1, 0.05, 0.6);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.7, 0.4, 0.1);
	glTranslated(0.9, 0.32, 0.47);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj* quadraticObj1 = gluNewQuadric();
	gluCylinder(quadraticObj1, 0.01, 0.01, 0.22, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.7, 0.4, 0.1);
	glTranslated(0.9, 0.32, 0.27);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj* quadraticObj2 = gluNewQuadric();
	gluCylinder(quadraticObj2, 0.01, 0.01, 0.22, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.7, 0.4, 0.1);
	glTranslated(0.9, 0.32, 0.07);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj* quadraticObj3 = gluNewQuadric();
	gluCylinder(quadraticObj3, 0.01, 0.01, 0.22, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.7, 0.4, 0.1);
	glRotated(90, 0, 1, 0);
	glRotated(-90, 1, 0, 0);
	glTranslated(-0.47, -0.9, 0.105);
	glutSolidCone(0.02, 0.02, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.7, 0.4, 0.1);
	glRotated(90, 0, 1, 0);
	glRotated(-90, 1, 0, 0);
	glTranslated(-0.27, -0.9, 0.105);
	glutSolidCone(0.02, 0.02, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.7, 0.4, 0.1);
	glRotated(90, 0, 1, 0);
	glRotated(-90, 1, 0, 0);
	glTranslated(-0.07, -0.9, 0.105);
	glutSolidCone(0.02, 0.02, 20, 20);
	glPopMatrix();
}

void drawStadiumLights1() {
	//rotate in -30 in y, 10 in x
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(1.13, 3.1, -2.63);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj* quadraticObj1 = gluNewQuadric();
	gluCylinder(quadraticObj1, 0.05, 0.05, 3, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glRotated(-90, 0, 1, 0);
	glRotated(-90, 1, 0, 0);
	//z,x,y  +0.2 
	glTranslated(-2.63, 1.13, 0.1);
	glutSolidCone(0.15, 0.15, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(1.13, 3.43, -2.6);
	glRotated(-30, 0, 1, 0);
	glRotated(10, 1, 0, 0);
	glScaled(0.5, 0.9, 0.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(1.07, 3.73, -2.5);
	glRotated(-30, 0, 1, 0);
	glRotated(10, 1, 0, 0);
	glScaled(0.45, 0.26, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(1.09, 3.43, -2.55);
	glRotated(-30, 0, 1, 0);
	glRotated(10, 1, 0, 0);
	glScaled(0.45, 0.26, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(1.11, 3.13, -2.6);
	glRotated(-30, 0, 1, 0);
	glRotated(10, 1, 0, 0);
	glScaled(0.45, 0.26, 0.1);
	glutSolidCube(1);
	glPopMatrix();
}


void drawStadiumLights2() {
	//translate all in x  to -3
	//rotate in -30 in y, -10 in x
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(-2.13, 3.1, -2.63);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj* quadraticObj1 = gluNewQuadric();
	gluCylinder(quadraticObj1, 0.05, 0.05, 3, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glRotated(-90, 0, 1, 0);
	glRotated(-90, 1, 0, 0);
	//z,x,y  +0.2 
	glTranslated(-2.63, -2.13, 0.1);
	glutSolidCone(0.15, 0.15, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(-2.13, 3.43, -2.6);
	glRotated(30, 0, 1, 0);
	glRotated(10, 1, 0, 0);
	glScaled(0.5, 0.9, 0.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(-2.07, 3.73, -2.5);
	glRotated(30, 0, 1, 0);
	glRotated(10, 1, 0, 0);
	glScaled(0.45, 0.26, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(-2.09, 3.43, -2.55);
	glRotated(30, 0, 1, 0);
	glRotated(10, 1, 0, 0);
	glScaled(0.45, 0.26, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(-2.11, 3.13, -2.6);
	glRotated(30, 0, 1, 0);
	glRotated(10, 1, 0, 0);
	glScaled(0.45, 0.26, 0.1);
	glutSolidCube(1);
	glPopMatrix();
}

void drawStadiumLights3() {
	//translate all in x  to -3
	//translate all in z  to +3
	//rotate in 30 in y, 10 in x
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(-2.13, 3.1, 1.63);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj* quadraticObj1 = gluNewQuadric();
	gluCylinder(quadraticObj1, 0.05, 0.05, 3, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glRotated(-90, 0, 1, 0);
	glRotated(-90, 1, 0, 0);
	//z,x,y  +0.2 
	glTranslated(1.63, -2.13, 0.1);
	glutSolidCone(0.15, 0.15, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(-2.13, 3.43, 1.6);
	glRotated(-30, 0, 1, 0);
	glRotated(-10, 1, 0, 0);
	glScaled(0.5, 0.9, 0.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(-2.07, 3.73, 1.5);
	glRotated(-30, 0, 1, 0);
	glRotated(-10, 1, 0, 0);
	glScaled(0.45, 0.26, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(-2.09, 3.43, 1.55);
	glRotated(-30, 0, 1, 0);
	glRotated(-10, 1, 0, 0);
	glScaled(0.45, 0.26, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(-2.11, 3.13, 1.6);
	glRotated(-30, 0, 1, 0);
	glRotated(-10, 1, 0, 0);
	glScaled(0.45, 0.26, 0.1);
	glutSolidCube(1);
	glPopMatrix();
}


void drawStadiumLights4() {
	//translate all in z to +3
	//rotate in 30 in y, 10 in x
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(1.13, 3.1, 1.63);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj* quadraticObj1 = gluNewQuadric();
	gluCylinder(quadraticObj1, 0.05, 0.05, 3, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glRotated(-90, 0, 1, 0);
	glRotated(-90, 1, 0, 0);
	//z,x,y  +0.2 
	glTranslated(1.63, 1.13, 0.1);
	glutSolidCone(0.15, 0.15, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(1.13, 3.43, 1.6);
	glRotated(30, 0, 1, 0);
	glRotated(-10, 1, 0, 0);
	glScaled(0.5, 0.9, 0.2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(1.07, 3.73, 1.5);
	glRotated(30, 0, 1, 0);
	glRotated(-10, 1, 0, 0);
	glScaled(0.45, 0.26, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(1.09, 3.43, 1.55);
	glRotated(30, 0, 1, 0);
	glRotated(-10, 1, 0, 0);
	glScaled(0.45, 0.26, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(1.11, 3.13, 1.6);
	glRotated(30, 0, 1, 0);
	glRotated(-10, 1, 0, 0);
	glScaled(0.45, 0.26, 0.1);
	glutSolidCube(1);
	glPopMatrix();
}

void drawWorldCup() {
	glPushMatrix();
	glColor3f(0.9, 0.8, 0);
	glTranslated(-2.1, 0.45, -1.5);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj* quadraticObj1 = gluNewQuadric();
	gluCylinder(quadraticObj1, 0.02, 0.04, 0.16, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.8, 0);
	glTranslated(-2.1, 0.6, -1.5);
	glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj* quadraticObj2 = gluNewQuadric();
	gluCylinder(quadraticObj2, 0.05, 0.02, 0.15, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.4, 0);
	glRotated(90, 1, 0, 0);
	//  x,z,y
	glTranslated(-2.1, -1.5, -0.37);
	glutSolidTorus(0.023, 0.008, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.4, 0);
	glRotated(90, 1, 0, 0);
	//  x,z,y
	glTranslated(-2.1, -1.5, -0.34);
	glutSolidTorus(0.027, 0.008, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.8, 0);
	glTranslated(-2.1, 0.58, -1.5);
	glutSolidSphere(0.053, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.7, 0.3, 1);
	glTranslated(-2.1, 0.18, -1.5);
	glScaled(0.2, 0.3, 0.2);
	glutSolidCube(1);
	glPopMatrix();
}

void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}
void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}


void displayTextOnScreen(float x, float y, void* font, char* string) {
	char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void winScreen() {

	glColor3f(1, 0, 0);
	char buf[100] = { 0 };
	sprintf_s(buf, ":::::::::::::YOU WON::::::::::::");
	displayTextOnScreen(0.3, 0.35, GLUT_BITMAP_TIMES_ROMAN_24, buf);
}

void loseScreen() {
	glColor3f(1, 0, 0);
	char buf[100] = { 0 };
	sprintf_s(buf, ":::::::::::::YOU LOST::::::::::::");
	displayTextOnScreen(0.3, 0.37, GLUT_BITMAP_TIMES_ROMAN_24, buf);
}

void tryAgainScreen() {
	glColor3f(1, 0, 0);
	char buf[100] = { 0 };
	sprintf_s(buf, ":::::::PRESS R TO TRY AGAIN:::::::");
	displayTextOnScreen(0.3, 0.2, GLUT_BITMAP_TIMES_ROMAN_24, buf);
}



void Display() {
	setupCamera();
	setupLights();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (victory) {
		winScreen();
		tryAgainScreen();
	}
	if (defeat) {
		loseScreen();
		tryAgainScreen();
	}

	glPopMatrix();
	glTranslatef(0.5, 0, 0.5);
	drawGround(0.2);
	drawSurrounding();
	drawWorldCup();
	drawStadiumLights1();
	drawStadiumLights2();
	drawStadiumLights3();
	drawStadiumLights4();
	glPushMatrix();
	glTranslatef(0.2, -0.1, 1.8);
	glScaled(1.9, 1.9, 1.9);
	drawFirstGoalNet();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.2, -0.1, -0.9);
	glScaled(1.9, 1.9, 1.9);
	drawSecondGoalNet();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.3);
	drawBench();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -0.6);
	drawBench();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, 0, -1.5);
	drawBench();
	glPopMatrix();


	glPushMatrix();
	glTranslated(moveX, 0, moveZ);
	glRotated(rotPlayer, 0, 1, 0);
	glTranslated(rotX, rotY, rotZ);
	drawPlayer();
	glPopMatrix();

	drawScoreBoard();

	glPushMatrix();
	glTranslatef(0, 0, ballZ);
	drawFootball(-0.55, 0.146, -0.4, 0.04);
	glPopMatrix();

	drawGermanFlag();
	drawFrenchFlag();
	drawItalianFlag();

	glPopMatrix();
	glFlush();
}

void Keyboard(unsigned char key, int x, int y) {

	if (key == 'w' || key == 'W') {
		camera.moveY(d);
	}
	if (key == 's' || key == 'S') {
		camera.moveY(-d);
	}
	if (key == 'a' || key == 'A') {
		camera.moveX(d);
	}
	if (key == 'd' || key == 'D') {
		camera.moveX(-d);
	}
	if (key == 'q' || key == 'Q') {
		camera.moveZ(d);
	}
	if (key == 'e' || key == 'E') {
		camera.moveZ(-d);
	}
	if (key == 't' || key == 'T') {
		//top view
		PlaySound(TEXT("snap.wav"), NULL, SND_ASYNC);
		camera.eye = Vector3f(0, 8, 0);
		camera.center = Vector3f(0, 0, 0);
		camera.up = Vector3f(0, 0, -1);
		Eye.x = 0;
		Eye.y = 8;
		Eye.z = 0;
		Center.x = 0;
		Center.y = 0;
		Center.z = 0;
		Up.x = 0;
		Up.y = 0;
		Up.z = -1;
	}

	if (key == 'f' || key == 'F') {
		//front view
		PlaySound(TEXT("snap.wav"), NULL, SND_ASYNC);
		camera.eye = Vector3f(0, 1, -5);
		camera.center = Vector3f(0, 0, 1);
		camera.up = Vector3f(0, 1, 0);
		Eye.x = 0;
		Eye.y = 1;
		Eye.z = -5;
		Center.x = 0;
		Center.y = 0;
		Center.z = 1;
		Up.x = 0;
		Up.y = 1;
		Up.z = 0;
	}
	if (key == 'u' || key == 'U') {
		//side view
		PlaySound(TEXT("snap.wav"), NULL, SND_ASYNC);
		camera.eye = Vector3f(5, 2, 0);
		camera.center = Vector3f(0, 0, 0);
		camera.up = Vector3f(0, 1, 0);
		Eye.x = 5.0f;
		Eye.y = 2.0f;
		Eye.z = 0.0f;
		Center.x = 0;
		Center.y = 0;
		Center.z = 0;
		Up.x = 0;
		Up.y = 1;
		Up.z = 0;
	}
	if (key == 'b' || key == 'B') {
		//default view
		PlaySound(TEXT("snap.wav"), NULL, SND_ASYNC);
		camera.eye = Vector3f(4.5f, 4.5f, 4.5f);
		camera.center = Vector3f(0.0f, 0.0f, 0.0f);
		camera.up = Vector3f(0.0f, 1.0f, 0.0f);
		Eye.x = 4.5f;
		Eye.y = 4.5f;
		Eye.z = 4.5f;
		Center.x = 0;
		Center.y = 0;
		Center.z = 0;
		Up.x = 0;
		Up.y = 1;
		Up.z = 0;
	}
	if (key == 'r' || key == 'R') {
		moveX = 0;
		moveZ = 0;
		rotPlayer = 0;
		rotX = 0;
		rotY = 0;
		rotZ = 0;
		d = 0.05;
		yy = 0.01;
		ballZ = 0;
		bXmin = -2.35;
		bXmax = 0.49;
		bZmin = -2.78;
		bZmax = 1.09;
		endOfGame = false;
		timeOver = false;
		defeat = false;
		victory = false;
		footShoot = 0;
		timer = 0;
		camera.eye = Vector3f(4.5f, 4.5f, 4.5f);
		camera.center = Vector3f(0.0f, 0.0f, 0.0f);
		camera.up = Vector3f(0.0f, 1.0f, 0.0f);
		Eye.x = 4.5f;
		Eye.y = 4.5f;
		Eye.z = 4.5f;
		Center.x = 0;
		Center.y = 0;
		Center.z = 0;
		Up.x = 0;
		Up.y = 1;
		Up.z = 0;
	}
	if (key == '1') {
		if ((moveX) < bXmax) {
			moveX += yy;
			rotPlayer = 0;
			rotX = 0;
			rotY = 0;
			rotZ = 0;
		}
	}
	if (key == '2') {
		if ((moveX) > bXmin) {
			moveX -= yy;
			rotPlayer = 180;
			rotX = -0.9;
			rotY = 0;
			rotZ = -0.7;
		}
	}
	if (key == '3') {
		if ((moveZ) < bZmax) {
			moveZ += yy;
			rotPlayer = -90;
			rotX = -0.1;
			rotY = 0;
			rotZ = -0.8;
		}
	}
	if (key == '4') {
		if ((moveZ) > bZmin) {
			moveZ -= yy;
			rotPlayer = 90;
			rotX = -0.8;
			rotY = 0;
			rotZ = 0.1;
		}
	}
	if (key == GLUT_KEY_ESCAPE) {
		exit(EXIT_SUCCESS);
	}
	glutPostRedisplay();
}


void Special(int key, int x, int y) {
	float a = 1.0;
	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}
	glutPostRedisplay();
}



void Anim(int value)
{
	timer++;
	if (timer == 6000 && !endOfGame) {
		timeOver = true;
		endOfGame = true;
		defeat = true;
		PlaySound(TEXT("referee.wav"), NULL, SND_ASYNC);
	}
	if (moveZ > -0.9 && moveZ < -0.66 && moveX < -0.93 && moveX > -1.07) {
		if (footShoot != 1) {
			PlaySound(TEXT("footballkick.wav"), NULL, SND_ASYNC);
			footShoot++;
		}
	}
	if (footShoot) {
		if (ballZ > -1.9) {
			ballZ -= 0.01;
		}
		else {
			endOfGame = true;
			if (!timeOver) {
				victory = true;
			}
		}
	}
	glutTimerFunc(1, Anim, 0);
	glutPostRedisplay();
}

void Motion(int x, int y)
{
	y = wHeight - y;

	if (cameraZoom - y > 0)
	{
		Eye.x += -0.05;
		Eye.z += -0.05;
	}
	else
	{
		Eye.x += 0.05;
		Eye.z += 0.05;
	}

	cameraZoom = y;

	glLoadIdentity();
	camera.eye = Vector3f(Eye.x, Eye.y, Eye.z);
	camera.center = Vector3f(Center.x, Center.y, Center.z);
	camera.up = Vector3f(Up.x, Up.y, Up.z);
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glutPostRedisplay();
}


void Mouse(int button, int state, int x, int y)
{
	y = wHeight - y;
	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}

}


void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glLoadIdentity();
	glOrtho(-90, 100, -15, 100, 0, 1);

}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(wWidth, wHeight);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	WCHAR music[] = L"background.wav";
	LPCWSTR const Back_ground_music = L"open background.wav type mpegvideo alias Sound";
	mciSendString(Back_ground_music, NULL, 0, NULL);
	MCIERROR onrepeat = mciSendString(L"play Sound repeat", NULL, 0, NULL);
	glutCreateWindow("World Cup");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	init();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glutTimerFunc(0, Anim, 0);
	glShadeModel(GL_SMOOTH);
	glutMainLoop();
}
