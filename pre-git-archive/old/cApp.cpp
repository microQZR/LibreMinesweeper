/*
 * cApp.cpp
 *
 *  Created on: Aug 19, 2020
 *      Author: qzr
 */

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
	m_frame1 = new cMain();
	m_frame1->Show();
	return true;
}
