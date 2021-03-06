#include "window.h"

namespace ec2 {
    namespace graphics {

        //I am still not sure why i have to have these here but it wont build if I dont.
        void window_resize(GLFWwindow *window, int width, int height);
        void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods); 
        void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
        void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

        Window::Window(const char *title, int width, int height)
        {
            _title = title;
            _width = width;
            _height = height;
            if (!init())
                glfwTerminate();

            FontManager::add(new Font("SourceSansPro", "SourceCodePro-Light.ttf", 32));

            for (int i = 0; i < MAX_KEYS; i++)
            {
                _keys[i] = false;
                _keyState[i] = false;
                _keyTyped[i] = false;
            }

            for (int i = 0; i < MAX_BUTTONS; i++)
            {
                _buttons[i] = false;
                _mouseState[i] = false;
                _mouseClicked[i] = false;
            }

        }

        Window::~Window()
        {
            FontManager::clean();
            glfwTerminate();
        }

        bool Window::init()
        {
            if (!glfwInit())
            {
                std::cout << "Failed to initialize GLFW" << std::endl;
                return false;
            }

            _window = glfwCreateWindow(_width, _height, _title, NULL, NULL);

            if (!_window)
            {
                glfwTerminate();
                std::cout << "Failed to create GLFW window!" << std::endl;
                return false;
            }

            glfwMakeContextCurrent(_window);
            glfwSetWindowUserPointer(_window, this);
            glfwSetFramebufferSizeCallback(_window, window_resize);
            glfwSetKeyCallback(_window, key_callback);
            glfwSetMouseButtonCallback(_window, mouse_button_callback);
            glfwSetCursorPosCallback(_window, cursor_position_callback);

            glfwSwapInterval(0.0);

            if (glewInit() != GLEW_OK)
            {
                std::cout << "Could not initialize GLEW!" << std::endl;
                return false;
            }

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

            return true;
        }

        bool Window::closed() const
        {
            return glfwWindowShouldClose(_window) == 1;
        }

        void Window::getMousePosition(double &x, double &y) const
        {
            x = _mx;
            y = _my;
        }

        void Window::clear() const
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void Window::update()
        {
            for (int i = 0; i < MAX_KEYS; i++) {
                _keyTyped[i] = _keys[i] && !_keyState[i];
            }

            memcpy(_keyState, _keys, MAX_KEYS);
            
            for (int i = 0; i < MAX_BUTTONS; i++) {
                _mouseClicked[i] = _buttons[i] && !_mouseState[i];
            }

            memcpy(_mouseState, _buttons, MAX_BUTTONS);

            GLenum error = glGetError();
            if (error != GL_NO_ERROR)
            {
                std::cout << "OpenGL Error: " << error << std::endl;
            }

            glfwPollEvents();
            glfwGetFramebufferSize(_window, &_width, &_height);
            glViewport(0, 0, _width, _height);
            glfwSwapBuffers(_window);
        }

        bool Window::isKeyPressed(unsigned int keycode) const
        {
            if (keycode >= MAX_KEYS)
                return false;
            return _keys[keycode];
        }

        bool Window::isKeyTyped(unsigned int keycode) const
        {
            if (keycode >= MAX_KEYS)
                return false;
            return _keyTyped[keycode];
        }

        bool Window::isButtonPressed(unsigned int button) const
        {
            if (button >= MAX_BUTTONS)
                return false;
            return _buttons[button];
        }

        bool Window::isButtonClicked(unsigned int button) const
        {
            if (button >= MAX_BUTTONS)
                return false;
            return _mouseClicked[button];
        }

        void window_resize(GLFWwindow *window, int width, int height)
        {
            glViewport(0, 0, width, height);
            Window* win = (Window*)glfwGetWindowUserPointer(window);
            win->_width = width;
            win->_height = height;
        }

        void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            Window* win = (Window*)glfwGetWindowUserPointer(window);
            
            win->_keys[key] = action != GLFW_RELEASE;
        }

        void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
        {
            Window* win = (Window*)glfwGetWindowUserPointer(window);

            win->_buttons[button] = action != GLFW_RELEASE;
        }

        void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
        {
            Window* win = (Window*)glfwGetWindowUserPointer(window);

            win->_my = ypos;
            win->_mx = xpos;
        }
    }
}