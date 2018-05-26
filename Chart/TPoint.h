#pragma once
#include "TRoot.h"
#include <iostream>
#include <fstream>

class TPoint :	public TRoot
{
protected:
	int x, y;

	void SetX(int _x);
	void SetY(int _y);

public:
	TPoint(int _x = 0, int _y = 0);
	~TPoint();

	virtual void Show(Graphics^ gr);
	virtual void Hide(Graphics^ gr);
	virtual void Move(Graphics^ gr, int dx, int dy);

	int GetX();
	int GetY();

	void ReadFromFile(std::ifstream&);
	void SaveToFile(std::ofstream&);

	void ReadFromString(std::string&);
};

