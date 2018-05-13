#include "stdafx.h"
#include "TPoint.h"


TPoint::TPoint(int _x = 0, int _y = 0){
	x = _x;
	y = _y;
}


TPoint::~TPoint()
{
}

void TPoint::Show(Graphics^ gr) {
	gr->DrawEllipse(Pens::Black, x - 2, y - 2, x + 2, y + 2);
	visible = true;
}

void TPoint::Hide(Graphics^ gr) {
	gr->DrawEllipse(Pens::White, x - 2, y - 2, x + 2, y + 2);
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


