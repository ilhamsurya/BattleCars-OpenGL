/*
 *  Obstacle.cpp
 *  Tanks
 *
 *  Created by Chris Cooper on 09-11-10.
 *
 */

#include "Obstacle.h"
#include "Cutils.h"
#include "Globals.h"
#include "BmpLoader.h"
GLuint _textureBricks;


Obstacle::Obstacle(float positionX, float positionZ, float radius){
	this->posX = positionX;
	this->posZ = positionZ;
	this->radius = radius;
}
GLuint loadTexture2(const char* filename) {
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
void Obstacle::drawSelf(){
	_textureBricks = loadTexture2("bricks.bmp");
	glPushMatrix();

	    glEnable(GL_TEXTURE_2D);
	        glBindTexture(GL_TEXTURE_2D, _textureBricks);
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	        glTranslatef(this->posX, 0.0f, this->posZ);
	     
	        glBegin(GL_QUADS);  // Wall
	            glTexCoord3f(0.0,3.0,0.1);  glVertex3f(-90,10,5);
	            glTexCoord3f(4.0,3.0,0.1);  glVertex3f(90,10,5);
	            glTexCoord3f(4.0,0.0,0.1);  glVertex3f(90,-10.5,5);
	            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-90,-10.5,5);
	        glEnd();
	        glDisable(GL_TEXTURE_2D);
	


	glPopMatrix();
}


float Obstacle::givePosX(){
	return this->posX;
}

float Obstacle::givePosZ(){
	return this->posZ;
}

float Obstacle::giveRadius(){
	return this->radius;
}


