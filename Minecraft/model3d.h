#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "vectors.h"

class Model3d {
  uint32_t texture[1];
  std::vector<Vector3d> vertexes;
  std::vector<Vector2d> UVs;
  std::vector<Vector3d> normals;
  std::vector<std::vector<Vector3i>> faces;

  void loadOBJ(std::string file_name);

 public:
  Model3d(){};
  Model3d(std::string file_name);
  Model3d(std::string file_obj, std::string texture_file);

  void draw();
  void load(std::string file_obj, std::string texture_file);
  ~Model3d();
};
