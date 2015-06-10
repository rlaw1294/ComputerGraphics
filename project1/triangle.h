//Author: Rachel Law
//Fall 2014 - CS 130

// triangle.h
//
// Contains all the functions necessary for filling triangles along with the
// corresponding z table and color table in order to fulfill filling
// 3D triangles.
/////////////////////////////////////////
#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__


#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include "point3d.h"
#include "transform.h"
using namespace std;

int calc_z(vector<Point3D> tritable, int tri_index, int x, int y);


void swap(vector<Point3D> &tritable, int a, int b) {
   Point3D temp = tritable[a];
   tritable[a] = tritable[b];
   tritable[b] = temp;
   return;
}

void sort_triangletable(vector<Point3D> &tritable) {
  if (tritable.size()>=3 && (tritable.size()%3==0)) {

    //bubble sorting
    for (int h=0; h<tritable.size(); h+=3) {
      for (int i=h; i<h+2; i++) {
        for (int j=h; j<h+2; j++) {
          if (tritable[j].y > tritable[j+1].y) { swap(tritable, j, j+1); }
        }
      }

      //also rearrange min mid max to what i want if they have same y value
      if (tritable[h].y == tritable[h+1].y) {
        if (tritable[h].x > tritable[h+1].x) {
        swap(tritable, h, h+1);
        }
      }
      if (tritable[h+1].y == tritable[h+2].y) {
        if (tritable[h+1].x > tritable[h+2].x) {
        swap(tritable, h+1, h+2);
        }
      }
    }
  }
}

//make 3 sets of pushes to make triangles into our result vector
void initialize_triangletable(vector<Point3D> pts, vector<Point3D> edges, vector<Point3D> &result) {
  if (edges.size()>0) {
    for (int i=0; i<edges.size(); i++) {
      result.push_back(pts[edges[i].x]);
      result.push_back(pts[edges[i].y]);
      result.push_back(pts[edges[i].z]);
    }
  }
}

//make 3 sets of pushes for r g b for each set of triangles :)
void initialize_colortable(vector<Point3D> edges, vector<float> &ctable) {
  if (edges.size()>0) {
    for (int i=0; i<=edges.size(); i++) {
      ctable.push_back(rand()%255 + 1);
      ctable.push_back(rand()%255 + 1);
      ctable.push_back(rand()%255 + 1);
    }
  }
}

//initialize all the z values to some huge number 
void initialize_ztable(vector<vector<float > > &ztable) {
  vector<float> temp(1000, 99999);
  for (int i=0; i<1000; i++) {
    ztable.push_back(temp);
  }
}

//reset z values back to huge number, or else rerender will be confused and 
//then not display anything due to the previous render's z values old information
void reset_ztable(vector<vector<float > > &ztable) {
  for (int i=0; i<1000; i++) {
    for (int j=0; j<1000; j++) {
      ztable[i][j] = 99999;
    }
  }
}


//Fill the triangle
void fill_triangle(vector<Point3D> tritable, vector<vector<float> > &ztable, vector<float> ctable, int tri_index) {
  Point3D min = tritable[tri_index];
  Point3D mid = tritable[tri_index+1];
  Point3D max = tritable[tri_index+2];
  float ml, mr, bl, br;
  float zcompare = -1;
  float my_z = -1;

  //Top Triangle
  //Finding INVERSE slopes| 1/m
  if (mid.y-max.y!=0) { ml = (mid.x - max.x) / (mid.y - max.y); }
  else { ml=0; }
  if (min.y-max.y!=0) { mr = (min.x - max.x) / (min.y - max.y); }
  else { mr=0; }

  //Finding b INVERSE | b = x-my
  bl = max.x - ml*max.y;
  br = max.x - mr*max.y;

  //Fill
  //x = x + 1/m*y
  for (int y=max.y; y>=mid.y; y--) {
    int xl = bl + ml*y;
    int xr = br + mr*y;
    //in case where the triangle sides are switched
    if (xl > xr) {
      int temp = xl;
      xl = xr;
      xr = temp;
    }
    for (int x=xl; x<=xr; x++) {
      if (x<1000 && y<1000 && x>0 && y>0) { zcompare = ztable[x][y]; }
      my_z = calc_z(tritable, tri_index, x, y);
      if (my_z < zcompare) {
        renderPixel(x,y);
        if (x<1000 && y <1000 && x>0 && y>0) { ztable[x][y] = my_z; }
      }
    }
  }


  //Bot Triangle
  //Finding INVERSE slopes| 1/m
  if (max.y-min.y!=0) ml = (max.x - min.x) / (max.y - min.y);
  else { ml=0; }
  if (mid.y-min.y!=0) mr = (mid.x - min.x) / (mid.y - min.y);
  else { mr=0; }

  //Finding b INVERSE | b = x-my
  bl = min.x - ml*min.y;
  br = min.x - mr*min.y;

  //Fill
  //x = x + 1/m*y
  for (int y=min.y; y<=mid.y; y++) {
    int xl = bl + ml*y;
    int xr = br + mr*y;
    //in case where the triangle sides are switched
    if (xl > xr) {
      int temp = xl;
      xl = xr;
      xr = temp;
    }
    for (int x=xl; x<=xr; x++) {
      if (x<1000 && y<1000 && x>0 && y>0) { zcompare = ztable[x][y]; }
      my_z = calc_z(tritable, tri_index, x, y);
      if (my_z < zcompare) {
        renderPixel(x,y);
        if (x<1000 && y <1000 && x>0 && y>0) { ztable[x][y] = my_z; }
      }      
    }
  }  
}

//Triangle crossproduct helper function to calculate z value
Point3D calc_triangle_crossproduct(Point3D min, Point3D mid, Point3D max) {
  Point3D u = min - mid;
  Point3D v = max - mid;

  //solve for cross product which is the normal
  Point3D normal;
  normal.x = u.y*v.z - u.z*v.y;
  normal.y = u.z*v.x - u.x*v.z;
  normal.z = u.x*v.y - u.y*v.x;

  return normal;
}

//Calculate z value using the points in the specified triangle, and
//at the specific x y coordinate given
int calc_z(vector<Point3D> tritable, int tri_index, int x, int y) {
  Point3D min = tritable[tri_index];
  Point3D mid = tritable[tri_index+1];
  Point3D max = tritable[tri_index+2];

  Point3D normal = calc_triangle_crossproduct(min, mid, max);

  /*Ax + By + Cz + D = 0
  A, B, C are the values from the normal
  D is solved by plugging in A B C with one of the points we found the normal from*/
  float A = normal.x;
  float B = normal.y;
  float C = normal.z;
  float D = -(A*mid.x + B*mid.y + C*mid.z);

  if (C==0) { return 0; } //can't work with undefined division
  return -((A*x + B*y + D) / C);
}

#endif
