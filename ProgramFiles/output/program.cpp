
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <math.h>
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "stb_image.h"

void printHex(const char *input_file_path, const char *output_file_path)
{
    std::ifstream file(input_file_path, std::ios::out | std::ios::binary);
    if (!file)
    {
        std::cerr << "Unable to open file: " << input_file_path << std::endl;
        return;
    }

    char byte;
    size_t digraph[256][256] = {0};
    std::vector<uint32_t> byte_store;
    uint32_t bt_front = 0, bt_back = 0;
    uint64_t num_of_bytes = 0;
    while (file.read(&byte, sizeof(byte)))
    {

        bt_front = (static_cast<int>(static_cast<unsigned char>(byte)));
        num_of_bytes++;
        if (num_of_bytes >= 2)
        {
            digraph[bt_back][bt_front]++;
        }
        bt_back = bt_front;

        // byte_store.emplace_back(bt);
        //  std::cout << std::setw(2)  << (static_cast<int>(static_cast<unsigned char>(byte))) << " ";
    }

    // int mn = 0;
    // for (uint32_t i = 0; i < num_of_bytes - 1; i++)
    // {
    //     digraph[byte_store[i]][byte_store[i + 1]]++;
    //     int f = digraph[byte_store[i]][byte_store[i + 1]];
    //     mn = std::min(mn, f);
    // }

    uint32_t pixels[256][256] = {0};
    for (int i = 0; i <= 255; i++)
    {
        for (int j = 0; j <= 255; j++)
        {

            uint32_t p = (digraph[i][j] * 1000);
            pixels[i][j] = 0xFF000000 | p | (p << 16) | (p << 8);
        }
    }
    int ms = 256;
    stbi_write_jpg(output_file_path, ms, ms, 4, pixels, ms * sizeof(uint32_t));
    std::cout << std::dec << std::endl;
    std::cout << "number of bytes  = " << num_of_bytes << '\n';
}

int main()
{
    // printHex("InputData/file_example_OOG_1MG.ogg", "OutputData/OGG_file_output.jpg");
    printHex("InputData/main.exe", "OutputData/exec_file_output.jpg");
    printHex("InputData/images.jpg", "OutputData/img_file_output.jpg");
    printHex("InputData/program.txt", "OutputData/txt_file_output.jpg");
    printHex("InputData/wavfile.sf2", "OutputData/wav_file_output.jpg");

    return 0;
}
