#include "app.h"
#include "frame.h"

IMPLEMENT_APP( MyApp );

bool MyApp::OnInit()
{
	//wxTest_1Frame* frameMain = new wxTest_1Frame();
	//frameMain->SetIcon( wxICON( amain ) );
	//frameMain->Show(true);
	wxTestFrame* frameAddTask = new wxTestFrame(wxT("Add New Dawg Task"));
	frameAddTask->Show(true);
	return true;
}
