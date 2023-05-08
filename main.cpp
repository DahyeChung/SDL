#define SDL_MAIN_HANDLED
#include "SDL.h"

int main()
{	//Start an SDL Program
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* pWindow = SDL_CreateWindow("Dahye's Game",
											100, 100, //Display x,y pixel position 우측 100 높이 100에 창 만들기
											640, 480, //Pixel width * height 넓이와 높이 지정
											SDL_WINDOW_SHOWN); // 윈도우 보여줘~! 

	SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1,
							SDL_RENDERER_ACCELERATED 
						||  SDL_RENDERER_PRESENTVSYNC);

	SDL_Surface* pBmp = SDL_LoadBMP("door.bmp");
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pBmp);
	SDL_FreeSurface(pBmp); //delete bmp ;


	//게임오버 까지 대기 
	bool isDone = false;

	//게임이 끝난게 아니라면
	while (!isDone)
	{
		//Create message pump
		SDL_Event e = {};
		//Get events from the operating system
		while (SDL_PollEvent(&e) != 0)
		{
			//Clicked the red X
			if (e.type == SDL_QUIT)
			{
				isDone == true;
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
		SDL_RenderClear(pRenderer); //paint black

		//Draw background
		{
			SDL_Rect srcRect = { 0, 0, 1280, 720 }; //사용이미지 픽셀
			SDL_Rect destRect = { 0,0, 1280, 720 }; //윈도우 창 크기 
			SDL_RenderCopy(pRenderer, pTexture, &srcRect, &destRect);
		}

		SDL_RenderPresent(pRenderer); //actual img display
	}


	SDL_DestroyTexture(pTexture);

	SDL_DestroyRenderer(pRenderer); //렌더시키고
	SDL_DestroyWindow(pWindow); //삭제시
	SDL_Quit;//Quit an SDL Program
	return 0;
}