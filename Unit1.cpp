//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Counter = 0;
	Button1->Enabled = false;
	Button2->Enabled = true;

	URLS = new TStringList();
	URLS->LoadFromFile("urls.txt");

	Words = new TStringList();
	Words->LoadFromFile("words.txt");

	randomize();

	Timer1->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Button1->Enabled = true;
	Button2->Enabled = false;

	Timer1->Enabled = false;

	delete Words;
	delete URLS;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	AnsiString ActMessage;
	AnsiString action = " Войти ";
	AnsiString login;
	AnsiString password;
	AnsiString url;



	// Generate data

	login = Words->Strings[rand()%Words->Count];
	password = Words->Strings[rand()%Words->Count];

	// Send data
	TStrings *Param = new TStringList();
	TStringStream *Answer = new TStringStream();

	Param->Add("Auth=submit");
	Param->Add("Login=" + login);
	Param->Add("password=" + password);
	Param->Add("login=" + login);
	Param->Add("pwd=" + password);
	Param->Add("pass=" + password);
	Param->Add("passw=" + password);
	// URL
	url = URLS->Strings[rand()%URLS->Count];

	Counter++;
	ActMessage = String(Counter) + " ;To: " + url + " ;Login: " + login + " ;Password: " + password;

	try
	{
		IdHTTP1->Request->ContentType = "text/html";
//		IdHTTP1->Post("http://auth.mail.ru/cgi-bin/auth", Param, Answer);
		IdHTTP1->Post(url, Param, Answer);
		ActMessage += " - PASS";
	}
	catch(...)
	{
		ActMessage += " - FAIL";
	}
	Memo1->Lines->Add(ActMessage);

	delete Param;
	delete Answer;
}
//---------------------------------------------------------------------------
