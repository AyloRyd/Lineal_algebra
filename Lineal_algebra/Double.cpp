#include "Double.h"

int countDigitsInDouble(double number) {
    bool isNegative = false;

    if (number < 0) {
        number = -number;
        isNegative = true;
    }

    int integerPart = (int)number;
    double fractionalPart = number - integerPart;;

    int digitsOfIntegerPart = std::to_string(integerPart).size();
    if (isNegative) digitsOfIntegerPart++;

    if (std::to_string(fractionalPart)[2] == '0') {
        return digitsOfIntegerPart;
    }

    int digitsOfFractionalPart = 0;
    int i = 1;
    while (std::to_string(fractionalPart)[i] != '0') {
        fractionalPart *= 10;
        digitsOfFractionalPart++;
        i++;
    }

    int totalDigits = digitsOfIntegerPart + digitsOfFractionalPart + 1; 

    return totalDigits;
}

double formatDouble(double number)
{
    return std::round(number * 100) / 100.0;
}
