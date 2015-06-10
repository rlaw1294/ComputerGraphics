//Author: Rachel Law
//Fall 2014 - CS 130

// transform.h
//
// Contains all the triangle transform functions
/////////////////////////////////////////
#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include "point3d.h"
#include "triangle.h"
using namespace std;

void rotate_left(vector<Point3D> &tritable) {
  int degree = 10;
  float radian = degree*M_PI/180;

  float center_x = 0;
  float center_y = 0;
  float center_z = 0;


  //Find center of object (average)
  for (int i=0; i<tritable.size(); i++) {
      center_x += tritable[i].x;
      center_y += tritable[i].y;
      center_z += tritable[i].z;
  }
  center_x /= tritable.size();
  center_y /= tritable.size();
  center_z /= tritable.size();

  //Rotation Steps - Handle per triangle set
  for (int i=0; i<tritable.size(); i+=3) {
    Point3D p0 = tritable[i];
    Point3D p1 = tritable[i+1];
    Point3D p2 = tritable[i+2];

    //Translate to center
    //Use temp variables to hold values for modifying the points
    p0.x -= center_x;
    p0.y -= center_y;
    p0.z -= center_z;

    p1.x -= center_x;
    p1.y -= center_y;
    p1.z -= center_z;

    p2.x -= center_x;
    p2.y -= center_y;
    p2.z -= center_z;

    //Can't continue using p0, p1, p2 because would end up overwriting, so use more temps
    /*Rotate (math functions in radians)
    x = x cos(theta) + x sin(theta)
    y = y
    z = -z sin(theta) + z cos(theta) 
    |cos    0    sin    0| | x |
    |0      1    0      0| | y |
    |-sin   0    cos    0| | z |
    |0      0    0      1| | 1 |*/

    float tempx0 = (p0.x * cos(radian)) + (p0.z * sin(radian));
    float tempy0 = p0.y;
    float tempz0 = -(p0.x * sin(radian)) + (p0.z * cos(radian));
    // cout << tempx0 << endl << tempy0 << endl << tempz0 << endl << endl;
    p0.x = tempx0;
    p0.y = tempy0;
    p0.z = tempz0;

    float tempx1 = (p1.x * cos(radian)) + (p1.z * sin(radian));
    float tempy1 = p1.y;
    float tempz1 = -(p1.x * sin(radian)) + (p1.z * cos(radian));
    // cout << tempx1 << endl << tempy1 << endl << tempz1 << endl << endl;
    p1.x = tempx1;
    p1.y = tempy1;
    p1.z = tempz1;

    float tempx2 = (p2.x * cos(radian)) + (p2.z * sin(radian));
    float tempy2 = p2.y;
    float tempz2 = -(p2.x * sin(radian)) + (p2.z * cos(radian));
    // cout << tempx2 << endl << tempy2 << endl << tempz2 << endl << endl;
    p2.x = tempx2;
    p2.y = tempy2;
    p2.z = tempz2;

    //Translate to original position
    p0.x += center_x;
    p0.y += center_y;
    p0.z += center_z;

    p1.x += center_x;
    p1.y += center_y;
    p1.z += center_z;

    p2.x += center_x;
    p2.y += center_y;
    p2.z += center_z;

    //Set actual points in vector to transformed points
    tritable[i] = p0;
    tritable[i+1] = p1;
    tritable[i+2] = p2;
  }
}

void rotate_right(vector<Point3D> &tritable) {
  int degree = 10;
  float radian = degree*M_PI/180;

  float center_x = 0;
  float center_y = 0;
  float center_z = 0;


  //Find center of object (average)
  for (int i=0; i<tritable.size(); i++) {
      center_x += tritable[i].x;
      center_y += tritable[i].y;
      center_z += tritable[i].z;
  }
  center_x /= tritable.size();
  center_y /= tritable.size();
  center_z /= tritable.size();

  //Rotation Steps - Handle per triangle set
  for (int i=0; i<tritable.size(); i+=3) {
    Point3D p0 = tritable[i];
    Point3D p1 = tritable[i+1];
    Point3D p2 = tritable[i+2];

    //Translate to center
    //Use temp variables to hold values for modifying the points
    p0.x -= center_x;
    p0.y -= center_y;
    p0.z -= center_z;

    p1.x -= center_x;
    p1.y -= center_y;
    p1.z -= center_z;

    p2.x -= center_x;
    p2.y -= center_y;
    p2.z -= center_z;

    //Can't continue using p0, p1, p2 because would end up overwriting, so use more temps
    /*Rotate (math functions in radians)
    x = x cos(theta) + x sin(theta)
    y = y
    z = -z sin(theta) + z cos(theta) 
    |cos    0    -sin    0| | x |
    |0      1    0      0| | y |
    |sin   0    cos    0| | z |
    |0      0    0      1| | 1 |*/

    float tempx0 = (p0.x * cos(radian)) - (p0.z * sin(radian));
    float tempy0 = p0.y;
    float tempz0 = (p0.x * sin(radian)) + (p0.z * cos(radian));
    // cout << tempx0 << endl << tempy0 << endl << tempz0 << endl << endl;
    p0.x = tempx0;
    p0.y = tempy0;
    p0.z = tempz0;

    float tempx1 = (p1.x * cos(radian)) - (p1.z * sin(radian));
    float tempy1 = p1.y;
    float tempz1 = +(p1.x * sin(radian)) + (p1.z * cos(radian));
    // cout << tempx1 << endl << tempy1 << endl << tempz1 << endl << endl;
    p1.x = tempx1;
    p1.y = tempy1;
    p1.z = tempz1;

    float tempx2 = (p2.x * cos(radian)) - (p2.z * sin(radian));
    float tempy2 = p2.y;
    float tempz2 = +(p2.x * sin(radian)) + (p2.z * cos(radian));
    // cout << tempx2 << endl << tempy2 << endl << tempz2 << endl << endl;
    p2.x = tempx2;
    p2.y = tempy2;
    p2.z = tempz2;

    //Translate to original position
    p0.x += center_x;
    p0.y += center_y;
    p0.z += center_z;

    p1.x += center_x;
    p1.y += center_y;
    p1.z += center_z;

    p2.x += center_x;
    p2.y += center_y;
    p2.z += center_z;

    //Set actual points in vector to transformed points
    tritable[i] = p0;
    tritable[i+1] = p1;
    tritable[i+2] = p2;
  }
}


void zoom_in(vector<Point3D> &tritable) {
  float zoom = 1.05;

  float center_x = 0;
  float center_y = 0;
  float center_z = 0;


  //Find center of object (average)
  for (int i=0; i<tritable.size(); i++) {
      center_x += tritable[i].x;
      center_y += tritable[i].y;
      center_z += tritable[i].z;
  }
  center_x /= tritable.size();
  center_y /= tritable.size();
  center_z /= tritable.size();

  //Rotation Steps - Handle per triangle set
  for (int i=0; i<tritable.size(); i+=3) {
    Point3D p0 = tritable[i];
    Point3D p1 = tritable[i+1];
    Point3D p2 = tritable[i+2];

    //Translate to center
    //Use temp variables to hold values for modifying the points
    p0.x -= center_x;
    p0.y -= center_y;
    p0.z -= center_z;

    p1.x -= center_x;
    p1.y -= center_y;
    p1.z -= center_z;

    p2.x -= center_x;
    p2.y -= center_y;
    p2.z -= center_z;

    /*
    |dx     0            0| | x |
    |0      dy    0      0| | y |
    |0      0     dz     0| | z |
    |0      0     0      1| | 1 |*/

    p0.x *= zoom;
    p0.y *= zoom;
    p0.z *= zoom;

    p1.x *= zoom;
    p1.y *= zoom;
    p1.z *= zoom;

    p2.x *= zoom;
    p2.y *= zoom;
    p2.z *= zoom;

    //Translate to original position
    p0.x += center_x;
    p0.y += center_y;
    p0.z += center_z;

    p1.x += center_x;
    p1.y += center_y;
    p1.z += center_z;

    p2.x += center_x;
    p2.y += center_y;
    p2.z += center_z;

    //Set actual points in vector to transformed points
    tritable[i] = p0;
    tritable[i+1] = p1;
    tritable[i+2] = p2;
  }
}


void zoom_out(vector<Point3D> &tritable) {
  float zoom = 0.9;

  float center_x = 0;
  float center_y = 0;
  float center_z = 0;


  //Find center of object (average)
  for (int i=0; i<tritable.size(); i++) {
      center_x += tritable[i].x;
      center_y += tritable[i].y;
      center_z += tritable[i].z;
  }
  center_x /= tritable.size();
  center_y /= tritable.size();
  center_z /= tritable.size();

  //Rotation Steps - Handle per triangle set
  for (int i=0; i<tritable.size(); i+=3) {
    Point3D p0 = tritable[i];
    Point3D p1 = tritable[i+1];
    Point3D p2 = tritable[i+2];

    //Translate to center
    //Use temp variables to hold values for modifying the points
    p0.x -= center_x;
    p0.y -= center_y;
    p0.z -= center_z;

    p1.x -= center_x;
    p1.y -= center_y;
    p1.z -= center_z;

    p2.x -= center_x;
    p2.y -= center_y;
    p2.z -= center_z;

    /*
    |dx     0            0| | x |
    |0      dy    0      0| | y |
    |0      0     dz     0| | z |
    |0      0     0      1| | 1 |*/

    p0.x *= zoom;
    p0.y *= zoom;
    p0.z *= zoom;

    p1.x *= zoom;
    p1.y *= zoom;
    p1.z *= zoom;

    p2.x *= zoom;
    p2.y *= zoom;
    p2.z *= zoom;

    //Translate to original position
    p0.x += center_x;
    p0.y += center_y;
    p0.z += center_z;

    p1.x += center_x;
    p1.y += center_y;
    p1.z += center_z;

    p2.x += center_x;
    p2.y += center_y;
    p2.z += center_z;

    //Set actual points in vector to transformed points
    tritable[i] = p0;
    tritable[i+1] = p1;
    tritable[i+2] = p2;
  }
}

void pan_left(vector<Point3D> &tritable) {
  float pan = 20;
  for (int i=0; i<tritable.size(); i+=3) {
    Point3D p0 = tritable[i];
    Point3D p1 = tritable[i+1];
    Point3D p2 = tritable[i+2];
    //Translate
    p0.x -= pan;
    p1.x -= pan;
    p2.x -= pan;

    /*
    |1      0           dx| | x |
    |0      1     0     dy| | y |
    |0      0     1     dz| | z |
    |0      0     0      1| | 1 |*/

    //Set actual points in vector to transformed points
    tritable[i] = p0;
    tritable[i+1] = p1;
    tritable[i+2] = p2;
  }
}

void pan_right(vector<Point3D> &tritable) {
  float pan = 20;
  for (int i=0; i<tritable.size(); i+=3) {
    Point3D p0 = tritable[i];
    Point3D p1 = tritable[i+1];
    Point3D p2 = tritable[i+2];
    //Translate
    p0.x += pan;
    p1.x += pan;
    p2.x += pan;

    /*
    |1      0           dx| | x |
    |0      1     0     dy| | y |
    |0      0     1     dz| | z |
    |0      0     0      1| | 1 |*/

    //Set actual points in vector to transformed points
    tritable[i] = p0;
    tritable[i+1] = p1;
    tritable[i+2] = p2;
  }
}

void pan_down(vector<Point3D> &tritable) {
  float pan = 20;
  for (int i=0; i<tritable.size(); i+=3) {
    Point3D p0 = tritable[i];
    Point3D p1 = tritable[i+1];
    Point3D p2 = tritable[i+2];
    //Translate
    p0.y -= pan;
    p1.y -= pan;
    p2.y -= pan;

    /*
    |1      0           dx| | x |
    |0      1     0     dy| | y |
    |0      0     1     dz| | z |
    |0      0     0      1| | 1 |*/

    //Set actual points in vector to transformed points
    tritable[i] = p0;
    tritable[i+1] = p1;
    tritable[i+2] = p2;
  }
}

void pan_up(vector<Point3D> &tritable) {
  float pan = 20;
  for (int i=0; i<tritable.size(); i+=3) {
    Point3D p0 = tritable[i];
    Point3D p1 = tritable[i+1];
    Point3D p2 = tritable[i+2];
    //Translate
    p0.y += pan;
    p1.y += pan;
    p2.y += pan;

    /*
    |1      0           dx| | x |
    |0      1     0     dy| | y |
    |0      0     1     dz| | z |
    |0      0     0      1| | 1 |*/

    //Set actual points in vector to transformed points
    tritable[i] = p0;
    tritable[i+1] = p1;
    tritable[i+2] = p2;
  }
}



#endif
