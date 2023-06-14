

#include "GenshinWishAnalyze.h"
#include "DataTypes.h"

int main()
{
	map<int, ItemAnalysis> ItemAnalysisResult;
	string DataPath;


#ifdef _WIN32
	system("chcp 65001 > nul");
#endif

	cout << "Provide player gacha data directory from GenshinWishFetch\n>>> ";
	std::getline(std::cin, DataPath);

	// Get item results
	ItemAnalysisResult[100] = GachaResultAnalysis(DataPath, 100);
	ItemAnalysisResult[200] = GachaResultAnalysis(DataPath, 200);
	ItemAnalysisResult[301] = GachaResultAnalysis(DataPath, 301);
	ItemAnalysisResult[302] = GachaResultAnalysis(DataPath, 302);

	InteractiveSession(ItemAnalysisResult);

	return 0;
}
