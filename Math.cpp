// Author: Muhammad Shahsawar Khan
// Company: Icelabs Inc

// Including some important header files.
#include "Math.h"

namespace Mathematics
{
    // [ Starting ] - value initializers.
    Number::Number()
    {
        // Default initializer.
        this->__sNumber = "0";
    }

    Number::Number(std::string sNumber)
    {
        // Helps to set the string number.
        this->__sNumber = sNumber;
    }

    Number::Number(int nNumber)
    {
        // Helps to set the integer number.
        this->__sNumber = std::to_string(nNumber);
    }

    Number::Number(float fNumber)
    {
        // Helps to set the float number.
        this->__sNumber = std::to_string(fNumber);
    }

    Number::Number(double fNumber)
    {
        // Helps to set the double number.
        this->__sNumber = std::to_string(fNumber);
    }

    Number::Number(char *sNumber)
    {
        // Helps to set the string number.
        this->__sNumber = sNumber;
    }

    // [ Ending ] - value initializers.
}
