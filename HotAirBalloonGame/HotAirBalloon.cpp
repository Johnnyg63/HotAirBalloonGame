
/*
* Hot Air Ballon Game from 1983 by John Galvin, a walk down memory lane
* I wrote this game in BASIC all those years ago for the C64
* This is my attempt to get it running, somewhat the same, as it was in 1983

*/

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#define OLC_PGEX_TRANSFORMEDVIEW
#include "olcPGEX_TransformedView.h"

#include "olcUTIL_Camera2D.h"



// Override base class with your custom functionality
class HotAirBalloon : public olc::PixelGameEngine
{
public:
	HotAirBalloon()
	{
		// Name your application
		sAppName = "Hot Air Balloon Johnnyg63";
	}

	float nStep = 20.0f; // Line step

	// Use for displaying the correct messages
	enum DisplayMessage {
		Welcome,
		Scores,
		ForgotRick,
		RickDead,
		YouDead
	};

	DisplayMessage CurrentMessages = HotAirBalloon::Welcome;

	/* Vectors */
	std::vector<std::string> vecMessages;	// Hold messages to be displayed
	std::vector<std::pair<int, olc::Pixel>> vecC64ColourCodes; // Holds the C64 colour code by key, value
	std::vector<std::pair<char, olc::Pixel>> vecC64PixelColourCodes; // Holds the C64 Pixel colour code by key, value


	/* Sprites */
	olc::Sprite* sprBalloon;
	olc::Decal* decBalloon;

	olc::Sprite* sprColourBalloon;
	olc::Decal* decColourBalloon;

	olc::Sprite* sprColourBalloonUp;
	olc::Decal* decColourBalloonUp;

	olc::Sprite* sprColourBalloonDown;
	olc::Decal* decColourBalloonDown;


	olc::Sprite* sprColourBalloonRight;
	olc::Decal* decColourBalloonRight;

	olc::Sprite* sprColourBalloonLeft;
	olc::Decal* decColourBalloonLeft;

	olc::Sprite* sprC64Level;
	olc::Decal* decC64Level;

	olc::Sprite* sprRickSpriteSheet;
	olc::Decal* decRickSpriteSheet;

	olc::Sprite* sprEnemiesSpriteSheeta;
	olc::Decal* decEnemiesSpriteSheeta;

	olc::Sprite* sprEnemiesSpriteSheetb;
	olc::Decal* decEnemiesSpriteSheetb;

	olc::Sprite* sprObjectsSpriteSheet;
	olc::Decal* decObjectsSpriteSheet;

	olc::Sprite* sprC64Banner;
	olc::Decal* decC64Banner;

	olc::Sprite* sprMSBanner;
	olc::Decal* decMSBanner;

	olc::Sprite* sprC64Logo;
	olc::Decal* decC64Logo;



	/* C64 Colour Code Pixels */
	// Thank you too: https://lospec.com/palette-list/commodore64 
	// Holds the correct RGB Colours codes for C64
	struct C64Colors
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

	C64Colors C64Color; // C64 colour palette

	struct C64FileTileKeys
	{
		uint8_t Blank = -1;		// Set the tile to blank
		uint8_t GetSprite = -2;	// Fill the title with the sprite from sprite sheet

		uint8_t SetBlockPlayer = -100; // Sets a block for Player collison
		uint8_t SetBlockHero = -110;	// Sets a block for Hero collison
		uint8_t SetBlockEnemies = -120; // Sets a block for Enemies collison

		uint8_t SetHero1 = 130;	// Set position for heros		
		uint8_t SetHero2 = 140;	// Set position for heros
		uint8_t SetHero3 = 150;	// Set position for heros
		uint8_t SetHero4 = 160;	// Set position for heros

		uint8_t SetEnemies1 = 170;	// Set position for Enemies
		uint8_t SetEnemies2 = 180; // Set position for Enemies
		uint8_t SetEnemies3 = 190; // Set position for Enemies
		uint8_t SetEnemies4 = 195; // Set position for Enemies
		uint8_t SetEnemies5 = 200; // Set position for Enemies
		uint8_t SetEnemies6 = 205; // Set position for Enemies

		uint8_t SetBomb1 = 210;		// Set position for bombs
		uint8_t SetExplosion1 = 215;	// Set position for explosions


		uint8_t Black = 0;		// Set the tile to this C64 Colour
		uint8_t DarkGrey = 1;	// Set the tile to this C64 Colour
		uint8_t Grey = 2;		// Set the tile to this C64 Colour
		uint8_t LightGrey = 3;	// Set the tile to this C64 Colour

		uint8_t White = 4;		// Set the tile to this C64 Colour
		uint8_t Red = 5;		// Set the tile to this C64 Colour
		uint8_t LightRed = 6;	// Set the tile to this C64 Colour
		uint8_t Brown = 7;		// Set the tile to this C64 Colour

		uint8_t Orange = 8;		// Set the tile to this C64 Colour
		uint8_t Yellow = 9;		// Set the tile to this C64 Colour
		uint8_t LightGreen = 10;// Set the tile to this C64 Colour
		uint8_t Green = 11;		// Set the tile to this C64 Colour

		uint8_t Cyan = 12;		// Set the tile to this C64 Colour
		uint8_t LightBlue = 13;	// Set the tile to this C64 Colour
		uint8_t Blue = 14;		// Set the tile to this C64 Colour
		uint8_t Purple = 15;	// Set the tile to this C64 Colour

	};
	C64FileTileKeys C64FileTileKey;



	/* Game Vars */
	bool bGameLoaded = false;
	bool bGameLoading = false;
	bool bStartRec = false;

	// C64 Display Stuff
private:

	/* C64 Base Screen text */
	std::string strHeaderText1 = "**** COMMODARE 64 BASIC V2 ****";
	std::string strLineBreak = " ";
	std::string strHeaderText2 = "64K RAM SYSTEM 38911 BASIC BYTES FREE";
	std::string strReady = "READY.";
	std::string strPrint = "PRINT OLC CODEJAM 2023: JOHNNYG64";
	std::string strPrintRes = "OLC CODEJAM 2023: JOHNNYG64";
	std::string strLoad = "LOAD";
	std::string strPlay = "PRESS PLAY ON TAPE";
	std::string strLoading = "LOADING...";
	std::string strRun = "RUN";
	std::string strMovement = "USE ARROW KEYS OR WSAD TO MOVE, B FOR BOMBS";
	std::string strMission = "YOUR MISSION IS TO HELP ALL THE C64 HEROS";
	std::string strRickForgot = "YOU FORGOT RICK!!";
	std::string strRickDead = "RICK IS DEAD, GAME OVER!";
	std::string strPlayerDead = "YOU DEAD, GAME OVER!";
	std::string strTotalScore = "TOTAL SCORE: ";
	std::string strEnemiesAlive = "ENEMIES LEFT: ";
	std::string strHeroLives = "HERO LIVES: ";
	std::string strPlayLives = "PLAYER LIVES: ";
	std::string strCOPY1 = "This demo is for eduction purposes only, images, logos and trademarks are owned by their respective identities";
	std::string strCOPY2 = "Power by OLC Pixel Game Engine 2.0. C OneLoneCoder.com 2023";

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

		//
		vecC64PixelColourCodes.clear();
		vecC64PixelColourCodes.push_back({ '0', C64Color.Black });
		vecC64PixelColourCodes.push_back({ '1', C64Color.DarkGrey });
		vecC64PixelColourCodes.push_back({ '2', C64Color.Grey });
		vecC64PixelColourCodes.push_back({ '3', C64Color.LightGrey });

		vecC64PixelColourCodes.push_back({ '4', C64Color.White });
		vecC64PixelColourCodes.push_back({ '5', C64Color.Red });
		vecC64PixelColourCodes.push_back({ '6', C64Color.LightRed });
		vecC64PixelColourCodes.push_back({ '7', C64Color.Brown });

		vecC64PixelColourCodes.push_back({ '8', C64Color.Orange });
		vecC64PixelColourCodes.push_back({ '9', C64Color.Yellow });
		vecC64PixelColourCodes.push_back({ 'A', C64Color.LightGreen });
		vecC64PixelColourCodes.push_back({ 'B', C64Color.Green });

		vecC64PixelColourCodes.push_back({ 'C', C64Color.Cyan });
		vecC64PixelColourCodes.push_back({ 'D', C64Color.LightBlue });
		vecC64PixelColourCodes.push_back({ 'E', C64Color.Blue });
		vecC64PixelColourCodes.push_back({ 'F', C64Color.Purple });



	}

	void C64DisplayScreen()
	{

		FillRectDecal({ 20,20 }, { 280, 200 }, C64Color.Blue);

	}

	void C64DisplayHeader(float fElapsedTime)
	{
		fDisplayTime += fElapsedTime;
		bGameLoading = false;
		DrawStringPropDecal({ 45, 30 }, strHeaderText1, C64Color.LightBlue, { 1.0f, 0.8f });
		DrawStringPropDecal({ 30, 40 }, strHeaderText2, C64Color.LightBlue, { 1.0f, 0.8f });
		DrawStringPropDecal({ 22, 60 }, strReady, C64Color.LightBlue, { 1.0f, 0.8f });
		if (fDisplayTime > 1.0f) DrawStringPropDecal({ 22, 70 }, strPrint, C64Color.LightBlue, { 1.0f, 0.8f });
		if (fDisplayTime > 1.2f) DrawStringPropDecal({ 22, 80 }, strPrintRes, C64Color.LightBlue, { 1.0f, 0.8f });

		if (fDisplayTime > 2.0f) DrawStringPropDecal({ 22, 90 }, strLoad, C64Color.LightBlue, { 1.0f, 0.8f });
		if (fDisplayTime > 3.0f) DrawStringPropDecal({ 22, 100 }, strPlay, C64Color.LightBlue, { 1.0f, 0.8f });
		if (fDisplayTime > 5.0f) DrawStringPropDecal({ 22, 110 }, strLoading, C64Color.LightBlue, { 1.0f, 0.8f });
		if (fDisplayTime > 5.0 && fDisplayTime < 8.0) { bGameLoading = true; }
		if (fDisplayTime > 8.0f) DrawStringPropDecal({ 22, 120 }, strRun, C64Color.LightBlue, { 1.0f, 0.8f });
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

	void C64CreateColourBalloonSprite()
	{
		// Right we have a sprite of size 24 X 20

		sprColourBalloon = new olc::Sprite(24, 20);

		std::string sBalloonMap =
			"........555555555......."
			"......5889999999885....."
			".....5899BBEEEBB9985...."
			".....589BEE44EEEB985...."
			"....589BEE4EE44EEB985..."
			"....589BEE4EEEEEEB985..."
			"....589BEE4EE55EEB985..."
			".....589BEE44EEEB985...."
			".....589BEEEEEEEB985...."
			".....7.589BEEEB985.7...."
			"......7..589B985..7....."
			"......7...58985...7....."
			".......7...585...7......"
			".......7...585...7......"
			"........7...9...7......."
			"........7...8...7......."
			".........8787878........"
			"..........87878........."
			"..........82528........."
			"...........878..........";

		olc::vi2d vBallonSize = { 24, 20 };

		size_t vecLength = sprColourBalloon->pColData.size();

		for (size_t i = 0; i < vecLength; i++)
		{

			if (sBalloonMap[i] == '.')
			{
				sprColourBalloon->pColData[i] = olc::BLANK;
				continue;
			}

			for (auto p : vecC64PixelColourCodes)
			{
				if (p.first == sBalloonMap[i])
				{
					sprColourBalloon->pColData[i] = p.second;
				}
			}
		}

		decColourBalloon = new olc::Decal(sprColourBalloon);



	}

	void C64CreateColourBalloonSpriteUP()
	{

		sprColourBalloonUp = new olc::Sprite(24, 20);

		std::string sBalloonMap =
			"........666666666......."
			"......6889999999886....."
			".....6899BBEEEBB9986...."
			".....689BEE44EEEB986...."
			"....689BEE4EE44EEB986..."
			"....689BEE4EEEEEEB986..."
			"....689BEE4EE55EEB986..."
			".....589BEE44EEEB985...."
			".....589BEEEEEEEB985...."
			".....7.589BEEEB985.7...."
			"......7..589B985..7....."			"......7...59595...7....."
			".......7...959...7......"
			".......7...959...7......"
			"........7...5...7......."
			"........7...8...7......."
			".........8787878........"
			"..........87878........."
			"..........82628........."
			"...........878..........";

		olc::vi2d vBallonSize = { 24, 20 };

		size_t vecLength = sprColourBalloonUp->pColData.size();

		for (size_t i = 0; i < vecLength; i++)
		{

			if (sBalloonMap[i] == '.')
			{
				sprColourBalloonUp->pColData[i] = olc::BLANK;
				continue;
			}

			for (auto p : vecC64PixelColourCodes)
			{
				if (p.first == sBalloonMap[i])
				{
					sprColourBalloonUp->pColData[i] = p.second;
				}
			}


		}

		decColourBalloonUp = new olc::Decal(sprColourBalloonUp);



	}

	void C64CreateColourBalloonSpriteDown()
	{
		sprColourBalloonDown = new olc::Sprite(24, 20);

		std::string sBalloonMap =
			".....555..CC.CC..555...."
			"......5889.CCC.9885....."
			".....5899BBECEBB9985...."
			".....589BEE44EEEB985...."
			"....589BEE4EE44EEB985..."
			"....589BEE4EEEEEEB985..."
			"....589BEE4EE55EEB985..."
			".....589BEE44EEEB985...."
			".....589BEEEEEEEB985...."
			".....7.589BEEEB985.7...."
			"......7..589B985..7....."
			"......7...58985...7....."
			".......7...585...7......"
			".......7...585...7......"
			"........7...9...7......."
			"........7...8...7......."
			".........8787878........"
			"..........87878........."
			"..........82528........."
			"...........878..........";

		olc::vi2d vBallonSize = { 24, 20 };

		size_t vecLength = sprColourBalloonDown->pColData.size();

		for (size_t i = 0; i < vecLength; i++)
		{

			if (sBalloonMap[i] == '.')
			{
				sprColourBalloonDown->pColData[i] = olc::BLANK;
				continue;
			}

			for (auto p : vecC64PixelColourCodes)
			{
				if (p.first == sBalloonMap[i])
				{
					sprColourBalloonDown->pColData[i] = p.second;
				}
			}

		}

		decColourBalloonDown = new olc::Decal(sprColourBalloonDown);



	}

	void C64CreateColourBalloonSpriteRight()
	{
		// Right we have a sprite of size 24 X 20

		sprColourBalloonRight = new olc::Sprite(24, 20);

		std::string sBalloonMap =
			".........555555555......"
			".......5889999999885...."
			"......5899BBEEEBB9985..."
			"......589BEE44EEEB985..."
			".....589BEE4EE44EEB985.."
			".....589BEE4EEEEEEB985.."
			".....589BEE4EE55EEB985.."
			"......589BEE44EEEB985..."
			"......589BEEEEEEEB985..."
			"......7.589BEEEB985.7..."
			".....7..589B985..7......"
			".....7...58985...7......"
			"......7...585...7......."
			"......7...585...7......."
			".......7...9...7........"
			".......7...8...7........"
			"........8787878........."
			".........87278.........."
			".........82528.........."
			"..........828...........";


		olc::vi2d vBallonSize = { 24, 20 };

		size_t vecLength = sprColourBalloonRight->pColData.size();

		for (size_t i = 0; i < vecLength; i++)
		{

			if (sBalloonMap[i] == '.')
			{
				sprColourBalloonRight->pColData[i] = olc::BLANK;
				continue;
			}

			for (auto p : vecC64PixelColourCodes)
			{
				if (p.first == sBalloonMap[i])
				{
					sprColourBalloonRight->pColData[i] = p.second;
				}
			}
		}

		decColourBalloonRight = new olc::Decal(sprColourBalloonRight);



	}

	void C64CreateColourBalloonSpriteLeft()
	{
		// Right we have a sprite of size 24 X 20

		sprColourBalloonLeft = new olc::Sprite(24, 20);

		std::string sBalloonMap =
			".......555555555........"
			".....5889999999885......"
			"....5899BBEEEBB9985....."
			"....589BEE44EEEB985....."
			"...589BEE4EE44EEB985...."
			"...589BEE4EEEEEEB985...."
			"...589BEE4EE55EEB985...."
			"....589BEE44EEEB985....."
			"....589BEEEEEEEB985....."
			".....7.589BEEEB985.7...."
			"........7..589B985..7..."
			"........7...58985...7..."
			"........7...585...7....."
			"........7...585...7....."
			".........7...9...7......"
			".........7...8...7......"
			"..........8787878......."
			"...........87278........"
			"...........82528........"
			"............828.........";


		olc::vi2d vBallonSize = { 24, 20 };

		size_t vecLength = sprColourBalloonLeft->pColData.size();

		for (size_t i = 0; i < vecLength; i++)
		{

			if (sBalloonMap[i] == '.')
			{
				sprColourBalloonLeft->pColData[i] = olc::BLANK;
				continue;
			}

			for (auto p : vecC64PixelColourCodes)
			{
				if (p.first == sBalloonMap[i])
				{
					sprColourBalloonLeft->pColData[i] = p.second;
				}
			}
		}

		decColourBalloonLeft = new olc::Decal(sprColourBalloonLeft);



	}

	// Game Level Stuff
private:

	void LoadLevel(int8_t nLevel)
	{
		// for this demo there will only be one level
		// but add more as you wish

		// 1: We need the level graphics
		// CopyRight: https://www.spriters-resource.com/commodore_64/gianasisters30thanniversaryhack/sheet/199050/
		sprC64Level = new olc::Sprite("assets/clevelonea.png");
		decC64Level = new olc::Decal(sprC64Level);

		sprC64Banner = new olc::Sprite("assets/commodorebannera.png");
		decC64Banner = new olc::Decal(sprC64Banner);

		sprMSBanner = new olc::Sprite("assets/microsoftbannera.png");
		decMSBanner = new olc::Decal(sprMSBanner);

		sprC64Logo = new olc::Sprite("assets/commodorelogoa.png");
		decC64Logo = new olc::Decal(sprC64Logo);

		LoadMap("assets/levelonea.bin");

	}

	void LoadSpriteSheets()
	{
		sprRickSpriteSheet = new olc::Sprite("assets/rickspritesheeta.png");
		decRickSpriteSheet = new olc::Decal(sprRickSpriteSheet);

		sprEnemiesSpriteSheeta = new olc::Sprite("assets/rickenemiesspritesheeta.png");
		decEnemiesSpriteSheeta = new olc::Decal(sprEnemiesSpriteSheeta);

		sprEnemiesSpriteSheetb = new olc::Sprite("assets/rickenemiesspritesheetb.png");
		decEnemiesSpriteSheetb = new olc::Decal(sprEnemiesSpriteSheetb);

		sprObjectsSpriteSheet = new olc::Sprite("assets/bitsspritesheeta.png");
		decObjectsSpriteSheet = new olc::Decal(sprObjectsSpriteSheet);

	}

	void CreateWorldObjects()
	{
		// Rick
		objectRick.fID = 100.0f;
		objectRick.fVelX = 0.5f;
		objectRick.fRadius = 1.0f;
		objectRick.fFrameChangeTime = 0.05f;
		objectRick.nRunCurrentFrame = 0;
		objectRick.nRunFrames = 3;
		objectRick.bCanLoseLives = true;
		objectRick.nDefaultLives = 5;
		objectRick.nLives = 5;
		objectRick.eObjecttype = HeroObject;
		objectRick.pDecal = decRickSpriteSheet;
		objectRick.vCenterPos = { 4.0f, 4.0f };
		objectRick.vPos = { 3.0f, 3.0f };
		objectRick.vPotentialPosition = { 0.0f, 0.0f };
		objectRick.vSize = { 24, 24 };
		objectRick.vSourceSize = { 32, 32 };
		objectRick.vSourceStand = { 64, 48 };

		objectRick.vecRunFrame.clear();
		objectRick.vecRunFrame.push_back({ 96, 48 });
		objectRick.vecRunFrame.push_back({ 128, 48 });
		objectRick.vecRunFrame.push_back({ 160, 48 });
		objectRick.vecRunFrame.push_back({ 192, 48 });
		objectRick.vecRunFrame.push_back({ 224, 48 });

		objectRick.vVel = { 0.0f, 0.2f };
		objectRick.C64FileKey = C64FileTileKey.SetHero1;

		// Microsoft
		objectMSBanner.fID = 200.0f;
		objectMSBanner.eObjecttype = HeroObject;
		objectMSBanner.fVelX = 0.0f;
		objectMSBanner.fVelY = 0.0f;
		objectMSBanner.bCanMove = false;
		objectMSBanner.fRadius = 3.0f;
		objectMSBanner.nRunCurrentFrame = 0;
		objectMSBanner.nRunFrames = 0;
		objectMSBanner.pDecal = decMSBanner;
		objectMSBanner.vCenterPos = { 4.0f, 4.0f };
		objectMSBanner.vPos = { 3.0f, 3.0f };
		objectMSBanner.vPotentialPosition = { 0.0f, 0.0f };
		objectMSBanner.vSize = { 24, 24 };
		objectMSBanner.vSourceSize = { 32, 32 };
		objectMSBanner.vSourceStand = { 64, 48 };
		objectMSBanner.vecRunFrame.clear();
		objectMSBanner.vVel = { 0.0f, 0.0f };
		objectMSBanner.C64FileKey = C64FileTileKey.SetHero2;

		// Commodore 64
		objectC64Banner.fID = 300.0f;
		objectC64Banner.fVelX = 0.0f;
		objectC64Banner.fVelY = 0.0f;
		objectC64Banner.eObjecttype = HeroObject;
		objectC64Banner.bCanMove = false;
		objectC64Banner.fRadius = 3.0f;
		objectC64Banner.nRunCurrentFrame = 0;
		objectC64Banner.nRunFrames = 0;
		objectC64Banner.pDecal = decC64Banner;
		objectC64Banner.vCenterPos = { 4.0f, 4.0f };
		objectC64Banner.vPos = { 3.0f, 3.0f };
		objectC64Banner.vPotentialPosition = { 0.0f, 0.0f };
		objectC64Banner.vSize = { 24, 24 };
		objectC64Banner.vSourceSize = { 32, 32 };
		objectC64Banner.vSourceStand = { 64, 48 };
		objectC64Banner.vecRunFrame.clear();
		objectC64Banner.vVel = { 0.0f, 0.0f };
		objectC64Banner.C64FileKey = C64FileTileKey.SetHero3;

		// Commodore 64 Logo
		objectC64Logo.fID = 400.0f;
		objectC64Logo.fVelX = 0.9f;
		objectC64Logo.fVelY = 0.0f;
		objectC64Logo.eObjecttype = HeroObject;
		objectC64Logo.fRadius = 0.5f;
		objectC64Logo.nRunCurrentFrame = 0;
		objectC64Logo.nRunFrames = 360;
		objectC64Logo.pDecal = decC64Logo;
		objectC64Logo.vCenterPos = { 4.0f, 4.0f };
		objectC64Logo.vPos = { 3.0f, 3.0f };
		objectC64Logo.vPotentialPosition = { 0.0f, 0.0f };
		objectC64Logo.vSize = { 24, 24 };
		objectC64Logo.vSourceSize = { 32, 32 };
		objectC64Logo.vSourceStand = { 64, 48 };
		objectC64Logo.vecRunFrame.clear();
		objectC64Logo.vVel = { 0.0f, 0.0f };
		objectC64Logo.fRototaion = 0.12;
		objectC64Logo.C64FileKey = C64FileTileKey.SetHero4;


		// Egyptian		
		objectEgyptian.fID = 500.0f;
		objectEgyptian.fRadius = 1.0f;
		objectEgyptian.eObjecttype = EnemiesObject;
		objectEgyptian.nDefaultLives = 1;
		objectEgyptian.nLives = 1;
		objectEgyptian.nRunCurrentFrame = 0;
		objectEgyptian.nRunFrames = 3;
		objectEgyptian.pDecal = decEnemiesSpriteSheeta;
		objectEgyptian.vCenterPos = { 4.0f, 4.0f };
		objectEgyptian.vPos = { 3.0f, 3.0f };
		objectEgyptian.vPotentialPosition = { 0.0f, 0.0f };
		objectEgyptian.vSize = { 24, 24 };
		objectEgyptian.vSourceSize = { 32, 32 };
		objectEgyptian.vSourceStand = { 64, 48 };

		objectEgyptian.vecRunFrame.clear();
		objectEgyptian.vecRunFrame.push_back({ 64, 48 });
		objectEgyptian.vecRunFrame.push_back({ 96, 48 });

		objectEgyptian.vVel = { 0.0f, 0.2f };
		objectEgyptian.C64FileKey = C64FileTileKey.SetEnemies1;


		// Soldier
		objectSoldier.fID = 600.0f;
		objectSoldier.fRadius = 1.0f;
		objectSoldier.eObjecttype = EnemiesObject;
		objectSoldier.nDefaultLives = 1;
		objectSoldier.nLives = 1;
		objectSoldier.nRunCurrentFrame = 0;
		objectSoldier.nRunFrames = 3;
		objectSoldier.pDecal = decEnemiesSpriteSheeta;
		objectSoldier.vCenterPos = { 4.0f, 4.0f };
		objectSoldier.vPos = { 3.0f, 3.0f };
		objectSoldier.vPotentialPosition = { 0.0f, 0.0f };
		objectSoldier.vSize = { 24, 24 };
		objectSoldier.vSourceSize = { 32, 32 };
		objectSoldier.vSourceStand = { 224, 48 };

		objectSoldier.vecRunFrame.clear();
		objectSoldier.vecRunFrame.push_back({ 256, 48 });
		objectSoldier.vecRunFrame.push_back({ 32, 80 });
		objectSoldier.vecRunFrame.push_back({ 64, 80 });

		objectSoldier.vVel = { 0.0f, 0.2f };
		objectSoldier.C64FileKey = C64FileTileKey.SetEnemies2;


		// warrior
		objectWarrior.fID = 700.0f;
		objectWarrior.fRadius = 1.0f;
		objectWarrior.eObjecttype = EnemiesObject;
		objectWarrior.nDefaultLives = 1;
		objectWarrior.nLives = 1;
		objectWarrior.nRunCurrentFrame = 0;
		objectWarrior.nRunFrames = 3;
		objectWarrior.pDecal = decEnemiesSpriteSheeta;
		objectWarrior.vCenterPos = { 4.0f, 4.0f };
		objectWarrior.vPos = { 3.0f, 3.0f };
		objectWarrior.vPotentialPosition = { 0.0f, 0.0f };
		objectWarrior.vSize = { 24, 24 };
		objectWarrior.vSourceSize = { 32, 32 };
		objectWarrior.vSourceStand = { 64, 112 };

		objectWarrior.vecRunFrame.clear();
		objectWarrior.vecRunFrame.push_back({ 64, 112 });
		objectWarrior.vecRunFrame.push_back({ 96, 112 });

		objectWarrior.vVel = { 0.0f, 0.2f };
		objectWarrior.C64FileKey = C64FileTileKey.SetEnemies3;

		// foot soldier
		objectFootSoldier.fID = 800.0f;
		objectFootSoldier.bIsForeGround = false;
		objectFootSoldier.fRadius = 1.0f;
		objectFootSoldier.eObjecttype = EnemiesObject;
		objectFootSoldier.nDefaultLives = 2;
		objectFootSoldier.nLives = 2;
		objectFootSoldier.nRunCurrentFrame = 0;
		objectFootSoldier.nRunFrames = 3;
		objectFootSoldier.pDecal = decEnemiesSpriteSheetb;
		objectFootSoldier.vCenterPos = { 4.0f, 4.0f };
		objectFootSoldier.vPos = { 3.0f, 3.0f };
		objectFootSoldier.vPotentialPosition = { 0.0f, 0.0f };
		objectFootSoldier.vSize = { 24, 24 };
		objectFootSoldier.vSourceSize = { 32, 32 };
		objectFootSoldier.vSourceStand = { 64, 48 };

		objectFootSoldier.vecRunFrame.clear();
		objectFootSoldier.vecRunFrame.push_back({ 64, 48 });
		objectFootSoldier.vecRunFrame.push_back({ 96, 48 });

		objectFootSoldier.vVel = { 0.0f, 0.2f };
		objectFootSoldier.C64FileKey = C64FileTileKey.SetEnemies4;

		// officer
		objectOfficer.fID = 900.0f;
		objectOfficer.fRadius = 1.0f;
		objectOfficer.eObjecttype = EnemiesObject;
		objectOfficer.nDefaultLives = 3;
		objectOfficer.nLives = 3;
		objectOfficer.nRunCurrentFrame = 0;
		objectOfficer.nRunFrames = 3;
		objectOfficer.pDecal = decEnemiesSpriteSheetb;
		objectOfficer.vCenterPos = { 4.0f, 4.0f };
		objectOfficer.vPos = { 3.0f, 3.0f };
		objectOfficer.vPotentialPosition = { 0.0f, 0.0f };
		objectOfficer.vSize = { 24, 24 };
		objectOfficer.vSourceSize = { 32, 32 };
		objectOfficer.vSourceStand = { 192, 80 };

		objectOfficer.vecRunFrame.clear();
		objectOfficer.vecRunFrame.push_back({ 128, 80 });
		objectOfficer.vecRunFrame.push_back({ 160, 80 });

		objectOfficer.vVel = { 0.0f, 0.2f };
		objectOfficer.C64FileKey = C64FileTileKey.SetEnemies5;

		objectMummy.fID = 1000.0f;
		objectMummy.bIsForeGround = true;
		objectMummy.fRadius = 1.0f;
		objectMummy.eObjecttype = EnemiesObject;
		objectMummy.nDefaultLives = 2;
		objectMummy.nLives = 2;
		objectMummy.nRunCurrentFrame = 0;
		objectMummy.nRunFrames = 3;
		objectMummy.pDecal = decEnemiesSpriteSheetb;
		objectMummy.vCenterPos = { 4.0f, 4.0f };
		objectMummy.vPos = { 3.0f, 3.0f };
		objectMummy.vPotentialPosition = { 0.0f, 0.0f };
		objectMummy.vSize = { 24, 24 };
		objectMummy.vSourceSize = { 32, 32 };
		objectMummy.vSourceStand = { 224, 114 };

		objectMummy.vecRunFrame.clear();
		objectMummy.vecRunFrame.push_back({ 224, 144 });
		objectMummy.vecRunFrame.push_back({ 256, 144 });

		objectMummy.vVel = { 0.0f, 0.2f };
		objectMummy.C64FileKey = C64FileTileKey.SetEnemies6;

		// Bombs
		objectBomb.fID = 1100.0f;
		objectBomb.fVelX = 0.2f;
		objectBomb.fVelY = 0.2f;
		objectBomb.fRadius = 1.0f;
		objectBomb.fFrameChangeTime = 0.333f;
		objectBomb.nRunCurrentFrame = 0;
		objectBomb.nRunFrames = 6;
		objectBomb.nDefaultLives = 99;
		objectBomb.nLives = 99;
		objectBomb.eObjecttype = BombObject;
		objectBomb.pDecal = decEnemiesSpriteSheeta;
		objectBomb.vCenterPos = { 4.0f, 4.0f };
		objectBomb.vPos = { 3.0f, 3.0f };
		objectBomb.vPotentialPosition = { 0.0f, 0.0f };
		objectBomb.vSize = { 24, 24 };
		objectBomb.vSourceSize = { 32, 32 };
		objectBomb.vSourceStand = { 64, 144 };

		objectBomb.vecRunFrame.clear();
		objectBomb.vecRunFrame.push_back({ 64, 144 });
		objectBomb.vecRunFrame.push_back({ 96, 144 });
		objectBomb.vecRunFrame.push_back({ 128, 144 });
		objectBomb.vecRunFrame.push_back({ 160, 144 });
		objectBomb.vecRunFrame.push_back({ 192, 144 });
		objectBomb.vecRunFrame.push_back({ 224, 144 });
		objectBomb.vecRunFrame.push_back({ 256, 144 });

		objectBomb.vVel = { 0.0f, 0.2f };
		objectBomb.C64FileKey = C64FileTileKey.SetBomb1;

		// Explosion
		objectExplosion.fID = 1200.0f;
		objectExplosion.fVelX = 0.5f;
		objectExplosion.fRadius = 1.5f;
		objectExplosion.nRunCurrentFrame = 0;
		objectExplosion.nRunFrames = 4;
		objectExplosion.nDefaultLives = 1;
		objectExplosion.nLives = 1;
		objectExplosion.eObjecttype = ExplosionObject;
		objectExplosion.pDecal = decObjectsSpriteSheet;
		objectExplosion.vCenterPos = { 4.0f, 4.0f };
		objectExplosion.vPos = { 3.0f, 3.0f };
		objectExplosion.vPotentialPosition = { 0.0f, 0.0f };
		objectExplosion.vSize = { 24, 24 };
		objectExplosion.vSourceSize = { 32, 32 };
		objectExplosion.vSourceStand = { 160, 48 };

		objectExplosion.vecRunFrame.clear();
		//objectExplosion.vecRunFrame.push_back({ 128, 48 });
		objectExplosion.vecRunFrame.push_back({ 160, 48 });
		objectExplosion.vecRunFrame.push_back({ 192, 48 });
		objectExplosion.vecRunFrame.push_back({ 224, 48 });
		objectExplosion.vecRunFrame.push_back({ 32, 80 });

		objectExplosion.vVel = { 0.0f, 0.2f };
		objectExplosion.C64FileKey = C64FileTileKey.SetExplosion1;



		// And finally
		objectPlayer.fID = 1.0f;
		objectPlayer.bCanMove = true;
		objectPlayer.bEnabled = true;
		objectPlayer.bVelChanged = true;
		objectPlayer.bIsDead = false;
		objectPlayer.eObjecttype = PlayerObject;
		objectPlayer.fRadius = 1.25f;
		objectPlayer.fStartIndex = 771;
		objectPlayer.pDecal = decColourBalloon;
		objectPlayer.nDefaultLives = 5;
		objectPlayer.nLives = 5;
		objectPlayer.vPos = { 3.0f, 3.0f };
		objectPlayer.vCenterPos = { 4.0f, 4.0f };
		objectPlayer.vStartPos = { 2.0, 3.0 };
		objectPlayer.vEndPos = m_vWorldSize;



	}

	void LoadWorldObjectsIntoMap()
	{
		for (int i = 0; i < vWorldMapHero.size(); i++)
		{
			if (vWorldMapObjects[i] == C64FileTileKey.SetHero1)
			{
				sWorldObject worldObject = objectRick;
				worldObject.fStartIndex = i;
				vecObjectHeros.push_back({ worldObject });
			}

			if (vWorldMapObjects[i] == C64FileTileKey.SetHero2)
			{
				sWorldObject worldObject = objectMSBanner;
				worldObject.fStartIndex = i;
				vecObjectHeros.push_back({ worldObject });
			}

			if (vWorldMapObjects[i] == C64FileTileKey.SetHero3)
			{
				sWorldObject worldObject = objectC64Banner;
				worldObject.fStartIndex = i;
				vecObjectHeros.push_back({ worldObject });
			}

			if (vWorldMapObjects[i] == C64FileTileKey.SetHero4)
			{
				sWorldObject worldObject = objectC64Logo;
				worldObject.fStartIndex = i;
				vecObjectHeros.push_back({ worldObject });
			}
		}

		for (int i = 0; i < vWorldMapEnemies.size(); i++)
		{

			if (vWorldMapObjects[i] == C64FileTileKey.SetEnemies1)
			{
				sWorldObject worldObject = objectEgyptian;
				worldObject.fStartIndex = i;
				vecObjectEnemies.push_back({ worldObject });
			}

			if (vWorldMapObjects[i] == C64FileTileKey.SetEnemies2)
			{
				sWorldObject worldObject = objectSoldier;
				worldObject.fStartIndex = i;
				vecObjectEnemies.push_back({ worldObject });
			}

			if (vWorldMapObjects[i] == C64FileTileKey.SetEnemies3)
			{
				sWorldObject worldObject = objectWarrior;
				worldObject.fStartIndex = i;
				vecObjectEnemies.push_back({ worldObject });
			}

			if (vWorldMapObjects[i] == C64FileTileKey.SetEnemies4)
			{
				sWorldObject worldObject = objectFootSoldier;
				worldObject.fStartIndex = i;
				vecObjectEnemies.push_back({ worldObject });
			}

			if (vWorldMapObjects[i] == C64FileTileKey.SetEnemies5)
			{
				sWorldObject worldObject = objectOfficer;
				worldObject.fStartIndex = i;
				vecObjectEnemies.push_back({ worldObject });
			}


			if (vWorldMapObjects[i] == C64FileTileKey.SetEnemies6)
			{
				sWorldObject worldObject = objectMummy;
				worldObject.fStartIndex = i;
				vecObjectEnemies.push_back({ worldObject });
			}

		}


	}

	// Transform View Stuff
public:

	// Transformed view object to make world offsetting simple
	olc::TileTransformedView tv;

	enum WorldObjectType
	{
		PlayerObject,
		HeroObject,
		EnemiesObject,
		BombObject,
		ExplosionObject
	};

	struct sWorldObject
	{
		olc::vf2d vPos;
		olc::vf2d vVel;
		float fVelX = 0.3f;
		float fVelY = 0.0f;

		olc::vf2d vCenterPos;
		olc::vf2d vPotentialPosition;
		float fRadius = 1.25f;
		olc::Decal* pDecal = nullptr;

		float fID = 0.01f;
		bool bEnabled = false;
		bool bVelChanged = false;
		bool bRunningRight = false;
		bool bIsForeGround = true;
		bool bCanMove = true;
		bool bIsDead = false;
		bool bCanLoseLives = true;

		int nDefaultLives = 5;
		int nLives = 1;
		float fGodModeTime = 0.0f;
		float fTottleTime = 0.0f;
		float fFlashTime = 0.1665f;
		float fFrameChangeTime = 0.1665f;
		float bShowHide = true;

		float fRototaion = 0.0f;
		uint8_t C64FileKey;
		HotAirBalloon::WorldObjectType eObjecttype = HotAirBalloon::PlayerObject;
		int nRunCurrentFrame = 0;
		float fFrameTime = 0.0f;
		int nRunFrames = 3;
		olc::vf2d vSourcePos = { 0,0 };
		olc::vf2d vSize = { 0.0f, 0.0f };
		olc::vf2d vSourceSize = { 0.0f, 0.0f };
		olc::vf2d vSourceStand = { 0.0f, 0.0f };
		std::vector<olc::vf2d> vecRunFrame;
		olc::vf2d vStartPos = { 0.0f, 0.0f };
		olc::vf2d vEndPos = { 0.0f, 0.0f };

		int fStartIndex = 0;


	};

	sWorldObject objectPlayer;		// Player Decal Object

	std::vector<sWorldObject> vecObjectHeros;	// Hero Objects
	std::vector<sWorldObject> vecObjectEnemies;	// Enemies Objects
	std::vector<sWorldObject> vecObjectBombs;	// Bombs Objects
	std::vector<sWorldObject> vecObjectExplosion;	// Bombs Objects

	sWorldObject objectRick;
	sWorldObject objectC64Banner;
	sWorldObject objectMSBanner;
	sWorldObject objectC64Logo;

	sWorldObject objectEgyptian;	// Enemies Egyptian object
	sWorldObject objectSoldier;		// Enemies Soldier object
	sWorldObject objectWarrior;		// Enemies Worrior object
	sWorldObject objectFootSoldier;	// Enemies Foot Soldier object
	sWorldObject objectOfficer;		// Enemies Offier object
	sWorldObject objectMummy;		// Enemies Mummy object

	sWorldObject objectBomb;		// Bomb object
	sWorldObject objectExplosion;	// Explosion object






	bool bFollowObject = false;

	// Conveninet constants to define tile map world
	olc::vi2d m_vWorldSize = { 256, 30 }; // 2048 64 cells
	olc::vi2d m_vTileSize = { 8, 8 };

	// The camera!
	olc::utils::Camera2D camera;

	// The point that represents the player, it is "tracked"
	// by the camera
	olc::vf2d vTrackedPoint;

	// Flag whether we are in "free roam" or "play" mode
	bool bFreeRoam = false;

	bool bShowGrid = false; // Hide/Show grid
	bool bShowGridPlayer = false; // Hide/Show grid
	bool bShowGridHero = false; // Hide/Show grid
	bool bShowGridEnemies = false; // Hide/Show grid
	bool bShowGridObjects = false; // Hide/Show grid


	// The world map, stored as a 1D array of graphics
	std::vector<uint8_t> vWorldMapPlayerGraphics;
	std::vector<uint8_t> vWorldMapPlayerGraphics_undo;


	// The world map, stored as a 1D array for collison
	std::vector<uint8_t> vWorldMapPlayer;
	std::vector<uint8_t> vWorldMapPlayer_undo;

	std::vector<uint8_t> vWorldMapHero;
	std::vector<uint8_t> vWorldMapHero_undo;

	std::vector<uint8_t> vWorldMapEnemies;
	std::vector<uint8_t> vWorldMapEnemies_undo;

	std::vector<uint8_t> vWorldMapObjects;
	std::vector<uint8_t> vWorldMapObjects_undo;

	float testTime = 0.0f;

	void EnableWorldObject(olc::vf2d vTile, WorldObjectType objectType, bool bRunningRight, int fStartIndex, uint8_t C64FileType)
	{
		bool bFoundObject = false;


		switch (objectType)
		{
		case HotAirBalloon::HeroObject:
		{
			for (auto& worldObject : vecObjectHeros)
			{
				if (worldObject.bIsDead) continue;
				if (worldObject.fStartIndex == fStartIndex && worldObject.bEnabled == false && worldObject.C64FileKey == C64FileType)
				{
					worldObject.vPos = vTile;
					worldObject.vPos.y += -0.5f;
					worldObject.vStartPos = vTile - olc::vf2d{ 128.0f, 0.00f };
					worldObject.vEndPos = vTile + olc::vf2d{ 128.0f, 3.0f };

					worldObject.vPotentialPosition = vTile;
					worldObject.bEnabled = true;
					worldObject.bRunningRight = bRunningRight;
					break;
				}
			}
			break;
		}

		case HotAirBalloon::EnemiesObject:
		{
			for (auto& worldObject : vecObjectEnemies)
			{
				if (worldObject.bIsDead) continue;
				if (worldObject.fStartIndex == fStartIndex && worldObject.bEnabled == false && worldObject.C64FileKey == C64FileType)
				{
					worldObject.vPos = vTile;
					worldObject.vPos.y += -0.5f;
					worldObject.vStartPos = vTile - olc::vf2d{ 128.0f, 0.00f };
					worldObject.vEndPos = vTile + olc::vf2d{ 128.0f, 3.0f };

					worldObject.vPotentialPosition = vTile;
					worldObject.bEnabled = true;
					worldObject.bRunningRight = bRunningRight;
					break;
				}
			}
			break;
		}

		case HotAirBalloon::BombObject:
		{
			for (auto& worldObject : vecObjectBombs)
			{
				if (worldObject.bIsDead) continue; // TODO remove from vector
				if (worldObject.fStartIndex == fStartIndex && worldObject.bEnabled == false && worldObject.C64FileKey == C64FileType)
				{
					worldObject.vPos = vTile;
					worldObject.vPos.y += -0.5f;
					worldObject.vStartPos = vTile - olc::vf2d{ 128.0f, 0.00f };
					worldObject.vEndPos = vTile + olc::vf2d{ 128.0f, 3.0f };

					worldObject.vPotentialPosition = vTile;
					worldObject.bEnabled = true;
					worldObject.bRunningRight = bRunningRight;
					break;
				}
			}
			break;
		}

		case HotAirBalloon::ExplosionObject:
		{
			for (auto& worldObject : vecObjectExplosion)
			{
				if (worldObject.bIsDead) continue; // TODO remove from vector
				if (worldObject.fStartIndex == fStartIndex && worldObject.bEnabled == false && worldObject.C64FileKey == C64FileType)
				{
					worldObject.vPos = vTile;
					worldObject.vPos.y += -0.5f;
					worldObject.vStartPos = vTile - olc::vf2d{ 128.0f, 0.00f };
					worldObject.vEndPos = vTile + olc::vf2d{ 128.0f, 3.0f };

					worldObject.vPotentialPosition = vTile;
					worldObject.bEnabled = true;
					worldObject.bRunningRight = bRunningRight;
					break;
				}
			}
			break;
		}
		default:
			break;
		}

	}


	// Draw the world objects, Heros, Enemies etc
	void DrawWorldObjects(float fElaspedTime, sWorldObject* worldObject, bool bIsForeGround)
	{

		if (!worldObject->bEnabled || worldObject->bIsDead) return;
		if (bIsForeGround != worldObject->bIsForeGround) return;

		worldObject->fFrameTime = worldObject->fFrameTime + fElaspedTime;

		float rotation = 0.125;
		if (worldObject->fFrameTime > (worldObject->fFrameChangeTime * (worldObject->nRunCurrentFrame + 1)))
		{
			worldObject->nRunCurrentFrame += 1;
			if (worldObject->nRunCurrentFrame >= worldObject->vecRunFrame.size())
			{
				if (worldObject->eObjecttype == BombObject)
				{
					// ok lets replace with it a explosion
					worldObject->bIsDead = true;
					int vPosX = worldObject->vPos.x;
					int vPosY = worldObject->vPos.y;

					size_t idx = (vPosY * m_vWorldSize.x) + vPosX;
					idx = std::min(idx, (vWorldMapObjects.size() - 1)); // Edge case, we to ensure we are within the array range
					vWorldMapObjects[idx] = C64FileTileKey.SetExplosion1;
					sWorldObject worldObject1 = objectExplosion;
					worldObject1.fStartIndex = idx;
					vecObjectExplosion.push_back({ worldObject1 });			
					
					return;

				}
				if (worldObject->eObjecttype == ExplosionObject)
				{
					worldObject->bIsDead = true;
					return;
				}
				worldObject->nRunCurrentFrame = 0;
			}

			worldObject->fFrameTime = 0.0f;

		}

		olc::vf2d vFrame = worldObject->vSourceStand;

		if (worldObject->vecRunFrame.size() > 0)
		{
			vFrame = worldObject->vecRunFrame[worldObject->nRunCurrentFrame];
		}

		// Speical Case
		if (worldObject->fID == objectC64Banner.fID)
		{
			tv.DrawRotatedDecal({ worldObject->vPos }, decC64Banner, (3.142f / 2.0f),
				{ float(decC64Banner->sprite->width / 2.0f), float(decC64Banner->sprite->height / 2.0f) }, { 0.10f, 0.13f });
			return;

		}

		if (worldObject->fID == objectMSBanner.fID)
		{
			tv.DrawRotatedDecal({ worldObject->vPos }, decMSBanner, (3.142f / 2.0f),
				{ float(decMSBanner->sprite->width / 2.0f), float(decMSBanner->sprite->height / 2.0f) }, { 0.05f, 0.05f });
			return;
		}

		// Bomb Object
		if (worldObject->eObjecttype == BombObject)
		{
			if (!worldObject->bIsDead) tv.DrawPartialDecal(worldObject->vPos - olc::vf2d(0.75f, 0.4f), worldObject->vSize, worldObject->pDecal, vFrame, worldObject->vSourceSize);
			return;
		}

		// Explosion Object
		if (worldObject->eObjecttype == ExplosionObject)
		{
			if (!worldObject->bIsDead) tv.DrawPartialDecal(worldObject->vPos - olc::vf2d(1.1f, 0.3f), worldObject->vSize, worldObject->pDecal, vFrame, worldObject->vSourceSize);
			return;
		}

		if (worldObject->fID == objectC64Logo.fID)
		{

			if (worldObject->bRunningRight)
			{
				worldObject->fRototaion += worldObject->fFrameChangeTime;
				tv.DrawRotatedDecal({ worldObject->vPos }, decC64Logo, worldObject->fRototaion,
					{ float(decMSBanner->sprite->width / 2.0f), float(decMSBanner->sprite->height / 2.0f) }, { 0.01f, 0.01f });
			}
			else
			{
				worldObject->fRototaion += worldObject->fFrameChangeTime;
				tv.DrawRotatedDecal({ worldObject->vPos }, decC64Logo, worldObject->fRototaion,
					{ float(decMSBanner->sprite->width / 2.0f), float(decMSBanner->sprite->height / 2.0f) }, { 0.01f, 0.01f });
			}

			return;

		}

		if (!worldObject->bCanLoseLives)
		{
			// Right we are in god mode lets flash
			worldObject->fTottleTime += fElaspedTime;
			if (worldObject->fTottleTime > worldObject->fFlashTime)
			{
				worldObject->fTottleTime = 0.0f;
				worldObject->bShowHide = !worldObject->bShowHide;
			}
		}

		if (worldObject->bRunningRight)
		{

			if (worldObject->bCanLoseLives || worldObject->bShowHide)
				tv.DrawPartialDecal(worldObject->vPos - olc::vf2d(1.0f, 0.4f), worldObject->vSize, worldObject->pDecal, vFrame, worldObject->vSourceSize);
		}
		else
		{
			if (worldObject->bCanLoseLives || worldObject->bShowHide)
				tv.DrawPartialDecal(worldObject->vPos - olc::vf2d(-1.0f, 0.4f), worldObject->vSize * olc::vf2d(-1.0f, 1.0f),
					worldObject->pDecal, vFrame, worldObject->vSourceSize);
		}


	}

	// lets get the collision
	void HandleCollison(float fElapsedTime, olc::vi2d* vTile, sWorldObject* worldObject)
	{
		if (worldObject->eObjecttype != PlayerObject)
		{
			if (!worldObject->bEnabled || !worldObject->bVelChanged) return;

		}
		olc::vf2d vNearestPoint;
		vNearestPoint.x = std::max(float(vTile->x), std::min(worldObject->vPotentialPosition.x, float(vTile->x + 1)));
		vNearestPoint.y = std::max(float(vTile->y), std::min(worldObject->vPotentialPosition.y, float(vTile->y + 1)));

		olc::vf2d vRayToNearest = vNearestPoint - worldObject->vPotentialPosition;
		float fOverlap = worldObject->fRadius - vRayToNearest.mag();
		if (std::isnan(fOverlap)) fOverlap = 0;

		// If overlap is positive, then a collision has occurred, so we displace backwards by the 
		// overlap amount. The potential position is then tested against other tiles in the area
		// therefore "statically" resolving the collision
		if (fOverlap > 0)
		{
			// Statically resolve the collision
			worldObject->vPotentialPosition = worldObject->vPotentialPosition - vRayToNearest.norm() * fOverlap;

			switch (worldObject->eObjecttype)
			{
			case HeroObject:
			case EnemiesObject:
				if (worldObject->bRunningRight)
				{
					worldObject->vEndPos.x = vTile->x;
					worldObject->vEndPos.y = vTile->y;
					worldObject->bRunningRight = false;
				}
				else
				{
					worldObject->vStartPos.x = vTile->x;
					worldObject->vStartPos.y = vTile->y;
					worldObject->bRunningRight = true;
				}
				break;
			case BombObject:
			case ExplosionObject:
			case PlayerObject:
			default:
				break;
			}



		}

		// Set the objects new position to the allowed potential position
		worldObject->vPos = worldObject->vPotentialPosition;
		if (worldObject->eObjecttype == PlayerObject)
		{
			vTrackedPoint = worldObject->vPotentialPosition;
		}

		// Draw Velocity
		if (worldObject->vVel.mag2() > 0)
		{
			//tv.DrawLineDecal(worldObject->vPos, worldObject->vPos + worldObject->vVel.norm() * worldObject->fRadius, olc::MAGENTA);
		}



	}


	// Handles if a object has hit another object
	void HandleObjectCollison(sWorldObject* testObject1, sWorldObject* worldObject, bool bIsPlayer)
	{

		if (!testObject1->bEnabled || testObject1->bIsDead || !worldObject->bEnabled || worldObject->bIsDead) return;

		olc::vi2d vTile;
		vTile.x = (int)testObject1->vPos.x;
		vTile.y = (int)testObject1->vPos.y;

		olc::vf2d vNearestPoint;
		vNearestPoint.x = std::max(float(vTile.x), std::min(worldObject->vPotentialPosition.x, float(vTile.x + 1)));
		vNearestPoint.y = std::max(float(vTile.y), std::min(worldObject->vPotentialPosition.y, float(vTile.y + 1)));

		olc::vf2d vRayToNearest = vNearestPoint - worldObject->vPotentialPosition;
		float fOverlap = worldObject->fRadius - vRayToNearest.mag();
		if (std::isnan(worldObject->vPotentialPosition.x))
		{
			// ok we are stuck or dead
			switch (worldObject->eObjecttype)
			{

			case HeroObject:
			case EnemiesObject:
			{
				worldObject->bIsDead = true;
				worldObject->bEnabled = false;
				worldObject->vPotentialPosition.x = worldObject->vStartPos.x + 1; // we need to move the position by 1 so not to case another collision
				worldObject->vPotentialPosition.y = worldObject->vStartPos.y;
				break;
			}
			case BombObject:
			{
				worldObject->bIsDead = true;
				worldObject->bEnabled = false;
				worldObject->vPotentialPosition.x = worldObject->vStartPos.x + 1; // we need to move the position by 1 so not to case another collision
				worldObject->vPotentialPosition.y = worldObject->vStartPos.y;
				// ok we are stuck lets blow it up
				return;
				break;

			}
			case ExplosionObject:
			{
				worldObject->bIsDead = true;
				worldObject->bEnabled = false;
				worldObject->vPotentialPosition.x = worldObject->vStartPos.x + 1; // we need to move the position by 1 so not to case another collision
				worldObject->vPotentialPosition.y = worldObject->vStartPos.y;
				break;
			}
			case PlayerObject:
			{
				worldObject->vPotentialPosition.x = worldObject->vStartPos.x + 1; // we need to move the position by 1 so not to case another collision
				worldObject->vPotentialPosition.y = worldObject->vStartPos.y;
				break;
			}
				
			default:
				break;
			}


		}
		if (std::isnan(fOverlap))
		{
			fOverlap = 0;
		}


		// If overlap is positive, then a collision has occurred, so we displace backwards by the 
		// overlap amount. The potential position is then tested against other tiles in the area
		// therefore "statically" resolving the collision
		if (fOverlap > 0)
		{
			// Statically resolve the collision
			worldObject->vPotentialPosition = worldObject->vPotentialPosition - vRayToNearest.norm() * fOverlap;

			// we need to check what are we testing against and then apply the rules
			// 1: Player can Touch a Hero Object and Bomb object, every else will cause a lost of a live
			// 2: When bomb object is touch its direction will change
			// 3: When a hero object or player object touchs an enemies a life will be lost
			// 4: Explosion object cannot move and will take a live from anything that touches it

			// Ok we will test the world object aganist our test object (debug this to get idea if what is happening)
			// sorry lots of switches, it is best way trust me, it makes it easier for expansion later, just debug it
			switch (testObject1->eObjecttype)
			{
			case ExplosionObject:
			{
				// Rule 4 everyone loses a life
				if (worldObject->bCanLoseLives)
				{
					worldObject->nLives--; // we lose a life
					if (worldObject->nLives < 0)
					{
						worldObject->bIsDead = true;

					}
					else
					{
						worldObject->bCanLoseLives = false;
					}

				}
				return;
				break;
			}
			case PlayerObject:
			case HeroObject:
			{
				switch (worldObject->eObjecttype)
				{
				case HeroObject:
				case PlayerObject:
				{
					// rule 1
					// Nothiong to do here they can touch
					break;
				}
					
				case BombObject:
				{
					// rule 2 change direction
					worldObject->bRunningRight = testObject1->bRunningRight;
					worldObject->fVelX = testObject1->fVelX + 0.1f; // Ensures it moves away from the object
					break;
				}
					
				case EnemiesObject:
				case ExplosionObject:
				{
					// Rule 3
					if (testObject1->bCanLoseLives)
					{
						testObject1->nLives--; // we lose a life
						if (testObject1->nLives < 0)
						{
							testObject1->bIsDead = true;

						}
						else
						{
							testObject1->bCanLoseLives = false;
						}

					}
					break;
				}
				default:
					break;
				}

				break;
			}

			case EnemiesObject:
			{
				switch (worldObject->eObjecttype)
				{
				case HeroObject:
				case PlayerObject:
				{
					// Rule 3
					if (worldObject->bCanLoseLives)
					{
						worldObject->nLives--; // we lose a life
						worldObject->bCanLoseLives = false;
					}
					break;
				}
					
				case BombObject:
				{
					// rule 2 change direction
					worldObject->bRunningRight = testObject1->bRunningRight;
					worldObject->fVelX = testObject1->fVelX + 0.1f; // Ensures it moves away from the object
					break;
				}
					
				case ExplosionObject:
				{
					// Rule 3
					if (testObject1->bCanLoseLives)
					{
						testObject1->nLives--; // we lose a life
						if (testObject1->nLives < 0)
						{
							testObject1->bIsDead = true;

						}
						else
						{
							testObject1->bCanLoseLives = false;
						}

					}
					break;
				}
				case EnemiesObject:
					break;
				default:
					break;
				}

				break;
			}
				
			case BombObject:
				// it does nothing the other object will move it around
				break;
			default:
				break;
			}

			
		}

		// Set the objects new position to the allowed potential position
		worldObject->vPos.x = worldObject->vPotentialPosition.x;

		if (worldObject->eObjecttype == PlayerObject)
		{
			vTrackedPoint = worldObject->vPotentialPosition;
		}


		// Draw Velocity
		if (worldObject->vVel.mag2() > 0)
		{
			//tv.DrawLineDecal(worldObject->vPos, worldObject->vPos + worldObject->vVel.norm() * worldObject->fRadius, olc::MAGENTA);
		}



	}

	// Handle input for graphics 
	void HandleInput(float fElapsedTime, olc::vi2d vTile)
	{
		if (GetMouse(0).bHeld || GetMouse(0).bPressed)
		{
			olc::vi2d vTilePos = tv.GetTileUnderScreenPos(GetMousePos());
			tv.FillRectDecal(vTile, { 1.0f, 1.0f }, olc::Pixel(60, 60, 60, 127));

			int idx = vTilePos.y * m_vWorldSize.x + vTilePos.x;
			//vWorldMapPlayerGraphics[idx] = C64FileTileKey.GetSprite;
			if (bShowGridPlayer) vWorldMapPlayer[idx] = C64FileTileKey.SetBlockPlayer;
			if (bShowGridHero) vWorldMapHero[idx] = C64FileTileKey.SetBlockHero;
			if (bShowGridEnemies) vWorldMapEnemies[idx] = C64FileTileKey.SetBlockEnemies;
			//if (bShowGridObjects) vWorldMapObjects[idx] = C64FileTileKey.SetHero1; //Rick
			//if (bShowGridObjects) vWorldMapObjects[idx] = C64FileTileKey.SetHero2; // Microsoft
			//if (bShowGridObjects) vWorldMapObjects[idx] = C64FileTileKey.SetHero3; // Commodore
			if (bShowGridObjects) vWorldMapObjects[idx] = C64FileTileKey.SetHero4;	// Commodore Logo
			//if (bShowGridObjects) vWorldMapObjects[idx] = C64FileTileKey.SetEnemies1;
			//if (bShowGridObjects) vWorldMapObjects[idx] = C64FileTileKey.SetEnemies2;
			//if (bShowGridObjects) vWorldMapObjects[idx] = C64FileTileKey.SetEnemies3;
			//if (bShowGridObjects) vWorldMapObjects[idx] = C64FileTileKey.SetEnemies4;
			//if (bShowGridObjects) vWorldMapObjects[idx] = C64FileTileKey.SetEnemies5;
			//if (bShowGridObjects) vWorldMapObjects[idx] = C64FileTileKey.SetEnemies6;
		}
		if (GetMouse(1).bHeld || GetMouse(1).bPressed)
		{
			// Undo Button
			olc::vi2d vTilePos = tv.GetTileUnderScreenPos(GetMousePos());
			int idx = vTilePos.y * m_vWorldSize.x + vTilePos.x;
			//vWorldMapPlayerGraphics[idx] = vWorldMapPlayerGraphics_undo[idx];
			if (bShowGridPlayer) vWorldMapPlayer[idx] = C64FileTileKey.Blank; // vWorldMapPlayer_undo[idx];
			if (bShowGridHero) vWorldMapHero[idx] = C64FileTileKey.Blank; //vWorldMapHero_undo[idx];
			if (bShowGridEnemies) vWorldMapEnemies[idx] = C64FileTileKey.Blank; //vWorldMapEnemies_undo[idx];
			if (bShowGridObjects) vWorldMapObjects[idx] = C64FileTileKey.Blank; // vWorldMapObjects_undo[idx];

		}


		if (GetKey(olc::L).bPressed)
		{
			// load a file

			LoadMap("assets/levelonea.bin");
		}

		if (GetKey(olc::R).bPressed)
		{
			// Save a file
			SaveMap("assets/levelonea.bin");
		}

		if (GetKey(olc::C).bPressed)
		{
			// Clear
			for (int i = 0; i < vWorldMapPlayerGraphics.size(); i++)
			{
				vWorldMapPlayerGraphics[i] = C64FileTileKey.Blank;
				vWorldMapPlayer[i] = C64FileTileKey.Blank;
			}
		}

		if (GetKey(olc::G).bPressed)
		{
			bShowGrid = !bShowGrid;
			bShowGridPlayer = false;
			bShowGridHero = false;
			bShowGridEnemies = false;
			bShowGridObjects = false;

		}

		if (GetKey(olc::K1).bPressed)
		{
			bShowGridPlayer = true;
			bShowGridHero = false;
			bShowGridEnemies = false;
			bShowGridObjects = false;
		}

		if (GetKey(olc::K2).bPressed)
		{
			bShowGridPlayer = false;
			bShowGridHero = true;
			bShowGridEnemies = false;
			bShowGridObjects = false;
		}

		if (GetKey(olc::K3).bPressed)
		{
			bShowGridPlayer = false;
			bShowGridHero = false;
			bShowGridEnemies = true;
			bShowGridObjects = false;
		}

		if (GetKey(olc::K4).bPressed)
		{
			bShowGridPlayer = false;
			bShowGridHero = false;
			bShowGridEnemies = false;
			bShowGridObjects = true;
		}

		if (GetKey(olc::B).bPressed)
		{
			// We want to drop a bomb
			size_t idx = ((int)objectPlayer.vPos.y * m_vWorldSize.x) + (int)objectPlayer.vPos.x;
			idx = std::min(idx, (vWorldMapObjects.size() - 1)); // Edge case, we to ensure we are within the array range
			vWorldMapObjects[idx] = C64FileTileKey.SetBomb1;
			sWorldObject worldObject = objectBomb;
			worldObject.fStartIndex = idx;
			vecObjectBombs.push_back({ worldObject });
		}
		if (GetKey(olc::E).bPressed)
		{
			// We want to drop a bomb
			size_t idx = ((int)objectPlayer.vPos.y * m_vWorldSize.x) + (int)objectPlayer.vPos.x;
			idx = std::min(idx, (vWorldMapObjects.size() - 1)); // Edge case, we to ensure we are within the array range
			vWorldMapObjects[idx] = C64FileTileKey.SetExplosion1;
			sWorldObject worldObject = objectExplosion;
			worldObject.fStartIndex = idx;
			vecObjectExplosion.push_back({ worldObject });
		}

	}

	// Handle borders
	void HandleBorders(sWorldObject* worldObject)
	{


		if (worldObject->vPos.x < 0.00f ||
			worldObject->vPos.x < worldObject->vStartPos.x ||
			worldObject->vPos.x < tv.GetTopLeftTile().x)
		{
			worldObject->bEnabled = false;
			worldObject->bVelChanged = false;
			worldObject->bVelChanged = false;
		}
		if (worldObject->vPos.x > m_vWorldSize.x ||
			worldObject->vPos.x > worldObject->vEndPos.x ||
			worldObject->vPos.x > tv.GetBottomRightTile().x)
		{
			worldObject->bEnabled = false;
			worldObject->bVelChanged = false;

		}

		if (worldObject->vPos.y < 0.01f)
		{
			worldObject->bEnabled = false;
			worldObject->bVelChanged = false;

		}

		if (worldObject->vPos.y > m_vWorldSize.y)
		{
			worldObject->bEnabled = false;
			worldObject->bVelChanged = false;

		}
	}


	float fLifeTime;
	// Handles the lost of a life
	void HandleGodMode(float fElapsedTime, sWorldObject* worldObject)
	{
		// When an object loses a life they get 5 seconds of GOD MODE, until they can again lose lives
		if (!worldObject->bCanLoseLives)
		{
			worldObject->fGodModeTime += fElapsedTime;
			if (worldObject->fGodModeTime > 5.0f)
			{
				worldObject->fGodModeTime = 0.0f;
				worldObject->bCanLoseLives = true;

			}
		}


	}

	// Handles the object when all lives are lost
	void HandleAllLivesLost(sWorldObject* worldObject)
	{
		// For reset we simply reset all the objects to thier default values

		if (!worldObject->bCanLoseLives) return; // They are in god mode
		
		if (worldObject->nLives < 0) worldObject->bIsDead = true;

		if (worldObject->bIsDead)
		{
			switch (worldObject->eObjecttype)
			{
			case HotAirBalloon::PlayerObject:
			{
				worldObject->bIsDead = false;
				worldObject->bEnabled = true;
				worldObject->nLives = worldObject->nDefaultLives;
				break;
			}

			case HotAirBalloon::HeroObject:
			case HotAirBalloon::EnemiesObject:
			{
				// Special case we only reset enemies if the game is been rest. i.e the player isDead
				worldObject->bIsDead = false;
				worldObject->bEnabled = false;
				
				break;
			}

			case HotAirBalloon::BombObject:
			{
				for (size_t i = 0; i < vecObjectBombs.size(); i++)
				{
					if (vecObjectBombs[i].bIsDead) {
						vecObjectBombs.erase(vecObjectBombs.begin() + i);
					}
				}
				break;
			}	
			case HotAirBalloon::ExplosionObject:
			{
				for (size_t i = 0; i < vecObjectExplosion.size(); i++)
				{
					if (vecObjectExplosion[i].bIsDead) {
						// ok we should now handle the explosion
						// however this is occuring as the bomb is stuck.... need to have a think about this
						vecObjectExplosion.erase(vecObjectExplosion.begin() + i);
					}
				}
				break;
			}

			default:
				break;
			}
		}
	}

	void HandleReset(sWorldObject* worldObject = nullptr)
	{
		if (worldObject == nullptr)
		{
			// Reset everything
			objectPlayer.bCanLoseLives = false;
			objectPlayer.bIsDead = false;
			objectPlayer.nLives = objectPlayer.nDefaultLives;
			objectPlayer.vPos = { 3.0f, 3.0f };
			vTrackedPoint = objectPlayer.vPos;

			// Clear the bombs
			vecObjectBombs.clear();
			vecObjectExplosion.clear();

			for (auto& heroObject : vecObjectHeros)
			{
				heroObject.bEnabled = false;
				heroObject.bIsDead = false;
				heroObject.nLives = heroObject.nDefaultLives;
				heroObject.vPos = { 3.0f, 3.0f };
			}

			for (auto& enemiesObject : vecObjectEnemies)
			{
				enemiesObject.bEnabled = false;
				enemiesObject.bIsDead = false;
				enemiesObject.nLives = enemiesObject.nDefaultLives;
				enemiesObject.vPos = { 3.0f, 3.0f };
			}

		}
		else
		{
			worldObject->bCanLoseLives = false;
			worldObject->bIsDead = false;
			worldObject->nLives = objectPlayer.nDefaultLives;
		}
	}

	float fChangeMessageTime = 0.0f;

	void HandleMessages(float fElapsedTime)
	{
		fChangeMessageTime += fElapsedTime;
		vecMessages.clear();
		switch (CurrentMessages)
		{
		case HotAirBalloon::Welcome:
		{
			if (fChangeMessageTime > 5)
			{
				fChangeMessageTime = 0.0f;
				CurrentMessages = HotAirBalloon::Scores;
				HandleMessages(fElapsedTime);
			}
			else
			{
				vecMessages.push_back({ strPrintRes });
				vecMessages.push_back({ strMovement });
				vecMessages.push_back({ strMission });
			}
			
			break;
		}	
		case HotAirBalloon::Scores:
		{
			std::string message = strTotalScore + std::to_string(nTotalScore);
			vecMessages.push_back({ message });	// TOTAL SCORE: 

			message = strPlayLives + std::to_string(nPlayerLives);
			vecMessages.push_back({ message });	// PLAYER LIVES:

			message = strEnemiesAlive + std::to_string(nTotalEnemiesLeft);
			vecMessages.push_back({ message }); // ENEMIES LEFT:

			message = strHeroLives + std::to_string(nHeroLives);
			vecMessages.push_back({ message });    // HERO LIVES:
			fChangeMessageTime = 0.0f;
			break;
		}
		case HotAirBalloon::ForgotRick:
		{
			if (fChangeMessageTime > 5)
			{
				fChangeMessageTime = 0.0f;
				CurrentMessages = HotAirBalloon::Scores;
				HandleMessages(fElapsedTime);
			}
			else
			{
				vecMessages.push_back({ strRickForgot });	// YOU FORGOT RICK!!
			}
			
			break;
		}
		case HotAirBalloon::RickDead:
		{
			if (fChangeMessageTime > 5)
			{
				fChangeMessageTime = 0.0f;
				CurrentMessages = HotAirBalloon::Welcome;
				HandleReset();
				HandleMessages(fElapsedTime);
			}
			else
			{
				vecMessages.push_back({ strRickDead });		// RICK IS DEAD, GAME OVER!
			}
			
			break;
		}
		case HotAirBalloon::YouDead:
		{
			if (fChangeMessageTime > 5)
			{
				fChangeMessageTime = 0.0f;
				CurrentMessages = HotAirBalloon::Welcome;
				HandleReset();
				HandleMessages(fElapsedTime);
			}
			else
			{
				vecMessages.push_back({ strRickDead });		// YOU DEAD, GAME OVER!
			}
			
			break;
		}
			
		default:

			break;
		}

	}

	int nTotalScore = 0;
	int nTotalEnemiesLeft = 0;
	int nPlayerLives = 0;
	int nHeroLives = 0;
	void HandleScores()
	{
		nTotalEnemiesLeft = vecObjectEnemies.size();
		// lets get the total score and emenies left;
		for (auto& enemiesObject : vecObjectEnemies)
		{
			if (enemiesObject.bIsDead)
			{
				nTotalScore += 10;
				nTotalEnemiesLeft--;
			}
		}

		nPlayerLives = objectPlayer.nLives;

		for (auto& heroObject : vecObjectHeros)
		{
			// we only care about hero 1
			if (heroObject.C64FileKey == C64FileTileKey.SetHero1)
			{
				// We have Rick
				nHeroLives = heroObject.nLives;
				break;
			}
		}


	}

	// Handle the Game graphics
	void HandleGraphics(float fElapsedTime)
	{

		// Handle player "physics" in response to key presses
		objectPlayer.vVel = { 0.0f, 0.2f };
		objectPlayer.pDecal = decColourBalloon;
		if (GetKey(olc::Key::W).bHeld || GetKey(olc::Key::UP).bHeld)
		{
			objectPlayer.vVel += {0, -1}; // up
			objectPlayer.pDecal = decColourBalloonUp;
		}

		if (GetKey(olc::Key::S).bHeld || GetKey(olc::Key::DOWN).bHeld)
		{
			objectPlayer.vVel += {0, +1}; // down
			objectPlayer.pDecal = decColourBalloonDown;
		}

		if (GetKey(olc::Key::A).bHeld || GetKey(olc::Key::LEFT).bHeld)
		{
			objectPlayer.vVel += {-1, 0}; // left

		}

		if (GetKey(olc::Key::D).bHeld || GetKey(olc::Key::RIGHT).bHeld)
		{
			objectPlayer.vVel += {+1, 0}; // right

		}

		vTrackedPoint += objectPlayer.vVel * 4.0f * fElapsedTime;

		for (auto& worldObject : vecObjectHeros)
		{
			if (worldObject.bEnabled)
			{
				DrawWorldObjects(fElapsedTime, &worldObject, false); // Draw Background worldObjects
				worldObject.vVel = { 0.0f, 0.0f };
				if (worldObject.bCanMove)
				{
					if (worldObject.bRunningRight)
					{
						worldObject.vVel += {+worldObject.fVelX, worldObject.fVelY};
					}
					else
					{
						worldObject.vVel += {-worldObject.fVelX, -worldObject.fVelY};
					};
					worldObject.vPotentialPosition = worldObject.vPos + worldObject.vVel * 4.0f * fElapsedTime;
					worldObject.bVelChanged = true;
				}

			}

		}
		//vecObjectEnemies
		for (auto& worldObject : vecObjectEnemies)
		{
			if (worldObject.bEnabled)
			{
				DrawWorldObjects(fElapsedTime, &worldObject, false); // Draw Background worldObjects
				worldObject.vVel = { 0.0f, 0.0f };
				if (worldObject.bCanMove)
				{
					if (worldObject.bRunningRight)
					{
						worldObject.vVel += {+worldObject.fVelX, worldObject.fVelY};
					}
					else
					{
						worldObject.vVel += {-worldObject.fVelX, worldObject.fVelY};
					};
					worldObject.vPotentialPosition = worldObject.vPos + worldObject.vVel * 4.0f * fElapsedTime;
					worldObject.bVelChanged = true;
				}

			}

		}

		for (auto& worldObject : vecObjectBombs)
		{
			if (worldObject.bEnabled)
			{
				DrawWorldObjects(fElapsedTime, &worldObject, false); // Draw Background worldObjects
				worldObject.vVel = { 0.0f, 0.2f };
				if (worldObject.bCanMove)
				{
					if (worldObject.bRunningRight)
					{
						worldObject.vVel += {+worldObject.fVelX, worldObject.fVelY};
					}
					else
					{
						worldObject.vVel += {-worldObject.fVelX, worldObject.fVelY};
					};
					worldObject.vPotentialPosition = worldObject.vPos + worldObject.vVel * 4.0f * fElapsedTime;
					worldObject.bVelChanged = true;
				}

			}

		}

		// true is returned
		bool bOnScreen = camera.Update(fElapsedTime);

		// Set the transformed view to that required by the camera
		tv.SetWorldOffset(camera.GetViewPosition());

		/// coll
		// Where will object be worst case?
		objectPlayer.vPotentialPosition = objectPlayer.vPos + objectPlayer.vVel * 4.0f * fElapsedTime;
		olc::vf2d vRayToNearest;

		// Render "tile map", by getting visible tiles
		olc::vi2d vTileTL = tv.GetTopLeftTile().max({ 0,0 });
		olc::vi2d vTileBR = tv.GetBottomRightTile().min(m_vWorldSize);
		olc::vi2d vTile;
		// Then looping through them and drawing them
		for (vTile.y = vTileTL.y; vTile.y < vTileBR.y; vTile.y++)
			for (vTile.x = vTileTL.x; vTile.x < vTileBR.x; vTile.x++)
			{
				int idx = vTile.y * m_vWorldSize.x + vTile.x;

				// TODO, Lets just set the background to blue
				//tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Blue);

				// Lets get our collison
				if (vWorldMapPlayer[idx] == C64FileTileKey.SetBlockPlayer)
				{
					HandleCollison(fElapsedTime, &vTile, &objectPlayer);
					for (auto& worldObject : vecObjectBombs)
					{
						HandleCollison(fElapsedTime, &vTile, &worldObject);
					}

					if (bShowGrid && bShowGridPlayer)
					{
						tv.FillRectDecal({ (float)vTile.x, (float)vTile.y }, { 1.0f, 1.0f }, C64Color.Red);
						continue;

					}

				}

				if (vWorldMapObjects[idx] == C64FileTileKey.SetHero1)
				{
					EnableWorldObject(vTile, WorldObjectType::HeroObject, true, idx, vWorldMapObjects[idx]);

					if (bShowGrid && bShowGridObjects)
					{
						tv.FillRectDecal({ (float)vTile.x, (float)vTile.y }, { 1.0f, 1.0f }, C64Color.Yellow);
						continue;
					}


				}

				if (vWorldMapObjects[idx] == C64FileTileKey.SetHero2)
				{
					EnableWorldObject(vTile, WorldObjectType::HeroObject, true, idx, vWorldMapObjects[idx]);
					if (bShowGrid && bShowGridObjects)
					{
						tv.FillRectDecal({ (float)vTile.x, (float)vTile.y }, { 1.0f, 1.0f }, C64Color.Orange);
						continue;
					}


				}

				if (vWorldMapObjects[idx] == C64FileTileKey.SetHero3)
				{
					EnableWorldObject(vTile, WorldObjectType::HeroObject, true, idx, vWorldMapObjects[idx]);
					if (bShowGrid && bShowGridObjects)
					{
						tv.FillRectDecal({ (float)vTile.x, (float)vTile.y }, { 1.0f, 1.0f }, C64Color.LightGreen);
						continue;
					}


				}

				if (vWorldMapObjects[idx] == C64FileTileKey.SetHero4)
				{
					EnableWorldObject(vTile, WorldObjectType::HeroObject, true, idx, vWorldMapObjects[idx]);
					if (bShowGrid && bShowGridObjects)
					{
						tv.FillRectDecal({ (float)vTile.x, (float)vTile.y }, { 1.0f, 1.0f }, C64Color.Purple);
						continue;
					}


				}

				if (vWorldMapObjects[idx] == C64FileTileKey.SetEnemies1)
				{
					EnableWorldObject(vTile, WorldObjectType::EnemiesObject, true, idx, vWorldMapObjects[idx]);

					if (bShowGrid && bShowGridObjects)
					{
						tv.FillRectDecal({ (float)vTile.x, (float)vTile.y }, { 1.0f, 1.0f }, C64Color.LightRed);
						continue;
					}


				}

				if (vWorldMapObjects[idx] == C64FileTileKey.SetEnemies2)
				{
					EnableWorldObject(vTile, WorldObjectType::EnemiesObject, false, idx, vWorldMapObjects[idx]);

					if (bShowGrid && bShowGridObjects)
					{
						tv.FillRectDecal({ (float)vTile.x, (float)vTile.y }, { 1.0f, 1.0f }, C64Color.Red);
						continue;
					}


				}

				if (vWorldMapObjects[idx] == C64FileTileKey.SetEnemies3)
				{
					EnableWorldObject(vTile, WorldObjectType::EnemiesObject, false, idx, vWorldMapObjects[idx]);

					if (bShowGrid && bShowGridObjects)
					{
						tv.FillRectDecal({ (float)vTile.x, (float)vTile.y }, { 1.0f, 1.0f }, C64Color.Purple);
						continue;
					}


				}

				if (vWorldMapObjects[idx] == C64FileTileKey.SetEnemies4)
				{
					EnableWorldObject(vTile, WorldObjectType::EnemiesObject, false, idx, vWorldMapObjects[idx]);

					if (bShowGrid && bShowGridObjects)
					{
						tv.FillRectDecal({ (float)vTile.x, (float)vTile.y }, { 1.0f, 1.0f }, C64Color.Green);
						continue;
					}


				}

				if (vWorldMapObjects[idx] == C64FileTileKey.SetEnemies5)
				{
					EnableWorldObject(vTile, WorldObjectType::EnemiesObject, false, idx, vWorldMapObjects[idx]);

					if (bShowGrid && bShowGridObjects)
					{
						tv.FillRectDecal({ (float)vTile.x, (float)vTile.y }, { 1.0f, 1.0f }, C64Color.LightGreen);
						continue;
					}


				}

				if (vWorldMapObjects[idx] == C64FileTileKey.SetEnemies6)
				{
					EnableWorldObject(vTile, WorldObjectType::EnemiesObject, false, idx, vWorldMapObjects[idx]);

					if (bShowGrid && bShowGridObjects)
					{
						tv.FillRectDecal({ (float)vTile.x, (float)vTile.y }, { 1.0f, 1.0f }, C64Color.LightGreen);
						continue;
					}


				}

				if (vWorldMapObjects[idx] == C64FileTileKey.SetBomb1)
				{
					EnableWorldObject(vTile, WorldObjectType::BombObject, true, idx, vWorldMapObjects[idx]);

				}

				if (vWorldMapObjects[idx] == C64FileTileKey.SetExplosion1)
				{
					EnableWorldObject(vTile, WorldObjectType::ExplosionObject, true, idx, vWorldMapObjects[idx]);

				}

				if (vWorldMapHero[idx] == C64FileTileKey.SetBlockHero)
				{

					for (auto& worldObject : vecObjectHeros)
					{
						HandleCollison(fElapsedTime, &vTile, &worldObject);
					}

					if (bShowGrid && bShowGridHero)
					{
						tv.FillRectDecal({ (float)vTile.x, (float)vTile.y }, { 1.0f, 1.0f }, C64Color.Yellow);
						continue;
					}


				}

				if (vWorldMapEnemies[idx] == C64FileTileKey.SetBlockEnemies)
				{
					for (auto& worldObject : vecObjectEnemies)
					{
						HandleCollison(fElapsedTime, &vTile, &worldObject);
					}

					if (bShowGrid && bShowGridEnemies)
					{
						tv.FillRectDecal({ (float)vTile.x, (float)vTile.y }, { 1.0f, 1.0f }, C64Color.LightBlue);
						continue;
					}

				}

				if (vWorldMapPlayerGraphics[idx] == C64FileTileKey.Blank)
				{
					if (bShowGrid)
					{
						tv.DrawRectDecal({ (float)vTile.x, (float)vTile.y }, { 1.0f, 1.0f }, C64Color.DarkGrey);
					}


				}

				if (vWorldMapPlayerGraphics[idx] == C64FileTileKey.GetSprite)
				{
					if (vTile.y > 8)
					{
						// We now need the SpriteSheet position
						// We know our screen is 320X240, and our SpriteSheet is 2048X160 and it is anchored to bottom of the screen
						// We do not care about the space below 80 realworld / 5 view world, and we dont care about the width
						// therefore we need some offsets
						olc::vi2d vSourcePos = { vTile.x, vTile.y - 10 }; // SpriteSheet Title position
						vSourcePos = vSourcePos * tv.GetWorldScale(); // SpriteSheet pixel position

						// OK now we get where in our realWorld to draw the decal
						olc::vi2d vScreenPos = vTile * tv.GetWorldScale();
						tv.DrawPartialDecal(vTile, tv.GetWorldScale(), decC64Level, vSourcePos, tv.GetWorldScale());
						//tv.FillRectDecal(vTile, { 1.0f, 1.0f }, olc::Pixel(60, 60, 60, 127));
					}
					continue;

				}

				if (vWorldMapPlayerGraphics[idx] == C64FileTileKey.Black)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Black);
					continue;
				}

				if (vWorldMapPlayerGraphics[idx] == C64FileTileKey.Blue)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Blue);
					continue;
				}

				if (vWorldMapPlayerGraphics[idx] == C64FileTileKey.Brown)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Brown);
					continue;
				}

				if (vWorldMapPlayerGraphics[idx] == C64FileTileKey.Cyan)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Cyan);
					continue;
				}

				if (vWorldMapPlayerGraphics[idx] == C64FileTileKey.DarkGrey)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.DarkGrey);
					continue;
				}

				if (vWorldMapPlayerGraphics[idx] == C64FileTileKey.Green)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Green);
					continue;
				}

				if (vWorldMapPlayerGraphics[idx] == C64FileTileKey.Grey)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Green);
					continue;
				}

				if (vWorldMapPlayerGraphics[idx] == C64FileTileKey.LightBlue)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.LightBlue);
					continue;
				}

				if (vWorldMapPlayerGraphics[idx] == C64FileTileKey.LightGreen)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.LightGreen);
					continue;
				}


				if (vWorldMapPlayerGraphics[idx] == C64FileTileKey.LightGrey)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.LightGrey);
					continue;
				}

				if (vWorldMapPlayerGraphics[idx] == C64FileTileKey.LightRed)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.LightRed);
					continue;
				}

				if (vWorldMapPlayerGraphics[idx] == C64FileTileKey.Orange)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Orange);
					continue;
				}


				if (vWorldMapPlayerGraphics[idx] == C64FileTileKey.Purple)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Purple);
					continue;
				}

				if (vWorldMapPlayerGraphics[idx] == C64FileTileKey.Red)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Red);
					continue;
				}

				if (vWorldMapPlayerGraphics[idx] == C64FileTileKey.White)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.White);
					continue;
				}


				if (vWorldMapPlayerGraphics[idx] == C64FileTileKey.Yellow)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Yellow);
					continue;
				}


			}


		// Some borders 
		if (vTrackedPoint.x < 0.00f)
		{
			vTrackedPoint.x = 0.00f;
			objectPlayer.vPos.x = 0.0f;
		}
		if (vTrackedPoint.x > m_vWorldSize.x)
		{
			vTrackedPoint.x = m_vWorldSize.x;
			objectPlayer.vPos.x = m_vWorldSize.x;
		}

		if (vTrackedPoint.y < 0.01f)
		{
			vTrackedPoint.y = 0.01f;
			objectPlayer.vPos.y = 0.01f;
		}

		if (vTrackedPoint.y > m_vWorldSize.y)
		{
			vTrackedPoint.y = m_vWorldSize.y;
			objectPlayer.vPos.y = m_vWorldSize.y;
		}


		// Draw our balloon
		if (!objectPlayer.bCanLoseLives)
		{
			// God mode
			objectPlayer.fTottleTime += fElapsedTime;
			if (objectPlayer.fTottleTime > objectPlayer.fFlashTime)
			{
				objectPlayer.fTottleTime = 0.0f;
				objectPlayer.bShowHide = !objectPlayer.bShowHide;
			}
		}

		if (objectPlayer.bCanLoseLives || objectPlayer.bShowHide)
			tv.DrawDecal(vTrackedPoint - olc::vf2d(1.5f, 1.5f), objectPlayer.pDecal);


		HandleBorders(&objectPlayer);
		HandleAllLivesLost(&objectPlayer);
		// if the player is dead it is time to reset
		if (objectPlayer.bIsDead)
		{
			HandleReset();
		}
		HandleGodMode(fElapsedTime, &objectPlayer);

		for (auto& heroObject : vecObjectHeros) // Handles Hero v Player
		{
			HandleBorders(&heroObject);
			HandleAllLivesLost(&heroObject);
			DrawWorldObjects(fElapsedTime, &heroObject, true);
			HandleObjectCollison(&heroObject, &objectPlayer, true);
			HandleGodMode(fElapsedTime, &heroObject);

		}

		for (auto& enemiesObject : vecObjectEnemies)
		{
			HandleBorders(&enemiesObject);
			HandleAllLivesLost(&enemiesObject);
			DrawWorldObjects(fElapsedTime, &enemiesObject, true);
			HandleObjectCollison(&enemiesObject, &objectPlayer, true); //handles enemies v player
			for (auto& heroObject : vecObjectHeros) // Handles Hero v Player
			{
				HandleObjectCollison(&heroObject, &enemiesObject, true);  //handles enemies v hero
				//HandleGodMode(fElapsedTime, &heroObject);

			}

			//TODO: Enemies v Hero
			HandleGodMode(fElapsedTime, &enemiesObject);

		}

		for (auto& bombObject : vecObjectBombs)
		{
			HandleAllLivesLost(&bombObject);
			DrawWorldObjects(fElapsedTime, &bombObject, true);
			//HandleObjectCollison(&bombObject, &objectPlayer, true);	// bombs do not affect the player
			for (auto& heroObject : vecObjectHeros) // Handles Hero v Player
			{
				HandleObjectCollison(&heroObject, &bombObject, true);  //handles enemies v hero
				

			}
			for (auto& enemiesObject : vecObjectEnemies)
			{
				HandleObjectCollison(&enemiesObject, &bombObject, true);  //handles enemies v hero
				
			}

		}


		for (auto& explosionObject : vecObjectExplosion)
		{
			HandleAllLivesLost(&explosionObject);
			DrawWorldObjects(fElapsedTime, &explosionObject, true);
			
			for (auto& heroObject : vecObjectHeros) // Handles Hero v Player
			{
				HandleObjectCollison(&heroObject, &explosionObject, true);  //handles enemies v hero
				

			}
			for (auto& enemiesObject : vecObjectEnemies)
			{
				HandleObjectCollison(&enemiesObject, &explosionObject, true);  //handles enemies v hero
				
			}

			
		}

		HandleInput(fElapsedTime, vTile);


	}



	// Game Save
private:

	void LoadMap(std::string sFilename)
	{
		std::ifstream file(sFilename, std::ios::in | std::ios::binary);

		if (file.is_open())
		{
			file.read((char*)&m_vWorldSize, sizeof(olc::vi2d));
			file.read((char*)&m_vTileSize, sizeof(olc::vi2d));

			// Graphics World
			for (int i = 0; i < vWorldMapPlayerGraphics.size(); i++)
			{
				file.read((char*)&vWorldMapPlayerGraphics[i], sizeof(uint8_t));
			}

			for (size_t i = 0; i < vWorldMapPlayerGraphics.size(); i++)
			{
				vWorldMapPlayerGraphics_undo[i] = vWorldMapPlayerGraphics[i];
			}

			// Player World
			for (int i = 0; i < vWorldMapPlayer.size(); i++)
			{
				file.read((char*)&vWorldMapPlayer[i], sizeof(uint8_t));
			}

			for (size_t i = 0; i < vWorldMapPlayer.size(); i++)
			{
				vWorldMapPlayer_undo[i] = vWorldMapPlayer[i];
			}

			// Hero World
			for (int i = 0; i < vWorldMapHero.size(); i++)
			{
				file.read((char*)&vWorldMapHero[i], sizeof(uint8_t));
			}

			for (size_t i = 0; i < vWorldMapHero.size(); i++)
			{
				vWorldMapHero_undo[i] = vWorldMapHero[i];
			}

			// Enemies World
			for (int i = 0; i < vWorldMapEnemies.size(); i++)
			{
				file.read((char*)&vWorldMapEnemies[i], sizeof(uint8_t));
			}

			for (size_t i = 0; i < vWorldMapEnemies.size(); i++)
			{
				vWorldMapEnemies_undo[i] = vWorldMapEnemies[i];
			}

			for (int i = 0; i < vWorldMapObjects.size(); i++)
			{
				file.read((char*)&vWorldMapObjects[i], sizeof(uint8_t));
			}

			for (size_t i = 0; i < vWorldMapObjects.size(); i++)
			{
				vWorldMapObjects[i] = vWorldMapObjects[i];
			}

			file.close();


		}




	}

	void SaveMap(std::string sFilename)
	{
		std::ofstream file(sFilename, std::ios::out | std::ios::binary);
		file.write((char*)&m_vWorldSize.x, sizeof(olc::vi2d));
		file.write((char*)&m_vTileSize, sizeof(olc::vi2d));

		// Graphic world
		for (size_t i = 0; i < vWorldMapPlayerGraphics.size(); i++)
		{
			file.write((char*)&vWorldMapPlayerGraphics[i], sizeof(uint8_t));
		}

		// Player world
		for (size_t i = 0; i < vWorldMapPlayer.size(); i++)
		{
			file.write((char*)&vWorldMapPlayer[i], sizeof(uint8_t));
		}

		// Hero world
		for (size_t i = 0; i < vWorldMapHero.size(); i++)
		{
			file.write((char*)&vWorldMapHero[i], sizeof(uint8_t));
		}


		// Enemies World
		for (size_t i = 0; i < vWorldMapEnemies.size(); i++)
		{
			file.write((char*)&vWorldMapEnemies[i], sizeof(uint8_t));
		}

		// Objects World
		for (size_t i = 0; i < vWorldMapObjects.size(); i++)
		{
			file.write((char*)&vWorldMapObjects[i], sizeof(uint8_t));
		}

		file.close();
	}

public:
	bool OnUserCreate() override
	{
		// Lets build up our colour code (will make life easier later
		C64LoadColourCodes();
		C64CreateBalloonSprite();
		C64CreateColourBalloonSprite();
		C64CreateColourBalloonSpriteUP();
		C64CreateColourBalloonSpriteDown();
		C64CreateColourBalloonSpriteLeft();
		C64CreateColourBalloonSpriteRight();

		// Construct transform view
		tv = olc::TileTransformedView(GetScreenSize(), m_vTileSize);

		// Construct Camera
		vTrackedPoint = { 1.0f, 5.0f };
		camera = olc::utils::Camera2D(GetScreenSize() / m_vTileSize, vTrackedPoint);

		// Configure Camera
		camera.SetTarget(vTrackedPoint);
		camera.SetMode(olc::utils::Camera2D::Mode::Simple);
		camera.SetWorldBoundary({ 0.0f, 0.0f }, m_vWorldSize);
		camera.EnableWorldBoundary(true);

		// Create "tile map" world with just two tiles
		vWorldMapPlayerGraphics.resize(m_vWorldSize.x * m_vWorldSize.y);
		vWorldMapPlayerGraphics_undo.resize(m_vWorldSize.x * m_vWorldSize.y);
		vWorldMapPlayer.resize(m_vWorldSize.x * m_vWorldSize.y);
		vWorldMapPlayer_undo.resize(m_vWorldSize.x * m_vWorldSize.y);
		vWorldMapHero.resize(m_vWorldSize.x * m_vWorldSize.y);
		vWorldMapHero_undo.resize(m_vWorldSize.x * m_vWorldSize.y);
		vWorldMapEnemies.resize(m_vWorldSize.x * m_vWorldSize.y);
		vWorldMapEnemies_undo.resize(m_vWorldSize.x * m_vWorldSize.y);
		vWorldMapObjects.resize(m_vWorldSize.x * m_vWorldSize.y);
		vWorldMapObjects_undo.resize(m_vWorldSize.x * m_vWorldSize.y);


		// Set default to C64FileKeyBlank
		for (int i = 0; i < vWorldMapPlayerGraphics.size(); i++)
		{
			vWorldMapPlayerGraphics[i] = C64FileTileKey.Blank;
			vWorldMapPlayerGraphics_undo[i] = C64FileTileKey.Blank;
			vWorldMapPlayer[i] = C64FileTileKey.Blank;
			vWorldMapPlayer_undo[i] = C64FileTileKey.Blank;
			vWorldMapHero[i] = C64FileTileKey.Blank;
			vWorldMapHero_undo[i] = C64FileTileKey.Blank;
			vWorldMapEnemies[i] = C64FileTileKey.Blank;
			vWorldMapEnemies_undo[i] = C64FileTileKey.Blank;
			vWorldMapObjects[i] = C64FileTileKey.Blank;
			vWorldMapObjects_undo[i] = C64FileTileKey.Blank;
		}


		// Load Level 1
		LoadLevel(1);

		// Load the sprite sheets
		LoadSpriteSheets();

		// Create the world objects, Heros, Enemies
		CreateWorldObjects();

		// Load the world object
		LoadWorldObjectsIntoMap();

		// Set background colour
		Clear(C64Color.Blue);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame, draws random coloured pixels
		SetDrawTarget(nullptr);

		if (GetKey(olc::SPACE).bPressed) bGameLoaded = true; // TODO: remove

		//if (!bStartRec) return true;


		if (!bGameLoaded)
		{
			FillRectDecal({ 0,0 }, { (float)ScreenWidth(), (float)ScreenHeight() }, C64Color.LightBlue);
			// We display the C64 screen and loading screen until the 'game' is loaded
			if (bGameLoading) C64LoadingScreen();
			C64DisplayScreen();
			C64DisplayHeader(fElapsedTime);

			return true;
		}


		HandleGraphics(fElapsedTime);
		
		HandleScores();
		
		if (nPlayerLives < 0) CurrentMessages = YouDead;
		if (nHeroLives < 0) CurrentMessages = RickDead;

		HandleMessages(fElapsedTime);
		nStep = 10.0f;
		for (auto& s : vecMessages)
		{
			DrawStringPropDecal( {15.0f, nStep}, s, C64Color.LightBlue, {1.0f, 0.8f});
			nStep += 10.0f;
		}
		vecMessages.clear();

		DrawStringPropDecal({ 15.0f, 225.0f }, strCOPY1, C64Color.White, { 0.4f, 0.4f });
		DrawStringPropDecal({ 15.0f, 230.0f }, strCOPY2, C64Color.White, { 0.4f, 0.4f });

		return true;
	}



};

int main()
{
	HotAirBalloon demo;
	if (demo.Construct(320, 240, 4, 3))
		demo.Start();
	return 0;
}