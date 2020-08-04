#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define PI 3.1415926
float h,m,s;
void Draw(){    
	int i;
	float R,TR,h_Angle,m_Angle,s_Angle,count,h_Length,m_Length,s_Length;
	R=0.5;    
	TR=R-0.05;    
	glClearColor(1.0,1.0,1.0,0.0);	
	glClear(GL_COLOR_BUFFER_BIT);  //用白色清空颜色缓冲区    
	glColor3f(0.0,0.0,0.0);
    //绘制表盘
	glLineWidth(20);    
	glBegin(GL_POLYGON); 
	glColor3f(0.98,0.625,0.12);
	for (i=0; i<100; i++)    
	{        
		glVertex2f(R*cos(2*PI/100*i),R*sin(2*PI/100*i));   
	} 
	glEnd();
	//绘制刻度      
	for (i=0; i<12; i++) 
	{    
		if (i == 0)        
		{            	            
			glColor3f(0.98,0.04,0.7);  //当画0点钟的刻度时，颜色设置为粉红色       
		}       
		else       
		{                   
			glColor3f(0.0,1.0,1.0);  //其他的刻度，颜色都为青色       
		}
		glPointSize(3.0f);
		glBegin(GL_POINTS);          
		glVertex2f(TR*sin(2*PI/12*i),TR*cos(2*PI/12*i));              
		glEnd(); 
	}   

	h_Length=0.2; 

	m_Length=0.3; 

	s_Length=0.4;

	count=60; //秒分时每次的转动幅度

	s_Angle=s/count;

	count*=60; 

	m_Angle=(m*60+s)/count; 

	count*=12; 

	h_Angle=(h*60*60+m*60+s)/count; 
    //秒针
	glLineWidth(1);

	glBegin(GL_LINES);  

    glColor3f(0.0,1.0,1.0);

	glVertex2f(0.0f,0.0f);        

	glVertex2f(s_Length*sin(2*PI*s_Angle),s_Length*cos(2*PI*s_Angle)); 

	glEnd();  
    //分针
	glLineWidth(3); 

	glBegin(GL_LINES);
	
    glColor3f(0.98,0.04,0.7);

	glVertex2f(0.0f,0.0f);     

	glVertex2f(m_Length*sin(2*PI*m_Angle),m_Length*cos(2*PI*m_Angle));  

	glEnd(); 
    //时针
	glLineWidth(5); 

	glBegin(GL_LINES);
    
    glColor3f(0.60,0.40,0.70);

    glVertex2f(0.0f,0.0f);   

	glVertex2f(h_Length*sin(2*PI*h_Angle),h_Length*cos(2*PI*h_Angle));   

	glEnd(); 
    //表芯
    glBegin(GL_POLYGON); 

    glColor3f(1.0,0.0,0.0);

	for (i=0; i<100; i++)   

	{      

		glVertex2f(0.03*cos(2*PI/100*i),0.03*sin(2*PI/100*i));  

	}  

	glEnd();  

	glutSwapBuffers();//在回调函数中所有绘制操作完成后调用glutSwapBuffers()交换两个缓冲区指针。

}

	

void Update()

	{   

	time_t rawtime;  

	struct tm * timeinfo;

    time ( &rawtime ); 

	timeinfo = localtime ( &rawtime );  

	h=timeinfo->tm_hour;  

	m=timeinfo->tm_min;   

	s=timeinfo->tm_sec;  

	glutPostRedisplay();//在图像绘制的所bai有操作之后，要加入 glutPostRedisplay() 来重绘图像，否则图像只有响应鼠标或键盘消息时才会更新图像。有点像窗口重绘函数一样。它要求当前的回调函数返回时执行显示回调函数

	}

	

void Reshape(int w,int h)

	{   
	
		glViewport(0,0,w,h);

	}

	

int main(int argc, char *argv[])

	{   

		glutInit(&argc, argv);   ////glutInit，对GLUT进行初始化，这个函数必须在其它的GLUT使用之前调用一次。其格式比较死板，一般照抄这句glutInit(&argc, argv)就可以了。

		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);//设置显示方式,其中GLUT_RGB表示使用RGB颜色,与之对应的GLUT_INDEX表示使用索引颜色。GLUT_SINGLE表示使用单缓冲，与之对应的还有GLUT_DOUBLE（使用双缓冲）

		glutInitWindowPosition(100, 100);  //设置窗口在屏幕中的位置.

		glutInitWindowSize(400, 400);   //设置窗口的大小

		glutCreateWindow("我的钟表");   

		glutDisplayFunc(&Draw);   

                glutReshapeFunc(&Reshape); 

		glutIdleFunc(&Update); 

		glutMainLoop();   //进行一个消息循环。这个函数可以显示窗口，并且等待窗口关闭后才会返回

		return 0;

	}
