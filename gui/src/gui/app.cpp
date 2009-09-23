#include "app.h"
#include "frame.h"

IMPLEMENT_APP( DawgGUI );

bool DawgGUI::OnInit()
{
	FrameTask* frmTask = new FrameTask(wxT("Add New Dawg Task"));
	frmTask->Show(true);
	return true;
}
