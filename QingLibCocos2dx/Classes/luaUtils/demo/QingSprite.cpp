//
//  QingSprite.cpp
//  QingLibCocos2dxLua
//
//  Created by Kevin Geng on 14-3-13.
//
//

#include "QingSprite.h"

USING_NS_QING;


QingSprite* QingSprite::createQingSprite(const char* name)
{
    CCLOG("img:%s", name);
    QingSprite* sp = new QingSprite();
    if(sp && sp->initWithFile(name)){
        sp->sayHello("create Ok!");
        sp->autorelease();
        return sp;
    }
    CC_SAFE_DELETE(sp);
    return NULL;
}

void QingSprite::sayHello(const char *str)
{
    CCMessageBox(str, "Hello from QingSprite");
}