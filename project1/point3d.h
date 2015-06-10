//Author: Rachel Law
//Fall 2014 - CS 130

// Point3D.h
// 
// Contains Point3D and Trivial GL stuff that I didn't want clogging my main file
// renderpixel, renderline
/////////////////////////////////////////
#ifndef __POINT3D_H__
#define __POINT3D_H__

struct Point3D
{
	double x;
	double y;
	double z;

	Point3D() : x(0.0), y(0.0), z(0.0) {}
	Point3D(const double & nx, const double & ny, const double & nz) : x(nx), y(ny), z(nz) {}
	
	Point3D operator+(const Point3D & rhs) const { return Point3D(x + rhs.x, y + rhs.y, z + rhs.z); }
	Point3D operator-(const Point3D & rhs) const { return Point3D(x - rhs.x, y - rhs.y, z - rhs.z); }
	Point3D operator*(double val) const { return Point3D(x * val, y * val, z * val); }
	Point3D operator/(double val) const { return Point3D(x / val, y / val, z / val); }
	Point3D operator+=(const Point3D & rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
	Point3D operator-=(const Point3D & rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
	Point3D operator*=(double val) { x *= val; y *= val; z *= val; return *this; }
	Point3D operator/=(double val) { x /= val; y /= val; z /= val; return *this; }
};

// Renders a quad at cell (x, y) with dimensions CELL_LENGTH
void renderPixel(int x, int y, float r = 1.0, float g = 1.0, float b = 1.0) {
  // glColor3b(r,g,b);
  glBegin(GL_POINTS);
  glVertex2f(x,y);
  glEnd();
}

void renderLine(int x0, int y0, int x1, int y1) { //Paul's 
    int dx = x1 - x0;
    int dy = y1 - y0;
    
    int steps;
    if (abs((float)dx) > abs((float)dy))
        steps = abs((float)dx);
    else
        steps = abs((float)dy);

    float stepx = static_cast<float>(dx) / steps;
    float stepy = static_cast<float>(dy) / steps;

    float x = x0;
    float y = y0;
    for (int i = 0; i <= steps; ++i) {
        renderPixel((int)(x + 0.5), (int)(y + 0.5));
        x += stepx;
        y += stepy;
    }
}

void renderLine(Point3D p0, Point3D p1) {
   int dx = p1.x - p0.x;
   int dy = p1.y - p0.y;

   int steps;
   if (abs((float)dx) > abs((float)dy))
     steps = abs((float)dx);
   else
     steps = abs((float)dy);

   float stepx = static_cast<float>(dx) / steps;
   float stepy = static_cast<float>(dy) / steps;

   float x = p0.x;
   float y = p0.y;
   for (int i = 0; i <= steps; ++i) {
     renderPixel((int)(x + 0.5), (int)(y + 0.5));
     x += stepx;
     y += stepy;
   }
}

#endif
