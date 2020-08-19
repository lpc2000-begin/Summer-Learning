#include <windows.h>
#include <gl/glut.h>
#define MAX_CHAR    128// ASCII字符总共只有0到127，一共128种字符
void selectFont(int size, int charset, const char* face) 
{
    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
        charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hOldFont);
}
void drawString(char *s)
{
	 //申请MAX_CHAR个连续的显示列表编号
    GLuint TextFont = glGenLists(MAX_CHAR);
        
    //把每个字符的绘制命令都装到对应的显示列表中
    wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, TextFont); 

    //调用每个字符对应的显示列表，绘制每个字符
    for(; *s!='\0'; ++s)
    glCallList(TextFont + *s);
}
void drawCNString(const char* str)	
{	
	int len, i;
	wchar_t* wstring;
    HDC hDC = wglGetCurrentDC();
    GLuint list = glGenLists(1);

    // 计算字符的个数
    // 如果是双字节字符的（比如中文字符），两个字节才算一个字符
    // 否则一个字节算一个字符
    len = 0;
    for(i=0; str[i]!='\0'; ++i)
    {
        if( IsDBCSLeadByte(str[i]) )
            ++i;
        ++len;
		}

    // 将混合字符转化为宽字符
    wstring = (wchar_t*)malloc((len+1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
    wstring[len] = L'\0';

    // 逐个输出字符
    for(i=0; i<len; ++i)
    {
        wglUseFontBitmapsW(hDC, wstring[i], 1, list);
        glCallList(list);
    }

    // 回收所有临时资源
    free(wstring);
    glDeleteLists(list, 1);
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    selectFont(48, ANSI_CHARSET, "Comic Sans MS");
    glColor3f(1.0, 0.0, 0.0);
    glRasterPos2f(0.5, 0.5);
    drawString("hello!");

    selectFont(12, GB2312_CHARSET, "楷体_GB2312");
    glColor3f(1.0f, 1.0f, 0.0f);
    glRasterPos2f(0.5, 0.4);
    drawCNString("我们的汉字");

	selectFont(12, DEFAULT_CHARSET, "华文仿宋");
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos2f(0.5, 0.3);
    drawCNString("傳統的中國漢字");

    glutSwapBuffers();
    glFlush();
}

void reshape(int w, int h)
{


  glViewport(0,0,w,h);

  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();

  glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();

}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA); 
    glutCreateWindow("play");
    glutDisplayFunc(display);
	glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
