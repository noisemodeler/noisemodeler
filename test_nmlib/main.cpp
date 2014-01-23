#include "test_serialization.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "Running tests for nmlib\n\n";
    bool success = true;

    success |= test_serialization();
}
