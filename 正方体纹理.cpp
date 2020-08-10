#define GLUT_DISABLE_ATEXIT_HACK
#include <gl/glut.h>
#include "math.h"
#include "windows.h"
float angle=0;
/** 再定义一个默认的光源 */
static float diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };	 
static float specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };	 
static float lightPosition[] = { 0.0f, 0.0f, 5.0f, 1.0f };

GLuint textures[4];


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
void DrawCube()
{
        
	
//top
		 glBindTexture(GL_TEXTURE_2D, textures[0]);
		 glEnable(GL_TEXTURE_2D);
     
   glBegin(GL_QUADS);
		 glNormal3f( 0.0f, 1.0f, 0.0f);								/**< 指定法线向上 */
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	
		glEnd();

	//front
		 
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glEnable(GL_TEXTURE_2D);
     
		glBegin(GL_QUADS);
	  glNormal3f(0.0,0,1.0);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1,1,1);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1,-1,1);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(1,-1,1);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(1,1,1);
		glEnd();

	//right
glBindTexture(GL_TEXTURE_2D, textures[2]);
glEnable(GL_TEXTURE_2D);
     
glBegin(GL_QUADS);
	 glNormal3f(1.0,0,0);
glTexCoord2f(0.0f, 1.0f);	glVertex3f(1,1,1);
glTexCoord2f(0.0f, 0.0f);	glVertex3f(1,-1,1);
glTexCoord2f(1.0f, 0.0f);	glVertex3f(1,-1,-1);
glTexCoord2f(1.0f, 1.0f);	glVertex3f(1,1,-1);
glEnd();

	//bottom
glBindTexture(GL_TEXTURE_2D, textures[3]);
glBegin(GL_QUADS);
	 glNormal3f(0,-1.0,0);
glTexCoord2f(0.0f, 1.0f);	glVertex3f(1,-1,-1);
glTexCoord2f(1.0f, 1.0f);	glVertex3f(1,-1,1);
glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1,-1,1);
glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1,-1,-1);
glEnd();

	//back
glBindTexture(GL_TEXTURE_2D, textures[1]);
glEnable(GL_TEXTURE_2D);
     
glBegin(GL_QUADS);
	 glNormal3f(0,0,-1.0);
glTexCoord2f(0.0f, 1.0f);	glVertex3f(1,1,-1);
glTexCoord2f(0.0f, 0.0f);	glVertex3f(1,-1,-1);
glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1,-1,-1);
glTexCoord2f(1.0f, 1.0f);	glVertex3f(-1,1,-1);
glEnd();
//left
glBindTexture(GL_TEXTURE_2D, textures[2]);
glEnable(GL_TEXTURE_2D);
     
glBegin(GL_QUADS);
	 glNormal3f(-1.0,0,0);
glTexCoord2f(0.0f, 0.0f);glVertex3f(-1,1,1);
glTexCoord2f(1.0f, 0.0f);glVertex3f(-1,1,-1);
glTexCoord2f(1.0f, 1.0f);glVertex3f(-1,-1,-1);
glTexCoord2f(0.0f, 1.0f);glVertex3f(-1,-1,1);



	glEnd();


	
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
	
   glGenTextures(4,textures);
	
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	// Load the texture objects
	pBytes = gltReadBMPBits("floor.bmp", &nWidth, &nHeight);
    glBindTexture(GL_TEXTURE_2D, textures[0]);	
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB8,nWidth, nHeight, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	free(pBytes);
	
	pBytes = gltReadBMPBits("block4.bmp", &nWidth, &nHeight);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB8,nWidth, nHeight, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	free(pBytes);
	
	pBytes = gltReadBMPBits("block5.bmp", &nWidth, &nHeight);
    glBindTexture(GL_TEXTURE_2D, textures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB8,nWidth, nHeight, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	free(pBytes);
	
	pBytes = gltReadBMPBits("block6.bmp", &nWidth, &nHeight);
    glBindTexture(GL_TEXTURE_2D, textures[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB8,nWidth, nHeight, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	free(pBytes);


}
//主要的绘制过程
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//清除颜色缓存    
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	
	glTranslatef(0,0,-10);




	glPushMatrix();


	glRotatef(angle,1,1,0);
	glColor3f(1.0,1.0,1.0);

	glColorMaterial(GL_FRONT,GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	DrawCube();	
	

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
	
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutCreateWindow("Basic");//设置窗口标题

	glutDisplayFunc(display);//设置显示回调函数 
	glutReshapeFunc(reshape);//设置reshape回调函数
	glutTimerFunc(500,TimerFunction, 1);
	
		init();//初始化OpenGL
   
	glutMainLoop();//进入主循环

	glDeleteTextures(4,textures);

}

