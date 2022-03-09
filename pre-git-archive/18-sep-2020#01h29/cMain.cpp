#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
wxEND_EVENT_TABLE()

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
	
	wxButton *settingsButton = new wxButton(toolbar1, 9001, "Setings", wxDefaultPosition, wxSize(40,40), 0);
	wxButton *forfeitButton = new wxButton(toolbar1, 9002, "Forfeit", wxDefaultPosition, wxSize(40,40), 0);
	wxButton *restartButton = new wxButton(toolbar1, 9003, "Restart", wxDefaultPosition, wxSize(40,40), 0);
    //##To be implemented##//SettingsB->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnSelectColour), nullptr, this);
	//settingsButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnClickSettings));
	

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
	wxStaticText *statsbarTxt = new wxStaticText(statsbar1, wxID_ANY, wxString("Hello!"), wxPoint(400,0));
	wxStaticBitmap *statsbarBMP = new wxStaticBitmap(statsbar1, wxID_ANY, *mineFlag, wxDefaultPosition, wxSize(20,20));//Working as should
	wxSlider *m_ZoomSlider = new wxSlider(statsbar1, 20001, 8, 1, 32, wxDefaultPosition, wxSize(200,20));//Working as should
	statsSizer->Add(statsbarTxt, 1, wxALIGN_CENTER);
	statsSizer->Add(statsbarBMP, 1, wxALIGN_CENTER);
	statsSizer->Add(m_ZoomSlider, 1, wxALIGN_CENTER);
	statsbar1->SetSizer(statsSizer);
	//END SECTION

	//##//End-game dialog section start//
	endGameDial = new wxDialog(this, 7000, wxString("Game Ended"));//add parameters
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
	wxStaticText *EndGTxt1 = new wxStaticText(endGameDial, wxID_ANY, wxString("Booom! Wrong Step!"));
	wxStaticText *EndGTxt2 = new wxStaticText(endGameDial, wxID_ANY, wxString("YOUR SCORE IS: "));
	bool qqq = EndGTxt2->SetBackgroundColour(*wxBLUE);
	wxStaticText *EndGTxt3 = new wxStaticText(endGameDial, wxID_ANY, wxString("###"));
	qqq = EndGTxt3->SetBackgroundColour(*wxBLUE);
	wxButton *EndGBtn1 = new wxButton(endGameDial, 7001, "Setings", wxDefaultPosition, wxSize(40,40));
	wxButton *EndGBtn2 = new wxButton(endGameDial, 7002, "Restart", wxDefaultPosition, wxSize(40,40));
	wxButton *EndGBtn3 = new wxButton(endGameDial, 7003, "Quit", wxDefaultPosition, wxSize(40,40));
	hbox1_EndGame->Add(EndGBmp1, 1, wxALIGN_CENTER | wxRIGHT, 10);
	hbox1_EndGame->Add(EndGTxt1, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
	hbox1_EndGame->Add(EndGBmp2, 1, wxALIGN_CENTER | wxLEFT, 10);
	hbox2_EndGame->Add(EndGTxt2, 1, wxALIGN_CENTER | wxRIGHT, 10);
	hbox2_EndGame->Add(EndGTxt3, 1, wxALIGN_CENTER);
	hbox3_EndGame->Add(EndGBtn1, 0, wxALIGN_CENTER | wxRIGHT, 10);
	hbox3_EndGame->Add(EndGBtn2, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
	hbox3_EndGame->Add(EndGBtn3, 0, wxALIGN_CENTER | wxLEFT, 10);
	vboxEndGame->Add(hbox1_EndGame, 1, wxALIGN_CENTER);
	vboxEndGame->Add(hbox2_EndGame, 1, wxALIGN_CENTER);
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
	SettingsTxtDescr = new wxStaticText(SettingsDial, wxID_ANY, wxString("Blah Blah Blah"));
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

	//##//Event binding section start//
	Bind(wxEVT_BUTTON, &cMain::OnClickSettings, this, 9001);
	Bind(wxEVT_BUTTON, &cMain::OnClickForfeit, this, 9002);
	Bind(wxEVT_BUTTON, &cMain::OnClickRestart, this, 9003);
	EndGBtn3->Bind(wxEVT_BUTTON, &cMain::OnClickQuit, this, 7003);
	EndGBtn2->Bind(wxEVT_BUTTON, &cMain::OnClickDialogRestart, this, 7002);
	EndGBtn1->Bind(wxEVT_BUTTON, &cMain::OnClickDialogSettings, this, 7001);
	SettingsDial->Bind(wxEVT_SLIDER, &cMain::OnLevelSelect, this, 7051);
	SettingsDial->Bind(wxEVT_BUTTON, &cMain::OnClickSettingsOK, this, wxID_OK);
	SettingsDial->Bind(wxEVT_BUTTON, &cMain::OnClickSettingsCancel, this, wxID_CANCEL);
	//Event binding section end//

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
		//Display end game message
		int aaa = endGameDial->ShowModal();
		if (hasClosed == true) hasClosed = this->Close();

		// Rest game
		wxCommandEvent *qqq;
		OnClickRestart(*qqq);

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
				btn[y*nFieldWidth + x]->SetLabel(std::to_string(mine_count));
			}
	}
	
	
	evt.Skip();
}


void cMain::OnRightClick(wxMouseEvent &evt)
{
	// Get coordinate of button in field array
	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;

	if(!hasMineFlag[y*nFieldWidth + x])
	btn[y*nFieldWidth + x]->SetLabel("X");

	else
	btn[y*nFieldWidth + x]->SetLabel("");

	hasMineFlag[y*nFieldWidth + x] = !hasMineFlag[y*nFieldWidth + x];
	
	evt.Skip();

}

void cMain::OnClickForfeit(wxCommandEvent &evt)
{
	wxMessageBox("==YOU HAVE JUST CLICKED FORFEIT==");
}

void cMain::OnClickSettings(wxCommandEvent &evt)
{
	int xyz = SettingsDial->ShowModal();
}

void cMain::OnClickRestart(wxCommandEvent &evt)
{
	bFirstClick = true;
		for (int x = 0; x < nFieldWidth; x++)
			for (int y = 0; y < nFieldHeight; y++)
			{
				nField[y*nFieldWidth + x] = 0;
				btn[y*nFieldWidth + x]->SetLabel("");
				btn[y*nFieldWidth + x]->Enable(true);
				hasMineFlag[y*nFieldWidth + x] = false;
			}
}

void cMain::OnClickDialogSettings(wxCommandEvent &evt)
{
	int xyz = SettingsDial->ShowModal();
}

void cMain::OnClickDialogRestart(wxCommandEvent &evt)
{
	endGameDial->EndModal(88);
}

void cMain::OnClickQuit(wxCommandEvent &evt)
{
	hasClosed = true;
	endGameDial->Destroy();
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
	wxCommandEvent *ccc;
	OnLevelSelect(*ccc);
	SettingsDial->EndModal(88);
}