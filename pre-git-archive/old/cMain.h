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


	void OnButtonClicked(wxCommandEvent &evt);
	//void OnRightClick(wxCommandEvent &evt); //***//

	wxDECLARE_EVENT_TABLE();
};

#endif /* CMAIN_H_ */
