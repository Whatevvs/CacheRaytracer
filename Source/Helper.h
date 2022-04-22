#pragma once

struct ScreenPos_NDC;
struct ScreenPos_Pixel;
struct ScreenPos_UV;

struct ScreenPos_NDC
{
	float x;
	float y;

	// -1.0 to 1.0 -> -1.0 to 1.0
	ScreenPos_NDC(float xin, float yin);

	// 1920 x 1080 -> -1.0 to 1.0
	ScreenPos_NDC(const ScreenPos_Pixel& in);

	// 0.0 to 1.0 -> -1.0 to 1.0
	ScreenPos_NDC(const ScreenPos_UV& in);
};

struct ScreenPos_Pixel
{
	int x;
	int y;

	// 1920 x 1080 -> 1920 x 1080
	ScreenPos_Pixel(int xin, int yin);

	// -1.0 to 1.0 -> 1920 x 1080
	ScreenPos_Pixel(const ScreenPos_NDC& in);

	// 0.0 to 1.0 -> 1920 x 1080
	ScreenPos_Pixel(const ScreenPos_UV& in);
};

struct ScreenPos_UV
{
	float u;
	float v;

	// 0.0 to 1.0 -> 0.0 to 1.0
	ScreenPos_UV(float xin, float yin);

	// -1.0 to 1.0 -> 0.0 to 1.0
	ScreenPos_UV(const ScreenPos_NDC& in);

	// 1920 x 1080 -> 0.0 to 1.0
	ScreenPos_UV(const ScreenPos_Pixel& in);
};