#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "sfml_part/Vector2.hpp"
#include "sfml_part/Vector3.hpp"

class Object3d {
  uint32_t texture[1];
  std::vector<sf::Vector3d> vertexes;
  std::vector<sf::Vector2d> UVs;
  std::vector<sf::Vector3d> normals;
  std::vector<std::vector<sf::Vector3i>> faces;

 public:
  Object3d();
  Object3d(std::string file_name);

  void loadOBJ(std::string file_name);
  
  void draw();

  ~Object3d();
};
