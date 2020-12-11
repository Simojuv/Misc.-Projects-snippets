#include "my_library.h"
#include <ctime>
int main()
{
    srand(static_cast<unsigned int >(time(nullptr)));
    Loop(50,20,20);
}
