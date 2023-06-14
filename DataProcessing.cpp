
#include "GenshinWishAnalyze.h"
#include "DataTypes.h"

#include "fmt/core.h"
#include "fmt/color.h"

ItemAnalysis GachaResultAnalysis(string path, int type)
{
	ItemAnalysis ret;
	FiveStarSession five;
	FourStarSession four;
	ifstream file;
	string linebuf;

	uint64_t GachaId;
	std::string ItemName;
	int ItemType, ItemRank;
	time_t Timestamp;

	int FourStarCounter = 0, FiveStarCounter = 0, FourStarInheritedCounter = 0;

	// Concatenate path
	path += '/' + std::to_string(type) + ".csv";
	file.open(path);

	if (!file)
	{
		fmt::print(fg(fmt::color::light_yellow), "Gacha type {} doesn't have data file.\n", type);
		return ret;
	}

	// Discard first line
	std::getline(file, linebuf);

	while(file)
	{
		// Read a line of data
		file >> GachaId;	file.get();
		std::getline(file, ItemName, ',');
		file >> ItemType;	file.get();
		file >> ItemRank;	file.get();
		file >> Timestamp;	file.get();
		std::getline(file, linebuf);

		// Increase counter
		if (ItemRank < 5)
		{
			FourStarCounter++;
			FourStarInheritedCounter++;
		}
		FiveStarCounter++;

		// Write data and/or clear counter
		if(ItemRank == 4)
		{
			four.ItemName = ItemName;
			four.Pulls = FourStarCounter;
			five.FourStars.emplace_back(four);
			ret.FourStarPulls.emplace_back(FourStarInheritedCounter);
			four = FourStarSession();

			FourStarCounter = FourStarInheritedCounter = 0;
		}

		if(ItemRank == 5)
		{
			five.ItemName = ItemName;
			five.TotalPulls = FiveStarCounter;
			ret.FiveStars.emplace_back(five);
			five = FiveStarSession();

			FourStarCounter = FiveStarCounter = 0;
		}
	}

	if(!five.FourStars.empty())
	{
		
		five.ItemName = "";
		five.TotalPulls = --FiveStarCounter; // There's no item pulled.
		ret.FiveStars.emplace_back(five);
	}

	ret.RemainingPulls = FourStarCounter;

	return ret;
}
