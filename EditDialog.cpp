#include "EditDialog.h"
#include <wx/filedlg.h>

//(*InternalHeaders(EditDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(EditDialog)
//*)

BEGIN_EVENT_TABLE(EditDialog,wxDialog)
	//(*EventTable(EditDialog)
	//*)
END_EVENT_TABLE()

EditDialog::EditDialog(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(EditDialog)
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	//*)
	m_canvas = 0;
}

EditDialog::~EditDialog()
{
	//(*Destroy(EditDialog)
	//*)
}

void EditDialog::OnButton_displayClick(wxCommandEvent& event)
{

}

void EditDialog::OnButton1Click(wxCommandEvent& event)
{

}
