
/*
* Hot Air Ballon Game from 1983 by John Galvin, a walk down memory lane
* I wrote this game in BASIC all those years ago for the C64
* This is my attempt to get it running, somewhat the same, as it was in 1983

*/

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"


// Override base class with your custom functionality
class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		// Name your application
		sAppName = "Hot Air Balloon Johnnyg63";
	}

	/* Vectors */
	std::vector<std::string> vecMessages;	// Hold messages to be displayed
	std::vector<std::pair<int, olc::Pixel>> vecC64ColourCodes; // Holds the C64 colour code by key, value
	

	/* Sprites */
	olc::Sprite* sprBalloon;
	olc::Decal* decBalloon;

	olc::Sprite* sprC64Level;
	olc::Decal* decC64Level;


	/* C64 Colour Code Pixels */
	// Thank you too: https://lospec.com/palette-list/commodore64 

	// Holds the correct RGB Colours codes for C64
	struct C64Color
	{
		olc::Pixel Black = { 0, 0, 0, 255 };			// - #000000
		olc::Pixel DarkGrey = { 98, 98, 98, 255 };		// - #626262
		olc::Pixel Grey = { 137, 137, 137, 255 };		// - #898989
		olc::Pixel LightGrey = { 173, 173, 173, 255 };	// - #adadad

		olc::Pixel White = { 255, 255, 255, 255 };		// - #ffffff
		olc::Pixel Red = { 159,78,68, 255 };			// - #9f4e44
		olc::Pixel LightRed = { 255, 119, 119, 255 };	// - #cb7e75
		olc::Pixel Brown = { 109, 84, 18, 255 };		// - #6d5412

		olc::Pixel Orange = { 161, 104, 60, 255 };		// - #a1683c
		olc::Pixel Yellow = { 201, 212, 135, 255 };		// - #c9d487
		olc::Pixel LightGreen = { 154, 226, 155, 255 };	// - #9ae29b
		olc::Pixel Green = { 92, 171, 94, 255 };		// - #5cab5e

		olc::Pixel Cyan = { 106, 191, 198, 255 };		// - #6abfc6
		olc::Pixel LightBlue = { 136, 126, 203, 255 };	// - #887ecb
		olc::Pixel Blue = { 80, 69, 155, 255 };			// - #887ecb
		olc::Pixel Purple = { 160, 87, 163, 255 };		// - #a057a3
		
		
	};

	// C64 colour palette
	C64Color C64Color;
	

	/* C64 Base Screen text */

	std::string strHeaderText1 = "**** COMMODARE 64 BASIC V2 ****";
	std::string strLineBreak = " ";
	std::string strHeaderText2 = "64K RAM SYSTEM 38911 BASIC BYTES FREE";
	std::string strReady = "READY.";
	std::string strLoad = "LOAD";
	std::string strPlay = "PRESS PLAY ON TAPE";
	std::string strLoading = "LOADING...";
	std::string strRun = "RUN...";

	/* Game Vars */
	bool bGameLoaded = false;
	bool bGameLoading = false;
	bool bStartRec = false;



public:
	bool OnUserCreate() override
	{
		// Lets build up our colour code (will make life easier later
		C64LoadColourCodes();

		C64CreateBalloonSprite();

		LoadLevel(1);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame, draws random coloured pixels
		SetDrawTarget(nullptr);
		
		if (GetKey(olc::SPACE).bPressed) bStartRec = true;

		if (!bStartRec) return true;

		
		if (!bGameLoaded)
		{
			FillRectDecal({ 0,0 }, { (float)ScreenWidth(), (float)ScreenHeight() }, C64Color.LightBlue);
			// We display the C64 screen and loading screen until the 'game' is loaded
			if (bGameLoading) C64LoadingScreen();
			C64DisplayScreen();
			C64DisplayHeader(fElapsedTime);
			
			return true;
		}

		FillRectDecal({ 0,0 }, { (float)ScreenWidth(), (float)ScreenHeight() }, C64Color.Blue);
		
		// Lets get the party going
		// first up we need a background
		DrawDecal({ 0, 40 }, decC64Level);
		
		if (GetMouse(0).bHeld) DrawDecal(GetMousePos(), decBalloon);


		return true;
	}


private:

	float fDisplayTime = 0.0f;

	void C64LoadColourCodes()
	{
		vecC64ColourCodes.clear();
		vecC64ColourCodes.push_back({ 0, C64Color.Black });
		vecC64ColourCodes.push_back({ 1, C64Color.DarkGrey });
		vecC64ColourCodes.push_back({ 2, C64Color.Grey });
		vecC64ColourCodes.push_back({ 3, C64Color.LightGrey });

		vecC64ColourCodes.push_back({ 4, C64Color.White });
		vecC64ColourCodes.push_back({ 5, C64Color.Red });
		vecC64ColourCodes.push_back({ 6, C64Color.LightRed });
		vecC64ColourCodes.push_back({ 7, C64Color.Brown });

		vecC64ColourCodes.push_back({ 8, C64Color.Orange });
		vecC64ColourCodes.push_back({ 9, C64Color.Yellow });
		vecC64ColourCodes.push_back({ 10, C64Color.LightGreen });
		vecC64ColourCodes.push_back({ 11, C64Color.Green });

		vecC64ColourCodes.push_back({ 12, C64Color.Cyan });
		vecC64ColourCodes.push_back({ 13, C64Color.LightBlue });
		vecC64ColourCodes.push_back({ 14, C64Color.Blue });
		vecC64ColourCodes.push_back({ 15, C64Color.Purple });

	}

	void C64DisplayScreen()
	{
		
		FillRectDecal({ 20,20 }, { 280, 160 }, C64Color.Blue);

	}

	void C64DisplayHeader(float fElapsedTime)
	{
		fDisplayTime += fElapsedTime;
		bGameLoading = false;
		DrawStringPropDecal({ 45, 30 }, strHeaderText1, C64Color.LightBlue, {1.0f, 0.8f});
		DrawStringPropDecal({ 30, 40 }, strHeaderText2, C64Color.LightBlue, {1.0f, 0.8f});
		DrawStringPropDecal({ 22, 60 }, strReady, C64Color.LightBlue, { 1.0f, 0.8f });

		if (fDisplayTime > 2.0f) DrawStringPropDecal({ 22, 70 }, strLoad, C64Color.LightBlue, { 1.0f, 0.8f });
		if (fDisplayTime > 3.0f) DrawStringPropDecal({ 22, 90 }, strPlay, C64Color.LightBlue, { 1.0f, 0.8f });
		if (fDisplayTime > 5.0f) DrawStringPropDecal({ 22, 100 }, strLoading, C64Color.LightBlue, { 1.0f, 0.8f });
		if (fDisplayTime > 5.0 && fDisplayTime < 8.0) { bGameLoading = true; }
		if (fDisplayTime > 8.0f) DrawStringPropDecal({ 22, 110 }, strRun, C64Color.LightBlue, { 1.0f, 0.8f });
		if (fDisplayTime > 10.5f) bGameLoaded = true;

	}

	void C64LoadingScreen()
	{
		int nC64PixelID;
		olc::Pixel p = olc::BLACK;
		for (int y = 0; y < ScreenHeight(); y += 10)
		{
			nC64PixelID = std::rand() % 16;
			for (auto c : vecC64ColourCodes)
			{
				if (c.first == nC64PixelID)
				{
					p = c.second;
					break;
				};
			}
			FillRectDecal({ 0.0f, (float)y }, { (float)ScreenWidth(), 10.0f }, p);
		}
	}

	void C64CreateBalloonSprite()
	{
		// Right we have a sprite of size 24 X 20
		
		sprBalloon = new olc::Sprite(24, 20);


		std::string sBalloonMap =
			".........#######........"
			".......###########......"
			"......#############....."
			"......#####..######....."
			".....#####.##..#####...."
			".....#####.#########...."
			".....#####.##..#####...."
			"......#####..######....."
			"......#############....."
			"......#.#########.#....."
			".......#.#######.#......"
			".......#..#####..#......"
			"........#..###..#......."
			"........#..###..#......."
			".........#..#..#........"
			".........#..#..#........"
			"..........#####........."
			"..........#####........."
			"..........#####........."
			"...........###..........";

		olc::vi2d vBallonSize = { 24, 20 };

		size_t vecLength = sprBalloon->pColData.size();

		for (size_t i = 0; i < vecLength; i++)
		{
			if (sBalloonMap[i] == '#')
			{
				sprBalloon->pColData[i] = C64Color.White;
				continue;
			}

			if (sBalloonMap[i] == '.')
			{
				sprBalloon->pColData[i] = olc::BLANK;
				continue;
			}


		}

		decBalloon = new olc::Decal(sprBalloon);

		

	}

private:

	void LoadLevel(int8_t nLevel)
	{
		// for this demo there will only be one level
		// but add more as you wish
		
		// 1: We need the level graphics
		// CopyRight: https://www.spriters-resource.com/commodore_64/gianasisters30thanniversaryhack/sheet/199050/
		sprC64Level = new olc::Sprite("./assests/C64LevelOne.png");
		decC64Level = new olc::Decal(sprC64Level);
	}
};

int main()
{
	Example demo;
	if (demo.Construct(320, 200, 4, 4))
		demo.Start();
	return 0;
}