
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
		uint8_t SetBlockHero = -110; // Sets a block for Hero collison
		uint8_t SetBlockEmemies = -120; // Sets a block for Ememies collison


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
	std::string strLoad = "LOAD";
	std::string strPlay = "PRESS PLAY ON TAPE";
	std::string strLoading = "LOADING...";
	std::string strRun = "RUN";

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
		DrawStringPropDecal({ 45, 30 }, strHeaderText1, C64Color.LightBlue, { 1.0f, 0.8f });
		DrawStringPropDecal({ 30, 40 }, strHeaderText2, C64Color.LightBlue, { 1.0f, 0.8f });
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

	// Game Level Stuff
private:

	void LoadLevel(int8_t nLevel)
	{
		// for this demo there will only be one level
		// but add more as you wish

		// 1: We need the level graphics
		// CopyRight: https://www.spriters-resource.com/commodore_64/gianasisters30thanniversaryhack/sheet/199050/
		sprC64Level = new olc::Sprite("./assets/C64LevelOne.png");
		decC64Level = new olc::Decal(sprC64Level);

		LoadMap("./assets/Levelone.bin");

	}

	// Transform View Stuff
public:

	// Transformed view object to make world offsetting simple
	olc::TileTransformedView tv;

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
	bool bShowGridEmemies = false; // Hide/Show grid


	// The world map, stored as a 1D array of graphics
	std::vector<uint8_t> vWorldMapGraphics;
	std::vector<uint8_t> vWorldMapGraphics_undo;


	// The world map, stored as a 1D array for collison
	std::vector<uint8_t> vWorldMap;
	std::vector<uint8_t> vWorldMap_undo;

	void TestCode(float fElapsedTime)
	{
		
		// Handle player "physics" in response to key presses
		olc::vf2d vVel = { 0.0f, 0.0f };
		if (GetKey(olc::Key::W).bHeld || GetKey(olc::Key::UP).bHeld) vVel += {0, -1}; // up
		if (GetKey(olc::Key::S).bHeld || GetKey(olc::Key::DOWN).bHeld) vVel += {0, +1}; // down
		if (GetKey(olc::Key::A).bHeld || GetKey(olc::Key::LEFT).bHeld) vVel += {-1, 0}; // left
		if (GetKey(olc::Key::D).bHeld || GetKey(olc::Key::RIGHT).bHeld) vVel += {+1, 0}; // right
		vTrackedPoint += vVel * 4.0f * fElapsedTime;

		// Some borders 
		if (vTrackedPoint.x < 0.00f) vTrackedPoint.x = 0.00f;
		if (vTrackedPoint.x > m_vWorldSize.x) vTrackedPoint.x = 128.0f;
		if (vTrackedPoint.y < 0.01f) vTrackedPoint.y = 0.01f;
		if (vTrackedPoint.y > m_vWorldSize.y) vTrackedPoint.y = 15.0f;


		// true is returned
		bool bOnScreen = camera.Update(fElapsedTime);

		// Set the transformed view to that required by the camera
		tv.SetWorldOffset(camera.GetViewPosition());

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
				tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Blue);
				
				// Lets get our collison
				if (vWorldMap[idx] == C64FileTileKey.SetBlockPlayer)
				{
					if (bShowGrid && bShowGridPlayer) {
						tv.FillRectDecal({ (float)vTile.x, (float)vTile.y }, { 1.0f, 1.0f }, C64Color.Red);
						continue;
					}
				}

				if (vWorldMap[idx] == C64FileTileKey.SetBlockHero)
				{
					if (bShowGrid && bShowGridHero)
					{
						tv.FillRectDecal({ (float)vTile.x, (float)vTile.y }, { 1.0f, 1.0f }, C64Color.Yellow);
						continue;
					}
				}

				if (vWorldMap[idx] == C64FileTileKey.SetBlockHero)
				{
					if (bShowGrid && bShowGridEmemies)
					{
						tv.FillRectDecal({ (float)vTile.x, (float)vTile.y }, { 1.0f, 1.0f }, C64Color.LightBlue);
						continue;
					}
					
				}

				// TODO: Needs refactoring... no time in Jam time
				if (vWorldMapGraphics[idx] == C64FileTileKey.Blank)
				{
					if (bShowGrid)
					{
						tv.DrawRectDecal({ (float)vTile.x, (float)vTile.y }, { 1.0f, 1.0f }, C64Color.DarkGrey);
					}
						
					
				}

				if (vWorldMapGraphics[idx] == C64FileTileKey.GetSprite)
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


				if (vWorldMapGraphics[idx] == C64FileTileKey.Black)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Black);
					continue;
				}

				if (vWorldMapGraphics[idx] == C64FileTileKey.Blue)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Blue);
					continue;
				}

				if (vWorldMapGraphics[idx] == C64FileTileKey.Brown)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Brown);
					continue;
				}

				if (vWorldMapGraphics[idx] == C64FileTileKey.Cyan)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Cyan);
					continue;
				}

				if (vWorldMapGraphics[idx] == C64FileTileKey.DarkGrey)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.DarkGrey);
					continue;
				}


				if (vWorldMapGraphics[idx] == C64FileTileKey.Green)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Green);
					continue;
				}

				if (vWorldMapGraphics[idx] == C64FileTileKey.Grey)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Green);
					continue;
				}


				if (vWorldMapGraphics[idx] == C64FileTileKey.LightBlue)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.LightBlue);
					continue;
				}

				
				if (vWorldMapGraphics[idx] == C64FileTileKey.LightGreen)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.LightGreen);
					continue;
				}


				if (vWorldMapGraphics[idx] == C64FileTileKey.LightGrey)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.LightGrey);
					continue;
				}

				if (vWorldMapGraphics[idx] == C64FileTileKey.LightRed)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.LightRed);
					continue;
				}


				if (vWorldMapGraphics[idx] == C64FileTileKey.Orange)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Orange);
					continue;
				}

				
				if (vWorldMapGraphics[idx] == C64FileTileKey.Purple)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Purple);
					continue;
				}


				if (vWorldMapGraphics[idx] == C64FileTileKey.Red)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Red);
					continue;
				}

				if (vWorldMapGraphics[idx] == C64FileTileKey.White)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.White);
					continue;
				}


				if (vWorldMapGraphics[idx] == C64FileTileKey.Yellow)
				{
					tv.FillRectDecal(vTile, { 1.0, 1.0 }, C64Color.Yellow);
					continue;
				}


			}

		// Draw our balloon
		tv.DrawDecal(vTrackedPoint - olc::vf2d(0.5f, 0.5f), decBalloon);

		/*DrawStringPropDecal({ 2,12 }, "WASD  : Move", olc::YELLOW);

		DrawStringPropDecal({ 2,42 }, vTrackedPoint.str(), olc::YELLOW);*/

		if (GetMouse(0).bHeld || GetMouse(0).bPressed)
		{
			olc::vi2d vTilePos = tv.GetTileUnderScreenPos(GetMousePos());
			tv.FillRectDecal(vTile, { 1.0f, 1.0f }, olc::Pixel(60, 60, 60, 127));

			int idx = vTilePos.y * m_vWorldSize.x + vTilePos.x;
			//vWorldMapGraphics[idx] = C64FileTileKey.Black;
			if(bShowGridPlayer) vWorldMap[idx] = C64FileTileKey.SetBlockPlayer;
			if (bShowGridHero) vWorldMap[idx] = C64FileTileKey.SetBlockHero;
			if (bShowGridEmemies) vWorldMap[idx] = C64FileTileKey.SetBlockEmemies;
			
		}
		if (GetMouse(1).bHeld || GetMouse(1).bPressed)
		{
			// Undo Button
			olc::vi2d vTilePos = tv.GetTileUnderScreenPos(GetMousePos());
			int idx = vTilePos.y * m_vWorldSize.x + vTilePos.x;
			//vWorldMapGraphics[idx] = vWorldMapGraphics_undo[idx];
			vWorldMap[idx] = vWorldMap_undo[idx];
		}


		if (GetKey(olc::L).bPressed)
		{
			// load a file
			
			LoadMap("./assets/levelone.bin");
		}

		if (GetKey(olc::S).bPressed)
		{
			// Save a file
			SaveMap("./assets/levelone.bin");
		}

		if (GetKey(olc::C).bPressed)
		{
			// Clear
			for (int i = 0; i < vWorldMapGraphics.size(); i++)
			{
				vWorldMapGraphics[i] = C64FileTileKey.Blank;
				vWorldMap[i] = C64FileTileKey.Blank;
			}
		}

		if (GetKey(olc::G).bPressed)
		{
			bShowGrid = !bShowGrid;
			bShowGridPlayer = false;
			bShowGridHero = false;
			bShowGridEmemies = false;

		}

		if (GetKey(olc::G).bHeld && GetKey(olc::K1).bPressed)
		{
			bShowGridPlayer = true;
			bShowGridPlayer = false;
			bShowGridPlayer = false;
		}


		if (GetKey(olc::G).bHeld && GetKey(olc::K2).bPressed)
		{
			bShowGridPlayer = false;
			bShowGridPlayer = true;
			bShowGridPlayer = false;
		}
			
		if (GetKey(olc::G).bHeld && GetKey(olc::K3).bPressed) 
		{
			bShowGridPlayer = false;
			bShowGridPlayer = false;
			bShowGridPlayer = true;
		}

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

				for (int i = 0; i < vWorldMapGraphics.size(); i++)
				{
					file.read((char*)&vWorldMapGraphics[i], sizeof(uint8_t));
				}

				for (int i = 0; i < vWorldMap.size(); i++)
				{
					file.read((char*)&vWorldMap[i], sizeof(uint8_t));
				}

				for (size_t i = 0; i < vWorldMapGraphics.size(); i++)
				{
					vWorldMapGraphics_undo[i] = vWorldMapGraphics[i];
				}

				for (size_t i = 0; i < vWorldMap.size(); i++)
				{
					vWorldMap_undo[i] = vWorldMap[i];
				}

				file.close();


			}



			
		}

		void SaveMap(std::string sFilename)
		{
			std::ofstream file(sFilename, std::ios::out | std::ios::binary);
			file.write((char*)&m_vWorldSize.x, sizeof(olc::vi2d));
			file.write((char*)&m_vTileSize, sizeof(olc::vi2d));

			for (size_t i = 0; i < vWorldMapGraphics.size(); i++)
			{
				file.write((char*)&vWorldMapGraphics[i], sizeof(uint8_t));
			}

			for (size_t i = 0; i < vWorldMap.size(); i++)
			{
				file.write((char*)&vWorldMap[i], sizeof(uint8_t));
			}


			file.close();
		}

public:
	bool OnUserCreate() override
	{
		// Lets build up our colour code (will make life easier later
		C64LoadColourCodes();

		C64CreateBalloonSprite();

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
		vWorldMapGraphics.resize(m_vWorldSize.x * m_vWorldSize.y);
		vWorldMapGraphics_undo.resize(m_vWorldSize.x * m_vWorldSize.y);
		vWorldMap.resize(m_vWorldSize.x * m_vWorldSize.y);
		vWorldMap_undo.resize(m_vWorldSize.x * m_vWorldSize.y);


		// Set default
		/*for (int i = 0; i < vWorldMapGraphics.size(); i++)
			vWorldMapGraphics[i] = ((rand() % 20) == 1) ? 1 : 0;*/
		for (int i = 0; i < vWorldMapGraphics.size(); i++)
		{
			vWorldMap[i] = C64FileTileKey.Blank;
			vWorldMap_undo[i] = C64FileTileKey.Blank;
			vWorldMapGraphics[i] = C64FileTileKey.Blank;
			vWorldMapGraphics_undo[i] = C64FileTileKey.Blank;
		}


		// Load Level 1
		LoadLevel(1);

		// Set background colour
		Clear(C64Color.Blue);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame, draws random coloured pixels
		SetDrawTarget(nullptr);
		
		//if (GetKey(olc::SPACE).bPressed) bStartRec = true;

		//if (!bStartRec) return true;

		//
		//if (!bGameLoaded)
		//{
		//	FillRectDecal({ 0,0 }, { (float)ScreenWidth(), (float)ScreenHeight() }, C64Color.LightBlue);
		//	// We display the C64 screen and loading screen until the 'game' is loaded
		//	if (bGameLoading) C64LoadingScreen();
		//	C64DisplayScreen();
		//	C64DisplayHeader(fElapsedTime);
		//	
		//	return true;
		//}

		//FillRectDecal({ 0,0 }, { (float)ScreenWidth(), (float)ScreenHeight() }, C64Color.Blue);
		//
		//// Lets get the party going
		//// first up we need a background
		//DrawDecal({ 0, 40 }, decC64Level);
		//
		//if (GetMouse(0).bHeld) DrawDecal(GetMousePos(), decBalloon);

		TestCode(fElapsedTime);


		return true;
	}



};

int main()
{
	Example demo;
	if (demo.Construct(320, 240, 4, 3))
		demo.Start();
	return 0;
}