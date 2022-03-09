#ifndef CAPP_H_
#define CAPP_H_

#include "wx/wx.h"
#include "cMain.h"


class cApp : public wxApp {
public:
	cApp();
	virtual ~cApp();
	virtual bool OnInit();

private:
	cMain* m_frame1 = nullptr;
};

#endif /* CAPP_H_ */
