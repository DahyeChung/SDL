#define SDL_MAIN_HANDLED
#include "SDL.h"

int main()
{   //Start an SDL Program
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* pWindow = SDL_CreateWindow("Dahye's Game",
		100, 100, //Display x,y pixel position 우측 100 높이 100에 창 만들기
		680, 480, //Pixel width * height 넓이와 높이 지정
		SDL_WINDOW_SHOWN); // 윈도우 보여줘~! 

	SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//BG img
	SDL_Surface* pBmp = SDL_LoadBMP("door.bmp");
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pBmp);
	SDL_FreeSurface(pBmp); //delete bmp ;

	//Enemy img
	SDL_Surface* pBmp2 = SDL_LoadBMP("skeleton.bmp");
	SDL_SetColorKey(pBmp2, SDL_TRUE, SDL_MapRGB(pBmp2->format, 0, 255, 0)); //RGB 삭제할 배경색 <nullptr>
	SDL_Texture* pTexture2 = SDL_CreateTextureFromSurface(pRenderer, pBmp2);
	SDL_FreeSurface(pBmp2); //delete bmp ;

	
	bool movingUp = true;
	int enemyX = 200;
	int enemyY = 500;

	//게임오버 까지 대기 
	bool isDone = false;

	//게임이 끝난게 아니라면
	while (!isDone)
	{
		//Get Input 
		{
			SDL_Event e = {}; //Create message pump
			while (SDL_PollEvent(&e) != 0) //Get events from the operating system
			{
				//Clicked the red X
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
		}

		//UpdatGame
		{
			if (movingUp) //해골 애니메이션
			{
				enemyY--; //y축 감소 == 다운 
				if (enemyY < 302) // 최저 위치 도달 시 
				{
					movingUp = false; //다시 업 
				}
			}
			else
			{
				enemyY++; //y축 증가 == 업
				if (enemyY < 500) // 최고 위치 도달 시 
				{
					movingUp = true; //다시 다운 
				}
			}
		}

		//RenderGame
		{
			SDL_RenderClear(pRenderer); //paint black

			//Draw background
			{
				SDL_Rect srcRect = { 0, 0, 680, 480, }; //사용이미지 픽셀
				SDL_Rect destRect = { 0,0, 680, 480, }; //윈도우 창 크기 
				SDL_RenderCopy(pRenderer, pTexture, &srcRect, &destRect);
			}

			//Draw enemy
			{
				SDL_Rect srcRect2 = { 0, 0, 673, 792 }; //사용이미지 픽셀
				SDL_Rect destRect2 = { enemyX, enemyY, 673, 792 }; // 윈도우 창 크기 
				SDL_RenderCopy(pRenderer, pTexture2, &srcRect2, &destRect2);
			}
			SDL_RenderPresent(pRenderer); // actual img display
		}



		
	}

	// Clean up resources
	SDL_DestroyTexture(pTexture);
	SDL_DestroyTexture(pTexture2);
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit();

	return 0;
}