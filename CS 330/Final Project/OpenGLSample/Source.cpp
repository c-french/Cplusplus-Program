#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);
GLuint InitObject(const GLfloat points[], const int size);

GLuint vbo;
GLuint vao[7];
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 2.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool orthographic = false;
float scrollspeed = 1.0f;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 pointLightPositions[] = {
        glm::vec3(-5.0f,  2.0f,  -5.0f),
        glm::vec3(5.0f, 2.0f, -5.0f),
        glm::vec3(-5.0f,  2.0f, 5.0f),
        glm::vec3(5.0f,  2.0f, 5.0f)
};

int main(int argc, char** argv)
{
    // glfw: initialize and configure
    // ------------------------------
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Charles French CS 330 Final Project", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("shaderfiles//6.multiple_lights.vs", "shaderfiles//6.multiple_lights.fs");
    Shader lightCubeShader("shaderfiles//6.light_cube.vs", "shaderfiles//6.light_cube.fs");
    Shader capShader("shaderfiles//4.1.texture.vs", "shaderfiles//4.1.texture.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
   
    //plane
    GLfloat points[] = {
        //x		y	  z	    | normals           |S	    T
        -5.0f, 0.0f, 5.0f,  0.0f, -1.0f, 0.0f,    0.0f, 0.0f,
        -5.0f, 0.0f, -5.0f, 0.0f, -1.0f, 0.0f,    0.0f, 1.0f,
        5.0f, 0.0f, -5.0f,  0.0f, -1.0f, 0.0f,    1.0f, 0.0f,
        -5.0f, 0.0f, 5.0f,  0.0f, -1.0f, 0.0f,    0.0f, 0.0f,
        5.0f, 0.0f, -5.0f,  0.0f, -1.0f, 0.0f,    1.0f, 1.0f,
        5.0f, 0.0f, 5.0f,   0.0f, -1.0f, 0.0f,    1.0f, 0.0f
    };
    //deck
    GLfloat deckSide[] = {
        //x		y	  z	    |normal            | S    T
        0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, //front left
        0.66f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f,

        0.66f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  //front right
        0.66f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f,

        0.0f, 0.0f, -0.1f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
        0.0f, 1.0f, -0.1f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,//back left
        0.66f, 1.0f, -0.1f, 0.0f, 0.0f, -1.0f,  0.0f, 1.0f,

        0.66f, 0.0f, -0.1f, 0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
        0.66f, 1.0f, -0.1f, 0.0f, 0.0f, -1.0f,  0.0f, 1.0f,//back right
        0.0f, 0.0f, -0.1f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f,

        0.0f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        0.0f, 1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, //left top
        0.0f, 1.0f, -0.1f,  -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,

        0.0f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        0.0f, 0.0f, -0.1f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f, //left bottom
        0.0f, 1.0f, -0.1f,  -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,

        0.66f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
        0.66f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,//right top
        0.66f, 1.0f, -0.1f, 1.0f, 0.0f, 0.0f,   1.0f, 0.0f,

        0.66f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
        0.66f, 0.0f, -0.1f, 1.0f, 0.0f, 0.0f,   0.0f, 0.0f, //right bottom
        0.66f, 1.0f, -0.1f, 1.0f, 0.0f, 0.0f,   1.0f, 0.0f,

        0.0f, 0.0f, 0.0f,   0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
        0.0f, 0.0f, -0.1f,  0.0f, -1.0f, 0.0f,  0.0f, 0.0f, // bottom left
        0.66f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f,

        0.0f, 0.0f, -0.1f,  0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
        0.66f, 0.0f, -0.1f, 0.0f, -1.0f, 0.0f,  1.0f, 0.0f,// bottom right
        0.66f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f,

        0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
        0.0f, 1.0f, -0.1f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,// top left
        0.66f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,

        0.0f, 1.0f, -0.1f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        0.66f, 1.0f, -0.1f, 0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // top right
        0.66f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f
    };
    //card
    GLfloat cardFace[] = {
        -0.33f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        -0.33f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        0.33f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f,  1.0f, 1.0f,

        -0.33f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        0.33f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        0.33f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f,  1.0f, 1.0f
    };
    //top of card deck
    GLfloat cardTop[] = {
        //x		y	  z	        |normals            |	S	T
        0.0f, 0.0f, 0.001f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        0.0f, 1.0f, 0.001f,     0.0f, 0.0f, 1.0f,   0.0f, 1.0f, //top left
        0.66f, 1.0f, 0.001f,    0.0f, 0.0f, 1.0f,   1.0f, 1.0f,

        0.66f, 0.0f, 0.001f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
        0.0f, 0.0f, 0.001f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  //top right
        0.66f, 1.0f, 0.001f,    0.0f, 0.0f, 1.0f,   1.0f, 1.0f
    };
    //bottom of card deck
    GLfloat cardBottom[] = {
        //x		y	z		    |normals            | S		T
        0.0f, 0.0f, -0.101f,    0.0f, 0.0f, -1.0f,   1.0f, 0.0f,
        0.0f, 1.0f, -0.101f,    0.0f, 0.0f, -1.0f,   1.0f, 1.0f,//bottom left
        0.66f, 1.0f, -0.101f,   0.0f, 0.0f, -1.0f,   0.0f, 1.0f,

        0.66f, 0.0f, -0.101f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f,
        0.66f, 1.0f, -0.101f,   0.0f, 0.0f, -1.0f,   0.0f, 1.0f,//bottom right
        0.0f, 0.0f, -0.101f,    0.0f, 0.0f, -1.0f,   1.0f, 0.0f
    };
   // circle (octagon) for plastic cap
    GLfloat capBottom[] = {
        //x y z                     | normals                   | texture
        0.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       0.5f,   0.5f,  //circle origin
        1.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       1.0f,   0.5f,  //rightmost vertex
        (sqrt(2.0f) / 2.0f), 0.01f, (-(sqrt(2.0f)/2.0f)),    0.0f,   1.0f,   0.0f,   1.0f,   1.0f,   //"upper right" of circle

        0.0f,   0.0f,   0.0f,       0.0f,   1.0f,   0.0f,       0.5f,   0.5f,  //circle origin
        (sqrt(2.0f) / 2.0f), 0.01f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   1.0f,   1.0f,   //"upper right" of circle
        0.0f,   0.01f,   -1.0f,      0.0f,   1.0f,   0.0f,       0.5f,   1.0f,  // top

        0.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       0.5f,   0.5f,  //circle origin
        0.0f,   0.01f,   -1.0f,      0.0f,   1.0f,   0.0f,       0.5f,   1.0f,  // top
        (-(sqrt(2.0f) / 2.0f)), 0.01f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //upper left

        0.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       0.5f,   0.5f,  //circle origin
        (-(sqrt(2.0f) / 2.0f)), 0.01f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //upper left
        -1.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       0.0f,   0.5f, //leftmost vertex

        0.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       0.5f,   0.5f,  //circle origin
        -1.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       0.0f,   0.5f, //leftmost vertex
        (-(sqrt(2.0f) / 2.0f)), 0.01f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //bottom left

        0.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       0.5f,   0.5f,  //circle origin
        (-(sqrt(2.0f) / 2.0f)), 0.01f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //bottom left
        0.0f,   0.01f,   1.0f,      0.0f,   1.0f,   0.0f,       0.5f,    0.0f, // bottom

        0.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       0.5f,   0.5f,  //circle origin
        0.0f,   0.01f,   1.0f,      0.0f,   1.0f,   0.0f,       0.5f,    0.0f, // bottom
        ((sqrt(2.0f) / 2.0f)), 0.01f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //bottom right

        0.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       0.5f,   0.5f,  //circle origin
        ((sqrt(2.0f) / 2.0f)), 0.01f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //bottom right
        1.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       1.0f,   0.5f  //rightmost vertex
    };
    // side for plastic cap
    GLfloat capSide[] = {
        //x y z                     | normals                   | texture
        1.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       1.0f,   0.5f,  //rightmost botom vertex
        1.0f,   0.51f,   0.0f,       0.0f,   1.0f,   0.0f,       1.0f,   0.5f,  //rightmost top vertex
        (sqrt(2.0f) / 2.0f), 0.01f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   1.0f,   1.0f,   //"upper right" of botom circle

        1.0f,   0.51f,   0.0f,       0.0f,   1.0f,   0.0f,       1.0f,   0.5f,  //rightmost botom vertex
        1.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       1.0f,   0.5f,  //rightmost top vertex
        (sqrt(2.0f) / 2.0f), 0.51f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   1.0f,   1.0f,   //"upper right" of botom circle

        1.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       1.0f,   0.5f,  //rightmost botom vertex
        (sqrt(2.0f) / 2.0f), 0.51f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   1.0f,   1.0f,   //"upper right" of top circle
        (sqrt(2.0f) / 2.0f), 0.01f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   1.0f,   1.0f,   //"upper right" of botom circle

        1.0f,   0.51f,   0.0f,       0.0f,   1.0f,   0.0f,       1.0f,   0.5f,  //rightmost botom vertex
        (sqrt(2.0f) / 2.0f), 0.01f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   1.0f,   1.0f,   //"upper right" of top circle
        (sqrt(2.0f) / 2.0f), 0.51f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   1.0f,   1.0f,   //"upper right" of botom circle

        (sqrt(2.0f) / 2.0f), 0.01f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   1.0f,   1.0f,   //"upper right" of botom circle
        (sqrt(2.0f) / 2.0f), 0.51f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   1.0f,   1.0f,   //"upper right" of top circle
        0.0f,   0.01f,   -1.0f,      0.0f,   1.0f,   0.0f,       0.5f,   1.0f,  // botom top

        (sqrt(2.0f) / 2.0f), 0.51f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   1.0f,   1.0f,   //"upper right" of botom circle
        (sqrt(2.0f) / 2.0f), 0.01f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   1.0f,   1.0f,   //"upper right" of top circle
        0.0f,   0.51f,   -1.0f,      0.0f,   1.0f,   0.0f,       0.5f,   1.0f,  // botom top

        (sqrt(2.0f) / 2.0f), 0.01f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   1.0f,   1.0f,   //"upper right" of botom circle
        0.0f,   0.51f,   -1.0f,      0.0f,   1.0f,   0.0f,       0.5f,   1.0f,  // top top
        0.0f,   0.01f,   -1.0f,      0.0f,   1.0f,   0.0f,       0.5f,   1.0f,  // botom top

        (sqrt(2.0f) / 2.0f), 0.51f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   1.0f,   1.0f,   //"upper right" of botom circle
        0.0f,   0.01f,   -1.0f,      0.0f,   1.0f,   0.0f,       0.5f,   1.0f,  // top top
        0.0f,   0.51f,   -1.0f,      0.0f,   1.0f,   0.0f,       0.5f,   1.0f,  // botom top

        0.0f,   0.01f,   -1.0f,      0.0f,   1.0f,   0.0f,       0.5f,   1.0f,  // botom top
        0.0f,   0.51f,   -1.0f,      0.0f,   1.0f,   0.0f,       0.5f,   1.0f,  // top top
        (-(sqrt(2.0f) / 2.0f)), 0.01f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //botom upper left

        0.0f,   0.51f,   -1.0f,      0.0f,   1.0f,   0.0f,       0.5f,   1.0f,  // botom top
        0.0f,   0.01f,   -1.0f,      0.0f,   1.0f,   0.0f,       0.5f,   1.0f,  // top top
        (-(sqrt(2.0f) / 2.0f)), 0.51f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //botom upper left

        0.0f,   0.01f,   -1.0f,      0.0f,   1.0f,   0.0f,       0.5f,   1.0f,  // botom top
        (-(sqrt(2.0f) / 2.0f)), 0.51f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //top upper left
        (-(sqrt(2.0f) / 2.0f)), 0.01f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //botom upper left

        0.0f,   0.51f,   -1.0f,      0.0f,   1.0f,   0.0f,       0.5f,   1.0f,  // botom top
        (-(sqrt(2.0f) / 2.0f)), 0.01f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //top upper left
        (-(sqrt(2.0f) / 2.0f)), 0.51f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //botom upper left

        (-(sqrt(2.0f) / 2.0f)), 0.01f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //botom upper left
        (-(sqrt(2.0f) / 2.0f)), 0.51f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //top upper left
        -1.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       0.0f,   0.5f, //botom leftmost vertex

        (-(sqrt(2.0f) / 2.0f)), 0.51f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //botom upper left
        (-(sqrt(2.0f) / 2.0f)), 0.01f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //top upper left
        -1.0f,   0.51f,   0.0f,       0.0f,   1.0f,   0.0f,       0.0f,   0.5f, //botom leftmost vertex

        (-(sqrt(2.0f) / 2.0f)), 0.01f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //botom upper left
        -1.0f,   0.51f,   0.0f,       0.0f,   1.0f,   0.0f,       0.0f,   0.5f, //top leftmost vertex
        -1.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       0.0f,   0.5f, //botom leftmost vertex

        (-(sqrt(2.0f) / 2.0f)), 0.51f, (-(sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //botom upper left
        -1.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       0.0f,   0.5f, //top leftmost vertex
        -1.0f,   0.51f,   0.0f,       0.0f,   1.0f,   0.0f,       0.0f,   0.5f, //botom leftmost vertex

        -1.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       0.0f,   0.5f, //botom leftmost vertex
        -1.0f,   0.51f,   0.0f,       0.0f,   1.0f,   0.0f,       0.0f,   0.5f, //top leftmost vertex
        (-(sqrt(2.0f) / 2.0f)), 0.01f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //botom bottom left

        -1.0f,   0.51f,   0.0f,       0.0f,   1.0f,   0.0f,       0.0f,   0.5f, //botom leftmost vertex
        -1.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       0.0f,   0.5f, //top leftmost vertex
        (-(sqrt(2.0f) / 2.0f)), 0.51f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //botom bottom left

        -1.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       0.0f,   0.5f, //botom leftmost vertex
        (-(sqrt(2.0f) / 2.0f)), 0.51f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //top bottom left
        (-(sqrt(2.0f) / 2.0f)), 0.01f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //botom bottom left

        -1.0f,   0.51f,   0.0f,       0.0f,   1.0f,   0.0f,       0.0f,   0.5f, //botom leftmost vertex
        (-(sqrt(2.0f) / 2.0f)), 0.01f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //top bottom left
        (-(sqrt(2.0f) / 2.0f)), 0.51f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //botom bottom left

        (-(sqrt(2.0f) / 2.0f)), 0.01f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //botom bottom left
        (-(sqrt(2.0f) / 2.0f)), 0.51f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //top bottom left
        0.0f,   0.01f,   1.0f,      0.0f,   1.0f,   0.0f,       0.5f,    0.0f, //botom  bottom

        (-(sqrt(2.0f) / 2.0f)), 0.51f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //botom bottom left
        (-(sqrt(2.0f) / 2.0f)), 0.01f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //top bottom left
        0.0f,   0.51f,   1.0f,      0.0f,   1.0f,   0.0f,       0.5f,    0.0f, //botom  bottom

        (-(sqrt(2.0f) / 2.0f)), 0.01f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //botom bottom left
        0.0f,   0.51f,   1.0f,      0.0f,   1.0f,   0.0f,       0.5f,    0.0f, //top bottom
        0.0f,   0.01f,   1.0f,      0.0f,   1.0f,   0.0f,       0.5f,    0.0f, //botom  bottom

        (-(sqrt(2.0f) / 2.0f)), 0.51f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //botom bottom left
        0.0f,   0.01f,   1.0f,      0.0f,   1.0f,   0.0f,       0.5f,    0.0f, //top bottom
        0.0f,   0.51f,   1.0f,      0.0f,   1.0f,   0.0f,       0.5f,    0.0f, //botom  bottom

        0.0f,   0.01f,   1.0f,      0.0f,   1.0f,   0.0f,       0.5f,    0.0f, //botom  bottom
        0.0f,   0.51f,   1.0f,      0.0f,   1.0f,   0.0f,       0.5f,    0.0f, //top  bottom
        ((sqrt(2.0f) / 2.0f)), 0.01f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //botom bottom right

        0.0f, 0.51f, 1.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, //botom  bottom
        0.0f, 0.01f, 1.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, //top  bottom
        ((sqrt(2.0f) / 2.0f)), 0.51f, ((sqrt(2.0f) / 2.0f)), 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //botom bottom right

        0.0f,   0.01f,   1.0f,      0.0f,   1.0f,   0.0f,       0.5f,    0.0f, //botom  bottom
        ((sqrt(2.0f) / 2.0f)), 0.51f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //top bottom right
        ((sqrt(2.0f) / 2.0f)), 0.01f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //botom bottom right

        0.0f, 0.51f, 1.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, //botom  bottom
        ((sqrt(2.0f) / 2.0f)), 0.01f, ((sqrt(2.0f) / 2.0f)), 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //top bottom right
        ((sqrt(2.0f) / 2.0f)), 0.51f, ((sqrt(2.0f) / 2.0f)), 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //botom bottom right

        ((sqrt(2.0f) / 2.0f)), 0.01f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //botom bottom right
        ((sqrt(2.0f) / 2.0f)), 0.51f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //top bottom right
        1.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       1.0f,   0.5f,  //rightmost botom  vertex

        ((sqrt(2.0f) / 2.0f)), 0.51f, ((sqrt(2.0f) / 2.0f)), 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //botom bottom right
        ((sqrt(2.0f) / 2.0f)), 0.01f, ((sqrt(2.0f) / 2.0f)), 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //top bottom right
        1.0f, 0.51f, 0.0f,          0.0f, 1.0f, 0.0f, 1.0f, 0.5f,  //rightmost botom  vertex

        ((sqrt(2.0f) / 2.0f)), 0.01f, ((sqrt(2.0f) / 2.0f)),    0.0f,   1.0f,   0.0f,   0.0f,   1.0f, //botom bottom right
        1.0f,   0.51f,   0.0f,       0.0f,   1.0f,   0.0f,       1.0f,   0.5f,  //rightmost top  vertex
        1.0f,   0.01f,   0.0f,       0.0f,   1.0f,   0.0f,       1.0f,   0.5f,  //rightmost botom  vertex

        ((sqrt(2.0f) / 2.0f)), 0.51f, ((sqrt(2.0f) / 2.0f)), 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //botom bottom right
        1.0f, 0.01f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f,  //rightmost top  vertex
        1.0f, 0.51f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f  //rightmost botom  vertex
    };

    //vertex data for light objects
    GLfloat lightVertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,

         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f
    };

    unsigned int lightVBO, lightVAO;
    glGenVertexArrays(1, &lightVBO);
    glGenBuffers(1, &lightVBO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);
    
   
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &vbo);
    glGenVertexArrays(7, vao);

    // initial first object into first VAO
    glBindVertexArray(vao[0]);
    InitObject(points, sizeof(points));
    glBindVertexArray(0);

    // second object in second VAO
    glBindVertexArray(vao[1]);
    InitObject(deckSide, sizeof(deckSide));
    glBindVertexArray(0);

    //card in deck
    glBindVertexArray(vao[2]);
    InitObject(cardFace, sizeof(cardFace));;
    glBindVertexArray(0);

    //top of deck
    glBindVertexArray(vao[3]);
    InitObject(cardTop, sizeof(cardTop));
    glBindVertexArray(0);

    //bottom of deck
    glBindVertexArray(vao[4]);
    InitObject(cardBottom, sizeof(cardBottom));
    glBindVertexArray(0);

    //cap bottom
    glBindVertexArray(vao[5]);
    InitObject(capBottom, sizeof(capBottom));
    glBindVertexArray(0);

    //cap sides
    glBindVertexArray(vao[6]);
    InitObject(capSide, sizeof(capSide));
    glBindVertexArray(0);

    //load texture
    stbi_set_flip_vertically_on_load(true);
    unsigned int deckface_diffuse = loadTexture("deckface.jpg");
    unsigned int deckface_specular = loadTexture("deckface_dark.jpg");
    unsigned int deckside_diffuse = loadTexture("deckside.jpg");
    unsigned int deckside_specular = loadTexture("deckside_dark.jpg");
    unsigned int mousepad_diffuse = loadTexture("mousepad.jpg");
    unsigned int mousepad_specular = loadTexture("mousepad_dark.jpg");
    unsigned int plastic_diffuse = loadTexture("plastic.jpg");
    unsigned int plastic_specular = loadTexture("plastic_dark.jpg");
    lightingShader.use();
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);

    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       
        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);
        lightingShader.setFloat("material.shininess", 2.0f);

        
        // directional light
        lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        lightingShader.setVec3("dirLight.ambient", 0.25f, 0.25f, 0.25f);
        lightingShader.setVec3("dirLight.diffuse", 0.25f, 0.25f, 0.25f);
        lightingShader.setVec3("dirLight.specular", 0.25f, 0.25f, 0.25f);
        // point light 1
        lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
        lightingShader.setVec3("pointLights[0].ambient", 0.25f, 0.25f, 0.25f);
        lightingShader.setVec3("pointLights[0].diffuse", 0.25f, 0.25f, 0.25f);
        lightingShader.setVec3("pointLights[0].specular", 0.25f, 0.25f, 0.25f);
        lightingShader.setFloat("pointLights[0].constant", 1.0f);
        lightingShader.setFloat("pointLights[0].linear", 0.09);
        lightingShader.setFloat("pointLights[0].quadratic", 0.032);
        // point light 2 - unused, but need to set RBG values for the shader to function properly (all 0's effectively disable the light)
        lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
        lightingShader.setVec3("pointLights[1].ambient", 0.25f, 0.25f, 0.25f);
        lightingShader.setVec3("pointLights[1].diffuse", 0.25f, 0.25f, 0.25f);
        lightingShader.setVec3("pointLights[1].specular", 0.25f, 0.25f, 0.25f);
        lightingShader.setFloat("pointLights[1].constant", 1.0f);
        lightingShader.setFloat("pointLights[1].linear", 0.09);
        lightingShader.setFloat("pointLights[1].quadratic", 0.032);
        // point light 3
        lightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
        lightingShader.setVec3("pointLights[2].ambient", 0.25f, 0.25f, 0.25f);
        lightingShader.setVec3("pointLights[2].diffuse", 0.25f, 0.25f, 0.25f);
        lightingShader.setVec3("pointLights[2].specular", 0.25f, 0.25f, 0.25f);
        lightingShader.setFloat("pointLights[2].constant", 1.0f);
        lightingShader.setFloat("pointLights[2].linear", 0.09);
        lightingShader.setFloat("pointLights[2].quadratic", 0.032);
        // point light 4 
        lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
        lightingShader.setVec3("pointLights[3].ambient", 0.5f, 0.5f, 0.5f);
        lightingShader.setVec3("pointLights[3].diffuse", 0.5f, 0.5f, 0.5f);
        lightingShader.setVec3("pointLights[3].specular", 0.5f, 0.5f, 0.5f);
        lightingShader.setFloat("pointLights[3].constant", 1.0f);
        lightingShader.setFloat("pointLights[3].linear", 0.09);
        lightingShader.setFloat("pointLights[3].quadratic", 0.032);
        // spotLight
        lightingShader.setVec3("spotLight.position", camera.Position);
        lightingShader.setVec3("spotLight.direction", camera.Front);
        lightingShader.setVec3("spotLight.ambient", 0.25f, 0.25f, 0.25f);
        lightingShader.setVec3("spotLight.diffuse", 0.25f, 0.25f, 0.50f);
        lightingShader.setVec3("spotLight.specular", 0.25f, 0.25f, 0.25f);
        lightingShader.setFloat("spotLight.constant", 1.0f);
        lightingShader.setFloat("spotLight.linear", 0.09);
        lightingShader.setFloat("spotLight.quadratic", 0.032);
        lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        // view/projection transformations
        glm::mat4 projection;
        if (orthographic) {
            float scale = 100;
            projection = glm::ortho(-((float)SCR_WIDTH / scale), ((float)SCR_WIDTH / scale), -((float)SCR_HEIGHT / scale), ((float)SCR_HEIGHT / scale), -10.0f, 10.0f);
        }
        else {
            projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
        }
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);

        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mousepad_diffuse);
        //bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, mousepad_specular);
        // render the mousepad
        glBindVertexArray(vao[0]);
        lightingShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 3 * 2);
        glBindVertexArray(0);

        // render inner deck, binding the right texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, deckside_diffuse);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, deckside_specular);
        glBindVertexArray(vao[1]);
        //move deck into correct place in the scene
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-3.0f, 0.2f, 1.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, -1.0f));
        model = glm::scale(model, glm::vec3(2.0f));
        lightingShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        // render outer deck faces

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, deckface_diffuse);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, deckface_specular);
        glBindVertexArray(vao[3]);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-3.0f, 0.2f, 1.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, -1.0f));
        model = glm::scale(model, glm::vec3(2.0f));
        lightingShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 3 * 2);
        glBindVertexArray(0);
       
        //render card sticking out of deck
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, deckface_diffuse);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, deckface_specular);
        glBindVertexArray(vao[2]);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.8f, 0.2f, 1.0f));
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
        model = glm::rotate(model, glm::radians(83.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(8.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        
        model = glm::scale(model, glm::vec3(2.0f));
        lightingShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 3 * 2);
        glBindVertexArray(0);

        //plastic cap
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, plastic_diffuse);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, plastic_specular);
        glBindVertexArray(vao[5]);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, 0.01f, 1.0f));
        model = glm::scale(model, glm::vec3(0.5f));
        lightingShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 3 * 8);
        glBindVertexArray(0);

        //plastic side
       
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, plastic_diffuse);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, plastic_specular);
        glBindVertexArray(vao[6]);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, 0.01f, 1.0f));
        model = glm::scale(model, glm::vec3(0.5f));
        lightingShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 3 * 32);
        glBindVertexArray(0);

        //render lights
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);

        glBindVertexArray(lightVAO);
        for (unsigned int i = 0; i < 4; i++) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            lightCubeShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 3 * 2);
        }
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &vao[0]);
    glDeleteVertexArrays(1, &vao[1]);
    glDeleteVertexArrays(1, &vao[2]);
    glDeleteVertexArrays(1, &vao[3]);
    glDeleteVertexArrays(1, &vao[4]);
    glDeleteVertexArrays(1, &vao[5]);
    glDeleteVertexArrays(1, &vao[6]);
    glDeleteBuffers(1, &vbo);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime * scrollspeed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime * scrollspeed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime * scrollspeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime * scrollspeed);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.Position = camera.Position + (glm::vec3(0.0f, 1.0f, 0.0f) * deltaTime * scrollspeed);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.Position = camera.Position - (glm::vec3(0.0f, 1.0f, 0.0f) * deltaTime * scrollspeed);
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        if (!orthographic) {
            orthographic = true;
        }
        else {
            orthographic = false;
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    scrollspeed = float(yoffset);
    if (scrollspeed < 1.0f) {
        scrollspeed = 1.0f;
    }
    if (scrollspeed > 200.0f) {
        scrollspeed = 200.0f;
    }
}
// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

GLuint InitObject(const GLfloat points[], const int size) {
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    return vbo;
}