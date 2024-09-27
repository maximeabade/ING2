#include "File.hpp"
#include "Image.hpp"
#include "Texte.hpp"
#include "Video.hpp"

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    Video video("video", "mp4", 100, 10, 30);
    Image image("image", "jpg", 100, 1920, 1080);
    Texte texte("texte", "txt", 100, Encoding::ASCII);

    std::cout << "Video compressed size: " << video.getCompressedSize() << std::endl;

    std::cout << "Image compressed size: " << image.getCompressedSize() << std::endl;

    std::cout << "Texte compressed size: " << texte.getCompressedSize() << std::endl;

    return 0;

}
