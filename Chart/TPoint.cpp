#include "stdafx.h"
#include "TPoint.h"
#include <regex>

TPoint::TPoint(int _x, int _y){
	x = _x;
	y = _y;
}


TPoint::~TPoint()
{
}

void TPoint::Show(Graphics^ gr) {
	gr->FillEllipse(Brushes::Black, x - 2, y - 2, 2, 2);
	visible = true;
}

void TPoint::Hide(Graphics^ gr) {
	gr->FillEllipse(Brushes::White, x - 2, y - 2, 2, 2);
	visible = true;
}

void TPoint::Move(Graphics^ gr, int dx, int dy) {
	Hide(gr);
	x += dx;
	y += dy;
	Show(gr);
}

int TPoint::GetX() {
	return x;
}

int TPoint::GetY() {
	return y;
}

void TPoint::SetX(int _x) {
	x = _x;
}

void TPoint::SetY(int _y) {
	y = _y;
}

void TPoint::ReadFromFile(std::ifstream& ifs) {
	std::smatch match;
	std::string thisLine;
	std::regex reg("(\\d+)");
	
	ifs >> thisLine;
	if (std::regex_search(thisLine, match, reg))
	{
		x = std::stoi(match.str());
		thisLine = match.suffix().str();
	}
	if (std::regex_search(thisLine, match, reg)) {
		y = std::stoi(match.str());
	}
}

void TPoint::SaveToFile(std::ofstream& ofs) {
	ofs << "(" << x << "," << y << ")";
}

void TPoint::ReadFromString(std::string& thisLine) {
	std::smatch match;
	std::regex reg("(\\d+)");
	std::string tmp = thisLine;

	if (std::regex_search(tmp, match, reg))
	{
		x = std::stoi(match.str());
		tmp = match.suffix().str();
	}
	if (std::regex_search(tmp, match, reg)) {
		y = std::stoi(match.str());
	}
}




