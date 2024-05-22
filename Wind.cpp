
#include "Wind.h"
Wind::Wind():RenderWindows(){};
void Wind::setSpeedScroll(int speedScroll){
    this->speedScroll=speedScroll;
}
/*void Wind::renderWind(SDL_Renderer* &gRenderer, int x,int y,double angle,SDL_RendererFlip flip){
    if(mWidth>200){
        for(int i = 0;i<7;i++) clip[i].w = mWidth;
    }
    render(gRenderer,x,y,&clip[scrollWind()],angle,NULL,flip);
}
void Wind::renderWind(SDL_Renderer* &gRenderer, int x, int y, double angle, SDL_RendererFlip flip, int customWidth, int customHeight){
    SDL_Rect customClip;
    if (customWidth > 0 && customHeight > 0) {
        customClip.w = customWidth;
        customClip.h = customHeight;
    } else {
        if (mWidth > 200) {
            for (int i = 0; i < 7; i++) clip[i].w = mWidth;
        }
        customClip = clip[scrollWind()];
    }
    customClip.x = clip[scrollWind()].x*3/4;
    customClip.y = clip[scrollWind()].y*3/4;

    render(gRenderer, x, y, &customClip, angle, NULL, flip);
}*/
void Wind::renderWind(SDL_Renderer* &gRenderer, int x, int y, double angle, SDL_RendererFlip flip) {
    // Nếu chiều rộng của ảnh lớn hơn 200, điều chỉnh các clip
    if (mWidth > 200) {
        for (int i = 0; i < 7; i++) {
            clip[i].w = mWidth;
        }
    }

    // Tạo một biến để lưu trữ kích thước mới của phần gió
    SDL_Rect newClip = clip[scrollWind()];
    newClip.w = newClip.w * 3 / 4; // Giảm chiều dài đi 3/4

    // Render phần gió với kích thước mới
    render(gRenderer, x, y, &newClip, angle, NULL, flip);
}
void Wind:: renderWinds(SDL_Renderer* &gRenderer,vector<Wind>&winds,vector<InfoWind>&windList){
    double angle = 0.0;
    for( int i = 0; i < windList.size(); i+=1) {
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if(windList[i].typeWind == 9) flip = SDL_FLIP_HORIZONTAL;
        else if(windList[i].typeWind == 8) flip = SDL_FLIP_VERTICAL;
        if(windList[i].typeWind >=4 && windList[i].typeWind <= 7) {
            angle = 180.0;
        } else angle = 0.0;
        winds[windList[i].typeWind].renderWind(gRenderer,
                                               windList[i].pos.x, windList[i].pos.y, angle, flip);
    }
}

int Wind::scrollWind(){
    int ret = countClip/speedScroll;
    countClip++;
    if(countClip>=speedScroll*7){
        countClip = 0;
    }
    return ret;
}
