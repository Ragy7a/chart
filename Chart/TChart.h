#pragma once
#include "TRoot.h"
#include "stack.h"

class TChart : public TRoot
{
protected:
	TRoot *pBegin, *pEnd;
	TChart * pRes;
	bool first;
	stack<TCurrLine> stack;

public:
	TChart(TRoot *pB, TRoot *pE);
	~TChart();

	void SetBegin(TRoot *pB);
	void SetEnd(TRoot *pE);
	TRoot* GetBegin();
	TRoot* GetEnd();

	virtual void Show(Graphics^ gr);
	virtual void Hide(Graphics^ gr);
	virtual void Move(Graphics^ gr);
	TRoot* Show(Graphics^ gr, TRoot *curr);
	bool Find(int tx, int ty);

	bool GetFirst();
};

