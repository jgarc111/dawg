#include "page.h"
#include "text.h"

dawgPage::dawgPage(dawgFrame* frame, const wxString& title)
{
	panel = new wxPanel(frame->nbMain);
	frame->nbMain->AddPage(panel, title);
	vbox = new wxBoxSizer(wxVERTICAL);
	//panel->SetSizer(vbox);
}

dawgPage::~dawgPage(void)
{
	free(vbox);
	free(panel);
}
