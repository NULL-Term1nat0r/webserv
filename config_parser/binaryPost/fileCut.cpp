
#include "binary.hpp"

//skip header at the start and everything that comes after endboundary

//check file names double in a path


void	Binary::cutFileStart() {
    int startChar = 6; // Example: Start deleting from the 7th character

    std::ifstream inputFile(_fileName.c_str(), std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    std::vector<uint8_t> data;
    char ch;
    int currentChar = 0;

    // Read and save data until the specified position
    while (inputFile.get(ch)) {
        if (currentChar >= startChar) {
            data.push_back(static_cast<uint8_t>(ch)); // Store as binary data
        }
        currentChar++;
    }

    inputFile.close();

    std::ofstream outputFile(_fileName.c_str(), std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open the file for writing." << std::endl;
        return;
    }

    // Write the saved data back into the file using a traditional for loop
    for (size_t i = 0; i < data.size(); ++i) {
        outputFile.put(static_cast<char>(data[i]));
    }

    std::cout << "Characters deleted successfully." << std::endl;

    outputFile.close();
}


void	Binary::cutFileEnd() {
    int endBytesToDelete = 6; // Example: Delete the last 6 bytes

    std::ifstream inputFile(_fileName.c_str(), std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    std::vector<uint8_t> data;
    uint8_t byte;

    // Read the data into a vector, saving all bytes
    while (inputFile.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        data.push_back(byte);
    }

    inputFile.close();

    std::ofstream outputFile(_fileName.c_str(), std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open the file for writing." << std::endl;
        return;
    }

    // Write the saved data back into the file, excluding the last 'endBytesToDelete' bytes
    std::size_t dataSize = data.size();
    for (std::size_t i = 0; i < dataSize - endBytesToDelete; ++i) {
        outputFile.write(reinterpret_cast<const char*>(&data[i]), sizeof(data[i]));
    }

    std::cout << "Bytes deleted from the end successfully." << std::endl;

    outputFile.close();
}
