
#include "binary.hpp"

Binary::Binary() {}

Binary::~Binary() {}

// void	Binary::cutFileEnd() {
//     int endBytesToDelete = 5; // Example: Delete the last 6 bytes

// 	_fileName = "debian.test";
//     std::ifstream inputFile(_fileName.c_str(), std::ios::binary);
//     if (!inputFile.is_open()) {
//         std::cerr << "Failed to open the file." << std::endl;
//         return;
//     }

//     std::vector<uint8_t> data;
//     uint8_t byte;



//     //Read the data into a vector, saving all bytes
//    while (inputFile.read(reinterpret_cast<char*>(&byte), sizeof(byte)))
//        data.push_back(byte);

//     inputFile.close();

//     std::ofstream outputFile(_fileName.c_str(), std::ios::binary);
//     if (!outputFile.is_open()) {
//         std::cerr << "Failed to open the file for writing." << std::endl;
//         return;
//     }

//     // Write the saved data back into the file, excluding the last 'endBytesToDelete' bytes
//     std::size_t dataSize = data.size();
//     for (std::size_t i = 0; i < dataSize - endBytesToDelete; ++i)
// 	{
// 		if (i % 1000000 == 0)
// 			std::cout << "1000000 bytes read" << std::endl;
// 		outputFile.put(static_cast<char>(data[i]));
// 	}
//     outputFile.close();
// }


// void	Binary::checkLastChunk(std::vector<uint8_t> &lastChunk, std::string startBoundary)
// {
// 	std::string endBoundary = "--" + startBoundary + "--";
// 	std::vector<uint8_t> boundary = std::vector<uint8_t>(endBoundary.begin(), endBoundary.end());
// 	std::vector<uint8_t>::iterator boundaryPos = std::search(lastChunk.begin(), lastChunk.end(), boundary.begin(), boundary.end());
// 	if (boundaryPos != lastChunk.end()) {
// 		lastChunk.erase(boundaryPos, lastChunk.end());
// 	}
// }



#include <iostream>
#include <vector>

// std::vector<uint8_t>::iterator find_subsequence(std::vector<uint8_t>& lastChunk, const std::vector<uint8_t>& boundary) {
//     for (std::vector<uint8_t>::iterator it = lastChunk.begin(); it != lastChunk.end(); ++it) {
//         if (std::equal(boundary.begin(), boundary.end(), it)) {
//             return it; // Return the iterator where the subsequence was found
//         }
//     }
//     return lastChunk.end(); // Return end() if subsequence is not found
// }

// void	Binary::checkLastChunk(std::vector<uint8_t> &lastChunk, std::string startBoundary) {
// 	_fileName = "tmp.txt";
// 	std::string endBoundary = "--" + startBoundary + "--";
// 	std::vector<uint8_t> boundary = std::vector<uint8_t>(endBoundary.begin(), endBoundary.end());

// 	std::vector<uint8_t>::iterator boundaryPos = find_subsequence(lastChunk, boundary);

//     if (boundaryPos != lastChunk.end())
//        lastChunk.erase(boundaryPos, lastChunk.end());
// 	std::ofstream outputFile(_fileName.c_str(), std::ios::binary);
//     if (!outputFile.is_open()) {
//         std::cerr << "Failed to open the file for writing." << std::endl;
//         return;
//     }
//     for (std::size_t i = 0; i < lastChunk.size(); ++i)
// 		outputFile.put(static_cast<char>(lastChunk[i]));

//     outputFile.close();
// }





std::vector<uint8_t>::iterator findEndBoundary(std::vector<uint8_t>& lastChunk, const std::vector<uint8_t>& boundary) {
    for (std::vector<uint8_t>::iterator it = lastChunk.begin(); it != lastChunk.end(); ++it) {
        if (std::equal(boundary.begin(), boundary.end(), it))
            return it;
    }
    return lastChunk.end();
}

void	Binary::checkLastChunk(std::vector<uint8_t> &lastChunk, std::string startBoundary) {
	std::string endBoundary = "--" + startBoundary + "--";
	std::vector<uint8_t> boundary = std::vector<uint8_t>(endBoundary.begin(), endBoundary.end());
	std::vector<uint8_t>::iterator boundaryPos = findEndBoundary(lastChunk, boundary);
    if (boundaryPos != lastChunk.end())
       lastChunk.erase(boundaryPos, lastChunk.end());
}


int main()
{
    std::ifstream inputFile("postRequest.txt", std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }
    std::vector<uint8_t> lastChunk;
    uint8_t byte;
   while (inputFile.read(reinterpret_cast<char*>(&byte), sizeof(byte)))
       lastChunk.push_back(byte);
	Binary binary;
	binary.checkLastChunk(lastChunk, "----WebKitFormBoundaryGG9teZBRABg3UEtC");
}