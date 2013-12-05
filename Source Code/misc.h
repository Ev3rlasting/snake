#pragma once

class Texture
{
 public:
  unsigned int id;
  int height;
  int width;
  
  Texture(){};
  Texture(char *fileName);
  unsigned int Load(char *fileName);
  ~Texture(){};

};


class Image
{
 public:
  int width;
  int height;
  unsigned char *image;

  Image();
  Image( char *fileName);

  void Load( char *fileName);
  ~Image();

};
