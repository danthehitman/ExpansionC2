#pragma once

#include <iostream>
#include <GLFW/glfw3.h>

namespace ec2 {
    namespace graphics {
        void windowResize(GLFWwindow *window, int width, int height);

        class Window
        {
        private:
            const char *_title;
            int _width, _height;
            GLFWwindow *_window;
            bool _closed;
        public:
            Window(const char *title, int width, int height);
            ~Window();
            bool closed() const;
            void update();
            void clear() const;

            int getWidth();
            int getHeight();
        private:
            bool init();
        };
    }
}