#include <iostream>
#include <fstream>

int main() {
	// Open the file for appending
	std::ofstream file("example.txt", std::ios::app);

	if (file.is_open()) {
		// Append data to the file
		file << "This is some additional text.\n";

		// Close the file when done
		file.close();

		std::cout << "Data appended successfully." << std::endl;
	} else {
		std::cerr << "Failed to open the file for appending." << std::endl;
	}

	return 0;
}



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
//	map["test2"] = static_cast<void*>(classB);
//	map["test3"] = static_cast<void*>(classCD);
//
//
//	// Access and cast the objects through the map
//	a* classAFromMap = static_cast<a*>(map["test1"]);
//	if (classAFromMap) {
//		classAFromMap->print();
//	}
//
//	b* classBFromMap = static_cast<b*>(map["test2"]);
//	if (classBFromMap) {
//		classBFromMap->print();
//	}
//
//	void *d = static_cast<a*>(map["test3"]);
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
