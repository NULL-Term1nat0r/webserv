//#include <iostream>
//#include <fstream>
//#include <vector>
//
//std::string vectorToString(const std::vector<uint8_t>& inputVector) {
//	std::string result;
//	for (size_t i = 0; i < inputVector.size(); ++i) {
//		result += static_cast<char>(inputVector[i]);
//	}
//	std::cout << "-------VECTORTOSTRING-----------------: \n" << result << std::endl;
//	return result;
//}
//
//class parent{
//public:
//	parent() {}
//	virtual ~parent() {}
//	virtual void print() {
//		std::cout << "test\n";
//	}
//};
//
//class a : public parent{
//	int _a;
//};
//
//class b : public parent {
//	int _b;
//};
//
//parent *returnClassPointer(){
//
//	a *newPointer = new a();
//	return newPointer;
//}
//
//int main() {
//	void *classParent = returnClassPointer();
//	if (dynamic_cast<a*>(static_cast<parent*>(classParent)))
//		std::cout << "a" << std::endl;
//	if (dynamic_cast<b*>(static_cast<parent*>(classParent)))
//		std::cout << "b" << std::endl;
//
//
//
//
////	void *classParent = new a();
////	if (dynamic_cast<a*>(static_cast<parent*>(classParent)))
////		std::cout << "a" << std::endl;
////	if (dynamic_cast<b*>(static_cast<parent*>(classParent)))
////		std::cout << "b" << std::endl;
//	return 0;
//}






//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <fstream>
//
//
//std::string returnValue(std::string key, std::string source, std::string limiter){
//	size_t start = source.find(key);
//	size_t end = source.find(limiter, start + key.length());
//	return source.substr(start + key.length(), end - start - key.length());
//}
//
//int main() {
//	// Open the file for reading
//	std::ifstream inputFile("../../ReadmeFiles/postRequest.txt");
//
//	// Check if the file is opened successfully
//	if (!inputFile.is_open()) {
//		std::cerr << "Error: Unable to open the file." << std::endl;
//		return 1;
//	}
//
//	// Vector to store characters read from the file
//	std::vector<char> charVector;
//
//	char ch;
//	// Read characters from the file one by one and store them in the vector
//	while (inputFile.get(ch)) {
//		charVector.push_back(ch);
//	}
//
//	// Close the file
//	inputFile.close();
//
//	// Print the characters stored in the vector
//	std::cout << "Characters read from the file and stored in the vector:" << std::endl;
//	for (char character : charVector) {
//		std::cout << character;
//	}
//	std::cout << std::endl;
//
//	return 0;
//}



//#include <iostream>
//#include <map>
//
//class base {
//public:
//	base() {}
//	virtual ~base() {}
//	virtual void print() {}
//};
//
//class a : public base {
//public:
//	a() : _a(1) {}
//	~a() {}
//	void print() {
//		std::cout << "value of a: " << _a << std::endl;
//	}
//private:
//	int _a;
//};
//
//class b : public base {
//public:
//	b() : _b(2) {}
//	~b() {}
//	void print() {
//		std::cout << "value of b: " << _b << std::endl;
//	}
//private:
//	int _b;
//};
//
//class cd{
//public:
//	cd() : _c(3), _d(4) {}
//	~cd() {}
//	void print() {
//		std::cout << "value of c: " << _c << std::endl;
//		std::cout << "value of d: " << _d << std::endl;
//	}
//private:
//	int _c;
//	int _d;
//};
//int main() {
//	std::map<std::string, void*> map;  // Use void* to store pointers to objects
//
//	a* classA = new a();  // Dynamically allocate objects
//	b* classB = new b();
//	cd* classCD = new cd();
//
//
//	map["test1"] = static_cast<void*>(classA);  // Store the void* pointers in the map
//	map["test2.png"] = static_cast<void*>(classB);
//	map["test3.png"] = static_cast<void*>(classCD);
//
//
//	// Access and cast the objects through the map
//	a* classAFromMap = static_cast<a*>(map["test1"]);
//	if (classAFromMap) {
//		classAFromMap->print();
//	}
//
//	b* classBFromMap = static_cast<b*>(map["test2.png"]);
//	if (classBFromMap) {
//		classBFromMap->print();
//	}
//
//	void *d = static_cast<a*>(map["test3.png"]);
//	cd* classCDFromMap = static_cast<cd*>(d);
//	if (classCDFromMap) {
//		classCDFromMap->print();
//	}
//
//	// Don't forget to clean up the dynamically allocated objects
//	delete classA;
//	delete classB;
//
//	return 0;
//}
#include <iostream>
#include <fstream>

int main() {
	std::ifstream file("../html_files/upload/greek-philosopher-coding-some-skript-in-c--.png", std::ios::binary);

	if (file.is_open()) {
		file.seekg(0, std::ios::end); // Move the file pointer to the end of the file
		std::streampos fileSize = file.tellg(); // Get the position, which is the file size
		file.close(); // Close the file

		if (fileSize != -1) {
			std::cout << "File size: " << static_cast<long>(fileSize) << " bytes" << std::endl;
		} else {
			std::cerr << "Error: Unable to determine the file size." << std::endl;
		}
	} else {
		std::cerr << "Error: Unable to open the file." << std::endl;
	}

	return 0;
}




