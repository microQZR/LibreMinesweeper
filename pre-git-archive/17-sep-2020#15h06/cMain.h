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
	cMain();
	virtual ~cMain();
	int nFieldWidth = 10;
	int nFieldHeight = 10;
	wxButton **btn;
	int *nField = nullptr;
	bool bFirstClick = true;
	wxDialog *endGameDial;
	wxDialog *SettingsDial;
	bool hasClosed = false;

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
	void OnClickQuit(wxCommandEvent &evt);

	wxDECLARE_EVENT_TABLE();
};

#endif /* CMAIN_H_ */
