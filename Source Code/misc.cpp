#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL\glut.h>
#include "misc.h"	

Image::Image()
{
  height = 0;
  width = 0;
  image = 0;
}

Image::Image(char *fileName)
{
  Load(fileName);
}

void Image::Load(char *fileName)
{
  FILE *fd;
  int  k, nm;
  char c;
  char b[100];
  int red, green, blue;

  int i;

  fd = fopen(fileName, "r");
  if(!fd){
    printf("can't open file:%s\n", fileName);
    exit(0);
  }

  fscanf(fd,"%[^\n] ",b);
  fscanf(fd, "%c",&c);
  while(c == '#'){      
    fscanf(fd, "%[^\n] ", b);
    fscanf(fd, "%c",&c);
  }
  ungetc(c,fd); 
  fscanf(fd, "%d %d %d", &width, &height, &k);

  nm = width * height;
  image = new unsigned char[3*nm];

  for(i=0;i<nm;i++){
    fscanf(fd,"%d %d %d",&red, &green, &blue);
    image[3*nm-3*i-3-3*((width-1)-2*(i%width))]=red;
    image[3*nm-3*i-2-3*((width-1)-2*(i%width))]=green;
    image[3*nm-3*i-1-3*((width-1)-2*(i%width))]=blue;
  }
  fclose(fd);
}



Image::~Image()
{
  if(image != 0)
    delete[] image;
}

//============================================
//===========================================
Texture::Texture(char *fileName)
{
  Load(fileName);
}


unsigned int Texture::Load(char *fileName)
{
  Image image;
  image.Load(fileName);

  if(image.image == 0)
    return 0;
  width = image.width;
  height = image.height;

  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //GL_CLAMP_TO_EDGE);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); //

  glTexImage2D(GL_TEXTURE_2D, 0, 3, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.image);
  return id;
}

