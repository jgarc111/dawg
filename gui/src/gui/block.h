#pragma once
#include <string>
#include <wx/wx.h>
#include "page.h"

#define BLOCK_HEIGHT 48

class dawgBlock
{
public:
	dawgBlock(dawgPage* page, const wxString& key, const std::string& def);
	~dawgBlock(void);

private:
	wxStaticText *label;
	wxTextCtrl   *textctrl;
};
