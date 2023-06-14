
#include "GenshinWishAnalyze.h"
#include "DataTypes.h"

#include <numeric>

#include "fmt/color.h"
#include "fmt/core.h"

#define PrintRoutine PrintBar

void PrintBar(fmt::color TargetColor, unsigned int width, string text);
void PrintLightBar(fmt::color TargetColor, unsigned int width, string text);
void PrintGradientBar(fmt::color TargetColor, unsigned int width, string text);

void InteractiveSession(map<int, ItemAnalysis> itemAnalysises)
{
	string linebuf;

	// Build the valid gacha IDs
	string ValidGachas = "(";
	for(auto &[kk, vv] : itemAnalysises)
		if(!vv.FourStarPulls.empty() || vv.RemainingPulls)
			ValidGachas += std::to_string(kk) + ',';
	ValidGachas.pop_back();
	ValidGachas += ')';

	while (true)
	{
		int GachaKind = 0;

		cout << "Gacha history " << ValidGachas << " >>> ";
		std::cin >> GachaKind;
		std::cin.clear();

		if(!itemAnalysises.count(GachaKind))
		{
			fmt::print(fg(fmt::color::white) | bg(fmt::color::red),
				"Gacha {} is not valid.\n",
				GachaKind);
			continue;
		}

		ItemAnalysis& analysis = itemAnalysises.at(GachaKind);

		if(analysis.RemainingPulls + analysis.FiveStars.size() + analysis.FourStarPulls.size() == 0)
		{
			fmt::print(fg(fmt::color::black) | bg(fmt::color::light_yellow),
				"Gacha {} is not valid.\n",
				GachaKind);
			continue;
		}

		for(auto &five : analysis.FiveStars)
		{
			int TotalFourStarPulls = 0;
			bool FlipMagenta = false;

			// Print color bars
			for(auto &four : five.FourStars)
			{
				PrintRoutine(FlipMagenta ? fmt::color::magenta : fmt::color::dark_magenta,
					four.Pulls,
					std::to_string(four.Pulls));
				TotalFourStarPulls += four.Pulls;
				FlipMagenta = !FlipMagenta;
			}
			PrintRoutine(five.ItemName.empty() ? fmt::color::light_green : fmt::color::orange,
				five.TotalPulls - TotalFourStarPulls,
				std::to_string(five.TotalPulls));
			fmt::print(" {}\n", five.ItemName);

			// Print four star names
			int offset = std::accumulate(
				five.FourStars.begin(),
				five.FourStars.end(),
				0,
				[](int a, FourStarSession& b) { return a + b.Pulls; });
			auto currentFourStar = five.FourStars.end();

			if(!five.FourStars.empty()) do {
				--currentFourStar;
				PrintBar(fmt::color::black, offset, "");
				cout << currentFourStar->ItemName << '\n';
				offset -= (currentFourStar)->Pulls;
			} while (currentFourStar != five.FourStars.begin());
		}
	}
}


void PrintGradientBar(fmt::color TargetColor, unsigned int width, string text)
{
	// Guarantee text fits
	width = std::max(text.size(), static_cast<size_t>(width));

	fmt::color MiddleColor, MiddleTextColor = fmt::color::white;

	switch(TargetColor)
	{
	case fmt::color::light_green:
		MiddleColor = fmt::color::green;
		break;

	case fmt::color::yellow:
		MiddleColor = fmt::color::orange;
		MiddleTextColor = fmt::color::black;
		break;

	case fmt::color::magenta:
		MiddleColor = fmt::color::dark_magenta;
		break;

	default:
		MiddleColor = TargetColor;
	}
	// FIXME: When White = 1, Middle = 0, Final = 1, Characters distribute to White and Middle
	const float PerBlock = static_cast<float>(width) / 3;
	const int WhiteWidth = roundf(PerBlock),
		MiddleWidth = roundf(PerBlock * 2) - WhiteWidth,
	    FinalWidth = width - WhiteWidth - MiddleWidth;
	string WhiteStr = text.substr(0, std::max(0, int(text.size()) - MiddleWidth - FinalWidth)),
		MiddleStr = text.substr(WhiteStr.size(), std::max(0, int(text.size()) - FinalWidth)),
		FinalStr = text.substr(WhiteStr.size() + MiddleStr.size()),
		WhiteSpace, MiddleSpace, FinalSpace;
	while (WhiteStr.size() + WhiteSpace.size() < WhiteWidth) WhiteSpace += ' ';
	while (MiddleStr.size() + MiddleSpace.size() < MiddleWidth) MiddleSpace += ' ';
	while (FinalStr.size() + FinalSpace.size() < FinalWidth) FinalSpace += ' ';

	fmt::print(fg(fmt::color::white) | bg(fmt::color::black), "{}{}", WhiteSpace, WhiteStr);
	fmt::print(fg(MiddleTextColor) | bg(MiddleColor), "{}{}", MiddleSpace, MiddleStr);
	fmt::print(fg(fmt::color::black) | bg(TargetColor), "{}{}", FinalSpace, FinalStr);
}

void PrintLightBar(fmt::color TargetColor, unsigned int width, string text)
{
	// Guarantee text fits
	width = std::max(text.size(), static_cast<size_t>(width));

	fmt::color BackColor, FrontTextColor = fmt::color::black;

	switch(TargetColor)
	{
	case fmt::color::light_green:
		BackColor = fmt::color::green;
		break;

	case fmt::color::yellow:
		BackColor = fmt::color::orange;
		break;

	case fmt::color::magenta:
		BackColor = fmt::color::dark_magenta;
		break;

	default:
		BackColor = TargetColor;
	}

	string Space;
	while(Space.size() + text.size() < width)
	{
		Space += ' ';
	}

	fmt::print(bg(BackColor), "{}", Space);
	fmt::print(fg(FrontTextColor) | bg(TargetColor), "{}", text);
}

void PrintBar(fmt::color TargetColor, unsigned int width, string text)
{
	fmt::color FrontTextColor = fmt::color::black;

	switch (TargetColor)
	{
	case fmt::color::green:
	case fmt::color::dark_magenta:
		FrontTextColor = fmt::color::white;
		break;

	default:
		break;
	}

	string Space;
	while (Space.size() + text.size() < width)
	{
		Space += ' ';
	}
	if(TargetColor == fmt::color::black)
		fmt::print("{}{}", Space, text);
	else
		fmt::print(fg(FrontTextColor) | bg(TargetColor), "{}{}", Space, text);
}
