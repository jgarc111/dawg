#pragma once
#include <wx/wx.h>
#include <wx/string.h>
#include "frame.h"
#include "page.h"

class dawgBool
{
public:
	dawgBool(dawgPage* page,
		const wxString& key,
		const bool value = false);
	~dawgBool(void);

private:
	wxBoxSizer   *hbox;
	wxCheckBox   *checkbox;
};
