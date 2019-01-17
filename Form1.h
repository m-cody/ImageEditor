#include <cstdlib>
#include <cmath>
#include "globals.h"
#include "image.h"
#include "ConsoleAdapter.h"


using namespace std;

bool loadImageFromFile(string filename);
void saveImageToFile(string filename);
image* displayImage();
void averageRegions(int blockWidth, int blockHeight);
void increaseRedValues(int value);
void increaseGreenValues(int value);
void increaseBlueValues(int value);
void increaseBlueValues(int value);
void grayImage();
void addNoise();
void deNoise();

std::string gc2std(System::String^ s)
{
	using System::IntPtr;
	using System::Runtime::InteropServices::Marshal;

	IntPtr ip = Marshal::StringToHGlobalAnsi(s);

	std::string ss;
	try 
	{
		ss = static_cast<const char*>(ip.ToPointer());
	} catch (std::bad_alloc&) 
	{
		Marshal::FreeHGlobal(ip);
		throw;
	}
	Marshal::FreeHGlobal(ip);
	return ss;
}


#pragma once

namespace MCS2514Pgm3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();

			if(SHOW_DEBUG_CONSOLE)
			{
				console = new ConsoleAdapter();
				console->CreateConsole(BOTH);
			}
			origImageWidth = 0;
			origImageHeight = 0;
			blockHeight = 0;
			shrunk = false;
			disableShrink();
			this->saveButton->Enabled = false;
			this->blockWidthBox->Enabled = false;
			this->greenBtn->Enabled = false;
			this->blueBtn->Enabled = false;
			this->redBtn->Enabled = false;
			this->invertBtn->Enabled = false;

			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
    private: static ConsoleAdapter* console;
	private: System::Windows::Forms::OpenFileDialog^  openSongDialog;
	private: System::Windows::Forms::Button^  openButton;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  origHeightLbl;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  origWidthLbl;
	private: System::Windows::Forms::Button^  shrinkButton;

	private: System::Windows::Forms::GroupBox^  groupBox2;

	private: System::Windows::Forms::Label^  label4;

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Button^  saveButton;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  blockHeightLbl;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  blockWidthBox;


	private: System::Windows::Forms::SaveFileDialog^  saveImageDialog;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  newHeightLbl;
	private: System::Windows::Forms::Label^  newWidthLbl;
	private: static int origImageWidth;
	private: static int origImageHeight;
	private: static int blockHeight;
	private: static bool shrunk;
	private: System::Windows::Forms::Button^  redBtn;
	private: System::Windows::Forms::Button^  greenBtn;
	private: System::Windows::Forms::Button^  blueBtn;
	private: System::Windows::Forms::Button^  invertBtn;
	private: System::Windows::Forms::Button^  addnoise;
	private: System::Windows::Forms::Button^  denoise;






	protected: 

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
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->openSongDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->origHeightLbl = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->origWidthLbl = (gcnew System::Windows::Forms::Label());
			this->shrinkButton = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->newHeightLbl = (gcnew System::Windows::Forms::Label());
			this->newWidthLbl = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->blockHeightLbl = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->blockWidthBox = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->saveButton = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->saveImageDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->redBtn = (gcnew System::Windows::Forms::Button());
			this->greenBtn = (gcnew System::Windows::Forms::Button());
			this->blueBtn = (gcnew System::Windows::Forms::Button());
			this->invertBtn = (gcnew System::Windows::Forms::Button());
			this->addnoise = (gcnew System::Windows::Forms::Button());
			this->denoise = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Black;
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pictureBox1->Location = System::Drawing::Point(16, 101);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(852, 590);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// openSongDialog
			// 
			this->openSongDialog->RestoreDirectory = true;
			// 
			// openButton
			// 
			this->openButton->Location = System::Drawing::Point(963, 101);
			this->openButton->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->openButton->Name = L"openButton";
			this->openButton->Size = System::Drawing::Size(112, 33);
			this->openButton->TabIndex = 1;
			this->openButton->Text = L"Open Image";
			this->openButton->UseVisualStyleBackColor = true;
			this->openButton->Click += gcnew System::EventHandler(this, &Form1::openButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(8, 32);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(102, 17);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Image Width:";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->origHeightLbl);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->origWidthLbl);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(877, 142);
			this->groupBox1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox1->Size = System::Drawing::Size(267, 108);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Original Image";
			// 
			// origHeightLbl
			// 
			this->origHeightLbl->AutoSize = true;
			this->origHeightLbl->Location = System::Drawing::Point(143, 66);
			this->origHeightLbl->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->origHeightLbl->Name = L"origHeightLbl";
			this->origHeightLbl->Size = System::Drawing::Size(34, 17);
			this->origHeightLbl->TabIndex = 5;
			this->origHeightLbl->Text = L"0 px";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(8, 66);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(108, 17);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Image Height:";
			// 
			// origWidthLbl
			// 
			this->origWidthLbl->AutoSize = true;
			this->origWidthLbl->Location = System::Drawing::Point(143, 32);
			this->origWidthLbl->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->origWidthLbl->Name = L"origWidthLbl";
			this->origWidthLbl->Size = System::Drawing::Size(34, 17);
			this->origWidthLbl->TabIndex = 3;
			this->origWidthLbl->Text = L"0 px";
			// 
			// shrinkButton
			// 
			this->shrinkButton->Location = System::Drawing::Point(963, 487);
			this->shrinkButton->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->shrinkButton->Name = L"shrinkButton";
			this->shrinkButton->Size = System::Drawing::Size(112, 33);
			this->shrinkButton->TabIndex = 4;
			this->shrinkButton->Text = L"Shrink Image";
			this->shrinkButton->UseVisualStyleBackColor = true;
			this->shrinkButton->Click += gcnew System::EventHandler(this, &Form1::shrinkButton_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->newHeightLbl);
			this->groupBox2->Controls->Add(this->newWidthLbl);
			this->groupBox2->Controls->Add(this->label8);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->blockHeightLbl);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->blockWidthBox);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Location = System::Drawing::Point(877, 308);
			this->groupBox2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox2->Size = System::Drawing::Size(267, 172);
			this->groupBox2->TabIndex = 5;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"New Image";
			// 
			// newHeightLbl
			// 
			this->newHeightLbl->AutoSize = true;
			this->newHeightLbl->Location = System::Drawing::Point(143, 138);
			this->newHeightLbl->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->newHeightLbl->Name = L"newHeightLbl";
			this->newHeightLbl->Size = System::Drawing::Size(34, 17);
			this->newHeightLbl->TabIndex = 12;
			this->newHeightLbl->Text = L"0 px";
			// 
			// newWidthLbl
			// 
			this->newWidthLbl->AutoSize = true;
			this->newWidthLbl->Location = System::Drawing::Point(143, 105);
			this->newWidthLbl->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->newWidthLbl->Name = L"newWidthLbl";
			this->newWidthLbl->Size = System::Drawing::Size(34, 17);
			this->newWidthLbl->TabIndex = 8;
			this->newWidthLbl->Text = L"0 px";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(8, 138);
			this->label8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(108, 17);
			this->label8->TabIndex = 11;
			this->label8->Text = L"Image Height:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(8, 105);
			this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(102, 17);
			this->label5->TabIndex = 10;
			this->label5->Text = L"Image Width:";
			// 
			// blockHeightLbl
			// 
			this->blockHeightLbl->AutoSize = true;
			this->blockHeightLbl->Location = System::Drawing::Point(143, 66);
			this->blockHeightLbl->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->blockHeightLbl->Name = L"blockHeightLbl";
			this->blockHeightLbl->Size = System::Drawing::Size(34, 17);
			this->blockHeightLbl->TabIndex = 9;
			this->blockHeightLbl->Text = L"0 px";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(235, 32);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(22, 17);
			this->label3->TabIndex = 8;
			this->label3->Text = L"px";
			// 
			// blockWidthBox
			// 
			this->blockWidthBox->Location = System::Drawing::Point(128, 28);
			this->blockWidthBox->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->blockWidthBox->Name = L"blockWidthBox";
			this->blockWidthBox->Size = System::Drawing::Size(103, 22);
			this->blockWidthBox->TabIndex = 6;
			this->blockWidthBox->TextChanged += gcnew System::EventHandler(this, &Form1::blockWidthBox_TextChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(8, 66);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(104, 17);
			this->label4->TabIndex = 4;
			this->label4->Text = L"Block Height:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(8, 32);
			this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(98, 17);
			this->label6->TabIndex = 2;
			this->label6->Text = L"Block Width:";
			// 
			// saveButton
			// 
			this->saveButton->Location = System::Drawing::Point(963, 660);
			this->saveButton->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->saveButton->Name = L"saveButton";
			this->saveButton->Size = System::Drawing::Size(112, 33);
			this->saveButton->TabIndex = 6;
			this->saveButton->Text = L"Save Image";
			this->saveButton->UseVisualStyleBackColor = true;
			this->saveButton->Click += gcnew System::EventHandler(this, &Form1::saveButton_Click);
			// 
			// label7
			// 
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 22, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::Color::Navy;
			this->label7->Location = System::Drawing::Point(16, 27);
			this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(853, 55);
			this->label7->TabIndex = 7;
			this->label7->Text = L"Image Processing";
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label7->Click += gcnew System::EventHandler(this, &Form1::label7_Click);
			// 
			// saveImageDialog
			// 
			this->saveImageDialog->DefaultExt = L"tif";
			this->saveImageDialog->FileName = L"myImage.tif";
			this->saveImageDialog->RestoreDirectory = true;
			// 
			// redBtn
			// 
			this->redBtn->ForeColor = System::Drawing::Color::Red;
			this->redBtn->Location = System::Drawing::Point(877, 528);
			this->redBtn->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->redBtn->Name = L"redBtn";
			this->redBtn->Size = System::Drawing::Size(73, 36);
			this->redBtn->TabIndex = 8;
			this->redBtn->Text = L"+ Red";
			this->redBtn->UseVisualStyleBackColor = true;
			this->redBtn->Click += gcnew System::EventHandler(this, &Form1::redBtn_Click);
			// 
			// greenBtn
			// 
			this->greenBtn->ForeColor = System::Drawing::Color::Green;
			this->greenBtn->Location = System::Drawing::Point(980, 528);
			this->greenBtn->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->greenBtn->Name = L"greenBtn";
			this->greenBtn->Size = System::Drawing::Size(76, 36);
			this->greenBtn->TabIndex = 9;
			this->greenBtn->Text = L"+ Green";
			this->greenBtn->UseVisualStyleBackColor = true;
			this->greenBtn->Click += gcnew System::EventHandler(this, &Form1::greenBtn_Click);
			// 
			// blueBtn
			// 
			this->blueBtn->ForeColor = System::Drawing::Color::Blue;
			this->blueBtn->Location = System::Drawing::Point(1064, 528);
			this->blueBtn->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->blueBtn->Name = L"blueBtn";
			this->blueBtn->Size = System::Drawing::Size(75, 36);
			this->blueBtn->TabIndex = 10;
			this->blueBtn->Text = L"+ Blue";
			this->blueBtn->UseVisualStyleBackColor = true;
			this->blueBtn->Click += gcnew System::EventHandler(this, &Form1::blueBtn_Click);
			// 
			// invertBtn
			// 
			this->invertBtn->Location = System::Drawing::Point(963, 571);
			this->invertBtn->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->invertBtn->Name = L"invertBtn";
			this->invertBtn->Size = System::Drawing::Size(131, 33);
			this->invertBtn->TabIndex = 11;
			this->invertBtn->Text = L"Gray Image";
			this->invertBtn->UseVisualStyleBackColor = true;
			this->invertBtn->Click += gcnew System::EventHandler(this, &Form1::invertBtn_Click);
			// 
			// addnoise
			// 
			this->addnoise->Location = System::Drawing::Point(877, 612);
			this->addnoise->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->addnoise->Name = L"addnoise";
			this->addnoise->Size = System::Drawing::Size(115, 41);
			this->addnoise->TabIndex = 12;
			this->addnoise->Text = L"add noise";
			this->addnoise->UseVisualStyleBackColor = true;
			this->addnoise->Click += gcnew System::EventHandler(this, &Form1::addnoise_Click);
			// 
			// denoise
			// 
			this->denoise->Location = System::Drawing::Point(1024, 613);
			this->denoise->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->denoise->Name = L"denoise";
			this->denoise->Size = System::Drawing::Size(120, 39);
			this->denoise->TabIndex = 13;
			this->denoise->Text = L"denoise(bonus)";
			this->denoise->UseVisualStyleBackColor = true;
			this->denoise->Click += gcnew System::EventHandler(this, &Form1::denoise_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1155, 708);
			this->Controls->Add(this->denoise);
			this->Controls->Add(this->addnoise);
			this->Controls->Add(this->invertBtn);
			this->Controls->Add(this->blueBtn);
			this->Controls->Add(this->greenBtn);
			this->Controls->Add(this->redBtn);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->saveButton);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->shrinkButton);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->openButton);
			this->Controls->Add(this->pictureBox1);
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"Form1";
			this->Text = L"MCS2514 Project2";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	
	private: System::Void openButton_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if(openSongDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				if(!loadImageFromFile(gc2std(openSongDialog->FileName)))
					return;
				image* myImage = displayImage();
				if(myImage && myImage->getPixels())
				{
					this->saveButton->Enabled = true;
					char buffer[20];
					this->blockWidthBox->Enabled = true;
					this->redBtn->Enabled = true;
					this->greenBtn->Enabled = true;
					this->blueBtn->Enabled = true;
					this->invertBtn->Enabled = true;
					sprintf(buffer, "%d px", myImage->getHeight());
					this->origHeightLbl->Text = gcnew System::String(buffer);
					this->origImageHeight = myImage->getHeight();
					sprintf(buffer, "%d px", myImage->getWidth());
					this->origWidthLbl->Text = gcnew System::String(buffer);
					this->origImageWidth = myImage->getWidth();
					if(int(myImage->getWidth()/100) > 0)
					{
						sprintf(buffer, "%d", myImage->getWidth()/100);
						this->blockWidthBox->Text = gcnew System::String(buffer);
						setBlockWidth(myImage->getWidth()/100);
					}
					else
					{
						sprintf(buffer, "%d", 2);
						this->blockWidthBox->Text = gcnew System::String(buffer);
						setBlockWidth(2);
					}
					this->shrunk = false;
					enableShrink();

					showImage(myImage);
				}
				else
				{
					cout << "The image could not be displayed because there is no pixel data!" << endl;
				}
				
			}
		}
private: void setBlockWidth(int width)
		{
			int newWidth = int(this->origImageWidth/width);
			int height = width;//ceil(float(width) / float(this->origImageWidth)*(float)origImageHeight);
			if(!height)
				height = 1;
			this->blockHeight = height;
			int newHeight = int(this->origImageHeight/height);
			char buffer[20];
			sprintf(buffer, "%d px", newHeight);
			this->newHeightLbl->Text = gcnew System::String(buffer);
			sprintf(buffer, "%d px", newWidth);
			this->newWidthLbl->Text = gcnew System::String(buffer);
			sprintf(buffer, "%d px", height);
			this->blockHeightLbl->Text = gcnew System::String(buffer);
		}

private: System::Void shrinkButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
				averageRegions(atoi(gc2std(this->blockWidthBox->Text).c_str()), this->blockHeight);
				this->shrunk = true;
				image* myImage = displayImage();
				if(myImage && myImage->getPixels())
				{
					this->blockWidthBox->Enabled = false;
					disableShrink();
					showImage(myImage);
				}
				else
				{
					cout << "The image could not be displayed because there is no pixel data!" << endl;
				}
		 
		 }
private: System::Void saveButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(this->saveImageDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				saveImageToFile(gc2std(saveImageDialog->FileName));
			}
		 }
private: System::Void blockWidthBox_TextChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			int value = atoi(gc2std(this->blockWidthBox->Text).c_str());
			if(value && !this->shrunk)
			{
				if(value > this->origImageHeight)
					value = origImageHeight;
				if(value > this->origImageWidth)
					value = origImageWidth;
				char buffer[20];
				sprintf(buffer, "%d", value);
				this->blockWidthBox->Text = gcnew System::String(buffer);

				setBlockWidth(value);
				enableShrink();
			}
			else
			{
				disableShrink();
			}
		 }
 private:  void disableShrink()
		   {
			   this->shrinkButton->Enabled = false;
			   if(!this->shrunk)
			   {
				   this->newHeightLbl->Text = L"N/A";
				   this->newWidthLbl->Text = L"N/A";
				   this->blockHeightLbl->Text = L"N/A";
				   this->blockHeight = 0;
			   }
		   }

private:  void showImage(image* myImage)
		  {
			  if(myImage->getPixels() && myImage->getHeight() && myImage->getWidth())
			  {
					CImage out;
					myImage->viewImage(&out);
					if(myImage->getWidth() < 640 && myImage->getHeight() < 480)
						this->pictureBox1->SizeMode = PictureBoxSizeMode::Normal;
					else
						this->pictureBox1->SizeMode = PictureBoxSizeMode::Zoom;
					this->pictureBox1->Image = Image::FromHbitmap(IntPtr(HBITMAP(out)));
			  }
		  }

private:  void enableShrink()
		   {
			   if(!this->shrunk)
					this->shrinkButton->Enabled = true;
		   }

private: System::Void redBtn_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
				increaseRedValues(COMPONENT_INCREASE_VALUE);
				image* myImage = displayImage();
				if(myImage && myImage->getPixels())
					showImage(myImage);
		 }
private: System::Void greenBtn_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
				increaseGreenValues(COMPONENT_INCREASE_VALUE);
				image* myImage = displayImage();
				if(myImage && myImage->getPixels())
					showImage(myImage);		 
		 }
private: System::Void blueBtn_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
				increaseBlueValues(COMPONENT_INCREASE_VALUE);
				image* myImage = displayImage();
				if(myImage && myImage->getPixels())
					showImage(myImage);			 
		 }
private: System::Void invertBtn_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
				grayImage();
				image* myImage = displayImage();
				if(myImage && myImage->getPixels())
					showImage(myImage);
		 }
private: System::Void label7_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void addnoise_Click(System::Object^  sender, System::EventArgs^  e) {

				addNoise();
				image* myImage = displayImage();
				if(myImage && myImage->getPixels())
					showImage(myImage);
		 }
private: System::Void denoise_Click(System::Object^  sender, System::EventArgs^  e) {
			 	deNoise();
				image* myImage = displayImage();
				if(myImage && myImage->getPixels())
					showImage(myImage);
		 }
};
	
}

