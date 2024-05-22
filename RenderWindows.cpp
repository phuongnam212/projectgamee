#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "RenderWindows.h"
#include "Entity.h"

bool RenderWindows::init() {
    if (!window || !renderer) {
        std::cerr << "Initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }
    if (TTF_Init() == -1) {
    std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
    return -1;
}
    return true;
}

RenderWindows::RenderWindows() {
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}


RenderWindows::RenderWindows(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

//
bool RenderWindows::loadFromFile( SDL_Renderer* gRenderer, std::string path ) {
    cleanUp();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    } else {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF ) );

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL ) {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        } else {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}


//
SDL_Texture* RenderWindows::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindows::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindows::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindows::render(Entity& p_entity)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getPos().x + (p_entity.getCurrentFrame().w - p_entity.getCurrentFrame().w*p_entity.getScale().x)/2;
	dst.y = p_entity.getPos().y + (p_entity.getCurrentFrame().h - p_entity.getCurrentFrame().h*p_entity.getScale().y)/2;
	dst.w = p_entity.getCurrentFrame().w*p_entity.getScale().x;
	dst.h = p_entity.getCurrentFrame().h*p_entity.getScale().y;

	SDL_RenderCopyEx(renderer, p_entity.getTex(), &src, &dst, p_entity.getAngle(), 0, SDL_FLIP_NONE);
}

void RenderWindows::render(int x, int y, SDL_Texture* p_tex)
{
	SDL_Rect src;
	src.x = 0;
	src. y = 0;
	src.w;
	src.h;

	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

void RenderWindows::render( SDL_Renderer* gRenderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip  ) {
    //Set rendering space and render to screen
    if(angle != 0) {
        mAngle = angle;
        std::cout<<angle<<'\n';
    }
    SDL_Rect renderQuad = { pos.x, pos.y, mWidth, mHeight };
    //Set clip rendering dimensions
    if( clip != NULL ) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    //Render to screen
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, mAngle, center, flip );
}
void RenderWindows::render( SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip  ) {
    //Set rendering space and render to screen
    if(angle != 0) {
        mAngle = angle;
    }
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    pos.x = x;
    pos.y = y;
    //Set clip rendering dimensions
    if( clip != NULL ) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    //Render to screen
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, mAngle, center, flip );
}





void RenderWindows::render(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
{
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended( font, p_text, textColor);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.w = surfaceMessage->w;
		src.h = surfaceMessage->h;

		SDL_Rect dst;
		dst.x = p_x;
		dst.y = p_y;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, message, &src, &dst);
		SDL_FreeSurface(surfaceMessage);
	 	SDL_DestroyTexture(message);
}

void RenderWindows::renderCenter(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
{
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended( font, p_text, textColor);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.w = surfaceMessage->w;
		src.h = surfaceMessage->h;

		SDL_Rect dst;
		dst.x = 640/2 - src.w/2 + p_x;
		dst.y = 480/2 - src.h/2 + p_y;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, message, &src, &dst);
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(message);
}

void RenderWindows::display()
{
	SDL_RenderPresent(renderer);
}
int RenderWindows::showMenu(const std::vector<std::string>& options) {
    int selectedOption = 0;
    bool quit = false;
    SDL_Event e;
    SDL_Texture* bgmu= loadTexture("res/gfx/bg.png");
    SDL_Texture* logoTexture = loadTexture("res/gfx/m.png");
    TTF_Font* menuFont = TTF_OpenFont("res/font/font.ttf", 28);
    if (!menuFont) {
        std::cerr << "Failed to load menu font: " << TTF_GetError() << std::endl;
        return -1;
    }

    SDL_Color textColor = {255, 255, 255};
    SDL_Color highlightColor = {173,216,230,255};


     std::vector<SDL_Rect> menuItemsRects(options.size());

    // Tính toán vị trí của mỗi tùy chọn menu
    int screenWidth = 640; // Chiều rộng cửa sổ
int startY = 240; // Vị trí Y ban đầu cho mục menu đầu tiên
int spacingY = 30; // Khoảng cách giữa các mục menu

// Lặp qua mỗi mục menu để tính toán vị trí
for (size_t i = 0; i < options.size(); ++i) {
    SDL_Surface* surface = TTF_RenderText_Blended(menuFont, options[i].c_str(), textColor);

    // Canh giữa mục menu theo chiều ngang
    int menuItemX = (screenWidth - surface->w) / 2;
    int menuItemY = startY + i * spacingY;

    // Cập nhật thông tin về kích thước và vị trí cho menuItemsRects
    menuItemsRects[i].x = menuItemX;
    menuItemsRects[i].y = menuItemY;
    menuItemsRects[i].w = surface->w;
    menuItemsRects[i].h = surface->h;

    SDL_FreeSurface(surface);
}

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
                selectedOption = -1;
            } else if (e.type == SDL_MOUSEMOTION) {
                for (size_t i = 0; i < options.size(); ++i) {
                    if (e.motion.x >= menuItemsRects[i].x && e.motion.x <= menuItemsRects[i].x + menuItemsRects[i].w &&
                        e.motion.y >= menuItemsRects[i].y && e.motion.y <= menuItemsRects[i].y + menuItemsRects[i].h) {
                        selectedOption = i;
                    }
                }
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    for (size_t i = 0; i< options.size(); ++i) {
                        if (e.button.x >= menuItemsRects[i].x && e.button.x <= menuItemsRects[i].x + menuItemsRects[i].w &&
                            e.button.y >= menuItemsRects[i].y && e.button.y <= menuItemsRects[i].y + menuItemsRects[i].h) {
                            selectedOption = i;
                            quit = true;
                            break;
                        }
                    }
                }
            }
        }

         // Clear the screen
        render(0,0,bgmu);
        render(320 - 160, 240 - 100 - 50 + 4*SDL_sin(SDL_GetTicks()*(3.14/1500)), logoTexture);
        // Render each menu option
        for (size_t i = 0; i < options.size(); ++i) {
            SDL_Color color = i == selectedOption ? highlightColor : textColor;
            renderCenter(0, 50 * i, options[i].c_str(), menuFont, color);
        }

        display(); // Update the screen
    }
    clear();
    TTF_CloseFont(menuFont);

    return selectedOption;
}
// trình diễn rule
void RenderWindows::showRules(RenderWindows &window) {
    bool showingRules = true;
    SDL_Event event;
    SDL_Rect backButton = { 640 / 2 - 50, 480 - 50, 100, 30 };

    // Tải hai ảnh cho nút "Back"
    SDL_Texture* backNormal = window.loadTexture("res/gfx/back_normal.png");
    SDL_Texture* backHover = window.loadTexture("res/gfx/back_hover.png");

    while (showingRules) {
        SDL_Point mousePos;
        SDL_GetMouseState(&mousePos.x, &mousePos.y);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    showingRules = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if (mousePos.x >= backButton.x && mousePos.x <= backButton.x + backButton.w &&
                            mousePos.y >= backButton.y && mousePos.y <= backButton.y + backButton.h) {
                            showingRules = false;
                        }
                    }
                    break;
            }
        }

        window.clear();
        SDL_Texture* rulesTexture = window.loadTexture("res/gfx/rules.png");
        window.render(0, 0, rulesTexture);

        // Kiểm tra nếu con trỏ chuột đang nằm trên nút "Back"
        bool hover = (mousePos.x >= backButton.x && mousePos.x <= backButton.x + backButton.w &&
                      mousePos.y >= backButton.y && mousePos.y <= backButton.y + backButton.h);

        // Hiển thị nút "Back" với ảnh thay đổi khi di chuột vào
        if (hover) {
            window.render(backButton.x, backButton.y, backHover);
        } else {
            window.render(backButton.x, backButton.y, backNormal);
        }

        window.display();
        SDL_DestroyTexture(rulesTexture);
    }

    // Dọn dẹp tài nguyên
    SDL_DestroyTexture(backNormal);
    SDL_DestroyTexture(backHover);
}

