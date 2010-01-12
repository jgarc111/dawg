#include "page.h"
#include "text.h"

dawgPage::dawgPage(dawgFrame* frame, const wxString& title)
{
	panel = new wxPanel(frame->notebook);
	frame->notebook->AddPage(panel, title);
	hbox  = new wxBoxSizer(wxHORIZONTAL);
	panel->SetSizer(hbox);
	sizer = new wxFlexGridSizer(2, 10, 10);
	sizer->AddGrowableCol(1);
	hbox->Add(sizer, 1, wxALL, 10);
}

dawgPage::~dawgPage(void)
{
	delete sizer, hbox, panel;
}
