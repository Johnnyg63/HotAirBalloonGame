
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
	std::vector<std::string> vecMessages;
	/* END Vectors*/

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
	
	/* END C64 Colour Code Pixels */

	/* C64 Base Screen text */

	std::string strHeaderText1 = "**** COMMODARE 64 BASIC V2 ****";
	std::string strLineBreak = " ";
	std::string strHeaderText2 = "64K RAM SYSTEM 38911 BASIC BYTES FREE";
	std::string strReady = "READY.";
	std::string strLoad = "LOAD";
	std::string strLoading = "LOADING...";
	std::string strRun = "RUN...";

	/* END C64 Base Screen text */



public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame, draws random coloured pixels
		DisplayC64Screen();
		DisplayC64Header();

		return true;
	}


private:


	void DisplayC64Screen()
	{
		Clear(C64Color.LightBlue);

		FillRect({ 20,20 }, { 280, 160 }, C64Color.Blue);

	}

	void DisplayC64Header()
	{
		DrawStringPropDecal({ 45, 30 }, strHeaderText1, C64Color.LightBlue, {1.0f, 0.8f});
		DrawStringPropDecal({ 30, 40 }, strHeaderText2, C64Color.LightBlue, {1.0f, 0.8f});
		DrawStringPropDecal({ 22, 60 }, strReady, C64Color.LightBlue, { 1.0f, 0.8f });
	}

};

int main()
{
	Example demo;
	if (demo.Construct(320, 200, 4, 4))
		demo.Start();
	return 0;
}