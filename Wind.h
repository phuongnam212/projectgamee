#pragma once
#include "RenderWindows.h"
#include "datawind.h"

class Wind: public RenderWindows{
private:
    SDL_Rect clip[7]={{0,0,200,64},{0,0,200,64},{0,32*2,200,64},{0,32*3,200,64},{0,32*4,200,64},{0,32*5,200,64},{0,32*6,200,64}};
    int countClip = 0;
    int speedScroll;
public:
    Wind();
    void setSpeedScroll(int speedScroll);
    void renderWind(SDL_Renderer* &gRenderer, int x, int y, double angle, SDL_RendererFlip flip);
    void renderWinds(SDL_Renderer* &gRenderer,vector<Wind>&winds,vector<InfoWind>&windList);
    int scrollWind();
};
