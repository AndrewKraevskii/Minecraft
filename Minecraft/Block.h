#pragma once

#include <glut.h>

#include "sfml_part/Vector3.hpp"

class Block {
  sf::Vector3d position;
  sf::Vector3d size;
  sf::Vector3d rotation;

 public:
  Block(sf::Vector3d position = {0, 0, 0}, sf::Vector3d size = {1, 1, 1},
        sf::Vector3d rotation = {0, 0, 0})
      : position(position), size(size), rotation(rotation) {}

  void move(sf::Vector3d move) { position += move; }

  void Draw() {
    glPushMatrix();
    glColor3d(1, 1, 0);
    glTranslated(position.x, position.y, position.z);
    glRotated(rotation.mode(), rotation.x, rotation.y, rotation.z);
    glutSolidCube(size.x);
    glPopMatrix();
  }
};
