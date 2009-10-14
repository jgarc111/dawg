#ifndef DAWG_GUI_H
#define DAWG_GUI_H

#include <wx/app.h>
#include "frame.h"
#include "page.h"
#include "text.h"

class DawgGUI : public wxApp
{
public:
	virtual bool OnInit();
};

#endif // APP_H
