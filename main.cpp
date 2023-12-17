//
// Created by David on 10/10/2023.
//

#include <iostream>
#include "Image.h"
#include "Editor.h"
#include "AVLMap.h"
#include "FileTreeNavigator.h"
#include <string>
#include "Mosaic.h"

int main(int argc, char* argv[]) {
    std::string inputPath;
    std::string inputDirectory;
    std::string outputPath;
    switch(argc) {
        case 4: {
            inputPath = argv[1];
            inputDirectory = argv[2];
            outputPath = argv[3];
            break;
        }
        case 2: {
            std::cout << "Debug (release ver. 1.0)" << std::endl;
            inputPath = "../sampleImages/jackfrost.jpg";
            inputDirectory = "../sampleImages";
            outputPath = "output.png";
            std::cout << "Generating mosaic...";
            break;
        }
        default: {
            std::cout << "Welcome! Please enter the input path: ";
            std::cin >> inputPath;
            std::cout << "Enter the directory of images to use: ";
            std::cin >> inputDirectory;
            std::cout << "Enter the output path for the mosaic: ";
            std::cin >> inputDirectory;
            std::cout << "Generating mosaic...";
            break;
        }
    }
    FileTreeNavigator ftn;
    auto data = ftn.readAllImages(inputDirectory, 3);
    Mosaic mosaic(data);
    mosaic.makeMosaic(inputPath, outputPath, 3);





}