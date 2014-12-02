#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include "CCanvas.h"
//(*Headers(EditDialog)
#include <wx/dialog.h>
//*)

class EditDialog: public wxDialog
{
	public:

		EditDialog(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~EditDialog();

		//(*Declarations(EditDialog)
		//*)

	protected:

		//(*Identifiers(EditDialog)
		//*)

	private:

		//(*Handlers(EditDialog)
		void OnButton_displayClick(wxCommandEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		//*)

        CGLCanvas* m_canvas;
		DECLARE_EVENT_TABLE()
};

#endif
