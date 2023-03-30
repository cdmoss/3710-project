#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>

// Colours
GLfloat tableTopColour[3] = {0.3, 0.0, 0.1};
GLfloat tableLegColour[3] = {0.2, 0.0, 0.1};
GLfloat roomCarpetColour[3] = {0.2, 0.3, 0.5};
GLfloat roomWallColour[3] = {0.7, 0.6, 0.6};

// ROOMS COORDS
// Floor
GLfloat roomFloorNorthEast[3] = {10, 10, 0};
GLfloat roomFloorSouthEast[3] = {10, -10, 0};
GLfloat roomFloorSouthWest[3] = {-10, -10, 0};
GLfloat roomFloorNorthWest[3] = {-10, 10, 0};
// Roof
GLfloat roomRoofNorthEast[3] = {10, 10, 12};
GLfloat roomRoofSouthEast[3] = {10, -10, 12};
GLfloat roomRoofSouthWest[3] = {-10, -10, 12};
GLfloat roomRoofNorthWest[3] = {-10, 10, 12};
// Window?

// TABLE COORDS

// Coordinates for north east leg
// Coords at floor of the leg
GLdouble legNorthEastFloorTopRight[3] = {5, 5, 0.1};
GLdouble legNorthEastFloorBottomRight[3] = {5, 4.5, 0.1};
GLdouble legNorthEastFloorBottomLeft[3] = {4.5, 4.5, 0.1};
GLdouble legNorthEastFloorTopLeft[3] = {4.5, 5, 0.1};
// Coords at the top of the leg
GLdouble legNorthEastTableTopRight[3] = {5, 5, 5};
GLdouble legNorthEastTableBottomRight[3] = {5, 4.5, 5};
GLdouble legNorthEastTableBottomLeft[3] = {4.5, 4.5, 5};
GLdouble legNorthEastTableTopLeft[3] = {4.5, 5, 5};

// Coordinates for south east leg
// Coords at floor of the leg
GLdouble legSouthEastFloorTopRight[3] = {5, -5, 0.1};
GLdouble legSouthEastFloorBottomRight[3] = {5, -5, 0.1};
GLdouble legSouthEastFloorBottomLeft[3] = {4.5, -5, 0.1};
GLdouble legSouthEastFloorTopLeft[3] = {4.5, -5, 0.1};
// Coords at the top of the leg
GLdouble legSouthEastTableTopRight[3] = {5, -5, 5};
GLdouble legSouthEastTableBottomRight[3] = {5, -4.5, 5};
GLdouble legSouthEastTableBottomLeft[3] = {4.5, -4.5, 5};
GLdouble legSouthEastTableTopLeft[3] = {4.5, -5, 5};

// Coordinates for south west leg
// Coords at floor of the leg
GLdouble legSouthWestFloorTopRight[3] = {-5, -5, 0.1};
GLdouble legSouthWestFloorBottomRight[3] = {-5, -4.5, 0.1};
GLdouble legSouthWestFloorBottomLeft[3] = {-4.5, -4.5, 0.1};
GLdouble legSouthWestFloorTopLeft[3] = {-4.5, -5, 0.1};
// Coords at the top of the leg
GLdouble legSouthWestTableTopRight[3] = {-5, -5, 5};
GLdouble legSouthWestTableBottomRight[3] = {-5, -4.5, 5};
GLdouble legSouthWestTableBottomLeft[3] = {-4.5, -4.5, 5};
GLdouble legSouthWestTableTopLeft[3] = {-4.5, -5, 5};

// Coordinates for north west leg
// Coords at floor of the leg
GLdouble legNorthWestFloorTopRight[3] = {-5, 5, 0.1};
GLdouble legNorthWestFloorBottomRight[3] = {-5, 4.5, 0.1};
GLdouble legNorthWestFloorBottomLeft[3] = {-4.5, 4.5, 0.1};
GLdouble legNorthWestFloorTopLeft[3] = {-4.5, 5, 0.1};
// Coords at the top of the leg
GLdouble legNorthWestTableTopRight[3] = {-5, 5, 5};
GLdouble legNorthWestTableBottomRight[3] = {-5, 4.5, 5};
GLdouble legNorthWestTableBottomLeft[3] = {-4.5, 4.5, 5};
GLdouble legNorthWestTableTopLeft[3] = {-4.5, 5, 5};

// COORDS FOR TABLETOP
// Top of table
GLdouble tableTopNorthEast[3] = {5, 5, 5};
GLdouble tableTopSouthEast[3] = {5, -5, 5};
GLdouble tableTopSouthWest[3] = {-5, -5, 5};
GLdouble tableTopNorthWest[3] = {-5, 5, 5};
// Bottom of table
GLdouble tableBottomNorthEast[3] = {5, 5, 5};
GLdouble tableBottomSouthEast[3] = {5, -5, 5};
GLdouble tableBottomSouthWest[3] = {-5, -5, 5};
GLdouble tableBottomNorthWest[3] = {-5, 5, 5};

struct Vertex {
    float x, y, z;
};

struct Face {
    unsigned int a, b, c;
};

std::vector<Vertex> vertices;
std::vector<Face> faces;

const int ORTHO_BOUNDS = 15;
bool foundVerticies = false;
float maxX = -INFINITY;
float maxY = -INFINITY;
float maxZ = -INFINITY;
float minX = INFINITY;
float minY = INFINITY;
float minZ = INFINITY;

// Store Terry's center
int terryCenterX = 0;
int terryCenterY = 0;

// Set Terry's position
float terryShift = 0.0;
float terryRotate = 0.0;

// Store camera position
float cameraPosY = -5.0f;

void drawRoomFloor() {
  glColor3f(roomCarpetColour[0], roomCarpetColour[1], roomCarpetColour[2]);
  glBegin(GL_POLYGON);
  glVertex3f(roomFloorNorthEast[0], roomFloorNorthEast[1],
             roomFloorNorthEast[2]);
  glVertex3f(roomFloorNorthWest[0], roomFloorNorthWest[1],
             roomFloorNorthWest[2]);
  glVertex3f(roomFloorSouthWest[0], roomFloorSouthWest[1],
             roomFloorSouthWest[2]);
  glVertex3f(roomFloorSouthEast[0], roomFloorSouthEast[1],
             roomFloorSouthEast[2]);
  glEnd();
  glFlush();
}

void drawRoomNorthWall() {
  glColor3f(roomWallColour[0], roomWallColour[1], roomWallColour[2]);
  glBegin(GL_POLYGON);
  glVertex3f(roomFloorNorthEast[0], roomFloorNorthEast[1],
             roomFloorNorthEast[2]);
  glVertex3f(roomFloorNorthWest[0], roomFloorNorthWest[1],
             roomFloorNorthWest[2]);
  glVertex3f(roomRoofNorthWest[0], roomRoofNorthWest[1], roomRoofNorthWest[2]);
  glVertex3f(roomRoofNorthEast[0], roomRoofNorthEast[1], roomRoofNorthEast[2]);
  glEnd();
  glFlush();
}

void drawRoomEastWall() {
  glColor3f(roomWallColour[0], roomWallColour[1], roomWallColour[2]);
  glBegin(GL_POLYGON);
  glVertex3f(roomFloorNorthEast[0], roomFloorNorthEast[1],
             roomFloorNorthEast[2]);
  glVertex3f(roomFloorSouthEast[0], roomFloorSouthEast[1],
             roomFloorSouthEast[2]);
  glVertex3f(roomRoofSouthEast[0], roomRoofSouthEast[1], roomRoofSouthEast[2]);
  glVertex3f(roomRoofNorthEast[0], roomRoofNorthEast[1], roomRoofNorthEast[2]);
  glEnd();
  glFlush();
}

void drawRoomSouthWall() {
  glColor3f(roomWallColour[0], roomWallColour[1], roomWallColour[2]);
  glBegin(GL_POLYGON);
  glVertex3f(roomFloorSouthEast[0], roomFloorSouthEast[1],
             roomFloorSouthEast[2]);
  glVertex3f(roomFloorSouthWest[0], roomFloorSouthWest[1],
             roomFloorSouthWest[2]);
  glVertex3f(roomRoofSouthWest[0], roomRoofSouthWest[1], roomRoofSouthWest[2]);
  glVertex3f(roomRoofSouthEast[0], roomRoofSouthEast[1], roomRoofSouthEast[2]);
  glEnd();
  glFlush();
}

void drawRoomWestWall() {
  glColor3f(roomWallColour[0], roomWallColour[1], roomWallColour[2]);
  glBegin(GL_POLYGON);
  glVertex3f(roomFloorSouthWest[0], roomFloorSouthWest[1],
             roomFloorSouthWest[2]);
  glVertex3f(roomFloorNorthWest[0], roomFloorNorthWest[1],
             roomFloorNorthWest[2]);
  glVertex3f(roomRoofNorthWest[0], roomRoofNorthWest[1], roomRoofNorthWest[2]);
  glVertex3f(roomRoofSouthWest[0], roomRoofSouthWest[1], roomRoofSouthWest[2]);
  glEnd();
  glFlush();
}

void drawLegNorthEast() {
  // Draw base of leg
  glColor3f(tableLegColour[0], tableLegColour[1], tableLegColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(legNorthEastFloorTopRight[0], legNorthEastFloorTopRight[1],
             legNorthEastFloorTopRight[2]);
  glVertex3f(legNorthEastFloorTopLeft[0], legNorthEastFloorTopLeft[1],
             legNorthEastFloorTopLeft[2]);
  glVertex3f(legNorthEastFloorBottomLeft[0], legNorthEastFloorBottomLeft[1],
             legNorthEastFloorBottomLeft[2]);
  glVertex3f(legNorthEastFloorBottomRight[0], legNorthEastFloorBottomRight[1],
             legNorthEastFloorBottomRight[2]);
  glEnd();
  glFlush();
  // Draw north facing side
  glColor3f(tableLegColour[0], tableLegColour[1], tableLegColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(legNorthEastFloorTopRight[0], legNorthEastFloorTopRight[1],
             legNorthEastFloorTopRight[2]);
  glVertex3f(legNorthEastTableTopLeft[0], legNorthEastTableTopLeft[1],
             legNorthEastTableTopLeft[2]);
  glVertex3f(legNorthEastTableTopRight[0], legNorthEastTableTopRight[1],
             legNorthEastTableTopRight[2]);
  glVertex3f(legNorthEastFloorTopLeft[0], legNorthEastFloorTopLeft[1],
             legNorthEastFloorTopLeft[2]);
  glEnd();
  glFlush();
  // Draw west facing side
  glColor3f(tableLegColour[0], tableLegColour[1], tableLegColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(legNorthEastFloorTopLeft[0], legNorthEastFloorTopLeft[1],
             legNorthEastFloorTopLeft[2]);
  glVertex3f(legNorthEastFloorBottomLeft[0], legNorthEastFloorBottomLeft[1],
             legNorthEastFloorBottomLeft[2]);
  glVertex3f(legNorthEastTableBottomLeft[0], legNorthEastTableBottomLeft[1],
             legNorthEastTableBottomLeft[2]);
  glVertex3f(legNorthEastTableTopLeft[0], legNorthEastTableTopLeft[1],
             legNorthEastTableTopLeft[2]);
  glEnd();
  glFlush();
  // Draw east facing side
  glColor3f(tableLegColour[0], tableLegColour[1], tableLegColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(legNorthEastFloorTopRight[0], legNorthEastFloorTopRight[1],
             legNorthEastFloorTopRight[2]);
  glVertex3f(legNorthEastFloorBottomRight[0], legNorthEastFloorBottomRight[1],
             legNorthEastFloorBottomRight[2]);
  glVertex3f(legNorthEastTableBottomRight[0], legNorthEastTableBottomRight[1],
             legNorthEastTableBottomRight[2]);
  glVertex3f(legNorthEastTableTopRight[0], legNorthEastTableTopRight[1],
             legNorthEastTableTopRight[2]);
  glEnd();
  glFlush();
  // Draw south facing side
  glColor3f(tableLegColour[0], tableLegColour[1], tableLegColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(legNorthEastFloorBottomRight[0], legNorthEastFloorBottomRight[1],
             legNorthEastFloorBottomRight[2]);
  glVertex3f(legNorthEastFloorBottomLeft[0], legNorthEastFloorBottomLeft[1],
             legNorthEastFloorBottomLeft[2]);
  glVertex3f(legNorthEastTableBottomLeft[0], legNorthEastTableBottomLeft[1],
             legNorthEastTableBottomLeft[2]);
  glVertex3f(legNorthEastTableBottomRight[0], legNorthEastTableBottomRight[1],
             legNorthEastTableBottomRight[2]);
  glEnd();
  glFlush();
}

void drawLegSouthEast() {
  // Draw base of leg
  glColor3f(tableLegColour[0], tableLegColour[1], tableLegColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(legSouthEastFloorTopRight[0], legSouthEastFloorTopRight[1],
             legSouthEastFloorTopRight[2]);
  glVertex3f(legSouthEastFloorTopLeft[0], legSouthEastFloorTopLeft[1],
             legSouthEastFloorTopLeft[2]);
  glVertex3f(legSouthEastFloorBottomLeft[0], legSouthEastFloorBottomLeft[1],
             legSouthEastFloorBottomLeft[2]);
  glVertex3f(legSouthEastFloorBottomRight[0], legSouthEastFloorBottomRight[1],
             legSouthEastFloorBottomRight[2]);
  glEnd();
  glFlush();
  // Draw north facing side
  glColor3f(tableLegColour[0], tableLegColour[1], tableLegColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(legSouthEastFloorTopRight[0], legSouthEastFloorTopRight[1],
             legSouthEastFloorTopRight[2]);
  glVertex3f(legSouthEastTableTopLeft[0], legSouthEastTableTopLeft[1],
             legSouthEastTableTopLeft[2]);
  glVertex3f(legSouthEastTableTopRight[0], legSouthEastTableTopRight[1],
             legSouthEastTableTopRight[2]);
  glVertex3f(legSouthEastFloorTopLeft[0], legSouthEastFloorTopLeft[1],
             legSouthEastFloorTopLeft[2]);
  glEnd();
  glFlush();
  // Draw west facing side
  glColor3f(tableLegColour[0], tableLegColour[1], tableLegColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(legSouthEastFloorTopLeft[0], legSouthEastFloorTopLeft[1],
             legSouthEastFloorTopLeft[2]);
  glVertex3f(legSouthEastFloorBottomLeft[0], legSouthEastFloorBottomLeft[1],
             legSouthEastFloorBottomLeft[2]);
  glVertex3f(legSouthEastTableBottomLeft[0], legSouthEastTableBottomLeft[1],
             legSouthEastTableBottomLeft[2]);
  glVertex3f(legSouthEastTableTopLeft[0], legSouthEastTableTopLeft[1],
             legSouthEastTableTopLeft[2]);
  glEnd();
  glFlush();
  // Draw east facing side
  glColor3f(tableLegColour[0], tableLegColour[1], tableLegColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(legSouthEastFloorTopRight[0], legSouthEastFloorTopRight[1],
             legSouthEastFloorTopRight[2]);
  glVertex3f(legSouthEastFloorBottomRight[0], legSouthEastFloorBottomRight[1],
             legSouthEastFloorBottomRight[2]);
  glVertex3f(legSouthEastTableBottomRight[0], legSouthEastTableBottomRight[1],
             legSouthEastTableBottomRight[2]);
  glVertex3f(legSouthEastTableTopRight[0], legSouthEastTableTopRight[1],
             legSouthEastTableTopRight[2]);
  glEnd();
  glFlush();
  // Draw south facing side
  glColor3f(tableLegColour[0], tableLegColour[1], tableLegColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(legSouthEastFloorBottomRight[0], legSouthEastFloorBottomRight[1],
             legSouthEastFloorBottomRight[2]);
  glVertex3f(legSouthEastFloorBottomLeft[0], legSouthEastFloorBottomLeft[1],
             legSouthEastFloorBottomLeft[2]);
  glVertex3f(legSouthEastTableBottomLeft[0], legSouthEastTableBottomLeft[1],
             legSouthEastTableBottomLeft[2]);
  glVertex3f(legSouthEastTableBottomRight[0], legSouthEastTableBottomRight[1],
             legSouthEastTableBottomRight[2]);
  glEnd();
  glFlush();
}

void drawLegSouthWest() {
  // Draw base of leg
  glColor3f(tableLegColour[0], tableLegColour[1], tableLegColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(legSouthWestFloorTopRight[0], legSouthWestFloorTopRight[1],
             legSouthWestFloorTopRight[2]);
  glVertex3f(legSouthWestFloorTopLeft[0], legSouthWestFloorTopLeft[1],
             legSouthWestFloorTopLeft[2]);
  glVertex3f(legSouthWestFloorBottomLeft[0], legSouthWestFloorBottomLeft[1],
             legSouthWestFloorBottomLeft[2]);
  glVertex3f(legSouthWestFloorBottomRight[0], legSouthWestFloorBottomRight[1],
             legSouthWestFloorBottomRight[2]);
  glEnd();
  glFlush();
  // Draw north facing side
  glColor3f(tableLegColour[0], tableLegColour[1], tableLegColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(legSouthWestFloorTopRight[0], legSouthWestFloorTopRight[1],
             legSouthWestFloorTopRight[2]);
  glVertex3f(legSouthWestTableTopLeft[0], legSouthWestTableTopLeft[1],
             legSouthWestTableTopLeft[2]);
  glVertex3f(legSouthWestTableTopRight[0], legSouthWestTableTopRight[1],
             legSouthWestTableTopRight[2]);
  glVertex3f(legSouthWestFloorTopLeft[0], legSouthWestFloorTopLeft[1],
             legSouthWestFloorTopLeft[2]);
  glEnd();
  glFlush();
  // Draw east facing side
  glColor3f(tableLegColour[0], tableLegColour[1], tableLegColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(legSouthWestFloorTopRight[0], legSouthWestFloorTopRight[1],
             legSouthWestFloorTopRight[2]);
  glVertex3f(legSouthWestFloorBottomRight[0], legSouthWestFloorBottomRight[1],
             legSouthWestFloorBottomRight[2]);
  glVertex3f(legSouthWestTableBottomRight[0], legSouthWestTableBottomRight[1],
             legSouthWestTableBottomRight[2]);
  glVertex3f(legSouthWestTableTopRight[0], legSouthWestTableTopRight[1],
             legSouthWestTableTopRight[2]);
  glEnd();
  glFlush();
  // Draw West facing side
  glColor3f(tableLegColour[0], tableLegColour[1], tableLegColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(legSouthWestFloorTopLeft[0], legSouthWestFloorTopLeft[1],
             legSouthWestFloorTopLeft[2]);
  glVertex3f(legSouthWestFloorBottomLeft[0], legSouthWestFloorBottomLeft[1],
             legSouthWestFloorBottomLeft[2]);
  glVertex3f(legSouthWestTableBottomLeft[0], legSouthWestTableBottomLeft[1],
             legSouthWestTableBottomLeft[2]);
  glVertex3f(legSouthWestTableTopLeft[0], legSouthWestTableTopLeft[1],
             legSouthWestTableTopLeft[2]);
  glEnd();
  glFlush();
  // Draw south facing side
  glColor3f(tableLegColour[0], tableLegColour[1], tableLegColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(legSouthWestFloorBottomRight[0], legSouthWestFloorBottomRight[1],
             legSouthWestFloorBottomRight[2]);
  glVertex3f(legSouthWestFloorBottomLeft[0], legSouthWestFloorBottomLeft[1],
             legSouthWestFloorBottomLeft[2]);
  glVertex3f(legSouthWestTableBottomLeft[0], legSouthWestTableBottomLeft[1],
             legSouthWestTableBottomLeft[2]);
  glVertex3f(legSouthWestTableBottomRight[0], legSouthWestTableBottomRight[1],
             legSouthWestTableBottomRight[2]);
  glEnd();
  glFlush();
}

void drawLegNorthWest() {
  // Draw base of leg
  glColor3f(tableLegColour[0], tableLegColour[1], tableLegColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(legNorthWestFloorTopRight[0], legNorthWestFloorTopRight[1],
             legNorthWestFloorTopRight[2]);
  glVertex3f(legNorthWestFloorTopLeft[0], legNorthWestFloorTopLeft[1],
             legNorthWestFloorTopLeft[2]);
  glVertex3f(legNorthWestFloorBottomLeft[0], legNorthWestFloorBottomLeft[1],
             legNorthWestFloorBottomLeft[2]);
  glVertex3f(legNorthWestFloorBottomRight[0], legNorthWestFloorBottomRight[1],
             legNorthWestFloorBottomRight[2]);
  glEnd();
  glFlush();
  // Draw north facing side
  glColor3f(tableLegColour[0], tableLegColour[1], tableLegColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(legNorthWestFloorTopRight[0], legNorthWestFloorTopRight[1],
             legNorthWestFloorTopRight[2]);
  glVertex3f(legNorthWestTableTopLeft[0], legNorthWestTableTopLeft[1],
             legNorthWestTableTopLeft[2]);
  glVertex3f(legNorthWestTableTopRight[0], legNorthWestTableTopRight[1],
             legNorthWestTableTopRight[2]);
  glVertex3f(legNorthWestFloorTopLeft[0], legNorthWestFloorTopLeft[1],
             legNorthWestFloorTopLeft[2]);
  glEnd();
  glFlush();
  // Draw east facing side
  glColor3f(tableLegColour[0], tableLegColour[1], tableLegColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(legNorthWestFloorTopRight[0], legNorthWestFloorTopRight[1],
             legNorthWestFloorTopRight[2]);
  glVertex3f(legNorthWestFloorBottomRight[0], legNorthWestFloorBottomRight[1],
             legNorthWestFloorBottomRight[2]);
  glVertex3f(legNorthWestTableBottomRight[0], legNorthWestTableBottomRight[1],
             legNorthWestTableBottomRight[2]);
  glVertex3f(legNorthWestTableTopRight[0], legNorthWestTableTopRight[1],
             legNorthWestTableTopRight[2]);
  glEnd();
  glFlush();
  // Draw West facing side
  glColor3f(tableLegColour[0], tableLegColour[1], tableLegColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(legNorthWestFloorTopLeft[0], legNorthWestFloorTopLeft[1],
             legNorthWestFloorTopLeft[2]);
  glVertex3f(legNorthWestFloorBottomLeft[0], legNorthWestFloorBottomLeft[1],
             legNorthWestFloorBottomLeft[2]);
  glVertex3f(legNorthWestTableBottomLeft[0], legNorthWestTableBottomLeft[1],
             legNorthWestTableBottomLeft[2]);
  glVertex3f(legNorthWestTableTopLeft[0], legNorthWestTableTopLeft[1],
             legNorthWestTableTopLeft[2]);
  glEnd();
  glFlush();
  // Draw North facing side
  glColor3f(tableLegColour[0], tableLegColour[1], tableLegColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(legNorthWestFloorBottomRight[0], legNorthWestFloorBottomRight[1],
             legNorthWestFloorBottomRight[2]);
  glVertex3f(legNorthWestFloorBottomLeft[0], legNorthWestFloorBottomLeft[1],
             legNorthWestFloorBottomLeft[2]);
  glVertex3f(legNorthWestTableBottomLeft[0], legNorthWestTableBottomLeft[1],
             legNorthWestTableBottomLeft[2]);
  glVertex3f(legNorthWestTableBottomRight[0], legNorthWestTableBottomRight[1],
             legNorthWestTableBottomRight[2]);
  glEnd();
  glFlush();
}

void drawTableSurfaces() {
  // Draw top of table
  glColor3f(tableTopColour[0], tableTopColour[1], tableTopColour[2]);
  glBegin(GL_QUADS);
  glVertex3f(tableTopNorthEast[0], tableTopNorthEast[1], tableTopNorthEast[2]);
  glVertex3f(tableTopNorthWest[0], tableTopNorthWest[1], tableTopNorthWest[2]);
  glVertex3f(tableTopSouthWest[0], tableTopSouthWest[1], tableTopSouthWest[2]);
  glVertex3f(tableTopSouthEast[0], tableTopSouthEast[1], tableTopSouthEast[2]);
  glEnd();
  glFlush();
}

void drawRoomAndTable() {
  drawRoomFloor();

  std::cout << "Camera position: " << cameraPosY << std::endl;

  drawRoomWestWall();
  drawRoomEastWall();

  if (cameraPosY < 0) {
    drawRoomNorthWall();
  } else {
    drawRoomSouthWall();
  }

  drawLegNorthEast();
  drawLegSouthEast();
  drawLegSouthWest();
  drawLegNorthWest();
  drawTableSurfaces();
}


bool loadBinaryFile(const char* filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return false;
    }

    size_t vertices_size, faces_size;
    in.read(reinterpret_cast<char*>(&vertices_size), sizeof(vertices_size));
    in.read(reinterpret_cast<char*>(&faces_size), sizeof(faces_size));

    vertices.resize(vertices_size);
    faces.resize(faces_size);

    in.read(reinterpret_cast<char*>(vertices.data()), vertices_size * sizeof(Vertex));
    in.read(reinterpret_cast<char*>(faces.data()), faces_size * sizeof(Face));

    in.close();
    return true;
}

void getTerryCenter() {
    for (const Face &face : faces) {
        unsigned int indices[] = {face.a, face.b, face.c};
        for (unsigned int i = 0; i < 3; i++) {
            const Vertex &position = vertices[indices[i]];
            if (position.x > maxX) {
                maxX = position.x;
            }
            if (position.y > maxY) {
                maxY = position.y;
            }
            if (position.z > maxZ) {
                maxZ = position.z;
            }
            if (position.x < minX) {
                minX = position.x;
            }
            if (position.y < minY) {
                minY = position.y;
            }
            if (position.z < minZ) {
                minZ = position.z;
            }
        }
    }

    terryCenterX = (maxX + minX) / 2;
    terryCenterY = (maxY + minY) / 2;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_CULL_FACE);
    gluLookAt(0.5f, cameraPosY, 6.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(.1f, .1f, 0.1f);

    glPushMatrix();
    float scale = 0.05f;
    glScalef(scale, scale, scale);
    glRotatef(terryRotate, 0.0f, 0.0f, 1.0f);
    glTranslatef(-terryCenterX, -terryCenterY + terryShift, 100.0f);

    for (const Face &face : faces) {
        glBegin(GL_POLYGON);
        unsigned int indices[] = {face.a, face.b, face.c};
        for (unsigned int i = 0; i < 3; i++) {
            const Vertex &position = vertices[indices[i]];
            glVertex3f(position.x, position.y, position.z);
        }
        glEnd();
    }


    glPopMatrix();

    drawRoomAndTable();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {  // taken from slides
  switch (key) {
    case 27:  // Escape to quit
      exit(0);
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

void specialKeys(int key, int x,
                 int y) {  // allows for us to use up/down to scale
  switch (key) {
      // scales sizes up when up arrow key is pressed
    case GLUT_KEY_UP:
      if (terryShift < 50.0f) terryShift += 2;
      break;
      // scales sizes down when down arrow key is pressed
    case GLUT_KEY_DOWN:
      if (terryShift > -50.0f) terryShift -= 2;
      break;
    case GLUT_KEY_LEFT:  // rotates around the x axis by 1
      terryRotate -= 90;
      break;
    case GLUT_KEY_RIGHT:  // rotates around the y axis by 1
      terryRotate += 90;
      break;
    case GLUT_KEY_F1:  // reset scale, rotation, shift
      cameraPosY = -5.0;
      break;
    case GLUT_KEY_F2:
      cameraPosY = 5.0;
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

void init() {  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-ORTHO_BOUNDS, ORTHO_BOUNDS, -ORTHO_BOUNDS, ORTHO_BOUNDS, -10, 200);
}

int main(int argc, char** argv) {
  bool success = loadBinaryFile("terry.bin");

  if (!success) {
    std::cerr << "Error loading terry data" << std::endl;
    return 1;
  }

  getTerryCenter();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("T E R R Y");
  init();

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeys);

  glutMainLoop();

  return 0;
}
