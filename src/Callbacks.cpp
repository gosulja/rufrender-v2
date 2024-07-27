#include "Callbacks.hpp"

Camera* g_Camera = nullptr;
float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;
static bool firstMouse = false;
static bool cursorEnabled = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_INSERT) == GLFW_PRESS) {
        if (cursorEnabled) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        cursorEnabled = !cursorEnabled;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if (cursorEnabled) return;

    if (g_Camera) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            g_Camera->ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            g_Camera->ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            g_Camera->ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            g_Camera->ProcessKeyboard(RIGHT, deltaTime);
    }
}

void mouse_callback(GLFWwindow* window, double xposi, double yposi) {
    float xpos = static_cast<float>(xposi);
    float ypos = static_cast<float>(yposi);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    if (cursorEnabled) return;

    g_Camera->ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (cursorEnabled) return;

    g_Camera->ProcessMouseScroll(yoffset);
}
