#include "stdafx.h"
#include "TChart.h"
#include "TPoint.h"

#include "TCurrLine.h"


TChart::TChart(TRoot *pB = NULL, TRoot *pE = NULL) {
	pBegin = pB;
	pEnd = pE;
}

void TChart::SetBegin(TRoot *pB) {
	TPoint *tp = dynamic_cast<TPoint*>(pB);
	TChart *tc = dynamic_cast<TChart*>(pB);

	if ((tc != NULL) || (tp != NULL)) 
		pBegin = pB;
}

void TChart::SetEnd(TRoot *pE) {
	TPoint *tp = dynamic_cast<TPoint*>(pE);
	TChart *tc = dynamic_cast<TChart*>(pE);

	if ((tc != NULL) || (tp != NULL))
		pEnd = pE;
}

TRoot* TChart::GetBegin() {
	return pBegin;
}

TRoot* TChart::GetEnd() {
	return pEnd;
}

TRoot* TChart::Show(Graphics^ gr, TRoot *curr) {
	TPoint *tp;
	TChart *tc;

	tp = dynamic_cast<TPoint*>(curr);
	if (tp != NULL) {
		tp->Show(gr);
		return tp;
	}
	else {
		tc = dynamic_cast<TChart*>(curr);
		if (tc != NULL) {
			TPoint* bp = dynamic_cast<TPoint*>(Show(gr, tc->GetBegin()));
			TPoint* ep = dynamic_cast<TPoint*>(Show(gr, tc->GetEnd()));

			gr->DrawLine(Pens::Black, bp->GetX(), bp->GetY(), ep->GetX(), ep->GetY());

			return ep;
		}

		return tc;
	}

	return tp;
}

void TChart::Show(Graphics ^gr) {
	TCurrLine curr;
	TPoint *tmp;

	curr.tC = this;
	curr.pB = NULL;
	curr.pE = NULL;

	stack.clear();
	stack.push(curr);

	while (!stack.isEmpty()) {
		curr = stack.pop();
		while (curr.pB == NULL) {
			tmp = dynamic_cast<TPoint*>(curr.tC->GetBegin());
			if (tmp != NULL) {
				curr.pB = tmp;
			}
			else {
				stack.push(curr);
				curr.tC = curr.tC->GetBegin();
			}
			if (curr.pE == NULL) {
				tmp = dynamic_cast<TPoint*>(curr.tC->GetEnd());
				if (tmp != NULL) {
					curr.pE = tmp;
				}
				else {
					stack.push(curr);
					curr.tC = dynamic_cast<TChart*>(curr.tC->GetEnd());
					curr.pB = NULL;
					stack.push(curr);
				}
			}

			if ((curr.pB != NULL) && (curr.pE != NULL)) {
				gr->DrawLine(Pens::Black,
					Point(curr.pB->GetX(), curr.pB->GetY()),
					Point(curr.pE->GetX(), curr.pE->GetY())
				);
				tmp = curr.pE;
				if (!stack.isEmpty()) {
					curr = stack.pop();
					if (curr.pB == NULL) {
						curr.pB = tmp;
					}
					else {
						curr.pE = tmp;
					}
					stack.push(curr);
				}
			}
		}
	}
}

bool TChart::Find(int tx, int ty) {
	TCurrLine curr;
	TPoint *tmp;

	curr.tC = this;
	curr.pB = NULL;
	curr.pE = NULL;

	stack.clear();
	stack.push(curr);

	while (!stack.isEmpty()) {
		curr = stack.pop();
		while (curr.pB == NULL) {
			tmp = dynamic_cast<TPoint*>(curr.tC->GetBegin());
			if (tmp != NULL) {
				curr.pB = tmp;
			}
			else {
				stack.push(curr);
				curr.tC = dynamic_cast<TChart*>(curr.tC->GetBegin());
			}
			if (curr.pE == NULL) {
				tmp = dynamic_cast<TPoint*>(curr.tC->GetEnd());
				if (tmp != NULL) {
					curr.pE = tmp;
				}
				else {
					stack.push(curr);
					curr.tC = dynamic_cast<TChart*>(curr.tC->GetEnd());
					curr.pB = NULL;
					stack.push(curr);
				}
			}

			if ((curr.pB != NULL) && (curr.pE != NULL)) {
				if ((abs(curr.pB->GetX() - tx) < 20) && (abs(curr.pB->GetY() - ty) < 20)) {
					pRes = curr.tC;
					first = true;
					return true;
				}

				if ((abs(curr.pE->GetX() - tx) < 20) && (abs(curr.pE->GetY() - ty) < 20)) {
					pRes = curr.tC;
					first = false;
					return true;
				}
			}
		}
	}
}

bool TChart::GetFirst() {
	return first;
}


