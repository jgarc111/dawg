#pragma once
#include <string>
#include <wx/wx.h>
#include "page.h"

#define TEXT_BLOCK_HEIGHT 48

class dawgBlock
{
public:
	dawgBlock(dawgPage* page,
		const wxString& key,
		const std::string& def);
	std::string GetValue();
	std::string GetTextValue();
	~dawgBlock(void);

private:
	wxStaticText *label;
	wxTextCtrl   *textctrl;
	wxString     wxDef;
};
