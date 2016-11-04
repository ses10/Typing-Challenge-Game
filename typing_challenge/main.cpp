//
//  main.cpp
//  typing_challenge
//
//  Created by Dennis on 11/4/16.
//  Copyright © 2016 All rights reserved.
//


#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int MAX_CHAR = 26;

//globals
SDL_Window* mWindow = NULL;
SDL_Surface* mScreenSurface = NULL;

//holds surfaces containing a character a-z
SDL_Surface* charSurfaces [MAX_CHAR];

bool init();
bool loadImages();
SDL_Surface* loadSurface(std::string path);
void close();

//initialize SDl
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		mWindow = SDL_CreateWindow( "Typing Challenge", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( mWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			mScreenSurface = SDL_GetWindowSurface( mWindow );
		}
	}

	return success;
}

bool loadImages()
{
    int a_ascii = 97;
    int z_ascii = 122;

    for(int i = a_ascii; i <= z_ascii; i++)
    {
        std::string path = "img/";
        path += (char)i;
        path += ".png";
        
        charSurfaces[i-a_ascii] = loadSurface(path);
    }

    return false;
}

SDL_Surface* loadSurface( std::string path )
{
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}

	return loadedSurface;
}

//check whether key pressed is the current char on window
bool checkKeyPress(int curSurface, int keySym)
{
    if(curSurface == (keySym - 'a'))
        return true;
    
    return false;
}

void close()
{
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}


int main(int argc, const char * argv[]) {
    
    srand(time(0));
    bool quit = false;
    bool correctKey = false;
    int curChar = rand() % MAX_CHAR;
    
    init();
    
    loadImages();
    
    SDL_Event e;
    
    while(!quit)
    {
    
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                if(checkKeyPress(curChar, e.key.keysym.sym))
                    correctKey = true;
            }
            
        }
        
        if(correctKey)
        {
            curChar = rand() % MAX_CHAR;
            correctKey = false;
        }
        
        //load a character on screen
        SDL_BlitSurface(charSurfaces[curChar], NULL, mScreenSurface, NULL);
        SDL_UpdateWindowSurface(mWindow);
    }
    
    close();
    return 0;
}
