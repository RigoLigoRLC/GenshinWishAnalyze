
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include "fmt/color.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::ifstream;
using std::map;

struct FiveStarSession;
struct ItemAnalysis;

// DataProcessing.cpp
ItemAnalysis GachaResultAnalysis(string path, int type);

// InteractiveSession.cpp
void InteractiveSession(map<int, ItemAnalysis> itemAnalysises);
void PrintGradientBar(fmt::color TargetColor, unsigned int width, string text);
