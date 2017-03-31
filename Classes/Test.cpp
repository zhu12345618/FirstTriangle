//
//  Test.cpp
//  FirstTriangle
//
//  Created by zhufu on 2017/3/27.
//
//

#include "Test.h"

Test* Test::create()
{
    Test* test = new(std::nothrow) Test();
    if(test && test->init())
    {
        test->autorelease();
        return test;
    }
    else
    {
        delete test;
        test = nullptr;
        return nullptr;
    }
}

bool Test::init()
{
    _glProgram = new GLProgram();
    _glProgram->initWithFilenames("shader/myVertexShader.vsh", "shader/myFragmentShader.fsh");
    _glProgram->link();
    //set uniform locations
    //使用此shader
    _glProgram->use();
    
    
    
    GLuint vertexVBO, colorVBO;
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    
    //创建和绑定vbo
    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    
    GLfloat vertexData[] = {
        //  X     Y     Z
        0.0f, 1.0f, 0.0f,
        -1.0f,-1.0f, 0.0f,
        1.0f,-1.0f, 0.0f,
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    
    //获取vertex attribute "a_position"的入口点
    GLuint positionLocation = glGetAttribLocation(_glProgram->getProgram(), "a_position");
    //打开入a_position入口点
    glEnableVertexAttribArray(positionLocation);
    //传递顶点数据给a_position，注意最后一个参数是数组的偏移了。
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    
    //set for color
    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    float color[] = {0,1,0,1,  1,0,0,1,  0,0,1,1};
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    
    GLuint colorLocation = glGetAttribLocation(_glProgram->getProgram(), "a_color");
    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    
    
    
    return true;
}

void Test::draw(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    _command.init(_globalZOrder);
    _command.func = CC_CALLBACK_0(Test::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_command);
}

void Test::onDraw()
{
    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT);
    
    // bind the program (the shaders)
    glUseProgram(_glProgram->getProgram());
    // bind the VAO (the triangle)
    glBindVertexArray(_vao);
    
    // draw the VAO
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // unbind the VAO
    glBindVertexArray(0);
    
    // unbind the program
    glUseProgram(0);
}
