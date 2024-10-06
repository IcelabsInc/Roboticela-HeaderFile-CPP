// Author: Muhammad Shahsawar.
// Company: Muhammad Technology.

#pragma once

// Including some important header files.
#include "Common.h"
#include <iostream>

namespace Mathematics
{
    class Number
    {
    private:
        std::string __sNumber;

    public:
        // [ Starting ] - value initializers.
        Number();
        Number(std::string sNumber);
        Number(int nNumber);
        Number(float fNumber);
        Number(double fNumber);
        Number(char *sNumber);
        // [ Ending ] - value initializers.
        
    };
}
