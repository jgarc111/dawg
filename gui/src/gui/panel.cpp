#include "panel.h"

BEGIN_EVENT_TABLE(Panel, MainPanel)
	EVT_BUTTON(ID_MAIN_OK, Panel::OnOK)
END_EVENT_TABLE()

Panel::Panel( wxWindow* parent )
	: MainPanel( parent )
{
}

Panel::~Panel()
{
}

void Panel::OnOK( wxCommandEvent& event )
{
	wxMessageBox( wxT("OK Button Pressed") );
}
