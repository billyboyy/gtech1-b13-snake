#include "main.hpp"
#include "MainSDLWindow.hpp"
#include "MainSDLWindow.cpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <time.h>

#define FRAME_RATE_MS 122
#define height 500
#define with 400

SDL_Window *gWindow = NULL;

SDL_Renderer *renderer = NULL;

SDL_Surface *gScreenSurface = NULL;

SDL_Surface *gHelloWorld = NULL;

SDL_Rect r;

SDL_Rect f;

char e;
int top;
int bot;

void speed(unsigned int frame_start)
{
  Uint32 duration = SDL_GetTicks() - frame_start;
  if (duration < FRAME_RATE_MS) SDL_Delay(FRAME_RATE_MS - duration);

  // if (frame_start < ticks)
  //   return;
  // else if (frame_start > ticks + FRAME_RATE_MS)
  //   SDL_Delay(FRAME_RATE_MS);
  // else
  //   SDL_Delay(frame_start - ticks);
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
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, height, with, SDL_WINDOW_SHOWN);
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

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);

  r.x = 20;
  r.y = 20;
  r.w = 20;
  r.h = 20;
}

void Food()
{
  srand(time(NULL));
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderClear(renderer);

  f.w = 20;
  f.h = 20;
  bot = rand() % 20;
  top = rand() % 25;
  f.x = top*20;
  f.y = bot*20;
}

void move()
{
  SDL_bool running = SDL_TRUE;
  while (running)
  {
    Uint32 frame_start = SDL_GetTicks();
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &f);
    SDL_RenderPresent(renderer);
    speed(frame_start);
  }
}

int main()
{
  if (!init())
  {
    printf("Failed to initialize!\n");
    exit(EXIT_FAILURE);
  }

  snake();
  Food();
  move();

  close();
  return 0;
}