#include "stdafx.h"
#include "TChart.h"
#include "TPoint.h"

#include "TCurrLine.h"


TChart::TChart(TRoot *pB, TRoot *pE) {
	pBegin = pB;
	pEnd = pE;
	pNull = new TPoint(0, 0);
}

void TChart::SetBegin(TRoot *pB) {
	TPoint *tp = dynamic_cast<TPoint*>(pB);
	TChart *tc = dynamic_cast<TChart*>(pB);

	if ((tc != NULL) || (tp != NULL)) {
		pBegin = pB;
	}
}

void TChart::SetEnd(TRoot *pE) {
	TPoint *tp = dynamic_cast<TPoint*>(pE);
	TChart *tc = dynamic_cast<TChart*>(pE);

	if ((tc != NULL) || (tp != NULL)) {
		pEnd = pE;
	}
}

TRoot* TChart::GetBegin() {
	return pBegin;
}

TRoot* TChart::GetEnd() {
	return pEnd;
}

TRoot* TChart::Draw(Graphics^ gr, TRoot *curr, Pen^ pen) {
	TPoint *tp;
	TChart *tc;

	visible = true;

	tp = dynamic_cast<TPoint*>(curr);
	if (tp != NULL) {
		tp->Show(gr);
		return tp;
	}
	else {
		tc = dynamic_cast<TChart*>(curr);
		if (tc != NULL) {
			TPoint* bp = dynamic_cast<TPoint*>(Draw(gr, tc->GetBegin(), pen));
			TPoint* ep = dynamic_cast<TPoint*>(Draw(gr, tc->GetEnd(), pen));

			if((bp != NULL) && (ep != NULL))
				gr->DrawLine(pen, bp->GetX(), bp->GetY(), ep->GetX(), ep->GetY());

			return ep;
		}

		return tc;
	}

	return tp;
}

void TChart::Draw(Graphics^ gr, Pen^ pen) {
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
			if (curr.pE != pNull) {
				Pen^ tmpPen = pen;

				if (curr.tC->active == true) {
					pen = gcnew Pen(Brushes::Red, 3.0f);
				}
				gr->DrawLine(pen,
					Point(curr.pB->GetX(), curr.pB->GetY()),
					Point(curr.pE->GetX(), curr.pE->GetY())
				);

				pen = tmpPen;
			}

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

void TChart::Show(Graphics ^gr) {
	Draw(gr, Pens::Black);
	visible = true;
}

void TChart::Hide(Graphics^ gr) {
	Pen ^pen = gcnew Pen(Color::White, 3.0f);
	Draw(gr, pen);
	visible = false;
}

TRoot* TChart::Move(Graphics^ gr, TRoot* curr, int dx, int dy) {
	TPoint *tp;
	TChart *tc;

	tp = dynamic_cast<TPoint*>(curr);
	if (tp != NULL) {
		tp->Move(gr, dx, dy);
		return tp;
	}
	else {
		tc = dynamic_cast<TChart*>(curr);
		if (tc != NULL) {
			TPoint* bp = dynamic_cast<TPoint*>(Move(gr, tc->GetBegin(), dx, dy));
			TPoint* ep = dynamic_cast<TPoint*>(Move(gr, tc->GetEnd(), dx, dy));

			return ep;
		}
		return tc;
	}
	return tp;
}

void TChart::Move(Graphics^ gr, int dx, int dy) {
	Hide(gr);
	Move(gr, this, dx, dy);
	Show(gr);
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
			if ((abs(curr.pB->GetX() - tx) < 10) && (abs(curr.pB->GetY() - ty) < 10)) {
				pRes = curr.tC;
				first = true;
				return true;
			}

			if ((abs(curr.pE->GetX() - tx) < 10) && (abs(curr.pE->GetY() - ty) < 10)) {
				pRes = curr.tC;
				first = false;
				return true;
			}

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

	return false;
}



bool TChart::FindLine(int x0, int y0) {
	TCurrLine curr;
	TPoint *tmp;
	bool isFounded = false;

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
			int y2 = curr.pE->GetY();
			int x2 = curr.pE->GetX();

			int y1 = curr.pB->GetY();
			int x1 = curr.pB->GetX();

			double distance = abs((y2 - y1) * x0 - (x2 - x1) * y0 + x2 * y1 - y2 * x1) / sqrt(pow((y2 - y1), 2) + pow((x2 - x1), 2));

			if (distance < 5.0) {
				if (!isFounded) {
					pRes = curr.tC;
					if (pRes->active == true) pRes->active = false;
					else pRes->active = true;
					isFounded = true;
				}
			}
			else {
				curr.tC->active = false;
			}

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

	if (isFounded)
		return true;
	else
		return false;
}

bool TChart::GetFirst() {
	return first;
}

TChart* TChart::GetRes() {
	return pRes;
}

void TChart::SetRes(TChart* res) {
	pRes = res;
}

bool TChart::Delete() {
	if (pRes == NULL) return false;
	TCurrLine curr;
	TPoint *tmp;
	TChart *prev;

	TChart *foundedLine = pRes;

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

		if (curr.tC->GetBegin() == pRes){
			curr.tC->SetBegin(pRes->GetEnd());
			if (pRes->GetBegin()) {
				//TRoot* newNull = new TPoint(0, 0);
				/*TPoint* linkedVertex = NULL;
				TChart* tmp = pRes;

				while (tmp->GetEnd()) {
					linkedVertex = dynamic_cast<TPoint*>(tmp->GetEnd());

					if (linkedVertex == NULL) {
						tmp = dynamic_cast<TChart* >(tmp->GetEnd());
					}
					else break;
				}*/

				if (dynamic_cast<TPoint*>(pRes->GetBegin()) == NULL) {
					*ptpNull = new TChart(pRes->GetBegin(), pNull);
					//(dynamic_cast<TChart*>(*ptpNull))->SetEnd(pRes->GetEnd());
					//pNull = newNull;

					//TRoot* newPtpNull = (dynamic_cast<TChart*>(*ptpNull))->GetBegin();
					setPtpNull((dynamic_cast<TChart*>(*ptpNull))->GetEndPointerAddr());
				}
				return true;
			}
		}else if (curr.tC->GetEnd() == pRes) {
			curr.tC->SetEnd(pRes->GetEnd());
			if (pRes->GetBegin()){
				//TRoot* newNull = new TPoint(0, 0);
				/*TPoint* linkedVertex = NULL;
				TChart* tmp = pRes;

				while (tmp->GetEnd()) {
				linkedVertex = dynamic_cast<TPoint*>(tmp->GetEnd());

				if (linkedVertex == NULL) {
				tmp = dynamic_cast<TChart* >(tmp->GetEnd());
				}
				else break;
				}*/

				if (dynamic_cast<TPoint*>(pRes->GetBegin()) == NULL) {
					*ptpNull = new TChart(pRes->GetBegin(), pNull);
					//(dynamic_cast<TChart*>(*ptpNull))->SetEnd(pRes->GetEnd());
					//pNull = newNull;

					//TRoot* newPtpNull = (dynamic_cast<TChart*>(*ptpNull))->GetBegin();
					setPtpNull((dynamic_cast<TChart*>(*ptpNull))->GetEndPointerAddr());
				}

				return true;
			}
		}

		if ((curr.pB != NULL) && (curr.pE != NULL)) {
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

	return false;
}

TRoot** TChart::GetPtpNull() {
	return ptpNull;
}

void TChart::setPtpNull(TRoot** _ptpNull) {
	ptpNull = _ptpNull;
}

TRoot* TChart::GetPNull() {
	return pNull;
}

void TChart::setPNull(TRoot* _pNull) {
	pNull = _pNull;
}

TRoot** TChart::GetBeginPointerAddr() {
	return &pBegin;
}

TRoot** TChart::GetEndPointerAddr() {
	return &pEnd;
}


