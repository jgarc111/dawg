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
		const wxString& value = wxEmptyString);
	~dawgText(void);

private:
	wxBoxSizer   *hbsText;
	wxStaticText *stKey;
	wxTextCtrl   *tcValue;
};
