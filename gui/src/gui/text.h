#pragma once
#include <wx/wx.h>
#include <wx/string.h>
#include "frame.h"
#include "page.h"

class dawgText
{
public:
	dawgText(dawgPage* page,
		const wxString& key,
		const std::string &value);
	~dawgText(void);

private:
	wxBoxSizer   *hbox;
	wxStaticText *statictext;
	wxTextCtrl   *textctrl;
};
