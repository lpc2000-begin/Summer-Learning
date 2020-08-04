#include "stdafx.h" 
#include <gl/glut.h>
#include"math.h"
void init(void)
{//光照参数初始化全位于此处	
GLfloat mat_specular   [] = {1.0,1.0,1.0,1.0};	
GLfloat mat_shininess  [] = {100.0};	
GLfloat light_position [] = {5.0,5.0,5.0,1.0};  //点光源	//
GLfloat light_position [] = {0.0,0.0,50.0,0.0};  //无限远模拟平行光	
GLfloat white_light    [] = {1.0,1.0,1.0,1.0};	
GLfloat model_ambient  [] = {0.1,0.1,0.1,1.0};	
glClearColor(0.0,0.0,0.0,0.0);	
glShadeModel(GL_SMOOTH);	//为场景中的物体定义材料属性：如何反射光线（材料环境、散射、镜面颜色、光泽度）	
glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);     //使用镜面材质颜色	
glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);   //使用光泽度 	
glLightfv(GL_LIGHT0,GL_POSITION,light_position);        //定义光源的位置	
glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light);            //定义散射光为白色
glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);           //定义镜面光为白色	
glLightModelfv(GL_LIGHT_MODEL_AMBIENT,model_ambient);   //光照模型参数：全局环境光 	
glEnable(GL_LIGHTING); //驱动光源	
glEnable(GL_LIGHT0);   //启动特定光源	
glEnable(GL_DEPTH_TEST);}
void display(void)
{	
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
glutSolidSphere(1.0,300,16);   //定义球体法向量	
glFlush();
}
void reshape(int w, int h)
{	
glViewport(0,0,(GLsizei)w,(GLsizei)h);	
glMatrixMode(GL_PROJECTION);	
glLoadIdentity();	
if( w<h )		
glOrtho(-1.5,1.5,-1.5*(GLfloat)h/(GLfloat)w, 1.5*(GLfloat)h/(GLfloat)w,-10.0,10.0);	
else		
glOrtho(-1.5,1.5,-1.5*(GLfloat)w/(GLfloat)h, 1.5*(GLfloat)w/(GLfloat)h,-10.0,10.0);	
glMatrixMode(GL_MODELVIEW);	
glLoadIdentity();
}
int main(int argc, char** argv)
{	
glutInit(&argc,argv);	
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);	
glutInitWindowPosition(200,200);	
glutInitWindowSize(400,400);	
glutCreateWindow(argv[0]);	
init();	
glutDisplayFunc(display);	
glutReshapeFunc(reshape);	
glutMainLoop();	
return 0;
}
