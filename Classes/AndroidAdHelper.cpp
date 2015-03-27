//
//  AndroidAdHelper.cpp
//  SQ
//
//  Created by David Villarreal on 3/26/15.
//
//

#if  CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "AndroidAdHelper.h"
#include "platform/android/jni/JniHelper.h" //vem do projeto principal - pasta cocos2dx
#include <jni.h>

USING_NS_CC;

const char* AppActivityClassName = "org/cocos2dx/cpp/AppActivity";

void AndroidAdHelper::showAd(){
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, AppActivityClassName, "showAd", "()V"))
    {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        
    }
}

#endif