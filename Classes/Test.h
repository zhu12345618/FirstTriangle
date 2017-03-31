//
//  Test.h
//  FirstTriangle
//
//  Created by zhufu on 2017/3/27.
//
//

#ifndef Test_h
#define Test_h

#include <stdio.h>
USING_NS_CC;
class Test : public Node
{
public:
    GLuint _program = 0;
    virtual bool init() override;
    static Test* create();
    virtual void draw(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) override;
    void onDraw();
    
    cocos2d::CustomCommand _command;
    GLProgram* _glProgram;
    
    GLuint _vao = 0;
    GLuint _vertexVBO = 0;
    GLuint _colorVBO = 0;
};

#endif /* Test_h */
