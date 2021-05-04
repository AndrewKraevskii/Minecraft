#include "model3d.h"

#include <glut.h>

#include <iostream>
#include <sstream>
#include <vector>

#include "lodepng.h"

void Model3d::draw() {
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

#pragma warning(disable : 4996)

typedef unsigned char byte;

static void ReadBMP(const char* fileName, byte** pixels, uint32_t* width,
                    uint32_t* height, uint32_t* bytesPerPixel) {
  FILE* imageFile = fopen(fileName, "rb");

  if (imageFile == nullptr) {
    *pixels = nullptr;
    return;
  }

  uint32_t dataOffset;
  fseek(imageFile, 0x000A, SEEK_SET);
  fread(&dataOffset, 4, 1, imageFile);
  fseek(imageFile, 0x0012, SEEK_SET);
  fread(width, 4, 1, imageFile);
  fseek(imageFile, 0x0016, SEEK_SET);
  fread(height, 4, 1, imageFile);
  int16_t bitsPerPixel;
  fseek(imageFile, 0x001C, SEEK_SET);
  fread(&bitsPerPixel, 2, 1, imageFile);
  *bytesPerPixel = ((uint32_t)bitsPerPixel) / 8;

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

void Model3d::loadOBJ(std::string file_name) {
  std::ifstream file(file_name);
  vertexes.clear();
  UVs.clear();
  normals.clear();
  faces.clear();
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

Model3d::Model3d(std::string file_name) { loadOBJ(file_name); }

static std::string tolower(std::string str) {
  std::string lowstr;
  for (auto& x : str) {
    lowstr += tolower(x);
  }
  return lowstr;
}

Model3d::Model3d(std::string file_obj, std::string texture_file) {
  load(file_obj, texture_file);
}

Model3d::~Model3d() {}

void Model3d::load(std::string file_obj, std::string texture_file) {
  loadOBJ(file_obj);

  uint32_t w, h;
  uint32_t bpp;

  std::string expansion = texture_file.substr(texture_file.rfind('.') + 1, 3);

  unsigned char* data = nullptr;
  if (tolower(expansion) == "bmp") {
    ReadBMP(texture_file.data(), &data, &w, &h, &bpp);
    if (data) {
      glGenTextures(1, texture);

      glBindTexture(GL_TEXTURE_2D, texture[0]);

      gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, data);

      delete[] data;
    }
  } else {
    std::vector<unsigned char> image;
    unsigned width, height;

    unsigned error = lodepng::decode(image, width, height, texture_file);

    if (error)
      std::cout << "decoder error " << error << ": "
                << lodepng_error_text(error) << std::endl;
    else {
      glGenTextures(1, texture);

      glBindTexture(GL_TEXTURE_2D, texture[0]);

      gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGBA,
                        GL_UNSIGNED_BYTE, image.data());
    }
  }
}