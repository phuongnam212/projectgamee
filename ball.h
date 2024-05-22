
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include "hole.h"
#include "Tile.h"
#include "Wind.h"
#include "Entity.h"
#include "math.h"


class Ball : public Entity
{
public:
	Ball(Vector2f p_pos, SDL_Texture* p_tex, SDL_Texture* p_pointTex, SDL_Texture* p_powerMTexFG, SDL_Texture* p_powerMTexBG, int p_index);
    Vector2f& getVelocity()
	{
		return velocity;
	}
    Vector2f& getInitialMousePos()
	{
		return initialMousePos;
	}
    std::vector<Entity> getPoints()
	{
		return points;
	}
    std::vector<Entity> getPowerBar()
	{
		return powerBar;
	}
    int getStrokes()
    {
        return strokes;
    }
    bool isWin()
    {
        return win;
    }
    void setWin(bool p_win);
    void setInitialMousePos(float x, float y);
    void setVelocity(float x, float y);
    void setLaunchedVelocity(float x, float y);
    struct SDL_FloatRect {
    float x, y, w, h;

    float getTop() const { return y; }
    float getBottom() const { return y + h; }
    float getLeft() const { return x; }
    float getRight() const { return x + w; }
};

bool checkCollision(SDL_FloatRect a, SDL_Rect b) {
    float topB, bottomB, leftB, rightB;
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if (a.getBottom() <= topB) {
        return false;
    }

    if (a.getTop() >= bottomB) {
        return false;
    }

    if (a.getRight() <= leftB) {
        return false;
    }

    if (a.getLeft() >= rightB) {
        return false;
    }

    // If none of the sides from A are outside B
    return true;
}
SDL_FloatRect getFloatRect() {
    Vector2f position = getPos();
    return {position.x, position.y, BALL_WIDTH, BALL_HEIGHT};
}

    void update(double deltaTime, bool mouseDown, bool mousePressed, std::vector<Tile> tiles,std::vector<Hole> holes,std::vector<SDL_Rect> windRectList, std::vector<InfoWind> windList, Mix_Chunk* chargeSfx, Mix_Chunk* swingSfx, Mix_Chunk* holeSfx,bool hasWind);
private:
    static const int BALL_WIDTH = 16;
    static const int BALL_HEIGHT = 16;
    Vector2f velocity;
    Vector2f target;
    Vector2f launchedVelocity;
    float velocity1D;
    float launchedVelocity1D;
    Vector2f initialMousePos;
    bool canMove = true;
    bool playedSwingFx = true;
    int index;
    int strokes = 0;
    int dirX = 1;
    int dirY = 1;
    bool win = false;
    float friction = 0.001;
    std::vector<Entity> points;
    std::vector<Entity> powerBar;
};
