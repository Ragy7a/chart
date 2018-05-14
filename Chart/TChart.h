#pragma once
#include "TRoot.h"
#include "stack.h"
#include "TCurrLine.h"

class TChart : public TRoot
{
protected:
	TRoot *pBegin, *pEnd;
	TChart * pRes;
	bool first;
	Stack<TCurrLine> stack;

	void Draw(Graphics^ gr, Pen^ pen);

public:
	TChart(TRoot *pB = NULL, TRoot *pE = NULL);
	~TChart();

	void SetBegin(TRoot *pB);
	void SetEnd(TRoot *pE);
	TRoot* GetBegin();
	TRoot* GetEnd();

	virtual void Show(Graphics^ gr);
	virtual void Hide(Graphics^ gr);
	virtual void Move(Graphics^ gr, int dx, int dy);

	TRoot* Show(Graphics^ gr, TRoot *curr);
	TRoot* Move(Graphics^ gr, TRoot *curr, int dx ,int dy);

	bool Find(int tx, int ty);

	TChart* GetRes();
	void SetRes(TChart* res);

	bool GetFirst();
};

