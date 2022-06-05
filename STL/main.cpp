#include <iostream>
#include <list>
#include "List.h"
#include "Vector.h"


int main()
{
    List<int> l {1,2,3,4,5};
    for(size_t i{}; i < l.Size(); ++i){
        std::cout << l[i] << " ";
    }
    std::cout << std::endl;
	return 0;
}
