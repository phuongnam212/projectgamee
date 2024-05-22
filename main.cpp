#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string.h>
#include "RenderWindows.h"
#include "Entity.h"
#include "ball.h"
#include "Tile.h"
#include "hole.h"
#include "Wind.h"
using namespace std;
//
RenderWindows window("dangphuongnam", 640, 480);
Mix_Music* backgroundmusic = NULL;
Wind wind200,wind300;
vector<InfoWind> windList;
vector<SDL_Rect> windRectList;
// Khai báo và khởi tạo vector của Wind
vector<Wind> winds(10);
void setupWinds()
{
    winds[0] = wind200;
    winds[0].setSpeedScroll(70);
    winds[4] = wind200;
    winds[4].setSpeedScroll(70);
    winds[1] = wind300;
    winds[1].setSpeedScroll(70);
    winds[5] = wind300;
    winds[5].setSpeedScroll(70);
    winds[2] = wind200;
    winds[2].setSpeedScroll(140);
    winds[6] = wind200;
    winds[6].setSpeedScroll(140);
    winds[3] = wind300;
    winds[3].setSpeedScroll(140);
    winds[7] = wind300;
    winds[7].setSpeedScroll(140);
    winds[8] = wind200;
    winds[8].setSpeedScroll(70);
    winds[9] = wind200;
    winds[9].setSpeedScroll(70);

}

bool init()
{
    // Khởi tạo SDL, kiểm tra lỗi
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << endl;
        return false;
    }

    // Khởi tạo hỗ trợ hình ảnh PNG, kiểm tra lỗi
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cout << "IMG_init has failed. Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return false;
    }
    // Khởi tạo hỗ trợ font chữ, kiểm tra lỗi
    if (TTF_Init() == -1) {
        cout << "TTF_init has failed. Error: " << SDL_GetError() << endl;
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    // Khởi tạo hệ thống âm thanh, kiểm tra lỗi
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "Mix_OpenAudio has failed. Error: " << Mix_GetError() << endl;
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return false;
    }
    backgroundmusic = Mix_LoadMUS("res/sfx/bgmusic.mp3");
    if (backgroundmusic == nullptr) {
        cout << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << endl;
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return false;
    }
    // Nếu tất cả các thành phần khởi tạo thành công, trả về true
    return true;
}


bool SDLinit = init();

SDL_Renderer*renderer=window.getrender();
SDL_Texture* ballTexture = window.loadTexture("res/gfx/ball.png");
SDL_Texture* holeTexture = window.loadTexture("res/gfx/hole.png");
SDL_Texture* pointTexture = window.loadTexture("res/gfx/point.png");
SDL_Texture* tileDarkTexture32 = window.loadTexture("res/gfx/tile32_dark.png");
SDL_Texture* tileDarkTexture64 = window.loadTexture("res/gfx/tile64_dark.png");
SDL_Texture* tileLightTexture32 = window.loadTexture("res/gfx/tile32_light.png");
SDL_Texture* tileLightTexture64 = window.loadTexture("res/gfx/tile64_light.png");
SDL_Texture* ballShadowTexture = window.loadTexture("res/gfx/ball_shadow.png");
SDL_Texture* bgTexture = window.loadTexture("res/gfx/bgg.png");
SDL_Texture* uiBgTexture = window.loadTexture("res/gfx/UI_bg.png");
SDL_Texture* levelTextBgTexture = window.loadTexture("res/gfx/levelText_bg.png");
SDL_Texture* powerMeterTexture_FG = window.loadTexture("res/gfx/thay.png");
SDL_Texture* powerMeterTexture_BG = window.loadTexture("res/gfx/powermeter_bg.png");
SDL_Texture* powerMeterTexture_overlay = window.loadTexture("res/gfx/powermeter_overlay.png");
SDL_Texture* logoTexture = window.loadTexture("res/gfx/m.png");
SDL_Texture* click2start = window.loadTexture("res/gfx/click2start.png");
SDL_Texture* endscreenOverlayTexture = window.loadTexture("res/gfx/end.png");
SDL_Texture* splashBgTexture = window.loadTexture("res/gfx/splashbg.png");

Mix_Chunk* chargeSfx = Mix_LoadWAV("res/sfx/charge.mp3");
Mix_Chunk* swingSfx = Mix_LoadWAV("res/sfx/swing.mp3");
Mix_Chunk* holeSfx = Mix_LoadWAV("res/sfx/hole.mp3");

SDL_Color white = { 255, 255, 255 };
SDL_Color black = { 0, 0, 0 };
TTF_Font* font32 = TTF_OpenFont("res/font/font.ttf", 32);
TTF_Font* font48 = TTF_OpenFont("res/font/font.ttf", 48);
TTF_Font* font24 = TTF_OpenFont("res/font/font.ttf", 24);

// Khai báo các đối tượng Wind
bool hasWind = false;
Ball balls[2] = {Ball(Vector2f(0, 0), ballTexture, pointTexture, powerMeterTexture_FG, powerMeterTexture_BG, 0), Ball(Vector2f(0, 0), ballTexture, pointTexture, powerMeterTexture_FG, powerMeterTexture_BG, 1)};
vector<Hole> holes = {Hole(Vector2f(0, 0), holeTexture), Hole(Vector2f(0, 0), holeTexture)};
// tao map cho cac van dau ,
vector<Tile> loadTiles(int level)
{
	std::vector<Tile> temp = {};
	switch(level)
	{
		case 0:
			temp.push_back(Tile(Vector2f(64*3, 64*3), tileDarkTexture64));
			temp.push_back(Tile(Vector2f(64*4, 64*3), tileDarkTexture64));
			temp.push_back(Tile(Vector2f(64*0, 64*3), tileDarkTexture64));
			temp.push_back(Tile(Vector2f(64*1, 64*3), tileDarkTexture64));

			temp.push_back(Tile(Vector2f(64*3 + 64*5, 64*3), tileLightTexture64));
			temp.push_back(Tile(Vector2f(64*4 + 64*5, 64*3), tileLightTexture64));
			temp.push_back(Tile(Vector2f(64*0 + 64*5, 64*3), tileLightTexture64));
			temp.push_back(Tile(Vector2f(64*1 + 64*5, 64*3), tileLightTexture64));
		break;
		case 1:
			temp.push_back(Tile(Vector2f(32*0, 64*4), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*1, 64*4), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*2, 64*4), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*3, 64*4), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*4, 64*4), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*5, 64*4), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*8, 64*4), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*9, 64*4), tileDarkTexture32));


			temp.push_back(Tile(Vector2f(32*10, 64*2), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*11, 64*2), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*12, 64*2), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*13, 64*2), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*14, 64*2), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*15, 64*2), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*16, 64*2), tileLightTexture32));



			temp.push_back(Tile(Vector2f(32*18, 64*5), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*19, 64*5), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*13, 64*5), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*14, 64*5), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*15, 64*5), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*16, 64*5), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*17, 64*5), tileLightTexture32));

		break;
		case 2:
		    temp.push_back(Tile(Vector2f(32*0, 64*3), tileDarkTexture32));
		    temp.push_back(Tile(Vector2f(32*1, 64*3), tileDarkTexture32));
		    temp.push_back(Tile(Vector2f(32*2, 64*3), tileDarkTexture32));
		    temp.push_back(Tile(Vector2f(32*3, 64*3), tileDarkTexture32));
		    temp.push_back(Tile(Vector2f(32*4, 64*3), tileDarkTexture32));
		    temp.push_back(Tile(Vector2f(32*4, 32*5), tileDarkTexture32));
		    temp.push_back(Tile(Vector2f(32*4, 32*4), tileDarkTexture32));
		    temp.push_back(Tile(Vector2f(32*4, 32*3), tileDarkTexture32));
            temp.push_back(Tile(Vector2f(32*4, 32*2), tileDarkTexture32));
            temp.push_back(Tile(Vector2f(32*5, 32*3), tileDarkTexture64));
            temp.push_back(Tile(Vector2f(32*8, 32*8), tileDarkTexture64));

			temp.push_back(Tile(Vector2f(32*14, 32*0), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*14, 32*1), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*14, 32*2), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*14, 32*3), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*14, 32*4), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*14, 32*5), tileLightTexture32));
            temp.push_back(Tile(Vector2f(32*17, 32*6), tileLightTexture32));
            temp.push_back(Tile(Vector2f(32*18, 32*6), tileLightTexture32));
            temp.push_back(Tile(Vector2f(32*19, 32*6), tileLightTexture32));
            temp.push_back(Tile(Vector2f(32*12, 32*8), tileLightTexture32));
            temp.push_back(Tile(Vector2f(32*13, 32*8), tileLightTexture32));
            temp.push_back(Tile(Vector2f(32*14, 32*8), tileLightTexture32));
            temp.push_back(Tile(Vector2f(32*18, 32*9), tileLightTexture64));






		break;
		case 3:
			temp.push_back(Tile(Vector2f(32*4, 32*7), tileDarkTexture64));
			temp.push_back(Tile(Vector2f(32*2, 32*4), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*2, 32*5), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*2, 32*6), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*2, 32*7), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*2, 32*8), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*3, 32*8), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*6, 32*8), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*7, 32*4), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*7, 32*5), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*7, 32*6), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*7, 32*7), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*7, 32*8), tileDarkTexture32));

			temp.push_back(Tile(Vector2f(32*10, 32*8), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*11, 32*8), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*12, 32*8), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*13, 32*8), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*14, 32*8), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*15, 32*10), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*15, 32*11), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*15, 32*12), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*15, 32*13), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*15, 32*14), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*18, 32*7), tileLightTexture64));
		break;
		case 4:
			temp.push_back(Tile(Vector2f(32*6, 32*2), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*7, 32*2), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*8, 32*2), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*9, 32*2), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*6, 32*10), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*7, 32*10), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*8, 32*10), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*9, 32*10), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*0, 32*6), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*1, 32*6), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*2, 32*6), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*3, 32*6), tileDarkTexture32));
			temp.push_back(Tile(Vector2f(32*0, 32*7), tileDarkTexture64));
			temp.push_back(Tile(Vector2f(32*8, 32*4), tileDarkTexture64));
			temp.push_back(Tile(Vector2f(32*8, 32*10), tileDarkTexture64));

			temp.push_back(Tile(Vector2f(32*14, 32*3), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*13, 32*3), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*12, 32*3), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*16, 32*5), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*16, 32*6), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*16, 32*7), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*13, 32*6), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*12, 32*7), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*11, 32*8), tileLightTexture32));
			temp.push_back(Tile(Vector2f(32*15, 32*3), tileLightTexture64));


		break;
	}
	return temp;
}


int level = 0;
vector<Tile> tiles = loadTiles(level);

bool gameRunning = false;
bool mouseDown = false;
bool mousePressed = false;

bool swingPlayed = false;
bool secondSwingPlayed = false;


SDL_Event event;

int state = 0; //0 = title screen, 1 = game, 2 = end screen

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;

void loadLevel(int level)
{
	if (level > 4)
	{
		state = 2;
		return;
	}
	balls[0].setVelocity(0, 0);
	balls[1].setVelocity(0,0);
    balls[0].setScale(1, 1);
	balls[1].setScale(1, 1);
	balls[0].setWin(false);
	balls[1].setWin(false);

	tiles = loadTiles(level);

	windList.clear();
    windRectList.clear();

    //setupWinds();
    switch(level)
    {
        case 0:

             hasWind=false;
            break;
        case 1:
              hasWind=false;
            break;
        case 2:
             setupWinds();
             hasWind=true;
             windRectList.resize(2);
             windList.resize(2);
             windList[0]= InfoWind {32*11,32*6,8};
             windRectList[0]={32*11,32*6,150,64};
             windList[1]= InfoWind {32*12,32*10,0};
             windRectList[1]={32*12,32*10,150,64};

            break;
        case 3:
             setupWinds();
             hasWind=true;
             windRectList.resize(4);
             windList.resize(4);
             windList[0]= InfoWind {20,0,8};
             windRectList[0]={10,0,150,64};
             windList[1]= InfoWind {150,0,4};
             windRectList[1]={150,0,150,64};
             windList[2]= InfoWind {320+20,32*4,4};
             windRectList[2]={320+20,32*4,150,64};
             windList[3]= InfoWind {640-170,32*4,8};
             windRectList[3]={640-170,32*4,150,64};
            break;
        case 4:
            setupWinds();
             hasWind=true;
             windRectList.resize(5);
             windList.resize(5);
             windList[0]= InfoWind {32*1,32*2,0};
             windRectList[0]={32*1,32*2,150,64};
             windList[1]= InfoWind {32*4,32*6,9};
             windRectList[1]={32*4,32*6,150,64};
             windList[2]= InfoWind {32*1,32*10,0};
             windRectList[2]={32*1,32*10,150,64};
             windList[3]= InfoWind {32*11,32*0,4};
             windRectList[3]={32*11,32*0,150,64};
             windList[4]= InfoWind {32*13,32*9,9};
             windRectList[4]={32*13,32*9,150,64};
    }

	switch (level)
	{
		case 0:
			balls[0].setPos( 24+ 32*4, 24 + 32*11);
			balls[1].setPos(24 + 32*4 + 32*10, 24 + 32*11);

			holes.at(0).setPos(24 + 32*4, 22 + 32*2);
			holes.at(1).setPos(24 + 32*4 + 32*10, 22 + 32*2);
		break;
		case 1:
			balls[0].setPos(24 + 32*4, 24 + 32*11);
			balls[1].setPos(24 + 32*4 + 32*10, 24 + 32*11);

			holes.at(0).setPos(24 + 32*4, 22 + 32*2);
			holes.at(1).setPos(24 + 32*4 + 32*10, 22 + 32*2);
		break;
		case 2:
			balls[0].setPos(32*2, 64*6);
			balls[1].setPos(32*18-6, 32*11);

			holes.at(0).setPos( 32*2, 6 + 32*4);
			holes.at(1).setPos(32*19, 6 + 32*3);
		break;
		case 3:
			balls[0].setPos(24 + 32*4,32*13);
			balls[1].setPos(64*5+32*2,32*2);

			holes.at(0).setPos(24 + 32*4,24 + 32*5);
			holes.at(1).setPos(64*5+32*3,32*12);
		break;
		case 4:
			balls[0].setPos(32*5,32*12);
			balls[1].setPos( 32*18+5,32*1);

			holes.at(0).setPos(32*7,32*1);
			holes.at(1).setPos(32*15,32*5-8);
		break;
	}

}

const char* getStrokeText()
{
	int biggestStroke = 0;
	if (balls[1].getStrokes() > balls[0].getStrokes())
	{
		biggestStroke = balls[1].getStrokes();
	}
	else
	{
		biggestStroke = balls[0].getStrokes();
	}
	std::string s = std::to_string(biggestStroke);
	s = "STOKES: " + s;
	return s.c_str();
}

const char* getLevelText(int side)
{
	int tempLevel = (level + 1)*2-1;
	if (side == 1)
	{
		tempLevel++;
	}
	string s = to_string(tempLevel);
	s = "HOLE: " + s;
	return s.c_str();
}

void update()
{

	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = (double)((currentTick - lastTick)*1000 / (double)SDL_GetPerformanceFrequency() );
	mousePressed = false;

	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			gameRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = true;
				mousePressed = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = false;
			}
			break;
		}
	}

	if (state == 1)
	{
		for (Ball& b : balls)
		{
			b.update(deltaTime, mouseDown, mousePressed, tiles, holes,windRectList,windList, chargeSfx, swingSfx, holeSfx,hasWind);
		}
		if (balls[0].getScale().x < -1 && balls[1].getScale().x < -1)
 		{
        	level++;
			loadLevel(level);
    	}
	}
}

void graphics()
{
    Wind wind;
	window.clear();
	window.render(0, 0, bgTexture);

	if (!windList.empty()) {
     wind.renderWinds(renderer, winds, windList);
    }
	// ve cac doi tuong lo
	for (Hole& h : holes)
	{
		window.render(h);
	}
    for (Tile& t : tiles)
	{
		window.render(t);
	}

	//Xu ly va ve cac qua bong
	for (Ball& b : balls)
	{
		if (!b.isWin())
		{
			window.render(b.getPos().x, b.getPos().y + 5, ballShadowTexture); // ve bong cua qua bong
		}
		// ve bong
		for (Entity& e : b.getPoints())
		{
			window.render(e);
		}
		window.render(b);
	}

	for (Ball& b : balls)
	{
		for (Entity& e : b.getPowerBar())
		{
			window.render(e);
		}
		window.render(b.getPowerBar().at(0).getPos().x, b.getPowerBar().at(0).getPos().y, powerMeterTexture_overlay);

	}
	// kiem tra trang thai va thong tin hien thi
	if (state != 2)
	{
		window.render(640/4 - 132/2, 480 - 32, levelTextBgTexture);
		window.renderCenter(-160, 240 - 16 + 3, getLevelText(0), font24, black);
		window.renderCenter(-160, 240 - 16, getLevelText(0), font24, white);

		window.render(640/2 + 640/4 - 132/2, 480 - 32, levelTextBgTexture);
		window.renderCenter(160, 240 - 16 + 3, getLevelText(1), font24, black);
		window.renderCenter(160, 240 - 16, getLevelText(1), font24, white);

		window.render(640/2 - 196/2, 0, uiBgTexture);
		window.renderCenter(0, -240 + 16 + 3, getStrokeText(), font24, black);
		window.renderCenter(0, -240 + 16, getStrokeText(), font24, white);
	}
	else
	{
		window.render(0, 0, endscreenOverlayTexture);
		window.renderCenter(0, 3 - 32, "YOU COMPLETED THE COURSE!", font48, black);
		window.renderCenter(0, -32, "YOU COMPLETED THE COURSE!", font48, white);
		window.renderCenter(0, 3 + 32, getStrokeText(), font32, black);
		window.renderCenter(0, 32, getStrokeText(), font32, white);
	}
	window.display();
}

void titleScreen()
{
	if (SDL_GetTicks() < 2000)
	{
	    // phat am thanh
		if (!swingPlayed)
		{
			Mix_PlayChannel(-1, swingSfx, 0);
			swingPlayed = true;
		}
		//Get our controls and events
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;
			}
		}

		window.clear();
		window.render(0, 0, bgTexture);
		window.render(0, 0, splashBgTexture);
		window.renderCenter(0, 0 - 3, "", font32, black);
		window.renderCenter(0, 0, "POLYMARS", font32, white);
		window.display();
	}
	else
	{
		if (!secondSwingPlayed)
		{
			Mix_PlayChannel(-1, swingSfx, 0);
			secondSwingPlayed = true;
		}
		lastTick = currentTick;
		currentTick = SDL_GetPerformanceCounter();
		deltaTime = (double)((currentTick - lastTick)*1000 / (double)SDL_GetPerformanceFrequency() );

		//Get our controls and events
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					Mix_PlayChannel(-1, holeSfx, 0);
					state = 1;
				}
				break;
			}
		}
		window.clear();
		window.render(0, 0, bgTexture);
		window.render(320 - 160, 240 - 100 - 50 + 4*SDL_sin(SDL_GetTicks()*(3.14/1500)), logoTexture);
		window.render(0, 0, click2start);
		window.renderCenter(0, 240 - 48 + 3 - 16*5, "LEFT CLICK TO START", font32, black);
		window.renderCenter(0, 240 - 48 - 16*5, "LEFT CLICK TO START", font32, white);
		window.display();
	}
}
void game()
{
	if (state == 0)
	{
		titleScreen();
	}
	else
	{
		update();
		graphics();
	}
}

int main(int argc, char* args[]) {

    if (!window.init()) {
        std::cerr << "Failed to initialize the window or SDL components." << std::endl;
        return -1;
    }

    if (Mix_PlayMusic(backgroundmusic,-1)==-1)
    {
    cout << "Mix_PlayMusic :" << Mix_GetError() <<endl;
    }

    //load wind
    wind200.loadFromFile(renderer,"res/gfx/wind.png");
    wind300.loadFromFile(renderer,"res/gfx/wind300.png");
    // Định nghĩa các tùy chọn cho menu
    bool quit = false;
    while (!quit){
    std::vector<std::string> menuItems = {"Play Game", "Rules", "Exit"};

    // Hiển thị menu và lấy kết quả lựa chọn từ người dùng
    int selectedOption = window.showMenu(menuItems);
    switch (selectedOption) {
        case 0:  // Play Game
            gameRunning = true;
            loadLevel(level);
            while (gameRunning) {
                game();
            }
            break;
        case 1:
            window.showRules(window);
            selectedOption = window.showMenu(menuItems);
            break;
        case 2:
            gameRunning = false;
            quit=true;
            exit(1);
            break;
        default:
            // Trường hợp không hợp lệ hoặc khi người dùng đóng cửa sổ menu
            gameRunning = false;


            break;
    }
}
    // Dọn dẹp khi game kết thúc
  window.cleanUp();
  Mix_FreeMusic(backgroundmusic);
TTF_CloseFont(font32);
TTF_CloseFont(font24);
SDL_Quit();
TTF_Quit();
    return 0;
}
