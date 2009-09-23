#include "panel.h"

BEGIN_EVENT_TABLE(wxTest_1Panel, MainPanel)
	EVT_BUTTON(ID_MAIN_OK, wxTest_1Panel::OnOK)
END_EVENT_TABLE()

wxTest_1Panel::wxTest_1Panel( wxWindow* parent )
	: MainPanel( parent )
{
}

wxTest_1Panel::~wxTest_1Panel()
{
}

void wxTest_1Panel::OnOK( wxCommandEvent& event )
{
	wxMessageBox( wxT("OK Button Pressed") );
}
