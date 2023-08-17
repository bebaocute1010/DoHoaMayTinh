#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <cmath>

using namespace std;

float headX = 0.0;
float headY = 0.0;
float headZ = 0.0;
float headRadius = .6; // Bán kính của đầu

float rotationAngle = 0.0;

float objectX = 0.0;//cho quay quanh trục y
float objectY = 0.0;
float objectZ = 0.0;

float initialObjectX = 0.0; // tọa độ đầu
float initialObjectY = 0.0;
float initialObjectZ = 0.0;

bool isMovingBack = false;// Biến để kiểm tra xem vật đang di chuyển về vị trí đầu tiên hay không

//float wingY = 0.0;

float maxOuterRadius = 1;

float totalLengthBee = headRadius / 1.18;
float curCircleRadius = .33;
float angleWing = 0;

int timerCount = 0;

bool isDrawing = false;
bool isMaxAngleWing = false;


float eyeX = 10;
float eyeY = 7;
float eyeZ = 15;
float centerX = 0;
float centerY = 0;
float centerZ = 0;
float upX = 0;
float upY = 1;
float upZ = 0;

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

void yellow() {
	GLfloat diffuse[] = { 1, .9, .1, 1.0 };// as khuếch tán
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glColor3f(1, .9, .1);
}

void brown() {
	GLfloat diffuse[] = { .8, .5, .1, 1.0 };// as khuếch tán
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glColor3f(.8, .5, .1);
}

void black() {
	GLfloat diffuse[] = { 0, 0, 0, 1.0 };// as khuếch tán
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glColor3f(0, 0, 0);
}

void wingColor() {
	GLfloat diffuse[] = { .1, .8, 1, 1.0 };// as khuếch tán
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glColor3f(.1, .8, 1);
}

void resetValueVariable() {
	maxOuterRadius = 1;
	totalLengthBee = headRadius / 1.18;
	curCircleRadius = .33;
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
	/*if (!isDrawing) {
		isDrawing = true;*/

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(0.0, 0.0, 0.0);
		glLoadIdentity();
		gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
		
		drawOxyz();

		//glutPostRedisplay();

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);// mặc định đc truyền màu light1-7 k dc màu đen
		GLfloat ambient[] = { 1.0, 0.5, 1.0, 1.0 };// ánh sáng môi trường, gt cuối là anpha
		GLfloat specular[] = { 1.0, 0.0, 0.0, 0.0 };// phản xạ
		GLfloat position[] = { 1.0, 1.0, 1.0, 1.0 };// vị trí nguồn sáng
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);// nguồn sáng, hàm số, gt
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);


		////////quay 360 
		glTranslatef(objectX, objectY, objectZ);
		glRotatef(rotationAngle, 0.0, 1.0, 0.0);

		//Vẽ đầu

		yellow();
		glPushMatrix();
		glTranslatef(headX, headY, headZ);
		glutSolidSphere(headRadius, 30, 30);
		glPopMatrix();

		// Vẽ thân		
		glPushMatrix();
		glTranslatef(headX , headY, headZ - 1.3);
		glScalef(.75, .75, 1);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();
		
		// Sọc
		
		glPushMatrix();
		black();
		glTranslatef(headX, headY, headZ - 0.65);		
		glScalef(0.37, 0.37, 0.3);
		glutSolidTorus(0.5, 1, 20, 20);
		glPopMatrix();
		
		// Sọc

		glPushMatrix();
		black();
		glTranslatef(headX, headY, headZ - 0.95);
		glScalef(0.49, 0.49, 0.3);
		glutSolidTorus(0.5, 1, 20, 20);
		glPopMatrix();

		// Sọc

		glPushMatrix();
		black();
		glTranslatef(headX, headY, headZ - 1.3);
		glScalef(0.53, 0.53, 0.3);
		glutSolidTorus(0.5, 1, 20, 20);
		glPopMatrix();

		// Sọc

		glPushMatrix();
		black();
		glTranslatef(headX, headY, headZ - 1.7);
		glScalef(0.49, 0.49, 0.3);
		glutSolidTorus(0.5, 1, 20, 20);
		glPopMatrix();

		// Sọc

		glPushMatrix();
		black();
		glTranslatef(headX, headY, headZ - 2.0);
		glScalef(0.35, 0.35, 0.3);
		glutSolidTorus(0.5, 1, 20, 20);
		glPopMatrix();

		//Vẽ mắt trái
		black();
		glPushMatrix();
		glTranslatef(headX + headRadius * .33, headY + headRadius * .33, headZ + headRadius - .01);
		glScalef(1, 1.25, 1);
		glutSolidSphere(.04, 30, 30);
		glPopMatrix();

		//Vẽ mắt phải
		black();
		glPushMatrix();
		glTranslatef(headX - headRadius * .33, headY + headRadius * .33, headZ + headRadius - .01);
		glScalef(1, 1.25, 1);
		glutSolidSphere(.04, 30, 30);
		glPopMatrix();

		//Vẽ miệng cười
		black();
		glPushMatrix();
		drawArc(headX, headY, headZ + headRadius * .87, headRadius / 2, PI, 2* PI, 20);
		glPopMatrix();

		//Vẽ râu trái
		brown();
		glPushMatrix();
		drawArc(headX - headRadius * 1.3, headY + headRadius * .87, headZ + headRadius / 2, headRadius, 0, PI / 2, 20, .01);
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
		drawArc(headX + headRadius * 1.3, headY + headRadius * .87, headZ + headRadius / 2, headRadius, PI, PI / 2, 20, .01);
		glPopMatrix();

		//Vẽ quả phải
		brown();
		glPushMatrix();
		glTranslatef(headX + headRadius * 1.27, headY + headRadius * 1.8, headZ + headRadius * .6);
		glutSolidSphere(.06, 30, 30);
		glPopMatrix();
		

		//Vẽ cánh trái
		wingColor();
		glPushMatrix();
		glRotatef(angleWing, 0, 0, -1);
		glRotatef(40, 0, 0, 1);
		glTranslatef(headX, headY + headRadius * 2, headZ - 1.2);
		glScalef(.1, 1.3, .5);
		glutSolidSphere(1, 30, 30);
		glPopMatrix();

		//Vẽ cánh trái
		wingColor();
		glPushMatrix();
		glRotatef(angleWing, 0,0,1);
		glRotatef(40, 0, 0, -1);
		glTranslatef(headX, headY + headRadius * 2, headZ - 1.2);
		glScalef(.1, 1.3, .5);
		glutSolidSphere(1, 30, 30);
		glPopMatrix();


		//Vẽ nọc
		black();
		glPushMatrix();
		glTranslatef(headX, headY, headZ - 2);
		glScalef(.5, .2, 1);
		glutSolidTetrahedron();
		glPopMatrix();

		glFlush();
	/*	isDrawing = false;
	}*/
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 1.5, 20);
	glMatrixMode(GL_MODELVIEW);
	//gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
	//gluLookAt(-7.0, 3.0, 5.0, 0, 0, 0, 0, 1, 0);
}

void specialKeyPress(int key, int x, int y) {
	switch (key)
	{
	/*case GLUT_KEY_UP:
		eyeY += 0.5;
		break;
	case GLUT_KEY_DOWN:
		eyeY -= 0.5;
		break;
	case GLUT_KEY_RIGHT:
		eyeZ -= 0.5;
		break;
	case GLUT_KEY_LEFT:
		eyeZ += 0.5;
		break;
	default:
			break;*/

	}
	resetValueVariable();
	glutPostRedisplay();
}

void keyboardPress(unsigned char key, int x, int y) {
	switch (key)
	{
		case 'r':/// phím r quay 360 quanh y
            rotationAngle += 1.0; // Tăng góc quay lên 5 độ
            if (rotationAngle >= 360.0) {
                rotationAngle -= 360.0; // Đảm bảo góc không vượt quá 360 độ
            }
            glutPostRedisplay();
            break;
		case 'm':
			isMovingBack = true;
			glutPostRedisplay();
			break;

		/*case 'l':
			eyeX += .5;
			break;
		case 'k':
			eyeX -= .5;
			break;*/
		case 'w':
			headY += 0.0;
			break;
		/*case 's':
			headY -= 0.1;
			break;
		case 'd':
			headZ -= 0.1;
			break;
		case 'a':
			headZ += 0.1;
			break;
		default:
			break;*/
	
	}
	if (key == 27) { // Phím ESC
		exit(0);
	}

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
	//headY += .2;
	headZ += .1;

	if (!isMaxAngleWing) {
		angleWing += 2.0;
		if (angleWing >= 90) {
			isMaxAngleWing = true;
		}
	}
	else {
		angleWing -= 2.0;
		if (angleWing <= 40) {
			isMaxAngleWing = false;
		}

	}

	if (isMovingBack && objectZ < headZ) {
		objectZ -= 0.01; // Giảm tọa độ X theo tốc độ di chuyển
	}
	else {
		isMovingBack = false;
	}

	resetValueVariable();
	glutPostRedisplay();
	glutTimerFunc(50, update, 0);
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(900, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutSpecialFunc(specialKeyPress);
	glutKeyboardFunc(keyboardPress);
	glutMouseFunc(mouseClick);
	glutDisplayFunc(display);
	glutTimerFunc(0, update, 1);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}