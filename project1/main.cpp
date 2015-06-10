//Author: Rachel Law
//Fall 2014 - CS 130

//Read the README!

#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <iostream>
#include "point3d.h"
#include <fstream>
#include "triangle.h"
#include "transform.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
using namespace std;


vector<Point3D> f_points; //file points
vector<Point3D> f_edges; //file edges

vector<Point3D> triangle_table; //actually drawn
vector<float> color_table; //color values to follow triangles
vector<vector<float> > z_table; //z values

bool wireframe = false;


void GL_MousePress(int button, int state, int x, int y) {
  if (state==GLUT_DOWN) {
      // triangle_table.push_back(Point3D(x,WINDOW_HEIGHT-y, 0));
      glutPostRedisplay();
  }
}

//keyboard functions
void GLKeyboardPress(unsigned char key, int x, int y) {
  //wireframe
  if(key=='w') {
    wireframe = !wireframe;
    glutPostRedisplay();
  }

  //rotate left/right
  if (key=='d') {
    rotate_right(triangle_table);
    glutPostRedisplay();
  }
  if (key=='a') {
    rotate_left(triangle_table);
    glutPostRedisplay();
  }

  //zoom in/out
  if (key=='z') {
    zoom_in(triangle_table);
    glutPostRedisplay();
  }
  if (key=='x') {
    zoom_out(triangle_table);
    glutPostRedisplay();
  }

  //pan left/right/down/up
  if (key=='j') {
    pan_left(triangle_table);
    glutPostRedisplay();
  }
  if (key=='l') {
    pan_right(triangle_table);
    glutPostRedisplay();
  }
  if (key=='k') {   
    pan_down(triangle_table);
    glutPostRedisplay();
  }
  if (key=='i') {
    pan_up(triangle_table);
    glutPostRedisplay();
  }
}

//Converts the provided point, p, from screen coordinates to OpenGL coordinate system
Point3D GLscreenToWindowCoordinates(const Point3D & p) {
   //Obtain conversion values
   GLdouble model[16];
   glGetDoublev(GL_MODELVIEW_MATRIX, model);
   GLdouble projection[16];
   glGetDoublev(GL_PROJECTION_MATRIX, projection);
   GLint viewport[4];
   glGetIntegerv(GL_VIEWPORT,viewport);
    
   Point3D converted;
   GLdouble temp;
   //viewport[3] - p.y because of the flip on the y axis
   gluUnProject(p.x, viewport[3] - p.y, 0, model, projection, viewport,
                 &converted.x, &converted.y, &temp);
   return converted;
}


void GL_render()
{
  //clear out old data for the new render
  glClear(GL_COLOR_BUFFER_BIT);
  reset_ztable(z_table);

  //First sort the triangle vector into their min mid max
  //Then either fill triangles or only do wireframe depending on wireframe variable
  if (triangle_table.size()>=3 && triangle_table.size()%3==0) {
    sort_triangletable(triangle_table);

    for (int i=0; i<triangle_table.size(); i+=3) {
      if(!wireframe) {
        glColor3ub(color_table[i], color_table[i+1], color_table[i+2]);
        fill_triangle(triangle_table, z_table, color_table, i);
      }
      else {
        renderLine(triangle_table[i], triangle_table[i+1]);
        renderLine(triangle_table[i+1], triangle_table[i+2]);
        renderLine(triangle_table[i+2], triangle_table[i]);
      }
    }
  }

  glutSwapBuffers();
}

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv) {
  glutInit(argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  
  
  glutCreateWindow("CS 130 - Rachel Law");
  glutDisplayFunc(GL_render);

  
  // The default view coordinates is (-1.0, -1.0) bottom left & (1.0, 1.0) top right.
  // For the purposes of this lab, this is set to the number of pixels
  // in each dimension.
  glMatrixMode(GL_PROJECTION_MATRIX);
  glutMouseFunc(GL_MousePress);
  glutKeyboardFunc(GLKeyboardPress);
  glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
}


int main(int argc, char** argv) { 

  int file_pts, file_edges;
  int file_x, file_y, file_z;
  int file_i1, file_i2, file_i3;

  

  //THIS IS WHERE YOU PUT THE FILE BEING TESTED
  ifstream sampletri("sampletri.txt");




  sampletri >> file_pts >> file_edges; // getting number of points and edges to take in
  for (int i=0; i<file_pts; i++) { //push points into point vector
    sampletri >> file_x >> file_y >> file_z;
    f_points.push_back(Point3D(file_x, file_y, file_z));
  }
  for (int i=0; i<file_edges; i++) { //push edge indices into an edge vector
    sampletri >> file_i1 >> file_i2 >> file_i3;
    f_edges.push_back(Point3D(file_i1, file_i2, file_i3));
  }
  sampletri.close();
  
  initialize_triangletable(f_points, f_edges, triangle_table); //spawn all the triangles needed for the 3D projection into a triangle_table vector
  initialize_colortable(f_edges, color_table);
  initialize_ztable(z_table);


  cout << endl;
  cout << "Welcome - Sorry! The program runs kind of slow.\n\n";
  cout << "If you would like to change the test file, \n";
  cout << "please modify the main loop's ifstream file to your file name\n";
  cout << "___________________________________________________________________\n\n";   
  cout << "W - Wireframe\n";
  cout << "___________________________________________________________________\n\n";  
  cout << "A (Left Rotate)                              D (Right Rotate)\n";
  cout << "___________________________________________________________________\n\n";
  cout << "Z (Zoom IN)                                  X (Zoom OUT)\n";
  cout << "___________________________________________________________________\n\n";
  cout << "                      I (pan up)\n";
  cout << "J (pan left)          K (pan down)           L (pan right)\n";
  cout << "___________________________________________________________________\n\n";  

  GLInit(&argc, argv);
  glutMainLoop();

  return 0;
}
