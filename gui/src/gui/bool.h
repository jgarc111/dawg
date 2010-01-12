#pragma once
#include <wx/wx.h>
#include <wx/string.h>
#include "frame.h"
#include "page.h"

class dawgBool
{
public:
	dawgBool(dawgPage* page, const wxString& key, bool def = false);
	~dawgBool(void);

private:
	wxStaticText *label;
	wxCheckBox   *checkbox;
};
