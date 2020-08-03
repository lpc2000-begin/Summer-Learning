#define GLUT_DISABLE_ATEXIT_HACK

#include <gl/glut.h>
#include<math.h>
float angle=0;
/** 再定义一个默认的光源 */
static float diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };	 
static float specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };	 
static float lightPosition[] = { 0.0f, 0.0f,  10.0f, 1.0f };


void CalculateNormal(GLdouble *dVertex1, 
			GLdouble *dVertex2, GLdouble *dVertex3, 
			GLdouble *dNormal)
{
	GLdouble dVector1[3],dVector2[3];
	dVector1[0]=dVertex2[0]-dVertex1[0];
	dVector1[1]=dVertex2[1]-dVertex1[1];
	dVector1[2]=dVertex2[2]-dVertex1[2];
	dVector2[0]=dVertex3[0]-dVertex1[0];
	dVector2[1]=dVertex3[1]-dVertex1[1];
	dVector2[2]=dVertex3[2]-dVertex1[2];

	dNormal[0]=dVector1[1]*dVector2[2]-dVector1[2]*dVector2[1];
	dNormal[1]=dVector1[2]*dVector2[0]-dVector1[0]*dVector2[2];
	dNormal[2]=dVector1[0]*dVector2[1]-dVector1[1]*dVector2[0];

	double dNormalLength=sqrt(dNormal[0]*dNormal[0]
			+dNormal[1]*dNormal[1]+dNormal[2]*dNormal[2]);
	if(dNormalLength!=0.0)
	{
		dNormal[0]=dNormal[0]/dNormalLength;
		dNormal[1]=dNormal[1]/dNormalLength;
		dNormal[2]=dNormal[2]/dNormalLength;
	}
	else
	{
		dNormal[0]=0.0;
		dNormal[1]=0.0;
		dNormal[2]=1.0;
	}

}


void DrawCube1()
{
 glBegin(GL_QUADS);
	
//top
   glNormal3f(0,1.0,0);
    glVertex3f(1,1,1);
	glVertex3f(1,1,-1);
	glVertex3f(-1,1,-1);
	glVertex3f(-1,1,1);
	//front
	  glNormal3f(0.0,0,1.0);
	glVertex3f(-1,1,1);
	glVertex3f(-1,-1,1);
	glVertex3f(1,-1,1);
	glVertex3f(1,1,1);
	//right
	 glNormal3f(1.0,0,0);
	glVertex3f(1,1,1);
	glVertex3f(1,-1,1);
	glVertex3f(1,-1,-1);
	glVertex3f(1,1,-1);
	//bottom
	 glNormal3f(0,-1.0,0);
	glVertex3f(1,-1,-1);
	glVertex3f(1,-1,1);
	glVertex3f(-1,-1,1);
	glVertex3f(-1,-1,-1);

	//back
	 glNormal3f(0,0,-1.0);
	glVertex3f(1,1,-1);
	glVertex3f(1,-1,-1);
	glVertex3f(-1,-1,-1);
	glVertex3f(-1,1,-1);
//left
	 glNormal3f(-1.0,0,0);
	glVertex3f(-1,1,1);
	glVertex3f(-1,1,-1);
	glVertex3f(-1,-1,-1);
	glVertex3f(-1,-1,1);


	glEnd();


}
void DrawCube()
{
        double dPoint1[3],dPoint2[3],dPoint3[3];
	double dNormal[3];

	
	//top
     dPoint1[0]=1;	 dPoint1[1]=1;  dPoint1[2]=-1;
	dPoint2[0]=-1;	 dPoint2[1]=1; dPoint2[2]=-1;
	dPoint3[0]=-1;	 dPoint3[1]=1; dPoint3[2]=1;
	CalculateNormal(dPoint1,dPoint2,dPoint3,dNormal);
	glBegin(GL_QUADS);
	glNormal3dv(dNormal);
     glVertex3f(1,1,-1);
	glVertex3f(-1,1,-1);	
	glVertex3f(-1,1,1);
	glVertex3f(1,1,1);
	glEnd();

	//front
	dPoint1[0]=-1;	 dPoint1[1]=1;  dPoint1[2]=1;
	dPoint2[0]=-1;	 dPoint2[1]=-1; dPoint2[2]=1;
	dPoint3[0]=1;	 dPoint3[1]=-1; dPoint3[2]=1;
	CalculateNormal(dPoint1,dPoint2,dPoint3,dNormal);
	glBegin(GL_QUADS);
	glNormal3dv(dNormal);
	glVertex3f(-1,1,1);
	glVertex3f(-1,-1,1);
	glVertex3f(1,-1,1);
	glVertex3f(1,1,1);
	glEnd();

	//right
	
	dPoint1[0]=1;	 dPoint1[1]=1;  dPoint1[2]=-1;
	dPoint2[0]=1;	 dPoint2[1]=1; dPoint2[2]=1;
	dPoint3[0]=1;	 dPoint3[1]=-1; dPoint3[2]=1;
	CalculateNormal(dPoint1,dPoint2,dPoint3,dNormal);
	glBegin(GL_QUADS);
	glNormal3dv(dNormal);
	glVertex3f(1,1,-1);
	glVertex3f(1,1,1);
	glVertex3f(1,-1,1);
	glVertex3f(1,-1,-1);

	glEnd();
	//bottom
	dPoint1[0]=1;	 dPoint1[1]=-1;  dPoint1[2]=1;
	dPoint2[0]=-1;	 dPoint2[1]=-1; dPoint2[2]=1;
	dPoint3[0]=-1;	 dPoint3[1]=-1; dPoint3[2]=-1;
	CalculateNormal(dPoint1,dPoint2,dPoint3,dNormal);
    glBegin(GL_QUADS);
	glNormal3dv(dNormal);
	glVertex3f(1,-1,1);
	glVertex3f(-1,-1,1);
	glVertex3f(-1,-1,-1);
	glVertex3f(1,-1,-1);
	glEnd();
	//back
	dPoint1[0]=1;	 dPoint1[1]=1;  dPoint1[2]=-1;
	dPoint2[0]=1;	 dPoint2[1]=-1; dPoint2[2]=-1;
	dPoint3[0]=-1;	 dPoint3[1]=-1; dPoint3[2]=-1;
	CalculateNormal(dPoint1,dPoint2,dPoint3,dNormal);
	glBegin(GL_QUADS);
	glNormal3dv(dNormal);
	glVertex3f(1,1,-1);
	glVertex3f(1,-1,-1);
	glVertex3f(-1,-1,-1);
	glVertex3f(-1,1,-1);
	glEnd();

	//left
	dPoint1[0]=-1;	 dPoint1[1]=1;  dPoint1[2]=1;
	dPoint2[0]=-1;	 dPoint2[1]=1; dPoint2[2]=-1;
	dPoint3[0]=-1;	 dPoint3[1]=-1; dPoint3[2]=-1;
	CalculateNormal(dPoint1,dPoint2,dPoint3,dNormal);
	glBegin(GL_QUADS);
	glNormal3dv(dNormal);
	glVertex3f(-1,1,1);
	glVertex3f(-1,1,-1);
	glVertex3f(-1,-1,-1);
	glVertex3f(-1,-1,1);	
	
	glEnd();
	
	

	
}
//初始化OpenGL
void init(void) 
{
	glClearColor(1.0f, 1.0f, 0.0f, 0.0f);//设置背景颜色
	glShadeModel(GL_SMOOTH);//设置明暗处理,有两种选择模式：GL_FLAT（不渐变）和GL_SMOOTH（渐变过渡）
	/** 设置0号光源 */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); /**< 启用0号灰色光源,让物体可见 */
}
//主要的绘制过程
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//清除颜色缓存    
	glLoadIdentity();

	
	glTranslatef(0,0,-10);




	glPushMatrix();


	glRotatef(angle,1,1,0);
	glColor3f(1.0,0.0,0.0);

	glColorMaterial(GL_FRONT,GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	DrawCube1();	
	
   glPopMatrix();
   glFlush();
	 glutSwapBuffers();
}
//在窗口改变大小时调用
void reshape(int w, int h){
       glViewport(0, 0, w, h);//设置视口
       glMatrixMode(GL_PROJECTION);//设置当前为投影变换模式
       glLoadIdentity();//用单位矩阵替换当前变换矩阵
       gluPerspective(45, (float)w/h, 4, 100.0);//设置正交投影视图体
        glMatrixMode (GL_MODELVIEW);
       glLoadIdentity();
}
void TimerFunction(int value)
{
    angle+=10;
	if(angle==360)
		angle=0;
	
	
	// Redraw the scene with new coordinates
    glutPostRedisplay();
	glutTimerFunc(500,TimerFunction, 1);
}

void main( )
{
	
	
	glutCreateWindow("Basic");//设置窗口标题
	init();//初始化OpenGL
	glutDisplayFunc(display);//设置显示回调函数 
	glutReshapeFunc(reshape);//设置reshape回调函数
	glutTimerFunc(500,TimerFunction, 1);

	glutMainLoop();//进入主循环

}

