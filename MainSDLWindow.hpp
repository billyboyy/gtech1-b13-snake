#ifndef MAINSDLWINDOW_HPP
#define MAINSDLWINDOW_HPP

#include <stdio.h>
#include <SDL2/SDL.h>

class MainSDLWindow
{
public:
    MainSDLWindow(void);
    ~MainSDLWindow(void);
    int Init(const char *title, int width, int height);
    SDL_Renderer *GetRenderer(void);

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};
#endif