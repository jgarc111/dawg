#include "app.h"
#include "about.h"

// About dialog's event loop.
// Not needed because we only have a default OK button.
//BEGIN_EVENT_TABLE( About, AboutDlg )
	//EVT_BUTTON( wxID_OK, About::OnOK )
//END_EVENT_TABLE()

About::About( wxWindow* parent )
	: AboutDlg( parent, -1 )
{
	// Get the file version.
	wxString fileVersion = wxT("TODO");
	
	// Set the version label.
	m_staticVersion->SetLabel( m_staticVersion->GetLabel() + wxT(" ") + fileVersion );
	
	// Resize to fit the contents.
	this->GetSizer()->SetSizeHints( this );
}

