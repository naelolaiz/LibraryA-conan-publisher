#include <iostream>
#include "LibraryA.h"

void LibraryA::runme() const
{
    std::cout << "Hello world!" << std::endl;
#ifdef __ARM64__
    std::cout << "arm64" << std::endl;
#else
    std::cout << "intel" << std::endl;
#endif
}

