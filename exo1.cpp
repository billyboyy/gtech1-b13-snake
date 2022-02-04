#include "exo1.hpp"
#include "MainSDLWindow.hpp"
#include "MainSDLWindow.cpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#define FPSLimit 122

SDL_Window *gWindow = NULL;

SDL_Renderer *renderer = NULL;

SDL_Surface *gScreenSurface = NULL;

SDL_Surface *gHelloWorld = NULL;

SDL_Rect r;

char e;

void speed(unsigned int limit)
{
  unsigned int ticks = SDL_GetTicks();
  if (limit < ticks)
    return;
  else if (limit > ticks + FPSLimit)
    SDL_Delay(FPSLimit);
  else
    SDL_Delay(limit - ticks);
}

SDL_bool init()
{
  SDL_bool success = SDL_TRUE;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = SDL_FALSE;
  }
  else
  {
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 500, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = SDL_FALSE;
    }
    else
    {
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }

  return success;
}

void close()
{
  SDL_FreeSurface(gHelloWorld);
  gHelloWorld = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  SDL_Quit();
}

void snake()
{
  renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

  SDL_RenderClear(renderer);

  r.x = 20;
  r.y = 20;
  r.w = 20;
  r.h = 20;

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  SDL_RenderFillRect(renderer, &r);

  SDL_RenderPresent(renderer);
}

void move()
{
  SDL_bool running = SDL_TRUE;
  while (running)
  {
    unsigned int frame_limit = SDL_GetTicks() + FPSLimit;
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {

      case SDL_QUIT:
        running = SDL_FALSE;
        break;

      case SDL_KEYDOWN:
        switch (event.key.keysym.scancode)
        {
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:
          e = 'U';
          break;
        case SDL_SCANCODE_A:
        case SDL_SCANCODE_LEFT:
          e = 'L';
          break;
        case SDL_SCANCODE_S:
        case SDL_SCANCODE_DOWN:
          e = 'D';
          break;
        case SDL_SCANCODE_D:
        case SDL_SCANCODE_RIGHT:
          e = 'R';
          break;
        default:
          break;
        }
      }
    }
    switch (e)
    {
    case 'U':
      r.y -= 20;
      break;
    case 'L':
      r.x -= 20;
      break;
    case 'D':
      r.y += 20;
      break;
    case 'R':
      r.x += 20;
      break;

    default:
      break;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &r);
    SDL_RenderPresent(renderer);
    speed(frame_limit);
  }
}

void ReplaceFood()
{
    int x, y;
    Block grid[800][500];
    SDL_Point food;
    while (true)
    {
        x = rand() % 800;
        y = rand() % 500;

        if (grid[x][y] == Block::empty)
        {
            grid[x][y] = Block::food;
            food.x = x;
            food.y = y;
            break;
        }
    }
}

int main()
{
  if (!init())
  {
    printf("Failed to initialize!\n");
  }
  else
  {
    snake();
    move();
  }
  close();
  return 0;
}