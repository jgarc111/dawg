#pragma once
#include <wx/wx.h>
#include <wx/notebook.h>

class FrameTask :
	public wxFrame
{
public:
	FrameTask(const wxString& title);
	void OnButtonExit(wxCommandEvent& eventQuit);
	wxNotebook *nbMain;
	wxPanel *pnlFrm, *pnlSeq, *pnlSub, *pnlInd, *pnlMisc;
	wxBoxSizer *vbsFrm, *vbsMain, *vbsNb, *vbsSeq, *vbsSub, *vbsInd, *vbsMisc,
		*hboxSubParams, *hboxSubACGT, *hboxIndParams, *hbsBottom;
	wxFlexGridSizer *fgsSeq, *fgsSub, *fgsInd, *fgsMisc;
	wxStaticBoxSizer *sbsSeq, *sbsSub, *sbsInd, *sbsMisc;
	wxStaticText *stSeqTree, *stSeqLen,
		*stSubModel, *stSubParams, *stSubACGT, *stSubGamma, *stSubIota,
		*stIndLambda, *stIndModel, *stIndParams, *stIndVerbose, *stIndHideLen,
		*stMiscReps, *stMiscSeed, *stMiscFormat, *stMiscInFile, *stMiscSvFile;
	wxChoice *chSubModel, *chIndModel, *chMiscFormat;
	wxTextCtrl *tcSeqTree, *tcSeqLen,
		*tcSubParam1, *tcSubParam2, *tcSubParam3, *tcSubParam4, *tcSubParam5, *tcSubParam6,
		*tcSubACGT1, *tcSubACGT2, *tcSubACGT3, *tcSubACGT4, *tcSubGamma, *tcSubIota,
		*tcIndLambda, *tcIndParam1, *tcIndParam2,
		*tcMiscReps, *tcMiscSeed;
	wxCheckBox *cbIndVerbose, *cbIndHideLen, *cbMiscInFile, *cbMiscSvFile;
	wxButton *btnSubmit, *btnExit;
	wxMenuBar *menubarMain;
	wxMenu *menuFile, *menuEdit, *menuHelp;
	~FrameTask(void);
};
