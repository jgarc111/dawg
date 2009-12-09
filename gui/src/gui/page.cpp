#include "page.h"
#include "text.h"

dawgPage::dawgPage(dawgFrame* frame, const wxString& title)
{
	pnlPage = new wxPanel(frame->nbMain);
	frame->nbMain->AddPage(pnlPage, title);
	vbsPage = new wxBoxSizer(wxVERTICAL);
	pnlPage->SetSizer(vbsPage);
}

dawgPage::~dawgPage(void)
{
}
