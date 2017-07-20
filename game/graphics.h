#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <vector>
#include <math.h>
#include <string>
//SDL & OpenGL
#include <GL/glu.h>
#include "sdl2/SDL.h"
#include "sdl2/SDL_opengl.h"
#include "sdl2/SDL_image.h"

class graphicsObject
{
public:
    void setX(float x1){x=x1;}
    void setY(float y1){y=y1;}
    void setWidth(float we){w=we;}
    void setHeight(float he){h=he;}
    void setAngle(double a){angle=a;}
    void setTexture(GLuint text){texture=text;}

    float getX(){return x;}
    float getY(){return y;}
    float getWidth(){return w;}
    float getHeight(){return h;}
    double getAngle(){return angle;}
    GLuint getTexture(){return texture;}
private:
    float x, y, w, h;
    double angle;
    GLuint texture;
};

class graphicsCamera{
public:
    graphicsCamera(float limx, float limy){limitx=limx;limity=limy;}
    void setX(float x1){if(x1+w>limitx) x=limitx-w; else if(x1<0) x=0; else x=x1;}
    void setY(float y1){if(y1+h>limity) y=limity-h; else if(y1<0) y=0; else y=y1;}
    void setWidth(float we){w=we;}
    void setHeight(float he){h=he;}
    void setLimitX(float x){limitx=x;}
    void setLimitY(float y){limity=y;}
    float getX(){return x;}
    float getY(){return y;}
    float getWidth(){return w;}
    float getHeight(){return h;}
    float getLimitX(){return limitx;}
    float getLimitY(){return limity;}
private:
    float limitx, limity, w, h, x, y;
};

class graphics
{
public:
    static graphics& Instance()
    {
            static graphics Single;
            return Single;
    }
    void setWindowWidth(int x){windowWidth = x;}
    int getWindowWidth(){return windowWidth;}
    void setWindowHeight(int x){windowHeight = x;}
    int getWindowHeight(){return windowHeight;}

    void glInit();

    void setCamera(graphicsCamera* cam){camera = cam; camera->setHeight( getWindowHeight()); camera->setWidth(getWindowWidth());}
    graphicsCamera* getCamera(){return camera;}
    GLuint loadTextureFromSurface(SDL_Surface* surface);

    void addObjectToScene(graphicsObject* object);
    void deleteObjFromScene(graphicsObject* object);
    void textureDestroy(GLuint id);
    void textureDestroyAll();
    void renderScene();
    void clearScene();

private:
    std::vector<graphicsObject*> scene;
    std::vector<GLuint> textures;
    graphicsCamera* camera;
    SDL_Window* sdlWindow = NULL;
    SDL_GLContext sdlGLContext;
    SDL_Event sdlEvents;
    int windowWidth=800, windowHeight=600;

};

#endif // GRAPHICS_H
