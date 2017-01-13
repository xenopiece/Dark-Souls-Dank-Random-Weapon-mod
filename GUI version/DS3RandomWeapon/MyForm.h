#pragma once
#include "SomeHeader.h"

namespace DS3RandomWeapon {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected:
	private: System::Windows::Forms::CheckedListBox^  checkedListBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->checkedListBox1 = (gcnew System::Windows::Forms::CheckedListBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(249, 38);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(182, 428);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Begin";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// checkedListBox1
			// 
			this->checkedListBox1->FormattingEnabled = true;
			this->checkedListBox1->Items->AddRange(gcnew cli::array< System::Object^  >(20) {
				L"Standard weapons (daggers, swords, etc.)",
					L"Bows", L"Whips", L"Shields", L"SECRET", L"Heavy infusions", L"Sharp infusions", L"Refined infusions", L"Simple infusions",
					L"Crystal infusions", L"Fire infusions", L"Chaos infusions", L"Lightning infusions", L"Deep infusions", L"Dark infusions", L"Poison infusions",
					L"Blood infusions", L"Raw infusions", L"Blessed infusions", L"Hollow infusions"
			});
			this->checkedListBox1->Location = System::Drawing::Point(12, 12);
			this->checkedListBox1->Name = L"checkedListBox1";
			this->checkedListBox1->Size = System::Drawing::Size(231, 454);
			this->checkedListBox1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(307, 12);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(124, 23);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Timer (seconds)";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(249, 12);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(56, 20);
			this->textBox1->TabIndex = 4;
			this->textBox1->KeyPress += gcnew KeyPressEventHandler(this, &MyForm::textBox1_KeyPress);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(443, 478);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->checkedListBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"DS3 Random Weapon mod";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs ^e) {
		e->Handled = (!isdigit(e->KeyChar)) && (e->KeyChar != '.') && (e->KeyChar != (Char)Keys::Delete && e->KeyChar != (Char)Keys::Back);
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		int timer = stoi(msclr::interop::marshal_as<std::string>(this->textBox1->Text));
		std::vector<std::string> bank;

		for (int i = 0; i < this->checkedListBox1->CheckedItems->Count; i++)
		{
			std::string selection = msclr::interop::marshal_as<std::string>(this->checkedListBox1->CheckedItems[i]->ToString());
			bank.push_back(selection);
		}

		somefunction(timer, bank);
	}
	};
}
