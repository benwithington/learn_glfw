#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include <memory>

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  if (key == GLFW_KEY_F && action == GLFW_PRESS) {
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height,
                         mode->refreshRate);
  }

  if (key == GLFW_KEY_W && action == GLFW_PRESS) {
    glfwSetWindowMonitor(window, nullptr, 100, 100, 800, 600, 0);
  }

  if (key == GLFW_KEY_I && action == GLFW_PRESS) {
    glfwIconifyWindow(window);
  }

  if (key == GLFW_KEY_M && action == GLFW_PRESS) {
    glfwMaximizeWindow(window);
  }

  if (key == GLFW_KEY_R && action == GLFW_PRESS) {
    glfwRestoreWindow(window);
  }

  if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
    glfwSetWindowOpacity(window, 0.0f);
  }

  if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
    glfwSetWindowOpacity(window, 0.5f);
  }

  if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
    glfwSetWindowOpacity(window, 1.0f);
  }

  if (key == GLFW_KEY_A && action == GLFW_PRESS) {
    glfwRequestWindowAttention(window);
  }

  if (key == GLFW_KEY_D && action == GLFW_PRESS) {
    auto decorated = glfwGetWindowAttrib(window, GLFW_DECORATED);
    if (decorated) {
      glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
    } else {
      glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_TRUE);
    }
  }
}

void error_callback(int code, const char *description) {
  switch (code) {
  case GLFW_NO_ERROR:
    break;
  case GLFW_NOT_INITIALIZED:
    std::cout << "GLFW_NOT_INITIALISED\n";
    break;
  case GLFW_NO_CURRENT_CONTEXT:
    std::cout << "GLFW_NO_CURRENT_CONTEXT\n";
    break;
  case GLFW_INVALID_ENUM:
    std::cout << "GLFW_INVALID_ENUM\n";
    break;
  case GLFW_INVALID_VALUE:
    std::cout << "GLFW_INVALID_VALUE\n";
    break;
  case GLFW_OUT_OF_MEMORY:
    std::cout << "GLFW_OUT_OF_MEMORY\n";
    break;
  case GLFW_API_UNAVAILABLE:
    std::cout << "GLFW_API_UNAVAILABLE\n";
    break;
  case GLFW_VERSION_UNAVAILABLE:
    std::cout << "GLFW_VERSION_UNAVAILABLE\n";
    break;
  case GLFW_PLATFORM_ERROR:
    std::cout << "GLFW_PLATFORM_ERROR\n";
    break;
  case GLFW_FORMAT_UNAVAILABLE:
    std::cout << "GLFW_FORMAT_UNAVAILABLE\n";
    break;
  case GLFW_NO_WINDOW_CONTEXT:
    std::cout << "GLFW_NO_WINDOW_CONTEXT\n";
    break;
  default:
    std::cout << "Invalid GLFW error code\n";
    break;
  }

  std::cout << description << '\n';
}

void window_pos_callback(GLFWwindow *window, int xpos, int ypos) {
  std::cout << "\nWindow X pos: " << xpos << "\nWindow Y pos: " << ypos << '\n';
}

void window_iconify_callback(GLFWwindow *window, int iconified) {
  if (iconified) {
    std::cout << "Window has been iconified\n";
  } else {
    std::cout << "Window has been restored\n";
  }
}

void window_maximised_callback(GLFWwindow *window, int maximised) {
  if (maximised) {
    std::cout << "Window has been maximised\n";
  } else {
    std::cout << "Window has been restored\n";
  }
}

void window_focus_callback(GLFWwindow *window, int focused) {
  if (focused) {
    std::cout << "Window is now focused\n";
  } else {
    std::cout << "Window has lost focus\n";
  }
}

int main() {
  /*
   *  Initialize the library
   *  Before most GLFW functions can be called it is required to initialise the
   *  library, this set checks which features are available on the machine
   */
  glfwSetErrorCallback(error_callback); // can be called before glfwInit

  int major{};
  int minor{};
  int revision{};

  glfwGetVersion(&major, &minor, &revision); // can be called before glfwInit
  std::cout << "Running against GLFW " << major << "." << minor << "."
            << revision << '\n';

  std::cout << glfwGetVersionString() << '\n'; // also works before glfwInit

  if (!glfwInit()) {
    std::cout << "Unable to initialise GLFW\n";
    return EXIT_FAILURE;
  }

  // monitors
  GLFWmonitor *primary = glfwGetPrimaryMonitor();
  std::cout << "Primary: " << glfwGetMonitorName(primary) << '\n';

  int monitor_count;
  GLFWmonitor **monitors = glfwGetMonitors(&monitor_count);
  for (int i = 0; i < monitor_count; ++i) {
    std::cout << "Monitor: " << (i + 1) << '\n';
    std::cout << "Name: " << glfwGetMonitorName(monitors[i]) << '\n';

    int mode_count;
    const GLFWvidmode *modes = glfwGetVideoModes(monitors[i], &mode_count);
    for (int j = 0; j < mode_count; ++j) {
      std::cout << "\tMode: " << j << '\n';
      std::cout << "\t\tWidht: " << modes[j].width << '\n';
      std::cout << "\t\tHeight: " << modes[j].height << '\n';
      std::cout << "\t\tReresh Rate: " << modes[j].refreshRate << '\n';
    }
  }

  /* Create a windowed mode window and its OpenGL context */
  std::unique_ptr<GLFWwindow, decltype(glfwDestroyWindow) *> window{
      glfwCreateWindow(800, 600, "GLFW", nullptr, nullptr), glfwDestroyWindow};

  if (!window) {
    glfwTerminate();
    std::cout << "Unable to initialise GLFW window\n";
    return EXIT_FAILURE;
  }

  // Setting callbacks
  glfwSetKeyCallback(window.get(), key_callback);
  glfwSetWindowPosCallback(window.get(), window_pos_callback);
  glfwSetWindowIconifyCallback(window.get(), window_iconify_callback);
  glfwSetWindowMaximizeCallback(window.get(), window_maximised_callback);
  glfwSetWindowFocusCallback(window.get(), window_focus_callback);

  // Other glfw functionality
  glfwSetWindowTitle(window.get(), "ｇｌｆｗ");

  /* Make the window's context current */
  glfwMakeContextCurrent(window.get());

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window.get())) {
    /* Render here */
    // glClear(GL_COLOR_BUFFER_BIT);

    /* Swap front and back buffers */
    glfwSwapBuffers(window.get());

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return EXIT_SUCCESS;
}