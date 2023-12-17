//
// Created by David on 11/4/2023.
//

#include "FileTreeNavigator.h"
#include "Editor.h"
#include <filesystem>

namespace fs = std::filesystem;

const int IMAGE_SIZE = 32;

AVLMap<Pixel, Image> FileTreeNavigator::readAllImages(std::string directory, int numComponents) {
    AVLMap<Pixel, Image> output = AVLMap<Pixel, Image>();
    fs::path imagesLocation(directory);
    if (!fs::exists(imagesLocation)) {
        std::cerr << "Directory does not exist.";
        return nullptr;
    }
    if (!fs::is_directory(directory)) {
        std::cerr << "Path is not a directory.";
        return nullptr;
    }

    //spin up the iterator!
    for(const fs::directory_entry& entry : fs::directory_iterator(imagesLocation)) {
        auto name = entry.path().filename().string();
        name = directory + "/" + name;
        //std::cout << name << std::endl;
        //std::cout << "Reading " + name << std::endl;
        Image current(name, numComponents);
        //std::cout << "Successful read!" << std::endl;
        Editor edit(current);
        //std::cout << "Made editor!" << std::endl;
        edit.resize(IMAGE_SIZE);
        //std::cout << "Successful resize!" << std::endl;
        output.put(current.getAvgRGB(), current);
        //std::cout << "Added to map!" << std::endl;
    }
    return output;
}
