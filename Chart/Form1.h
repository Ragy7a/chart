#pragma once
#include "TChart.h"
#include "TPoint.h"

namespace CppCLR_WinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	protected:
		Graphics ^gr;
		TChart *pFirst;
		TPoint *p1;
		TPoint *p2;
		int x1, x2, y1, y2;
	private: System::Windows::Forms::ListBox^  listBox;
	private: System::Windows::Forms::Button^  bShow;
	private: System::Windows::Forms::Button^  bHide;
	private: System::Windows::Forms::Button^  bDelete;
	private: System::Windows::Forms::Button^  bMove;
	protected:
		bool flag;
		bool isMove;

		int lastX, lastY;

	public:
		Form1(void)
		{
			InitializeComponent();
			gr = pictureBox->CreateGraphics();
			pFirst = NULL;
			flag = false;
			isMove = false;
			lastX = -1;
			lastY = -1;
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox;
	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->listBox = (gcnew System::Windows::Forms::ListBox());
			this->bShow = (gcnew System::Windows::Forms::Button());
			this->bHide = (gcnew System::Windows::Forms::Button());
			this->bDelete = (gcnew System::Windows::Forms::Button());
			this->bMove = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox
			// 
			this->pictureBox->BackColor = System::Drawing::Color::White;
			this->pictureBox->Location = System::Drawing::Point(12, 21);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(511, 329);
			this->pictureBox->TabIndex = 0;
			this->pictureBox->TabStop = false;
			this->pictureBox->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox_MouseDown);
			this->pictureBox->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox_MouseMove);
			this->pictureBox->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox_MouseUp);
			// 
			// listBox
			// 
			this->listBox->FormattingEnabled = true;
			this->listBox->Location = System::Drawing::Point(530, 21);
			this->listBox->Name = L"listBox";
			this->listBox->Size = System::Drawing::Size(159, 95);
			this->listBox->TabIndex = 1;
			// 
			// bShow
			// 
			this->bShow->Location = System::Drawing::Point(530, 123);
			this->bShow->Name = L"bShow";
			this->bShow->Size = System::Drawing::Size(75, 23);
			this->bShow->TabIndex = 2;
			this->bShow->Text = L"Show";
			this->bShow->UseVisualStyleBackColor = true;
			this->bShow->Click += gcnew System::EventHandler(this, &Form1::bShow_Click);
			// 
			// bHide
			// 
			this->bHide->Location = System::Drawing::Point(530, 152);
			this->bHide->Name = L"bHide";
			this->bHide->Size = System::Drawing::Size(75, 23);
			this->bHide->TabIndex = 3;
			this->bHide->Text = L"Hide";
			this->bHide->UseVisualStyleBackColor = true;
			this->bHide->Click += gcnew System::EventHandler(this, &Form1::bHide_Click);
			// 
			// bDelete
			// 
			this->bDelete->Location = System::Drawing::Point(530, 182);
			this->bDelete->Name = L"bDelete";
			this->bDelete->Size = System::Drawing::Size(75, 23);
			this->bDelete->TabIndex = 4;
			this->bDelete->Text = L"Delete";
			this->bDelete->UseVisualStyleBackColor = true;
			this->bDelete->Click += gcnew System::EventHandler(this, &Form1::bDelete_Click);
			// 
			// bMove
			// 
			this->bMove->Location = System::Drawing::Point(530, 212);
			this->bMove->Name = L"bMove";
			this->bMove->Size = System::Drawing::Size(75, 23);
			this->bMove->TabIndex = 5;
			this->bMove->Text = L"Move";
			this->bMove->UseVisualStyleBackColor = true;
			this->bMove->Click += gcnew System::EventHandler(this, &Form1::bMove_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(701, 362);
			this->Controls->Add(this->bMove);
			this->Controls->Add(this->bDelete);
			this->Controls->Add(this->bHide);
			this->Controls->Add(this->bShow);
			this->Controls->Add(this->listBox);
			this->Controls->Add(this->pictureBox);
			this->Name = L"Form1";
			this->Text = L"Form1";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: void SelectLine(int x1, int y1) {
		pFirst->FindLine(x1, y1);
		pFirst->Hide(gr);
		pFirst->Show(gr);
	}

	private: System::Void pictureBox_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		x1 = x2 = e->X;
		y1 = y2 = e->Y;

		if (e->Button == System::Windows::Forms::MouseButtons::Right) {
			SelectLine(x1, y1);
		}
		else {
			flag = true;
		}
	}

	private: System::Void pictureBox_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (!isMove && flag) {
			gr->DrawLine(Pens::White, x1, y1, x2, y2);
			
			x2 = e->X;
			y2 = e->Y;

			gr->DrawLine(Pens::Black, x1, y1, x2, y2);
		}

		if (isMove && flag) {
			int dx, dy;
			int dlen;

			x2 = e->X;
			y2 = e->Y;

			if (lastX == -1) {
				lastX = x2 - 1;
				lastY = y2 - 1;
			}

			dx = x2 - lastX;
			dy = y2 - lastY;

			//dlen = Math::Sqrt(dy*dx + dy*dy);

			//dx /= dlen;
			//dy /= dlen;

			gr->Clear(Color::White);
			pFirst->Move(gr, dx, dy);
			
			lastX = x2;
			lastY = y2;

			_sleep(50);
		}
	}
	private: System::Void pictureBox_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		TChart *tmp = new TChart();
		TChart *tmpRes = NULL;

		/*TChart *p1Res, *p2Res;
		bool p1First, p2First;
		bool p1Founded, p2Founded;

		p1Founded = pFirst->Find(x1, y1);
		p1Res = pFirst->GetRes();
		p1First = pFirst->GetFirst();

		p2Founded = pFirst->Find(x2, y2);
		p2Res = pFirst->GetRes();
		p2First = pFirst->GetFirst();*/

		if (flag && !isMove) {
			listBox->Items->Add(String::Format("({0},{1}); ({2},{3})", x1, y1, x2, y2));

			if (pFirst == NULL) {
				TChart* tmp;
				TRoot* pNull;

				p1 = new TPoint(x1, y1);
				p2 = new TPoint(x2, y2);

				tmp = new TChart(p2, p1);

				pFirst = new TChart();
				pNull = pFirst->GetPNull();
				pFirst->SetBegin(tmp);
				pFirst->SetEnd(pNull);

				pFirst->setPtpNull(pFirst->GetEndPointerAddr());
				//pFirst->Show(gr);
			}
			else {
				if (pFirst->Find(x1, y1)) {
					p2 = new TPoint(x2, y2);

					if (pFirst->GetFirst()) {
						p1 = dynamic_cast<TPoint*>(pFirst->GetRes()->GetBegin());
					}
					else {
						p1 = dynamic_cast<TPoint*>(pFirst->GetRes()->GetEnd());
					}
					tmp->SetBegin(p2);
					tmp->SetEnd(p1);

					tmpRes = pFirst->GetRes();

					if (pFirst->GetFirst()) {
						tmpRes->SetBegin(tmp);
					}
					else {
						tmpRes->SetEnd(tmp);
					}
				}
				else {
					if (pFirst->Find(x2, y2)) {

						if (pFirst->GetFirst()) {
							p2 = dynamic_cast<TPoint*>(pFirst->GetRes()->GetBegin());
						}
						else {
							p2 = dynamic_cast<TPoint*>(pFirst->GetRes()->GetEnd());
						}
						if (tmpRes != NULL) {
							tmp->SetBegin(p2);
							tmp->SetEnd(p1);
						}
						else {
							TChart *tmpP2 = new TChart();

							p1 = new TPoint(x1, y1);

							tmp->SetBegin(p2);
							tmp->SetEnd(p1);
						}

						tmpRes = pFirst->GetRes();

						if (pFirst->GetFirst()) {
							tmpRes->SetBegin(tmp);
						}
						else {
							tmpRes->SetEnd(tmp);
						}
					}
					else {
						TPoint *firstVertex = new TPoint(x1, y1);
						TPoint *secondVertex = new TPoint(x2, y2);

						TChart *edgeChart = new TChart(secondVertex, firstVertex);
						TChart *nullChart = new TChart(edgeChart, pFirst->GetPNull());

						TRoot** ptpNull = pFirst->GetPtpNull();
						(*ptpNull) = nullChart;

						TRoot** tmp = nullChart->GetEndPointerAddr();
						pFirst->setPtpNull(tmp);
					}
				}
			}
			pFirst->Hide(gr);
			pFirst->Show(gr);
		}
		flag = false;
	}
private: System::Void bShow_Click(System::Object^  sender, System::EventArgs^  e) {
	if (!pFirst->GetVisible()) {
		pFirst->Show(gr);
	}
}

private: System::Void bHide_Click(System::Object^  sender, System::EventArgs^  e) {
	if (pFirst->GetVisible()) { 
		pFirst->Hide(gr);
		gr->FillRectangle(Brushes::White, 0, 0, pictureBox->Width, pictureBox->Height);
	}
}

private: System::Void bDelete_Click(System::Object^  sender, System::EventArgs^  e) {
	if (pFirst->GetRes() != NULL) {
		pFirst->Delete();
		pFirst->Hide(gr);
		gr->Clear(Color::White);
		pFirst->Show(gr);
	}
}
private: System::Void bMove_Click(System::Object^  sender, System::EventArgs^  e) {
	if (isMove) {
		isMove = false;
		this->Cursor = Cursors::Default;
	}
	else {
		isMove = true;
		this->Cursor = Cursors::SizeAll;

		lastX = -1;
		lastY = -1;
	}
}
};
}
