#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "fontManager.h"

namespace ec2 {
    namespace graphics {

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

        class Window
        {
        private:
            const char *_title;
            int _width, _height;
            GLFWwindow *_window;
            bool _closed;

            bool _keys[MAX_KEYS];
            bool _keyState[MAX_KEYS];
            bool _keyTyped[MAX_KEYS];
            bool _buttons[MAX_BUTTONS];
            bool _mouseState[MAX_KEYS];
            bool _mouseClicked[MAX_KEYS];
            double _mx, _my;
        public:
            Window(const char *title, int width, int height);
            ~Window();
            bool closed() const;
            void update();
            void clear() const;

            inline int getWidth() const { return _width; }
            inline int getHeight() const { return _height; }

            bool isKeyPressed(unsigned int keycode) const;
            bool isKeyTyped(unsigned int keycode) const;
            bool isButtonPressed(unsigned int button) const;
            bool isButtonClicked(unsigned int button) const;
            void getMousePosition(double &x, double &y) const;

        private:
            bool init();
            friend static void window_resize(GLFWwindow *window, int width, int height);
            friend static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
            friend static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
            friend static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
        };
    }
}