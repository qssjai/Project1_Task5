#pragma once
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>

double mean(const std::vector<int>& v);
double median(std::vector<int> v);
int mode(const std::vector<int>& v);
std::map<int, double> percentages(const std::vector<int>& v);