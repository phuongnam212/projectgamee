#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include<vector>

#include "Entity.h"

class RenderWindows
{
public:
    RenderWindows();
	RenderWindows(const char* p_title, int p_w, int p_h);

	bool loadFromFile(SDL_Renderer* gRenderer, std::string path);

	SDL_Texture* loadTexture(const char* p_filePath);
	bool init();

    SDL_Renderer* getrender () const {
        return renderer;
    }

	int showMenu(const std::vector<std::string>& options);
   // void handleOptions(RenderWindows& window);
    void showRules(RenderWindows &window);

	void cleanUp();
	void clear();
	void render(Entity& p_entity);
	void render(int x, int y, SDL_Texture* p_tex);
    void render( SDL_Renderer* gRenderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    void render( SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
	void render(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
	void renderCenter(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);

	void display();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* mTexture;
	 std::vector<std::string> menuItems = {"Play Game", "Options", "Exit"};

protected:
    double mAngle = 0.0;
    //Image dimensions
    int mWidth;
    int mHeight;
    Vector2f pos;
};
