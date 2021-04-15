/*
 * cMain.cpp
 *
 *  Created on: Aug 19, 2020
 *      Author: qzr
 */

#include "cMain.h"

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "OneLoneCoder.com - wxWidgets!", wxPoint(100, 100), wxSize(600, 665))
{
	//##//Setting size hints
	this->SetSizeHints(wxSize(250,250), wxSize(1000,1000));

	btn = new wxButton*[nFieldWidth*nFieldHeight];
	wxGridSizer *grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);

	nField = new int[nFieldWidth * nFieldHeight];

	//##//Indicates presence of mine flags over buttons
	hasMineFlag = new bool[nFieldWidth * nFieldHeight];
	for (int x = 0; x < nFieldWidth; x++)
		for (int y =0; y <nFieldHeight; y++)
		{ hasMineFlag[y*nFieldWidth + x] = false; }

	//##//Adding toolbar and buttons for game control
	toolbar1 = this->CreateToolBar(wxTB_HORIZONTAL, wxID_ANY);
	
	wxButton *settingsButton = new wxButton(toolbar1, 9001, "abc", wxDefaultPosition, wxSize(40,40), 0); //come here//string label "Settings" removed to be restored//
	wxButton *forfeitButton = new wxButton(toolbar1, 9002, "Forfeit", wxDefaultPosition, wxSize(40,40), 0);
	wxButton *restartButton = new wxButton(toolbar1, 9003, "Restart", wxDefaultPosition, wxSize(40,40), 0);
    //##To be implemented##//SettingsB->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnSelectColour), nullptr, this);
	//settingsButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnClickSettings));
	//come here//debug test line for testing button bmp label
	//settingsButton->SetLabel(wxEmptyString);
	settingsButton->SetBitmap(*bmpFlag20p, wxRIGHT); //APIBUG//This line only works if the button was initially constructed with an empty string label AND the label cannot be set to a bitmap once it has been set to a string. OTOH the label can be successfully set to a string after it has been set to a bitmap.


	toolbar1->AddStretchableSpace();
	toolbar1->AddStretchableSpace();
	toolbar1->AddControl(settingsButton);
	toolbar1->AddStretchableSpace();
	toolbar1->AddControl(forfeitButton);
	toolbar1->AddStretchableSpace();
	toolbar1->AddControl(restartButton);
	toolbar1->AddStretchableSpace();
	toolbar1->AddStretchableSpace();
	toolbar1->Realize();


	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int x = 0; x < nFieldWidth; x++)
	{
		for (int y =0; y <nFieldHeight; y++)
		{
			btn[y*nFieldWidth + x] = new wxButton(this, 10000 + (y*nFieldWidth +x),"", wxDefaultPosition,wxSize(10,10));
			btn[y*nFieldWidth + x]->SetFont(font);
			grid->Add(btn[y*nFieldWidth+x], 1, wxEXPAND | wxALL);

			btn[y*nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			btn[y*nFieldWidth + x]->Bind(wxEVT_RIGHT_DOWN, &cMain::OnRightClick, this); //!!!// Binding right click event to buttons
			nField[y*nFieldWidth + x] = 0;
		}
	}	

	//##//Setting sizer within sizer to attempt to control aspect ratio
	wxBoxSizer *vBox = new wxBoxSizer(wxVERTICAL);
	vBox->Add(grid, 1, wxSHAPED | wxALIGN_CENTER);
	
	this->SetSizer(vBox); //##//Changed parameter from 'grid' to vBox
	
	grid->Layout(); //##//See above
	vBox->Layout();

	//##//implementing a status bar
	//add: 1.sizer; 2.wxSaticBitmap (i.e. bitmap control); 3.staticTxt
	statsbar1 = this->CreateStatusBar(1, wxSTB_DEFAULT_STYLE, wxID_ANY);
	wxBitmap *mineFlag = new wxBitmap(wxString("testgimp.png"), wxBITMAP_TYPE_PNG);
	//SECTION FOR UPDATE
	wxBoxSizer *statsSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *hbox1_StatsB = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *hbox2_StatsB = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *statsbarTxt1 = new wxStaticText(statsbar1, wxID_ANY, wxString("Flags Remaining: "), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
	statsbarTxt1->SetBackgroundColour(*wxYELLOW);
	statsbarTxt2 = new wxStaticText(statsbar1, wxID_ANY, wxString(" x ")<<std::to_string(lvlSelect), wxDefaultPosition, wxDefaultSize);
	statsbarTxt2->SetBackgroundColour(*wxGREEN);
	wxStaticText *statsbarTxt3 = new wxStaticText(statsbar1, wxID_ANY, wxString("Current Score: "), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
	statsbarTxt3->SetBackgroundColour(*wxYELLOW);
	statsbarTxt4 = new wxStaticText(statsbar1, wxID_ANY, wxString("0"), wxDefaultPosition, wxDefaultSize);
	statsbarTxt4->SetBackgroundColour(*wxGREEN);
	wxStaticBitmap *statsbarBMP = new wxStaticBitmap(statsbar1, wxID_ANY, *bmpFlag20p, wxDefaultPosition, wxSize(20, 20));//Working as should
	//hbox1_StatsB->AddStretchSpacer(1);
	hbox1_StatsB->Add(statsbarTxt1, 1, wxALIGN_CENTER | wxLEFT, 45);
	hbox1_StatsB->Add(statsbarBMP, 0, wxALIGN_CENTER);
	hbox1_StatsB->Add(statsbarTxt2, 1, wxALIGN_CENTER);
	//hbox1_StatsB->AddStretchSpacer(1);
	hbox2_StatsB->Add(statsbarTxt3, 1, wxALIGN_CENTER);
	hbox2_StatsB->Add(statsbarTxt4, 1, wxALIGN_CENTER);
	statsSizer->Add(hbox1_StatsB, 1, wxEXPAND);
	statsSizer->Add(hbox2_StatsB, 1, wxEXPAND);
	statsbar1->SetSizer(statsSizer);
	//END SECTION

	//##//End-game dialog section start//
	endGameDial = new wxDialog(this, 7000, wxString("Game Ended"), wxDefaultPosition, wxSize(450, 300));//add parameters
	wxBoxSizer *vboxEndGame = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hbox1_EndGame = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *hbox2_EndGame = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *hbox3_EndGame = new wxBoxSizer(wxHORIZONTAL);
	wxStaticBitmap *EndGBmp1 = new wxStaticBitmap(endGameDial, wxID_ANY, *mineFlag, wxDefaultPosition, wxSize(20,20));
	wxStaticBitmap *EndGBmp2 = new wxStaticBitmap(endGameDial, wxID_ANY, *mineFlag, wxDefaultPosition, wxSize(20,20));
	//wxStaticBitmap *EndGBmp3 = new wxStaticBitmap(endGameDial, wxID_ANY, *mineFlag, wxDefaultPosition, wxSize(20,20));
	//wxStaticBitmap *EndGBmp4 = new wxStaticBitmap(endGameDial, wxID_ANY, *mineFlag, wxDefaultPosition, wxSize(20,20));
	//wxStaticBitmap *EndGBmp5 = new wxStaticBitmap(endGameDial, wxID_ANY, *mineFlag, wxDefaultPosition, wxSize(20,20));
	//THE ABOVE 3 LINES SHOULD LOAD 3 WXBITMAP INSTEAD, FOR SETTING AS BITMAP LABEL!!!
	EndGTxt1 = new wxStaticText(endGameDial, wxID_ANY, wxString("Booom! Wrong Step!"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
	EndGTxt2 = new wxStaticText(endGameDial, wxID_ANY, wxString("FINAL SCORE: ###"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
	//bool qqq = EndGTxt2->SetBackgroundColour(*wxBLUE);
	//wxStaticText *EndGTxt3 = new wxStaticText(endGameDial, wxID_ANY, wxString("###"));
	//qqq = EndGTxt3->SetBackgroundColour(*wxBLUE);
	wxButton *EndGBtn1 = new wxButton(endGameDial, 7001, "Setings", wxDefaultPosition, wxSize(40,40));
	wxButton *EndGBtn2 = new wxButton(endGameDial, 7002, "Restart", wxDefaultPosition, wxSize(40,40));
	wxButton *EndGBtn3 = new wxButton(endGameDial, 7003, "Quit", wxDefaultPosition, wxSize(40,40));
	wxBoxSizer *hboxExtra_EndGame = new wxBoxSizer(wxHORIZONTAL);
	wxStaticBitmap *EndGBmp3 = new wxStaticBitmap(endGameDial, wxID_ANY, *bmpFlag50p, wxDefaultPosition, wxSize(50,50));
	//********************continue here//######################
	EndGTxt3 = new wxStaticText(endGameDial, wxID_ANY, wxString("Base score: "), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
	EndGTxt3->SetBackgroundColour(*wxGREEN);
	wxStaticText *EndGTxt4 = new wxStaticText(endGameDial, wxID_ANY, wxString("difficulty bonus"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
	EndGTxt4->SetBackgroundColour(*wxYELLOW);
	hboxExtra_EndGame->Add(EndGTxt3, 1, wxALIGN_CENTER | wxRIGHT, 20);
	hboxExtra_EndGame->Add(EndGBmp3, 0, wxALIGN_CENTER | wxRIGHT, 5);
	hboxExtra_EndGame->Add(EndGTxt4, 1, wxALIGN_CENTER | wxLEFT, 5);

	hbox1_EndGame->Add(EndGBmp1, 1, wxALIGN_CENTER | wxRIGHT, 10);
	hbox1_EndGame->Add(EndGTxt1, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
	hbox1_EndGame->Add(EndGBmp2, 1, wxALIGN_CENTER | wxLEFT, 10);
	hbox2_EndGame->Add(EndGTxt2, 1, wxALIGN_CENTER);
	hbox3_EndGame->Add(EndGBtn1, 0, wxALIGN_CENTER | wxRIGHT, 10);
	hbox3_EndGame->Add(EndGBtn2, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
	hbox3_EndGame->Add(EndGBtn3, 0, wxALIGN_CENTER | wxLEFT, 10);
	vboxEndGame->Add(hbox1_EndGame, 1, wxALIGN_CENTER);
	vboxEndGame->Add(hbox2_EndGame, 1, wxALIGN_CENTER);
	//add extra hbox
	vboxEndGame->Add(hboxExtra_EndGame, 1, wxALIGN_CENTER);
	vboxEndGame->Add(hbox3_EndGame, 1, wxALIGN_CENTER);
	endGameDial->SetSizer(vboxEndGame);
	vboxEndGame->Layout();
	//End-game dialog section end//

	//##//Settings dialog section start//
	SettingsDial = new wxDialog(this, 7050, wxString("Settings"));
	wxBoxSizer *vboxSettings = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hbox1_Settings = new wxBoxSizer(wxHORIZONTAL);
	//wxBoxSizer *hbox2_Settings = new wxBoxSizer(wxHORIZONTAL);
	//wxBoxSizer *hbox3_Settings = new wxBoxSizer(wxHORIZONTAL);
	wxSizer *hbox4_Settings = SettingsDial->CreateButtonSizer(wxCANCEL + wxOK);
	//wxButton *SettingsCancel = new wxButton(SettingsDial, 7061, "Setings", wxDefaultPosition, wxSize(80,20));
	//wxButton *SettingsOK = new wxButton(SettingsDial, 7062, "Restart", wxDefaultPosition, wxSize(80,20));
	wxStaticText *SettingsTxt1 = new wxStaticText(SettingsDial, wxID_ANY, wxString("Game Difficulty"));
	SettingsTxtDescr = new wxStaticText(SettingsDial, wxID_ANY, wxString("Hello Detective!\nSelect a game difficulty to get started."));
	wxStaticText *SettingsTxtEZ = new wxStaticText(SettingsDial, wxID_ANY, wxString("Eazy"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxStaticText *SettingsTxtMED = new wxStaticText(SettingsDial, wxID_ANY, wxString("Medium"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
	wxStaticText *SettingsTxtHRD = new wxStaticText(SettingsDial, wxID_ANY, wxString("Hard"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
	//bool qqq = SettingsTxtHRD->SetBackgroundColour(*wxBLUE);
	//qqq = SettingsTxtEZ->SetBackgroundColour(*wxBLUE);
	//qqq = SettingsTxtMED->SetBackgroundColour(*wxBLUE);
	SettingsSlider = new wxSlider(SettingsDial, 7051, 2, 1, 3, wxDefaultPosition, wxDefaultSize, wxSL_BOTH);
	SettingsSlider->SetTickFreq(1);
	hbox1_Settings->Add(SettingsTxtEZ, 1, wxLEFT, 10);
	hbox1_Settings->AddStretchSpacer(1);
	hbox1_Settings->Add(SettingsTxtMED, 1);
	hbox1_Settings->AddStretchSpacer(1);
	hbox1_Settings->Add(SettingsTxtHRD, 1, wxRIGHT, 10);
	//hbox2_Settings->AddStretchSpacer(1);
	//hbox2_Settings->Add(SettingsCancel, 0);
	//hbox2_Settings->Add(SettingsOK, 0, wxRIGHT, 15);
	vboxSettings->AddSpacer(20);
	vboxSettings->Add(SettingsTxt1, 1, wxALIGN_LEFT | wxLEFT | wxRIGHT, 30);
	vboxSettings->Add(SettingsSlider, 1, wxEXPAND | wxLEFT | wxRIGHT, 20);
	vboxSettings->Add(hbox1_Settings, 1, wxEXPAND);
	vboxSettings->AddSpacer(15);
	vboxSettings->Add(SettingsTxtDescr, 1, wxEXPAND | wxLEFT | wxRIGHT, 30);
	vboxSettings->AddSpacer(15);
	vboxSettings->Add(hbox4_Settings, 1, wxALIGN_RIGHT);
	SettingsDial->SetSizer(vboxSettings);
	vboxSettings->Layout();
	//Settings dialog section end//

	/*
	//come here//debug section
	wxBoxSizer *debugSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticBitmap *debugFlagBMP = new wxStaticBitmap(nullptr, wxID_ANY, *bmpFlag50p, wxDefaultPosition, wxSize(50,50));
	debugSizer->Add(debugSizer, 1, wxSHAPED | wxEXPAND | wxALL, 10);
	btn[0]->SetSizer(debugSizer);
	//debug section end
	*/

	//##//Event binding section start//
	Bind(wxEVT_BUTTON, &cMain::OnClickSettings, this, 9001);
	Bind(wxEVT_BUTTON, &cMain::OnClickForfeit, this, 9002);
	Bind(wxEVT_BUTTON, &cMain::OnClickRestart, this, 9003);
	EndGBtn3->Bind(wxEVT_BUTTON, &cMain::OnClickQuit, this, 7003);
	EndGBtn2->Bind(wxEVT_BUTTON, &cMain::OnClickDialogRestart, this, 7002);
	EndGBtn1->Bind(wxEVT_BUTTON, &cMain::OnClickSettings, this, 7001);
	SettingsDial->Bind(wxEVT_SLIDER, &cMain::OnLevelSelect, this, 7051);
	SettingsDial->Bind(wxEVT_BUTTON, &cMain::OnClickSettingsOK, this, wxID_OK);
	SettingsDial->Bind(wxEVT_BUTTON, &cMain::OnClickSettingsCancel, this, wxID_CANCEL);
	//Event binding section end//

	//Showing the Greetings Dialog
	int xyz = SettingsDial->ShowModal();

	
}

cMain::~cMain() {
	delete[] btn;
	delete[] nField; //##//deleting array of mine which was omitted during tutorial
	delete[] hasMineFlag; //##//deleting array of mine flags
}

void cMain::OnButtonClicked(wxCommandEvent &evt)
{
	// Get coordinate of button in field array
	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;
	
	if (bFirstClick)
	{
		int totalMineCount = lvlSelect;
		while (totalMineCount)
		{
			int ry = rand() % nFieldHeight;
			int rx = rand() % nFieldWidth;

			if (nField[ry * nFieldWidth + rx] == 0 && rx !=x && ry != y)
			{
				nField[ry * nFieldWidth + rx] = -1;
				totalMineCount--;
			}
		}
		bFirstClick = false;
	}

	// Disable Button, preventing it being pressed again
	btn[y*nFieldWidth + x]->Enable(false);

	// Check if player hit mine
	if (nField[y*nFieldWidth + x] == -1)
	{
		//---COMMON BLOCK--------------------------------------------
		//Reset end game message
		switch(rand() % 2) 
		{
			case 0:
				EndGTxt1->SetLabel("Booom! Wrong Step!");
				break;
			case 1:
				EndGTxt1->SetLabel("Booom! You've died, detective...");
				break;
		}
		//Update end game score
		UpdateEndGameScore();
		int aaa = endGameDial->ShowModal();
		if (hasClosed == true) hasClosed = this->Close();

		// Rest game
		wxCommandEvent *qqq;
		OnClickRestart(*qqq);
		//-----------------------------------------------------------
	}

	else
	{
		// Count neighbouring mine
		int mine_count = 0;
		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + i < nFieldWidth && y +j >= 0 && y + j < nFieldHeight)
				{
					if (nField[(y + j)*nFieldWidth + (x + i)] == -1)
						mine_count++;
				}
			}

			// Update buttons label to show mine count if > 0
			if (mine_count > 0)
			{
				btn[y*nFieldWidth + x]->SetLabel(std::to_string(mine_count));//disabled for debugging//come here
			}

		scoreUnit++;
		//update status bar score
		statsbarTxt4->SetLabel(wxString(std::to_string(GetBaseScore())));
		//int testdebug = 0; //debug var TO BE REMOVED
		//testdebug = GetBaseScore();
		//testdebug = 888;
	}

	if (scoreUnit == (nFieldWidth * nFieldHeight) - lvlSelect)
	{
		victoryAchieved = true;
		//INSERT CODE FOR CHANGING THE TOP BITMAPS, MAY BE INCLUDED IN THE SWITH CASES
		
		//---COMMON BLOCK--------------------------------------------
		switch(rand() % 3) 
		{
			case 0:
				EndGTxt1->SetLabel("Congratulations! Mission success!");
				break;
			case 1:
				EndGTxt1->SetLabel("Good job Chief! You did it!");
				break;
			case 2:
				EndGTxt1->SetLabel("Outstanding! Victory achieved!");
				break;
		}
		//Update end game score
		UpdateEndGameScore();
		int aaa = endGameDial->ShowModal();
		if (hasClosed == true) hasClosed = this->Close();

		// Rest game
		wxCommandEvent *qqq;
		OnClickRestart(*qqq);
		//-----------------------------------------------------------
	}
	
	evt.Skip();
}


void cMain::OnRightClick(wxMouseEvent &evt)
{
	wxBitmap *bmpFlag30p = new wxBitmap(imgFlag->Scale(30, 30, wxIMAGE_QUALITY_HIGH)); //come here//debug line added
	
	// Get coordinate of button in field array
	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;

	if(!hasMineFlag[y*nFieldWidth + x])
	{
		if(flagCount < lvlSelect)
			{
				btn[y*nFieldWidth + x]->SetBitmapLabel(*bmpFlag30p);
				flagCount++;
				hasMineFlag[y*nFieldWidth + x] = true;
			}
	}
	else
	{
		btn[y*nFieldWidth + x]->SetLabel(""); //disabled temporarily for debug//to be re-enabled//come here
		flagCount--;
		hasMineFlag[y*nFieldWidth + x] = false;
	}
	
	//hasMineFlag[y*nFieldWidth + x] = !hasMineFlag[y*nFieldWidth + x];

	//Updating status bar flag msg
	statsbarTxt2->SetLabel(wxString(" x ")<<std::to_string(lvlSelect-flagCount));

	evt.Skip();

}

void cMain::OnClickForfeit(wxCommandEvent &evt)
{
	//wxMessageBox("==YOU HAVE JUST CLICKED FORFEIT==");
	if (alreadyForfeit) return; //test state flag

	alreadyForfeit = true; //set state flag

	if (bFirstClick)
	{
		int totalMineCount = lvlSelect;

		while (totalMineCount)
		{
			int ry = rand() % nFieldHeight;
			int rx = rand() % nFieldWidth;

			if (nField[ry * nFieldWidth + rx] == 0)
			{
				nField[ry * nFieldWidth + rx] = -1;
				totalMineCount--;
			}
		}
	}

	for (int y =0; y <nFieldHeight; y++)
	{
		for (int x = 0; x < nFieldWidth; x++)
		{
			btn[y*nFieldWidth + x]->Enable(false);

			if (nField[y*nFieldWidth + x] == -1)
				btn[y*nFieldWidth + x]->SetLabel("B");//disabled for debug//come here
				//int qwerty = 1; //debug line//to be removed
			else 
			{
				// Count neighbouring mine
				int mine_count = 0;
				for (int i = -1; i < 2; i++)
					for (int j = -1; j < 2; j++)
					{
						if (x + i >= 0 && x + i < nFieldWidth && y +j >= 0 && y + j < nFieldHeight)
						{
							if (nField[(y + j)*nFieldWidth + (x + i)] == -1)
								mine_count++;
						}
					}

					// Update buttons label to show mine count if > 0
					if (mine_count > 0)
					{
						btn[y*nFieldWidth + x]->SetLabel(std::to_string(mine_count)); //disbled for debug//come here
					}
			}
		}		
	}

	//---COMMON BLOCK--------------------------------------------
	switch(rand() % 2) 
	{
		case 0:
			EndGTxt1->SetLabel("Pick yourself up! Ready to go again?");
			break;
		case 1:
			EndGTxt1->SetLabel("Consider this a trial run.\nHow about another round?");
			break;
	}
	//Update end game score
	UpdateEndGameScore();
	int aaa = endGameDial->ShowModal();
	if (hasClosed == true) hasClosed = this->Close();
	//-----------------------------------------------------------
}

void cMain::OnClickSettings(wxCommandEvent &evt)
{
	ResetSettingsMsg();
	int xyz = SettingsDial->ShowModal();
}

void cMain::OnClickRestart(wxCommandEvent &evt)
{
	bFirstClick = true;
	for (int x = 0; x < nFieldWidth; x++)
		for (int y = 0; y < nFieldHeight; y++)
		{
			nField[y*nFieldWidth + x] = 0;
			btn[y*nFieldWidth + x]->SetLabel(""); //disabled for debug//come here
			btn[y*nFieldWidth + x]->Enable(true);
			hasMineFlag[y*nFieldWidth + x] = false;
		}
	flagCount = 0;
	alreadyForfeit = false; //remove forfeit flag
	scoreUnit = 0; //reset score units
	//update status bar score
	statsbarTxt4->SetLabel(wxString("0"));

	//Updating status bar flag msg
	statsbarTxt2->SetLabel(wxString(" x ")<<std::to_string(lvlSelect));
}

void cMain::OnClickDialogRestart(wxCommandEvent &evt)
{
	endGameDial->EndModal(88);

	// Rest game
	wxCommandEvent *qqq;
	OnClickRestart(*qqq);
}

void cMain::OnClickQuit(wxCommandEvent &evt)
{
	hasClosed = true;
	endGameDial->EndModal(88);
}

void cMain::OnLevelSelect(wxCommandEvent &evt)
{
	switch(SettingsSlider->GetValue())
	{
		case 1:
			//lvlSelect = levelEasy;
			SettingsTxtDescr->SetLabel(wxString("15 Mines - For an easy cruising!"));
			break;
		case 2:
			SettingsTxtDescr->SetLabel(wxString("30 Mines - For the average Joe."));
			break;
		case 3:
			SettingsTxtDescr->SetLabel(wxString("45 Mines - At your own risk. For pros only!"));
			break;
	}
}

void cMain::OnClickSettingsOK(wxCommandEvent &evt)
{
	gameLevel oldLvlSelect =lvlSelect;
	switch(SettingsSlider->GetValue())
	{
		case 1:
			lvlSelect = levelEasy;
			break;
		case 2:
			lvlSelect = levelMedium;
			break;
		case 3:
			lvlSelect = levelHard;
			break;
	}
	SettingsDial->EndModal(88);

	if (oldLvlSelect != lvlSelect)
	{
		// Rest game
		wxCommandEvent *qqq;
		OnClickRestart(*qqq);
	}
}

void cMain::OnClickSettingsCancel(wxCommandEvent &evt)
{
	switch(lvlSelect)
	{
		case levelEasy:
			SettingsSlider->SetValue(1);
			break;
		case levelMedium:
			SettingsSlider->SetValue(2);
			break;
		case levelHard:
			SettingsSlider->SetValue(3);
			break;
	}
	ResetSettingsMsg();
	SettingsDial->EndModal(88);
}

void cMain::ResetSettingsMsg() 
{
	wxCommandEvent *ccc;
	OnLevelSelect(*ccc);
}

/*
void cMain::ResetEndGMsg() 
{
	switch(rand() % 2) 
	{
		case 0:
			EndGTxt1->SetLabel("Booom! Wrong Step!");
			break;
		case 1:
			EndGTxt1->SetLabel("Booom! You've died, detective...");
			break;
	}

	//EndGTxt2->SetLabel( wxString("FINAL SCORE: ") <<std::to_string(GetBaseScore()));
}
*/

int cMain::GetBaseScore() //returns the base score
{
	switch (lvlSelect)
	{
	case levelEasy:
		if (scoreUnit * baseMultipl[0] - int(scoreUnit * baseMultipl[0]) < 0.5f)
		return (scoreUnit * baseMultipl[0]);
		else
		return (scoreUnit * baseMultipl[0] + 1);
		
	case levelMedium:
		if (scoreUnit * baseMultipl[1] - int(scoreUnit * baseMultipl[1]) < 0.5f)
		return (scoreUnit * baseMultipl[1]);
		else
		return (scoreUnit * baseMultipl[1] + 1);
	
	case levelHard:
		if (scoreUnit * baseMultipl[2] - int(scoreUnit * baseMultipl[2]) < 0.5f)
		return (scoreUnit * baseMultipl[2]);
		else
		return (scoreUnit * baseMultipl[2] + 1);

	case testLevel:
		return 999;
	}
}

void cMain::UpdateEndGameScore()
{
	float victoryMultip = 1.0;
	int finalScore;
	if (victoryAchieved)
	{
		victoryMultip = 2.0;
		//INSET CODE FOR VICTORY MULTIPLIER BITMAP AND "VICTORY BONUS" STATIC TEXT
	}
	switch (lvlSelect)
	{
	case levelEasy:
		finalScore = GetBaseScore() * lvlMultipl[0] * victoryMultip;
		if((GetBaseScore() * lvlMultipl[0] * victoryMultip - finalScore) >= 0.5f)
			finalScore++;
		//INSERT CODE FOR UPDATING LEVEL MULTIPLIER BITMAP
		break;
	
	case levelMedium:
		finalScore = GetBaseScore() * lvlMultipl[1] * victoryMultip;
		if((GetBaseScore() * lvlMultipl[1] * victoryMultip - finalScore) >= 0.5f)
			finalScore++;
		//INSERT CODE FOR UPDATING LEVEL MULTIPLIER BITMAP
		break;

	case levelHard:
		finalScore = GetBaseScore() * lvlMultipl[2] * victoryMultip;
		if((GetBaseScore() * lvlMultipl[2] * victoryMultip - finalScore) >= 0.5f)
			finalScore++;
		//INSERT CODE FOR UPDATING LEVEL MULTIPLIER BITMAP
		break;

	case testLevel:
		finalScore = 888 * victoryMultip;
		break;
	}
	EndGTxt2->SetLabel( wxString("FINAL SCORE: ") <<std::to_string(finalScore));
	EndGTxt3->SetLabel( wxString("Base score: ") <<std::to_string(GetBaseScore()));
}