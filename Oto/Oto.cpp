#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <cmath>

using namespace std;

float headX = 0.0;
float headY = 0.0;
float headZ = 0.0;
float headRadius = .6; // Bán kính của đầu

float maxOuterRadius = 1;

float totalNumberCircleDrawed = headRadius / 1.18;
float curCircleRadius = .33;

bool isDrawing = false;

const int CODE_YELLOW = 0;
const int CODE_BROWN = 1;
const int CODE_BLACK = 2;

const int MODE_DOWN = 0;
const int MODE_UP = 1;

const float RATE_WIDTH_CIRCLE = .035;

const float PI = 3.14159;


void init() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);
}

void drawOxyz() {
	glBegin(GL_LINES);

	//Vẽ trục x
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(20, 0, 0);
	
	//Vẽ trục y
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 20, 0);

	//Vẽ trục z
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 20);

	glEnd();
}

void drawCircle(float innerRadius, float outerRadius, float zPoint) {
	glPushMatrix();
	glTranslatef(headX, headY, headZ - zPoint);
	glutSolidTorus(innerRadius, outerRadius, (GLint)100, (GLint)100);
	glPopMatrix();
}

void yellow() {
	glColor3f(1, .9, .1);
}

void brown() {
	glColor3f(.8, .5, .1);
}

void black() {
	glColor3f(0, 0, 0);
}

void wingColor() {
	glColor3f(0.7, 1, 0.9);
}

void resetValueVariable() {
	maxOuterRadius = 1;
	totalNumberCircleDrawed = headRadius / 1.18;
	curCircleRadius = .33;
}

void drawCircles(int numberCircle, float startRadius, int color, int mode, float increaseRadius, float dis) {
	for (int i = 0; i < numberCircle; i++)
	{
		if (color == CODE_YELLOW) {
			yellow();
		}
		else if (color == CODE_BROWN) {
			brown();
		}
		else if (color == CODE_BLACK) {
			black();
		}
		float radius = mode == MODE_UP ? i * increaseRadius : -i * increaseRadius;
		totalNumberCircleDrawed += dis;
		drawCircle(.04, startRadius + radius, totalNumberCircleDrawed);
		curCircleRadius = mode == MODE_UP ? curCircleRadius + increaseRadius : curCircleRadius - increaseRadius;
	}
}

void drawArc(float startX, float startY, float startZ, float radius, float startAngle, float endAngle, int numSegments, float increaseZ = 0) {
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= numSegments; ++i) {
		float angle = startAngle + (endAngle - startAngle) * i / numSegments;
		float x = startX + radius * cos(angle);
		float y = startY + radius * sin(angle);
		glVertex3f(x, y, startZ + increaseZ);
	}
	glEnd();
}

void display() {
	if (!isDrawing) {
		isDrawing = true;

		float eyeX = 7;
		float eyeY = 7;
		float eyeZ = 7;
		float centerX = 0;
		float centerY = 0;
		float centerZ = 0;
		float upX = 0;
		float upY = 1;
		float upZ = 0;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(0.0, 0.0, 0.0);
		glLoadIdentity();

		gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
		drawOxyz();

		//Vẽ đầu
		yellow();
		glPushMatrix();
		glTranslatef(headX, headY, headZ);
		glutSolidSphere(headRadius, 30, 30);
		glPopMatrix();

		//Vẽ mắt trái
		black();
		glPushMatrix();
		glTranslatef(headX + headRadius / 3.0, headY + headRadius / 3.0, headZ + headRadius - .01);
		glScalef(1, 1.25, 1);
		glutSolidSphere(.04, 30, 30);
		glPopMatrix();

		//Vẽ mắt phải
		black();
		glPushMatrix();
		glScalef(1, 1.25, 1);
		glTranslatef(headX - headRadius / 3.0, headY + headRadius / 3.0, headZ + headRadius - .01);
		glutSolidSphere(.04, 30, 30);
		glPopMatrix();

		//Vẽ miệng cười
		black();
		glPushMatrix();
		drawArc(0, 0, headRadius * .87, headRadius / 2, PI, 2* PI, 20);
		glPopMatrix();

		//Vẽ râu trái
		brown();
		glPushMatrix();
		drawArc(headX - headRadius * 1.3, headRadius * .87, headRadius / 2, headRadius, 0, PI / 2, 20, .01);
		glPopMatrix();

		//Vẽ quả trái
		brown();
		glPushMatrix();
		glTranslatef(headX - headRadius * 1.27, headY + headRadius * 1.8, headZ + headRadius * .6);
		glutSolidSphere(.06, 30, 30);
		glPopMatrix();

		//Vẽ râu phải
		brown();
		glPushMatrix();
		drawArc(headX + headRadius * 1.3, headRadius * .87, headRadius / 2, headRadius, PI, PI / 2, 20, .01);
		glPopMatrix();

		//Vẽ quả phải
		brown();
		glPushMatrix();
		glTranslatef(headX + headRadius * 1.27, headY + headRadius * 1.8, headZ + headRadius * .6);
		glutSolidSphere(.06, 30, 30);
		glPopMatrix();


		//Vẽ thân
		drawCircles(1, .3, CODE_BLACK, MODE_UP, .004, RATE_WIDTH_CIRCLE/2);

		drawCircles(3, curCircleRadius, CODE_YELLOW, MODE_UP, .03, RATE_WIDTH_CIRCLE);
		drawCircles(3, curCircleRadius, CODE_YELLOW, MODE_UP, .025, RATE_WIDTH_CIRCLE);
		drawCircles(1, curCircleRadius, CODE_BLACK, MODE_UP, .03, RATE_WIDTH_CIRCLE);

		drawCircles(5, curCircleRadius, CODE_BROWN, MODE_UP, .03, RATE_WIDTH_CIRCLE);
		drawCircles(1, curCircleRadius, CODE_BLACK, MODE_UP, .03, RATE_WIDTH_CIRCLE);

		drawCircles(5, curCircleRadius, CODE_YELLOW, MODE_UP, .01, RATE_WIDTH_CIRCLE);
		drawCircles(5, curCircleRadius, CODE_YELLOW, MODE_UP, .01, RATE_WIDTH_CIRCLE);
		drawCircles(1, curCircleRadius, CODE_BLACK, MODE_UP, .01, RATE_WIDTH_CIRCLE);

		drawCircles(7, curCircleRadius, CODE_BROWN, MODE_UP, .01, RATE_WIDTH_CIRCLE);
		drawCircles(1, curCircleRadius, CODE_BLACK, MODE_UP, .01, RATE_WIDTH_CIRCLE);

		drawCircles(5, curCircleRadius, CODE_YELLOW, MODE_UP, .009, RATE_WIDTH_CIRCLE);
		drawCircles(5, curCircleRadius, CODE_YELLOW, MODE_UP, .006, RATE_WIDTH_CIRCLE);
		drawCircles(1, curCircleRadius, CODE_BLACK, MODE_UP, .006, RATE_WIDTH_CIRCLE);

		drawCircles(7, curCircleRadius, CODE_BROWN, MODE_DOWN, .006, RATE_WIDTH_CIRCLE);
		drawCircles(1, curCircleRadius, CODE_BLACK, MODE_DOWN, .006, RATE_WIDTH_CIRCLE);

		drawCircles(5, curCircleRadius, CODE_YELLOW, MODE_DOWN, .009, RATE_WIDTH_CIRCLE);
		drawCircles(3, curCircleRadius, CODE_YELLOW, MODE_DOWN, .015, RATE_WIDTH_CIRCLE);
		drawCircles(5, curCircleRadius, CODE_YELLOW, MODE_DOWN, .02, RATE_WIDTH_CIRCLE);
		drawCircles(7, curCircleRadius, CODE_YELLOW, MODE_DOWN, .033, RATE_WIDTH_CIRCLE);
		//

		//Vẽ cánh trái
		wingColor();
		glPushMatrix();
		glScalef(.1, 1.25, .3);
		glRotatef(60.0, headX, headY + headRadius * 1.3, headZ - totalNumberCircleDrawed * 1.3);
		glTranslatef(headX, headY + headRadius * 1.3,  headZ - totalNumberCircleDrawed * 1.3);
		glutSolidSphere(1, 30, 30);
		glPopMatrix();

		//Vẽ cánh trái
		wingColor();
		glPushMatrix();
		glScalef(.1, 1.25, .3);
		glRotatef(-60.0, headX, headY + headRadius * 1.3, headZ - totalNumberCircleDrawed * 1.3);
		glTranslatef(headX, headY + headRadius * 1.3, headZ - totalNumberCircleDrawed * 1.3);
		glutSolidSphere(1, 30, 30);
		glPopMatrix();

		//Vẽ nọc
		black();
		glPushMatrix();
		glTranslatef(headX, headY, headZ - totalNumberCircleDrawed);
		glScalef(1, .2, 1);
		glutSolidTetrahedron();
		glPopMatrix();


		glFlush();

		isDrawing = false;
	}
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 1.5, 20);
	glMatrixMode(GL_MODELVIEW);
}

void keyPress(int key, int x, int y) {
	switch (key)
	{

		default:
			break;
	}
	resetValueVariable();
	glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// Xử lý sự kiện click chuột trái ở tọa độ (x, y)
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		// Xử lý sự kiện click chuột phải ở tọa độ (x, y)
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		// Xử lý sự kiện click chuột giữa ở tọa độ (x, y)
	}
	resetValueVariable();
	glutPostRedisplay();
}

void update(int value) {
	headY += 0.02;
	resetValueVariable();
	glutPostRedisplay();
	glutTimerFunc(5, update, 0);
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutSpecialFunc(keyPress);
	glutMouseFunc(mouseClick);
	glutDisplayFunc(display);
	glutTimerFunc(0, update, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}