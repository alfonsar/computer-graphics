/*
  CSCI 480 Computer Graphics
  Assignment 1: Height Fields
  C++ starter code
*/

#include <stdlib.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <pic.h>

int g_iMenuId;

int g_vMousePos[2] = {0, 0};
int g_iLeftMouseButton = 0;    /* 1 if pressed, 0 if not */
int g_iMiddleMouseButton = 0;
int g_iRightMouseButton = 0;
float s = 0.5;
float t=0.0;
typedef enum { ROTATE, TRANSLATE, SCALE } CONTROLSTATE;
enum polygon{POINTS,WIREFRAME,TRI};
polygon poly = WIREFRAME;

CONTROLSTATE g_ControlState = ROTATE;

/* state of the world */
float g_vLandRotate[3] = {0.0, 0.0, 0.0};
float g_vLandTranslate[3] = {0.0, 0.0, 0.0};
float g_vLandScale[3] = {1.0, 1.0, 1.0};

/* see <your pic directory>/pic.h for type Pic */
Pic * g_pHeightData;

/* Write a screenshot to the specified filename */
void saveScreenshot (char *filename)
{
  int i, j;
  Pic *in = NULL;

  if (filename == NULL)
    return;

  /* Allocate a picture buffer */
  in = pic_alloc(640, 480, 3, NULL);

  printf("File to save to: %s\n", filename);

  for (i=479; i>=0; i--) {
    glReadPixels(0, 479-i, 640, 1, GL_RGB, GL_UNSIGNED_BYTE,
                 &in->pix[i*in->nx*in->bpp]);
  }

  if (jpeg_write(filename, in))
    printf("File saved Successfully\n");
  else
    printf("Error in Saving\n");

  pic_free(in);
}

void myinit()
{
  /* setup gl view here */
  glClearColor(0.0, 0.0, 0.0, 0.0);
  //enable Depth Test
  glEnable(GL_DEPTH_TEST);
  //interpolate colors using rasterization
  glShadeModel(GL_SMOOTH);
  //setupCamera();
  //display();

}
//GLfloat theta[3] = {0.0, 0.0, 0.0};
void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  /* draw 1x1 cube about origin */
  /* replace this code with your height field implementation */
  /* you may also want to precede it with your 
rotation/translation/scaling */
  //glTranslatef(0.5f,0.0f,0.0f);
  //glRotatef(45.0f,0.0f,0.0f,1.0f);

  //write logic inside 
  // glBegin(GL_POLYGON);

  // glColor3f(1.0, 1.0, 1.0);
  // glVertex3f(-0.5, -0.5, 0.0);
  // glColor3f(0.0, 0.0, 1.0);
  // glVertex3f(-0.5, 0.5, 0.0);
  // glColor3f(0.0, 0.0, 0.0);
  // glVertex3f(0.5, 0.5, 0.0);
  // glColor3f(1.0, 1.0, 0.0);
  // glVertex3f(0.5, -0.5, 0.0);

  // glEnd();
    int width=g_pHeightData->nx;
    int height=g_pHeightData->ny;
    float divider = width/height;
  //glLoadIdentity resets matrix to back to its default state
  glLoadIdentity();
  //specifies a viewing frustrum into the world system coordinate
  gluPerspective(60.0, divider, 0.01, 1000.0);   
  //this is essential. gluLookAt creates a viewing matrix derived from an eye point, a reference point indicating the center of the scene, and an UP vector.
  //gluLookAt creates a viewing matrix by taking in an eyepoint, a reference point, and up vector
  gluLookAt(0.0, 1.5, 2.0, 0, 0, 0, 0, -1.0, 0);
  
  /*the switch is controlled by the keyboard inputs
  the switch controls the state that we want to be in 
   g_ControlState = TRANSLATE | ROTATE | SCALE
   We also control the type of polygon whether we want 
   polygonMode= POINTS | WIREFRAME | TRIANGLES
  z->wireframe x->point c->triangles */
  switch(g_ControlState){
      case ROTATE:
        glRotatef(g_vLandRotate[0],1,0,0);
        glRotatef(g_vLandRotate[1],0,1,0);
        glRotatef(g_vLandRotate[2],0,0,1);
        break;
      case TRANSLATE:
        glTranslatef(g_vLandTranslate[0],g_vLandTranslate[1],g_vLandTranslate[2]);
        break;
      case SCALE:
        glScalef(g_vLandScale[0],g_vLandScale[1],g_vLandScale[2]);
        break;
  }
  switch(poly){
    case POINTS:
      glPolygonMode(GL_FRONT,GL_POINT);
      glPolygonMode(GL_BACK,GL_POINT);
      break;
    case WIREFRAME:
      glPolygonMode(GL_FRONT, GL_LINE);
      glPolygonMode(GL_BACK, GL_LINE);
      break;
    case TRI:
      glPolygonMode(GL_FRONT,GL_FILL);
      glPolygonMode(GL_BACK,GL_FILL);
      break;
  }
       for(int i = 1; i <= height-1; i++)
       {
         glBegin(GL_TRIANGLE_STRIP);
               for(int j = 1; j <= width; j++)
               {
                 //grabs z index of the first pixel
                 int indx0=PIC_PIXEL(g_pHeightData,j,i,0);
                 //grabs z index of the second pixel
                 int indx1=PIC_PIXEL(g_pHeightData,j,i+1,0);
                 //printf("%f\n",indx0/255.0);
                 //color white
                 glColor3f(1.0, 1.0, 1.0);
                 glVertex3f((float (j) - float (width/2)) / (width/2),(float (i) - float (height/2)) / (height/2),indx0/255.0);
                 //instead of a static color, I chose color based on index heights
                 glColor3f(indx0/255.0, indx1/255.0, 1.0);
                 glVertex3f((float (j) - float (width/2)) / (width/2),(float (i+1) - float (height/2)) / (height/2),indx1/255.0);


               }
            glEnd(); 
       }
   
  glutSwapBuffers();
}
//glutPerspectice 
//rotate with keyboard
//position camera to look at front and zoomed out 

void menufunc(int value)
{
  switch (value)
  {
    case 0:
      exit(0);
      break;
  }
}
//using the keyboard to control the type of rendering whether wireframe, point, triangle
void keyboard(unsigned char key, int x, int y)
{
    if (key=='q' || key == 'Q') 
        exit(0);

    if (key=='z') 
      poly=WIREFRAME;
    if (key=='x') 
      poly=POINTS;
    if (key=='c') 
      poly=TRI;
   
    if(key=='s'){
      g_ControlState=SCALE;
    }
    if(key=='r'){
      g_ControlState=ROTATE;
    }
    if(key=='t'){
      g_ControlState=TRANSLATE;
    }
      


}
void doIdle()
{
  /* do some stuff... */

  /* make the screen update */
  glutPostRedisplay();
}

/* converts mouse drags into information about 
rotation/translation/scaling */
void mousedrag(int x, int y)
{
  int vMouseDelta[2] = {x-g_vMousePos[0], y-g_vMousePos[1]};
  
  switch (g_ControlState)
  {
    case TRANSLATE:  
      if (g_iLeftMouseButton)
      {
        g_vLandTranslate[0] += vMouseDelta[0]*0.01;
        g_vLandTranslate[1] -= vMouseDelta[1]*0.01;
      }
      if (g_iMiddleMouseButton)
      {
        g_vLandTranslate[2] += vMouseDelta[1]*0.01;
      }
      break;
    case ROTATE:
      if (g_iLeftMouseButton)
      {
        g_vLandRotate[0] += vMouseDelta[1];
        g_vLandRotate[1] += vMouseDelta[0];
      }
      if (g_iMiddleMouseButton)
      {
        g_vLandRotate[2] += vMouseDelta[1];
      }
      break;
    case SCALE:
      if (g_iLeftMouseButton)
      {
        g_vLandScale[0] *= 1.0+vMouseDelta[0]*0.01;
        g_vLandScale[1] *= 1.0-vMouseDelta[1]*0.01;
      }
      if (g_iMiddleMouseButton)
      {
        g_vLandScale[2] *= 1.0-vMouseDelta[1]*0.01;
      }
      break;
  }
  g_vMousePos[0] = x;
  g_vMousePos[1] = y;
}

void mouseidle(int x, int y)
{
  g_vMousePos[0] = x;
  g_vMousePos[1] = y;
}

void mousebutton(int button, int state, int x, int y)
{

  switch (button)
  {
    case GLUT_LEFT_BUTTON:
      g_iLeftMouseButton = (state==GLUT_DOWN);
      break;
    case GLUT_MIDDLE_BUTTON:
      g_iMiddleMouseButton = (state==GLUT_DOWN);
      break;
    case GLUT_RIGHT_BUTTON:
      g_iRightMouseButton = (state==GLUT_DOWN);
      break;
  }
 
  switch(glutGetModifiers())
  {
    case GLUT_ACTIVE_CTRL:
      g_ControlState = TRANSLATE;
      break;
    case GLUT_ACTIVE_SHIFT:
      g_ControlState = SCALE;
      break;
    default:
      g_ControlState = ROTATE;
      break;
  }

  g_vMousePos[0] = x;
  g_vMousePos[1] = y;
}

int main (int argc, char ** argv)
{
  if (argc<2)
  {  
    printf ("usage: %s heightfield.jpg\n", argv[0]);
    exit(1);
  }
  //name of image
  g_pHeightData = jpeg_read(argv[1], NULL);
  if (!g_pHeightData)
  {
    printf ("error reading %s.\n", argv[1]);
    exit(1);
  }

  glutInit(&argc,argv);
  
  /*
    create a window here..should be double buffered and use depth testing
  
    the code past here will segfault if you don't have a window set up....
    replace the exit once you add those calls.
  */
 //glutDouble -> allocate two frame buffers to switch between for smoother animations
 // GLUT_DEPTH --> allocate a Z-buffer for hidden surface elimination as per homework instructions request
 //glutInitDisplayMode --> set up display frame buffer
 glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
 //set up window size
 glutInitWindowSize(640,480);
 glutInitWindowPosition(100,100);
 //name the window you want to create -> in this case the name of the jpg
 glutCreateWindow("WE MISS YOU OBAMA!");
 //does depth comparisons and updates depth buffer
  glEnable(GL_DEPTH_TEST);

 // exit(0);

  /* tells glut to use a particular display function to redraw */
  glutDisplayFunc(display);
  
  /* allow the user to quit using the right mouse button menu */
  g_iMenuId = glutCreateMenu(menufunc);
  glutSetMenu(g_iMenuId);
  glutAddMenuEntry("Quit",0);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  
  /* replace with any animate code */
  glutIdleFunc(doIdle);

  /* callback for mouse drags */
  glutMotionFunc(mousedrag);
  /* callback for idle mouse movement */
  glutPassiveMotionFunc(mouseidle);
  /* callback for mouse button changes */
  glutMouseFunc(mousebutton);
  //callback for keyboard clicks
  glutKeyboardFunc(keyboard);
  /* do initialization */
  myinit();

  glutMainLoop();
  return(0);
}
