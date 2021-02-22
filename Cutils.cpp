/*
 *  Cutils.cpp
 *  Tanks
 *
 *  Created by Chris Cooper on 09-11-04.
 * 
 *
 */

#include "Cutils.h"
#include "Globals.h"
#include "BmpLoader.h"
GLuint _textureGrass,_textureSky;
float _angle = 0.0;

void makeCube(float size){
	float len = 0.5f*size;
	makeRectangularPrism(-len, -len, -len, len, len, len);
}

void makeReferenceCubes(float size, float cubeSize){
	
	
	glColor3f(1.0f, 8.0f, 1.0f);
	
	glPushMatrix();
	
	glTranslatef(size, size, size);
	makeCube(cubeSize);
	
	glTranslatef(-2*size, 0.0f, 0.0f);
	makeCube(cubeSize);
	
	glTranslatef(0.0f, 0.0f, -2*size);
	makeCube(cubeSize);
	
	glTranslatef(2*size, 0.0f, 0.0f);
	makeCube(cubeSize);
	
	glTranslatef(0.0f, -2*size, 0.0f);
	makeCube(cubeSize);
	
	glTranslatef(-2*size, 0.0f, 0.0f);
	makeCube(cubeSize);
	
	glTranslatef(0.0f, 0.0f, 2*size);
	makeCube(cubeSize);
	
	glTranslatef(2*size, 0.0f, 0.0f);
	makeCube(cubeSize);
	
	glPopMatrix();
}

void makeRectangularPrism(float x1, float y1, float z1, float x2, float y2, float z2){
	float width = (x2-x1)/2;
	if (width < 1){
		width = -width;
	}
	float height = (y2-y1)/2;
	if (height < 1){
		height = -height;
	} 
	float depth = (z2-z1)/2;
	if (depth < 1){
		depth = -depth;
	}
	
	glBegin(GL_QUADS);
	//Front
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-width, -height, depth);
	glVertex3f(width, -height, depth);
	glVertex3f(width, height, depth);
	glVertex3f(-width, height, depth);
	
	//Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(width, -height, -depth);
	glVertex3f(width, height, -depth);
	glVertex3f(width, height, depth);
	glVertex3f(width, -height, depth);
	
	//Back
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-width, -height, -depth);
	glVertex3f(-width, height, -depth);
	glVertex3f(width, height, -depth);
	glVertex3f(width, -height, -depth);
	
	//Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-width, -height, -depth);
	glVertex3f(-width, -height, depth);
	glVertex3f(-width, height, depth);
	glVertex3f(-width, height, -depth);
	
	//Top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-width, height, -depth);
	glVertex3f(-width, height, depth);
	glVertex3f(width, height, depth);
	glVertex3f(width, height, -depth);
	
	//Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-width, -height, -depth);
	glVertex3f(-width, -height, depth);
	glVertex3f(width, -height, depth);
	glVertex3f(width, -height, -depth);
	
	glEnd();
}

void normalize(float v[3])
{    
	GLfloat d = sqrt(v[1]*v[1]+v[2]*v[2]+v[3]*v[3]); 
	if (d == 0.0) {
		std::cout << "Error: Zero vector passed to function \"void normalize(float v[3])\"";
		return;
	}
	v[1] /= d;
	v[2] /= d;
	v[3] /= d; 
}

void normalizedCrossProduct(float v1[3], float v2[3], float out[3]) 
{ 	
	out[0] = v1[1]*v2[2] - v1[2]*v2[1];
	out[1] = v1[2]*v2[0] - v1[0]*v2[2];
	out[2] = v1[0]*v2[1] - v1[1]*v2[0];
	normalize(out); 
}

GLuint loadTexture(const char* filename) {
	BmpLoader bl(filename);	
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,
				 bl.iWidth, bl.iHeight,
				 0,
				 GL_RGB,
				 GL_UNSIGNED_BYTE,
				 bl.textureData);
	return textureId;
}

void makeGrid(float size){
	_textureGrass = loadTexture("grass.bmp");
	_textureSky = loadTexture("sky.bmp");
	// Sky
    glPushMatrix();
    	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureSky);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS); //Belakang
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-100,100,-100);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-100,-100,-100);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(100,-100,-100);
            glTexCoord3f(0.0,1.0,0);  glVertex3f(100,100,-100);
        glEnd();
        glBegin(GL_QUADS); //Depan
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-100,100,100);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-100,-100,100);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(100,-100,100);
            glTexCoord3f(0.0,1.0,0);  glVertex3f(100,100,100);
        glEnd();
        glBegin(GL_QUADS); //Kanan
            glTexCoord3f(1.0,1.0,0);  glVertex3f(100,100,-100);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(100,-100,-100);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(100,-100,100);
            glTexCoord3f(0.0,1.0,0);  glVertex3f(100,100,100);
        glEnd();
        glBegin(GL_QUADS); //Kiri
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-100,100,-100);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-100,-100,-100);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(-100,-100,100);
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-100,100,100);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
	
    // Grass
    glPushMatrix();
    	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureGrass );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);
    
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,70.0,1);  glVertex3f(-70,0,70);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(-70,0,-70);
            glTexCoord3f(70.0,0.0,1);  glVertex3f(70,0,-70);
            glTexCoord3f(70.0,70.0,1);  glVertex3f(70,0,70);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

float distanceBetween(float x1, float z1, float x2, float z2){
	return sqrt((x2-x1)*(x2-x1) + (z2-z1)*(z2-z1));
}
