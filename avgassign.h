#ifndef AVGASSIGN_H
#define AVGASSIGN_H

#include <vector>
#include <string>
#include <unordered_map>
#include "Course.h"
using namespace std;

void loadCourses(const string& filename);
vector<string> TopologicalSort();
void assignCourses(const vector<string>& sortedCourses, vector<double> creditDemand);

#endif
