using namespace System::Drawing;

#pragma once
class TRoot
{
protected: 
	bool visible, active;
public:
	TRoot() {
		visible = false;
		active = false;
	}
	~TRoot() {}

	virtual void Show(Graphics^ gr) = 0;
	virtual void Hide(Graphics^ gr) = 0;
	virtual void Move(Graphics^ gr, int dx, int dy) = 0;
	
	bool GetActive(Graphics^ gr) {
		return active;
	}

	bool GetVisible(Graphics^ gr) {
		return visible;
	}
};

