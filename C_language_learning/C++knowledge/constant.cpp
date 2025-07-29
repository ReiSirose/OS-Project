#include "constant.h"
#include <iostream>

extern constexpr int MAX_VALUE = 100; // Definition is in the header
                               // Has external linkage implicitly (unless static)
                               // No 'extern' keyword needed for this common use case.
