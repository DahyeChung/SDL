#define SDL_MAIN_HANDLED
#include "SDL.h"

int main()
{
    //Start an SDL Program
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* pWindow = SDL_CreateWindow("Dahye's Game",
        100, 100, //Display x,y pixel position 
        1280, 720, //Pixel width * height 
        SDL_WINDOW_SHOWN); // Show the window

    SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Load background image
    SDL_Surface* pBmp = SDL_LoadBMP("door.bmp");
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pBmp);
    SDL_FreeSurface(pBmp); //delete bmp ;

    // Load enemy image
    SDL_Surface* pBmp2 = SDL_LoadBMP("skeleton.bmp");
    SDL_SetColorKey(pBmp2, SDL_TRUE, SDL_MapRGB(pBmp2->format, 0, 255, 0)); //RGB 삭제할 배경색 <nullptr>
    SDL_Texture* pTexture2 = SDL_CreateTextureFromSurface(pRenderer, pBmp2);
    SDL_FreeSurface(pBmp2); //delete bmp ;

    // Set initial state of enemy
    bool movingLeft = true;
    int enemyX = 200;
    int enemyY = 500;
    int enemyMinX = 400;
    int enemyMaxX = 450;

    // Wait until game over
    bool isDone = false;

    while (!isDone)
    {
        // Get Input 
        SDL_Event e = {};
        while (SDL_PollEvent(&e) != 0)
        {
            // Clicked the red X
            if (e.type == SDL_QUIT)
            {
                isDone = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                auto KeyCode = e.key.keysym.sym;

                switch (KeyCode)
                {
                case SDLK_ESCAPE: //esc -> quit 
                    isDone = true;
                    break;
                }
            }
        }

        // Update Game
        if (movingLeft) // Move enemy left
        {
            enemyX--; //x-axis decrease
            if (enemyX < enemyMinX) // reached the left limit
            {
                movingLeft = false; // move right
            }
        }
        else // Move enemy right
        {
            enemyX++; //x-axis increase
            if (enemyX > enemyMaxX) // reached the right limit
            {
                movingLeft = true; // move left
            }
        }

        // Render Game
        SDL_RenderClear(pRenderer); //paint black

        // Draw background
        SDL_Rect srcRect = { 0, 0, 1280, 720 }; //source image pixel
        SDL_Rect destRect = { 0,0, 1280, 720 }; //window size
        SDL_RenderCopy(pRenderer, pTexture, &srcRect, &destRect);

        // Draw enemy
        SDL_Rect srcRect2 = { 0, 0, 673, 792 }; //source image pixel
        SDL_Rect destRect2 = { enemyX, enemyY, 673, 792 }; // window size
        SDL_RenderCopy(pRenderer, pTexture2, &srcRect2, &destRect2);

        SDL_RenderPresent(pRenderer); // actual img display
    }
		
	

	// Clean up resources
	SDL_DestroyTexture(pTexture);
	SDL_DestroyTexture(pTexture2);
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit();

	return 0;
}