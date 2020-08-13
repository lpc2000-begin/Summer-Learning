#define GLUT_DISABLE_ATEXIT_HACK

#include <gl/glut.h>

#include"math.h"

#include "windows.h"

GLUquadricObj* qobj;//二次曲面声明类型

float angle=0;

float PI=3.14;

static float diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };	 

static float specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };	 

static float lightPosition[] = { 0.0f, 0.0f, 5.0f, 1.0f };



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



BYTE* gltReadBMPBits(const char *szFileName, int *nWidth, int *nHeight)

	{

	HANDLE hFileHandle;

	BITMAPINFO *pBitmapInfo = NULL;

	unsigned long lInfoSize = 0;

	unsigned long lBitSize = 0;

	BYTE *pBits = NULL;					// Bitmaps bits

	BITMAPFILEHEADER	bitmapHeader;

	DWORD dwBytes;



	// Open the Bitmap file

	hFileHandle = CreateFile(szFileName,GENERIC_READ,FILE_SHARE_READ,

		NULL,OPEN_EXISTING,FILE_FLAG_SEQUENTIAL_SCAN,NULL);



	// Check for open failure (most likely file does not exist).

	if(hFileHandle == INVALID_HANDLE_VALUE)

		return NULL;



	// File is Open. Read in bitmap header information

	ReadFile(hFileHandle,&bitmapHeader,sizeof(BITMAPFILEHEADER),	

		&dwBytes,NULL);



	// Check for a couple of simple errors	

	if(dwBytes != sizeof(BITMAPFILEHEADER))

		return FALSE;



	// Check format of bitmap file

	if(bitmapHeader.bfType != 'MB')

		return FALSE;



	// Read in bitmap information structure

	lInfoSize = bitmapHeader.bfOffBits - sizeof(BITMAPFILEHEADER);

	pBitmapInfo = (BITMAPINFO *) malloc(sizeof(BYTE)*lInfoSize);

	ReadFile(hFileHandle,pBitmapInfo,lInfoSize,&dwBytes,NULL);



	if(dwBytes != lInfoSize)

		{

        free(pBitmapInfo);

		CloseHandle(hFileHandle);

		return FALSE;

		}



	// Save the size and dimensions of the bitmap

	*nWidth = pBitmapInfo->bmiHeader.biWidth;

	*nHeight = pBitmapInfo->bmiHeader.biHeight;

	lBitSize = pBitmapInfo->bmiHeader.biSizeImage;



	// If the size isn't specified, calculate it anyway	

	if(pBitmapInfo->bmiHeader.biBitCount != 24)

		{

        free(pBitmapInfo);

		return FALSE;

		}



	if(lBitSize == 0)

		lBitSize = (*nWidth *

           pBitmapInfo->bmiHeader.biBitCount + 7) / 8 *

  		  abs(*nHeight);



	// Allocate space for the actual bitmap

	free(pBitmapInfo);

	pBits =(	BYTE *) malloc(sizeof(BYTE)*lBitSize);



	// Read in the bitmap bits, check for corruption

	if(!ReadFile(hFileHandle,pBits,lBitSize,&dwBytes,NULL) ||

			dwBytes != (sizeof(BYTE)*lBitSize))

		pBits = NULL;



	// Close the bitmap file now that we have all the data we need

	CloseHandle(hFileHandle);



	return pBits;

	}

//初始化OpenGL







void init(void) 



{

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//设置背景颜色

	glShadeModel(GL_SMOOTH);//设置明暗处理,有两种选择模式：GL_FLAT（不渐变）和GL_SMOOTH（渐变过渡）

	/** 设置0号光源 */

	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);

	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0); /**< 启用0号灰色光源,让物体可见 */

     BYTE *pBytes;

    int nWidth, nHeight;

	// 打开位图

	pBytes = gltReadBMPBits("earth.bmp", &nWidth, &nHeight);

////定义二维纹理

   glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,nWidth, nHeight, 0,

	GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

//

//控制滤波

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//说明映射方式

    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);



    glEnable(GL_TEXTURE_2D);

     

}



//球心坐标为（x，y，z），球的半径为radius，M，N分别表示球体的横纵向被分成多少份



void drawSphere(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat radius, GLfloat M, GLfloat N)

{ 



 float step_z = PI/M; 



 float step_xy = 2*PI/N;



 double x[4],y[4],z[4],a[3],b[3],c[3],s[4],t[4]; 


 double dNormal[3];



 float angle_z = 0.0; 



 float angle_xy = 0.0; 



 int i=0, j=0; 



 glBegin(GL_QUADS);  // glBegin(GL_LINE_LOOP); 



 for(i=0; i<=M; i++)  



 {   

 angle_z = i * step_z; 

	for(j=0; j<=N; j++) 
{    

 angle_xy = j * step_xy; 

 x[0] = radius * sin(angle_z) * cos(angle_xy); 
 
 y[0] = radius * sin(angle_z) * sin(angle_xy);   

 z[0] = radius * cos(angle_z);  
 
 s[0]=angle_xy/(2*PI);

 t[0]=angle_z/PI;

 x[1] = radius * sin(angle_z + step_z) * cos(angle_xy);   

 y[1] = radius * sin(angle_z + step_z) * sin(angle_xy);    

 z[1] = radius * cos(angle_z + step_z);    

 s[1]=angle_xy/(2*PI);

 t[1]=(angle_z + step_z)/PI;

 x[2] = radius*sin(angle_z + step_z)*cos(angle_xy + step_xy);    

 y[2] = radius*sin(angle_z + step_z)*sin(angle_xy + step_xy);    

 z[2] = radius*cos(angle_z + step_z);    

 s[2]=(angle_xy + step_xy)/(2*PI);

 t[2]=(angle_z + step_z)/PI;

 x[3] = radius * sin(angle_z) * cos(angle_xy + step_xy);    

 y[3] = radius * sin(angle_z) * sin(angle_xy + step_xy);    

 z[3] = radius * cos(angle_z);    

 s[3]=(angle_xy + step_xy)/(2*PI);

 t[3]=angle_z /PI;

 a[0]=x[0];
 a[1]=y[0];
 a[2]=z[0];

 b[0]=x[1];
 b[1]=y[1];
 b[2]=z[1];

 c[0]=x[2];
 c[1]=y[2];
 c[2]=z[2];
 
 
 
 

 for(int k=0; k<4; k++)    



 {    
    
	 CalculateNormal(a, b, c, dNormal);

	 glNormal3f(dNormal[0],dNormal[1],dNormal[2]);

     glTexCoord2f(s[k],t[k]);

	 glVertex3f(xx+x[k], yy+y[k],zz+z[k]);    

 }  

}  



} glEnd();



}


void earth()
{

	qobj = gluNewQuadric();//申请空间

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);//启用二维纹理

	gluQuadricTexture(qobj, GL_TRUE);//纹理函数

	//glutSolidSphere(10, 200, 200);                //画球体   

	gluSphere(qobj, 5, 60, 60); //二次曲面qobj

	glDisable(GL_TEXTURE_2D);//禁用二维纹理

	glPopMatrix();
}
//主要的绘制过程



void display(void)



{



	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//清除颜色缓存    

    glEnable(GL_DEPTH_TEST);

	glLoadIdentity();



	glTranslatef(0,0,-15);



	glColor3f(1.0,0,0);



//	glutSolidTeapot(2.0);



	

    glPushMatrix();

	

	glRotatef(angle,1,1,1);

	glColor3f(1.0,1.0,1.0);

	glColorMaterial(GL_FRONT,GL_DIFFUSE);

	glEnable(GL_COLOR_MATERIAL);
//earth();
    drawSphere(0.0,0.0,0.0,4.0,30.0,60.0);

	//glutSolidSphere(5,20,20);

glPopMatrix();

    glFlush();

 glutSwapBuffers();

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
