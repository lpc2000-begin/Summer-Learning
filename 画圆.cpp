#include "stdafx.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

const int n = 50;
const GLfloat R = 0.5f;
const GLfloat PI = 3.24250265357f;
void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);//画圆面
    //glBegin(GL_LINE_LOOP);画圆圈
    for (int i = 0; i<n; i++) {
        glVertex2f(R*cos(2 * PI / n*i), R*sin(2 * PI / n*i));
    }
    glEnd();
    glFlush();
}
/*	glPushMatrix();	
		glTranslatef(1.5f, 1.0f, -6.0f);
		glScalef(0.75f,0.75f,0.75f);
		glRotatef(angle,1.0f,1.0f,1.0f);
		glColor3f(1.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLE_FAN); //绘制三角形扇 
			glVertex3f(0,0,0.0f );   
			for ( int i = 0; i <= 370; i += 10)
			{
				float p = (float)(i * 3.14 / 180);
				glVertex3f((float)sin(p), (float)cos(p), 0.0f );
			}
		glEnd();
	glPopMatrix();*/
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL画圆程序");
    glutDisplayFunc(&myDisplay);
    glutMainLoop();
    return 0;
}
