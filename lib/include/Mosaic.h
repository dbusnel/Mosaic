//
// Created by David on 11/5/2023.
//

#ifndef PHOTOMOSAIC_MOSAIC_H
#define PHOTOMOSAIC_MOSAIC_H


#include "Pixel.h"
#include "Image.h"
#include "AVLMap.h"
#include <string>

class Mosaic {
private:
    const AVLMap<Pixel, Image>& data;
public:
    explicit Mosaic(const AVLMap<Pixel, Image>& data) : data(data){ }
    void makeMosaic(std::string inputImage, std::string outputPath, int);
};


#endif //PHOTOMOSAIC_MOSAIC_H
