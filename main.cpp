#include "main.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <time.h>

#define FRAME_RATE_MS 122
#define height 500
#define width 400

SDL_Window *gWindow = NULL;

SDL_Renderer *renderer = NULL;

SDL_Surface *gScreenSurface = NULL;

SDL_Surface *gHelloWorld = NULL;

SDL_Rect r;
SDL_Rect f;
SDL_Rect m;

char e;
int top;
int bot;

void kill()
{
  SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
  SDL_RenderClear(renderer);

  m.w = 20;
  m.h = 20;
  bot = rand() % 40;
  top = rand() % 50;
  m.x = top * 20;
  m.y = bot * 20;
}

void speed(unsigned int frame_start)
{
  Uint32 duration = SDL_GetTicks() - frame_start;
  if (duration < FRAME_RATE_MS)
    SDL_Delay(FRAME_RATE_MS - duration);
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
    gWindow = SDL_CreateWindow("moi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, height, width, SDL_WINDOW_SHOWN);
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
  f.x = top * 20;
  f.y = bot * 20;
}

int collision()
{
  if (f.x == r.x && f.y == r.y)
  {
    Food();
    kill();
    return 0;
  }
  else if (r.x >= height || r.y >= width || r.x < 0 || r.y < 0 || m.x == r.x && m.y == r.y)
  {
    return -1;
  }
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
    if (collision() == -1)
      running = SDL_FALSE;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &r);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &f);
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderFillRect(renderer, &m);
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
  kill();
  move();

  close();
  return 0;
}