#pragma once
#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/toolbook.h>
#include <wx/listbook.h>
#include <wx/spinctrl.h>

class dawgFrame :
	public wxFrame
{
public:
	dawgFrame(const wxString& title);
	~dawgFrame(void);
	wxPanel    *panel;
	wxBoxSizer *vbox;
	//wxNotebook *book;
	wxListbook *book;
	//wxToolbook *book;
	wxMenuBar  *menubar;

private:
	void BuildMenuBar(wxMenuBar* menubar);
	void BuildBottom(wxBoxSizer* hbsBottom);
	void OnButtonExit(wxCommandEvent& eventQuit);
	wxBoxSizer *hbsBottom;
	wxButton *btnSubmit, *btnExit;
	wxMenu *menuFile, *menuEdit, *menuHelp;
};
