#pragma once
#include "TRoot.h"
#include "stack.h"
#include "TCurrLine.h"

class TChart : public TRoot
{
protected:
	TRoot *pBegin, *pEnd;
	TRoot *pNull;
	TRoot **ptpNull;
	TChart * pRes;
	bool first;
	Stack<TCurrLine> stack;

public:
	TChart(TRoot *pB = NULL, TRoot *pE = NULL);
	~TChart() {};

	void SetBegin(TRoot *pB);
	void SetEnd(TRoot *pE);
	TRoot* GetBegin();
	TRoot* GetEnd();

	virtual void Show(Graphics^ gr);
	virtual void Hide(Graphics^ gr);
	virtual void Move(Graphics^ gr, int dx, int dy);

	void Draw(Graphics^ gr, Pen^ pen);

	TRoot* Draw(Graphics^ gr, TRoot *curr, Pen^ pen);
	TRoot* Move(Graphics^ gr, TRoot *curr, int dx ,int dy);

	bool FindLine(int tx, int ty);

	bool Find(int tx, int ty);

	TChart* GetRes();
	void SetRes(TChart* res);

	bool GetFirst();

	bool Delete();
	
	TRoot** GetPtpNull();
	void setPtpNull(TRoot** _ptpNull);

	TRoot* GetPNull();
	void setPNull(TRoot* _pNull);

	TRoot** GetBeginPointerAddr();
	TRoot** GetEndPointerAddr();

};

