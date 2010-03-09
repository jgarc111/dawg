#pragma once
#include <wx/wx.h>
#include "page.h"

class dawgIntegar
{
public:
	dawgIntegar(dawgPage* page,
		const wxString& key, unsigned int def);
	unsigned int GetValue();
	std::string GetTextValue();
	~dawgIntegar(void);

private:
	wxStaticText *label;
	wxTextCtrl   *textctrl;
	wxString     wxDef;
};
