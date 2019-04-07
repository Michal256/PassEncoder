//© All rights reserved @2018. Appliaction "PassEncoder" Author: Michał Ziółek.
//Application is using Simple and Fast Multimedia Library (SFML).
//Application is using OpenSSL toolkit, see OpenSSL toolkit license in openssl_toolkit_license.txt file.
/*
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <iostream>
#include <SFML\Graphics.hpp>
#include <windows.h>
#include <string>
#include <fstream>
#include <openssl/sha.h>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <SFML\Window\Event.hpp>
#include <stdio.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;
using std::stringstream;
using std::ios;
using std::getline;
using std::fstream;


string *readFile(int number);
string *separators(string note);

void writeInBoxWithoutProblems(float localBoundsText,float localBoundsBox,sf::String &contentBottomBox, sf::String &contentBottomBoxMemory,sf::Event event, sf::Text &textBottomBox,sf::String &contentBottomBoxFull);
void addToFile(sf::String &id, sf::String &pass, sf::String &fileName, sf::String &note, sf::String &noteKey,string &password);

void sha256(char *data, char outputBuffer[65]);
void encryptData(string &data,string &password,bool decrypt);
void checkFile(int &numberOfFiles);
void delFile(short int number,int &numberOfFiles,int &nNextFile);

string *checkFileName(int numberOfFiles);

void reNumE(string *tab, int numberOfFiles,string password,string TNpassword);

int main()
{
	cout << std::setprecision(100000);
	sf::Vector2i vc1(800, 600);
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(vc1.x, vc1.y), "PassEncoder",sf::Style::Titlebar|sf::Style::Close);
	sf::Font font;
	if (!font.loadFromFile("img/lucon.ttf"))
	{
		system("pause");
		exit(0);
	}
	sf::Texture tlo;
	if (!tlo.loadFromFile("img/tlo.png"))
	{
		system("pause");
		exit(0);
	}
	
	sf::Sprite spritetlo;
	spritetlo.setTexture(tlo);


	sf::Texture lupa;
	if (!lupa.loadFromFile("img/lupa.png"))
	{
		system("pause");
		exit(0);
	}
	sf::Sprite spritelupa;
	spritelupa.setTexture(lupa);
	spritelupa.setPosition(345, 540);

	sf::RectangleShape header(sf::Vector2f(800, 30));
	header.setPosition(0, 0);
	header.setFillColor(sf::Color(220, 220, 220));
	header.setOutlineColor(sf::Color(150, 150, 150));
	header.setOutlineThickness(5);

	sf::String hcontent = L"PassEncoder";
	sf::Text htext(hcontent, font, 20);
	htext.setPosition(335, 5);
	htext.setColor(sf::Color::Black);
	htext.setStyle(sf::Text::Bold|sf::Text::Italic);

	sf::String hcontent2 = L"©Copyright Michał Ziółek";
	sf::Text htext2(hcontent2, font, 14);
	htext2.setPosition(570, 8);
	htext2.setColor(sf::Color(4,44,99));
	htext2.setStyle(sf::Text::Bold);


//TRYB LOGIN=0 MENU=1 ADD=2 P=3
	short int tryb = 0;

//------------------------Zmienne Tryb 1
	bool bottomBoxAllow = false;
	bool changeFileBut = false;
	bool askMouse = false;
	bool chPassAdd = false;
	short int numberChangeFile = -1;
	int nNextFile = 0;
	int numberOfFiles = 0;
	int found = -1;
	string password = "abcd";
	bool searchFound = false;
//---
//-------------------------------------------------------MENU
//-----------------------------------------------------------
	sf::RectangleShape leftmBox1(sf::Vector2f(270, 56.25));
	leftmBox1.setPosition(0, 35);
	leftmBox1.setFillColor(sf::Color(170, 170, 170,190));
	leftmBox1.setOutlineThickness(0);

	sf::RectangleShape leftmBox2(sf::Vector2f(270, 56.25));
	leftmBox2.setPosition(0, 96.25);
	leftmBox2.setFillColor(sf::Color(170, 170, 170, 190));
	leftmBox2.setOutlineThickness(0);

	sf::RectangleShape leftmBox3(sf::Vector2f(270, 56.25));
	leftmBox3.setPosition(0, 157.5);
	leftmBox3.setFillColor(sf::Color(170, 170, 170, 190));
	leftmBox3.setOutlineThickness(0);

	sf::RectangleShape leftmBox4(sf::Vector2f(270, 56.25));
	leftmBox4.setPosition(0, 218.75);
	leftmBox4.setFillColor(sf::Color(170, 170, 170, 190));
	leftmBox4.setOutlineThickness(0);

	sf::RectangleShape leftmBox5(sf::Vector2f(270, 56.25));
	leftmBox5.setPosition(0, 280);
	leftmBox5.setFillColor(sf::Color(170, 170, 170, 190));
	leftmBox5.setOutlineThickness(0);

	sf::RectangleShape leftmBox6(sf::Vector2f(270, 56.25));
	leftmBox6.setPosition(0, 341.25);
	leftmBox6.setFillColor(sf::Color(170, 170, 170, 190));
	leftmBox6.setOutlineThickness(0);

	sf::RectangleShape leftmBox7(sf::Vector2f(270, 56.25));
	leftmBox7.setPosition(0, 402.5);
	leftmBox7.setFillColor(sf::Color(170, 170, 170, 190));
	leftmBox7.setOutlineThickness(0);

	sf::RectangleShape leftmBox8(sf::Vector2f(270, 56.25));
	leftmBox8.setPosition(0, 463.75);
	leftmBox8.setFillColor(sf::Color(170, 170, 170, 190));
	leftmBox8.setOutlineThickness(0);

	sf::String contentLeftmBox1 = L"Plik1";
	sf::Text textLeftmBox1(contentLeftmBox1, font, 20);
	textLeftmBox1.setPosition(5, 50);
	textLeftmBox1.setColor(sf::Color::White);
	textLeftmBox1.setStyle(sf::Text::Bold);
	
	sf::RectangleShape Leftboxes[8] = { leftmBox1,leftmBox2,leftmBox3,leftmBox4,leftmBox5,leftmBox6,leftmBox7,leftmBox8};

	sf::String contentLeftmBox2 = L"Plik2";
	sf::Text textLeftmBox2(contentLeftmBox2, font, 20);
	textLeftmBox2.setPosition(5, 111.25);
	textLeftmBox2.setColor(sf::Color::White);
	textLeftmBox2.setStyle(sf::Text::Bold);

	sf::String contentLeftmBox3 = L"Plik3";
	sf::Text textLeftmBox3(contentLeftmBox3, font, 20);
	textLeftmBox3.setPosition(5, 172.5);
	textLeftmBox3.setColor(sf::Color::White);
	textLeftmBox3.setStyle(sf::Text::Bold);

	sf::String contentLeftmBox4 = L"Plik4";
	sf::Text textLeftmBox4(contentLeftmBox4, font, 20);
	textLeftmBox4.setPosition(5, 233.75);
	textLeftmBox4.setColor(sf::Color::White);
	textLeftmBox4.setStyle(sf::Text::Bold);

	sf::String contentLeftmBox5 = L"Plik5";
	sf::Text textLeftmBox5(contentLeftmBox5, font, 20);
	textLeftmBox5.setPosition(5, 295);
	textLeftmBox5.setColor(sf::Color::White);
	textLeftmBox5.setStyle(sf::Text::Bold);

	sf::String contentLeftmBox6 = L"Plik6";
	sf::Text textLeftmBox6(contentLeftmBox6, font, 20);
	textLeftmBox6.setPosition(5, 356.25);
	textLeftmBox6.setColor(sf::Color::White);
	textLeftmBox6.setStyle(sf::Text::Bold);

	sf::String contentLeftmBox7 = L"Plik7";
	sf::Text textLeftmBox7(contentLeftmBox7, font, 20);
	textLeftmBox7.setPosition(5, 417.5);
	textLeftmBox7.setColor(sf::Color::White);
	textLeftmBox7.setStyle(sf::Text::Bold);

	sf::String contentLeftmBox8 = L"Plik8";
	sf::Text textLeftmBox8(contentLeftmBox8, font, 20);
	textLeftmBox8.setPosition(5, 478.75);
	textLeftmBox8.setColor(sf::Color::White);
	textLeftmBox8.setStyle(sf::Text::Bold);

//---------------------------------------------------------------
	sf::RectangleShape leftmBorder(sf::Vector2f(270, 5));
	leftmBorder.setPosition(0, 520);
	leftmBorder.setFillColor(sf::Color(150, 150, 150));
	leftmBorder.setOutlineThickness(0);

	sf::RectangleShape rightBox(sf::Vector2f(520, 485));
	rightBox.setPosition(275, 35);
	rightBox.setFillColor(sf::Color(200, 200, 200));
	rightBox.setOutlineColor(sf::Color(150, 150, 150));
	rightBox.setOutlineThickness(5);

	sf::RectangleShape bottomBox(sf::Vector2f(320, 45));
	bottomBox.setPosition(15, 540);
	bottomBox.setFillColor(sf::Color(220, 220, 220,200));
	bottomBox.setOutlineThickness(0);

	sf::RectangleShape bottomBoxAdd(sf::Vector2f(90, 45));
	bottomBoxAdd.setPosition(405, 540);
	bottomBoxAdd.setFillColor(sf::Color(95, 95, 95,200));
	bottomBoxAdd.setOutlineThickness(0);

	sf::RectangleShape bottomBoxDel(sf::Vector2f(90, 45));
	bottomBoxDel.setPosition(510, 540);
	bottomBoxDel.setFillColor(sf::Color(95, 95, 95, 200));
	bottomBoxDel.setOutlineThickness(0);

	sf::RectangleShape bottomBoxcp(sf::Vector2f(45, 45));
	bottomBoxcp.setPosition(615, 540);
	bottomBoxcp.setFillColor(sf::Color(95, 95, 95, 200));
	bottomBoxcp.setOutlineThickness(0);

	sf::RectangleShape bottomBoxExit(sf::Vector2f(110, 55));
	bottomBoxExit.setPosition(675, 535);
	bottomBoxExit.setFillColor(sf::Color(175, 175, 30, 200));
	bottomBoxExit.setOutlineThickness(0);

	sf::String contentBottomBox = L"";
	sf::String contentBottomBoxMemory = L"";
	sf::String contentBottomBoxFull = L"";
	sf::Text textBottomBox(contentBottomBox, font, 23);
	textBottomBox.setPosition(20, 547);
	textBottomBox.setColor(sf::Color::Black);
	textBottomBox.setStyle(sf::Text::Bold|sf::Text::Italic);

	sf::String contentadd = L"Add";
	sf::Text textadd(contentadd, font, 20);
	textadd.setPosition(430, 550);
	textadd.setColor(sf::Color::White);
	textadd.setStyle(sf::Text::Bold);

	sf::String contentdel = L"Del";
	sf::Text textdel(contentdel, font, 20);
	textdel.setPosition(536, 550);
	textdel.setColor(sf::Color::White);
	textdel.setStyle(sf::Text::Bold);

	sf::String contentpass = L"P";
	sf::Text textpass(contentpass, font, 20);
	textpass.setPosition(631, 550);
	textpass.setColor(sf::Color::White);
	textpass.setStyle(sf::Text::Bold);

	sf::String contentExit = L"Log-out\nExit";
	sf::Text textExit(contentExit, font, 20);
	textExit.setPosition(683, 538);
	textExit.setColor(sf::Color::White);
	textExit.setStyle(sf::Text::Bold);





	//---------------------------------------------------------------------------------------------

	sf::RectangleShape addIdBoxMenu(sf::Vector2f(490, 35));
	addIdBoxMenu.setPosition(290, 100);
	addIdBoxMenu.setFillColor(sf::Color(100, 100, 100, 150));
	addIdBoxMenu.setOutlineThickness(0);

	sf::RectangleShape addPassBoxMenu(sf::Vector2f(490, 35));
	addPassBoxMenu.setPosition(290, 200);
	addPassBoxMenu.setFillColor(sf::Color(100, 100, 100, 150));
	addPassBoxMenu.setOutlineThickness(0);


	sf::RectangleShape addNoteBoxMenu(sf::Vector2f(490, 35));
	addNoteBoxMenu.setPosition(290, 300);
	addNoteBoxMenu.setFillColor(sf::Color(100, 100, 100, 150));
	addNoteBoxMenu.setOutlineThickness(0);

	sf::RectangleShape addNoteKeyBoxMenu(sf::Vector2f(490, 35));
	addNoteKeyBoxMenu.setPosition(290, 400);
	addNoteKeyBoxMenu.setFillColor(sf::Color(100, 100, 100, 150));
	addNoteKeyBoxMenu.setOutlineThickness(0);

	//10px odstepu od ramki
	sf::String contentaddIdBoxMenuF = L"ID:";

	sf::Text textaddIdBoxMenuF(contentaddIdBoxMenuF, font, 25);
	textaddIdBoxMenuF.setPosition(300, 65);
	textaddIdBoxMenuF.setColor(sf::Color(18,97,224));
	textaddIdBoxMenuF.setStyle(sf::Text::Bold);

	//10px odstepu od ramki
	sf::String contentaddIdBoxMenu = L"";

	sf::Text textaddIdBoxMenu(contentaddIdBoxMenu, font, 25);
	textaddIdBoxMenu.setPosition(300, 101);
	textaddIdBoxMenu.setColor(sf::Color::White);
	textaddIdBoxMenu.setStyle(sf::Text::Bold);



	sf::String contentaddPassBoxMenuF = L"Password:";
	sf::Text textaddPassBoxMenuF(contentaddPassBoxMenuF, font, 25);
	textaddPassBoxMenuF.setPosition(300, 165);
	textaddPassBoxMenuF.setColor(sf::Color(18, 97, 224));
	textaddPassBoxMenuF.setStyle(sf::Text::Bold);

	sf::String contentaddPassBoxMenu = L"";
	sf::Text textaddPassBoxMenu(contentaddPassBoxMenu, font, 25);
	textaddPassBoxMenu.setPosition(300, 201);
	textaddPassBoxMenu.setColor(sf::Color::White);
	textaddPassBoxMenu.setStyle(sf::Text::Bold);


	sf::String contentaddNoteBoxMenuF = L"Note:";
	sf::Text textaddNoteBoxMenuF(contentaddNoteBoxMenuF, font, 25);
	textaddNoteBoxMenuF.setPosition(300, 265);
	textaddNoteBoxMenuF.setColor(sf::Color(18, 97, 224));
	textaddNoteBoxMenuF.setStyle(sf::Text::Bold);

	sf::String contentaddNoteBoxMenu = L"";
	sf::Text textaddNoteBoxMenu(contentaddNoteBoxMenu, font, 25);
	textaddNoteBoxMenu.setPosition(300, 301);
	textaddNoteBoxMenu.setColor(sf::Color::White);
	textaddNoteBoxMenu.setStyle(sf::Text::Bold);


	sf::String contentaddNoteKeyBoxMenuF = L"Note Key:";

	sf::Text textaddNoteKeyBoxMenuF(contentaddNoteKeyBoxMenuF, font, 25);
	textaddNoteKeyBoxMenuF.setPosition(300, 365);
	textaddNoteKeyBoxMenuF.setColor(sf::Color(18, 97, 224));
	textaddNoteKeyBoxMenuF.setStyle(sf::Text::Bold);


	sf::String contentaddNoteKeyBoxMenu = L"";

	sf::Text textaddNoteKeyBoxMenu(contentaddNoteKeyBoxMenu, font, 25);
	textaddNoteKeyBoxMenu.setPosition(300, 401);
	textaddNoteKeyBoxMenu.setColor(sf::Color::White);
	textaddNoteKeyBoxMenu.setStyle(sf::Text::Bold);


//-------------------------------------------------------------------------------------KONIEC MENU


//Zmienne ADD

	bool idAllow = false, passAllow = false, fileNameAllow = false, noteAllow = false, noteKeyAllow = false;
//------------------------------------------------ADD

	sf::RectangleShape bottomBoxBack(sf::Vector2f(90, 45));
	bottomBoxBack.setPosition(510, 540);
	bottomBoxBack.setFillColor(sf::Color(95, 95, 95, 200));
	bottomBoxBack.setOutlineThickness(0);

	sf::String contentback = L"Back";
	sf::Text textback(contentback, font, 20);
	textback.setPosition(530, 550);
	textback.setColor(sf::Color::White);
	textback.setStyle(sf::Text::Bold);

	sf::String contentaddId = L"ID:";
	sf::Text textaddId(contentaddId, font, 40);
	textaddId.setPosition(195, 45);
	textaddId.setColor(sf::Color::White);
	textaddId.setStyle(sf::Text::Bold);

	sf::String contentaddPass = L"Password:";
	sf::Text textaddPass(contentaddPass, font, 40);
	textaddPass.setPosition(45, 110);
	textaddPass.setColor(sf::Color::White);
	textaddPass.setStyle(sf::Text::Bold);

	sf::String contentaddName = L"File name:";
	sf::Text textaddName(contentaddName, font, 40);
	textaddName.setPosition(20, 220);
	textaddName.setColor(sf::Color::White);
	textaddName.setStyle(sf::Text::Bold);

	sf::String contentaddNote = L"Note:";
	sf::Text textaddNote(contentaddNote, font, 40);
	textaddNote.setPosition(145, 285);
	textaddNote.setColor(sf::Color::White);
	textaddNote.setStyle(sf::Text::Bold);

	sf::String contentaddNoteKey = L"Note Key:";
	sf::Text textaddNoteKey(contentaddNoteKey, font, 40);
	textaddNoteKey.setPosition(45, 350);
	textaddNoteKey.setColor(sf::Color::White);
	textaddNoteKey.setStyle(sf::Text::Bold);





	sf::RectangleShape addIdBox(sf::Vector2f(490, 35));
	addIdBox.setPosition(290, 55);
	addIdBox.setFillColor(sf::Color(100, 100, 100, 150));
	addIdBox.setOutlineThickness(0);


	//10px odstepu od ramki
	sf::String contentaddIdBox = L"";
	sf::String contentaddIdBoxMemory = L"";
	sf::String contentaddIdBoxFull = L"";
	sf::Text textaddIdBox(contentaddIdBox, font, 25);
	textaddIdBox.setPosition(300, 56);
	textaddIdBox.setColor(sf::Color::White);
	textaddIdBox.setStyle(sf::Text::Bold);



	sf::RectangleShape addPassBox(sf::Vector2f(490, 35));
	addPassBox.setPosition(290, 120);
	addPassBox.setFillColor(sf::Color(100, 100, 100, 150));
	addPassBox.setOutlineThickness(0);

	sf::String contentaddPassBox = L"";
	sf::String contentaddPassBoxMemory = L"";
	sf::String contentaddPassBoxFull = L"";
	sf::Text textaddPassBox(contentaddPassBox, font, 25);
	textaddPassBox.setPosition(300, 121);
	textaddPassBox.setColor(sf::Color::White);
	textaddPassBox.setStyle(sf::Text::Bold);



	sf::RectangleShape addFileNameBox(sf::Vector2f(490, 35));
	addFileNameBox.setPosition(290, 230);
	addFileNameBox.setFillColor(sf::Color(100, 100, 100, 150));
	addFileNameBox.setOutlineThickness(0);

	sf::String contentaddNameBox = L"";
	sf::String contentaddNameBoxMemory = L"";
	sf::String contentaddNameBoxFull = L"";
	sf::Text textaddNameBox(contentaddNameBox, font, 25);
	textaddNameBox.setPosition(300, 231);
	textaddNameBox.setColor(sf::Color::White);
	textaddNameBox.setStyle(sf::Text::Bold);


	sf::RectangleShape addNoteBox(sf::Vector2f(490, 35));
	addNoteBox.setPosition(290, 295);
	addNoteBox.setFillColor(sf::Color(100, 100, 100, 150));
	addNoteBox.setOutlineThickness(0);

	sf::String contentaddNoteBox = L"";
	sf::String contentaddNoteBoxMemory = L"";
	sf::String contentaddNoteBoxFull = L"";
	sf::Text textaddNoteBox(contentaddNoteBox, font, 25);
	textaddNoteBox.setPosition(300, 296);
	textaddNoteBox.setColor(sf::Color::White);
	textaddNoteBox.setStyle(sf::Text::Bold);

	sf::RectangleShape addNoteKeyBox(sf::Vector2f(490, 35));
	addNoteKeyBox.setPosition(290, 360);
	addNoteKeyBox.setFillColor(sf::Color(100, 100, 100, 150));
	addNoteKeyBox.setOutlineThickness(0);

	sf::String contentaddNoteKeyBox = L"";
	sf::String contentaddNoteKeyBoxMemory = L"";
	sf::String contentaddNoteKeyBoxFull = L"";
	sf::Text textaddNoteKeyBox(contentaddNoteKeyBox, font, 25);
	textaddNoteKeyBox.setPosition(300, 361);
	textaddNoteKeyBox.setColor(sf::Color::White);
	textaddNoteKeyBox.setStyle(sf::Text::Bold);
//------------------------------------------------KONIEC ADD
	bool rePass = false;
	bool chPass = false;
//------------------------------------------------Start Change Pass
	sf::String contentChange = L"Change";
	sf::Text textChange(contentChange, font, 20);
	textChange.setPosition(412, 550);
	textChange.setColor(sf::Color::White);
	textChange.setStyle(sf::Text::Bold);

	sf::RectangleShape bottomBoxChange(sf::Vector2f(90, 45));
	bottomBoxChange.setPosition(405, 540);
	bottomBoxChange.setFillColor(sf::Color(95, 95, 95, 200));
	bottomBoxChange.setOutlineThickness(0);


	sf::String contentaddPass1 = L"Your Password:";
	sf::Text textaddPass1(contentaddPass1, font, 30);
	textaddPass1.setPosition(5, 52);
	textaddPass1.setColor(sf::Color::White);
	textaddPass1.setStyle(sf::Text::Bold);

	sf::String contentaddPassNew = L"New Password:";
	sf::Text textaddPassNew(contentaddPassNew, font, 30);
	textaddPassNew.setPosition(23, 117);
	textaddPassNew.setColor(sf::Color::White);
	textaddPassNew.setStyle(sf::Text::Bold);

	sf::String contentaddPassNewRe = L"Repeat new\n password:";
	sf::Text textaddPassNewRe(contentaddPassNewRe, font, 30);
	textaddPassNewRe.setPosition(70, 182);
	textaddPassNewRe.setColor(sf::Color::White);
	textaddPassNewRe.setStyle(sf::Text::Bold);

	sf::RectangleShape addPassNewReBox(sf::Vector2f(490, 35));
	addPassNewReBox.setPosition(290, 210);
	addPassNewReBox.setFillColor(sf::Color(100, 100, 100, 150));
	addPassNewReBox.setOutlineThickness(0);


	//------------------------

	sf::String contentaddPass1F = L"";
	sf::String contentaddPass1FMemory = L"";
	sf::String contentaddPass1FFull = L"";

	sf::Text textaddPass1F(contentaddPass1F, font, 25);
	textaddPass1F.setPosition(300, 56);
	textaddPass1F.setColor(sf::Color::White);
	textaddPass1F.setStyle(sf::Text::Bold);



	sf::String contentaddPass1FNew = L"";
	sf::String contentaddPass1FMemoryNew = L"";
	sf::String contentaddPass1FFullNew = L"";

	sf::Text textaddPass1FNew(contentaddPass1FNew, font, 25);
	textaddPass1FNew.setPosition(300, 121);
	textaddPass1FNew.setColor(sf::Color::White);
	textaddPass1FNew.setStyle(sf::Text::Bold);



	sf::String contentaddPass1FNewRe = L"";
	sf::String contentaddPass1FMemoryNewRe = L"";
	sf::String contentaddPass1FFullNewRe = L"";

	sf::Text textaddPass1FNewRe(contentaddPass1FNewRe, font, 25);
	textaddPass1FNewRe.setPosition(300,211);
	textaddPass1FNewRe.setColor(sf::Color::White);
	textaddPass1FNewRe.setStyle(sf::Text::Bold);


	//--------------------------



//------------------------------------------------END OF CHANGE PASS
	bool passLoginAllow = false;
	short int howManyTimes = 1;
//------------------------------------------------Log in
	sf::String contentLogin = L"Sign in";
	sf::Text textLogin(contentLogin, font, 20);
	textLogin.setPosition(409, 550);
	textLogin.setColor(sf::Color::White);
	textLogin.setStyle(sf::Text::Bold);

	sf::RectangleShape bottomBoxLogin(sf::Vector2f(100, 55));
	bottomBoxLogin.setPosition(405, 535);
	bottomBoxLogin.setFillColor(sf::Color(95, 95, 95, 200));
	bottomBoxLogin.setOutlineThickness(0);
	
	sf::RectangleShape addPassBoxLogin(sf::Vector2f(490, 35));
	addPassBoxLogin.setPosition(290, 55);
	addPassBoxLogin.setFillColor(sf::Color(100, 100, 100, 150));
	addPassBoxLogin.setOutlineThickness(0);

	sf::String contentaddPassLogin = L"Password:";
	sf::Text textaddPassLogin(contentaddPassLogin, font, 40);
	textaddPassLogin.setPosition(45, 45);
	textaddPassLogin.setColor(sf::Color::White);
	textaddPassLogin.setStyle(sf::Text::Bold);

	sf::String contentPassLogin = L"";
	sf::String contentPassLoginMemory = L"";
	sf::String contentPassLoginFull = L"";

	sf::Text textPassLogin(contentPassLogin, font, 25);

	textPassLogin.setPosition(300, 56);
	textPassLogin.setColor(sf::Color::White);
	textPassLogin.setStyle(sf::Text::Bold);

	//spr ile jest plikow
	checkFile(numberOfFiles);
	string *tabN=checkFileName(numberOfFiles);


//------------------------------------------------END Log in

	while (Window.isOpen())
	{
		sf::Event event;
		while (Window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					Window.close();
					break;
				}
				case sf::Event::MouseButtonPressed:
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						sf::Vector2i mms(0, 0);
						mms.x = event.mouseButton.x;
						mms.y = event.mouseButton.y;


						if (mms.x >= 675 && mms.x <= 785 && mms.y >= 535 && mms.y <= 590)
						{
							exit(0);
						}
						else
						{
//TRYB 1 MOUSE-------------------------------------------------------------------------------
							if (tryb == 1)
							{
								if (mms.x >= 15 && mms.x <= 335 && mms.y >= 540 && mms.y <= 585)
								{
									
									
									bottomBox.setFillColor(sf::Color(78, 191, 70, 255));
									bottomBoxAllow = true;
									
									
								}
								else if (mms.x >= 345 && mms.x <= 385 && mms.y >= 540 && mms.y <= 580)
								{
									string *tab = new string[numberOfFiles];
									tab = checkFileName(numberOfFiles);
									
									string contentBottomBoxFullS = contentBottomBoxFull;
									bool prefound = false;
									int i = 0;
									if (searchFound == true)
									{
										prefound = true;
										if (found < numberOfFiles)
										{
											i = found;
										}
										found = -1;
										searchFound = false;
									}
									
									while(i<numberOfFiles&&searchFound!=true)
									{
										encryptData(tab[i], password, true);

										int contentLength = contentBottomBoxFullS.length();
										int tempTabLength = tab[i].length();

										if (tempTabLength >= contentLength)
										{
											bool similar = true;
											for (int x = 0; x < contentLength; x++)
											{

												if (tab[i][x] != contentBottomBoxFullS[x])
												{
													similar = false;
													break;
												}
											}
											if (similar == true)
											{
												found = i + 1;
												searchFound = true;
												nNextFile = 0;
												numberChangeFile = -1;

												changeFileBut = true;
												if (found > 8)
												{
													nNextFile = found - 8;
												}

												if (found > 8)
												{
													numberChangeFile = found-nNextFile - 1;
												}
												else
												{
													numberChangeFile = found - 1;
												}

												if (numberChangeFile == 0)
												{
													leftmBox1.setFillColor(sf::Color(28, 169, 230, 230));

													string *tab = readFile(1 + nNextFile);

													encryptData(tab[0], password, true);
													encryptData(tab[1], password, true);
													encryptData(tab[2], password, true);
													encryptData(tab[3], password, true);
													encryptData(tab[4], password, true);
													encryptData(tab[5], password, true);
													encryptData(tab[6], password, true);
													encryptData(tab[7], password, true);

													textaddIdBoxMenu.setString(tab[0]);
													textaddPassBoxMenu.setString(tab[1]);
													textaddNoteBoxMenu.setString(tab[2] +'|'+ tab[3] + '|' + tab[4]);
													textaddNoteKeyBoxMenu.setString(tab[5] + '|' + tab[6] + '|' + tab[7]);

													delete[] tab;
												}
												else if (numberChangeFile == 1)
												{
													leftmBox2.setFillColor(sf::Color(28, 169, 230, 230));

													string *tab = readFile(2 + nNextFile);

													encryptData(tab[0], password, true);
													encryptData(tab[1], password, true);
													encryptData(tab[2], password, true);
													encryptData(tab[3], password, true);
													encryptData(tab[4], password, true);
													encryptData(tab[5], password, true);
													encryptData(tab[6], password, true);
													encryptData(tab[7], password, true);

													textaddIdBoxMenu.setString(tab[0]);
													textaddPassBoxMenu.setString(tab[1]);
													textaddNoteBoxMenu.setString(tab[2] + '|' + tab[3] + '|' + tab[4]);
													textaddNoteKeyBoxMenu.setString(tab[5] + '|' + tab[6] + '|' + tab[7]);

													delete[] tab;
												}
												else if (numberChangeFile == 2)
												{
													leftmBox3.setFillColor(sf::Color(28, 169, 230, 230));

													string *tab = readFile(3 + nNextFile);

													encryptData(tab[0], password, true);
													encryptData(tab[1], password, true);
													encryptData(tab[2], password, true);
													encryptData(tab[3], password, true);
													encryptData(tab[4], password, true);
													encryptData(tab[5], password, true);
													encryptData(tab[6], password, true);
													encryptData(tab[7], password, true);

													textaddIdBoxMenu.setString(tab[0]);
													textaddPassBoxMenu.setString(tab[1]);
													textaddNoteBoxMenu.setString(tab[2] + '|' + tab[3] + '|' + tab[4]);
													textaddNoteKeyBoxMenu.setString(tab[5] + '|' + tab[6] + '|' + tab[7]);

													delete[] tab;
												}
												else if (numberChangeFile == 3)
												{
													leftmBox4.setFillColor(sf::Color(28, 169, 230, 230));

													string *tab = readFile(4 + nNextFile);

													encryptData(tab[0], password, true);
													encryptData(tab[1], password, true);
													encryptData(tab[2], password, true);
													encryptData(tab[3], password, true);
													encryptData(tab[4], password, true);
													encryptData(tab[5], password, true);
													encryptData(tab[6], password, true);
													encryptData(tab[7], password, true);

													textaddIdBoxMenu.setString(tab[0]);
													textaddPassBoxMenu.setString(tab[1]);
													textaddNoteBoxMenu.setString(tab[2] + '|' + tab[3] + '|' + tab[4]);
													textaddNoteKeyBoxMenu.setString(tab[5] + '|' + tab[6] + '|' + tab[7]);

													delete[] tab;

												}
												else if (numberChangeFile == 4)
												{
													leftmBox5.setFillColor(sf::Color(28, 169, 230, 230));
													
													string *tab = readFile(5 + nNextFile);

													encryptData(tab[0], password, true);
													encryptData(tab[1], password, true);
													encryptData(tab[2], password, true);
													encryptData(tab[3], password, true);
													encryptData(tab[4], password, true);
													encryptData(tab[5], password, true);
													encryptData(tab[6], password, true);
													encryptData(tab[7], password, true);

													textaddIdBoxMenu.setString(tab[0]);
													textaddPassBoxMenu.setString(tab[1]);
													textaddNoteBoxMenu.setString(tab[2] + '|' + tab[3] + '|' + tab[4]);
													textaddNoteKeyBoxMenu.setString(tab[5] + '|' + tab[6] + '|' + tab[7]);

													delete[] tab;
												}
												else if (numberChangeFile == 5)
												{
													leftmBox6.setFillColor(sf::Color(28, 169, 230, 230));

													string *tab = readFile(6 + nNextFile);

													encryptData(tab[0], password, true);
													encryptData(tab[1], password, true);
													encryptData(tab[2], password, true);
													encryptData(tab[3], password, true);
													encryptData(tab[4], password, true);
													encryptData(tab[5], password, true);
													encryptData(tab[6], password, true);
													encryptData(tab[7], password, true);

													textaddIdBoxMenu.setString(tab[0]);
													textaddPassBoxMenu.setString(tab[1]);
													textaddNoteBoxMenu.setString(tab[2] + '|' + tab[3] + '|' + tab[4]);
													textaddNoteKeyBoxMenu.setString(tab[5] + '|' + tab[6] + '|' + tab[7]);

													delete[] tab;
												}
												else if (numberChangeFile == 6)
												{
													leftmBox7.setFillColor(sf::Color(28, 169, 230, 230));

													string *tab = readFile(7 + nNextFile);

													encryptData(tab[0], password, true);
													encryptData(tab[1], password, true);
													encryptData(tab[2], password, true);
													encryptData(tab[3], password, true);
													encryptData(tab[4], password, true);
													encryptData(tab[5], password, true);
													encryptData(tab[6], password, true);
													encryptData(tab[7], password, true);

													textaddIdBoxMenu.setString(tab[0]);
													textaddPassBoxMenu.setString(tab[1]);
													textaddNoteBoxMenu.setString(tab[2] + '|' + tab[3] + '|' + tab[4]);
													textaddNoteKeyBoxMenu.setString(tab[5] + '|' + tab[6] + '|' + tab[7]);

													delete[] tab;
												}
												else if (numberChangeFile == 7)
												{
													leftmBox8.setFillColor(sf::Color(28, 169, 230, 230));

													string *tab = readFile(8 + nNextFile);

													encryptData(tab[0], password, true);
													encryptData(tab[1], password, true);
													encryptData(tab[2], password, true);
													encryptData(tab[3], password, true);
													encryptData(tab[4], password, true);
													encryptData(tab[5], password, true);
													encryptData(tab[6], password, true);
													encryptData(tab[7], password, true);

													textaddIdBoxMenu.setString(tab[0]);
													textaddPassBoxMenu.setString(tab[1]);
													textaddNoteBoxMenu.setString(tab[2] + '|' + tab[3] + '|' + tab[4]);
													textaddNoteKeyBoxMenu.setString(tab[5] + '|' + tab[6] +'|'+ tab[7]);

													delete[] tab;
												}
											}
											else if ((searchFound == false) && (prefound == true)&&(i+1>=numberOfFiles))
											{
												i = -1;
												nNextFile = 0;
												numberChangeFile = -1;
												
											}
										
											
										}
										
										
										i++;
									}
									
									delete[]tab;
									
								}
								else if (mms.x >= 405 && mms.x <= 495 && mms.y >= 540 && mms.y <= 585)
								{
									tryb = 2;
								}
								else if (mms.x >= 510 && mms.x <= 600 && mms.y >= 540 && mms.y <= 585)
								{
									if (numberChangeFile != -1)
									{
										textaddIdBoxMenu.setString("");
										textaddPassBoxMenu.setString("");
										textaddNoteBoxMenu.setString("");
										textaddNoteKeyBoxMenu.setString("");


										contentaddIdBoxMenu = "";
										contentaddPassBoxMenu = "";
										contentaddNoteBoxMenu = "";
										contentaddNoteKeyBoxMenu = "";

										delFile(numberChangeFile, numberOfFiles, nNextFile);
										numberChangeFile = -1;


										chPassAdd = true;
									}
									else
									{
										
									}


									
								}
								else if (mms.x >= 615 && mms.x <= 660 && mms.y >= 540 && mms.y <= 585)
								{
									tryb = 3;
								}


								else if (mms.x >= 0 && mms.x <= 270 && mms.y >= 35 && mms.y <= 91.25&&numberOfFiles>=1)
								{
									leftmBox1.setFillColor(sf::Color(28, 169, 230, 230));
									changeFileBut = true;
									numberChangeFile = 0;
									string *tab= readFile(1+nNextFile); 


									encryptData(tab[0], password, true);
									encryptData(tab[1], password, true);
									encryptData(tab[2], password, true);
									encryptData(tab[3], password, true);
									encryptData(tab[4], password, true);
									encryptData(tab[5], password, true);
									encryptData(tab[6], password, true);
									encryptData(tab[7], password, true);


									textaddIdBoxMenu.setString(tab[0]);
									textaddPassBoxMenu.setString(tab[1]);
									textaddNoteBoxMenu.setString(tab[2] +'|'+ tab[3]+'|'+ tab[4]);
									textaddNoteKeyBoxMenu.setString(tab[5]+'|'+ tab[6]+'|'+ tab[7]);

									delete[] tab;

									
								}
								else if (mms.x >= 0 && mms.x <= 270 && mms.y >= 96.25 && mms.y <= 152.5&&numberOfFiles >= 2)
								{
									leftmBox2.setFillColor(sf::Color(28, 169, 230, 230));
									changeFileBut = true;
									numberChangeFile = 1;
									string *tab = readFile(2+nNextFile);


									encryptData(tab[0], password, true);
									encryptData(tab[1], password, true);
									encryptData(tab[2], password, true);
									encryptData(tab[3], password, true);
									encryptData(tab[4], password, true);
									encryptData(tab[5], password, true);
									encryptData(tab[6], password, true);
									encryptData(tab[7], password, true);

									textaddIdBoxMenu.setString(tab[0]);
									textaddPassBoxMenu.setString(tab[1]);
									textaddNoteBoxMenu.setString(tab[2] + '|' + tab[3] + '|' + tab[4]);
									textaddNoteKeyBoxMenu.setString(tab[5] + '|' +tab[6] + '|' +tab[7]);

									delete[] tab;

									
								}
								else if (mms.x >= 0 && mms.x <= 270 && mms.y >= 157.5 && mms.y <= 213.75&&numberOfFiles >= 3)
								{
									leftmBox3.setFillColor(sf::Color(28, 169, 230, 230));
									changeFileBut = true;
									numberChangeFile = 2;
									string *tab = readFile(3+nNextFile);

									encryptData(tab[0],password,true);
									encryptData(tab[1],password,true);
									encryptData(tab[2],password,true);
									encryptData(tab[3],password,true);
									encryptData(tab[4],password,true);
									encryptData(tab[5],password,true);
									encryptData(tab[6],password,true);
									encryptData(tab[7],password,true);

									textaddIdBoxMenu.setString(tab[0]);
									textaddPassBoxMenu.setString(tab[1]);
									textaddNoteBoxMenu.setString(tab[2] + '|' + tab[3] + '|' + tab[4]);
									textaddNoteKeyBoxMenu.setString(tab[5] + '|' + tab[6] + '|' + tab[7]);

									delete[] tab;
								}
								else if (mms.x >= 0 && mms.x <= 270 && mms.y >= 218.75 && mms.y <= 275 && numberOfFiles >= 4)
								{
									leftmBox4.setFillColor(sf::Color(28, 169, 230, 230));
									changeFileBut = true;
									numberChangeFile =3;
									string *tab = readFile(4+nNextFile);


									encryptData(tab[0], password, true);
									encryptData(tab[1], password, true);
									encryptData(tab[2], password, true);
									encryptData(tab[3], password, true);
									encryptData(tab[4], password, true);
									encryptData(tab[5], password, true);
									encryptData(tab[6], password, true);
									encryptData(tab[7], password, true);

									textaddIdBoxMenu.setString(tab[0]);
									textaddPassBoxMenu.setString(tab[1]);
									textaddNoteBoxMenu.setString(tab[2] + '|' + tab[3] + '|' + tab[4]);
									textaddNoteKeyBoxMenu.setString(tab[5] + '|' + tab[6] + '|' + tab[7]);

									delete[] tab;
								}
								else if (mms.x >= 0 && mms.x <= 270 && mms.y >= 280 && mms.y <= 336.25&&numberOfFiles >= 5)
								{
									leftmBox5.setFillColor(sf::Color(28, 169, 230, 230));
									changeFileBut = true;
									numberChangeFile = 4;
									string *tab = readFile(5+nNextFile);


									encryptData(tab[0], password, true);
									encryptData(tab[1], password, true);
									encryptData(tab[2], password, true);
									encryptData(tab[3], password, true);
									encryptData(tab[4], password, true);
									encryptData(tab[5], password, true);
									encryptData(tab[6], password, true);
									encryptData(tab[7], password, true);

									textaddIdBoxMenu.setString(tab[0]);
									textaddPassBoxMenu.setString(tab[1]);
									textaddNoteBoxMenu.setString(tab[2] + '|' + tab[3] + '|' + tab[4]);
									textaddNoteKeyBoxMenu.setString(tab[5] + '|' + tab[6] + '|' + tab[7]);

									delete[] tab;
								}
								else if (mms.x >= 0 && mms.x <= 270 && mms.y >= 341.25 && mms.y <= 397.5&&numberOfFiles >= 6)
								{
									leftmBox6.setFillColor(sf::Color(28, 169, 230, 230));
									changeFileBut = true;
									numberChangeFile = 5;
									string *tab = readFile(6+nNextFile);


									encryptData(tab[0], password, true);
									encryptData(tab[1], password, true);
									encryptData(tab[2], password, true);
									encryptData(tab[3], password, true);
									encryptData(tab[4], password, true);
									encryptData(tab[5], password, true);
									encryptData(tab[6], password, true);
									encryptData(tab[7], password, true);

									textaddIdBoxMenu.setString(tab[0]);
									textaddPassBoxMenu.setString(tab[1]);
									textaddNoteBoxMenu.setString(tab[2] + '|' + tab[3] + '|' + tab[4]);
									textaddNoteKeyBoxMenu.setString(tab[5] + '|' + tab[6] + '|' + tab[7]);

									delete[] tab;
								}
								else if (mms.x >= 0 && mms.x <= 270 && mms.y >= 402.5 && mms.y <= 458.75&&numberOfFiles >= 7)
								{
									leftmBox7.setFillColor(sf::Color(28, 169, 230, 230));
									changeFileBut = true;
									numberChangeFile = 6;

									string *tab = readFile(7+nNextFile);


									encryptData(tab[0], password, true);
									encryptData(tab[1], password, true);
									encryptData(tab[2], password, true);
									encryptData(tab[3], password, true);
									encryptData(tab[4], password, true);
									encryptData(tab[5], password, true);
									encryptData(tab[6], password, true);
									encryptData(tab[7], password, true);

									textaddIdBoxMenu.setString(tab[0]);
									textaddPassBoxMenu.setString(tab[1]);
									textaddNoteBoxMenu.setString(tab[2] + '|' + tab[3] + '|' + tab[4]);
									textaddNoteKeyBoxMenu.setString(tab[5] + '|' + tab[6] + '|' + tab[7]);

									delete[] tab;
								}
								else if (mms.x >= 0 && mms.x <= 270 && mms.y >= 463.75 && mms.y <= 520 && numberOfFiles >= 8)
								{
									leftmBox8.setFillColor(sf::Color(28, 169, 230, 230));
									changeFileBut = true;
									numberChangeFile = 7;

									string *tab = readFile(8+nNextFile);


									encryptData(tab[0], password, true);
									encryptData(tab[1], password, true);
									encryptData(tab[2], password, true);
									encryptData(tab[3], password, true);
									encryptData(tab[4], password, true);
									encryptData(tab[5], password, true);
									encryptData(tab[6], password, true);
									encryptData(tab[7], password, true);

									textaddIdBoxMenu.setString(tab[0]);
									textaddPassBoxMenu.setString(tab[1]);
									textaddNoteBoxMenu.setString(tab[2] + '|' + tab[3] + '|' + tab[4]);
									textaddNoteKeyBoxMenu.setString(tab[5] + '|' + tab[6] + '|' + tab[7]);

									delete[] tab;
								}
								
								else
								{
									bottomBox.setFillColor(sf::Color(220, 220, 220, 200));
									bottomBoxAllow = false;

								}
								
								if (changeFileBut == true)
								{
									
										if (numberChangeFile != 0)
										{
											leftmBox1.setFillColor(sf::Color(170, 170, 170, 190));
										}

										if (numberChangeFile != 1)
										{
											leftmBox2.setFillColor(sf::Color(170, 170, 170, 190));
										}

										if (numberChangeFile != 2)
										{
											leftmBox3.setFillColor(sf::Color(170, 170, 170, 190));
										}

										if (numberChangeFile != 3)
										{
											leftmBox4.setFillColor(sf::Color(170, 170, 170, 190));
										}

										if (numberChangeFile != 4)
										{
											leftmBox5.setFillColor(sf::Color(170, 170, 170, 190));
										}

										if (numberChangeFile != 5)
										{
											leftmBox6.setFillColor(sf::Color(170, 170, 170, 190));
										}

										if (numberChangeFile != 6)
										{
											leftmBox7.setFillColor(sf::Color(170, 170, 170, 190));
										}

										if (numberChangeFile != 7)
										{
											leftmBox8.setFillColor(sf::Color(170, 170, 170, 190));
										}
									changeFileBut = false;
								}
							}
//TRYB 2 MOUSE-------------------------------------------------------------------------------
							else if (tryb == 2)
							{
										addIdBox.setFillColor(sf::Color(100, 100, 100, 150));
										addPassBox.setFillColor(sf::Color(100, 100, 100, 150));
										addFileNameBox.setFillColor(sf::Color(100, 100, 100, 150));
										addNoteBox.setFillColor(sf::Color(100, 100, 100, 150));
										addNoteKeyBox.setFillColor(sf::Color(100, 100, 100, 150));
										idAllow = false;
										passAllow = false;
										fileNameAllow = false;
										noteAllow = false;
										noteKeyAllow = false;


										if (mms.x >= 290 && mms.x <= 780 && mms.y >= 55 && mms.y <= 90)
										{
											
											addIdBox.setFillColor(sf::Color(78, 191, 70, 255));
											idAllow = true;
										}
										else if (mms.x >= 290 && mms.x <= 780 && mms.y >= 120 && mms.y <= 155)
										{
											
											addPassBox.setFillColor(sf::Color(78, 191, 70, 255));
											passAllow = true;
										}
										else if (mms.x >= 290 && mms.x <= 780 && mms.y >= 230 && mms.y <= 265)
										{
											
											addFileNameBox.setFillColor(sf::Color(78, 191, 70, 255));
											fileNameAllow = true;
										}
										else if (mms.x >= 290 && mms.x <= 780 && mms.y >= 295 && mms.y <= 330)
										{

											addNoteBox.setFillColor(sf::Color(78, 191, 70, 255));
											noteAllow = true;
										}
										else if (mms.x >= 290 && mms.x <= 780 && mms.y >= 360 && mms.y <= 395)
										{

											addNoteKeyBox.setFillColor(sf::Color(78, 191, 70, 255));
											noteKeyAllow = true;
										}
										else if (mms.x >= 405 && mms.x <= 495 && mms.y >= 540 && mms.y <= 585)
										{
											if (contentaddNameBox != ""&&contentaddNameBox!="Added!"&&contentaddNameBox != "File already exists!")
											{
												cout << "Welcome" << endl;
												ifstream newFileCheck;
												newFileCheck.open("files/config.txt");
												if (newFileCheck.good() == true)
												{
													string name;
													bool pass = true;
													for (int i = 0; i < numberOfFiles; i++)
													{
														getline(newFileCheck, name);
														encryptData(name, password, true);
														if (contentaddNameBox == name)
														{
															pass = false;
														}
													}

													
													if (pass == true)
													{
														addToFile(contentaddIdBoxFull, contentaddPassBoxFull, contentaddNameBoxFull, contentaddNoteBoxFull, contentaddNoteKeyBoxFull, password);
														contentaddNameBox = "Added!";
														contentaddNameBoxFull = "Added!";
														contentaddNameBoxMemory = "Added!";
														chPassAdd = true;
													}
													else
													{
														contentaddNameBox = "File already exists!";
														contentaddNameBoxFull = "File already exists!";
														contentaddNameBoxMemory = "File already exists!";
													}
														textaddIdBox.setString("");
														textaddPassBox.setString("");
														textaddNameBox.setString(contentaddNameBox);
														textaddNoteBox.setString("");
														textaddNoteKeyBox.setString("");

														contentaddIdBox = "";
														contentaddPassBox = "";
														contentaddNoteBox = "";
														contentaddNoteKeyBox = "";

														contentaddIdBoxFull = "";
														contentaddPassBoxFull = "";
														contentaddNoteBoxFull = "";
														contentaddNoteKeyBoxFull = "";

														contentaddIdBoxMemory = "";
														contentaddPassBoxMemory = "";
														contentaddNoteBoxMemory = "";
														contentaddNoteKeyBoxMemory = "";
													
												}
											
												newFileCheck.close();
											}
											else
											{
												textaddNameBox.setString("File name needed!");
											}
										}
										else if (mms.x >= 510 && mms.x <= 600 && mms.y >= 540 && mms.y <= 585)
										{
											textaddIdBox.setString("");
											textaddPassBox.setString("");
											textaddNameBox.setString("");
											textaddNoteBox.setString("");
											textaddNoteKeyBox.setString("");

											contentaddIdBox = "";
											contentaddPassBox = "";
											contentaddNameBox = "";
											contentaddNoteBox = "";
											contentaddNoteKeyBox = "";

											contentaddIdBoxFull = "";
											contentaddPassBoxFull = "";
											contentaddNameBoxFull = "";
											contentaddNoteBoxFull = "";
											contentaddNoteKeyBoxFull = "";

											contentaddIdBoxMemory = "";
											contentaddPassBoxMemory = "";
											contentaddNameBoxMemory = "";
											contentaddNoteBoxMemory = "";
											contentaddNoteKeyBoxMemory = "";

											tryb = 1;
										}

							}

							else if (tryb == 0)
							{
							
								if (mms.x >= 290 && mms.x <= 780 && mms.y >= 55 && mms.y <= 90)
								{
									addPassBoxLogin.setFillColor(sf::Color(78, 191, 70, 255));
									passLoginAllow = true;
								}
								else if (mms.x >= 405 && mms.x <= 505 && mms.y >= 535 && mms.y <= 590)
								{

									password=contentPassLoginFull;
									int n = password.length();
									char *arrayOfStringPass = new char[n + 1];
									strcpy(arrayOfStringPass, password.c_str());

									char passHash[65];
									sha256(arrayOfStringPass, passHash);

									
									ifstream newFile;
									newFile.open("files/pass.txt",ios::in);
									if (newFile.good())
									{
										string name;
										
										getline(newFile, name);

										
										if (name == (string)passHash)
										{
											tryb = 1;
										}
										else
										{
											contentPassLogin = L"";
											contentPassLoginMemory = L"";
											contentPassLoginFull = L"";

											textPassLogin.setString(contentPassLogin);
											addPassBoxLogin.setFillColor(sf::Color(100, 100, 100, 150));
											passLoginAllow = false;
											howManyTimes++;
											if (howManyTimes > 3)
											{
												exit(1);
											}
											
										}

										
											
										
									}
									else
									{
										
										exit(0);
									}
									newFile.close();
									delete[] arrayOfStringPass;
									
								}
								else
								{
									addPassBoxLogin.setFillColor(sf::Color(100, 100, 100, 150));
									passLoginAllow = false;
								}
									
							}
							else if (tryb == 3)
							{
								addIdBox.setFillColor(sf::Color(100, 100, 100, 150));
								addPassBox.setFillColor(sf::Color(100, 100, 100, 150));
								addPassNewReBox.setFillColor(sf::Color(100, 100, 100, 150));
								idAllow = false;
								passAllow = false;
								rePass = false;

								if (mms.x >= 290 && mms.x <= 780 && mms.y >= 55 && mms.y <= 90)
								{
									addIdBox.setFillColor(sf::Color(78, 191, 70, 255));
									idAllow = true;
								}
								else if (mms.x >= 290 && mms.x <= 780 && mms.y >= 120 && mms.y <= 155)
								{
									
									addPassBox.setFillColor(sf::Color(78, 191, 70, 255));
									passAllow = true;
								}
								else if (mms.x >= 290 && mms.x <= 780 && mms.y >= 210 && mms.y <= 245)
								{
									
									addPassNewReBox.setFillColor(sf::Color(78, 191, 70, 255));
									rePass = true;
								}
								else if (mms.x >= 405 && mms.x <= 495 && mms.y >= 540 && mms.y <= 585)
								{

									string Tpassword = contentaddPass1FFull;

									int n = Tpassword.length();
									char *arrayOfStringPass = new char[n + 1];
									strcpy(arrayOfStringPass, Tpassword.c_str());

									char passHash[65];
									sha256(arrayOfStringPass, passHash);

									bool passwordCheck = false;
									ifstream newFile;
									newFile.open("files/pass.txt", ios::in);
									if (newFile.good()==true)
									{
										string name;
										getline(newFile, name);

										
										if (name == (string)passHash)
										{	
											passwordCheck = true;
										}

									}
									else
									{
										
									
										
									}
									newFile.close();

									if (passwordCheck == true&& contentaddPass1FFullNew == contentaddPass1FFullNewRe)
									{
											ofstream newFile2;
											newFile2.open("files/pass.txt", ios::out | ios::trunc);
											if (newFile2.good() == true)
											{
												
												string TNpassword = contentaddPass1FFullNew;

												int n = TNpassword.length();
												char *arrayOfStringPassN = new char[n + 1];
												strcpy(arrayOfStringPassN, TNpassword.c_str());

												char passHashN[65];
												sha256(arrayOfStringPassN, passHashN);

												delete[] arrayOfStringPassN;
												
												string *arrayOfFiles = checkFileName(numberOfFiles);
												reNumE(arrayOfFiles, numberOfFiles, password, TNpassword);

												string oldPass = password;
												password = TNpassword;
												chPass = true;
												
												ofstream configFile;

												configFile.open("files/config.txt", ios::out,ios::trunc);
												if (configFile.good() == true)
												{
													
													for (int z = 0; z < numberOfFiles; z++)
													{
														configFile << arrayOfFiles[z] << endl;
													}
													
												}
												else
												{
													
													password = oldPass;
													reNumE(arrayOfFiles, numberOfFiles, TNpassword, password);
												}
												configFile.close();





												contentaddPass1F = "";
												contentaddPass1FNew = "";
												contentaddPass1FNewRe = "";

												contentaddPass1FMemory = "";
												contentaddPass1FMemoryNew = "";
												contentaddPass1FMemoryNewRe = "";

												contentaddPass1FFull = "";
												contentaddPass1FFullNew = "";
												contentaddPass1FFullNewRe = "";

												textaddPass1F.setString("");
												textaddPass1FNew.setString("");
												textaddPass1FNewRe.setString("");
												if (password == oldPass)
												{
													int n = password.length();
													char *arrayOfStringPassNRe = new char[n + 1];
													strcpy(arrayOfStringPassNRe, TNpassword.c_str());

													char passHashN[65];
													sha256(arrayOfStringPassNRe, passHashN);
													delete[] arrayOfStringPassNRe;
													newFile2 << passHashN;
													textaddPass1F.setString("Error!");
													
												}
												else
												{
													newFile2 << passHashN;
													textaddPass1F.setString("Password changed!");
													
												}

												delete[]arrayOfFiles;

											}
											else
											{
												
												

											}
											newFile2.close();
										
									
									}

									delete[] arrayOfStringPass;
								}
								else if (mms.x >= 510 && mms.x <= 600 && mms.y >= 540 && mms.y <= 585)
								{
									tryb = 1;
								}
								
								
								
							}
						}


					}
					break;
				}
//----------------------------------------------Klawiatura
				case sf::Event::TextEntered:
				{
					if (tryb == 1 && bottomBoxAllow==true)
					{
						float width = textBottomBox.getLocalBounds().width;
						writeInBoxWithoutProblems(width,285,contentBottomBox,contentBottomBoxMemory,event,textBottomBox,contentBottomBoxFull);
					}
					else if (tryb == 2)
					{
						if (event.text.unicode == 9)
						{
							if (idAllow == true)
							{
								addIdBox.setFillColor(sf::Color(100, 100, 100, 150));
								idAllow = false;

								addPassBox.setFillColor(sf::Color(78, 191, 70, 255));
								passAllow = true;
							}
							else if (passAllow == true)
							{
								addPassBox.setFillColor(sf::Color(100, 100, 100, 150));
								passAllow = false;

								addFileNameBox.setFillColor(sf::Color(78, 191, 70, 255));
								fileNameAllow = true;
							}
							else if (fileNameAllow == true)
							{
								addFileNameBox.setFillColor(sf::Color(100, 100, 100, 150));
								fileNameAllow = false;

								addNoteBox.setFillColor(sf::Color(78, 191, 70, 255));
								noteAllow = true;
							}
							else if (noteAllow == true)
							{
								addNoteBox.setFillColor(sf::Color(100, 100, 100, 150));
								noteAllow = false;

								addNoteKeyBox.setFillColor(sf::Color(78, 191, 70, 255));
								noteKeyAllow = true;
							}
							else if (noteKeyAllow == true)
							{
								addNoteKeyBox.setFillColor(sf::Color(100, 100, 100, 150));
								noteKeyAllow = false;

								addIdBox.setFillColor(sf::Color(78, 191, 70, 255));
								idAllow = true;
							}
						}

						else if (idAllow == true)
						{
							float width = textaddIdBox.getLocalBounds().width;
							writeInBoxWithoutProblems(width, 460, contentaddIdBox, contentaddIdBoxMemory, event, textaddIdBox,contentaddIdBoxFull);
						}
						else if (passAllow == true)
						{
							float width = textaddPassBox.getLocalBounds().width;
							writeInBoxWithoutProblems(width, 460, contentaddPassBox, contentaddPassBoxMemory, event, textaddPassBox,contentaddPassBoxFull);
						}
						else if (fileNameAllow == true)
						{
							float width = textaddNameBox.getLocalBounds().width;
							writeInBoxWithoutProblems(width, 460, contentaddNameBox, contentaddNameBoxMemory, event, textaddNameBox,contentaddNameBoxFull);
						}
						else if (noteAllow == true)
						{
							float width = textaddNoteBox.getLocalBounds().width;
							writeInBoxWithoutProblems(width, 460, contentaddNoteBox, contentaddNoteBoxMemory, event, textaddNoteBox,contentaddNoteBoxFull);
						}
						else if (noteKeyAllow == true)
						{
							float width = textaddNoteKeyBox.getLocalBounds().width;
							writeInBoxWithoutProblems(width, 460, contentaddNoteKeyBox, contentaddNoteKeyBoxMemory, event, textaddNoteKeyBox,contentaddNoteKeyBoxFull);
						}

					}
					else if (tryb == 0)
					{
						if (passLoginAllow == true)
						{
							float width = textPassLogin.getLocalBounds().width;
							
							
							writeInBoxWithoutProblems(width, 460, contentPassLogin, contentPassLoginMemory, event, textPassLogin, contentPassLoginFull);
							for (int i = 0; i < contentPassLogin.getSize(); i++)
							{
								contentPassLogin[i] = '*';
							}
							textPassLogin.setString(contentPassLogin);
						}
					}
					else if (tryb == 3)
					{
							if (event.text.unicode == 9)
							{
								if (idAllow == true)
								{
									addIdBox.setFillColor(sf::Color(100, 100, 100, 150));
									idAllow = false;

									addPassBox.setFillColor(sf::Color(78, 191, 70, 255));
									passAllow = true;
								}
								else if (passAllow == true)
								{
									addPassBox.setFillColor(sf::Color(100, 100, 100, 150));
									passAllow = false;

									addPassNewReBox.setFillColor(sf::Color(78, 191, 70, 255));
									rePass = true;
								}
								else if (rePass == true)
								{
									addPassNewReBox.setFillColor(sf::Color(100, 100, 100, 150));
									rePass = false;

									addIdBox.setFillColor(sf::Color(78, 191, 70, 255));
									idAllow = true;
								}
							}

							else if (idAllow == true)
							{
								float width = textaddPass1F.getLocalBounds().width;
								writeInBoxWithoutProblems(width, 460, contentaddPass1F, contentaddPass1FMemory, event, textaddPass1F, contentaddPass1FFull);
							}
							else if (passAllow == true)
							{
								float width = textaddPass1FNew.getLocalBounds().width;
								writeInBoxWithoutProblems(width, 460, contentaddPass1FNew, contentaddPass1FMemoryNew, event, textaddPass1FNew, contentaddPass1FFullNew);
							}
							else if (rePass == true)
							{
								float width = textaddPass1FNewRe.getLocalBounds().width;
								writeInBoxWithoutProblems(width, 460, contentaddPass1FNewRe, contentaddPass1FMemoryNewRe, event, textaddPass1FNewRe, contentaddPass1FFullNewRe);
							}
					}
					break;
				}
				case sf::Event::MouseWheelScrolled:
				{
					
					if (event.mouseWheelScroll.delta==-1&&(nNextFile+8)<numberOfFiles)
					{
						nNextFile++;
						askMouse = true;
						
					}
					else if (event.mouseWheelScroll.delta == 1&&(nNextFile+8)>8)
					{
						nNextFile--;
						askMouse = true;

					}
					if (askMouse == true)
					{
						numberChangeFile = -1;
						changeFileBut = true;
						textaddIdBoxMenu.setString("");
						textaddPassBoxMenu.setString("");
						textaddNoteBoxMenu.setString("");
						textaddNoteKeyBoxMenu.setString("");
						askMouse = false;
					}
					
						if (changeFileBut == true)
						{

							if (numberChangeFile != 0)
							{
								leftmBox1.setFillColor(sf::Color(170, 170, 170, 190));
							}

							if (numberChangeFile != 1)
							{
								leftmBox2.setFillColor(sf::Color(170, 170, 170, 190));
							}

							if (numberChangeFile != 2)
							{
								leftmBox3.setFillColor(sf::Color(170, 170, 170, 190));
							}

							if (numberChangeFile != 3)
							{
								leftmBox4.setFillColor(sf::Color(170, 170, 170, 190));
							}

							if (numberChangeFile != 4)
							{
								leftmBox5.setFillColor(sf::Color(170, 170, 170, 190));
							}

							if (numberChangeFile != 5)
							{
								leftmBox6.setFillColor(sf::Color(170, 170, 170, 190));
							}

							if (numberChangeFile != 6)
							{
								leftmBox7.setFillColor(sf::Color(170, 170, 170, 190));
							}

							if (numberChangeFile != 7)
							{
								leftmBox8.setFillColor(sf::Color(170, 170, 170, 190));
							}
							changeFileBut = false;
						}
					break;
				}
			}
			
		}

		for (int x = 0; x < 2; x++)
		{
			for (int y = 0; y < 2; y++)
			{
				spritetlo.setPosition(x * 400, y * 400);
				Window.draw(spritetlo);
			}
		}
		
		Window.draw(header);
		Window.draw(htext);
		Window.draw(htext2);


		Window.draw(bottomBoxExit);
		Window.draw(textExit);

		Window.draw(rightBox);
		if (tryb == 0)
		{

			Window.draw(bottomBoxLogin);
			Window.draw(textLogin);

			Window.draw(textaddPassLogin);

			Window.draw(addPassBoxLogin);
			Window.draw(textPassLogin);
		}
		else if (tryb == 1)
		{

			if (chPass == true|| chPassAdd == true)
			{
				checkFile(numberOfFiles);
				delete[] tabN;
				tabN = checkFileName(numberOfFiles);
				chPassAdd = false;
			}

			Window.draw(bottomBoxAdd);
			Window.draw(textadd);
				
			if (numberOfFiles >= 1)
			{
				if (contentLeftmBox1 != tabN[nNextFile]||chPass==true)
				{
					contentLeftmBox1 = tabN[nNextFile];
					
					string contentLeftmBox1S = contentLeftmBox1;
					encryptData(contentLeftmBox1S, password, true);

					textLeftmBox1.setString(contentLeftmBox1S);
					
				}
				Window.draw(leftmBox1);
				Window.draw(textLeftmBox1);
			}

			if (numberOfFiles >= 2)
			{
				if (contentLeftmBox2 != tabN[1 + nNextFile]||chPass==true)
				{
					contentLeftmBox2 = tabN[1 + nNextFile];

					string contentLeftmBox2S = contentLeftmBox2;
					encryptData(contentLeftmBox2S, password, true);

					textLeftmBox2.setString(contentLeftmBox2S);
					
				}
				Window.draw(leftmBox2);
				Window.draw(textLeftmBox2);
			}
			if (numberOfFiles >= 3)
			{
				if (contentLeftmBox3 != tabN[2 + nNextFile]||chPass==true)
				{
					contentLeftmBox3 = tabN[2 + nNextFile];

					string contentLeftmBox3S = contentLeftmBox3;
					encryptData(contentLeftmBox3S, password, true);

					textLeftmBox3.setString(contentLeftmBox3S);
					
				}
				Window.draw(leftmBox3);
				Window.draw(textLeftmBox3);
			}
			if (numberOfFiles >= 4)
			{
				if (contentLeftmBox4 != tabN[3 + nNextFile]||chPass==true)
				{
					contentLeftmBox4 = tabN[3 + nNextFile];

					string contentLeftmBox4S = contentLeftmBox4;
					encryptData(contentLeftmBox4S, password, true);

					textLeftmBox4.setString(contentLeftmBox4S);
					
				}
				Window.draw(leftmBox4);
				Window.draw(textLeftmBox4);
			}
			if (numberOfFiles >= 5)
			{
				if (contentLeftmBox5 != tabN[4 + nNextFile]||chPass==true)
				{
					contentLeftmBox5 = tabN[4 + nNextFile];

					string contentLeftmBox5S = contentLeftmBox5;
					encryptData(contentLeftmBox5S, password, true);

					textLeftmBox5.setString(contentLeftmBox5S);
					
				}
				Window.draw(leftmBox5);
				Window.draw(textLeftmBox5);
			}
			if (numberOfFiles >= 6)
			{
				if (contentLeftmBox6 != tabN[5 + nNextFile]||chPass==true)
				{
					contentLeftmBox6 = tabN[5 + nNextFile];

					string contentLeftmBox6S = contentLeftmBox6;
					encryptData(contentLeftmBox6S, password, true);

					textLeftmBox6.setString(contentLeftmBox6S);
					
				}
				Window.draw(leftmBox6);
				Window.draw(textLeftmBox6);
			}
			if (numberOfFiles >= 7)
			{
				if (contentLeftmBox7 != tabN[6 + nNextFile]||chPass==true)
				{
					contentLeftmBox7 = tabN[6 + nNextFile];

					string contentLeftmBox7S = contentLeftmBox7;
					encryptData(contentLeftmBox7S, password, true);

					textLeftmBox7.setString(contentLeftmBox7S);
					
				}
				Window.draw(leftmBox7);
				Window.draw(textLeftmBox7);
			}
			if (numberOfFiles >= 8)
			{
				if (contentLeftmBox8 != tabN[7 + nNextFile]||chPass==true)
				{
					contentLeftmBox8 = tabN[7 + nNextFile];

					string contentLeftmBox8S = contentLeftmBox8;
					encryptData(contentLeftmBox8S, password, true);

					textLeftmBox8.setString(contentLeftmBox8S);
					
				}
				if (chPass == true)
				{
					chPass = false;
				}
				Window.draw(leftmBox8);
				Window.draw(textLeftmBox8);
			}

			Window.draw(leftmBorder);
			Window.draw(bottomBox);
			Window.draw(textBottomBox);
			Window.draw(spritelupa);

			Window.draw(bottomBoxDel);
			Window.draw(textdel);

			Window.draw(bottomBoxcp);
			Window.draw(textpass);

			Window.draw(addIdBoxMenu);
			Window.draw(addPassBoxMenu);
			Window.draw(addNoteBoxMenu);
			Window.draw(addNoteKeyBoxMenu);

			Window.draw(textaddIdBoxMenu);
			Window.draw(textaddPassBoxMenu);
			Window.draw(textaddNoteBoxMenu);
			Window.draw(textaddNoteKeyBoxMenu);

			Window.draw(textaddIdBoxMenuF);
			Window.draw(textaddPassBoxMenuF);
			Window.draw(textaddNoteBoxMenuF);
			Window.draw(textaddNoteKeyBoxMenuF);

		}
		else if (tryb == 2)
		{
			Window.draw(bottomBoxAdd);
			Window.draw(textadd);

			Window.draw(bottomBoxBack);
			Window.draw(textback);
			Window.draw(textaddId);
			Window.draw(textaddPass);
			Window.draw(textaddNote);
			Window.draw(textaddName);
			Window.draw(textaddNoteKey);
			Window.draw(addIdBox);
			Window.draw(addPassBox);
			Window.draw(addFileNameBox);
			Window.draw(addNoteBox);
			Window.draw(addNoteKeyBox);

			Window.draw(textaddIdBox);
			Window.draw(textaddPassBox);
			Window.draw(textaddNoteBox);
			Window.draw(textaddNoteKeyBox);
			Window.draw(textaddNameBox);
		}
	
		else if (tryb == 3)
		{
			Window.draw(bottomBoxBack);
			Window.draw(textback);

			Window.draw(bottomBoxChange);
			Window.draw(textChange);

			Window.draw(textaddPass1);
			Window.draw(textaddPassNew);
			Window.draw(textaddPassNewRe);

			Window.draw(addIdBox);
			Window.draw(addPassBox);
			Window.draw(addPassNewReBox);

			Window.draw(textaddPass1F);
			Window.draw(textaddPass1FNew);
			Window.draw(textaddPass1FNewRe);
		}
		Window.display();
		Window.clear();
	}
	delete[] tabN;
	
	return 0;
}

string *readFile(int number)
{
	string name;

	ifstream newFile;

	try
	{
		newFile.open("files/config.txt");
		if (!newFile)
		{
			string exepction = "Brak pliku!";
			throw exepction;
		}
		int i = 0;
		while (number > i&&getline(newFile, name))
		{
			i++;

		}
		newFile.close();


		string data;

		string filePath = "files/" + name + ".txt";
		newFile.open(filePath);
		if (!newFile)
		{
			string exepction = "Brak pliku!";
			throw exepction;
		}

		int x = 0;
		string id;
		string pass;
		string note;
		string noteKey;
		while (x <= 3 && getline(newFile, data))
		{

			if (x == 0)
			{
				id = data;
			}
			else if (x == 1)
			{
				pass = data;
			}
			else if (x == 2)
			{
				note = data;
			}
			else if (x == 3)
			{
				noteKey = data;
			}
			else
			{
				exit(1);
			}
			x++;
		}

		if (x < 4)
		{
				string exepction = "Zle zapisany plik!";
				throw exepction;
		}
		newFile.close();

		string *noteTab = new string[3];
		noteTab = separators(note);
		
		string *noteTabKey = new string[3];
		noteTabKey = separators(noteKey);

		string *DataTab = new string[8];
		DataTab[0] = id;
		DataTab[1] = pass;
		DataTab[2] = noteTab[0];
		DataTab[3] = noteTab[1];
		DataTab[4] = noteTab[2];
		DataTab[5] = noteTabKey[0];
		DataTab[6] = noteTabKey[1];
		DataTab[7] = noteTabKey[2];
		delete[] noteTab;
		delete[] noteTabKey;
		return DataTab;
	}
	catch (string error)
	{
		
		return 0;
	}
}

string *separators(string note)
{

	int startF = 0;
	int endF = 0;
	int z = 0;

	string *noteTab = new string[3];

	while (z <= 2)
	{

		endF = note.find('|', startF);

			string tempSub = note.substr(startF, (endF - startF));

			startF = endF + 1;
			noteTab[z] = tempSub;
		
			z++;

		if (endF == -1&&z<=2)
		{
			do
			{
				noteTab[z] = "";
				z++;
			} while (z <= 2);
		}

	}

	return noteTab;

}

void writeInBoxWithoutProblems(float localBoundsText,float localBoundsBox, sf::String &contentBottomBox, sf::String &contentBottomBoxMemory,sf::Event event,sf::Text &textBottomBox, sf::String &contentBottomBoxFull)
{
	if (event.text.unicode >= 32 && event.text.unicode <= 126)
	{
		contentBottomBox += event.text.unicode;
		contentBottomBoxFull += event.text.unicode;
		if (localBoundsText >= localBoundsBox)
		{
			contentBottomBoxMemory += contentBottomBox.substring(0, 1);
			contentBottomBox = contentBottomBox.substring(1, contentBottomBox.getSize() - 1);
		}

		textBottomBox.setString(contentBottomBox);



	}
	else if (event.text.unicode == 8 && contentBottomBox.getSize() > 0)
	{
		contentBottomBox = contentBottomBox.substring(0, contentBottomBox.getSize() - 1);
		contentBottomBoxFull = contentBottomBoxFull.substring(0, contentBottomBoxFull.getSize() - 1);

		if (localBoundsText >= localBoundsBox && contentBottomBoxMemory.getSize()>0)
		{
			sf::String znak = contentBottomBoxMemory.substring(contentBottomBoxMemory.getSize() - 1, contentBottomBoxMemory.getSize());
			contentBottomBoxMemory = contentBottomBoxMemory.substring(0, contentBottomBoxMemory.getSize() - 1);

			contentBottomBox = znak + contentBottomBox;

		}
		textBottomBox.setString(contentBottomBox);



	}
	else if (event.text.unicode == 8 && contentBottomBox.getSize() == 0)
	{
		textBottomBox.setString(contentBottomBox);
	}
}

void addToFile(sf::String &id, sf::String &pass, sf::String &fileName, sf::String &note, sf::String &noteKey, string &password)
{

	ofstream addFile;
	try
	{
		string fileNameS = fileName;

		encryptData(fileNameS, password,false);

		bool check = false;
		addFile.open("files/" + fileNameS + ".txt", ios::trunc);
		if (addFile.is_open())
		{
			
			string idS = id;
			encryptData(idS, password,false);

			string passS = pass;
			encryptData(passS, password,false);

			string noteS = note;
			encryptData(noteS, password,false);

			string noteKeyS = noteKey;
			encryptData(noteKeyS, password,false);

			string *noteTab = new string[3];
			noteTab = separators(noteS);

			string *noteTabKey = new string[3];
			noteTabKey = separators(noteKeyS);



			addFile << idS + "\n" + passS + "\n" + (noteTab[0] + "|" + noteTab[1] + "|" + noteTab[2]) + "\n" + (noteTabKey[0] + "|" + noteTabKey[1] + "|" + noteTabKey[2]);
			check = true;
			delete[] noteTab;
			delete[] noteTabKey;

		}
		else
		{
			check = false;
			throw("Błąd zapisu pliku!");
			exit(1);
		}
		addFile.close();

		if (check == true)
		{
			addFile.open("files/config.txt", ios::app);
			addFile <<fileNameS<<endl;
			addFile.close();
		}
	}
	catch (string exepction)
	{
		
	}


}

void checkFile(int &numberOfFiles)
{
	fstream newFile;
	try
	{
		newFile.open("files/config.txt");
		if (!newFile)
		{
			string exepction = "Brak pliku!";
			throw exepction;
		}
		int i = 0;
		string name;
		while (getline(newFile, name))
		{
			i++;
		}
		newFile.close();
		numberOfFiles = i;
	}
	catch (string ex)
	{
		
	}
	
}

string *checkFileName(int numberOfFiles)
{
	fstream newFile;
	try
	{
		newFile.open("files/config.txt");
		if (!newFile)
		{
			string exepction = "Brak pliku!";
			throw exepction;
		}
		string *fNames=new string[numberOfFiles];

		string name;
		int i = 0;
		while (getline(newFile, name))
		{
			if (numberOfFiles > i)
			{
				fNames[i] = name;
			}
			i++;
		}
		newFile.close();
		return fNames;
	}
	catch (string ex)
	{
		
		return 0;
	}

}


void delFile(short int number,int &numberOfFiles,int &nNextFile)
{
	
	try
	{
		string *fNames = new string[numberOfFiles];

		ifstream newFile;
		newFile.open("files/config.txt");
		if (newFile.good()==true)
		{
			
			string name;
			int i = 0;
			while (getline(newFile, name))
			{
				fNames[i] = name;
				i++;
			}
			string path = "files/" + fNames[number + nNextFile] + ".txt";
			
	
			
			if (remove(path.c_str()) != 0)
			{
				throw("Blad 0!");
			}
			

			for (int i = number + nNextFile; i < numberOfFiles - 1; i++)
			{

				fNames[i] = fNames[i + 1];
			}
			numberOfFiles--;
			if (nNextFile > 0)
			{
				nNextFile--;
			}
		}
		else
		{
			string exepction = "Brak pliku!";
			throw exepction;
		}
		newFile.close();

		ofstream newFile2;
		newFile2.open("files/config.txt",std::ofstream::out,std::ofstream::trunc);
		if (newFile2.good() == true)
		{
			for (int i = 0; i < numberOfFiles; i++)
			{
				newFile2 << fNames[i] << endl;
			}
		}
		else
		{
			string exepction = "Blad zapisu pliku!";
			throw exepction;
		}
		newFile2.close();
		
		delete[] fNames;
	}
	catch (string ex)
	{
		
	}
}



void sha256(char *data, char outputBuffer[65])
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, data, strlen(data));
	SHA256_Final(hash, &sha256);


	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		sprintf(outputBuffer + (i * 2), "%02x", hash[i]);

	}
	outputBuffer[64] = 0;


}
void encryptData(string &data,string &password,bool decrypt)
{
	//Generating unique key

	string passwordInAscii;
	for (int i = 0; i < password.length(); i++)
	{
		stringstream ss;
		ss << std::setprecision(100000);
		ss << (int)password[i];
		string str = ss.str();
		passwordInAscii += str;
	
	}
//-One
	string passwordInAscii2 = passwordInAscii + passwordInAscii+ "One0";

	
//Using sha256 to hash value(sha256 used from openssl library)
	//one
	int n = passwordInAscii.length();
	char *arrayOfStringAscii = new char[n + 1];
	strcpy(arrayOfStringAscii, passwordInAscii.c_str());

	char passInAsciiH1[65];
	sha256(arrayOfStringAscii, passInAsciiH1);
	delete[] arrayOfStringAscii;


	//two
	n = passwordInAscii2.length();
	char *arrayOfStringAscii2 = new char[n + 1];
	strcpy(arrayOfStringAscii2, passwordInAscii2.c_str());

	char passInAsciiH2[65];
	sha256(arrayOfStringAscii2, passInAsciiH2);
	delete[] arrayOfStringAscii2;

//End of using sha256 from openssl library 


	char letterHash[16] = {
		'0','1','2','3','4','5','6','7','8','9',
		'a','b','c','d','e','f'};

	char letterHex[64] = {
		'0','1','2','3','4','5','6','7','8','9',
		'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','.','@'};

	char letterMemory[64] = {
		'0','1','2','3','4','5','6','7','8','9',
		'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','.','@'};

	for (int i = 0; i < 64; i++)
	{
		
		int x = 1;
		while (passInAsciiH2[i] != letterHash[x-1] && x <= 16)
		{
			x++;
		}

		int y = 1;
		while (passInAsciiH1[i] != letterHash[y-1] && y <= 16)
		{
			y++;
		}

		int temp = letterHex[i];
		letterHex[i] = letterHex[(3 * x + y)-1];
		letterHex[(3 * x + y)-1] = temp;
	
	}

	if (decrypt == false)
	{
		for (int i = 0; i < data.length(); i++)
		{
			int m = 0;
			
			while (data[i] != letterMemory[m] && m < 64)
			{
				m++;
			}
			if (m < 64)
			{
				data[i] = letterHex[m];
			}
		}
	}
	else if (decrypt == true)
	{
		for (int i = 0; i < data.length(); i++)
		{
			
			int m = 0;
			while (data[i] != letterHex[m] && m < 64)
			{
				m++;
			}
			if (m < 64)
			{
				data[i] = letterMemory[m];
			}
		}
	}

}

void reNumE(string *tab, int numberOfFiles, string password,string TNpassword)
{

	for (int i = 0; i < numberOfFiles; i++)
	{

		string *tabOld = readFile(i+1);

		sf::String tabOldSf[4];
		for (int x = 0; x < 8; x++)
		{
			encryptData(tabOld[x], password, true);
			
		
		}

		tabOldSf[0] = tabOld[0];
		tabOldSf[1] = tabOld[1];
		tabOldSf[2] = tabOld[2] + '|' + tabOld[3] + '|' + tabOld[4];
		tabOldSf[3] = tabOld[5] + '|' + tabOld[6] + '|' + tabOld[7];

		string oldName = tab[i];
		encryptData(tab[i], password, true);
		sf::String normalName = tab[i];
		encryptData(tab[i], TNpassword, false);
		string oldPath = "files/" + oldName+".txt";
		string newPath = "files/" + tab[i]+".txt";
		int result=rename(oldPath.c_str(), newPath.c_str());

		if (result == 0)
			puts("File successfully renamed");

		addToFile(tabOldSf[0], tabOldSf[1], normalName, tabOldSf[2], tabOldSf[3], TNpassword);
		delete[] tabOld;

	}

}

