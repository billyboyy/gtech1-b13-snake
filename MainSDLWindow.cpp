#include <SDL2/SDL.h>
#include "MainSDLWindow.hpp"

MainSDLWindow::MainSDLWindow()
{
    this->window = NULL;
    this->renderer = NULL;
}

MainSDLWindow::~MainSDLWindow()
{
    if (this->renderer != NULL)
        SDL_DestroyRenderer(this->renderer);
    if (this->window != NULL)
        SDL_DestroyWindow(this->window);
}

int MainSDLWindow::Init(const char *title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_Log("ERREUR: %s> %s\n", "quit", SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
    this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    
    if (this->window == NULL)
        SDL_Log("ERREUR: %s> %s\n","quit", SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_SOFTWARE);
    
    if (this->renderer == NULL)
        SDL_Log("ERREUR: %s> %s\n","quit", SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);

    return 0;
}