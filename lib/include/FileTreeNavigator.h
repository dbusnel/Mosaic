//
// Created by David on 11/4/2023.
//

#ifndef PHOTOMOSAIC_FILETREENAVIGATOR_H
#define PHOTOMOSAIC_FILETREENAVIGATOR_H


#include "Image.h"
#include "AVLMap.h"
#include <string>

class FileTreeNavigator {
public:
    AVLMap<Pixel, Image> readAllImages(std::string directory, int numComponents);
};


#endif //PHOTOMOSAIC_FILETREENAVIGATOR_H
