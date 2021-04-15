/*
 * cMain.h
 *
 *  Created on: Aug 19, 2020
 *      Author: qzr
 */

#ifndef CMAIN_H_
#define CMAIN_H_

#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	enum gameLevel : char
	{
		levelEasy = 15, levelMedium = 30, levelHard = 45, testLevel = 3
	};

	cMain();
	virtual ~cMain();
	int nFieldWidth = 10;
	int nFieldHeight = 10;
	wxButton **btn;
	int *nField = nullptr; //array mask for registering presence of mines
	bool bFirstClick = true;
	wxDialog *endGameDial;
	wxStaticText *EndGTxt1;
	wxStaticText *EndGTxt2;
	wxStaticText *EndGTxt3;
	wxDialog *SettingsDial;
	wxSlider *SettingsSlider;
	wxStaticText *SettingsTxtDescr;
	bool hasClosed = false;
	gameLevel lvlSelect = levelMedium; //THE DEFAULT TO BE RESTORE AFTER TESTING!!!
	//gameLevel lvlSelect = testLevel; //THIS IS A TEST LINE
	int flagCount = 0;
	bool alreadyForfeit = false; //state flag to enable/diable forfeit button
	wxStaticText *statsbarTxt2; //some status bar text with flags remaining count
	wxStaticText *statsbarTxt4; //status bar score label
	bool victoryAchieved = false; //victory flag

	//Score keeping elements
	int scoreUnit = 0;
	float baseMultipl[3] = {11.765, 14.286, 18.182};
	float lvlMultipl[3] = {1.0, 1.5, 2.0};

	//##//Indicates presence of mine flags over buttons
	bool *hasMineFlag = nullptr;

	//##//Add a toolbar for control
	wxToolBar *toolbar1 = nullptr;

	//##//Add a status bar
	wxStatusBar *statsbar1 = nullptr;


	void OnButtonClicked(wxCommandEvent &evt);
	void OnRightClick(wxMouseEvent &evt); //***//
	void OnClickForfeit(wxCommandEvent &evt);
	void OnClickSettings(wxCommandEvent &evt);
	void OnClickRestart(wxCommandEvent &evt);
	void OnClickDialogRestart(wxCommandEvent &evt);
	//void OnClickDialogSettings(wxCommandEvent &evt);
	void OnClickQuit(wxCommandEvent &evt);
	void OnLevelSelect(wxCommandEvent &evt);
	void OnClickSettingsOK(wxCommandEvent &evt);
	void OnClickSettingsCancel(wxCommandEvent &evt);
	void ResetSettingsMsg();
	void ResetEndGMsg();
	int GetBaseScore();
	void UpdateEndGameScore();

	wxDECLARE_EVENT_TABLE();
};

#endif
