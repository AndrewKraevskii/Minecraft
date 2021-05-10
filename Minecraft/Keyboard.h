#pragma once

#include <functional>
#include <vector>

class Keyboard {
  Keyboard() = delete;

  static std::vector<std::function<void(unsigned char, int, int)>>
      callbacks_down;
  static std::vector<std::function<void(unsigned char, int, int)>> callbacks_up;

  static std::vector<std::function<void(int, int, int)>> special_callbacks_down;
  static std::vector<std::function<void(int, int, int)>> special_callbacks_up;

  static bool is_button_down[256];
  static bool is_special_down[21];

  static void button_down(unsigned char key, int x, int y);
  static void button_up(unsigned char key, int x, int y);
  static void special_down(int key, int x, int y);
  static void special_up(int key, int x, int y);

 public:
  static void init();
  static bool is_button_pressed(unsigned char key);
  static bool is_special_pressed(int key);

  static void callback_down(void (*func)(unsigned char key, int x, int y));
  static void callback_up(void (*func)(unsigned char key, int x, int y));
  static void special_callback_down(void (*func)(int key, int x, int y));
  static void special_callback_up(void (*func)(int key, int x, int y));
  static int get_modifiers();
};
