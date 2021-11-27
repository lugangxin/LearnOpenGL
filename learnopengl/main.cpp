#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION //Ԥ���������޸�ͷ�ļ�������ֻ������صĺ�������Դ�룬�����ǽ����ͷ�ļ���Ϊһ�� .cpp �ļ�
#include <iostream>
#include "shader.h"
#include <stb_image.h>
#include <learnopengl/filesystem.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
//�����
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f,0.0f,-1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f,1.0f,0.0f);

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0f / 2.0;
float fov = 45.0f;
//ʱ��
float deltaTime = 0.0f;
float lastFrame = 0.0f;
/*
const char* vertexShaderSource = "#version 330 core\n"
"layout(location=0) in vec3 aPos;\n" //ʹ��in�ؼ��֣��ڶ�����ɫ�����������е����붥������
//ʹ������ɫ���ܹ�������ɫֵ��Ϊ������������
"layout(location=1) in vec3 aColor;\n"
"out vec3 ourColor;\n"//��Ƭ����ɫ�����һ����ɫ
"void main()\n"
"{\n"
//"   gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0);\n"//���һ����������͸�ӳ���
"   gl_Position=vec4(aPos,1.0);\n"//���һ����������͸�ӳ���
"   ourColor=aColor;\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
//"uniform vec4 ourColor;"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
//"   FragColor=vec4(1.0f,0.5f,0.2f,1.0f);\n"
//"   FragColor=ourColor;\n"
"   FragColor=vec4(ourColor,1.0f);\n"
"}\0";*/
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();//��ʼ��glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//����1����ѡ������ƣ�ö��ֵ��������2�������ѡ���ֵ
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//�����汾��(Major)�ʹΰ汾��(Minor)����Ϊ3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//ʹ�ú���ģʽ��ζ������ֻ��ʹ��OpenGL���ܵ�һ���Ӽ�
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);//�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳���������
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//ע���������������GLFW����ϣ��ÿ�����ڵ�����С��ʱ������������
    glfwSetCursorPosCallback(window,mouse_callback);
    glfwSetScrollCallback(window,scroll_callback);

    // glad: load all OpenGL function pointers����OpenGL����ָ�룬��ʼ��glad,���Ǹ�GLAD��������������ϵͳ��ص�OpenGL����ָ���ַ�ĺ���
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //��Ȼ���
    glEnable(GL_DEPTH_TEST);
    Shader ourShader("3.3.shader.vs","3.3.shader.fs");
    /*
    //�����ͱ���shader����
    //������ɫ��
    unsigned int vertexShader;//ID
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //�������ɫ��Դ�븽�ӵ���ɫ�������ϣ�Ȼ�������
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//����2ָ���˴��ݵ�Դ���ַ�������
    glCompileShader(vertexShader);
    //�������Ƿ����
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //ƬԪ��ɫ��
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //�������Ƿ����
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //����shader
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //��������Ƿ����
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    //�������Ժ�ɾ����ɫ������
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);*/

    //�����������ݺͻ��岢���ö�������
    /*
    float vertices[] = {//-1.0-1.0��Χ�ڣ���׼���豸����
    -0.5f,-0.5f,0.0f,
    0.5f,-0.5f,0.0f,
    0.0f,0.5f,0.0f
    };*/
    /*//���������
    float vertices[] = {
    0.5f, 0.5f, 0.0f,   // ���Ͻ�
    0.5f, -0.5f, 0.0f,  // ���½�
    -0.5f, -0.5f, 0.0f, // ���½�
    -0.5f, 0.5f, 0.0f   // ���Ͻ�
    };

    unsigned int indices[] = { // ע��������0��ʼ! 
        0, 1, 3, // ��һ��������
        1, 2, 3  // �ڶ���������
    };
    //�ڶ����а�����ɫ
    float vertices[] = {
        // λ��              // ��ɫ
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
    };*/
    /*
    //������������
    float vertices[] = {
        //     ---- λ�� ----       ---- ��ɫ ----     - �������� -
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
    };
    unsigned int indices[] = { // ע��������0��ʼ! 
        0, 1, 3, // ��һ��������
        1, 2, 3  // �ڶ���������
    };*/
    //������6���棬ÿ����2�������Σ�һ��������3�����㣬��36����
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    unsigned int VBO, VAO;//, EBO;
    glGenVertexArrays(1, &VAO);//�����������
    glGenBuffers(1, &VBO);//ʹ��glGenBuffers������һ������ID����һ��VBO����
    //glGenBuffers(1, &EBO);//�����������

    glBindVertexArray(VAO);



    glBindBuffer(GL_ARRAY_BUFFER, VBO);//���㻺�����Ļ���������GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//��֮ǰ����Ķ������ݸ��Ƶ�������ڴ���

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //���ö�������ָ��
    //����1���������ԣ�������λ��ֵΪ0������2���������Դ�С,vec3��3��ֵ��ɣ����Դ�СΪ3
    //����3���������� vec*���ɸ�����ֵ��� ����4���Ƿ�ϣ�����ݱ���׼�� ����5�������������Ķ���������֮��ļ��
    //����6�������ڻ�������ʼλ�õ�ƫ����
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);//������ɫ
    glEnableVertexAttribArray(0);//�Զ�������λ��ֵ��Ϊ���������ö�������
    /*
    //������������ɫ����
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    */
    //������������
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //��������
    unsigned int texture1;
    glGenTextures(1,&texture1);
    glBindTexture(GL_TEXTURE_2D,texture1);
    //Ϊ��ǰ�󶨶������û��ơ����˷�ʽ
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    //����ͼ��
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);//��תy��
    unsigned char* data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(),&width,&height,&nrChannels,0);
    if (data) {
        //����1������Ŀ�꣬����2���༶��Զ������0Ϊ��������  ����3������洢��ʽ
        //����4��5 ���  ����6��ʼ��Ϊ0   ����7��8��Դͼ�ĸ�ʽ����������
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    //��������
    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    //Ϊ��ǰ�󶨶������û��ơ����˷�ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //����ͼ��
    data = stbi_load(FileSystem::getPath("resources/textures/bricks2.jpg").c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        //����1������Ŀ�꣬����2���༶��Զ������0Ϊ��������  ����3������洢��ʽ
        //����4��5 ���  ����6��ʼ��Ϊ0   ����7��8��Դͼ�ĸ�ʽ����������
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    //����OpenGLÿ����ɫ�������������ĸ�����Ԫ��������Ⱦѭ��ǰ��
    ourShader.use();
    glUniform1i(glGetUniformLocation(ourShader.ID,"texture1"),0);
    ourShader.setInt("texture2",1);
    //������������ʹ��
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);//�󶨵�Ԫ�ػ���������洢��VAO�У�����������������
    glBindVertexArray(0);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))//ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�
    {
        float currentFram = glfwGetTime();
        deltaTime = currentFram - lastFrame;
        lastFrame = currentFram;
        
        // input
        // -----
        processInput(window);
        //��Ⱦָ��
        glClearColor(0.2f,0.3f,0.3f,1.0f);//�����Ļ��ʹ����ɫ
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//�����ɫ���壬������ɫ���嶼�ᱻ���ΪglClearColor�������õ���ɫ

        //������
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,texture1);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,texture2);
        /*
        //����任
        glm::mat4 transform = glm::mat4(1.0f);//��ʼ��
        transform = glm::translate(transform,glm::vec3(0.5f,-0.5f,0.0f));
        transform = glm::rotate(transform,(float)glfwGetTime(),glm::vec3(0.0f,0.0f,1.0f));
        */
        //����������
        //glUseProgram(shaderProgram);
        ourShader.use();
        /*
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID,"transform");
        glUniformMatrix4fv(transformLoc,1,GL_FALSE,glm::value_ptr(transform));//����2�����Ͷ��ٸ����� ����3���Ƿ�ת�ã�Ĭ�������� ����4���任�����ľ�������
        */
        //�����
        glm::mat4 view = glm::mat4(1.0f);
        float radius = 10.f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        //view = glm::lookAt(glm::vec3(camX,0.0f,camZ),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
        view = glm::lookAt(cameraPos,cameraPos+cameraFront,cameraUp);
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        /*
        // create transformations
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model,(float)glfwGetTime(),glm::vec3(0.5f,1.0f,0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        */
        //ourShader.setMat4("projection", projection);
        //unsigned int projecLoc = glGetUniformLocation(ourShader.ID, "projection");
        //glUniformMatrix4fv(projecLoc, 1, GL_FALSE, &projection[0][0]);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
        float angle = 20.0f;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        unsigned int projecLoc = glGetUniformLocation(ourShader.ID, "projection");
        glUniformMatrix4fv(projecLoc, 1, GL_FALSE, &projection[0][0]);
        /*
        //����uniform��ɫ
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram,"ourColor");
        glUniform4f(vertexColorLocation,0.0f,greenValue,0.0f,1.0f);
        */
        glBindVertexArray(VAO);//VAO��洢glBindBuffer�ĺ�������
        //glDrawArrays(GL_TRIANGLES, 0, 3);//����2������������ʼ���� ����3��������ƶ��ٸ�����
        //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);//����������ͼ
        glDrawArrays(GL_TRIANGLES, 0, 36);
        /*
        // second transformation
        // ---------------------
        transform = glm::mat4(1.0f); // reset it to identity matrix
        transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));//���Ͻ�
        float scaleAmount = sin(glfwGetTime());
        transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));//���sin�ﵽ��������
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]); // this time take the matrix value array's first element as its memory pointer value

        // now with the uniform matrix being replaced with new transformations, draw it again.
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        */
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);//������ɫ����
        glfwPollEvents();//�����û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    //glDeleteBuffers(1,&EBO);
    //glDeleteProgram(shaderProgram);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate(); //����Ⱦѭ��������������Ҫ��ȷ�ͷ� / ɾ��֮ǰ�ķ����������Դ
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//��Ҫһ�������Լ�һ��������Ϊ���롣����������᷵����������Ƿ����ڱ�����
        glfwSetWindowShouldClose(window, true);
    float cameraSpeed = 2.5 * deltaTime;
    if (glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * glm::normalize(glm::cross(cameraFront,cameraUp));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
//���û��ı䴰�ڵĴ�С��ʱ���ӿ�ҲӦ�ñ����������ǿ��ԶԴ���ע��һ���ص�����(Callback Function)��������ÿ�δ��ڴ�С��������ʱ�򱻵���
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window,double xpos,double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw += xoffset;
    pitch += yoffset;
    if (pitch>89.0f) {
        pitch = 89.0f;
    }
    if (pitch<-89.0f) {
        pitch = -89.0f;
    }
    glm::vec3 front;
    front.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}
void scroll_callback(GLFWwindow* window,double xoffset,double yoffset) {
    fov -= (float)yoffset;
    if (fov<1.0f) {
        fov = 1.0f;
    }
    if (fov>45.0f) {
        fov = 45.0f;
    }
}