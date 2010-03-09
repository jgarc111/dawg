#pragma once
#include <wx/wx.h>
#include "frame.h"

#define LABEL_MIN_WIDTH 100

class dawgPage
{
public:
	dawgPage(dawgFrame*, const wxString&);
	~dawgPage(void);
	wxPanel *panel;
	wxFlexGridSizer *sizer;

private:
	wxBoxSizer *hbox;
};
