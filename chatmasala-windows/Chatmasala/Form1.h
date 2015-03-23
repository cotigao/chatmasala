/* ChatMasala
 * Copyright (C) 2013 Vikram Fugro <vikram.fugro@gmail.com>
 *
 * Form1.h: main body
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details
 */

#pragma once
#include <windows.h>
#include <winuser.h>


namespace Chatmasala {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::Text;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Runtime::InteropServices;
	using namespace System::Net::NetworkInformation;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
#if 1
	public ref class XString
	{
		public:
		bool self;
		bool sent;
		String^ str;
	};

	public ref class Buddy
	{
		public:
		String^ name;
		String^ ip;
		Socket^ sSocket;
		Socket^ rSocket;
		System::Object^ ptr;
		array<Byte>^ buffer;
		int dataSize;
		int totalMsgLength;
		System::Collections::ArrayList^ iMsgs;
		int pendingRead;
		System::Drawing::Color color;
		System::Object^ form3;

		~Buddy()
		{
			if (name)
				delete name;
			if (ip)
				delete ip;
			if (rSocket) {
				try {
					if (rSocket->Connected) {
						//rSocket->Disconnect(false);
					}
					rSocket->Close();
				}
				catch (System::Net::Sockets::SocketException^ e) {
				}
				delete rSocket;
			}
			if (sSocket) {
				try {
					if (sSocket->Connected) {
						//sSocket->Disconnect(false);
					}
					sSocket->Close();
				}
				catch (System::Net::Sockets::SocketException^ e) {
				}
				delete sSocket;
			}
			if (buffer)
				delete buffer;
			if (form3) {
				delete form3;
			}
			if (iMsgs) {
				for (int i=0; i < iMsgs->Count; i++) {
					Chatmasala::XString^ xStr = dynamic_cast<Chatmasala::XString^>(iMsgs[i]);
					if (xStr) {
						if (xStr->str)
							delete xStr->str;
						delete xStr;
					}
				}
				delete  iMsgs;
			}
		}

		Buddy(System::Object^ obj, String^ ips)
		{
			ip = ips;
			ptr = obj;
			buffer = gcnew array<Byte>(2048);
			iMsgs = gcnew System::Collections::ArrayList;
		}

		Buddy (System::Object^ obj, String^ ips, Socket^ msSocket, Socket^ mrSocket)
		{
			ip = ips;
			ptr = obj;
			buffer = gcnew array<Byte>(2048);
			sSocket = msSocket;
			rSocket = mrSocket;
			iMsgs = gcnew System::Collections::ArrayList;
		}

		Buddy (System::Object^ obj, String^ips, Socket^ msSocket, Socket^ mrSocket, String^ mName)
		{
			ip = ips;
			name = mName;
			ptr = obj;
			buffer = gcnew array<Byte>(2048);
			sSocket = msSocket;
			rSocket = mrSocket;
			iMsgs = gcnew System::Collections::ArrayList;
		}
		
		virtual String^ ToString () override
		{
			if (name != nullptr)
				return name;
			else
				return ip;
		}
	};

	public ref class customUpdateEventArgs : System::EventArgs
	{
		public:
		String^ mtext;
		int index;
		Chatmasala::Buddy^ buddy;

		~customUpdateEventArgs()
		{
			if (mtext)
				delete mtext;
		}

		customUpdateEventArgs (String^ text, int mIndex, Chatmasala::Buddy^ buddy)
		{
			this->mtext = text;
			this->index = mIndex;
			this->buddy = buddy;
		}
	};
#endif

#if 1
	public ref class Form2 : public System::Windows::Forms::Form
	{
		public:
		int index;

		Form2(String^ ip, int mIndex)
		{
			this->index = mIndex;
	
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(5, 9);
			this->label1->Name = L"Alias";
			this->label1->Size = System::Drawing::Size(60, 10);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Enter Alias for " + ip;
			//this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);

			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->textBox1->Location = System::Drawing::Point(45, 50);
			this->textBox1->Name = L"textBox2";
			this->textBox1->Size = System::Drawing::Size(150, 10);
			this->textBox1->KeyDown += (gcnew System::Windows::Forms::KeyEventHandler (this, &Form2::textBox1_KeyDown));
			//this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox2_TextChanged);

			this->components = (gcnew System::ComponentModel::Container());
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->SuspendLayout();
			this->AutoScale = true;
			this->ClientSize = System::Drawing::Size(240, 90);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->Name = L"Form2";
			this->Text = L"Alias";
			//this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			//this->DoubleClick += gcnew System::EventHandler(this, &Form1::listBox1_DoubleClick);
			this->ResumeLayout(false);
			this->PerformLayout();
			this->BackColor = System::Drawing::Color::LightSeaGreen;
		}
		
		~Form2()
		{
			if (components)
			{
				delete components;
			}
		}

		Label^ label1;
		TextBox^ textBox1;
		System::ComponentModel::IContainer^  components;
		delegate void aliasUpdateHandler (System::Object^ sender, customUpdateEventArgs^ e);
		event aliasUpdateHandler^ aliasUpdated;

		System::Void textBox1_KeyDown (System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			if (e->KeyCode == System::Windows::Forms::Keys::Enter) {
				customUpdateEventArgs^ args = gcnew 
					customUpdateEventArgs (this->textBox1->Text->Copy(this->textBox1->Text), this->index, nullptr);
				e->Handled = true;
				aliasUpdated (this, args);
			}
		}
	};
#endif

	ref class Form1;

#if 1
	public ref class Form3 : public System::Windows::Forms::Form
	{
		public:
		Form3(Chatmasala::Buddy^ bd)
		{
			buddy = bd;
			buddy->color = System::Drawing::Color::White;
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form3()
		{
			customUpdateEventArgs^ args = gcnew 
				customUpdateEventArgs (nullptr, -1, buddy);
			sendData (this, args);
		}

		RichTextBox^  textBox1;
		TextBox^  textBox2;
		System::Windows::Forms::ContextMenuStrip^ contextMenu1;
		Chatmasala::Buddy^ buddy;
		bool blink;
		delegate void sendDataHandler (System::Object^ sender, customUpdateEventArgs^ e);
		event sendDataHandler^ sendData;

		delegate void UpdateTextBoxDelegate (String^ str, int idLen, System::Drawing::Color color);
		delegate void ScrollToCaretDelegate ();
		delegate void ClearTextBoxDelegate ();

		void InitializeComponent(void)
		{
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->textBox1->Cursor = System::Windows::Forms::Cursors::Default;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Verdana", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(6, 5);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(672, 341);
			this->textBox1->TabIndex = 1;
			this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form3::textBox1_KeyDown);
			this->textBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form3::textBox1_MouseDown);
			// 
			// textBox2
			// 
			this->textBox2->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->textBox2->Location = System::Drawing::Point(6, 352);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox2->Size = System::Drawing::Size(481, 74);
			this->textBox2->TabIndex = 3;
			this->textBox2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form3::textBox2_KeyDown);

			this->contextMenu1 = gcnew System::Windows::Forms::ContextMenuStrip;
			this->contextMenu1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler
				(this, &Form3::contextMenu1_itemClicked);
			this->contextMenu1->Items->Add ("Copy");
			this->contextMenu1->Items->Add ("Clear");

			// 
			// Form3
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(683, 431);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->Name = L"Form1";
			this->ActiveControl = textBox2;
			this->ResumeLayout(false);
			this->PerformLayout();
			this->BackColor = System::Drawing::Color::LightSeaGreen;
			this->Resize += gcnew System::EventHandler(this, &Form3::form3_Resized);
		}

		void updateTextBox (String^ str, int idLen, System::Drawing::Color color)
		{
			if (this->InvokeRequired) {
				UpdateTextBoxDelegate^ d = 
					gcnew UpdateTextBoxDelegate(this, &Form3::updateTextBox);
				this->Invoke(d, gcnew array<Object^> {str, idLen, color});
				delete d;
			} else {
				if (idLen) {
					int len = this->textBox1->Text->Length;

					this->textBox1->AppendText (str);

					this->textBox1->Select(len + idLen, this->textBox1->Text->Length - idLen);
					this->textBox1->SelectionColor = color;
			
					delete str;
				} else {
					this->textBox1->Update();
					this->textBox1->Refresh();
				}
			}
		}

		void scrollToCaret ()
		{
			if (this->InvokeRequired) {
				ScrollToCaretDelegate^ d = 
					gcnew ScrollToCaretDelegate(this, &Form3::scrollToCaret);
				this->Invoke(d, gcnew array<Object^> {});
				delete d;
			} else {
				this->textBox1->SelectionStart = this->textBox1->Text->Length;
				this->textBox1->ScrollToCaret();
				this->textBox1->Update();
				this->textBox1->Refresh();
			}
		}
		
		void clearTextBox ()
		{
			if (this->InvokeRequired) {
				ClearTextBoxDelegate^ d = 
					gcnew ClearTextBoxDelegate(this, &Form3::clearTextBox);
				this->Invoke(d, gcnew array<Object^> {});
				delete d;
			} else {
				this->textBox1->Clear();
				this->textBox1->Update();
				this->textBox1->Refresh();
			}
		}

		void startFlashing (int c) {
			FLASHWINFO w;
			System::IntPtr p = this->Handle;
			w.cbSize = sizeof (w);
			if (c > 0) {
				w.dwTimeout = 500;
				w.dwFlags = FLASHW_ALL | FLASHW_TIMER;
			} else if (c < 0){
				w.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;
				w.dwTimeout = 0;
			} else {
				w.dwFlags = FLASHW_STOP;
				w.dwTimeout = 0;
			}
			w.hwnd = (HWND)p.ToPointer();
			
			if (c < 0) {
				w.uCount = UInt32::MaxValue;
			} else if (c > 0) {
				if (c == Int32::MaxValue)
					w.uCount = UInt32::MaxValue;
				else
					w.uCount = System::Convert::ToUInt32 (c);
			} else {
				w.uCount = 0;
			}
			FlashWindowEx (&w);
		}

		private: System::Void textBox2_KeyDown (System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			if (e->KeyCode == System::Windows::Forms::Keys::Enter) {
				customUpdateEventArgs^ args = gcnew 
					customUpdateEventArgs (this->textBox2->Text->Copy (this->textBox2->Text), 0, buddy);
				e->Handled = true;
				sendData (this, args);
				this->textBox2->Clear();
			} else if (e->Control && e->KeyCode == System::Windows::Forms::Keys::A) {
				this->textBox2->SelectAll();
			}
		}

	    private: System::Void textBox1_KeyDown (System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			if (e->Control && e->KeyCode == System::Windows::Forms::Keys::A) {
				this->textBox1->SelectAll();
			}
		}

	    

		private: System::Void textBox1_MouseDown (System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			if (e->Button == System::Windows::Forms::MouseButtons::Right) {
				this->contextMenu1->Show(this->textBox1, e->Location);
			}
		}

	    private: System::Void contextMenu1_itemClicked (System::Object^ sender, System::Windows::Forms::ToolStripItemClickedEventArgs^ e) {
			switch (this->contextMenu1->Items->IndexOf (e->ClickedItem)) {
				case 0: {
					this->textBox1->Copy();
				}
				break;

				case 1: {
					this->textBox1->Clear();
				}
				break;

				default:
				break;
			}
		}

		private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		}

	    private: System::Void form3_Resized (System::Object^ sender, System::EventArgs^ e)
		{ 
			if (this->WindowState == System::Windows::Forms::FormWindowState::Minimized) {
				customUpdateEventArgs^ args = gcnew 
					customUpdateEventArgs (nullptr, 1, buddy);
				sendData (this, args);
			} else {
				customUpdateEventArgs^ args = gcnew 
					customUpdateEventArgs (nullptr, 1, buddy);
				sendData (this, args);
			}
		}
	};
#endif

#if 1
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();


#if 0
			array<NetworkInterface^>^adapters = NetworkInterface::GetAllNetworkInterfaces();
			System::Collections::IEnumerator^ myEnum10 = adapters->GetEnumerator();
			while (myEnum10->MoveNext()) {
			 NetworkInterface ^ adapter = safe_cast<NetworkInterface ^>(myEnum10->Current);
			 System::Diagnostics::Debug::Write( "\n\n\n\n");
			 System::Diagnostics::Debug::Write( adapter->Name, " >> ");
			System::Net::NetworkInformation::PhysicalAddress ^ addr = adapter->GetPhysicalAddress();
			System::Diagnostics::Debug::Write(addr->ToString(), " >> " );
			IPInterfaceProperties^ adapterProperties =  adapter->GetIPProperties();
			IPAddressCollection ^ dnsServers = adapterProperties->DnsAddresses;
#if 1
   UnicastIPAddressInformationCollection ^ uniCast = adapterProperties->UnicastAddresses;
   if ( uniCast != nullptr )
   {	
      String^ lifeTimeFormat = "dddd, MMMM dd, yyyy  hh:mm:ss tt";
      System::Collections::IEnumerator^ myEnum3 = uniCast->GetEnumerator();
      while ( myEnum3->MoveNext() )
      {	
         UnicastIPAddressInformation ^ uni = safe_cast<UnicastIPAddressInformation ^>(myEnum3->Current);
         DateTime when;
		 if (uni->Address->AddressFamily == AddressFamily::InterNetwork && uni->IsDnsEligible)
			System::Diagnostics::Debug::Write(uni->Address->ToString(), " >> ");
         Console::WriteLine( "     Prefix Origin ........................ : {0}", uni->PrefixOrigin );
         Console::WriteLine( "     Suffix Origin ........................ : {0}", uni->SuffixOrigin );
         Console::WriteLine( "     Duplicate Address Detection .......... : {0}", uni->DuplicateAddressDetectionState );

         // Format the lifetimes as Sunday, February 16, 2003 11:33:44 PM 
         // if en-us is the current culture. 
         // Calculate the date and time at the end of the lifetimes.
         when = DateTime::UtcNow + TimeSpan::FromSeconds( (double)uni->AddressValidLifetime );
         when = when.ToLocalTime();
         Console::WriteLine( "     Valid Life Time ...................... : {0}", when.ToString( lifeTimeFormat, System::Globalization::CultureInfo::CurrentCulture ) );
         when = DateTime::UtcNow + TimeSpan::FromSeconds( (double)uni->AddressPreferredLifetime );
         when = when.ToLocalTime();
         Console::WriteLine( "     Preferred life time .................. : {0}", when.ToString( lifeTimeFormat, System::Globalization::CultureInfo::CurrentCulture ) );
         when = DateTime::UtcNow + TimeSpan::FromSeconds( (double)uni->DhcpLeaseLifetime );
         when = when.ToLocalTime();
         Console::WriteLine( "     DHCP Leased Life Time ................ : {0}", when.ToString( lifeTimeFormat, System::Globalization::CultureInfo::CurrentCulture ) );
      }

      Console::WriteLine();
   }
#endif
			}
#endif



			//
			//TODO: Add the constructor code here
			//
		}
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			sockConn->Close();
			delete sockConn;
			if (components)
			{
				delete components;
			}
		}

	Button^  button2;	
	TextBox^  textBox3;
	System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^  components;
	public: 

	System::Windows::Forms::ListBox^  listBox1;
	System::Windows::Forms::ContextMenuStrip^ contextMenu1;
	private: System::Windows::Forms::Button^  button1;
	public: 

	Socket^ sockConn;
	delegate void AddBuddyDelegate(Chatmasala::Buddy^ bd);
	delegate void GetDataDelegate(Chatmasala::Buddy^ bd, int size);

	delegate void SendDataDelegate (System::Object^ sender, customUpdateEventArgs^ e);
	delegate void UpdateAliasDelegate (System::Object^ sender, customUpdateEventArgs^ e);

	void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::SandyBrown;
			this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button2->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button2->Location = System::Drawing::Point(3, 28);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(52, 24);
			this->button2->TabIndex = 6;
			this->button2->Text = L"Add IP";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Clicked);
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Verdana", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox3->Location = System::Drawing::Point(61, 28);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(134, 24);
			this->textBox3->TabIndex = 7;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &Form1::textBox3_TextChanged);
			this->textBox3->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::textBox3_KeyDown);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// listBox1
			// 
			this->listBox1->DrawMode = System::Windows::Forms::DrawMode::OwnerDrawFixed;
			this->listBox1->Font = (gcnew System::Drawing::Font(L"Verdana", 10));
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 18;
			this->listBox1->Location = System::Drawing::Point(3, 60);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(192, 418);
			this->listBox1->TabIndex = 10;
			this->listBox1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::listBox1_DoubleClick);
			this->listBox1->DrawItem += gcnew System::Windows::Forms::DrawItemEventHandler(this, &Form1::listBox1_DrawItem);
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listBox1_selectedIndexChanged);
			this->listBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::listBox1_MouseDown);
			this->listBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::listBox1_KeyDown);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(3, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(44, 19);
			this->button1->TabIndex = 11;
			this->button1->Text = L"About";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Clicked);
			//
			// contextMenu1
			//
			this->contextMenu1 = gcnew System::Windows::Forms::ContextMenuStrip;
			this->contextMenu1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler
				(this, &Form1::contextMenu1_itemClicked);
			this->contextMenu1->Items->Add ("Chat");
			this->contextMenu1->Items->Add ("Details");
			this->contextMenu1->Items->Add ("Rename (Alias)");
			this->contextMenu1->Items->Add ("Remove");
			this->contextMenu1->Items->Add ("Cancel");
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(198, 481);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->button2);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->Name = L"Form1";
			this->Text = L"Chat Masala";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();
			this->BackColor = System::Drawing::Color::LightSeaGreen;
			this->Resize += gcnew System::EventHandler (this, &Form1::form1_Resized);
	}

	void updateTextBox (Chatmasala::Buddy^ bd, bool clear)
	{	
		Chatmasala::XString^ xStr;
		System::String^ tStr = nullptr;
		int i, startMsg, pendingRead = bd->pendingRead;
		System::Drawing::Color color;

		
		if (bd->pendingRead && bd->form3 == nullptr 
			&& this->WindowState == System::Windows::Forms::FormWindowState::Minimized) {
			/* TODO: remove below code, no need to flash this */
		    /*
			FLASHWINFO w;
			System::IntPtr p = this->Handle;
			w.cbSize = sizeof (w);
			w.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;
			w.hwnd = (HWND)p.ToPointer();
			w.dwTimeout = 0;
			w.uCount = UInt32::MaxValue;
			FlashWindowEx (&w);
			*/
		}
		
		if (bd->form3 == nullptr) {
			/* Earlier: !(don't return but create buddy chat form and set it minimized) */
			clear = true;
			Chatmasala::Form3^ form3 = gcnew Chatmasala::Form3(bd);
			bd->form3 = form3;
			form3->sendData += gcnew Chatmasala::Form3::sendDataHandler (this, &Form1::send_Data);
			form3->WindowState = System::Windows::Forms::FormWindowState::Minimized;
			form3->Show();
		}

		Chatmasala::Form3^ form3 = dynamic_cast<Chatmasala::Form3^>(bd->form3);

		if (form3->WindowState == System::Windows::Forms::FormWindowState::Minimized) {
			if (bd->pendingRead) {
				form3->startFlashing(Int32::MaxValue);
			}
		}

		if (clear) {
			startMsg = 0;
			form3->clearTextBox();
		} else {
			startMsg = bd->iMsgs->Count - bd->pendingRead;
		}

		for (i = startMsg; i < bd->iMsgs->Count; i++) {
			xStr = dynamic_cast<Chatmasala::XString^>(bd->iMsgs[i]);
			System::Drawing::Color color;
			int idLen;

			if (xStr->self) {
				tStr = "me";
				if (!xStr->sent) {
					tStr += " (failed to deliver): ";
					color = System::Drawing::Color::CornflowerBlue;
				} else {
					tStr += ": ";
					color = System::Drawing::Color::DarkBlue;
				}
			} else {
				tStr = bd->ToString() + ": ";
				color = System::Drawing::Color::DarkMagenta;
			}

			idLen = tStr->Length;
			tStr += xStr->str + System::Environment::NewLine + System::Environment::NewLine;

			form3->updateTextBox(tStr->Copy(tStr), idLen, color);

			delete tStr;
		}
		
		form3->updateTextBox(nullptr, 0, color);
		form3->scrollToCaret();
		delete form3->Text;
		form3->Text = bd->ToString();
		form3->Update();
		form3->Refresh();
		bd->pendingRead = 0;

		if (form3->WindowState == System::Windows::Forms::FormWindowState::Minimized 
			&& pendingRead) {
			form3->blink = true;
		} else if (form3->WindowState != System::Windows::Forms::FormWindowState::Minimized) {
			form3->blink = false;
			form3->startFlashing(0);
		} else {
			System::Drawing::Rectangle rc = 
				this->listBox1->GetItemRectangle (this->listBox1->Items->IndexOf (bd));
			Graphics^ obj = Graphics::FromHwnd (this->listBox1->Handle);
			if (bd == this->listBox1->SelectedItem && 
				bd->color != System::Drawing::Color::LightBlue) {
					obj->FillRectangle(gcnew System::Drawing::SolidBrush
					(System::Drawing::Color::LightBlue), rc);
				bd->color = System::Drawing::Color::LightBlue;
				obj->DrawString(bd->ToString(),
					gcnew System::Drawing::Font(L"Verdana", 10),
					gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black), rc);
			} else if (bd != this->listBox1->SelectedItem &&
				bd->color != System::Drawing::Color::White) {
					obj->FillRectangle(gcnew System::Drawing::SolidBrush
					(System::Drawing::Color::White), rc);
				bd->color = System::Drawing::Color::White;
				obj->DrawString(bd->ToString(),
					gcnew System::Drawing::Font(L"Verdana", 10),
					gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black), rc);
			}
		}
	}

	void getData (Chatmasala::Buddy^ bd, int size)
	{
		if (this->InvokeRequired) {
			GetDataDelegate^ d = 
				gcnew GetDataDelegate(this, &Form1::getData);
			this->Invoke(d, gcnew array<Object^> { bd, size});
			delete d;
		} else {
			if (size > 0) {
				if (bd->dataSize == 0) {
					System::Text::ASCIIEncoding^ e = gcnew System::Text::ASCIIEncoding;
					String^ str = e->GetString(bd->buffer, 0, 6);
					
					if (str) {
						if (!str->CompareTo("!chat!")) {
							String^ rtr = e->GetString(bd->buffer, 6, 5);
							bd->totalMsgLength = System::Convert::ToInt32(rtr);
							delete rtr;
						} else {
							size = 0;
							bd->totalMsgLength = 0;
						}
						delete str;
					} else {
						size = 0;
						bd->totalMsgLength = 0;
					}
					delete e;
				}

				bd->dataSize += size;
				if (bd->dataSize) { 
					if (bd->dataSize - 11 == bd->totalMsgLength) {
						System::Text::ASCIIEncoding^ e = gcnew System::Text::ASCIIEncoding;
						String^ str = e->GetString(bd->buffer, 11, bd->totalMsgLength);
						Chatmasala::XString^ xStr = gcnew Chatmasala::XString;
						xStr->str = str;
						xStr->self = false;
						bd->iMsgs->Add(xStr);
						bd->buffer->Resize(bd->buffer, 2048);
						bd->buffer->Clear(bd->buffer, 0, 2048);
						bd->dataSize = 0;
						bd->totalMsgLength = 0;
						delete e;
						bd->pendingRead++;
						updateTextBox (bd, false);
					}

					if (bd->buffer->Length - bd->dataSize < 2048) {
						bd->buffer->Resize (bd->buffer, bd->buffer->Length + 2048);
					}
				}
			} 
		}
	}

	static void OnReceivedBuffer (System::IAsyncResult^ ar)
	{
		Chatmasala::Buddy^ buddy = dynamic_cast<Chatmasala::Buddy^>(ar->AsyncState);
		Chatmasala::Form1^ ptr = dynamic_cast<Chatmasala::Form1^>(buddy->ptr);
		int recv;
		try {
			if (buddy->rSocket)	
				recv = buddy->rSocket->EndReceive (ar);
			//FIXME: per message setup
			/*else
				recv = buddy->sSocket->EndReceive (ar);*/
		}
		catch (System::Net::Sockets::SocketException^ e) {
			recv = -1;
		}
		catch (System::ObjectDisposedException ^ e) {
			recv = -1;
		}
		catch (System::ArgumentException^ e) {
			recv = -1;
		}

		if (recv > 0) {
			ptr->getData(buddy, recv);
			
			if (buddy->rSocket)
				buddy->rSocket->BeginReceive (buddy->buffer, buddy->dataSize, 2048, 
					System::Net::Sockets::SocketFlags::None,
						gcnew AsyncCallback(&Chatmasala::Form1::OnReceivedBuffer), buddy);
			//FIXME: per message setup
			/*else
				buddy->sSocket->BeginReceive (buddy->buffer, buddy->dataSize, 2048, 
					System::Net::Sockets::SocketFlags::None,
						gcnew AsyncCallback(&Chatmasala::Form1::OnReceivedBuffer), buddy);*/
		} else {
			if (buddy->rSocket) {
				try {
					buddy->rSocket->Shutdown(Sockets::SocketShutdown::Both);
				}
				catch (System::Net::Sockets::SocketException^ e) {
				}
				try {	
					buddy->rSocket->Close();
				}
				catch (System::Net::Sockets::SocketException^ e) {
				}
				delete buddy->rSocket;
				buddy->rSocket = nullptr;
			} 
			//FIXME: per message setup
			/*if (buddy->sSocket){
				buddy->sSocket->Close();
				delete buddy->sSocket;
				buddy->sSocket = nullptr;
			}*/

			buddy->totalMsgLength = 0;
			buddy->dataSize = 0;
			buddy->buffer->Resize (buddy->buffer, 2048);
			buddy->buffer->Clear (buddy->buffer, 0, 2048);
		}
	}

	void addBuddy (Chatmasala::Buddy^ bd)
	{
		if (this->InvokeRequired) {
			AddBuddyDelegate^ d = 
				gcnew AddBuddyDelegate(this, &Form1::addBuddy);
			this->Invoke(d, gcnew array<Object^> { bd });
			delete d;
		} else {
			int  i = 0;
			bool recv_changed = false;

			for (i = 0; i < this->listBox1->Items->Count; i++) {
				Chatmasala::Buddy^ buddy = dynamic_cast<Chatmasala::Buddy^>(this->listBox1->Items[i]);

				if (buddy->ip == bd->ip) {
					if (bd->rSocket) {
						if (buddy->rSocket) {
							try {
								buddy->rSocket->Close(false);
							}
							catch (System::Net::Sockets::SocketException^ e) {
							}
							delete buddy->rSocket;
						}
						buddy->rSocket = bd->rSocket;
						bd->rSocket = nullptr;
						bd->sSocket = nullptr;
						delete bd;

						buddy->totalMsgLength = 0;
						buddy->dataSize = 0;
						buddy->buffer->Resize (buddy->buffer, 2048);
						buddy->buffer->Clear (buddy->buffer, 0, 2048);
						recv_changed = true;

					}
					//FIXME: per message setup
					/* else if (bd->sSocket) {
						if (buddy->sSocket) {
							try {	
								buddy->sSocket->Close(false);
							}
							catch (System::Net::Sockets::SocketException^ e) {
							}
							delete buddy->sSocket;
						}
						buddy->sSocket = bd->sSocket;
						bd->rSocket = nullptr;
						bd->sSocket = nullptr;
						delete bd;

						if (buddy->rSocket == nullptr) {
							buddy->totalMsgLength = 0;
							buddy->dataSize = 0;
							buddy->buffer->Resize (buddy->buffer, 2048);
							buddy->buffer->Clear (buddy->buffer, 0, 2048);
							recv_changed = true;
						}
					}*/

					if (recv_changed) {
						if (buddy->rSocket)
							buddy->rSocket->BeginReceive (buddy->buffer, buddy->dataSize, 2048, 
								System::Net::Sockets::SocketFlags::None,
									gcnew AsyncCallback(&Chatmasala::Form1::OnReceivedBuffer), buddy);
						//FIXME: per message setup
						/*else
							buddy->sSocket->BeginReceive (buddy->buffer, buddy->dataSize, 2048, 
								System::Net::Sockets::SocketFlags::None,
									gcnew AsyncCallback(&Chatmasala::Form1::OnReceivedBuffer), buddy);*/
					}

					break;
				}
			}

			if (i == this->listBox1->Items->Count) {
				this->listBox1->Items->Add(bd);
				if (bd->rSocket)
					bd->rSocket->BeginReceive (bd->buffer, 0, 2048, System::Net::Sockets::SocketFlags::None,
						gcnew AsyncCallback(&Chatmasala::Form1::OnReceivedBuffer), bd);
				//FIXME: per message setup
				/*else if (bd->sSocket)
					bd->sSocket->BeginReceive (bd->buffer, 0, 2048, System::Net::Sockets::SocketFlags::None,
						gcnew AsyncCallback(&Chatmasala::Form1::OnReceivedBuffer), bd);*/
			}

			//this->listBox1->Update();
			//this->listBox1->Refresh();
		}
	}

    static void OnConnectionRequest (System::IAsyncResult^ ar)
	{
		Chatmasala::Form1^ ptr = dynamic_cast<Chatmasala::Form1^>(ar->AsyncState);
		Socket^ rSocket;
		try {
			rSocket = ptr->sockConn->EndAccept (ar);
		}
		catch (System::Net::Sockets::SocketException^ e) {
			return;
		}
		catch (System::ObjectDisposedException ^ e) {
			return;
		}
		catch (System::ArgumentException^ e) {
			return;
		}
		if (rSocket) {
			IPEndPoint^ ipe = dynamic_cast<IPEndPoint^>(rSocket->RemoteEndPoint);
			Chatmasala::Buddy^ bd = gcnew Chatmasala::Buddy(ptr, ipe->Address->ToString(), nullptr, rSocket);
			ptr->addBuddy (bd);
			ptr->sockConn->BeginAccept (gcnew AsyncCallback(&Chatmasala::Form1::OnConnectionRequest), 
					ptr);
		}
	}

	System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				this->sockConn = (gcnew Socket (AddressFamily::InterNetwork, 
									SocketType::Stream, ProtocolType::Tcp));
				this->sockConn->Bind (gcnew IPEndPoint (IPAddress::Any, 5231));
				this->sockConn->Listen (10);
				this->sockConn->BeginAccept (gcnew AsyncCallback(&Chatmasala::Form1::OnConnectionRequest), 
					this);
			 }

	System::Void button2_Clicked(System::Object^  sender, System::EventArgs^  e) {
					if (this->textBox3->Text) {
						System::Net::IPAddress^ ip;
						
						try {
							ip = System::Net::IPAddress::Parse(this->textBox3->Text);
						}
						catch ( ArgumentNullException^ e ) {
      
						}
						catch ( FormatException^ e ) {
     
						}
						catch ( Exception^ e ) {
						
						}
						if (ip) {
							Chatmasala::Buddy^ bd = gcnew Chatmasala::Buddy(this, ip->ToString());
							this->addBuddy (bd);
						}

						this->textBox3->Clear();
					}
				}
	System::Void button1_Clicked(System::Object^  sender, System::EventArgs^  e) {
					MessageBox::Show ("Chat Masala v0.1" + System::Environment::NewLine 
						+ "by ViKRaM F \"cotigao\" <vikram.fugro@gmail.com>" 
						+ System::Environment::NewLine + System::Environment::NewLine
						+ "Papdi Chat!");
				}
	System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				{		
					for (int i = 0; i < this->listBox1->Items->Count; i++) {
						Chatmasala::Buddy^ bd = dynamic_cast<Chatmasala::Buddy^>(this->listBox1->Items[i]);
						bool blink = false;
						
						if (bd->form3) {
							Chatmasala::Form3^ form3 = dynamic_cast<Chatmasala::Form3^>(bd->form3);
							blink = form3->blink;
						}
						if (bd->pendingRead || blink) {
							System::Drawing::Rectangle rc = this->listBox1->GetItemRectangle (i);
							Graphics^ obj = Graphics::FromHwnd (this->listBox1->Handle);
							if (bd->color == System::Drawing::Color::Chartreuse) {
								obj->FillRectangle(gcnew System::Drawing::SolidBrush
									(System::Drawing::Color::Orange), rc);
								bd->color = System::Drawing::Color::Orange;
								obj->DrawString(bd->ToString(),
									gcnew System::Drawing::Font(L"Verdana", 10),
									gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black), rc);
							} else {
								obj->FillRectangle(gcnew System::Drawing::SolidBrush
									(System::Drawing::Color::Chartreuse), rc);
								bd->color = System::Drawing::Color::Chartreuse;
								obj->DrawString(bd->ToString(),
									gcnew System::Drawing::Font(L"Verdana", 10),
									gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black), rc);
							}
						}
					}
				}
			}

	void updatedAlias (System::Object^ sender, customUpdateEventArgs^ e) {
			if (this->InvokeRequired) {
				UpdateAliasDelegate^ d = 
					gcnew UpdateAliasDelegate(this, &Form1::updatedAlias);
				this->Invoke(d, gcnew array<Object^> { sender, e});
				delete d;
			} else {
				Chatmasala::Buddy^ buddy = dynamic_cast<Chatmasala::Buddy^>(this->listBox1->Items[e->index]);

				this->listBox1->Items->Remove(buddy);
				buddy->name = e->mtext->Copy(e->mtext);
				this->listBox1->Items->Insert(e->index, buddy);
			
				this->listBox1->SetSelected (this->listBox1->Items->IndexOf (buddy), true);
				//this->listBox1->Update();
				//this->listBox1->Refresh();
				
				updateTextBox (buddy, true);

				delete e;
				delete sender;
			}
		}

	System::Void listBox1_KeyDown (System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			if (e->KeyCode == System::Windows::Forms::Keys::Delete) {
				Chatmasala::Buddy^ buddy = dynamic_cast<Chatmasala::Buddy^>(this->listBox1->SelectedItem);
				if (buddy) {
					int index  = this->listBox1->Items->IndexOf (buddy);
					this->listBox1->Items->Remove(buddy);
					delete buddy;
					this->listBox1->Update();
					this->listBox1->Refresh();
					if (index < this->listBox1->Items->Count)
						this->listBox1->SetSelected (index, true);
					else if (this->listBox1->Items->Count > 0)
						this->listBox1->SetSelected(0, true);
				}
				//this->listBox1->Update();
				//this->listBox1->Refresh();
			} else if (e->KeyCode == System::Windows::Forms::Keys::C) {
				Chatmasala::Buddy^ buddy = dynamic_cast<Chatmasala::Buddy^>(this->listBox1->SelectedItem);
				if (buddy) {
					Chatmasala::Form2^ form2 = gcnew Chatmasala::Form2(buddy->ip, this->listBox1->SelectedIndex);
					form2->aliasUpdated += gcnew Chatmasala::Form2::aliasUpdateHandler (this, &Form1::updatedAlias);
					form2->Show();
				} 
			}
		}
	System::Void listBox1_DrawItem(System::Object^ sender, DrawItemEventArgs^ e) {
			if (e->Index < 0) {
				e->DrawBackground ();
				e->DrawFocusRectangle();
				return;
			}

			Chatmasala::Buddy^ bd = dynamic_cast<Chatmasala::Buddy^>(this->listBox1->Items[e->Index]);
			System::Drawing::Graphics^ obj = e->Graphics;
			e->DrawBackground();

			if (bd != this->listBox1->SelectedItem) {
				obj->FillRectangle(gcnew System::Drawing::SolidBrush(System::Drawing::Color::White), 
					e->Bounds);
				bd->color = System::Drawing::Color::White;
				e->Graphics->DrawString(this->listBox1->Items[e->Index]->ToString(), e->Font, 
					gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black), e->Bounds, 
					System::Drawing::StringFormat::GenericDefault);
			} else {
				obj->FillRectangle(gcnew System::Drawing::SolidBrush(System::Drawing::Color::LightBlue), 
					e->Bounds);
				bd->color = System::Drawing::Color::LightBlue;
				e->Graphics->DrawString(this->listBox1->Items[e->Index]->ToString(), e->Font, 
					gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black), e->Bounds, 
					System::Drawing::StringFormat::GenericDefault);
			}
		
			if (this->listBox1->Focused)
				e->DrawFocusRectangle();
		}

	System::Void listBox1_DoubleClick (System::Object^ sender, System::Windows::Forms::MouseEventArgs^  e) 
		{
			Chatmasala::Buddy^ buddy = dynamic_cast<Chatmasala::Buddy^>(this->listBox1->SelectedItem);

			if (buddy) {
				Chatmasala::Form3^ form3;
				if (buddy->form3 == nullptr) {
					form3 = gcnew Chatmasala::Form3(buddy);
					buddy->form3 = form3;
					form3->sendData += gcnew Chatmasala::Form3::sendDataHandler (this, &Form1::send_Data);
					form3->Show();
					updateTextBox (buddy, true);
				} else {
					form3 = dynamic_cast<Chatmasala::Form3^>(buddy->form3);
					form3->WindowState = System::Windows::Forms::FormWindowState::Normal;
					form3->Update();
					form3->ResumeLayout();
				}
			}
		}

	System::Void listBox1_MouseDown (System::Object^ sender, System::Windows::Forms::MouseEventArgs^  e) 
		{
			if (e->Button == System::Windows::Forms::MouseButtons::Right) {
				int _selectedIndex = this->listBox1->IndexFromPoint(e->Location);
				if (_selectedIndex == -1 || _selectedIndex > this->listBox1->Items->Count - 1)
					return;
				if (this->listBox1->SelectedItem != this->listBox1->Items[_selectedIndex])
					this->listBox1->SetSelected (_selectedIndex, true);
				this->listBox1->Update();
				this->listBox1->Refresh();
				this->contextMenu1->Show(this->listBox1, e->Location);
			}
		}
	void send_Data (System::Object^ sender, customUpdateEventArgs^ e) 
		{
			if (this->InvokeRequired) {
				SendDataDelegate^ d = 
					gcnew SendDataDelegate(this, &Form1::send_Data);
				this->Invoke(d, gcnew array<Object^> { sender, e});
				delete d;
			} else  {
			Chatmasala::Buddy^ buddy = e->buddy;			
				
			if (e->index == -1) {
				buddy->form3 = nullptr;
				delete e;
				return;
			}

			if (e->index == 1) {
				updateTextBox (buddy, false);
				delete e;
				return;
			}

			//FIXME: per message setup
			//if (buddy->sSocket == nullptr && buddy->rSocket == nullptr) {
				buddy->sSocket = (gcnew Socket (AddressFamily::InterNetwork, 
									SocketType::Stream, ProtocolType::Tcp));
				try {
					System::IAsyncResult^ r = 
						buddy->sSocket->BeginConnect (buddy->ip, 5231, nullptr, nullptr);
					r->AsyncWaitHandle->WaitOne(2500, true);
					if (!buddy->sSocket->Connected) {
						buddy->sSocket->Close();
						delete buddy->sSocket;
						buddy->sSocket = nullptr;
					}
				}
				catch (System::Net::Sockets::SocketException ^ e) {
					buddy->sSocket->Close();
					delete buddy->sSocket;
					buddy->sSocket = nullptr;
				}
				catch (System::ObjectDisposedException^ e) {
					buddy->sSocket->Close();
					delete buddy->sSocket;
					buddy->sSocket = nullptr;
				}
				//FIXME: per message setup
				/*buddy->totalMsgLength = 0;
				buddy->dataSize = 0;
				buddy->buffer->Resize (buddy->buffer, 2048);
				buddy->buffer->Clear (buddy->buffer, 0, 2048);

				if (buddy->sSocket) {
					buddy->sSocket->BeginReceive (buddy->buffer, 0, 2048, 
						System::Net::Sockets::SocketFlags::None,
						gcnew AsyncCallback(&Chatmasala::Form1::OnReceivedBuffer), buddy);
				}

			}*/

			int toSend, sent, offset = 0;
			System::Text::ASCIIEncoding^ ac = gcnew System::Text::ASCIIEncoding;
					
			Chatmasala::XString^ xStr = gcnew Chatmasala::XString;
			String^ vstr = "\r\n";
			xStr->str = e->mtext->TrimStart(vstr->ToCharArray());
			xStr->str = xStr->str->TrimEnd(vstr->ToCharArray());
			xStr->self = true;
			String^ sStr = (System::Convert::ToString(xStr->str->Length))->PadLeft(5, '0');
			String^ tStr = "!chat!" + sStr + xStr->str;
			toSend = ac->GetByteCount (tStr->ToCharArray(), 0, tStr->Length);
			
			delete ac;
			delete sStr;
			delete vstr;
			
			if (toSend > 11) {
				array<Byte>^ buffer = gcnew array<Byte>(toSend);
				ac->GetBytes (tStr, 0, toSend, buffer, 0);

				if (buddy->sSocket) {
					buddy->sSocket->SendTimeout = 2500;
					while (toSend) {
						try {
							sent = buddy->sSocket->Send(buffer, offset, toSend, 
								System::Net::Sockets::SocketFlags::None);	
						}
						catch (System::Net::Sockets::SocketException ^ e) {
								break;
						}
						catch (System::ObjectDisposedException^ e) {
								break;
						}
							
						toSend -= sent;
						offset += sent;
					}
				} 
				//FIXME: per message setup
				/*else if (buddy->rSocket) {
					buddy->rSocket->SendTimeout = 2000;
					while (toSend) {
						try {
							sent = buddy->rSocket->Send(buffer, offset, toSend, 
									System::Net::Sockets::SocketFlags::None);	
						}
						catch (System::Net::Sockets::SocketException ^ e) {
							break;
						}
						catch (System::ObjectDisposedException^ e) {
							break;
						}
						
						toSend -= sent;
						offset += sent;
					}
				}*/

				buddy->iMsgs->Add(xStr);
				buddy->pendingRead++;

				if (toSend == 0) {
					xStr->sent = true;
				}
				//FIXME: per message setup
				//else 
				{
					if (buddy->sSocket){
						try {
							buddy->sSocket->Shutdown (System::Net::Sockets::SocketShutdown::Both);
						}
						catch (System::Net::Sockets::SocketException^ e) {
						}
						try {
							buddy->sSocket->Close(false);
						}
						catch (System::Net::Sockets::SocketException^ e) {
						}
						delete buddy->sSocket;
						buddy->sSocket = nullptr;
					}

					//FIXME: per message setup
					/*if (buddy->rSocket) {
						try {
							buddy->rSocket->Close(false);
						}
						catch (System::Net::Sockets::SocketException^ e) {
						}
						delete buddy->rSocket;
						buddy->rSocket = nullptr;
					} 

					buddy->totalMsgLength = 0;
					buddy->dataSize = 0;
					buddy->buffer->Resize (buddy->buffer, 2048);
					buddy->buffer->Clear (buddy->buffer, 0, 2048); */
				}

				delete buffer;
				
				updateTextBox (buddy, false);
					
			} else {
				if (tStr)
					delete tStr;
				if (xStr) {
					if (xStr->str)
						delete xStr->str;
					delete xStr;
				}
			}

			delete e;
			}
		}
		private: System::Void listBox1_selectedIndexChanged (System::Object^  sender, System::EventArgs^  e) {
			this->listBox1->Update();
			this->listBox1->Refresh();
		}
		private: System::Void textBox3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
					 
		}
		private: System::Void contextMenu1_itemClicked (System::Object^ sender, System::Windows::Forms::ToolStripItemClickedEventArgs^ e) {
			Chatmasala::Buddy^ buddy = dynamic_cast<Chatmasala::Buddy^>(this->listBox1->SelectedItem);
			if (buddy) {	
				switch (this->contextMenu1->Items->IndexOf (e->ClickedItem)) {
					case 0: {
						Chatmasala::Form3^ form3;
						if (buddy->form3 == nullptr) {
							form3 = gcnew Chatmasala::Form3(buddy);
							buddy->form3 = form3;
							form3->sendData += gcnew Chatmasala::Form3::sendDataHandler (this, &Form1::send_Data);
							form3->Show();
							updateTextBox (buddy, true);
						} else {
							form3 = dynamic_cast<Chatmasala::Form3^>(buddy->form3);
							form3->WindowState = System::Windows::Forms::FormWindowState::Normal;
							form3->Update();
							form3->ResumeLayout();
						}
					}
					break;

					case 1:
						MessageBox::Show (buddy->name + System::Environment::NewLine + "IP: " + buddy->ip);
					break;

					case 2: {
						Chatmasala::Form2^ form2 = gcnew Chatmasala::Form2(buddy->ip, this->listBox1->SelectedIndex);
						form2->aliasUpdated += gcnew Chatmasala::Form2::aliasUpdateHandler (this, &Form1::updatedAlias);
						form2->Show();
					}
					break;

					case 3: {
						int index  = this->listBox1->Items->IndexOf (buddy);
						this->listBox1->Items->Remove(buddy);
						delete buddy;
						this->listBox1->Update();
						this->listBox1->Refresh();
						if (index < this->listBox1->Items->Count)
							this->listBox1->SetSelected (index, true);
						else if (this->listBox1->Items->Count > 0)
							this->listBox1->SetSelected(0, true);
					}
					break;

					case 4:
					break;

					default:
					break;
				}
			}
		}
		private: System::Void form1_Resized (System::Object^ sender, System::EventArgs^ e)
		{ 
			if (this->WindowState == System::Windows::Forms::FormWindowState::Minimized) {
				
			} else {

			}
		}
		private: System::Void textBox3_KeyDown (System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			if (e->KeyCode == System::Windows::Forms::Keys::Enter) {
				if (this->textBox3->Text) {
						System::Net::IPAddress^ ip;
						
						try {
							ip = System::Net::IPAddress::Parse(this->textBox3->Text);
						}
						catch ( ArgumentNullException^ e ) {
      
						}
						catch ( FormatException^ e ) {
     
						}
						catch ( Exception^ e ) {
						
						}
						if (ip) {
							Chatmasala::Buddy^ bd = gcnew Chatmasala::Buddy(this, ip->ToString());
							this->addBuddy (bd);
						}
						e->Handled = true;
						this->textBox3->Clear();
				}
			}
		}
	};
#endif
}

