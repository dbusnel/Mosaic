//
// Created by David on 11/5/2023.
//

#include "Mosaic.h"
#include <cmath>

const int IMAGE_SIZE = 32;

void Mosaic::makeMosaic(std::string inputImage, std::string outputPath, int numComponents) {
    Image inputRef(inputImage, numComponents);
    int imagesX = std::ceil(inputRef.getWidth() / IMAGE_SIZE);
    int imagesY = std::ceil(inputRef.getHeight() / IMAGE_SIZE);

    Pixel** outputData = new Pixel*[imagesY * IMAGE_SIZE];

    for (int row = 0; row < imagesY * IMAGE_SIZE; row++) {
        outputData[row] = new Pixel[imagesX * IMAGE_SIZE];
    }

    for (int curImageY = 0; curImageY < imagesY; curImageY++) {
        for (int curImageX = 0; curImageX < imagesX; curImageX++) {
            Pixel avgColor = inputRef.calcAvgRGBFromArea(curImageX * IMAGE_SIZE, curImageY * IMAGE_SIZE,
                                                         (curImageX + 1) * IMAGE_SIZE, (curImageY + 1) * IMAGE_SIZE);
            Image toUse = this->data.get(avgColor);

            for (int curRow = curImageY * IMAGE_SIZE; curRow < (curImageY + 1) * IMAGE_SIZE; curRow++) {
                for (int curCol = curImageX * IMAGE_SIZE; curCol < (curImageX + 1) * IMAGE_SIZE; curCol++) {
                    //std::cout << curRow << " " << curCol << std::endl;
                    outputData[curRow][curCol] = toUse.getLayout()[curRow - curImageY * IMAGE_SIZE][curCol - curImageX * IMAGE_SIZE];
                }
            }
        }
    }

    Image output(outputData, numComponents, imagesY * IMAGE_SIZE, imagesX * IMAGE_SIZE);
    output.saveAs(outputPath);

}
