#include "graphics.h"

void graphics::glInit()
{
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    sdlWindow = SDL_CreateWindow("App",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    sdlGLContext = SDL_GL_CreateContext( sdlWindow );
    SDL_GL_SetSwapInterval( 1 );
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor( 0.f, 0.f, 0.f, 1.f );
}



GLuint graphics::loadTextureFromSurface(SDL_Surface* surf)
{
    GLuint tid;
    GLenum texture_format;
    GLint ncolors;
    SDL_Surface* s = surf;
    if(s == NULL){return 0;}
    /* Convert SDL_Surface to OpenGL Texture */
    ncolors = s->format->BytesPerPixel;
    if (ncolors == 4) {
        //alpha channel
        if (s->format->Rmask == 0x000000ff)
            texture_format = GL_RGBA;
        else
            texture_format = GL_BGRA;
    } else {
        if (ncolors == 3) {
            //no alpha channel
            if (s->format->Rmask == 0x000000ff)
                texture_format = GL_RGB;
            else
                texture_format = GL_BGR;
        } else {
            return 0;
        }
    }
    glGenTextures(1, &tid);
    glBindTexture(GL_TEXTURE_2D, tid);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, ncolors, s->w, s->h, 0, texture_format, GL_UNSIGNED_BYTE, s->pixels);
    textures.push_back(tid);
    return tid;
}



void graphics::textureDestroy(GLuint id)
{
    glDeleteTextures(1,&id);
}

void graphics::deleteObjFromScene(graphicsObject* object)
{
    std::vector<graphicsObject*>::iterator the_iterator;
    the_iterator = scene.begin();
    while(the_iterator != scene.end())
    {
        if(object==(*the_iterator)){scene.erase(the_iterator); continue;}
        the_iterator++;
    }
}

void graphics::clearScene()
{
    std::vector<graphicsObject*>::iterator the_iterator;
    the_iterator = scene.begin();
    while(the_iterator != scene.end())
    {
        scene.erase(the_iterator);
    }
}

void graphics::textureDestroyAll()
{
    std::vector<GLuint>::iterator the_iterator;
    the_iterator = textures.begin();
    while(the_iterator != textures.end())
    {
        textureDestroy(*the_iterator);
        ++the_iterator;
    }
}

void graphics::addObjectToScene(graphicsObject* obj)
{
    scene.push_back(obj);
}

void graphics::renderScene()
{
    float
        w, h, x, y, cx, cy,
        x1, x2, x3, x4, y1, y2, y3, y4;
    double a;
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    for(int i=0; i<scene.size(); i++)
    {
        w=scene[i]->getWidth(),h=scene[i]->getHeight(),
        x=scene[i]->getX(), y=scene[i]->getY(),
        cx=x+w/2, cy=y+h/2,
        a=scene[i]->getAngle();

        x1 = cx + (x - cx) * cos(a) - (y - cy) * sin(a);
        y1 = cy + (y - cy) * cos(a) + (x - cx) * sin(a);
        x2 = cx + (x + w - cx) * cos(a) - (y - cy) * sin(a);
        y2 = cy + (y - cy) * cos(a) + (x + w - cx) * sin(a);
        x3 = cx + (x + w - cx) * cos(a) - (y + h - cy) * sin(a);
        y3 = cy + (y + h - cy) * cos(a) + (x + w - cx) * sin(a);
        x4 = cx + (x - cx) * cos(a) - (y + h - cy) * sin(a);
        y4 = cy + (y + h - cy) * cos(a) + (x - cx) * sin(a);

        glBindTexture(GL_TEXTURE_2D, scene[i]->getTexture());
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x1-camera->getX(), y1-camera->getY());  // Bottom Left Of The Texture and Quad
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x2-camera->getX(), y2-camera->getY());  // Bottom Right Of The Texture and Quad
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x3-camera->getX(), y3-camera->getY());  // Top Right Of The Texture and Quad
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x4-camera->getX(), y4-camera->getY());  // Top Left Of The Texture and Quad
        glEnd();
    }
    SDL_GL_SwapWindow( sdlWindow );
}
