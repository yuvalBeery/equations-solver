#pragma once
#include <iostream>
#include "functions.h"
const int X_APPART = 100;
const int Y_APPART = 50;
fraction matrix[MAX_ARRAY_LENGTH][MAX_ARRAY_LENGTH + 1];
std::string valueArray[MAX_ARRAY_LENGTH];
bool isSimulated = true;


namespace equationsSolver2 {

	using namespace std;
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

			createMatrix();
		};


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
	private: System::Windows::Forms::Label^ headerLable;
	private: System::Windows::Forms::TextBox^ valueTextBox;
	private: System::Windows::Forms::Button^ calcButton;
	private: System::Windows::Forms::Button^ resetButton;
	private: System::Windows::Forms::Button^ fractionState;
	private: System::Windows::Forms::ComboBox^ comboBox1;


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->headerLable = (gcnew System::Windows::Forms::Label());
			this->valueTextBox = (gcnew System::Windows::Forms::TextBox());
			this->calcButton = (gcnew System::Windows::Forms::Button());
			this->resetButton = (gcnew System::Windows::Forms::Button());
			this->fractionState = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->SuspendLayout();
			// 
			// headerLable
			// 
			this->headerLable->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->headerLable->Location = System::Drawing::Point(52, 63);
			this->headerLable->Name = L"headerLable";
			this->headerLable->Size = System::Drawing::Size(500, 69);
			this->headerLable->TabIndex = 1;
			this->headerLable->Text = L"equations solver";
			// 
			// valueTextBox
			// 
			this->valueTextBox->BackColor = System::Drawing::Color::DarkTurquoise;
			this->valueTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->valueTextBox->Location = System::Drawing::Point(64, 245);
			this->valueTextBox->Multiline = true;
			this->valueTextBox->Name = L"valueTextBox";
			this->valueTextBox->Size = System::Drawing::Size(1032, 67);
			this->valueTextBox->TabIndex = 61;
			// 
			// calcButton
			// 
			this->calcButton->BackColor = System::Drawing::Color::MediumSlateBlue;
			this->calcButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->calcButton->Location = System::Drawing::Point(64, 811);
			this->calcButton->Name = L"calcButton";
			this->calcButton->Size = System::Drawing::Size(210, 78);
			this->calcButton->TabIndex = 62;
			this->calcButton->Text = L"calculate";
			this->calcButton->UseVisualStyleBackColor = false;
			this->calcButton->Click += gcnew System::EventHandler(this, &MyForm::calcButton_Click);
			// 
			// resetButton
			// 
			this->resetButton->BackColor = System::Drawing::Color::MediumSlateBlue;
			this->resetButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->resetButton->Location = System::Drawing::Point(500, 811);
			this->resetButton->Name = L"resetButton";
			this->resetButton->Size = System::Drawing::Size(210, 78);
			this->resetButton->TabIndex = 63;
			this->resetButton->Text = L"reset";
			this->resetButton->UseVisualStyleBackColor = false;
			this->resetButton->Click += gcnew System::EventHandler(this, &MyForm::resetButton_Click);
			// 
			// fractionState
			// 
			this->fractionState->BackColor = System::Drawing::Color::MediumSlateBlue;
			this->fractionState->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->fractionState->Location = System::Drawing::Point(64, 170);
			this->fractionState->Name = L"fractionState";
			this->fractionState->Size = System::Drawing::Size(218, 66);
			this->fractionState->TabIndex = 64;
			this->fractionState->Text = L"b/c";
			this->fractionState->UseVisualStyleBackColor = false;
			this->fractionState->Click += gcnew System::EventHandler(this, &MyForm::fractionState_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(8) {
				L"2 x 2", L"3 x 3", L"4 x 4", L"5 x 5", L"6 x 6",
					L"7 x 7", L"8 x 8", L"9 x 9"
			});
			this->comboBox1->Location = System::Drawing::Point(950, 170);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(145, 44);
			this->comboBox1->TabIndex = 65;
			this->comboBox1->Text = L"3 x 3";
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox1_SelectedIndexChanged);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(16, 31);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::PaleGreen;
			this->ClientSize = System::Drawing::Size(1370, 1220);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->fractionState);
			this->Controls->Add(this->resetButton);
			this->Controls->Add(this->calcButton);
			this->Controls->Add(this->valueTextBox);
			this->Controls->Add(this->headerLable);
			this->Name = L"MyForm";
			this->Text = L"equations solver";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		cli::array<TextBox^, 2>^ textBoxsArray = gcnew cli::array<TextBox^, 2>(MAX_ARRAY_LENGTH, MAX_ARRAY_LENGTH + 1);
		cli::array<Label^, 2>^ signLabelsArray = gcnew cli::array<Label^, 2>(MAX_ARRAY_LENGTH, MAX_ARRAY_LENGTH + 1);
		cli::array<Label^, 2>^ xPlaseslabelsArray = gcnew cli::array<Label^, 2>(2, MAX_ARRAY_LENGTH + 1);
		
		void createMatrix()
		{
			for (int i = 0; i < currentArrayLength; i++)
			{
				for (int j = 0; j < currentArrayLength; j++)
				{
					textBoxsArray[i, j] = gcnew System::Windows::Forms::TextBox();
					textBoxsArray[i, j]->BackColor = System::Drawing::Color::DodgerBlue;
					textBoxsArray[i, j]->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
					textBoxsArray[i, j]->ForeColor = System::Drawing::Color::White;
					textBoxsArray[i, j]->Location = System::Drawing::Point(valueTextBox->Location.X + (X_APPART * j), 175 + (Y_APPART * i));
					textBoxsArray[i, j]->Name = L"x" + i + "" + j + "TextBox";
					textBoxsArray[i, j]->Size = System::Drawing::Size(65, 50);
					textBoxsArray[i, j]->TabIndex = 45;
					this->Controls->Add(textBoxsArray[i, j]);

					if (i == 0)
					{
						xPlaseslabelsArray[i, j] = gcnew System::Windows::Forms::Label();
						xPlaseslabelsArray[i, j]->BackColor = System::Drawing::Color::PaleGreen;
						xPlaseslabelsArray[i, j]->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
						xPlaseslabelsArray[i, j]->Location = System::Drawing::Point(35 + (X_APPART * j), 145 + (Y_APPART * i));
						xPlaseslabelsArray[i, j]->Size = System::Drawing::Size(50, 25);
						xPlaseslabelsArray[i, j]->TabIndex = 61;
						xPlaseslabelsArray[i, j]->Text = L"x" + "[" + (j + 1) + "]";
						this->Controls->Add(xPlaseslabelsArray[i, j]);
					}

					if (j != 0)
					{
						signLabelsArray[i, j] = gcnew System::Windows::Forms::Label();
						signLabelsArray[i, j]->BackColor = System::Drawing::Color::PaleGreen;
						signLabelsArray[i, j]->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
						signLabelsArray[i, j]->Location = System::Drawing::Point(-2 + (X_APPART * j), 175 + (Y_APPART * i));
						signLabelsArray[i, j]->Size = System::Drawing::Size(25, 25);
						signLabelsArray[i, j]->TabIndex = 61;
						signLabelsArray[i, j]->Text = L"+";
						this->Controls->Add(signLabelsArray[i, j]);
					}
				}

				textBoxsArray[i, currentArrayLength] = gcnew System::Windows::Forms::TextBox();
				textBoxsArray[i, currentArrayLength]->BackColor = System::Drawing::Color::DodgerBlue;
				textBoxsArray[i, currentArrayLength]->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				textBoxsArray[i, currentArrayLength]->ForeColor = System::Drawing::Color::White;
				textBoxsArray[i, currentArrayLength]->Location = System::Drawing::Point(42 + (X_APPART * currentArrayLength), 175 + (Y_APPART * i));
				textBoxsArray[i, currentArrayLength]->Name = L"x" + i + "" + currentArrayLength + "TextBox";
				textBoxsArray[i, currentArrayLength]->Size = System::Drawing::Size(60, 50);
				textBoxsArray[i, currentArrayLength]->TabIndex = 45;
				this->Controls->Add(textBoxsArray[i, currentArrayLength]);

				if (i == 0)
				{
					xPlaseslabelsArray[i, currentArrayLength] = gcnew System::Windows::Forms::Label();
					xPlaseslabelsArray[i, currentArrayLength]->BackColor = System::Drawing::Color::PaleGreen;
					xPlaseslabelsArray[i, currentArrayLength]->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
					xPlaseslabelsArray[i, currentArrayLength]->Location = System::Drawing::Point(62 + (X_APPART * currentArrayLength), 145 + (Y_APPART * i));
					xPlaseslabelsArray[i, currentArrayLength]->Size = System::Drawing::Size(50, 25);
					xPlaseslabelsArray[i, currentArrayLength]->TabIndex = 61;
					xPlaseslabelsArray[i, currentArrayLength]->Text = L"n";
					this->Controls->Add(xPlaseslabelsArray[i, currentArrayLength]);
				}

				xPlaseslabelsArray[1, i] = gcnew System::Windows::Forms::Label();
				xPlaseslabelsArray[1, i]->BackColor = System::Drawing::Color::PaleGreen;
				xPlaseslabelsArray[1, i]->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				xPlaseslabelsArray[1, i]->Location = System::Drawing::Point(2, 175 + (Y_APPART * i));
				xPlaseslabelsArray[1, i]->Size = System::Drawing::Size(25, 25);
				xPlaseslabelsArray[1, i]->TabIndex = 61;
				xPlaseslabelsArray[1, i]->Text = L"" + (i + 1) + "";
				this->Controls->Add(xPlaseslabelsArray[1, i]);

				signLabelsArray[i, currentArrayLength] = gcnew System::Windows::Forms::Label();
				signLabelsArray[i, currentArrayLength]->BackColor = System::Drawing::Color::PaleGreen;
				signLabelsArray[i, currentArrayLength]->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				signLabelsArray[i, currentArrayLength]->Location = System::Drawing::Point(8 + (X_APPART * currentArrayLength), 175 + (Y_APPART * i));
				signLabelsArray[i, currentArrayLength]->Size = System::Drawing::Size(25, 25);
				signLabelsArray[i, currentArrayLength]->TabIndex = 61;
				signLabelsArray[i, currentArrayLength]->Text = L"=";
				this->Controls->Add(signLabelsArray[i, currentArrayLength]);
			}

			this->valueTextBox->Size = System::Drawing::Size(textBoxsArray[currentArrayLength - 1, currentArrayLength]->Location.X + 37, 25);
			this->calcButton->Location = System::Drawing::Point(valueTextBox->Location.X, textBoxsArray[currentArrayLength - 1, currentArrayLength - 1]->Location.Y + 60);
			this->resetButton->Location = System::Drawing::Point(valueTextBox->Location.X + valueTextBox->Size.Width - resetButton->Size.Width, calcButton->Location.Y);
			this->comboBox1->Location = System::Drawing::Point(valueTextBox->Location.X + valueTextBox->Size.Width - comboBox1->Size.Width, 50);
			this->Size = System::Drawing::Size(valueTextBox->Location.X + valueTextBox->Size.Width + 50, calcButton->Location.Y + 100);
		}
		
		void cleanForm()
		{
			for (int i = 0; i < currentArrayLength; i++)
			{
				for (int j = 0; j < currentArrayLength + 1; j++)
				{
					delete textBoxsArray[i, j];
					delete signLabelsArray[i, j];
					if (i < 2)
						delete xPlaseslabelsArray[i, j];
				}
			}
		}

		
		
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		cleanForm();
		currentArrayLength = comboBox1->SelectedIndex + 2;
		valueTextBox->Text = L"";
		createMatrix();
	}
	private: System::Void resetButton_Click(System::Object^ sender, System::EventArgs^ e) {
		for (int i = 0; i < currentArrayLength; i++)
		{
			for (int j = 0; j < currentArrayLength + 1; j++)
				textBoxsArray[i, j]->Text = L"";
			valueArray[i] = "";
		}
		valueTextBox->Text = L"";

	}
	private: System::Void calcButton_Click(System::Object^ sender, System::EventArgs^ e) {

		valueTextBox->Text = "";
		std::string strxArray[MAX_ARRAY_LENGTH][MAX_ARRAY_LENGTH + 1];
		for (int i = 0; i < currentArrayLength; i++)
		{
			for (int j = 0; j < currentArrayLength + 1; j++)
			{
				MarshalString(textBoxsArray[i, j]->Text, strxArray[i][j]);
				if (strxArray[i][j] == "")
				{
					if (j < currentArrayLength)
					{
						valueTextBox->Text = L"x" + "[" + (j + 1) + "]" + (i + 1) + " is missing";
						return;
					}
					else
					{
						valueTextBox->Text = L"n" + "[" + (i + 1) + "] is missing";
						return;
					}
				}

				if (!isFractionValid(strxArray[i][j]))
				{
					if (j < currentArrayLength)
					{
						valueTextBox->Text = L"x" + "[" + (j + 1) + "]" + (i + 1) + " is invalid";
						return;
					}
					else
					{
						valueTextBox->Text = L"n" + "[" + (i + 1) + "] is invalid";
						return;
					}
				}
			}
		}

		for (int i = 0; i < currentArrayLength; i++)
		{
			for (int j = 0; j < currentArrayLength + 1; j++)
				matrix[i][j] = fraction(strxArray[i][j]);
		}

		solve(matrix);
		setValueArray(matrix, valueArray, isSimulated);

		for (int i = 0; i < currentArrayLength; i++)
		{
			if (valueArray[i] == "0/0")
				valueTextBox->Text += "x" + "[" + gcnew String(to_string(i + 1).c_str()) + "]" + " = infinite    ";
			else if (valueArray[i] == "1/0")
			{
				valueTextBox->Text = "no solutions";
				return;
			}
			else
				valueTextBox->Text += "x" + "[" + gcnew String(to_string(i + 1).c_str()) + "]" + " = " + gcnew String(valueArray[i].c_str()) + "    ";
		}
	}
private: System::Void fractionState_Click(System::Object^ sender, System::EventArgs^ e) {
	valueTextBox->Text = "";
	if (fractionState->Text == "b/c")
	{
		fractionState->Text = "a(b/c)";
		isSimulated = false;
	}
	else
	{
		fractionState->Text = "b/c";
		isSimulated = true;
	}

	if (valueArray[0] == "")
		return;
	setValueArray(matrix, valueArray, isSimulated);

	for (int i = 0; i < currentArrayLength; i++)
	{
		if (valueArray[i] == "0/0")
			valueTextBox->Text += "x" + "[" + gcnew String(to_string(i + 1).c_str()) + "]" + " = infinite    ";
		else if (valueArray[i] == "1/0")
		{
			valueTextBox->Text = "no solutions";
			return;
		}
		else
			valueTextBox->Text += "x" + "[" + gcnew String(to_string(i + 1).c_str()) + "]" + " = " + gcnew String(valueArray[i].c_str()) + "    ";
	}
}
};
}
