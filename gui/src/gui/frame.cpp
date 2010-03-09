#include "frame.h"

dawgFrame::dawgFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title,
	wxDefaultPosition, wxSize(600, 600))
{
	Centre();

	menubar = new wxMenuBar;
	BuildMenuBar(menubar);
	SetMenuBar(menubar);

	panel  = new wxPanel(this);
	sizer  = new wxBoxSizer(wxVERTICAL);
	panel->SetSizer(sizer);

	book  = new wxListbook(panel, wxID_ANY);
	sizer->Add(book, 1, wxEXPAND | wxALL, 8);

	hbsBottom = new wxBoxSizer(wxHORIZONTAL);
	BuildBottom(hbsBottom);
	sizer->Add(hbsBottom, 0,
		wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);

}

void dawgFrame::BuildMenuBar(wxMenuBar* menubar)
{
	menuFile = new wxMenu;
	menuFile->Append(wxID_NEW, wxT("&New"));
	menuFile->Append(wxID_OPEN, wxT("&Open"));
	menuFile->Append(wxID_EXIT, wxT("&Save"));
	menuFile->Append(wxID_EXIT, wxT("Save &As..."));
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT, wxT("E&xit"));
	menubar->Append(menuFile, wxT("&File"));
	menuEdit = new wxMenu;
	menuEdit->Append(wxID_CUT, wxT("Cu&t"));
	menuEdit->Append(wxID_COPY, wxT("&Copy"));
	menuEdit->Append(wxID_PASTE, wxT("&Paste"));
	menuEdit->Append(wxID_DELETE, wxT("&Delete"));
	menubar->Append(menuEdit, wxT("&Edit"));
	menuHelp = new wxMenu;
	menuHelp->Append(wxID_HELP, wxT("&Help"));
	menuHelp->AppendSeparator();
	menuHelp->Append(wxID_ABOUT, wxT("&About"));
	menubar->Append(menuHelp, wxT("&Help"));
}

void dawgFrame::BuildBottom(wxBoxSizer* hbsBottom)
{
	btnSubmit = new wxButton(panel, DAWG_ID_SUBMIT, wxT("Submit"), wxPoint(20, 400), wxDefaultSize);
	btnSubmit->SetFocus();
	btnExit = new wxButton(panel, wxID_EXIT, wxT("Exit"), wxPoint(20, 400), wxDefaultSize);
	Connect(DAWG_ID_SUBMIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(dawgFrame::OnButtonSubmit));
	Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(dawgFrame::OnButtonExit));
	hbsBottom->Add(btnSubmit, 0, wxLEFT, 10);
	hbsBottom->Add(btnExit, 0, wxLEFT, 10);
}

void dawgFrame::OnButtonSubmit(wxCommandEvent & WXUNUSED(event))
{
	// To do
}

void dawgFrame::OnButtonExit(wxCommandEvent & WXUNUSED(event))
{
	Close(true);
}

dawgFrame::~dawgFrame(void)
{
}
