#include "productivityoutofrangeexception.h"

ProductivityOutOfRangeException::ProductivityOutOfRangeException():
std::invalid_argument("Productivity exceeds range from 1 to 9"){}