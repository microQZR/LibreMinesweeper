#ifndef CMAIN_H_
#define CMAIN_H_

#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	enum gameLevel : char
	{
		levelEasy = 15, levelMedium = 30, levelHard = 45
	};

	cMain();
	virtual ~cMain();
	int nFieldWidth = 10;
	int nFieldHeight = 10;
	wxButton **btn;
	int *nField = nullptr; //array mask for registering presence of mines
	bool bFirstClick = true;
	wxDialog *endGameDial;
	wxDialog *SettingsDial;
	wxSlider *SettingsSlider;
	wxStaticText *SettingsTxtDescr;
	bool hasClosed = false;
	gameLevel lvlSelect = levelMedium;

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
	void OnClickDialogSettings(wxCommandEvent &evt);
	void OnClickQuit(wxCommandEvent &evt);
	void OnLevelSelect(wxCommandEvent &evt);
	void OnClickSettingsOK(wxCommandEvent &evt);
	void OnClickSettingsCancel(wxCommandEvent &evt);

	wxDECLARE_EVENT_TABLE();
};

#endif /* CMAIN_H_ */
