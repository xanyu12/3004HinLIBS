#ifndef DEFS_H
#define DEFS_H

#include <iostream>
#include "date.h"

#include <string>
using namespace std;

static const int MAX_LOANS = 3;
static const int MAX_ARR = 50;
static const int LOAN_PERIOD = 14;

enum class Condition{New, Fine, Acceptable, Poor};
enum class Status{Available, Unavailable, Missing, Withdrawn};

#endif // DEFS_H
