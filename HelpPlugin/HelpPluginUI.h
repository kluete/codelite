//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: HelpPluginUI.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef HELPPLUGINUI_BASE_CLASSES_H
#define HELPPLUGINUI_BASE_CLASSES_H

#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/dialog.h>
#include <wx/iconbndl.h>
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/hyperlink.h>
#include <wx/button.h>
#if wxVERSION_NUMBER >= 2900
#include <wx/persist.h>
#include <wx/persist/toplevel.h>
#include <wx/persist/bookctrl.h>
#include <wx/persist/treebook.h>
#endif

class HelpPluginMessageBaseDlg : public wxDialog
{
protected:
    wxStaticBitmap* m_staticBitmap14;
    wxStaticText* m_staticText;
    wxHyperlinkCtrl* m_hyperLink;
    wxStdDialogButtonSizer* m_stdBtnSizer4;
    wxButton* m_button6;

protected:

public:
    wxStaticBitmap* GetStaticBitmap14() { return m_staticBitmap14; }
    wxStaticText* GetStaticText() { return m_staticText; }
    wxHyperlinkCtrl* GetHyperLink() { return m_hyperLink; }
    HelpPluginMessageBaseDlg(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Help Plugin Error"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(400,-1), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);
    virtual ~HelpPluginMessageBaseDlg();
};

#endif
