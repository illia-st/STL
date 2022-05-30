#include <iostream>
#include <memory>


int main()
{
	auto ptr = std::make_unique<int[]>(10);

	int* raw_ptr = &ptr[0];

	for (size_t i = 0; i < 10; ++i) {
		raw_ptr[i] = i;
		std::cout << raw_ptr[i] << " ";
	}
	std::cout << ptr.get()[2] << std::endl;
	return 0;
}
