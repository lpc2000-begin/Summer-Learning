void reshape(int w,int h)
{
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
if(w>h)
{
  glOrtho(-2.0,2.0,-2.0*h/w,2.0*h/w,-10,10);
}
else{
  glOrtho(-2.0*w/h,2.0*w/h,-2.0,2.0,-10,10);
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
