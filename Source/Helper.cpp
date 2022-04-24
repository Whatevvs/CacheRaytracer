#include "Precomp.h"

/* ---- NDC SCREEN POS ---- */

// -1.0 to 1.0 -> -1.0 to 1.0
ScreenPos_NDC::ScreenPos_NDC(float xin, float yin) : 
	x(xin), 
	y(yin) 
{};

// 1920 x 1080 -> -1.0 to 1.0
ScreenPos_NDC::ScreenPos_NDC(const ScreenPos_Pixel& in) : 
	x(((static_cast<float>(in.x) / static_cast<float>(ScreenWidth)) * 2.0f) - 1.0f),
	y(((static_cast<float>(in.y) / static_cast<float>(ScreenHeight)) * 2.0f) - 1.0f)
{};

// 0.0 to 1.0 -> -1.0 to 1.0
ScreenPos_NDC::ScreenPos_NDC(const ScreenPos_UV& in) : 
	x((in.u * 2.0f) - 1.0f),
	y((in.v * 2.0f) - 1.0f)
{};

/* ---- PIXEL SCREEN POS ---- */

// 1920 x 1080 -> 1920 x 1080
ScreenPos_Pixel::ScreenPos_Pixel(int xin, int yin) : 
	x(xin), 
	y(yin) 
{};

// -1.0 to 1.0 -> 1920 x 1080
ScreenPos_Pixel::ScreenPos_Pixel(const ScreenPos_NDC& in) : 
	x((in.x * static_cast<float>(ScreenWidth)) + (static_cast<float>(ScreenWidth) * 0.5f)),
	y((in.y * static_cast<float>(ScreenHeight)) + (static_cast<float>(ScreenHeight) * 0.5f))
{};

// 0.0 to 1.0 -> 1920 x 1080
ScreenPos_Pixel::ScreenPos_Pixel(const ScreenPos_UV& in) : 
	x(in.u * static_cast<float>(ScreenWidth)),
	y(in.v * static_cast<float>(ScreenHeight))
{};

/* ---- UV SCREEN POS ---- */

// 0.0 to 1.0 -> 0.0 to 1.0
ScreenPos_UV::ScreenPos_UV(float xin, float yin) : 
	u(xin), 
	v(yin) 
{};

// -1.0 to 1.0 -> 0.0 to 1.0
ScreenPos_UV::ScreenPos_UV(const ScreenPos_NDC& in) : 
	u((in.x + 1.0f) * 0.5f),
	v((in.y + 1.0f) * 0.5f)
{};

// 1920 x 1080 -> 0.0 to 1.0
ScreenPos_UV::ScreenPos_UV(const ScreenPos_Pixel& in) : 
	u(in.x / static_cast<float>(ScreenWidth)),
	v(in.y / static_cast<float>(ScreenHeight))
{};