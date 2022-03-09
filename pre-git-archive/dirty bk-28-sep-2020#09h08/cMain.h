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

	//Main button array section
	int nFieldWidth = 10;
	int nFieldHeight = 10;
	wxBitmapButton **btn; //changed from wxButton to wxBitmapButton
	int *nField = nullptr; //array mask for registering presence of mines
	bool *hasMineFlag = nullptr; //Indicates presence of mine flags over buttons
	int flagCount = 0;
	bool bFirstClick = true;
	
	//End game dialog section
	bool hasClosed = false;
	wxDialog *endGameDial = nullptr;
	wxStaticText *EndGTxt1 = nullptr;
	wxStaticText *EndGTxt2 = nullptr;
	wxStaticText *EndGTxt3 = nullptr;
	wxStaticText *EndGTxt4 = nullptr;
	wxBoxSizer *hbox1_EndGame = nullptr; //End game dialog top sizer
	wxBoxSizer *hboxExtra_EndGame = nullptr; //End game dialog score breakdown and multiplier sizer
	wxBoxSizer *vboxEndGame = nullptr;
	wxStaticBitmap *EndGBmp_TL = nullptr; //Top left bitmap
	wxStaticBitmap *EndGBmp_TR = nullptr; //Top right bitmap
	wxStaticBitmap *EndGBmpMultiplier1 = nullptr; //1st multiplier bitmap
	//wxStaticBitmap *EndGBmpMultiplier2 = nullptr; //2nd multiplier bitmap//DEBUG//moved object declaration to implementation file
	
	//Settings dialog section
	wxDialog *SettingsDial = nullptr;
	wxSlider *SettingsSlider = nullptr;
	wxStaticText *SettingsTxtDescr = nullptr;
		
	//Status bar section
	wxStatusBar *statsbar1 = nullptr; //Add a status bar
	wxStaticText *statsbarTxt2 = nullptr; //some status bar text with flags remaining count
	wxStaticText *statsbarTxt4 = nullptr; //status bar score label
	
	//MISC elements section
	//gameLevel lvlSelect = levelMedium; //THE DEFAULT TO BE RESTORE AFTER TESTING!!!
	gameLevel lvlSelect = testLevel; //THIS IS A TEST LINE
	bool alreadyForfeit = false; //state flag to enable/diable forfeit button
	bool victoryAchieved = false; //victory flag
	
	//Score keeping elements
	int scoreUnit = 0;
	float baseMultipl[3] = {11.765, 14.286, 18.182};
	float lvlMultipl[3] = {1.0, 1.5, 2.0};



	void OnButtonClicked(wxCommandEvent &evt);
	void OnRightClick(wxMouseEvent &evt); //***//
	void OnClickForfeit(wxCommandEvent &evt);
	void OnClickSettings(wxCommandEvent &evt);
	void OnClickRestart(wxCommandEvent &evt);
	void OnClickDialogRestart(wxCommandEvent &evt);
	//void OnClickDialogSettings(wxCommandEvent &evt);
	void OnClickQuit(wxCommandEvent &evt);
	void OnSliderLevelSelect(wxCommandEvent &evt);
	void OnClickSettingsOK(wxCommandEvent &evt);
	void OnClickSettingsCancel(wxCommandEvent &evt);
	//void ResetSettingsMsg(); //Phased out useless
	//void ResetEndGMsg(); //Unused
	int GetBaseScore();
	void UpdateEndGameScore();
	void InvokeEndGameDialog();

//Preparing bitmaps & graphics for use
	wxImage *imgFlag = new wxImage(wxString("Resources/Flag.png"), wxBITMAP_TYPE_PNG);
	wxImage *imgMine = new wxImage(wxString("Resources/Mine.png"), wxBITMAP_TYPE_PNG);
	wxImage *img1 = new wxImage(wxString("Resources/digits-mainV2/1.png"), wxBITMAP_TYPE_PNG);
	wxImage *img2 = new wxImage(wxString("Resources/digits-mainV2/2.png"), wxBITMAP_TYPE_PNG);
	wxImage *img3 = new wxImage(wxString("Resources/digits-mainV2/3.png"), wxBITMAP_TYPE_PNG);
	wxImage *img4 = new wxImage(wxString("Resources/digits-mainV2/4.png"), wxBITMAP_TYPE_PNG);
	wxImage *img5 = new wxImage(wxString("Resources/digits-mainV2/5.png"), wxBITMAP_TYPE_PNG);
	wxImage *img6 = new wxImage(wxString("Resources/digits-mainV2/6.png"), wxBITMAP_TYPE_PNG);
	wxImage *img7 = new wxImage(wxString("Resources/digits-mainV2/7.png"), wxBITMAP_TYPE_PNG);
	wxImage *img8 = new wxImage(wxString("Resources/digits-mainV2/8.png"), wxBITMAP_TYPE_PNG);
	wxImage *imgSettings = new wxImage("Resources/Settings-cog.png", wxBITMAP_TYPE_PNG);
	wxImage *imgForfeit = new wxImage("Resources/Forfeit.png", wxBITMAP_TYPE_PNG);
	wxImage *imgRestart = new wxImage("Resources/Restart.png", wxBITMAP_TYPE_PNG);
	wxImage *imgExit = new wxImage("Resources/Exit.png", wxBITMAP_TYPE_PNG);
	wxImage *imgMultiplierX1 = new wxImage("Resources/MultiplierX1V2.png", wxBITMAP_TYPE_PNG);
	wxImage *imgMultiplierX1_5 = new wxImage("Resources/MultiplierX1_5.png", wxBITMAP_TYPE_PNG);
	wxImage *imgMultiplierX2 = new wxImage("Resources/MultiplierX2.png", wxBITMAP_TYPE_PNG);
	wxImage *imgMultiplierX2Victory = new wxImage("Resources/MultiplierX2V2.png", wxBITMAP_TYPE_PNG);

	wxImage *imgEndGDial_TR = new wxImage("Resources/Skull and Bones (EndGDial-TR).png", wxBITMAP_TYPE_PNG);
	wxImage *imgEndGDial_TL = new wxImage("Resources/Mushroom Cloud (EndGDial-TL).png", wxBITMAP_TYPE_PNG);
	wxImage *imgForfeitDial_TL = new wxImage("Resources/Hat and Scope (Forfeit Dial TL).png", wxBITMAP_TYPE_PNG);
	wxImage *imgForfeitDial_TR = new wxImage("Resources/Pondering Emoji (Forfeit Dial TR).png", wxBITMAP_TYPE_PNG);
	wxImage *imgWinningDial_TLTR = new wxImage("Resources/Trophy (Winning Dialog TL&TR).png", wxBITMAP_TYPE_PNG);

	wxBitmap *bmpFlag30p = new wxBitmap(imgFlag->Scale(30,30, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmpFlag20p = new wxBitmap(imgFlag->Scale(20,20, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmpMine40p = new wxBitmap(imgMine->Scale(40,40, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmpSettings40p = new wxBitmap(imgSettings->Scale(40,40, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmpSettings25p = new wxBitmap(imgSettings->Scale(25,25, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmpForfeit40p = new wxBitmap(imgForfeit->Scale(40,40, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmpRestart40p = new wxBitmap(imgRestart->Scale(40,40, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmpRestart25p = new wxBitmap(imgRestart->Scale(25,25, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmpExit25p = new wxBitmap(imgExit->Scale(25,25, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmpMultiplierX1_55p = new wxBitmap(imgMultiplierX1->Scale(55,55, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmpMultiplierX2_55p = new wxBitmap(imgMultiplierX2->Scale(55,55, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmpMultiplierX1_5_55p = new wxBitmap(imgMultiplierX1_5->Scale(55,55, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmpMultiplierX2Victory_55p = new wxBitmap(imgMultiplierX2Victory->Scale(55,55, wxIMAGE_QUALITY_HIGH));
	
	wxBitmap *bmpEndGDial_TL40p = new wxBitmap(imgEndGDial_TL->Scale(40,40, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmpEndGDial_TR40p = new wxBitmap(imgEndGDial_TR->Scale(40,40, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmpForfeitDial_TL40p = new wxBitmap(imgForfeitDial_TL->Scale(40,40, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmpForfeitDial_TR40p = new wxBitmap(imgForfeitDial_TR->Scale(40,40, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmpWinningDial_TLTR65p = new wxBitmap(imgWinningDial_TLTR->Scale(65,65, wxIMAGE_QUALITY_HIGH));

	wxBitmap *bmp1_30p = new wxBitmap(img1->Scale(40,40, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmp2_30p = new wxBitmap(img2->Scale(40,40, wxIMAGE_QUALITY_HIGH));	
	wxBitmap *bmp3_30p = new wxBitmap(img3->Scale(40,40, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmp4_30p = new wxBitmap(img4->Scale(40,40, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmp5_30p = new wxBitmap(img5->Scale(40,40, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmp6_30p = new wxBitmap(img6->Scale(40,40, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmp7_30p = new wxBitmap(img7->Scale(40,40, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmp8_30p = new wxBitmap(img8->Scale(40,40, wxIMAGE_QUALITY_HIGH));
	wxBitmap *bmpBlank = new wxBitmap(wxString("Resources/blank.png"), wxBITMAP_TYPE_PNG);
//end section

};

#endif
