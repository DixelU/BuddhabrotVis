#include "pch.h"
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <filesystem>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <limits>
#include <fstream>
#include <set>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>
#include <deque>
#include <thread>
#include <mutex>
#include <Windows.h>

//#define WIN32_LEAN_AND_MEAN

#include "glut.h"
#include "freeglut.h"
#ifndef __X64
#pragma comment (lib, "freeglut.lib")
#else
#pragma comment (lib, "x64\\freeglut.lib")
#endif

#include "consts.h"
#include "field_vis.h"

#define NULL nullptr

using namespace std;

typedef unsigned char BYTE;
typedef bool BIT;

#define BEG_RANGE 200
FLOAT RANGE = BEG_RANGE, MXPOS = 0.f, MYPOS = 0.f;

const char* WINDOWTITLE = "____\0";
wstring RegPath = L"Software\\SAF_APP_UNNAMED\\";
string FONTNAME = "Arial";
BIT is_fonted = 0;

//#define ROT_ANGLE 0.7
#define TRY_CATCH(code,msg) try{code}catch(...){cout<<msg<<endl;}

float ROT_ANGLE = 0.f, centx = 0., centy = 0.;
#define ROT_RAD ANGTORAD(ROT_ANGLE)
//#define RANGE 200
#define WINDXSIZE 720
#define WINDYSIZE 720

#define ANGTORAD(a) (0.0174532925f*(a))
#define RANDFLOAT(range)  ((0 - range) + ((float)rand()/((float)RAND_MAX/(2*range))))
#define RANDSGN ((rand()&1)?-1:1)
#define SLOWDPROG(a,b,progressrate) ((a + (progressrate - 1)*b)/progressrate)

#define GLCOLOR(uINT) glColor4ub(((uINT & 0xFF000000) >> 24), ((uINT & 0xFF0000) >> 16), ((uINT & 0xFF00) >> 8), (uINT & 0xFF))

float WindX = WINDXSIZE, WindY = WINDYSIZE;

BIT ANIMATION_IS_ACTIVE = 0, FIRSTBOOT = 1, DRAG_OVER = 0,
APRIL_FOOL = 0;
DWORD TimerV = 0;
HWND hWnd;
HDC hDc;
auto HandCursor = ::LoadCursor(NULL, IDC_HAND), AllDirectCursor = ::LoadCursor(NULL, IDC_CROSS);///AAAAAAAAAAA
//const float singlepixwidth = (float)RANGE / WINDXSIZE;

void absoluteToActualCoords(int ix, int iy, float &x, float &y);
float CONSTZERO(float x, float y) { return 0.f; }
int TIMESEED() {
	SYSTEMTIME t;
	GetLocalTime(&t);
	if (t.wMonth == 4 && t.wDay == 1)APRIL_FOOL = 1;
	return t.wMilliseconds + (t.wSecond * 1000) + t.wMinute * 60000;
}

unordered_map<char, string> ASCII;
void InitASCIIMap() {
	ASCII.clear();
	ifstream file("ascii.dotmap", ios::in);
	string T;
	if (true) {
		for (int i = 0; i <= 32; i++)ASCII[i] = " ";
		ASCII['!'] = "85 2";
		ASCII['"'] = "74 96";
		ASCII['#'] = "81 92 64";
		ASCII['$'] = "974631 82";
		ASCII['%'] = "7487 3623 91";
		ASCII['&'] = "37954126";
		ASCII['\'']= "85";
		ASCII['('] = "842";
		ASCII[')'] = "862";
		ASCII['*'] = "67 58 94~";
		ASCII['+'] = "46 82";
		ASCII[','] = "15~";
		ASCII['-'] = "46";
		ASCII['.'] = "2";
		ASCII['/'] = "81";
		ASCII['0'] = "97139";
		ASCII['1'] = "482 13";
		ASCII['2'] = "796413";
		ASCII['3'] = "7965 631";
		ASCII['4'] = "746 93";
		ASCII['5'] = "974631";
		ASCII['6'] = "9741364";
		ASCII['7'] = "7952";
		ASCII['8'] = "17931 46";
		ASCII['9'] = "1369746";
		ASCII[':'] = "8 5~";
		ASCII[';'] = "8 15~";
		ASCII['<'] = "943";
		ASCII['='] = "46 79~";
		ASCII['>'] = "761";
		ASCII['?'] = "795 2";
		ASCII['@'] = "317962486";
		ASCII['A'] = "1793 46";
		ASCII['B'] = "17954 531";
		ASCII['C'] = "9713";
		ASCII['D'] = "178621";
		ASCII['E'] = "9713 54";
		ASCII['F'] = "971 54";
		ASCII['G'] = "971365";
		ASCII['H'] = "9641 74 63";
		ASCII['I'] = "79 82 13";
		ASCII['J'] = "79 821";
		ASCII['K'] = "71 954 53";
		ASCII['L'] = "713";
		ASCII['M'] = "17593";
		ASCII['N'] = "1739";
		ASCII['O'] = "97139";
		ASCII['P'] = "17964";
		ASCII['Q'] = "179621 53";
		ASCII['R'] = "17964 53";
		ASCII['S'] = "974631";
		ASCII['T'] = "79 82";
		ASCII['U'] = "712693";
		ASCII['V'] = "729";
		ASCII['W'] = "71539";
		ASCII['X'] = "73 91";
		ASCII['Y'] = "752 95";
		ASCII['Z'] = "7913 46";
		ASCII['['] = "9823";
		ASCII['\\']= "72";
		ASCII[']'] = "7821";
		ASCII['^'] = "486";
		ASCII['_'] = "13";
		ASCII['`'] = "75";
		ASCII['a'] = "153";
		ASCII['b'] = "71364";
		ASCII['c'] = "6413";
		ASCII['d'] = "93146";
		ASCII['e'] = "31461";
		ASCII['f'] = "289 56";
		ASCII['g'] = "139746#";
		ASCII['h'] = "71 463";
		ASCII['i'] = "52 8";
		ASCII['j'] = "521 8";
		ASCII['k'] = "716 35";
		ASCII['l'] = "82";
		ASCII['m'] = "1452 563";
		ASCII['n'] = "1463";
		ASCII['o'] = "14631";
		ASCII['p'] = "17964#";
		ASCII['q'] = "39746#";
		ASCII['r'] = "146";
		ASCII['s'] = "6431";
		ASCII['t'] = "823 56";
		ASCII['u'] = "4136";
		ASCII['v'] = "426";
		ASCII['w'] = "4125 236";
		ASCII['x'] = "16 34";
		ASCII['y'] = "75 91#";
		ASCII['z'] = "4613";
		ASCII['{'] = "9854523";
		ASCII['|'] = "82";
		ASCII['}'] = "7856521";
		ASCII['~'] = "4859~";
		ASCII[127] = "71937 97 31";
		for (int i = 128; i < 256; i++)ASCII[i] = " ";
	}
	else {
		for (int i = 0; i < 256; i++) {
			getline(file, T);
			ASCII[(char)i] = T;
		}
	}
	file.close();
}

struct Coords {
	float x, y;
	void Set(float newx, float newy) {
		x = newx; y = newy;
	}
};
struct DottedSymbol {
	float Xpos, Ypos;
	BYTE R, G, B, A, LineWidth;
	Coords Points[9];
	string RenderWay;
	vector<char> PointPlacement;
	DottedSymbol(string RenderWay,float Xpos,float Ypos,float XUnitSize,float YUnitSize, BYTE LineWidth = 2,BYTE Red=255,BYTE Green=255,BYTE Blue=255, BYTE Alpha=255) {
		if (!RenderWay.size())RenderWay = " ";
		this->RenderWay = RenderWay;
		this->Xpos = Xpos;
		this->LineWidth = LineWidth;
		this->Ypos = Ypos;
		this->R = Red; this->G = Green; this->B = Blue; this->A = Alpha;
		for (int x = -1; x <= 1; x++) {
			for (int y = -1; y <= 1; y++) {
				Points[x + 1 + 3 * (y + 1)].Set(XUnitSize*x, YUnitSize*y);
			}
		}
		UpdatePointPlacementPositions();
	}
	DottedSymbol(char Symbol, float Xpos, float Ypos, float XUnitSize, float YUnitSize, BYTE LineWidth = 2, BYTE Red = 255, BYTE Green = 255, BYTE Blue = 255, BYTE Alpha = 255) : 
		DottedSymbol(ASCII[Symbol], Xpos, Ypos, XUnitSize, YUnitSize, LineWidth, Red, Green, Blue, Alpha) {}

	DottedSymbol(string RenderWay, float Xpos, float Ypos, float XUnitSize, float YUnitSize, BYTE LineWidth, DWORD *RGBAColor) : 
		DottedSymbol(RenderWay, Xpos, Ypos, XUnitSize, YUnitSize, LineWidth, *RGBAColor >> 24, (*RGBAColor >> 16) & 0xFF, (*RGBAColor >> 8) & 0xFF, (*RGBAColor) & 0xFF) {
		delete RGBAColor;
	}
	DottedSymbol(char Symbol, float Xpos, float Ypos, float XUnitSize, float YUnitSize, BYTE LineWidth, DWORD *RGBAColor) : 
		DottedSymbol(ASCII[Symbol], Xpos, Ypos, XUnitSize, YUnitSize, LineWidth, *RGBAColor >> 24, (*RGBAColor >> 16) & 0xFF, (*RGBAColor >> 8) & 0xFF, (*RGBAColor) & 0xFF) {
		delete RGBAColor;
	}
	inline static BIT IsRenderwaySymb(CHAR C) {
		return (C <= '9' && C >= '0' || C == ' ');
	}
	inline static BIT IsNumber(CHAR C) {
		return (C <= '9' && C >= '0');
	}

	void UpdatePointPlacementPositions() {
		PointPlacement.clear();
		if (RenderWay.size() > 1) {
			if (IsNumber(RenderWay[0]) && !IsNumber(RenderWay[1]))
				PointPlacement.push_back(RenderWay[0]);
			if (IsNumber(RenderWay.back()) && !IsNumber(RenderWay[RenderWay.size() - 2]))PointPlacement.push_back(RenderWay.back());
			for (int i = 1; i < RenderWay.size() - 1; ++i) {
				if (IsNumber(RenderWay[i]) && !IsNumber(RenderWay[i - 1]) && !IsNumber(RenderWay[i + 1]))
					PointPlacement.push_back(RenderWay[i]);
			}
		}
		else if (RenderWay.size() && IsNumber(RenderWay[0])) {
			PointPlacement.push_back(RenderWay[0]);
		}
	}
	void virtual Draw() {
		if (RenderWay == " ")return;
		float VerticalFlag = 0.f;
		CHAR BACK=0;
		if (RenderWay.back() == '#' || RenderWay.back() == '~') {
			BACK = RenderWay.back();
			RenderWay.back() = ' ';
			switch (BACK) {
				case '#':
					VerticalFlag = Points->y - Points[3].y;
				break;
				case '~':
					VerticalFlag = (Points->y - Points[3].y)/2;
				break;
			}
		}
		glColor4ub(R, G, B, A);
		glLineWidth(LineWidth);
		glPointSize(LineWidth);
		glBegin(GL_LINE_STRIP);
		BYTE IO;
		for (int i = 0; i < RenderWay.length(); i++) {
			if (RenderWay[i] == ' ') {
				glEnd();
				glBegin(GL_LINE_STRIP);
				continue;
			}
			IO = RenderWay[i] - '1';
			glVertex2f(Xpos + Points[IO].x, Ypos + Points[IO].y + VerticalFlag);
		}
		glEnd();
		glBegin(GL_POINTS);
		for (int i = 0; i < PointPlacement.size(); ++i) 
			glVertex2f(Xpos + Points[PointPlacement[i] - '1'].x, Ypos + Points[PointPlacement[i] - '1'].y + VerticalFlag);
		glEnd();
		if (BACK)RenderWay.back() = BACK;
	}
	void SafePositionChange(float NewXPos, float NewYPos) {
		SafeCharMove(NewXPos - Xpos, NewYPos - Ypos);
	}
	void SafeCharMove(float dx, float dy) {
		Xpos += dx; Ypos += dy;
	}
	inline float _XUnitSize() const {
		return Points[1].x - Points[0].x;
	}
	inline float _YUnitSize() const {
		return Points[3].y - Points[0].y;
	}
	void virtual RefillGradient(DWORD *RGBAColor, DWORD *gRGBAColor, BYTE BaseColorPoint, BYTE GradColorPoint) {
		return;
	}
	void virtual RefillGradient(BYTE Red = 255, BYTE Green = 255, BYTE Blue = 255, BYTE Alpha = 255,
		BYTE gRed = 255, BYTE gGreen = 255, BYTE gBlue = 255, BYTE gAlpha = 255,
		BYTE BaseColorPoint = 5, BYTE GradColorPoint = 8) {
		return;
	}
};
FLOAT lFONT_HEIGHT_TO_WIDTH = 2.5;
namespace lFontSymbolsInfo {
	bool IsInitialised = false;
	GLuint CurrentFont = 0; 
	HFONT SelectedFont;
	INT32 Size = 16;
	struct lFontSymbInfosListDestructor {
		bool abc;
		~lFontSymbInfosListDestructor() {
			glDeleteLists(CurrentFont, 256);
		}
	};
	lFontSymbInfosListDestructor __wFSILD = { 0 };
	void InitialiseFont(string FontName) {
		if (!IsInitialised) {
			CurrentFont = glGenLists(256);
			IsInitialised = true;
		}
		wglUseFontBitmaps(hDc, 0, 255, CurrentFont);
		SelectedFont = CreateFontA(
			Size*(BEG_RANGE/RANGE), 
			(Size>0)? Size * (BEG_RANGE / RANGE) / lFONT_HEIGHT_TO_WIDTH: 0,
			0, 0,
			FW_NORMAL,
			FALSE,
			FALSE, 
			FALSE, 
			DEFAULT_CHARSET, 
			OUT_TT_PRECIS, 
			CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY, 
			FF_DONTCARE | DEFAULT_PITCH, 
			FontName.c_str()
		);
		if (SelectedFont)
			SelectObject(hDc, SelectedFont);
	}
	inline void CallListOnChar(char C) {
		if (IsInitialised) {
			const char PsChStr[2] = {C,0};
			glPushAttrib(GL_LIST_BIT);
			glListBase(CurrentFont);
			glCallLists(1, GL_UNSIGNED_BYTE, (const char*)(PsChStr));
			glPopAttrib();
		}
	}
	inline void CallListOnString(const string &S) {
		if (IsInitialised) {
			glPushAttrib(GL_LIST_BIT);
			glListBase(CurrentFont);
			glCallLists(1, GL_UNSIGNED_BYTE, S.c_str());
			glPopAttrib();
		}
	}
	const _MAT2 MT = { {0, 1}, {0, 0}, {0, 0}, {0, 1} };;
}
struct lFontSymbol : DottedSymbol {
	char Symb;
	GLYPHMETRICS GM;
	lFontSymbol(char Symb, float CXpos, float CYpos, float XUnitSize, float YUnitSize, DWORD RGBA) :
		DottedSymbol(" ", CXpos, CYpos, XUnitSize, YUnitSize, 1, RGBA >> 24, (RGBA >> 16) & 0xFF, (RGBA >> 8) & 0xFF, RGBA & 0xFF) {
		this->Symb = Symb;
	}
	void Draw() override {
		float PixelSize = (RANGE * 2) / WINDXSIZE;
		float rotX = Xpos, rotY = Ypos;
		//rotate(rotX, rotY);
		if (fabsf(rotX) + 2.5 > PixelSize* WindX / 2 || fabsf(rotY) + 2.5 > PixelSize* WindY / 2)
			return;
		SelectObject(hDc, lFontSymbolsInfo::SelectedFont);
		GetGlyphOutline(hDc, Symb, GGO_METRICS, &GM, 0, NULL, &lFontSymbolsInfo::MT);
		glColor4ub(R, G, B, A);
		glRasterPos2f(Xpos - PixelSize*GM.gmBlackBoxX*0.5, Ypos - _YUnitSize()*0.5);
		lFontSymbolsInfo::CallListOnChar(Symb);
	}
};
struct BiColoredDottedSymbol : DottedSymbol {
	BYTE gR[9],gG[9],gB[9],gA[9];
	BYTE _PointData;
	BiColoredDottedSymbol(string RenderWay, float Xpos, float Ypos, float XUnitSize, float YUnitSize, BYTE LineWidth = 2,
		BYTE Red = 255, BYTE Green = 255, BYTE Blue = 255, BYTE Alpha = 255,
		BYTE gRed = 255, BYTE gGreen = 255, BYTE gBlue = 255, BYTE gAlpha = 255, 
		BYTE BaseColorPoint = 5, BYTE GradColorPoint = 8) : 
		DottedSymbol(RenderWay,Xpos,Ypos,XUnitSize,YUnitSize,LineWidth,new DWORD(0)) {
		this->_PointData = (((BaseColorPoint & 0xF) << 4) | (GradColorPoint & 0xF));
		if (BaseColorPoint == GradColorPoint) {
			for (int i = 0; i < 9; i++) {
				gR[i] = Red;
				gG[i] = Green;
				gB[i] = Blue;
				gA[i] = Alpha;
			}
		}
		else {
			BaseColorPoint--;
			GradColorPoint--;
			RefillGradient(Red, Green, Blue, Alpha, gRed, gGreen, gBlue, gAlpha, BaseColorPoint, GradColorPoint);
		}
	}
	BiColoredDottedSymbol(char Symbol, float Xpos, float Ypos, float XUnitSize, float YUnitSize, BYTE LineWidth = 2,
		BYTE Red = 255, BYTE Green = 255, BYTE Blue = 255, BYTE Alpha = 255,
		BYTE gRed = 255, BYTE gGreen = 255, BYTE gBlue = 255, BYTE gAlpha = 255,
		BYTE BaseColorPoint = 5, BYTE GradColorPoint = 8) : BiColoredDottedSymbol(ASCII[Symbol], Xpos, Ypos, XUnitSize, YUnitSize, LineWidth, Red, Green, Blue, Alpha, gRed, gGreen, gBlue, gAlpha, BaseColorPoint, GradColorPoint) {}

	BiColoredDottedSymbol(char Symbol, float Xpos, float Ypos, float XUnitSize, float YUnitSize, BYTE LineWidth,
		DWORD *RGBAColor, DWORD *gRGBAColor,
		BYTE BaseColorPoint = 5, BYTE GradColorPoint = 8) : BiColoredDottedSymbol(ASCII[Symbol], Xpos, Ypos, XUnitSize, YUnitSize, LineWidth, *RGBAColor >> 24, (*RGBAColor >> 16) & 0xFF, (*RGBAColor >> 8) & 0xFF, (*RGBAColor) & 0xFF, *gRGBAColor >> 24, (*gRGBAColor >> 16) & 0xFF, (*gRGBAColor >> 8) & 0xFF, *gRGBAColor & 0xFF, BaseColorPoint, GradColorPoint) {
		delete RGBAColor;
		delete gRGBAColor;
	}
	BiColoredDottedSymbol(string RenderWay, float Xpos, float Ypos, float XUnitSize, float YUnitSize, BYTE LineWidth,
		DWORD *RGBAColor, DWORD *gRGBAColor,
		BYTE BaseColorPoint = 5, BYTE GradColorPoint = 8) : BiColoredDottedSymbol(RenderWay, Xpos, Ypos, XUnitSize, YUnitSize, LineWidth, *RGBAColor >> 24, (*RGBAColor >> 16) & 0xFF, (*RGBAColor >> 8) & 0xFF, (*RGBAColor) & 0xFF, *gRGBAColor >> 24, (*gRGBAColor >> 16) & 0xFF, (*gRGBAColor >> 8) & 0xFF, *gRGBAColor & 0xFF, BaseColorPoint, GradColorPoint) {
		delete RGBAColor;
		delete gRGBAColor;
	}
	void RefillGradient(BYTE Red = 255, BYTE Green = 255, BYTE Blue = 255, BYTE Alpha = 255,
		BYTE gRed = 255, BYTE gGreen = 255, BYTE gBlue = 255, BYTE gAlpha = 255,
		BYTE BaseColorPoint = 5, BYTE GradColorPoint = 8) override {
		float xbase = (((float)(BaseColorPoint % 3)) - 1.f), ybase = (((float)(BaseColorPoint / 3)) - 1.f),
			xgrad = (((float)(GradColorPoint % 3)) - 1.f), ygrad = (((float)(GradColorPoint / 3)) - 1.f);
		float ax = xgrad - xbase, ay = ygrad - ybase, t;
		float ial = 1.f / (ax*ax + ay * ay);
		///R
		for (int x = -1; x <= 1; x++) {
			for (int y = -1; y <= 1; y++) {
				t = (ax * (x - xbase) + ay * (y - ybase)) * ial;
				t = (Red * t + (1.f - t)*gRed);
				if (t < 0)t = 0;
				if (t > 255)t = 255;
				gR[(x + 1) + (3 * (y + 1))] = round(t);
			}
		}
		///G
		for (int x = -1; x <= 1; x++) {
			for (int y = -1; y <= 1; y++) {
				t = (ax * (x - xbase) + ay * (y - ybase)) * ial;
				t = (Green * t + (1.f - t)*gGreen);
				if (t < 0)t = 0;
				if (t > 255)t = 255;
				gG[(x + 1) + (3 * (y + 1))] = round(t);
			}
		}
		///B
		for (int x = -1; x <= 1; x++) {
			for (int y = -1; y <= 1; y++) {
				t = (ax * (x - xbase) + ay * (y - ybase)) * ial;
				t = (Blue * t + (1.f - t)*gBlue);
				if (t < 0)t = 0;
				if (t > 255)t = 255;
				gB[(x + 1) + (3 * (y + 1))] = round(t);
			}
		}
		///A
		for (int x = -1; x <= 1; x++) {
			for (int y = -1; y <= 1; y++) {
				t = (ax * (x - xbase) + ay * (y - ybase)) * ial;
				t = (Alpha * t + (1.f - t)*gAlpha);
				if (t < 0)t = 0;
				if (t > 255)t = 255;
				gA[(x + 1) + (3 * (y + 1))] = round(t);
			}
		}
	}
	void RefillGradient(DWORD *RGBAColor,DWORD *gRGBAColor,BYTE BaseColorPoint, BYTE GradColorPoint) override {
		RefillGradient(*RGBAColor >> 24, (*RGBAColor >> 16) & 0xFF, (*RGBAColor >> 8) & 0xFF, (*RGBAColor) & 0xFF, *gRGBAColor >> 24, (*gRGBAColor >> 16) & 0xFF, (*gRGBAColor >> 8) & 0xFF, *gRGBAColor & 0xFF, BaseColorPoint, GradColorPoint);
		delete RGBAColor;
		delete gRGBAColor;
	}
	void Draw() override {
		if (RenderWay == " ")return;
		float VerticalFlag = 0.; 
		CHAR BACK = 0;
		if (RenderWay.back() == '#' || RenderWay.back() == '~') {
			BACK = RenderWay.back();
			RenderWay.back() = ' ';
			switch (BACK) {
			case '#':
				VerticalFlag = Points->y - Points[3].y;
				break;
			case '~':
				VerticalFlag = (Points->y - Points[3].y) / 2;
				break;
			}
		}
		if (RenderWay.back() == '#') {
			RenderWay.back() = ' ';
			VerticalFlag = Points->y - Points[4].y;
		}
		BYTE IO;
		glLineWidth(LineWidth);
		glPointSize(LineWidth);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < RenderWay.length(); i++) {
			if (RenderWay[i] == ' ') {
				glEnd();
				glBegin(GL_LINE_STRIP);
				continue;
			}
			IO = RenderWay[i] - '1';
			//printf("%x %x %x %x\n", gR[IO], gG[IO], gB[IO], gA[IO]);
			glColor4ub(gR[IO], gG[IO], gB[IO], gA[IO]);
			glVertex2f(Xpos + Points[IO].x, Ypos + Points[IO].y + VerticalFlag);
		}
		glEnd();
		glBegin(GL_POINTS);
		for (int i = 0; i < PointPlacement.size(); ++i){
			IO = PointPlacement[i] - '1';
			glColor4ub(gR[IO], gG[IO], gB[IO], gA[IO]);
			glVertex2f(Xpos + Points[IO].x, Ypos + Points[IO].y + VerticalFlag);
		}
		glEnd();
		if (BACK)RenderWay.back() = BACK;
	}
};
struct SingleTextLine {
	string _CurrentText;
	float CXpos, CYpos;
	float SpaceWidth;
	DWORD RGBAColor, gRGBAColor;
	float CalculatedWidth, CalculatedHeight;
	BIT isBicolored, isListedFont;
	float _XUnitSize, _YUnitSize;
	vector<DottedSymbol*> Chars;
	~SingleTextLine() {
		for (auto i = Chars.begin(); i != Chars.end(); i++)
			if (*i)delete* i;
		Chars.clear();
	}
	SingleTextLine(string Text, float CXpos, float CYpos, float XUnitSize, float YUnitSize, float SpaceWidth, BYTE LineWidth = 2, DWORD RGBAColor = 0xFFFFFFFF, DWORD* RGBAGradColor = NULL, BYTE OrigNGradPoints = ((5 << 4) | 5), bool isListedFont = false) {
		if (!Text.size())Text = " ";
		this->_CurrentText = Text;
		CalculatedHeight = 2 * YUnitSize;
		CalculatedWidth = Text.size() * 2.f * XUnitSize + (Text.size() - 1) * SpaceWidth;
		this->CXpos = CXpos;
		this->CYpos = CYpos;
		this->RGBAColor = RGBAColor;
		this->SpaceWidth = SpaceWidth;
		this->_XUnitSize = XUnitSize;
		this->_YUnitSize = YUnitSize;
		this->isListedFont = isListedFont;
		float CharXPosition = CXpos - (CalculatedWidth * 0.5) + XUnitSize, CharXPosIncrement = 2.f * XUnitSize + SpaceWidth;
		for (int i = 0; i < Text.size(); i++) {
			if (!RGBAGradColor && !isListedFont)Chars.push_back(
				new DottedSymbol(Text[i], CharXPosition, CYpos, XUnitSize, YUnitSize, LineWidth, new DWORD(RGBAColor))
			);
			else if (!isListedFont) Chars.push_back(
				new BiColoredDottedSymbol(Text[i], CharXPosition, CYpos, XUnitSize, YUnitSize, LineWidth, new DWORD(RGBAColor), new DWORD(*RGBAGradColor), (BYTE)(OrigNGradPoints >> 4), (BYTE)(OrigNGradPoints & 0xF))
			);
			else Chars.push_back(
				new lFontSymbol(Text[i], CharXPosition, CYpos, XUnitSize, YUnitSize, RGBAColor)
			);
			CharXPosition += CharXPosIncrement;
		}
		if (RGBAGradColor) {
			this->isBicolored = true;
			this->gRGBAColor = *RGBAGradColor;
			delete RGBAGradColor;
		}
		else
			this->isBicolored = false;
	}
	void SafeColorChange(DWORD NewRGBAColor) {
		if (isBicolored) {
			SafeColorChange(NewRGBAColor, gRGBAColor,
				((BiColoredDottedSymbol*)(this->Chars.front()))->_PointData >> 4,
				((BiColoredDottedSymbol*)(this->Chars.front()))->_PointData & 0xF
			);
			return;
		}
		BYTE R = (NewRGBAColor >> 24), G = (NewRGBAColor >> 16) & 0xFF, B = (NewRGBAColor >> 8) & 0xFF, A = (NewRGBAColor) & 0xFF;
		RGBAColor = NewRGBAColor;
		for (int i = 0; i < Chars.size(); i++) {
			Chars[i]->R = R;
			Chars[i]->G = G;
			Chars[i]->B = B;
			Chars[i]->A = A;
		}
	}
	void SafeColorChange(DWORD NewBaseRGBAColor, DWORD NewGRGBAColor, BYTE BasePoint, BYTE gPoint) {
		if (!isBicolored) {
			SafeColorChange(NewBaseRGBAColor);
			return;
		}
		for (int i = 0; i < Chars.size(); i++) {
			Chars[i]->RefillGradient(new DWORD(NewBaseRGBAColor), new DWORD(NewGRGBAColor), BasePoint, gPoint);
		}
	}
	void SafeChangePosition(float NewCXPos, float NewCYPos) {
		NewCXPos = NewCXPos - CXpos;
		NewCYPos = NewCYPos - CYpos;
		SafeMove(NewCXPos, NewCYPos);
	}
	void SafeMove(float dx, float dy) {
		CXpos += dx;
		CYpos += dy;
		for (int i = 0; i < Chars.size(); i++)
			Chars[i]->SafeCharMove(dx, dy);
	}
	BIT SafeReplaceChar(int i, char CH) {
		if (i >= Chars.size())return 0;
		if (isListedFont) {
			((lFontSymbol*)Chars[i])->Symb = CH;
		}
		else {
			Chars[i]->RenderWay = ASCII[CH];
			Chars[i]->UpdatePointPlacementPositions();
		}
		return 1;
	}
	BIT SafeReplaceChar(int i, string CHrenderway) {
		if (i >= Chars.size())return 0;
		if (isListedFont) return 0;
		Chars[i]->RenderWay = CHrenderway;
		Chars[i]->UpdatePointPlacementPositions();
		return 1;
	}
	void RecalculateWidth() {
		CalculatedWidth = Chars.size() * (2.f * _XUnitSize) + (Chars.size() - 1) * SpaceWidth;
		float CharXPosition = CXpos - (CalculatedWidth * 0.5f) + _XUnitSize, CharXPosIncrement = 2.f * _XUnitSize + SpaceWidth;
		for (int i = 0; i < Chars.size(); i++) {
			Chars[i]->Xpos = CharXPosition;
			CharXPosition += CharXPosIncrement;
		}
	}
	void SafeChangePosition_Argumented(BYTE Arg, float newX, float newY) {
		///STL_CHANGE_POSITION_ARGUMENT_LEFT
		float CW = 0.5f * (
			(INT32)((BIT)(GLOBAL_LEFT & Arg))
			- (INT32)((BIT)(GLOBAL_RIGHT & Arg))
			) * CalculatedWidth,
			CH = 0.5f * (
			(INT32)((BIT)(GLOBAL_BOTTOM & Arg))
				- (INT32)((BIT)(GLOBAL_TOP & Arg))
				) * CalculatedHeight;
		SafeChangePosition(newX + CW, newY + CH);
	}
	void SafeStringReplace(string NewString) {
		if (!NewString.size()) NewString = " ";
		_CurrentText = NewString;
		while (NewString.size() > Chars.size()) {
			if (isBicolored)
				Chars.push_back(new BiColoredDottedSymbol((*((BiColoredDottedSymbol*)(Chars.front())))));
			else if (isListedFont)
				Chars.push_back(new lFontSymbol(*((lFontSymbol*)(Chars.front()))));
			else
				Chars.push_back(new DottedSymbol(*(Chars.front())));
		}
		while (NewString.size() < Chars.size()) Chars.pop_back();
		for (int i = 0; i < Chars.size(); i++)
			SafeReplaceChar(i, NewString[i]);
		RecalculateWidth();
	}
	void Draw() {
		for (int i = 0; i < Chars.size(); i++) {
			Chars[i]->Draw();
		}
	}
};

#define CharWidthPerHeight_Fonted 0.666f
#define CharWidthPerHeight 0.5f
#define CharSpaceBetween(CharHeight) CharHeight/2.f
#define CharLineWidth(CharHeight) ceil(CharHeight/7.5f)
struct SingleTextLineSettings {
	string STLstring;
	float CXpos, CYpos, XUnitSize, YUnitSize;
	BYTE BasePoint, GradPoint, LineWidth, SpaceWidth;
	BIT isFonted;
	DWORD RGBAColor, gRGBAColor;
	SingleTextLineSettings(string Text, float CXpos, float CYpos, float XUnitSize, float YUnitSize, BYTE LineWidth, BYTE SpaceWidth, DWORD RGBAColor, DWORD gRGBAColor, BYTE BasePoint, BYTE GradPoint) {
		this->STLstring = Text;
		this->CXpos = CXpos;
		this->CYpos = CYpos;
		this->XUnitSize = XUnitSize;
		this->YUnitSize = YUnitSize;
		this->RGBAColor = RGBAColor;
		this->gRGBAColor = gRGBAColor;
		this->LineWidth = LineWidth;
		this->SpaceWidth = SpaceWidth;
		this->BasePoint = BasePoint;
		this->GradPoint = GradPoint;
		this->isFonted = 0;
	}
	SingleTextLineSettings(string Text, float CXpos, float CYpos, float XUnitSize, float YUnitSize, BYTE LineWidth, BYTE SpaceWidth, DWORD RGBAColor) :
		SingleTextLineSettings(Text, CXpos, CYpos, XUnitSize, YUnitSize, LineWidth, SpaceWidth, RGBAColor, 0, 255, 255) {}
	SingleTextLineSettings(string Text, float CXpos, float CYpos, float CharHeight, DWORD RGBAColor, DWORD gRGBAColor, BYTE BasePoint, BYTE GradPoint) :
		SingleTextLineSettings(Text, CXpos, CYpos, CharHeight* CharWidthPerHeight / 2, CharHeight / 2, CharLineWidth(CharHeight), CharSpaceBetween(CharHeight), RGBAColor, gRGBAColor, BasePoint, GradPoint) {}
	SingleTextLineSettings(string Text, float CXpos, float CYpos, float CharHeight, DWORD RGBAColor) :
		SingleTextLineSettings(Text, CXpos, CYpos, CharHeight, RGBAColor, 0, 255, 255) {}
	SingleTextLineSettings(float XUnitSize, float YUnitSize, DWORD RGBAColor) :
		SingleTextLineSettings("_", 0, 0, YUnitSize, RGBAColor) {
		this->isFonted = 1;
		this->XUnitSize = XUnitSize;
		this->YUnitSize = YUnitSize;
		this->RGBAColor = RGBAColor;
	}
	SingleTextLineSettings(float CharHeight, DWORD RGBAColor) :
		SingleTextLineSettings(CharHeight* CharWidthPerHeight / 4, CharHeight / 2, RGBAColor) {}
	SingleTextLineSettings(SingleTextLine* Example, BIT KeepText = false) :
		SingleTextLineSettings(
		((KeepText) ? Example->_CurrentText : " "), Example->CXpos, Example->CYpos, Example->_XUnitSize, Example->_YUnitSize, Example->Chars.front()->LineWidth, Example->SpaceWidth, Example->RGBAColor, Example->gRGBAColor,
			((Example->isBicolored) ? (((BiColoredDottedSymbol*)(Example->Chars.front()))->_PointData & 0xF0) >> 4 : 0xF), ((Example->isBicolored) ? (((BiColoredDottedSymbol*)(Example->Chars.front()))->_PointData) & 0xF : 0xF)
		) {
		this->isFonted = Example->isListedFont;
	}
	SingleTextLine* CreateOne() {
		if (GradPoint & 0xF0 && !isFonted)
			return new SingleTextLine(STLstring, CXpos, CYpos, XUnitSize, YUnitSize, SpaceWidth, LineWidth, RGBAColor);
		if (!isFonted) return new SingleTextLine(STLstring, CXpos, CYpos, XUnitSize, YUnitSize, SpaceWidth, LineWidth, RGBAColor, new DWORD(gRGBAColor), ((BasePoint & 0xF) << 4) | (GradPoint & 0xF));
		return new SingleTextLine(STLstring, CXpos, CYpos, XUnitSize, YUnitSize, SpaceWidth, LineWidth, RGBAColor, nullptr, 0xF, true);
	}
	SingleTextLine* CreateOne(string TextOverride) {
		if (GradPoint & 0xF0 && !isFonted)
			return new SingleTextLine(TextOverride, CXpos, CYpos, XUnitSize, YUnitSize, SpaceWidth, LineWidth, RGBAColor);
		if (!isFonted) return new SingleTextLine(TextOverride, CXpos, CYpos, XUnitSize, YUnitSize, SpaceWidth, LineWidth, RGBAColor, new DWORD(gRGBAColor), ((BasePoint & 0xF) << 4) | (GradPoint & 0xF));
		return new SingleTextLine(TextOverride, CXpos, CYpos, XUnitSize, YUnitSize, SpaceWidth, LineWidth, RGBAColor, nullptr, 0xF, true);
	}
	void SetNewPos(float NewXPos, float NewYPos) {
		this->CXpos = NewXPos;
		this->CYpos = NewYPos;
	}
	void Move(float dx, float dy) {
		this->CXpos += dx;
		this->CYpos += dy;
	}
};

struct HandleableUIPart {
	recursive_mutex Lock;
	~HandleableUIPart() {}
	HandleableUIPart() {}
	BIT virtual MouseHandler(float mx, float my, CHAR Button/*-1 left, 1 right*/, CHAR State /*-1 down, 1 up*/) = 0;
	void virtual Draw() = 0;
	void virtual SafeMove(float, float) = 0;
	void virtual SafeChangePosition(float, float) = 0;
	void virtual SafeChangePosition_Argumented(BYTE, float, float) = 0;
	void virtual SafeStringReplace(string) = 0;
	void virtual KeyboardHandler(char CH) = 0;
	inline DWORD virtual TellType() {
		return TT_UNSPECIFIED;
	}
};

struct CheckBox : HandleableUIPart {///NeedsTest
	float Xpos, Ypos, SideSize;
	DWORD BorderRGBAColor, UncheckedRGBABackground, CheckedRGBABackground;
	SingleTextLine* Tip;
	BIT State, Focused;
	BYTE BorderWidth;
	~CheckBox() {
		Lock.lock();
		if (Tip)delete Tip;
		Lock.unlock();
	}
	CheckBox(float Xpos, float Ypos, float SideSize, DWORD BorderRGBAColor, DWORD UncheckedRGBABackground, DWORD CheckedRGBABackground, BYTE BorderWidth, BIT StartState = false, SingleTextLineSettings* TipSettings = NULL, _Align TipAlign = _Align::left, string TipText = " ") {
		this->Xpos = Xpos;
		this->Ypos = Ypos;
		this->SideSize = SideSize;
		this->BorderRGBAColor = BorderRGBAColor;
		this->UncheckedRGBABackground = UncheckedRGBABackground;
		this->CheckedRGBABackground = CheckedRGBABackground;
		this->State = StartState;
		this->Focused = 0;
		this->BorderWidth = BorderWidth;
		if (TipSettings) {
			this->Tip = TipSettings->CreateOne(TipText);
			this->Tip->SafeChangePosition_Argumented(TipAlign, Xpos - ((TipAlign == _Align::left) ? 0.5f : ((TipAlign == _Align::right) ? -0.5f : 0)) * SideSize, Ypos - SideSize);
		}
	}
	void Draw() override {
		Lock.lock();
		float hSideSize = 0.5f * SideSize;
		if (State)
			GLCOLOR(CheckedRGBABackground);
		else
			GLCOLOR(UncheckedRGBABackground);
		glBegin(GL_QUADS);
		glVertex2f(Xpos + hSideSize, Ypos + hSideSize);
		glVertex2f(Xpos - hSideSize, Ypos + hSideSize);
		glVertex2f(Xpos - hSideSize, Ypos - hSideSize);
		glVertex2f(Xpos + hSideSize, Ypos - hSideSize);
		glEnd();
		if ((BYTE)BorderRGBAColor && BorderWidth) {
			GLCOLOR(BorderRGBAColor);
			glLineWidth(BorderWidth);
			glBegin(GL_LINE_LOOP);
			glVertex2f(Xpos + hSideSize, Ypos + hSideSize);
			glVertex2f(Xpos - hSideSize, Ypos + hSideSize);
			glVertex2f(Xpos - hSideSize, Ypos - hSideSize);
			glVertex2f(Xpos + hSideSize, Ypos - hSideSize);
			glEnd();
			glPointSize(BorderWidth);
			glBegin(GL_POINTS);
			glVertex2f(Xpos + hSideSize, Ypos + hSideSize);
			glVertex2f(Xpos - hSideSize, Ypos + hSideSize);
			glVertex2f(Xpos - hSideSize, Ypos - hSideSize);
			glVertex2f(Xpos + hSideSize, Ypos - hSideSize);
			glEnd();
		}
		if (Focused && Tip)Tip->Draw();
		Lock.unlock();
	}
	void SafeMove(float dx, float dy) override {
		Lock.lock();
		Xpos += dx;
		Ypos += dy;
		if (Tip)Tip->SafeMove(dx, dy);
		Lock.unlock();
	}
	void SafeChangePosition(float NewX, float NewY) override {
		Lock.lock();
		NewX -= Xpos;
		NewY -= Ypos;
		SafeMove(NewX, NewY);
		Lock.unlock();
	}
	void SafeChangePosition_Argumented(BYTE Arg, float NewX, float NewY) override {
		Lock.lock();
		float CW = 0.5f * (
			(INT32)((BIT)(GLOBAL_LEFT & Arg))
			- (INT32)((BIT)(GLOBAL_RIGHT & Arg))
			) * SideSize,
			CH = 0.5f * (
			(INT32)((BIT)(GLOBAL_BOTTOM & Arg))
				- (INT32)((BIT)(GLOBAL_TOP & Arg))
				) * SideSize;
		SafeChangePosition(NewX + CW, NewY + CH);
		Lock.unlock();
	}
	void KeyboardHandler(CHAR CH) override {
		return;
	}
	void SafeStringReplace(string TipString) override {
		Lock.lock();
		if (Tip)Tip->SafeStringReplace(TipString);
		Lock.unlock();
	}
	void FocusChange() {
		Lock.lock();
		this->Focused = !this->Focused;
		BorderRGBAColor = (((~(BorderRGBAColor >> 8)) << 8) | (BorderRGBAColor & 0xFF));
		Lock.unlock();
	}
	BIT MouseHandler(float mx, float my, CHAR Button, CHAR State) override {
		Lock.lock();
		if (fabsf(mx - Xpos) < 0.5 * SideSize && fabsf(my - Ypos) < 0.5 * SideSize) {
			if (!Focused)
				FocusChange();
			if (Button) {
				//cout << "State switch from " << State << endl;
				if (State == 1)
					this->State = !this->State;
				Lock.unlock();
				return 1;
			}
			else {
				Lock.unlock();
				return 0;
			}
		}
		else {
			if (Focused)
				FocusChange();
			Lock.unlock();
			return 0;
		}
	}
	inline DWORD TellType() override {
		return _TellType::checkbox;
	}
};

struct InputField : HandleableUIPart {
	enum PassCharsType {
		PassNumbers = 0b1,
		PassFirstPoint = 0b10,
		PassFrontMinusSign = 0b100,
		PassAll = 0xFF
	};
	enum Type {
		NaturalNumbers = PassCharsType::PassNumbers,
		WholeNumbers = PassCharsType::PassNumbers | PassCharsType::PassFrontMinusSign,
		FP_PositiveNumbers = PassCharsType::PassNumbers | PassCharsType::PassFirstPoint,
		FP_Any = PassCharsType::PassNumbers | PassCharsType::PassFirstPoint | PassCharsType::PassFrontMinusSign,
		Text = PassCharsType::PassAll,
	};
	_Align InputAlign, TipAlign;
	Type InputType;
	string CurrentString, DefaultString;
	string* OutputSource;
	DWORD MaxChars, BorderRGBAColor;
	float Xpos, Ypos, Height, Width;
	BIT Focused, FirstInput;
	SingleTextLine* STL;
	SingleTextLine* Tip;
	InputField(string DefaultString, float Xpos, float Ypos, float Height, float Width, SingleTextLineSettings* DefaultStringSettings, string* OutputSource, DWORD BorderRGBAColor, SingleTextLineSettings* TipLineSettings = NULL, string TipLineText = " ", DWORD MaxChars = 0, _Align InputAlign = _Align::left, _Align TipAlign = _Align::center, Type InputType = Type::Text) {
		this->DefaultString = DefaultString;
		DefaultStringSettings->SetNewPos(Xpos, Ypos);
		this->STL = DefaultStringSettings->CreateOne(DefaultString);
		if (TipLineSettings) {
			this->Tip = TipLineSettings->CreateOne(TipLineText);
			this->Tip->SafeChangePosition_Argumented(TipAlign, Xpos - ((TipAlign == _Align::left) ? 0.5f : ((TipAlign == _Align::right) ? -0.5f : 0)) * Width, Ypos - Height);
		}
		else this->Tip = NULL;
		this->InputAlign = InputAlign;
		this->InputType = InputType;
		this->TipAlign = TipAlign;

		this->MaxChars = MaxChars;
		this->BorderRGBAColor = BorderRGBAColor;
		this->Xpos = Xpos;
		this->Ypos = Ypos;
		this->Height = (DefaultStringSettings->YUnitSize * 2 > Height) ? DefaultStringSettings->YUnitSize * 2 : Height;
		this->Width = Width;
		this->CurrentString = "";//DefaultString;
		this->FirstInput = this->Focused = false;
		this->OutputSource = OutputSource;
	}
	BIT MouseHandler(float mx, float my, CHAR Button/*-1 left, 1 right, 0 move*/, CHAR State /*-1 down, 1 up*/) override {
		if (abs(mx - Xpos) < 0.5 * Width && abs(my - Ypos) < 0.5 * Height) {
			if (!Focused)
				FocusChange();
			if (Button)return 1;
			else return 0;
		}
		else {
			if (Focused)
				FocusChange();
			return 0;
		}
	}
	void SafeMove(float dx, float dy) {
		Lock.lock();
		STL->SafeMove(dx, dy);
		if (Tip)Tip->SafeMove(dx, dy);
		Xpos += dx;
		Ypos += dy;
		Lock.unlock();
	}
	void SafeChangePosition(float NewX, float NewY) {
		Lock.lock();
		NewX = Xpos - NewX;
		NewY = Ypos - NewY;
		SafeMove(NewX, NewY);
		Lock.unlock();
	}
	void FocusChange() {
		Lock.lock();
		this->Focused = !this->Focused;
		BorderRGBAColor = (((~(BorderRGBAColor >> 8)) << 8) | (BorderRGBAColor & 0xFF));
		Lock.unlock();
	}
	void UpdateInputString(string NewString = "") {
		Lock.lock();
		if (NewString.size())CurrentString = "";
		float x = Xpos - ((InputAlign == _Align::left) ? 1 : ((InputAlign == _Align::right) ? -1 : 0)) * (0.5f * Width - STL->_XUnitSize);
		this->STL->SafeStringReplace((NewString.size()) ? NewString.substr(0, this->MaxChars) : CurrentString);
		this->STL->SafeChangePosition_Argumented(InputAlign, x, Ypos);
		Lock.unlock();
	}
	void BackSpace() {
		Lock.lock();
		ProcessFirstInput();
		if (CurrentString.size()) {
			CurrentString.pop_back();
			UpdateInputString();
		}
		else {
			this->STL->SafeStringReplace(" ");
		}
		Lock.unlock();
	}
	void FlushCurrentStringWithoutGUIUpdate(BIT SetDefault = false) {
		Lock.lock();
		this->CurrentString = (SetDefault) ? this->DefaultString : "";
		Lock.unlock();
	}
	void PutIntoSource(string* AnotherSource = NULL) {
		Lock.lock();
		if (OutputSource) {
			if (CurrentString.size())
				*OutputSource = CurrentString;
		}
		else if (AnotherSource)
			if (CurrentString.size())
				*AnotherSource = CurrentString;
		Lock.unlock();
	}
	void ProcessFirstInput() {
		Lock.lock();
		if (FirstInput) {
			FirstInput = 0;
			CurrentString = "";
		}
		Lock.unlock();
	}
	void KeyboardHandler(char CH) {
		Lock.lock();
		if (Focused) {
			if (CH >= 32) {
				if (InputType & PassCharsType::PassNumbers) {
					if (CH >= '0' && CH <= '9') {
						Input(CH);
						Lock.unlock();
						return;
					}
				}
				if (InputType & PassCharsType::PassFrontMinusSign) {
					if (CH == '-' && CurrentString.empty()) {
						Input(CH);
						Lock.unlock();
						return;
					}
				}
				if (InputType & PassCharsType::PassFirstPoint) {
					if (CH == '.' && CurrentString.find('.') >= CurrentString.size()) {
						Input(CH);
						Lock.unlock();
						return;
					}
				}

				if (InputType == PassCharsType::PassAll)Input(CH);
			}
			else if (CH == 13)PutIntoSource();
			else if (CH == 8)BackSpace();
		}
		Lock.unlock();
	}
	void Input(char CH) {
		Lock.lock();
		ProcessFirstInput();
		if (!MaxChars || CurrentString.size() < MaxChars) {
			CurrentString.push_back(CH);
			UpdateInputString();
		}
		Lock.unlock();
	}
	void SafeChangePosition_Argumented(BYTE Arg, float NewX, float NewY) {
		Lock.lock();
		float CW = 0.5f * (
			(INT32)((BIT)(GLOBAL_LEFT & Arg))
			- (INT32)((BIT)(GLOBAL_RIGHT & Arg))
			) * Width,
			CH = 0.5f * (
			(INT32)((BIT)(GLOBAL_BOTTOM & Arg))
				- (INT32)((BIT)(GLOBAL_TOP & Arg))
				) * Height;
		SafeChangePosition(NewX + CW, NewY + CH);
		Lock.unlock();
	}
	void SafeStringReplace(string NewString) override {
		Lock.lock();
		CurrentString = NewString.substr(0, this->MaxChars);
		UpdateInputString(NewString);
		FirstInput = 1;
		Lock.unlock();
	}
	void Draw() override {
		Lock.lock();
		GLCOLOR(BorderRGBAColor);
		glLineWidth(1);
		glBegin(GL_LINE_LOOP);
		glVertex2f(Xpos + 0.5f * Width, Ypos + 0.5f * Height);
		glVertex2f(Xpos - 0.5f * Width, Ypos + 0.5f * Height);
		glVertex2f(Xpos - 0.5f * Width, Ypos - 0.5f * Height);
		glVertex2f(Xpos + 0.5f * Width, Ypos - 0.5f * Height);
		glEnd();
		this->STL->Draw();
		if (Focused && Tip)Tip->Draw();
		Lock.unlock();
	}
	inline DWORD TellType() override {
		return TT_INPUT_FIELD;
	}
};

struct Button : HandleableUIPart {
	SingleTextLine* STL, * Tip;
	float Xpos, Ypos;
	float Width, Height;
	DWORD RGBAColor, RGBABackground, RGBABorder;
	DWORD HoveredRGBAColor, HoveredRGBABackground, HoveredRGBABorder;
	BYTE BorderWidth;
	BIT Hovered;
	void(*OnClick)();
	~Button() {
		delete STL;
		if (Tip)delete Tip;
	}
	Button(string ButtonText, void(*OnClick)(), float Xpos, float Ypos, float Width, float Height, float CharHeight, DWORD RGBAColor, DWORD gRGBAColor, BYTE BasePoint/*15 if gradient is disabled*/, BYTE GradPoint, BYTE BorderWidth, DWORD RGBABackground, DWORD RGBABorder, DWORD HoveredRGBAColor, DWORD HoveredRGBABackground, DWORD HoveredRGBABorder, SingleTextLineSettings* Tip, string TipText = " ") {
		SingleTextLineSettings STLS(ButtonText, Xpos, Ypos, CharHeight, RGBAColor, gRGBAColor, BasePoint, GradPoint);
		this->STL = STLS.CreateOne();
		if (Tip) {
			Tip->SetNewPos(Xpos, Ypos - Height);
			this->Tip = Tip->CreateOne(TipText);
		}
		else this->Tip = NULL;
		this->BorderWidth = BorderWidth;
		this->Xpos = Xpos;
		this->Ypos = Ypos;
		this->Width = Width;
		this->Height = Height;
		this->RGBAColor = RGBAColor;
		this->RGBABorder = RGBABorder;
		this->RGBABackground = RGBABackground;
		this->HoveredRGBAColor = HoveredRGBAColor;
		this->HoveredRGBABorder = HoveredRGBABorder;
		this->HoveredRGBABackground = HoveredRGBABackground;
		this->Hovered = 0;
		this->OnClick = OnClick;
	}
	Button(string ButtonText, SingleTextLineSettings* ButtonTextSTLS, void(*OnClick)(), float Xpos, float Ypos, float Width, float Height, BYTE BorderWidth, DWORD RGBABackground, DWORD RGBABorder, DWORD HoveredRGBAColor, DWORD HoveredRGBABackground, DWORD HoveredRGBABorder, SingleTextLineSettings* Tip, string TipText = " ") {
		ButtonTextSTLS->SetNewPos(Xpos, Ypos);
		this->STL = ButtonTextSTLS->CreateOne(ButtonText);
		if (Tip) {
			Tip->SetNewPos(Xpos, Ypos - Height);
			this->Tip = Tip->CreateOne(TipText);
		}
		else this->Tip = NULL;
		this->BorderWidth = BorderWidth;
		this->Xpos = Xpos;
		this->Ypos = Ypos;
		this->Width = Width;
		this->Height = Height;
		this->RGBAColor = ButtonTextSTLS->RGBAColor;
		this->RGBABorder = RGBABorder;
		this->RGBABackground = RGBABackground;
		this->HoveredRGBAColor = HoveredRGBAColor;
		this->HoveredRGBABorder = HoveredRGBABorder;
		this->HoveredRGBABackground = HoveredRGBABackground;
		this->Hovered = 0;
		this->OnClick = OnClick;
	}
	BIT MouseHandler(float mx, float my, CHAR Button/*-1 left, 1 right, 0 move*/, CHAR State /*-1 down, 1 up*/)  override {
		Lock.lock();
		mx = Xpos - mx;
		my = Ypos - my;
		if (Hovered) {
			if (fabsf(mx) > Width * 0.5 || fabsf(my) > Height * 0.5) {
				//cout << "UNHOVERED\n";
				Hovered = 0;
				STL->SafeColorChange(RGBAColor);
			}
			else {
				SetCursor(HandCursor);
				if (Button && State == 1) {

					if (Button == -1 && OnClick)OnClick();
					Lock.unlock();
					return 1;
				}

			}
		}
		else {
			if (fabsf(mx) <= Width * 0.5 && fabsf(my) <= Height * 0.5) {
				Hovered = 1;
				STL->SafeColorChange(HoveredRGBAColor);
			}
		}
		Lock.unlock();
		return 0;
	}
	void SafeMove(float dx, float dy) {
		Lock.lock();
		if (Tip)Tip->SafeMove(dx, dy);
		STL->SafeMove(dx, dy);
		Xpos += dx;
		Ypos += dy;
		Lock.unlock();
	}
	void KeyboardHandler(char CH) override {
		return;
	}
	void SafeStringReplace(string NewString) override {
		Lock.lock();
		this->STL->SafeStringReplace(NewString);
		Lock.unlock();
	}
	void SafeChangePosition(float NewX, float NewY) {
		Lock.lock();
		NewX -= Xpos;
		NewY -= Ypos;
		SafeMove(NewX, NewY);
		Lock.unlock();
	}
	void SafeChangePosition_Argumented(BYTE Arg, float NewX, float NewY) {
		Lock.lock();
		float CW = 0.5f * (
			(INT32)((BIT)(GLOBAL_LEFT & Arg))
			- (INT32)((BIT)(GLOBAL_RIGHT & Arg))
			) * Width,
			CH = 0.5f * (
			(INT32)((BIT)(GLOBAL_BOTTOM & Arg))
				- (INT32)((BIT)(GLOBAL_TOP & Arg))
				) * Height;
		SafeChangePosition(NewX + CW, NewY + CH);
		Lock.unlock();
	}
	void Draw() {
		Lock.lock();
		if (Hovered) {
			if ((BYTE)HoveredRGBABackground) {
				GLCOLOR(HoveredRGBABackground);
				glBegin(GL_QUADS);
				glVertex2f(Xpos - Width * 0.5f, Ypos + 0.5f * Height);
				glVertex2f(Xpos + Width * 0.5f, Ypos + 0.5f * Height);
				glVertex2f(Xpos + Width * 0.5f, Ypos - 0.5f * Height);
				glVertex2f(Xpos - Width * 0.5f, Ypos - 0.5f * Height);
				glEnd();
			}
			if ((BYTE)HoveredRGBABorder) {
				GLCOLOR(HoveredRGBABorder);
				glLineWidth(BorderWidth);
				glBegin(GL_LINE_LOOP);
				glVertex2f(Xpos - Width * 0.5f, Ypos + 0.5f * Height);
				glVertex2f(Xpos + Width * 0.5f, Ypos + 0.5f * Height);
				glVertex2f(Xpos + Width * 0.5f, Ypos - 0.5f * Height);
				glVertex2f(Xpos - Width * 0.5f, Ypos - 0.5f * Height);
				glEnd();
			}
		}
		else {
			if ((BYTE)RGBABackground) {
				GLCOLOR(RGBABackground);
				glBegin(GL_QUADS);
				glVertex2f(Xpos - Width * 0.5f, Ypos + 0.5f * Height);
				glVertex2f(Xpos + Width * 0.5f, Ypos + 0.5f * Height);
				glVertex2f(Xpos + Width * 0.5f, Ypos - 0.5f * Height);
				glVertex2f(Xpos - Width * 0.5f, Ypos - 0.5f * Height);
				glEnd();
			}
			if ((BYTE)RGBABorder) {
				GLCOLOR(RGBABorder);
				glLineWidth(BorderWidth);
				glBegin(GL_LINE_LOOP);
				glVertex2f(Xpos - Width * 0.5f, Ypos + 0.5f * Height);
				glVertex2f(Xpos + Width * 0.5f, Ypos + 0.5f * Height);
				glVertex2f(Xpos + Width * 0.5f, Ypos - 0.5f * Height);
				glVertex2f(Xpos - Width * 0.5f, Ypos - 0.5f * Height);
				glEnd();
			}
		}
		if (Tip && Hovered)Tip->Draw();
		STL->Draw();
		Lock.unlock();
	}
	inline DWORD TellType() override {
		return TT_BUTTON;
	}
};

struct ButtonSettings {
	string ButtonText, TipText;
	void(*OnClick)();
	float Xpos, Ypos, Width, Height, CharHeight;
	DWORD RGBAColor, gRGBAColor, RGBABackground, RGBABorder, HoveredRGBAColor, HoveredRGBABackground, HoveredRGBABorder;
	BYTE BasePoint, GradPoint, BorderWidth;
	BIT STLSBasedSettings;
	SingleTextLineSettings* Tip, * STLS;
	ButtonSettings(string ButtonText, void(*OnClick)(), float Xpos, float Ypos, float Width, float Height, float CharHeight, DWORD RGBAColor, DWORD gRGBAColor, BYTE BasePoint, BYTE GradPoint, BYTE BorderWidth, DWORD RGBABackground, DWORD RGBABorder, DWORD HoveredRGBAColor, DWORD HoveredRGBABackground, DWORD HoveredRGBABorder, SingleTextLineSettings* Tip, string TipText) {
		this->STLSBasedSettings = 0;
		this->ButtonText = ButtonText;
		this->TipText = TipText;
		this->OnClick = OnClick;
		this->Tip = Tip;
		this->Xpos = Xpos;
		this->Ypos = Ypos;
		this->Width = Width;
		this->Height = Height;
		this->CharHeight = CharHeight;
		this->RGBAColor = RGBAColor;
		this->gRGBAColor = gRGBAColor;
		this->BasePoint = BasePoint;
		this->GradPoint = GradPoint;
		this->BorderWidth = BorderWidth;
		this->RGBABackground = RGBABackground;
		this->RGBABorder = RGBABorder;
		this->HoveredRGBABackground = HoveredRGBABackground;
		this->HoveredRGBABorder = HoveredRGBABorder;
	}
	ButtonSettings(string ButtonText, SingleTextLineSettings* ButtonTextSTLS, void(*OnClick)(), float Xpos, float Ypos, float Width, float Height, BYTE BorderWidth, DWORD RGBABackground, DWORD RGBABorder, DWORD HoveredRGBAColor, DWORD HoveredRGBABackground, DWORD HoveredRGBABorder, SingleTextLineSettings* Tip, string TipText = " ") {
		this->STLSBasedSettings = 1;
		this->ButtonText = ButtonText;
		this->TipText = TipText;
		this->OnClick = OnClick;
		this->Tip = Tip;
		this->Xpos = Xpos;
		this->Ypos = Ypos;
		this->Width = Width;
		this->Height = Height;
		this->STLS = ButtonTextSTLS;
		this->BorderWidth = BorderWidth;
		this->RGBAColor = ButtonTextSTLS->RGBAColor;
		this->RGBABackground = RGBABackground;
		this->RGBABorder = RGBABorder;
		this->HoveredRGBAColor = HoveredRGBAColor;
		this->HoveredRGBABackground = HoveredRGBABackground;
		this->HoveredRGBABorder = HoveredRGBABorder;
	}
	ButtonSettings(string ButtonText, void(*OnClick)(), float Xpos, float Ypos, float Width, float Height, float CharHeight, DWORD RGBAColor, BYTE BorderWidth, DWORD RGBABackground, DWORD RGBABorder, DWORD HoveredRGBAColor, DWORD HoveredRGBABackground, DWORD HoveredRGBABorder, SingleTextLineSettings* Tip, string TipText) :ButtonSettings(ButtonText, OnClick, Xpos, Ypos, Width, Height, CharHeight, RGBAColor, 0, 15, 15, BorderWidth, RGBABackground, RGBABorder, HoveredRGBAColor, HoveredRGBABackground, HoveredRGBABorder, Tip, TipText) {}
	ButtonSettings(string ButtonText, SingleTextLineSettings* ButtonTextSTLS, void(*OnClick)(), float Xpos, float Ypos, float Width, float Height, BYTE BorderWidth, DWORD RGBABackground, DWORD RGBABorder, DWORD HoveredRGBAColor, DWORD HoveredRGBABackground, DWORD HoveredRGBABorder) :ButtonSettings(ButtonText, ButtonTextSTLS, OnClick, Xpos, Ypos, Width, Height, BorderWidth, RGBABackground, RGBABorder, HoveredRGBAColor, HoveredRGBABackground, HoveredRGBABorder, NULL, " ") {}
	ButtonSettings(string ButtonText, void(*OnClick)(), float Xpos, float Ypos, float Width, float Height, float CharHeight, DWORD RGBAColor, BYTE BorderWidth, DWORD RGBABackground, DWORD RGBABorder, DWORD HoveredRGBAColor, DWORD HoveredRGBABackground, DWORD HoveredRGBABorder) :ButtonSettings(ButtonText, OnClick, Xpos, Ypos, Width, Height, CharHeight, RGBAColor, 0, 15, 15, BorderWidth, RGBABackground, RGBABorder, HoveredRGBAColor, HoveredRGBABackground, HoveredRGBABorder, NULL, " ") {}

	ButtonSettings(SingleTextLineSettings* ButtonTextSTLS, void(*OnClick)(), float Xpos, float Ypos, float Width, float Height, BYTE BorderWidth, DWORD RGBABackground, DWORD RGBABorder, DWORD HoveredRGBAColor, DWORD HoveredRGBABackground, DWORD HoveredRGBABorder) :ButtonSettings(" ", ButtonTextSTLS, OnClick, Xpos, Ypos, Width, Height, BorderWidth, RGBABackground, RGBABorder, HoveredRGBAColor, HoveredRGBABackground, HoveredRGBABorder, NULL, " ") {}
	ButtonSettings(string ButtonText, void(*OnClick)(), float Xpos, float Ypos, float Width, float Height, float CharHeight, DWORD RGBAColor, DWORD gRGBAColor, BYTE BasePoint, BYTE GradPoint, BYTE BorderWidth, DWORD RGBABackground, DWORD RGBABorder, DWORD HoveredRGBAColor, DWORD HoveredRGBABackground, DWORD HoveredRGBABorder) :ButtonSettings(ButtonText, OnClick, Xpos, Ypos, Width, Height, CharHeight, RGBAColor, gRGBAColor, BasePoint, GradPoint, BorderWidth, RGBABackground, RGBABorder, HoveredRGBAColor, HoveredRGBABackground, HoveredRGBABorder, NULL, " ") {}
	ButtonSettings(SingleTextLineSettings* ButtonTextSTLS, float Xpos, float Ypos, float Width, float Height, BYTE BorderWidth, DWORD RGBABackground, DWORD RGBABorder, DWORD HoveredRGBAColor, DWORD HoveredRGBABackground, DWORD HoveredRGBABorder) :ButtonSettings(" ", ButtonTextSTLS, NULL, Xpos, Ypos, Width, Height, BorderWidth, RGBABackground, RGBABorder, HoveredRGBAColor, HoveredRGBABackground, HoveredRGBABorder, NULL, " ") {}
	ButtonSettings(float Xpos, float Ypos, float Width, float Height, float CharHeight, DWORD RGBAColor, BYTE BorderWidth, DWORD RGBABackground, DWORD RGBABorder, DWORD HoveredRGBAColor, DWORD HoveredRGBABackground, DWORD HoveredRGBABorder) :ButtonSettings(" ", NULL, Xpos, Ypos, Width, Height, CharHeight, RGBAColor, 0, 15, 15, BorderWidth, RGBABackground, RGBABorder, HoveredRGBAColor, HoveredRGBABackground, HoveredRGBABorder, NULL, " ") {}
	ButtonSettings(Button* Example, BIT KeepText = false) {
		this->STLSBasedSettings = 1;
		this->ButtonText = (KeepText) ? Example->STL->_CurrentText : " ";
		if (!this->ButtonText.size())this->ButtonText = " ";
		if (Example->Tip) {
			this->Tip = Tip;
			if (TipText.size())
				this->TipText = TipText;
			else
				this->TipText = " ";
		}
		else {
			this->TipText = " ";
			this->Tip = NULL;
		}
		this->OnClick = Example->OnClick;
		this->Xpos = Example->Xpos;
		this->Ypos = Example->Ypos;
		this->Width = Example->Width;
		this->Height = Example->Height;
		this->HoveredRGBAColor = Example->HoveredRGBAColor;
		this->RGBAColor = Example->RGBAColor;
		this->STLS = new SingleTextLineSettings(Example->STL);
		this->gRGBAColor = this->STLS->gRGBAColor;
		this->BorderWidth = Example->BorderWidth;
		this->RGBABackground = Example->RGBABackground;
		this->RGBABorder = Example->RGBABorder;
		this->HoveredRGBABackground = Example->HoveredRGBABackground;
		this->HoveredRGBABorder = Example->HoveredRGBABorder;
	}
	void Move(float dx, float dy) {
		Xpos += dx;
		Ypos += dy;
	}
	void ChangePosition(float NewX, float NewY) {
		NewX -= Xpos;
		NewY -= Ypos;
		Move(NewX, NewY);
	}
	Button* CreateOne(string ButtonText, BIT KeepText = false) {
		if (STLS && STLSBasedSettings)
			return new Button(((KeepText) ? this->ButtonText : ButtonText), STLS, OnClick, Xpos, Ypos, Width, Height, BorderWidth, RGBABackground, RGBABorder, HoveredRGBAColor, HoveredRGBABackground, HoveredRGBABorder, Tip, TipText);
		else
			return new Button(((KeepText) ? this->ButtonText : ButtonText), OnClick, Xpos, Ypos, Width, Height, CharHeight, RGBAColor, gRGBAColor, BasePoint, GradPoint, BorderWidth, RGBABackground, RGBABorder, HoveredRGBAColor, HoveredRGBABackground, HoveredRGBABorder, Tip, TipText);
	}
};

struct TextBox : HandleableUIPart {
	enum class VerticalOverflow { cut, display, recalibrate };
	_Align TextAlign;
	VerticalOverflow VOverflow;
	string Text;
	vector<SingleTextLine*> Lines;
	float Xpos, Ypos;
	float Width, Height;
	float VerticalOffset, CalculatedTextHeight;
	SingleTextLineSettings* STLS;
	BYTE BorderWidth;
	DWORD RGBABorder, RGBABackground, SymbolsPerLine;
	~TextBox() {
		Lock.lock();
		for (auto i = Lines.begin(); i != Lines.end(); i++)
			if (*i)delete* i;
		Lines.clear();
		Lock.unlock();
	}
	TextBox(string Text, SingleTextLineSettings* STLS, float Xpos, float Ypos, float Height, float Width, float VerticalOffset, DWORD RGBABackground, DWORD RGBABorder, BYTE BorderWidth, _Align TextAlign = _Align::left, VerticalOverflow VOverflow = VerticalOverflow::cut) {
		this->TextAlign = TextAlign;
		this->VOverflow = VOverflow;
		this->BorderWidth = BorderWidth;
		this->VerticalOffset = VerticalOffset;
		this->STLS = STLS;
		this->Xpos = Xpos;
		this->Ypos = Ypos;
		this->Width = Width;
		this->RGBABorder = RGBABorder;
		this->RGBABackground = RGBABackground;
		this->Height = Height;
		this->Text = (Text.size()) ? Text : " ";
		RecalculateAvailableSpaceForText();
		TextReformat();
	}
	void TextReformat() {
		Lock.lock();
		vector<vector<string>>SplittedText;
		vector<string> Paragraph;
		string Line;
		STLS->SetNewPos(Xpos, Ypos + 0.5f * Height + 0.5f * VerticalOffset);
		////OOOOOF... Someone help me with these please :d
		for (int i = 0; i < Text.size(); i++) {
			if (Text[i] == ' ') {
				Paragraph.push_back(Line);
				Line.clear();
			}
			else if (Text[i] == '\n') {
				Paragraph.push_back(Line);
				Line.clear();
				SplittedText.push_back(Paragraph);
				Paragraph.clear();
			}
			else Line.push_back(Text[i]);
			if (i == Text.size() - 1) {
				Paragraph.push_back(Line);
				SplittedText.push_back(Paragraph);
				Line.clear();
				Paragraph.clear();
			}
		}
		for (int i = 0; i < SplittedText.size(); i++) {
#define Para SplittedText[i]
#define LINES Paragraph
			for (int q = 0; q < Para.size(); q++) {
				if ((Para[q].size() + 1 + Line.size()) < SymbolsPerLine)
					if (Line.size())Line = (Line + " " + Para[q]);
					else Line = Para[q];
				else {
					if (Line.size())LINES.push_back(Line);
					Line = Para[q];
				}
				while (Line.size() >= SymbolsPerLine) {
					Paragraph.push_back(Line.substr(0, SymbolsPerLine));
					Line = Line.erase(0, SymbolsPerLine);
				}
			}
			Paragraph.push_back(Line);
			Line.clear();
#undef LINES	
#undef Para
		}
		for (int i = 0; i < Paragraph.size(); i++) {
			STLS->Move(0, 0 - VerticalOffset);
			//cout << Paragraph[i] << endl;
			if (VOverflow == VerticalOverflow::cut && STLS->CYpos < Ypos - Height)break;
			Lines.push_back(STLS->CreateOne(Paragraph[i]));
			if (TextAlign == _Align::right)Lines.back()->SafeChangePosition_Argumented(GLOBAL_RIGHT, ((this->Xpos) + (0.5f * Width) - this->STLS->XUnitSize), Lines.back()->CYpos);
			else if (TextAlign == _Align::left)Lines.back()->SafeChangePosition_Argumented(GLOBAL_LEFT, ((this->Xpos) - (0.5f * Width) + this->STLS->XUnitSize), Lines.back()->CYpos);
		}
		CalculatedTextHeight = (Lines.front()->CYpos - Lines.back()->CYpos) + Lines.front()->CalculatedHeight;
		if (VOverflow == VerticalOverflow::recalibrate) {
			float dy = (CalculatedTextHeight - this->Height);
			for (auto Y = Lines.begin(); Y != Lines.end(); Y++) {
				(*Y)->SafeMove(0, (dy + Lines.front()->CalculatedHeight) * 0.5f);
			}
		}
		Lock.unlock();
	}
	void SafeTextColorChange(DWORD NewColor) {
		Lock.lock();
		for (auto i = Lines.begin(); i != Lines.end(); i++) {
			(*i)->SafeColorChange(NewColor);
		}
		Lock.unlock();
	}
	BIT MouseHandler(float mx, float my, CHAR Button/*-1 left, 1 right, 0 move*/, CHAR State /*-1 down, 1 up*/)  override {
		return 0;
	}
	void SafeStringReplace(string NewString) override {
		Lock.lock();
		this->Text = NewString;
		Lines.clear();
		RecalculateAvailableSpaceForText();
		TextReformat();
		Lock.unlock();
	}
	void KeyboardHandler(char CH) {
		return;
	}
	void RecalculateAvailableSpaceForText() {
		Lock.lock();
		SymbolsPerLine = floor((Width + STLS->XUnitSize * 2) / (STLS->XUnitSize * 2 + STLS->SpaceWidth));
		Lock.unlock();
	}
	void SafeMove(float dx, float dy) {
		Lock.lock();
		Xpos += dx;
		Ypos += dy;
		STLS->Move(dx, dy);
		for (int i = 0; i < Lines.size(); i++) {
			Lines[i]->SafeMove(dx, dy);
		}
		Lock.unlock();
	}
	void SafeChangePosition(float NewX, float NewY) {
		Lock.lock();
		NewX -= Xpos;
		NewY -= Ypos;
		SafeMove(NewX, NewY);
		Lock.unlock();
	}
	void SafeChangePosition_Argumented(BYTE Arg, float NewX, float NewY) {
		Lock.lock();
		float CW = 0.5f * (
			(INT32)((BIT)(GLOBAL_LEFT & Arg))
			- (INT32)((BIT)(GLOBAL_RIGHT & Arg))
			) * Width,
			CH = 0.5f * (
			(INT32)((BIT)(GLOBAL_BOTTOM & Arg))
				- (INT32)((BIT)(GLOBAL_TOP & Arg))
				) * Height;
		SafeChangePosition(NewX + CW, NewY + CH);
		Lock.unlock();
	}
	void Draw() override {
		Lock.lock();
		if ((BYTE)RGBABackground) {
			GLCOLOR(RGBABackground);
			glBegin(GL_QUADS);
			glVertex2f(Xpos - (Width * 0.5f), Ypos + (0.5f * Height));
			glVertex2f(Xpos + (Width * 0.5f), Ypos + (0.5f * Height));
			glVertex2f(Xpos + (Width * 0.5f), Ypos - (0.5f * Height));
			glVertex2f(Xpos - (Width * 0.5f), Ypos - (0.5f * Height));
			glEnd();
		}
		if ((BYTE)RGBABorder) {
			GLCOLOR(RGBABorder);
			glLineWidth(BorderWidth);
			glBegin(GL_LINE_LOOP);
			glVertex2f(Xpos - (Width * 0.5f), Ypos + (0.5f * Height));
			glVertex2f(Xpos + (Width * 0.5f), Ypos + (0.5f * Height));
			glVertex2f(Xpos + (Width * 0.5f), Ypos - (0.5f * Height));
			glVertex2f(Xpos - (Width * 0.5f), Ypos - (0.5f * Height));
			glEnd();
		}
		for (int i = 0; i < Lines.size(); i++) Lines[i]->Draw();
		Lock.unlock();
	}
	inline DWORD TellType() override {
		return TT_TEXTBOX;
	}
};

#define ARROW_STICK_HEIGHT 10
struct SelectablePropertedList : HandleableUIPart {
	_Align TextInButtonsAlign;
	void(*OnSelect)(int ID);
	void(*OnGetProperties)(int ID);
	float HeaderCXPos, HeaderYPos, CalculatedHeight, SpaceBetween, Width;
	ButtonSettings* ButtSettings;
	deque<string> SelectorsText;
	deque<Button*> Selectors;
	DWORD SelectedID;
	DWORD MaxVisibleLines, CurrentTopLineID, MaxCharsInLine;
	BYTE TopArrowHovered, BottomArrowHovered;
	~SelectablePropertedList() {
		Lock.lock();
		for (auto Y = Selectors.begin(); Y != Selectors.end(); Y++)
			delete (*Y);
		Lock.unlock();
	}
	SelectablePropertedList(ButtonSettings* ButtSettings, void(*OnSelect)(int SelectedID), void(*OnGetProperties)(int ID), float HeaderCXPos, float HeaderYPos, float Width, float SpaceBetween, DWORD MaxCharsInLine = 0, DWORD MaxVisibleLines = 0, _Align TextInButtonsAlign = _Align::left) {
		this->MaxCharsInLine = MaxCharsInLine;
		this->MaxVisibleLines = MaxVisibleLines;
		this->ButtSettings = ButtSettings;
		this->OnSelect = OnSelect;
		this->OnGetProperties = OnGetProperties;
		this->HeaderCXPos = HeaderCXPos;
		this->Width = Width;
		this->SpaceBetween = SpaceBetween;
		this->HeaderCXPos = HeaderCXPos;
		this->HeaderYPos = HeaderYPos;
		this->CurrentTopLineID = 0;
		this->TextInButtonsAlign = TextInButtonsAlign;
		SelectedID = 0xFFFFFFFF;
	}
	void RecalculateCurrentHeight() {
		Lock.lock();
		CalculatedHeight = SpaceBetween * Selectors.size();
		Lock.unlock();
	}
	BIT MouseHandler(float mx, float my, CHAR Button/*-1 left, 1 right, 0 move*/, CHAR State /*-1 down, 1 up*/)  override {
		Lock.lock();
		TopArrowHovered = BottomArrowHovered = 0;
		if (fabsf(mx - HeaderCXPos) < 0.5 * Width && my < HeaderYPos && my > HeaderYPos - CalculatedHeight) {
			if (Button == 2 /*UP*/) {
				if (State == -1) {
					SafeRotateList(-3);
				}
			}
			else if (Button == 3 /*DOWN*/) {
				if (State == -1) {
					SafeRotateList(3);
				}
			}
		}
		if (MaxVisibleLines && Selectors.size() < SelectorsText.size()) {
			if (fabsf(mx - HeaderCXPos) < 0.5 * Width) {
				if (my > HeaderYPos&& my < HeaderYPos + ARROW_STICK_HEIGHT) {
					TopArrowHovered = 1;
					if (Button == -1 && State == -1) {
						SafeRotateList(-1);
						Lock.unlock();
						return 1;
					}
				}
				else if (my < HeaderYPos - CalculatedHeight && my > HeaderYPos - CalculatedHeight - ARROW_STICK_HEIGHT) {
					BottomArrowHovered = 1;
					if (Button == -1 && State == -1) {
						SafeRotateList(1);
						Lock.unlock();
						return 1;
					}
				}
			}
		}
		if (Button) {
			BIT flag = 1;
			for (int i = 0; i < Selectors.size(); i++) {
				if (Selectors[i]->MouseHandler(mx, my, Button, State) && flag) {
					if (Button == -1) {
						SelectedID = i + CurrentTopLineID;
						if (OnSelect)OnSelect(i + CurrentTopLineID);
					}
					if (Button == 1) {
						//cout << "PROP\n";
						if (OnGetProperties)OnGetProperties(i + CurrentTopLineID);
					}
					flag = 0;
					Lock.unlock();
					return 1;
				}
			}
		}
		else {
			for (int i = 0; i < Selectors.size(); i++)
				Selectors[i]->MouseHandler(mx, my, 0, 0);
		}
		if (SelectedID < SelectorsText.size())
			if (SelectedID >= CurrentTopLineID && SelectedID < CurrentTopLineID + MaxVisibleLines)
				Selectors[SelectedID - CurrentTopLineID]->MouseHandler(Selectors[SelectedID - CurrentTopLineID]->Xpos, Selectors[SelectedID - CurrentTopLineID]->Ypos, 0, 0);
		Lock.unlock();
		return 0;
	}
	void SafeStringReplace(string NewString) override {
		Lock.lock();
		this->SafeStringReplace(NewString, 0xFFFFFFFF);
		Lock.unlock();
	}
	void SafeStringReplace(string NewString, DWORD LineID) {
		Lock.lock();
		if (LineID == 0xFFFFFFFF) {
			SelectorsText[SelectedID] = NewString;
			if (SelectedID < SelectorsText.size() && MaxVisibleLines)
				if (SelectedID > CurrentTopLineID&& SelectedID < CurrentTopLineID + MaxVisibleLines)
					Selectors[SelectedID - CurrentTopLineID]->SafeStringReplace(NewString);
		}
		else {
			SelectorsText[LineID] = NewString;
			if (LineID > CurrentTopLineID&& LineID - CurrentTopLineID < MaxVisibleLines)
				Selectors[LineID - CurrentTopLineID]->SafeStringReplace(NewString);
		}
		Lock.unlock();
	}
	void SafeUpdateLines() {
		Lock.lock();
		while (SelectorsText.size() < Selectors.size())Selectors.pop_back();
		if (CurrentTopLineID + MaxVisibleLines > SelectorsText.size()) {
			if (SelectorsText.size() >= MaxVisibleLines)CurrentTopLineID = SelectorsText.size() - MaxVisibleLines;
			else CurrentTopLineID = 0;
		}
		for (int i = 0; i < Selectors.size(); i++)
			if (i + CurrentTopLineID < SelectorsText.size())
				Selectors[i]->SafeStringReplace(
				(MaxCharsInLine) ?
					(SelectorsText[i + CurrentTopLineID].substr(0, MaxCharsInLine))
					:
					(SelectorsText[i + CurrentTopLineID])
				);
		ReSetAlign_All(TextInButtonsAlign);
		Lock.unlock();
	}
	void SafeRotateList(INT32 Delta) {
		Lock.lock();
		if (!MaxVisibleLines) {
			Lock.unlock(); return;
		}
		if (Delta < 0 && CurrentTopLineID < 0 - Delta)CurrentTopLineID = 0;
		else if (Delta > 0 && CurrentTopLineID + Delta + MaxVisibleLines > SelectorsText.size())
			CurrentTopLineID = SelectorsText.size() - MaxVisibleLines;
		else CurrentTopLineID += Delta;
		SafeUpdateLines();
		Lock.unlock();
	}
	void SafeRemoveStringByID(DWORD ID) {
		Lock.lock();
		if (ID >= SelectorsText.size()) {
			Lock.unlock(); return;
		}
		if (SelectorsText.empty()) {
			Lock.unlock(); return;
		}
		if (MaxVisibleLines) {
			if (ID < CurrentTopLineID) {
				CurrentTopLineID--;
			}
			else if (ID == CurrentTopLineID) {
				if (CurrentTopLineID == SelectorsText.size() - 1)CurrentTopLineID--;
			}
		}
		SelectorsText.erase(SelectorsText.begin() + ID);
		SafeUpdateLines();
		SelectedID = 0xFFFFFFFF;
		Lock.unlock();
	}
	void ReSetAlignFor(DWORD ID, _Align Align) {
		Lock.lock();
		if (ID >= Selectors.size()) {
			Lock.unlock(); return;
		}
		float nx = HeaderCXPos - ((Align == _Align::left) ? 0.5f : ((Align == _Align::right) ? 0 - 0.5f : 0)) * (Width - SpaceBetween);
		Selectors[ID]->STL->SafeChangePosition_Argumented(Align, nx, Selectors[ID]->Ypos);
		Lock.unlock();
	}
	void ReSetAlign_All(_Align Align) {
		Lock.lock();
		if (!Align) {
			Lock.unlock(); return;
		}
		float nx = HeaderCXPos - ((Align == _Align::left) ? 0.5f : ((Align == _Align::right) ? 0 - 0.5f : 0)) * (Width - SpaceBetween);
		for (int i = 0; i < Selectors.size(); i++)
			Selectors[i]->STL->SafeChangePosition_Argumented(Align, nx, Selectors[i]->Ypos);
		Lock.unlock();
	}
	void SafePushBackNewString(string ButtonText) {
		Lock.lock();
		if (MaxCharsInLine)ButtonText = ButtonText.substr(0, MaxCharsInLine);
		SelectorsText.push_back(ButtonText);
		if (MaxVisibleLines && SelectorsText.size() > MaxVisibleLines) {
			SafeUpdateLines(); {
				Lock.unlock(); return;
			}
		}
		ButtSettings->ChangePosition(HeaderCXPos, HeaderYPos - (SelectorsText.size() - 0.5f) * SpaceBetween);
		ButtSettings->Height = SpaceBetween;
		ButtSettings->Width = Width;
		ButtSettings->OnClick = NULL;
		Button* ptr;
		Selectors.push_back(ptr = ButtSettings->CreateOne(ButtonText));
		//free(ptr);
		RecalculateCurrentHeight();
		ReSetAlignFor(SelectorsText.size() - 1, this->TextInButtonsAlign);
		Lock.unlock();
	}
	void PushStrings(list<string> LStrings) {
		Lock.lock();
		for (auto Y = LStrings.begin(); Y != LStrings.end(); Y++)
			SafePushBackNewString(*Y);
		Lock.unlock();
	}
	void PushStrings(vector<string> LStrings) {
		Lock.lock();
		for (auto Y = LStrings.begin(); Y != LStrings.end(); Y++)
			SafePushBackNewString(*Y);
		Lock.unlock();
	}
	void PushStrings(initializer_list<string> LStrings) {
		Lock.lock();
		for (auto Y = LStrings.begin(); Y != LStrings.end(); Y++)
			SafePushBackNewString(*Y);
		Lock.unlock();
	}
	void SafeChangePosition_Argumented(BYTE Arg, float NewX, float NewY) {
		Lock.lock();
		float CW = 0.5f * (
			(INT32)((BIT)(GLOBAL_LEFT & Arg))
			- (INT32)((BIT)(GLOBAL_RIGHT & Arg))
			) * Width,
			CH = 0.5f * (
			(INT32)((BIT)(GLOBAL_BOTTOM & Arg))
				- (INT32)((BIT)(GLOBAL_TOP & Arg))
				) * CalculatedHeight;
		SafeChangePosition(NewX + CW, NewY - 0.5f * CalculatedHeight + CH);
		Lock.unlock();
	}
	void KeyboardHandler(CHAR CH) override {
		return;
	}
	void SafeChangePosition(float NewCXPos, float NewHeaderYPos) override {
		Lock.lock();
		NewCXPos -= HeaderCXPos;
		NewHeaderYPos -= HeaderYPos;
		SafeMove(NewCXPos, NewHeaderYPos);
		Lock.unlock();
	}
	void SafeMove(float dx, float dy) override {
		Lock.lock();
		HeaderCXPos += dx;
		HeaderYPos += dy;
		for (auto Y = Selectors.begin(); Y != Selectors.end(); Y++)
			(*Y)->SafeMove(dx, dy);
		Lock.unlock();
	}
	void Draw() override {
		Lock.lock();
		if (Selectors.size() < SelectorsText.size()) {
			///TOP BAR
			if (TopArrowHovered)GLCOLOR(ButtSettings->HoveredRGBABorder);
			else GLCOLOR(ButtSettings->RGBABorder);
			glBegin(GL_QUADS);
			glVertex2f(HeaderCXPos - 0.5f * Width, HeaderYPos);
			glVertex2f(HeaderCXPos + 0.5f * Width, HeaderYPos);
			glVertex2f(HeaderCXPos + 0.5f * Width, HeaderYPos + ARROW_STICK_HEIGHT);
			glVertex2f(HeaderCXPos - 0.5f * Width, HeaderYPos + ARROW_STICK_HEIGHT);
			///BOTTOM BAR
			if (BottomArrowHovered)GLCOLOR(ButtSettings->HoveredRGBABorder);
			else GLCOLOR(ButtSettings->RGBABorder);
			glVertex2f(HeaderCXPos - 0.5f * Width, HeaderYPos - CalculatedHeight);
			glVertex2f(HeaderCXPos + 0.5f * Width, HeaderYPos - CalculatedHeight);
			glVertex2f(HeaderCXPos + 0.5f * Width, HeaderYPos - CalculatedHeight - ARROW_STICK_HEIGHT);
			glVertex2f(HeaderCXPos - 0.5f * Width, HeaderYPos - CalculatedHeight - ARROW_STICK_HEIGHT);
			glEnd();
			///TOP ARROW
			if (TopArrowHovered)
				if (ButtSettings->HoveredRGBAColor & 0xFF)GLCOLOR(ButtSettings->HoveredRGBAColor);
				else GLCOLOR(ButtSettings->RGBAColor);
			else GLCOLOR(ButtSettings->RGBAColor);
			glBegin(GL_TRIANGLES);
			glVertex2f(HeaderCXPos, HeaderYPos + 9 * ARROW_STICK_HEIGHT / 10);
			glVertex2f(HeaderCXPos + ARROW_STICK_HEIGHT * 0.5f, HeaderYPos + ARROW_STICK_HEIGHT / 10);
			glVertex2f(HeaderCXPos - ARROW_STICK_HEIGHT * 0.5f, HeaderYPos + ARROW_STICK_HEIGHT / 10);
			///BOTTOM ARROW
			if (BottomArrowHovered)
				if (ButtSettings->HoveredRGBAColor & 0xFF)GLCOLOR(ButtSettings->HoveredRGBAColor);
				else GLCOLOR(ButtSettings->RGBAColor);
			else GLCOLOR(ButtSettings->RGBAColor);
			glVertex2f(HeaderCXPos, HeaderYPos - CalculatedHeight - 9 * ARROW_STICK_HEIGHT / 10);
			glVertex2f(HeaderCXPos + ARROW_STICK_HEIGHT * 0.5f, HeaderYPos - CalculatedHeight - ARROW_STICK_HEIGHT / 10);
			glVertex2f(HeaderCXPos - ARROW_STICK_HEIGHT * 0.5f, HeaderYPos - CalculatedHeight - ARROW_STICK_HEIGHT / 10);
			glEnd();
		}
		for (auto Y = Selectors.begin(); Y != Selectors.end(); Y++)
			(*Y)->Draw();
		Lock.unlock();
	}
	inline DWORD TellType() override {
		return TT_SELPROPLIST;
	}
};

#define HTSQ2 (2)
struct SpecialSigns {
	static void DrawOK(float x, float y, float SZParam, DWORD RGBAColor, DWORD NOARGUMENT = 0) {
		GLCOLOR(RGBAColor);
		glLineWidth(ceil(SZParam / 2));
		glBegin(GL_LINE_STRIP);
		glVertex2f(x - SZParam * 0.766f, y + SZParam * 0.916f);
		glVertex2f(x - SZParam * 0.1f, y + SZParam * 0.25f);
		glVertex2f(x + SZParam * 0.9f, y + SZParam * 1.25f);
		glEnd();
		glPointSize(ceil(SZParam / 2));
		glBegin(GL_POINTS);
		glVertex2f(x - SZParam * 0.1f, y + SZParam * 0.25f);
		glEnd();
	}
	static void DrawExTriangle(float x, float y, float SZParam, DWORD RGBAColor, DWORD SecondaryRGBAColor) {
		GLCOLOR(RGBAColor);
		glBegin(GL_TRIANGLES);
		glVertex2f(x, y + HTSQ2 * SZParam);
		glVertex2f(x - SZParam, y);
		glVertex2f(x + SZParam, y);
		glEnd();
		GLCOLOR(SecondaryRGBAColor);
		glLineWidth(ceil(SZParam / 8));
		glBegin(GL_LINE_LOOP);
		glVertex2f(x, y + HTSQ2 * SZParam);
		glVertex2f(x - SZParam, y);
		glVertex2f(x + SZParam, y);
		glEnd();
		glLineWidth(ceil(SZParam / 4));
		glBegin(GL_LINES);
		glVertex2f(x, y + SZParam * 0.6f);
		glVertex2f(x, y + SZParam * 1.40f);
		glVertex2f(x, y + SZParam * 0.2f);
		glVertex2f(x, y + SZParam * 0.4f);
		glEnd();
	}
	static void DrawFileSign(float x, float y, float SZParam, DWORD RGBAColor, DWORD SecondaryRGBAColor) {
		GLCOLOR(RGBAColor);
		glLineWidth(ceil(SZParam / 5));
		glBegin(GL_LINE_LOOP);
		glVertex2f(x, y + SZParam);
		glVertex2f(x - SZParam, y);
		glVertex2f(x - SZParam, y - SZParam);
		glVertex2f(x + SZParam, y - SZParam);
		glVertex2f(x + SZParam, y + SZParam);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(x, y + SZParam);
		glVertex2f(x, y);
		glVertex2f(x, y);
		glVertex2f(x - SZParam, y);
		glEnd();
		glPointSize(ceil(SZParam / 5));
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glVertex2f(x, y + SZParam);
		glVertex2f(x - SZParam, y);
		glVertex2f(x - SZParam, y - SZParam);
		glVertex2f(x + SZParam, y - SZParam);
		glVertex2f(x + SZParam, y + SZParam);
		glEnd();
	}
	static void DrawACircle(float x, float y, float SZParam, DWORD RGBAColor, DWORD SecondaryRGBAColor) {
		GLCOLOR(SecondaryRGBAColor);
		glBegin(GL_POLYGON);
		for (float a = -90; a < 270; a += 5)
			glVertex2f(SZParam * 1.25f * (cos(ANGTORAD(a))) + x, SZParam * 1.25f * (sin(ANGTORAD(a))) + y + SZParam * 0.75f);
		glEnd();
		GLCOLOR(RGBAColor);
		glLineWidth(ceil(SZParam / 10));
		glBegin(GL_LINE_LOOP);
		for (float a = -90; a < 270; a += 5)
			glVertex2f(SZParam * 1.25f * (cos(ANGTORAD(a))) + x, SZParam * 1.25f * (sin(ANGTORAD(a))) + y + SZParam * 0.75f);
		glEnd();
	}
	static void DrawNo(float x, float y, float SZParam, DWORD RGBAColor, DWORD NOARGUMENT = 0) {
		GLCOLOR(RGBAColor);
		glLineWidth(ceil(SZParam / 2));
		glBegin(GL_LINES);
		glVertex2f(x - SZParam * 0.5f, y + SZParam * 0.25f);
		glVertex2f(x + SZParam * 0.5f, y + SZParam * 1.25f);
		glVertex2f(x + SZParam * 0.5f, y + SZParam * 0.25f);
		glVertex2f(x - SZParam * 0.5f, y + SZParam * 1.25f);
		glEnd();
	}
	static void DrawWait(float x, float y, float SZParam, DWORD RGBAColor, DWORD TotalStages) {
		float Start = ((float)((TimerV % TotalStages) * 360)) / (float)(TotalStages), t;
		BYTE R = (RGBAColor >> 24), G = (RGBAColor >> 16) & 0xFF, B = (RGBAColor >> 8) & 0xFF, A = (RGBAColor) & 0xFF;
		//printf("%x\n", CurStage_TotalStages);
		glLineWidth(ceil(SZParam / 1.5f));
		glBegin(GL_LINES);
		for (float a = 0; a < 360.5f; a += (180.f / (TotalStages))) {
			t = a / 360.f;
			glColor4ub(
				255 * (t)+R * (1 - t),
				255 * (t)+G * (1 - t),
				255 * (t)+B * (1 - t),
				255 * (t)+A * (1 - t)
			);
			glVertex2f(SZParam * 1.25f * (cos(ANGTORAD(a + Start))) + x, SZParam * 1.25f * (sin(ANGTORAD(a + Start))) + y + SZParam * 0.75f);
		}
		glEnd();
	}
};

struct SpecialSignHandler : HandleableUIPart {
	float x, y, SZParam;
	DWORD FRGBA, SRGBA;
	void(*DrawFunc)(float, float, float, DWORD, DWORD);
	SpecialSignHandler(void(*DrawFunc)(float, float, float, DWORD, DWORD), float x, float y, float SZParam, DWORD FRGBA, DWORD SRGBA) {
		this->DrawFunc = DrawFunc;
		this->x = x;
		this->y = y;
		this->SZParam = SZParam;
		this->FRGBA = FRGBA;
		this->SRGBA = SRGBA;
	}
	void Draw() override {
		Lock.lock();
		if (this->DrawFunc)this->DrawFunc(x, y, SZParam, FRGBA, SRGBA);
		Lock.unlock();
	}
	void SafeMove(float dx, float dy) override {
		Lock.lock();
		x += dx;
		y += dy;
		Lock.unlock();
	}
	void SafeChangePosition(float NewX, float NewY) override {
		Lock.lock();
		x = NewX;
		y = NewY;
		Lock.unlock();
	}
	void _ReplaceVoidFunc(void(*NewDrawFunc)(float, float, float, DWORD, DWORD)) {
		Lock.lock();
		this->DrawFunc = NewDrawFunc;
		Lock.unlock();
	}
	void SafeChangePosition_Argumented(BYTE Arg, float NewX, float NewY) override {

	}
	void KeyboardHandler(CHAR CH) override {
		return;
	}
	void SafeStringReplace(string Meaningless) override {
		return;
	}
	BIT MouseHandler(float mx, float my, CHAR Button, CHAR State) override {
		return 0;
	}
};

struct WheelVariableChanger :HandleableUIPart {
	enum class Type { exponential, linear };
	enum class Sensitivity { on_enter, on_click, on_wheel };
	Type type;
	Sensitivity Sen;
	InputField* var_if, * fac_if;
	float Width, Height;
	float Xpos, Ypos;
	string var_s, fact_s;
	double variable;
	double factor;
	bool IsHovered, WheelFieldHovered;
	void(*OnApply)(double);
	~WheelVariableChanger() {
		if (var_if)
			delete var_if;
		if (var_if)
			delete fac_if;
	}
	WheelVariableChanger(void(*OnApply)(double), float Xpos, float Ypos, double default_var, double default_fact, SingleTextLineSettings* STLS, string var_string = " ", string fac_string = " ", Type type = Type::exponential) : Width(100), Height(50) {
		this->OnApply = OnApply;
		this->Xpos = Xpos;
		this->Ypos = Ypos;
		this->variable = default_var;
		this->factor = default_fact;
		this->IsHovered = WheelFieldHovered = false;
		this->type = type;
		this->Sen = Sensitivity::on_wheel;
		var_if = new InputField(to_string(default_var).substr(0, 8), Xpos - 25., Ypos + 15, 10, 40, STLS, nullptr, 0x007FFFFF, STLS, var_string, 8, _Align::center, _Align::center, InputField::Type::FP_PositiveNumbers);
		fac_if = new InputField(to_string(default_fact).substr(0, 8), Xpos - 25., Ypos - 5, 10, 40, STLS, nullptr, 0x007FFFFF, STLS, fac_string, 8, _Align::center, _Align::center, InputField::Type::FP_PositiveNumbers);
	}
	void Draw() override {
		GLCOLOR(0xFFFFFF3F + WheelFieldHovered * 0x3F);
		glBegin(GL_QUADS);
		glVertex2f(Xpos, Ypos + 25);
		glVertex2f(Xpos, Ypos - 25);
		glVertex2f(Xpos + 50, Ypos - 25);
		glVertex2f(Xpos + 50, Ypos + 25);
		glEnd();
		GLCOLOR((0x007FFF3F + WheelFieldHovered * 0x3F));
		glBegin(GL_LINE_LOOP);
		glVertex2f(Xpos, Ypos + 25);
		glVertex2f(Xpos, Ypos - 25);
		glVertex2f(Xpos + 50, Ypos - 25);
		glVertex2f(Xpos + 50, Ypos + 25);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex2f(Xpos - 50, Ypos + 25);
		glVertex2f(Xpos - 50, Ypos - 25);
		glVertex2f(Xpos + 50, Ypos - 25);
		glVertex2f(Xpos + 50, Ypos + 25);
		glEnd();
		var_if->Draw();
		fac_if->Draw();
	}
	void SafeMove(float dx, float dy) override {
		Xpos += dx;
		Ypos += dy;
		var_if->SafeMove(dx, dy);
		fac_if->SafeMove(dx, dy);
	}
	void SafeChangePosition(float NewX, float NewY) override {
		NewX -= Xpos;
		NewY -= Ypos;
		SafeMove(NewX, NewY);
	}
	void SafeChangePosition_Argumented(BYTE Arg, float NewX, float NewY) override {
		float CW = 0.5f * (
			(INT32)((BIT)(GLOBAL_LEFT & Arg))
			- (INT32)((BIT)(GLOBAL_RIGHT & Arg))
			) * Width,
			CH = 0.5f * (
			(INT32)((BIT)(GLOBAL_BOTTOM & Arg))
				- (INT32)((BIT)(GLOBAL_TOP & Arg))
				) * Height;
		SafeChangePosition(NewX + CW, NewY + CH);
	}
	void CheckupInputs() {
		variable = stod(var_if->STL->_CurrentText);
		factor = stod(fac_if->STL->_CurrentText);
	}
	void KeyboardHandler(CHAR CH) override {
		fac_if->KeyboardHandler(CH);
		var_if->KeyboardHandler(CH);
		if (IsHovered) {
			if (CH == 13) {
				CheckupInputs();
				if (OnApply)
					OnApply(variable);
			}
		}
	}
	void SafeStringReplace(string Meaningless) override {

	}
	inline void Increment(double new_factor) {
		switch (type) {
		case WheelVariableChanger::Type::exponential: {variable *= new_factor; break; }
		case WheelVariableChanger::Type::linear: {variable += new_factor; break; }
		}
		var_if->UpdateInputString(to_string(variable));
	}
	inline void Decrement(double new_factor) {
		switch (type) {
		case WheelVariableChanger::Type::exponential: {variable /= new_factor; break; }
		case WheelVariableChanger::Type::linear: {variable -= new_factor; break; }
		}
		var_if->UpdateInputString(to_string(variable));
	}
	BIT MouseHandler(float mx, float my, CHAR Button, CHAR State) override {
		this->fac_if->MouseHandler(mx, my, Button, State);
		this->var_if->MouseHandler(mx, my, Button, State);
		mx -= Xpos;
		my -= Ypos;
		if (fabsf(mx) < Width * 0.5 && fabsf(my) < Height * 0.5) {
			IsHovered = true;
			if (mx >= 0 && mx <= Width * 0.5 && fabsf(my) < Height * 0.5) {
				if (Sen == Sensitivity::on_click && State == 1)
					if (OnApply)
						OnApply(variable);
				WheelFieldHovered = true;
				if (Button) {
					CheckupInputs();
					if (Button == 2 /*UP*/) {
						if (State == -1) {
							Increment(factor);
							if (Sen == Sensitivity::on_wheel)
								if (OnApply)
									OnApply(variable);
						}
					}
					else if (Button == 3 /*DOWN*/) {
						if (State == -1) {
							Decrement(factor);
							if (Sen == Sensitivity::on_wheel)
								if (OnApply)
									OnApply(variable);
						}
					}
				}
			}
		}
		else {
			IsHovered = false;
			WheelFieldHovered = false;
		}
		return 0;
	}
};

#define WindowHeapSize 15
struct MoveableWindow :HandleableUIPart {
	float XWindowPos, YWindowPos;//leftup corner coordinates
	float Width, Height;
	DWORD RGBABackground, RGBAThemeColor, RGBAGradBackground;
	SingleTextLine* WindowName;
	map<string, HandleableUIPart*> WindowActivities;
	BIT Drawable;
	BIT HoveredCloseButton;
	BIT CursorFollowMode;
	float PCurX, PCurY;
	~MoveableWindow() {
		Lock.lock();
		delete WindowName;
		for (auto i = WindowActivities.begin(); i != WindowActivities.end(); i++)
			delete i->second;
		WindowActivities.clear();
		Lock.unlock();
	}
	MoveableWindow(string WindowName, SingleTextLineSettings* WindowNameSettings, float XPos, float YPos, float Width, float Height, DWORD RGBABackground, DWORD RGBAThemeColor, DWORD RGBAGradBackground = 0) {
		if (WindowNameSettings) {
			WindowNameSettings->SetNewPos(XPos, YPos);
			this->WindowName = WindowNameSettings->CreateOne(WindowName);
			this->WindowName->SafeMove(this->WindowName->CalculatedWidth * 0.5 + WindowHeapSize * 0.5f, 0 - WindowHeapSize * 0.5f);
		}
		this->XWindowPos = XPos;
		this->YWindowPos = YPos;
		this->Width = Width;
		this->Height = (Height < WindowHeapSize) ? WindowHeapSize : Height;
		this->RGBABackground = RGBABackground;
		this->RGBAThemeColor = RGBAThemeColor;
		this->RGBAGradBackground = RGBAGradBackground;
		this->CursorFollowMode = 0;
		this->HoveredCloseButton = 0;
		this->Drawable = 1;
		this->PCurX = 0.;
		this->PCurY = 0.;
	}
	void KeyboardHandler(char CH) {
		Lock.lock();
		for (auto i = WindowActivities.begin(); i != WindowActivities.end(); i++)
			i->second->KeyboardHandler(CH);
		Lock.unlock();
	}
	BIT MouseHandler(float mx, float my, CHAR Button/*-1 left, 1 right, 0 move*/, CHAR State /*-1 down, 1 up*/) override {
		Lock.lock();
		if (!Drawable) {
			Lock.unlock();
			return 0;
		}
		HoveredCloseButton = 0;
		if (mx > XWindowPos + Width - WindowHeapSize && mx < XWindowPos + Width && my < YWindowPos && my > YWindowPos - WindowHeapSize) {///close button
			if (Button && State == 1) {
				Drawable = 0;
				CursorFollowMode = 0;
				Lock.unlock();
				return 1;
			}
			else if (!Button) {
				HoveredCloseButton = 1;
			}
		}
		else if (mx - XWindowPos < Width && mx - XWindowPos>0 && my<YWindowPos && my>YWindowPos - WindowHeapSize) {
			if (Button == -1) {///window header
				if (State == -1) {
					CursorFollowMode = !CursorFollowMode;
					PCurX = mx;
					PCurY = my;
				}
				Lock.unlock();
				return 1;
			}
		}
		if (CursorFollowMode) {
			SafeMove(mx - PCurX, my - PCurY);
			PCurX = mx;
			PCurY = my;
			Lock.unlock();
			return 1;
		}

		BIT flag = 0;
		auto Y = WindowActivities.begin();
		while (Y != WindowActivities.end()) {
			flag = Y->second->MouseHandler(mx, my, Button, State);
			Y++;
		}

		if (mx - XWindowPos < Width && mx - XWindowPos > 0 && YWindowPos - my > 0 && YWindowPos - my < Height)
			if (Button) {
				Lock.unlock();
				return 1;
			}
			else {
				Lock.unlock();
				return flag;
			}
		else {
			Lock.unlock();
			return flag;
		}
		//return 1;

	}
	void SafeChangePosition(float NewXpos, float NewYpos) override {
		Lock.lock();
		NewXpos -= XWindowPos;
		NewYpos -= YWindowPos;
		SafeMove(NewXpos, NewYpos);
		Lock.unlock();
	}
	BIT DeleteUIElementByName(string ElementName) {
		Lock.lock();
		auto ptr = WindowActivities.find(ElementName);
		if (ptr == WindowActivities.end()) {
			Lock.unlock();
			return 0;
		}
		auto deletable = ptr->second;
		WindowActivities.erase(ElementName);
		delete deletable;
		Lock.unlock();
		return 1;
	}
	BIT AddUIElement(string ElementName, HandleableUIPart* Elem) {
		Lock.lock();
		auto ans = WindowActivities.insert_or_assign(ElementName, Elem);
		Lock.unlock();
		return ans.second;
	}
	void SafeMove(float dx, float dy) override {
		Lock.lock();
		XWindowPos += dx;
		YWindowPos += dy;
		WindowName->SafeMove(dx, dy);
		for (auto Y = WindowActivities.begin(); Y != WindowActivities.end(); Y++)
			Y->second->SafeMove(dx, dy);
		Lock.unlock();
	}
	void SafeChangePosition_Argumented(BYTE Arg, float NewX, float NewY) {
		Lock.lock();
		float CW = 0.5f * (
			(INT32)(!!(GLOBAL_LEFT & Arg))
			- (INT32)(!!(GLOBAL_RIGHT & Arg))
			- 1) * Width,
			CH = 0.5f * (
			(INT32)(!!(GLOBAL_BOTTOM & Arg))
				- (INT32)(!!(GLOBAL_TOP & Arg))
				+ 1) * Height;
		SafeChangePosition(NewX + CW, NewY + CH);
		Lock.unlock();
	}
	void Draw() override {
		Lock.lock();
		if (!Drawable) {
			Lock.unlock();
			return;
		}
		GLCOLOR(RGBABackground);
		glBegin(GL_QUADS);
		glVertex2f(XWindowPos, YWindowPos);
		glVertex2f(XWindowPos + Width, YWindowPos);
		if (RGBAGradBackground)GLCOLOR(RGBAGradBackground);
		glVertex2f(XWindowPos + Width, YWindowPos - Height);
		glVertex2f(XWindowPos, YWindowPos - Height);
		glEnd();
		GLCOLOR(RGBAThemeColor);
		glLineWidth(1);
		glBegin(GL_LINE_LOOP);
		glVertex2f(XWindowPos, YWindowPos);
		glVertex2f(XWindowPos + Width, YWindowPos);
		glVertex2f(XWindowPos + Width, YWindowPos - Height);
		glVertex2f(XWindowPos, YWindowPos - Height);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2f(XWindowPos, YWindowPos);
		glVertex2f(XWindowPos + Width, YWindowPos);
		glVertex2f(XWindowPos + Width, YWindowPos - WindowHeapSize);
		glVertex2f(XWindowPos, YWindowPos - WindowHeapSize);
		glColor4ub(255, 32 + 32 * HoveredCloseButton, 32 + 32 * HoveredCloseButton, 255);
		glVertex2f(XWindowPos + Width, YWindowPos);
		glVertex2f(XWindowPos + Width, YWindowPos + 1 - WindowHeapSize);
		glVertex2f(XWindowPos + Width - WindowHeapSize, YWindowPos + 1 - WindowHeapSize);
		glVertex2f(XWindowPos + Width - WindowHeapSize, YWindowPos);
		glEnd();

		if (WindowName)WindowName->Draw();

		for (auto Y = WindowActivities.begin(); Y != WindowActivities.end(); Y++)
			Y->second->Draw();
		Lock.unlock();
	}
	void _NotSafeResize(float NewHeight, float NewWidth) {
		Lock.lock();
		this->Height = NewHeight;
		this->Width = NewWidth;
		Lock.unlock();
	}
	void _NotSafeResize_Centered(float NewHeight, float NewWidth) {
		Lock.lock();
		float dx, dy;
		XWindowPos += (dx = -0.5f * (NewWidth - Width));
		YWindowPos += (dy = 0.5f * (NewHeight - Height));
		WindowName->SafeMove(dx, dy);
		Width = NewWidth;
		Height = NewHeight;
		Lock.unlock();
	}
	void SafeStringReplace(string NewWindowTitle) override {
		Lock.lock();
		SafeWindowRename(NewWindowTitle);
		Lock.unlock();
	}
	void SafeWindowRename(string NewWindowTitle) {
		Lock.lock();
		if (WindowName) {
			WindowName->SafeStringReplace(NewWindowTitle);
			WindowName->SafeChangePosition_Argumented(GLOBAL_LEFT, XWindowPos + WindowHeapSize * 0.5f, WindowName->CYpos);
		}
		Lock.unlock();
	}
	HandleableUIPart*& operator[](string ID) {
		return WindowActivities[ID];
	}
	DWORD TellType() {
		return TT_MOVEABLE_WINDOW;
	}
};


SingleTextLineSettings
* _STLS_WhiteSmall = new SingleTextLineSettings("_", 0, 0, 5, 0xFFFFFFFF),
* _STLS_BlackSmall = new SingleTextLineSettings("_", 0, 0, 5, 0x000000FF),

* System_Black = (is_fonted) ? new SingleTextLineSettings(10, 0x000000FF) : new SingleTextLineSettings("_", 0, 0, 5, 0x000000FF),
* System_White = (is_fonted) ? new SingleTextLineSettings(10, 0xFFFFFFFF) : new SingleTextLineSettings("_", 0, 0, 5, 0xFFFFFFFF);

struct WindowsHandler {
	map<string, MoveableWindow*> Map;
#define Map(WindowName,ElementName) (*Map[WindowName])[ElementName]
	list<map<string, MoveableWindow*>::iterator> ActiveWindows;
	string MainWindow_ID, MW_ID_Holder;
	BIT InterfaceIsActive, WindowWasDisabledDuringMouseHandling;
	WindowsHandler() {
		MW_ID_Holder = "";
		MainWindow_ID = "MAIN";
		InterfaceIsActive = 1;
		WindowWasDisabledDuringMouseHandling = 0;
		MoveableWindow* ptr;
		Map["ALERT"] = ptr = new MoveableWindow("Alert window", System_White, -100, 25, 200, 50, 0xFFFFFFAF, 0x3F3F3F7F);
		(*ptr)["AlertText"] = new TextBox("_", System_Black, 17.5, -7.5, 37, 160, 7.5, 0, 0, 0, _Align::left, TextBox::VerticalOverflow::recalibrate);
		(*ptr)["AlertSign"] = new SpecialSignHandler(SpecialSigns::DrawACircle, -80, -12.5, 7.5, 0x000000FF, 0x001FFFFF);

		Map["PROMPT"] = ptr = new MoveableWindow("prompt", System_White, -50, 50, 100, 100, 0x3F3F3FCF, 0x7F7F7F7F);
		(*ptr)["FLD"] = new InputField("", 0, 35 - WindowHeapSize, 10, 80, System_White, NULL, 0x007FFFFF, NULL, "", 0, _Align::center);
		(*ptr)["TXT"] = new TextBox("_abc_", System_White, 0, 7.5 - WindowHeapSize, 10, 80, 7.5, 0, 0, 2, _Align::center, TextBox::VerticalOverflow::recalibrate);
		(*ptr)["BUTT"] = new Button("Submit", System_White, NULL, -0, -20 - WindowHeapSize, 80, 10, 1, 0x007FFF3F, 0x007FFFFF, 0xFF7F00FF, 0xFFFFFFFF, 0xFF7F00FF, NULL, " ");
	}
	void MouseHandler(float mx, float my, CHAR Button, CHAR State) {
		if (!InterfaceIsActive)return;
		//printf("%X\n", Button);
		list<map<string, MoveableWindow*>::iterator>::iterator AWIterator = ActiveWindows.begin(), CurrentAW;
		CurrentAW = AWIterator;
		BIT flag = 0;
		if (!Button && !ActiveWindows.empty())(*ActiveWindows.begin())->second->MouseHandler(mx, my, 0, 0);
		else {
			while (AWIterator != ActiveWindows.end() && !((*AWIterator)->second->MouseHandler(mx, my, Button, State)) && !WindowWasDisabledDuringMouseHandling)
				AWIterator++;
			if (!WindowWasDisabledDuringMouseHandling && ActiveWindows.size() > 1 && AWIterator != ActiveWindows.end() && AWIterator != ActiveWindows.begin())
				if (CurrentAW == ActiveWindows.begin())EnableWindow(*AWIterator);
			if (WindowWasDisabledDuringMouseHandling)
				WindowWasDisabledDuringMouseHandling = 0;
		}
	}
	void ThrowPrompt(string StaticTipText, string WindowTitle, void(*OnSubmit)(), _Align STipAlign, InputField::Type InputType, string DefaultString = "", DWORD MaxChars = 0) {
		auto wptr = Map["PROMPT"];
		auto ifptr = ((InputField*)(*wptr)["FLD"]);
		auto tbptr = ((TextBox*)(*wptr)["TXT"]);
		wptr->SafeWindowRename(WindowTitle);
		ifptr->InputType = InputType;
		ifptr->MaxChars = MaxChars;
		ifptr->UpdateInputString(DefaultString);
		tbptr->TextAlign = STipAlign;
		tbptr->SafeStringReplace(StaticTipText);
		((Button*)(*wptr)["BUTT"])->OnClick = OnSubmit;

		wptr->SafeChangePosition(-50, 50);
		EnableWindow("PROMPT");
	}
	void ThrowAlert(string AlertText, string AlertHeader, void(*SpecialSignsDrawFunc)(float, float, float, DWORD, DWORD), BIT Update = false, DWORD FRGBA = 0, DWORD SRGBA = 0) {
		auto AlertWptr = Map["ALERT"];
		AlertWptr->SafeWindowRename(AlertHeader);
		AlertWptr->_NotSafeResize_Centered(50, 200);
		AlertWptr->SafeChangePosition_Argumented(0, 0, 0);
		TextBox* AlertWTptr = (TextBox*)((*AlertWptr)["AlertText"]);
		AlertWTptr->SafeStringReplace(AlertText);
		if (AlertWTptr->CalculatedTextHeight > AlertWTptr->Height) {
			AlertWptr->_NotSafeResize_Centered(AlertWTptr->CalculatedTextHeight + WindowHeapSize, AlertWptr->Width);
		}
		auto AlertWSptr = ((SpecialSignHandler*)(*AlertWptr)["AlertSign"]);
		AlertWSptr->_ReplaceVoidFunc(SpecialSignsDrawFunc);
		if (Update) {
			AlertWSptr->FRGBA = FRGBA;
			AlertWSptr->SRGBA = SRGBA;
		}
		EnableWindow("ALERT");
	}
	void DisableWindow(string ID) {
		auto Y = Map.find(ID);
		if (Y != Map.end()) {
			WindowWasDisabledDuringMouseHandling = 1;
			Y->second->Drawable = 1;
			ActiveWindows.remove(Y);
		}
	}
	void DisableAllWindows() {
		ActiveWindows.clear();
		EnableWindow(MainWindow_ID);
	}
	void TurnOnMainWindow() {
		if (this->MW_ID_Holder != "")
			swap(this->MainWindow_ID, this->MW_ID_Holder);
		this->EnableWindow(MainWindow_ID);
	}
	void TurnOffMainWindow() {
		if (this->MW_ID_Holder == "")
			swap(this->MainWindow_ID, this->MW_ID_Holder);
		this->DisableWindow(MainWindow_ID);
	}
	void DisableWindow(list<map<string, MoveableWindow*>::iterator>::iterator Window) {
		if (Window == ActiveWindows.end())return;
		WindowWasDisabledDuringMouseHandling = 1;
		(*Window)->second->Drawable = 1;
		ActiveWindows.erase(Window);
	}
	void EnableWindow(map<string, MoveableWindow*>::iterator Window) {
		if (Window == Map.end())return;
		for (auto Y = ActiveWindows.begin(), Q = ActiveWindows.begin(); Y != ActiveWindows.end(); Y++) {
			if (*Y == Window) {
				Window->second->Drawable = 1;
				if (Y != ActiveWindows.begin()) {
					Q = Y;
					Q--;
					ActiveWindows.erase(Y);
					Y = Q;
				}
				else {
					ActiveWindows.erase(Y);
					if (ActiveWindows.size())Y = ActiveWindows.begin();
					else break;
				}
			}
		}

		ActiveWindows.push_front(Window);
		//cout << Window->first << " " << ActiveWindows.front()->first << endl;
	}
	void EnableWindow(string ID) {
		this->EnableWindow(Map.find(ID));
	}
	void KeyboardHandler(char CH) {
		if (!InterfaceIsActive)return;
		if (ActiveWindows.size())
			(*(ActiveWindows.begin()))->second->KeyboardHandler(CH);
	}
	void Draw() {
		BIT MetMain = 0;
		if (!InterfaceIsActive)return;
		if (!ActiveWindows.empty()) {//if only reverse iterators could be easily converted to usual iterators...
			auto Y = (++ActiveWindows.rbegin()).base();

			while (true) {
				//cout << ((*Y)->first) << endl;
				if (!((*Y)->second->Drawable)) {
					if ((*Y)->first != MainWindow_ID)
						if (Y == ActiveWindows.begin()) {
							DisableWindow(Y);
							break;
						}
						else DisableWindow(Y);
					else (*Y)->second->Drawable = true;
					continue;
				}
				(*Y)->second->Draw();
				if ((*Y)->first == MainWindow_ID)MetMain = 1;
				if (Y == ActiveWindows.begin())break;
				Y--;
			}
		}
		//cout << endl;
		if (!MetMain)this->EnableWindow(MainWindow_ID);
	}
	inline MoveableWindow*& operator[](string ID) {
		return (this->Map[ID]);
	}
};
WindowsHandler* WH;

//////////////////////////////
////TRUE USAGE STARTS HERE////
//////////////////////////////

//#include "grav_eq_iterator.h"
#include "buddhabrot.h"

struct FieldAdapter : HandleableUIPart {
	dsfield *dsf;
	float x, y, side_size, brightness;
	float* pixel_size;
	int64_t hovered_x, hovered_y;
	FieldAdapter(dsfield *dsf,float x, float y,float side_size,float* pixel_size,float brightness) {
		this->dsf = dsf;
		this->x = x;
		this->y = y;
		this->side_size = side_size;
		this->pixel_size = pixel_size;
		this->brightness = brightness;
	}
	void Draw() override {
		bb::global_pause_lock.lock();
		draw_dsfield(*dsf, x, y, side_size*0.5, *pixel_size, brightness);
		bb::global_pause_lock.unlock();
	}
	void SafeMove(float dx, float dy) override {
		x += dx;
		y += dy;
	}
	void SafeChangePosition(float NewX, float NewY) override {
		x = NewX;
		y = NewY;
	}
	void SafeChangePosition_Argumented(BYTE Arg, float NewX, float NewY) override {

	}
	void KeyboardHandler(CHAR CH) override {
		return;
	}
	void SafeStringReplace(string Meaningless) override {
		return;
	}
	BIT MouseHandler(float mx, float my, CHAR Button, CHAR State) override {
		if (fabsf(mx - x) < 0.5*side_size && fabsf(my - y) < 0.5*side_size) {
			mx = mx - x + 0.5*side_size;
			my = my - y + 0.5*side_size;
			mx = mx / side_size * dsf->size();
			my = my / side_size * dsf->size();
			hovered_x = mx;
			hovered_y = my;
		}
		else {
			hovered_x = -1;
			hovered_y = -1;
		}
		return 0;
	}
};
float pix_size = 2 * RANGE / (min(WindX, WindY));
FieldAdapter *Field_Adapter_ptr = new FieldAdapter(nullptr, 0, 0, 400, &pix_size, 1);
TextBox *TB_ptr = new TextBox("", System_White, -260, -155 - WindowHeapSize, 10, 70, 10, 0, 0xFFFFFFFF, 1, _Align::center);
WheelVariableChanger* WVC_ptr = nullptr;

void OnWheel_BrightPress(double var) {
	Field_Adapter_ptr->brightness = var;
}
void OnWheel_ItersPress(double var) {
	bb::max_iters = var;
}
void OnWheel_AmountPress(double var) {
	bb::amount = var;
}
void OnWheel_PRPress(double var) {
	bb::progressrate = var;
}


void Pause() {
	bb::iter_pause ^= true;
	switch (bb::iter_pause)	{
		case true:
		bb::global_pause_lock.lock();
		break;
		case false:
		bb::global_pause_lock.unlock();
		break;
	}
}

ButtonSettings *BS_List_Black_Small = new ButtonSettings(System_White, 0, 0, 100, 10, 1, 0, 0, 0xFFEFDFFF, 0x00003F7F, 0x7F7F7FFF);

void Init() {
	SelectablePropertedList *L;
	auto T = new MoveableWindow("Field window", System_White, -325, 200 + WindowHeapSize, 525, 400 + WindowHeapSize, 0xFF, 0x7F7F7F7F);
	(*T)["WHEEL"] = WVC_ptr = new WheelVariableChanger(OnWheel_BrightPress, -260, 175 - WindowHeapSize, Field_Adapter_ptr->brightness, 2, System_White, "Brightness", "Delta", WheelVariableChanger::Type::exponential);
	(*T)["ITERS"] = new WheelVariableChanger(OnWheel_ItersPress, -260, 120 - WindowHeapSize, bb::max_iters, 10, System_White, "Max Iters", "Delta", WheelVariableChanger::Type::linear);
	(*T)["AMOUNT"] = new WheelVariableChanger(OnWheel_AmountPress, -260, 65 - WindowHeapSize, bb::amount, 1.5, System_White, "Amount", "Delta");
	(*T)["PRATE"] = new WheelVariableChanger(OnWheel_PRPress, -260, 10 - WindowHeapSize, bb::progressrate, 1, System_White, "PRate", "Delta", WheelVariableChanger::Type::linear);
	(*T)["FIELD"] = Field_Adapter_ptr;
	(*T)["TEXTBOX"] = TB_ptr;

	(*WH)["FWD"] = T;
	WH->MainWindow_ID = "FWD";
}

///////////////////////////////////////
/////////////END OF USE////////////////
///////////////////////////////////////

void onTimer(int v);
void mDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (FIRSTBOOT) {
		FIRSTBOOT = 0;

		bb::create_iter_threads();

		Field_Adapter_ptr->dsf = &bb::iter_counts;

		WH = new WindowsHandler();
		Init();
		
		ANIMATION_IS_ACTIVE = !ANIMATION_IS_ACTIVE;
		onTimer(0);
	}

	pix_size = 2 * RANGE / (min(WindX, WindY));
	TB_ptr->SafeStringReplace(to_string(Field_Adapter_ptr->dsf->at(Field_Adapter_ptr->hovered_x, Field_Adapter_ptr->hovered_y)));

	glTranslatef(centx, centy, 0);
	WH->Draw();
	glTranslatef(0 - centx, 0 - centy, 0);

	glutSwapBuffers();
}

void mInit() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D((0 - RANGE) * (WindX / WINDXSIZE), RANGE * (WindX / WINDXSIZE), (0 - RANGE) * (WindY / WINDYSIZE), RANGE * (WindY / WINDYSIZE));
}

void onTimer(int v) {
	glutTimerFunc(33, onTimer, 0);
	if (ANIMATION_IS_ACTIVE) {
		mDisplay();
		++TimerV;
	}
}

void OnResize(int x, int y) {
	WindX = x;
	WindY = y;
	mInit();
	glViewport(0, 0, x, y);
}
void inline absoluteToActualCoords(int ix, int iy, float& x, float& y) {
	float wx = WindX, wy = WindY, t;
	x = ((float)(ix - wx * 0.5)) / (0.5 * (wx / (RANGE * (WindX / WINDXSIZE))));
	y = ((float)(0 - iy + wy * 0.5)) / (0.5 * (wy / (RANGE * (WindY / WINDYSIZE))));
	t = x * cos(ROT_RAD) + y * sin(ROT_RAD) - centx;
	y = 0 - x * sin(ROT_RAD) + y * cos(ROT_RAD) - centy;
	x = t;
}
void mMotion(int ix, int iy) {
	float fx, fy;
	absoluteToActualCoords(ix, iy, fx, fy);
	MXPOS = fx;
	MYPOS = fy;
	if (WH)WH->MouseHandler(fx, fy, 0, 0);
}
void mKey(BYTE k, int x, int y) {
	if (WH)WH->KeyboardHandler(k);

	if (k == '=') { ANIMATION_IS_ACTIVE = !ANIMATION_IS_ACTIVE; }
	else if (k == 27)exit(1);
	else {
		switch (k) {
		case 'w':
			centy -= RANGE / 15;
			break;
		case 's':
			centy += RANGE / 15;
			break;
		case 'd':
			centx -= RANGE / 15;
			break;
		case 'a':
			centx += RANGE / 15;
			break;
		case 'n':
			if (WVC_ptr) {
				auto local_type = WVC_ptr->type;
				WVC_ptr->type = WheelVariableChanger::Type::exponential;
				WVC_ptr->Increment(-1);
				WVC_ptr->type = local_type;
				WVC_ptr->OnApply(WVC_ptr->variable);
			}
			break;
		case ' ':
			Pause();
			break;
		}//ForceUpdateValue
	}
}
void mDrag(int x, int y) {
	//mClick(88, MOUSE_DRAG_EVENT, x, y);
	mMotion(x, y);
}
void mClick(int butt, int state, int x, int y) {
	float fx, fy;
	CHAR Button, State = 0;
	absoluteToActualCoords(x, y, fx, fy);
	Button = butt - 1;
	if (state == GLUT_DOWN)State = -1;
	else if (state == GLUT_UP)State = 1;
	if (WH)WH->MouseHandler(fx, fy, Button, State);
}
void mSpecialKey(int Key, int x, int y) {
	//cout << "Spec: " << Key << endl;
	if (Key == GLUT_KEY_DOWN) {
		RANGE *= 1.1;
		OnResize(WindX, WindY);
	}
	else if (Key == GLUT_KEY_UP) {
		RANGE /= 1.1;
		OnResize(WindX, WindY);
	}
}
void mExit(int a) {

}

int main(int argc, char** argv) {

	if (1)
		ShowWindow(GetConsoleWindow(), SW_SHOW);
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
	InitASCIIMap();

	srand(TIMESEED());
	__glutInitWithExit(&argc, argv, mExit);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDXSIZE, WINDYSIZE);
	glutCreateWindow(WINDOWTITLE);

	//if (APRIL_FOOL || true)
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);//_MINUS_SRC_ALPHA
//else
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//_MINUS_SRC_ALPHA
	glEnable(GL_BLEND);
	//glEnable(GL_POLYGON_SMOOTH);//laggy af
	glEnable(GL_LINE_SMOOTH);//GL_POLYGON_SMOOTH
	glEnable(GL_POINT_SMOOTH);

	glShadeModel(GL_SMOOTH);

	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);//GL_FASTEST//GL_NICEST
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glutMouseFunc(mClick);
	glutReshapeFunc(OnResize);
	glutSpecialFunc(mSpecialKey);
	glutMotionFunc(mDrag);
	glutPassiveMotionFunc(mMotion);
	glutKeyboardFunc(mKey);
	glutDisplayFunc(mDisplay);
	mInit();
	glutMainLoop();
	return 0;
}