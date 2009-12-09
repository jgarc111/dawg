#include "app.h"

IMPLEMENT_APP( DawgGUI );

bool DawgGUI::OnInit()
{
	dawgFrame *frmTask = new dawgFrame(wxT("Add New Dawg Task"));
	frmTask->Show(true);
	dawgPage *pgTest  = new dawgPage(frmTask, wxT("Test"));
	//dawgText *txtTest = new dawgText(pgTest, wxT("Test Key:"), wxT("Test Value"));
	return true;
}
