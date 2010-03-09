#pragma once
#include <wx/wx.h>
#include "page.h"

class dawgDouble
{
public:
	dawgDouble(dawgPage* page,
		const wxString& key,
		double def);
	double GetValue();
	std::string GetTextValue();
	~dawgDouble(void);

private:
	wxStaticText *label;
	wxTextCtrl   *textctrl;
	wxString     wxDef;
};
