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
		bool flag;

	public:
		Form1(void)
		{
			InitializeComponent();
			gr = pictureBox->CreateGraphics();
			pFirst = NULL;
			flag = false;
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
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(701, 362);
			this->Controls->Add(this->pictureBox);
			this->Name = L"Form1";
			this->Text = L"Form1";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void pictureBox_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		flag = true;
		x1 = x2 = e->x;
		y1 = y2 = e->y;
	}

	private: System::Void pictureBox_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (flag) {
			gr->DrawLine(Pens::White, x1, y1, x2, y2);

			x2 = e->x;
			y2 = e->y;
			
			gr->DrawLine(Pens::Black, x1, y1, x2, y2);
		}
	}
	private: System::Void pictureBox_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		TChart *tmp = new TChart();
		TChart *tmpRes = NULL;

		flag = false;
		if (pFirst == NULL) {
			p1 = new TPoint(x1, y1);
			p2 = new TPoint(x2, y2);

			pFirst = new TChart();
			pFirst->SetBegin(p1);
			pFirst->SetEnd(p2);
			pFirst->Show(gr);
		}
		else {
			if (pFirst->Find(x1, y1)) {
				p2 = new TPoint(x2, y2);

				if (pFirst->first) {
					p1 = pFirst->pRes->GetBegin();
				}
				else {
					p1 = pFirst->pRes->GetEnd();
				}
				tmp->SetBegin(p2);
				tmp->SetEnd(p1);

				tmpRes = pRes;

				if (pFirst->first) {
					pRes->SetBegin(tmp);
				}
				else {
					pRes->SetEnd(tmp);
				}
			}

			if (pFirst->Find(x2, y2)) {

				if (pFirst->first) {
					p2 = pFirst->pRes->GetBegin();
				}
				else {
					p2 = pFirst->pRes->GetEnd();
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

				if (pFirst->first) {
					pRes->SetBegin(tmp);
				}
				else {
					pRes->SetEnd(tmp);
				}
			}
		}
	}
	};
}
