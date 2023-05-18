#include "Utilities.h"

#ifdef _WIN32
    #include <Windows.h>
#else
    #include <cstdlib>
#endif

namespace Utilities {
    void clearScreen() {
#ifdef _WIN32
        std::system("cls");
#else
        std::system("clear");
#endif
    }
}
