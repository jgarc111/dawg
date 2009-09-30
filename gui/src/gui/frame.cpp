#include "frame.h"

FrameTask::FrameTask(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 360))
{
	Centre();
	pnlFrm  = new wxPanel(this, wxID_ANY);
	vbsFrm  = new wxBoxSizer(wxVERTICAL);
	pnlFrm->SetSizer(vbsFrm);

	nbMain  = new wxNotebook(pnlFrm, wxID_ANY);
	vbsFrm->Add(nbMain, 1, wxEXPAND | wxALL, 8);

	pnlSeq  = new wxPanel(nbMain, wxID_ANY);
	pnlSub  = new wxPanel(nbMain, wxID_ANY);
	pnlInd  = new wxPanel(nbMain, wxID_ANY);
	pnlMisc = new wxPanel(nbMain, wxID_ANY);

	nbMain->AddPage(pnlSeq, wxT("Sequence"),       true);
	nbMain->AddPage(pnlSub, wxT("Substitution"),   false);
	nbMain->AddPage(pnlInd, wxT("Indels"),         false);
	nbMain->AddPage(pnlMisc, wxT("Miscellaneous"), false);

	// Sequence Panel

	vbsSeq    = new wxBoxSizer(wxVERTICAL);
	fgsSeq    = new wxFlexGridSizer(2, 2, 8, 8);
	vbsSeq->Add(fgsSeq, 1, wxEXPAND | wxALL, 10);
	pnlSeq->SetSizer(vbsSeq);

	stSeqTree = new wxStaticText(pnlSeq, wxID_ANY, wxT("Tree:"));
	stSeqLen  = new wxStaticText(pnlSeq, wxID_ANY, wxT("Length:"));
	tcSeqTree = new wxTextCtrl(pnlSeq, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(-1, 60), wxTE_MULTILINE);
	tcSeqLen  = new wxTextCtrl(pnlSeq, wxID_ANY, wxT("100"), wxDefaultPosition, wxSize(80, 18));
	fgsSeq->Add(stSeqTree);
	fgsSeq->Add(tcSeqTree, 1, wxEXPAND);
	fgsSeq->Add(stSeqLen);
	fgsSeq->Add(tcSeqLen, 1, wxEXPAND);
	fgsSeq->AddGrowableRow(0, 1);
	fgsSeq->AddGrowableCol(1, 1);

	// Substitution Panel

	vbsSub      = new wxBoxSizer(wxVERTICAL);
	fgsSub      = new wxFlexGridSizer(5, 2, 8, 8);
	vbsSub->Add(fgsSub, 1, wxEXPAND | wxALL, 10);
	pnlSub->SetSizer(vbsSub);

	stSubModel  = new wxStaticText(pnlSub, wxID_ANY, wxT("Model:"));
	stSubParams = new wxStaticText(pnlSub, wxID_ANY, wxT("Params:"));
	stSubACGT   = new wxStaticText(pnlSub, wxID_ANY, wxT("ACGT:"));
	stSubGamma  = new wxStaticText(pnlSub, wxID_ANY, wxT("Gamma:"));
	stSubIota   = new wxStaticText(pnlSub, wxID_ANY, wxT("Iota:"));

	wxString asSubModels[] = {wxT("Felsenstein 1981"), wxT("Felsenstein 1984"), wxT("General Time Reversible"), wxT("Hasegawa, Kishino, and Yano"),
		wxT("Jukes and Cantor"), wxT("Kimura Two Parameter"), wxT("Kimura Three Parameter"), wxT("Tamura and Nei")};
	chSubModel = new wxChoice(pnlSub, wxID_ANY, wxDefaultPosition, wxSize(200, -1), 8, asSubModels);
	chSubModel->SetSelection(4);	// Jukes and Cantor

	tcSubParam1 = new wxTextCtrl(pnlSub, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxSize(36, 18));
	tcSubParam2 = new wxTextCtrl(pnlSub, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxSize(36, 18));
	tcSubParam3 = new wxTextCtrl(pnlSub, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxSize(36, 18));
	tcSubParam4 = new wxTextCtrl(pnlSub, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxSize(36, 18));
	tcSubParam5 = new wxTextCtrl(pnlSub, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxSize(36, 18));
	tcSubParam6 = new wxTextCtrl(pnlSub, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxSize(36, 18));
	hboxSubParams = new wxBoxSizer(wxHORIZONTAL);
	hboxSubParams->Add(tcSubParam1);
	hboxSubParams->Add(tcSubParam2);
	hboxSubParams->Add(tcSubParam3);
	hboxSubParams->Add(tcSubParam4);
	hboxSubParams->Add(tcSubParam5);
	hboxSubParams->Add(tcSubParam6);

	tcSubACGT1 = new wxTextCtrl(pnlSub, wxID_ANY, wxT("0.25"), wxDefaultPosition, wxSize(36, 18));
	tcSubACGT2 = new wxTextCtrl(pnlSub, wxID_ANY, wxT("0.25"), wxDefaultPosition, wxSize(36, 18));
	tcSubACGT3 = new wxTextCtrl(pnlSub, wxID_ANY, wxT("0.25"), wxDefaultPosition, wxSize(36, 18));
	tcSubACGT4 = new wxTextCtrl(pnlSub, wxID_ANY, wxT("0.25"), wxDefaultPosition, wxSize(36, 18));
	hboxSubACGT = new wxBoxSizer(wxHORIZONTAL);
	hboxSubACGT->Add(tcSubACGT1);
	hboxSubACGT->Add(tcSubACGT2);
	hboxSubACGT->Add(tcSubACGT3);
	hboxSubACGT->Add(tcSubACGT4);

	tcSubGamma = new wxTextCtrl(pnlSub, wxID_ANY, wxT("0.0"), wxDefaultPosition, wxSize(72, 18));
	tcSubIota  = new wxTextCtrl(pnlSub, wxID_ANY, wxT("0.0"), wxDefaultPosition, wxSize(72, 18));

	fgsSub->Add(stSubModel);
	fgsSub->Add(chSubModel);
	fgsSub->Add(stSubParams);
	fgsSub->Add(hboxSubParams);
	fgsSub->Add(stSubACGT);
	fgsSub->Add(hboxSubACGT);
	fgsSub->Add(stSubGamma);
	fgsSub->Add(tcSubGamma);
	fgsSub->Add(stSubIota);
	fgsSub->Add(tcSubIota);
	fgsSub->AddGrowableCol(1, 1);

	// Indels Panel

	vbsInd       = new wxBoxSizer(wxVERTICAL);
	fgsInd       = new wxFlexGridSizer(5, 2, 8, 8);
	vbsInd->Add(fgsInd, 1, wxEXPAND | wxALL, 10);
	pnlInd->SetSizer(vbsInd);

	stIndLambda  = new wxStaticText(pnlInd, wxID_ANY, wxT("Lambda:"));
	stIndModel   = new wxStaticText(pnlInd, wxID_ANY, wxT("Model:"));
	stIndParams  = new wxStaticText(pnlInd, wxID_ANY, wxT("Params:"));
	stIndVerbose = new wxStaticText(pnlInd, wxID_ANY, wxT("Verbose:"));
	stIndHideLen = new wxStaticText(pnlInd, wxID_ANY, wxT("Hide Length:"));

	wxString asIndModels[] = {wxT("Negative Binomial"), wxT("Power Law")};
	chIndModel   = new wxChoice(pnlInd, wxID_ANY, wxDefaultPosition, wxSize(200, -1), 2, asIndModels);
	chIndModel->SetSelection(1);	// Power Law

	tcIndLambda   = new wxTextCtrl(pnlInd, wxID_ANY, wxT("0.0"), wxDefaultPosition, wxSize(72, 18));
	tcIndParam1   = new wxTextCtrl(pnlInd, wxID_ANY, wxT("1.5"), wxDefaultPosition, wxSize(36, 18));
	tcIndParam2   = new wxTextCtrl(pnlInd, wxID_ANY, wxT("100"), wxDefaultPosition, wxSize(36, 18));
	hboxIndParams = new wxBoxSizer(wxHORIZONTAL);
	hboxIndParams->Add(tcIndParam1);
	hboxIndParams->Add(tcIndParam2);

	cbIndVerbose = new wxCheckBox(pnlInd, wxID_ANY, wxT(""));
	cbIndHideLen = new wxCheckBox(pnlInd, wxID_ANY, wxT(""));

	fgsInd->Add(stIndLambda);
	fgsInd->Add(tcIndLambda);
	fgsInd->Add(stIndModel);
	fgsInd->Add(chIndModel);
	fgsInd->Add(stIndParams);
	fgsInd->Add(hboxIndParams);
	fgsInd->Add(stIndVerbose);
	fgsInd->Add(cbIndVerbose);
	fgsInd->Add(stIndHideLen);
	fgsInd->Add(cbIndHideLen);
	fgsInd->AddGrowableCol(1, 1);

	// Miscellaneous Panel

	vbsMisc      = new wxBoxSizer(wxVERTICAL);
	fgsMisc      = new wxFlexGridSizer(5, 2, 8, 8);

	stMiscReps   = new wxStaticText(pnlMisc, wxID_ANY, wxT("Reps:"));
	stMiscSeed   = new wxStaticText(pnlMisc, wxID_ANY, wxT("Seed:"));
	stMiscFormat = new wxStaticText(pnlMisc, wxID_ANY, wxT("Format:"));
	stMiscInFile = new wxStaticText(pnlMisc, wxID_ANY, wxT("Input File:"));
	stMiscSvFile = new wxStaticText(pnlMisc, wxID_ANY, wxT("Save to File:"));

	tcMiscReps   = new wxTextCtrl(pnlMisc, wxID_ANY, wxT("1"), wxDefaultPosition, wxSize(72, 18));
	tcMiscSeed   = new wxTextCtrl(pnlMisc, wxID_ANY, wxT("21569"), wxDefaultPosition, wxSize(72, 18));

	wxString asMiscFormats[] = {wxT("Clustal"), wxT("Fasta"), wxT("Nexus"), wxT("Phylip")};
	chMiscFormat = new wxChoice(pnlMisc, wxID_ANY, wxDefaultPosition, wxSize(200, -1), 2, asMiscFormats);
	chMiscFormat->SetSelection(0);	// Clustal

	cbMiscInFile = new wxCheckBox(pnlMisc, wxID_ANY, wxT(""));
	cbMiscSvFile = new wxCheckBox(pnlMisc, wxID_ANY, wxT(""));

	fgsMisc->Add(stMiscReps);
	fgsMisc->Add(tcMiscReps);
	fgsMisc->Add(stMiscSeed);
	fgsMisc->Add(tcMiscSeed);
	fgsMisc->Add(stMiscFormat);
	fgsMisc->Add(chMiscFormat);
	fgsMisc->Add(stMiscInFile);
	fgsMisc->Add(cbMiscInFile);
	fgsMisc->Add(stMiscSvFile);
	fgsMisc->Add(cbMiscSvFile);
	fgsMisc->SetItemMinSize((size_t)0, 64, -1);
	fgsMisc->AddGrowableCol(1, 1);

	vbsMisc->Add(fgsMisc, 1, wxEXPAND | wxALL, 10);
	pnlMisc->SetSizer(vbsMisc);

	// Bottom: Buttons

	hbsBottom = new wxBoxSizer(wxHORIZONTAL);

	btnSubmit = new wxButton(pnlFrm, wxID_EXIT, wxT("Submit"), wxPoint(20, 400), wxDefaultSize);
	btnSubmit->SetFocus();
	Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameTask::OnButtonExit));
	btnExit = new wxButton(pnlFrm, wxID_EXIT, wxT("Exit"), wxPoint(20, 400), wxDefaultSize);
	Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameTask::OnButtonExit));
	
	hbsBottom->Add(btnSubmit, 0, wxLEFT, 10);
	hbsBottom->Add(btnExit, 0, wxLEFT, 10);
	
	vbsFrm->Add(hbsBottom, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);

	// Menu Bar

	menubarMain = new wxMenuBar;
	menuFile = new wxMenu;
	menuFile->Append(wxID_NEW, wxT("&New"));
	menuFile->Append(wxID_OPEN, wxT("&Open"));
	menuFile->Append(wxID_EXIT, wxT("&Save"));
	menuFile->Append(wxID_EXIT, wxT("Save &As..."));
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT, wxT("E&xit"));
	menubarMain->Append(menuFile, wxT("&File"));
	menuEdit = new wxMenu;
	menuEdit->Append(wxID_CUT, wxT("Cu&t"));
	menuEdit->Append(wxID_COPY, wxT("&Copy"));
	menuEdit->Append(wxID_PASTE, wxT("&Paste"));
	menuEdit->Append(wxID_DELETE, wxT("&Delete"));
	menubarMain->Append(menuEdit, wxT("&Edit"));
	menuHelp = new wxMenu;
	menuHelp->Append(wxID_HELP, wxT("&Help"));
	menuHelp->AppendSeparator();
	menuHelp->Append(wxID_ABOUT, wxT("&About"));
	menubarMain->Append(menuHelp, wxT("&Help"));
	SetMenuBar(menubarMain);
}

void FrameTask::OnButtonExit(wxCommandEvent & WXUNUSED(event))
{
	Close(true);
}

FrameTask::~FrameTask(void)
{
}
