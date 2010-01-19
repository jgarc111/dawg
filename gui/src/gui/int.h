#pragma once
#include <wx/wx.h>
#include "page.h"

class dawgIntegar
{
public:
	dawgIntegar(dawgPage* page, const wxString& key, int def);
	~dawgIntegar(void);

private:
	wxStaticText *label;
	wxTextCtrl   *textctrl;
};
