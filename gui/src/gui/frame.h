#pragma once
#include <wx/wx.h>
#include <wx/listbook.h>
#include <wx/spinctrl.h>

class dawgFrame :
	public wxFrame
{
public:
	dawgFrame(const wxString& title);
	~dawgFrame(void);
	wxPanel    *panel;
	wxListbook *book;
	wxMenuBar  *menubar;

private:
	void BuildMenuBar(wxMenuBar* menubar);
	void BuildBottom(wxBoxSizer* hbsBottom);
	void OnButtonExit(wxCommandEvent& eventQuit);
	wxBoxSizer *sizer;
	wxBoxSizer *hbsBottom;
	wxButton   *btnSubmit, *btnExit;
	wxMenu     *menuFile, *menuEdit, *menuHelp;
};
