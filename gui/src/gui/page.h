#pragma once
#include <wx/wx.h>
#include "frame.h"

class dawgPage
{
public:
	dawgPage(dawgFrame*, const wxString&);
	~dawgPage(void);
	wxPanel    *panel;
	wxBoxSizer *vbox;

private:
};
