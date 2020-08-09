// sphere.cpp : Defines the entry point for the console application.
//

#define GLUT_DISABLE_ATEXIT_HACK

#include <gl/glut.h>
#include"math.h"
float angle=0;
float PI=3.14;
//初始化OpenGL

void init(void) 
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);//设置背景颜色
	glShadeModel(GL_SMOOTH);//设置明暗处理,有两种选择模式：GL_FLAT（不渐变）和GL_SMOOTH（渐变过渡）
}

//球心坐标为（x，y，z），球的半径为radius，M，N分别表示球体的横纵向被分成多少份
void drawSphere(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat radius, GLfloat M, GLfloat N)
{ 
 float step_z = PI/M; 
 float step_xy = 2*PI/N;
 float x[4],y[4],z[4]; 
 float angle_z = 0.0; 
 float angle_xy = 0.0; 
 int i=0, j=0; 
 glBegin(GL_QUADS);  // glBegin(GL_LINE_LOOP); 
 for(i=0; i<M; i++)  
 {   
 angle_z = i * step_z; 
 for(j=0; j<N; j++) 
 {    
 angle_xy = j * step_xy; 
 x[0] = radius * sin(angle_z) * cos(angle_xy); 
 y[0] = radius * sin(angle_z) * sin(angle_xy);   
 z[0] = radius * cos(angle_z);    
 x[1] = radius * sin(angle_z + step_z) * cos(angle_xy);   
 y[1] = radius * sin(angle_z + step_z) * sin(angle_xy);    
 z[1] = radius * cos(angle_z + step_z);    
 x[2] = radius*sin(angle_z + step_z)*cos(angle_xy + step_xy);    
 y[2] = radius*sin(angle_z + step_z)*sin(angle_xy + step_xy);    
 z[2] = radius*cos(angle_z + step_z);    
 x[3] = radius * sin(angle_z) * cos(angle_xy + step_xy);    
 y[3] = radius * sin(angle_z) * sin(angle_xy + step_xy);    
 z[3] = radius * cos(angle_z);    
 for(int k=0; k<4; k++)    
 {     
	 glVertex3f(xx+x[k], yy+y[k],zz+z[k]);    
 }   
}  
} glEnd();
}
//主要的绘制过程
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);//清除颜色缓存    
	glLoadIdentity();
	glTranslatef(0,0,-15);
	glColor3f(1.0,0,0);
//	glutSolidTeapot(2.0);
//	glutSolidSphere(5,20,20);
	glRotatef(angle,1,1,1);
    drawSphere(0.0,0.0,0.0,5.0,30.0,60.0);
    glFlush();
}
//在窗口改变大小时调用
void reshape(int w, int h){
       glViewport(0, 0, w, h);//设置视口
       glMatrixMode(GL_PROJECTION);//切换到投影矩阵
       glLoadIdentity();//用单位矩阵替换当前变换矩阵
       gluPerspective(45, (float)w/h, 4, 100.0);//设置透视投影视图体
       glMatrixMode (GL_MODELVIEW);//设置完成后开始画图,需要切换到 模型视图矩阵 才能正确画图
       glLoadIdentity();
}
void TimerFunction(int value)
{
    angle+=10;
	if(angle==360)
		angle=0;
	// Redraw the scene with new coordinates
    glutPostRedisplay();
	glutTimerFunc(500,TimerFunction,1);
}

void main( )
{
	glutCreateWindow("sphere");//设置窗口标题
	init();//初始化OpenGL
	glutDisplayFunc(display);//设置显示回调函数 
	glutReshapeFunc(reshape);//设置reshape回调函数
	glutTimerFunc(500,TimerFunction, 1);

	glutMainLoop();//进入主循环

}
