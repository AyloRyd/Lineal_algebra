#include "formatDouble.h"

double format(double number) {
    return std::round(number * 100) / 100.0;
}
