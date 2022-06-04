#include <iostream>
#include <memory>
#include "Vector.h"


int main()
{
	Vector<int> arr{1,2,3,4,5};
	
	for (int & it : arr) {
		std::cout << it << std::endl;
	}


	return 0;
}
