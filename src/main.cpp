#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Image.h"
#include <algorithm>

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

struct point {
	int x, y, z;
};


int main(int argc, char **argv)
{
	cout << "Test" << endl;
	return 0;
}
