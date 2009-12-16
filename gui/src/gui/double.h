#pragma once
#include <wx/wx.h>
#include <wx/string.h>
#include "frame.h"
#include "page.h"

class dawgDouble
{
public:
	dawgDouble(dawgPage* page,
		const wxString& key,
		const wxString& value = wxEmptyString);
	~dawgDouble(void);

private:
	wxBoxSizer   *hbox;
	wxStaticText *statictext;
	wxTextCtrl   *textctrl;
};
