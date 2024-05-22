#pragma once


struct InfoWind{
    Vector2f pos;
    Vector2f velocWind;
    int typeWind;
    Vector2f VELOCITIES_OF_WIND[10] = {{0.5,-0.5},{0.5,-0.5},
    {0.25,-0.25},{0.25,-0.25},
    {-0.5,0.5},{-0.5,0.5},
    {-0.25,0.25},{-0.25,0.25},
    {0.5,0.5},{-0.5,-0.5}};
    InfoWind(double posX = 0.0,double posY = 0.0,int typeWind = 0){
        pos = Vector2f(posX,posY);
        this->typeWind = typeWind;
        velocWind = VELOCITIES_OF_WIND[typeWind];
    }
};


