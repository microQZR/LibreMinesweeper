#include "cApp.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp() {
	// TODO Auto-generated constructor stub

}

cApp::~cApp() {
	// TODO Auto-generated destructor stub
}

bool cApp::OnInit()
{
	wxImage::AddHandler(new wxPNGHandler());//for use when loading png files to wxImage
	m_frame1 = new cMain();
	m_frame1->Show();
	return true;
}
