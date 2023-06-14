
#include "GenshinWishAnalyze.h"

struct FourStarSession
{
	int Pulls;
	string ItemName;
};

struct FiveStarSession
{
	int TotalPulls;
	string ItemName;
	vector<FourStarSession> FourStars;
};

struct ItemAnalysis
{
	vector<FiveStarSession> FiveStars;
	vector<int> FourStarPulls;
	int RemainingPulls;
};
