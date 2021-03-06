#include "stdafx.h"
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <glew.h> 
#include <freeglut.h>
#pragma comment(lib,"glew32.lib") 
#include <iostream>

using namespace std;
GLfloat rotateV = 0.0;// 旋转速率
GLfloat rotateAngle = 0.0;//旋转角度
GLfloat anglex = 0.0;
GLfloat angley = 0.0;
GLfloat anglez = 0.0;
GLfloat axisx = 0.0;
GLfloat axisy = 0.0;
GLfloat axisz = 5.0;
GLint WinW = 600;
GLint WinH = 600;
GLfloat oldx; 
GLfloat oldy;

void init(void){
	glClearColor(0.0,0.0,0.0,0.0); //背景 
	glShadeModel(GL_FLAT);
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0); //线条
	glLoadIdentity();  //加载单位矩阵  
	gluLookAt(axisx, axisy, axisz,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
	glRotatef(rotateAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(anglex, 1.0, 0.0, 0.0);
	glRotatef(angley, 0.0, 1.0, 0.0);
	glRotatef(anglez, 0.0, 0.0, 1.0);
	glutWireTeapot(2);
	rotateAngle += rotateV;
	glutSwapBuffers();
}

void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON)	{
		if (state == GLUT_DOWN)	{
			rotateV = 0;
			rotateAngle = 0;
			oldx = x;
			oldy = y;
			cout << "moving" << endl;
		}

	}
	if (button == GLUT_RIGHT_BUTTON){
		if (state == GLUT_DOWN)	{
			rotateV -= 0.2f;
			cout << "rotating" << endl;
		}

	}
	if (button == 3){
		axisz -= 0.2;
	}
	if (button == 4){
		axisz += 0.2;
	}
}

void keyboard(unsigned char key, int x, int y){
	switch (key) {
		case 'w':
			axisz -= 0.2;
			glutPostRedisplay();
			break;
		case 's':
			axisz += 0.2;
			glutPostRedisplay();
			break;
		case 27:
			exit(0);
			break;
	}
}

void motion(int x, int y){
	GLint deltax = oldx - x;
	GLint deltay = oldy - y;
	anglex += 360 * (GLfloat)deltax / (GLfloat)WinW;
	angley += 360 * (GLfloat)deltay / (GLfloat)WinH;
	//anglez += 360 * (GLfloat)deltay / (GLfloat)WinH;
	oldx = x; 
	oldy = y;  
	glutPostRedisplay();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}
