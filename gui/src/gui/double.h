#pragma once
#include <wx/wx.h>
#include "page.h"

class dawgDouble
{
public:
	dawgDouble(dawgPage* page, const wxString& key, double def);
	~dawgDouble(void);

private:
	wxStaticText *label;
	wxTextCtrl   *textctrl;
	wxString     wxDef;
};
