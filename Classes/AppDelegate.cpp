#include "AppDelegate.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
    
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    controller = new MainController();
    
    
    
    controller->begin();
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    controller->pause();
    CCLOG("paused");
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    controller->resume();
}


