#include "Object3d.h"

#include <glut.h>

#include <iostream>
#include <sstream>
#include <vector>

void Object3d::draw() {
  for (auto& face : faces) {
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    {
      glNormal3d(normals[face[0].z].x, normals[face[0].z].y,
                 normals[face[0].z].z);

      for (auto& vertex : face) {
        glTexCoord2d(UVs[vertex.y].x, UVs[vertex.y].y);
        glVertex3d(vertexes[vertex.x].x, vertexes[vertex.x].y,
                   vertexes[vertex.x].z);
      }
    }
    glEnd();
  }
}


// Стырено отсюда
/////////////////////////////////
#define DATA_OFFSET_OFFSET 0x000A
#define WIDTH_OFFSET 0x0012
#define HEIGHT_OFFSET 0x0016
#define BITS_PER_PIXEL_OFFSET 0x001C
#define HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define NO_COMPRESION 0
#define MAX_NUMBER_OF_COLORS 0
#define ALL_COLORS_REQUIRED 0
#pragma warning(disable : 4996)

typedef unsigned int int32;
typedef short int16;
typedef unsigned char byte;

void ReadImage(const char* fileName, byte** pixels, int32* width, int32* height,
               int32* bytesPerPixel) {
  FILE* imageFile = fopen(fileName, "rb");

  if (imageFile == nullptr) {
    *pixels = nullptr;
    return;
  }

  int32 dataOffset;
  fseek(imageFile, DATA_OFFSET_OFFSET, SEEK_SET);
  fread(&dataOffset, 4, 1, imageFile);
  fseek(imageFile, WIDTH_OFFSET, SEEK_SET);
  fread(width, 4, 1, imageFile);
  fseek(imageFile, HEIGHT_OFFSET, SEEK_SET);
  fread(height, 4, 1, imageFile);
  int16 bitsPerPixel;
  fseek(imageFile, BITS_PER_PIXEL_OFFSET, SEEK_SET);
  fread(&bitsPerPixel, 2, 1, imageFile);
  *bytesPerPixel = ((int32)bitsPerPixel) / 8;

  int paddedRowSize =
      (int)(4 * ceil((float)(*width) / 4.0f)) * (*bytesPerPixel);
  int unpaddedRowSize = (*width) * (*bytesPerPixel);
  int totalSize = unpaddedRowSize * (*height);
  *pixels = (byte*)malloc(totalSize);
  int i = 0;
  byte* currentRowPointer = *pixels + ((*height - 1) * unpaddedRowSize);
  for (i = 0; i < *height; i++) {
    fseek(imageFile, dataOffset + (i * paddedRowSize), SEEK_SET);
    fread(currentRowPointer, 1, unpaddedRowSize, imageFile);
    currentRowPointer -= unpaddedRowSize;
  }

  fclose(imageFile);

  for (size_t i = 0; i < totalSize; i += 3) {
    byte tmp = (*pixels)[i];
    (*pixels)[i] = (*pixels)[i + 2];
    (*pixels)[i + 2] = tmp;
  }
}
/////////////////////////////////


void Object3d::loadOBJ(std::string file_name) {
  std::ifstream file(file_name);

  file.seekg(0, file.beg);
  std::string str;
  while (file >> str) {
    if (str == "v") {
      Vector3d pos;
      file >> pos.x >> pos.y >> pos.z;
      vertexes.push_back(pos);
    } else if (str == "vt") {
      Vector2d pos;
      file >> pos.x >> pos.y;
      UVs.push_back(pos);
    } else if (str == "vn") {
      Vector3d norm;
      file >> norm.x >> norm.y >> norm.z;
      normals.push_back(norm);
    } else if (str == "f") {
      int v, vt, vn;
      faces.push_back({});
      std::getline(file, str);
      std::stringstream stream(str);
      while (!stream.eof()) {
        stream >> v;
        stream.get();
        stream >> vt;
        stream.get();
        stream >> vn;
        faces.back().push_back({v - 1, vt - 1, vn - 1});
      };
    }
  }
}

Object3d::Object3d(std::string file_name) {
  std::string obj = ".obj";
  std::string bmp = ".bmp";

  loadOBJ(file_name + obj);
  int32 w, h;

  std::string name(file_name + bmp);

  unsigned char* data;
  int32 bpp;
  ReadImage(name.data(), &data, &w, &h, &bpp);

  glGenTextures(1, texture);

  glBindTexture(GL_TEXTURE_2D, texture[0]);

  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, data);

  delete data;
}

Object3d::~Object3d() {}
