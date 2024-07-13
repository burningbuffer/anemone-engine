#pragma once

// uncomment to disable assert
//#define NDEBUG
#include <cassert>
 
#define check_assert(exp, msg) assert(((void)msg, exp))