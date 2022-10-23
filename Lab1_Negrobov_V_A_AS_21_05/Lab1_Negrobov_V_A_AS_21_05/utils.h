#pragma once
#include <limits>

float get_float_value(float least = 0, float great = std::numeric_limits<float>::max());

int get_int_value(int least = 0, int great = std::numeric_limits<int>::max());

bool pipe_in_rep_input();