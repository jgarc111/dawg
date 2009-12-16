#include "app.h"

IMPLEMENT_APP( DawgGUI );

bool DawgGUI::OnInit()
{
	dawgFrame *frmTest = new dawgFrame(wxT("Dawg Test Frame"));
	frmTest->Show(true);
	dawgPage *pgTest  = new dawgPage(frmTest, wxT("Test"));
	dawgText *txtTest1 = new dawgText(pgTest, wxT("Test Key 1:"), wxT("Test Value 1"));
	dawgText *txtTest2 = new dawgText(pgTest, wxT("Test Key 2:"), wxT("Test Value 2"));
	dawgText *txtTest3 = new dawgText(pgTest, wxT("Test Key 3:"), wxT("Test Value 3"));
	#define XM(name, type, def) new dawgPage(frmTest, wxT("type _V(name)"));
	#include "dawgma.xmh"
	#undef XM
	return true;
}
