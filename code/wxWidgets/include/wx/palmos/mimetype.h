/////////////////////////////////////////////////////////////////////////////
// Name:        wx/palmos/mimetype.h
// Purpose:     classes and functions to manage MIME types
// Author:      William Osborne - minimal working wxPalmOS port
// Modified by:
// Created:     10/13/04
// RCS-ID:      $Id: mimetype.h,v 1.2 2005/01/18 21:14:26 ABX Exp $
// Copyright:   (c) William Osborne
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _MIMETYPE_IMPL_H
#define _MIMETYPE_IMPL_H

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma interface "mimetype.h"
#endif

#include "wx/defs.h"

#if wxUSE_MIMETYPE

#include "wx/mimetype.h"

// ----------------------------------------------------------------------------
// wxFileTypeImpl is the MSW version of wxFileType, this is a private class
// and is never used directly by the application
// ----------------------------------------------------------------------------

class WXDLLIMPEXP_BASE wxFileTypeImpl
{
public:
    // ctor
    wxFileTypeImpl() { }

    // one of these Init() function must be called (ctor can't take any
    // arguments because it's common)

        // initialize us with our file type name and extension - in this case
        // we will read all other data from the registry
    void Init(const wxString& strFileType, const wxString& ext);

    // implement accessor functions
    bool GetExtensions(wxArrayString& extensions);
    bool GetMimeType(wxString *mimeType) const;
    bool GetMimeTypes(wxArrayString& mimeTypes) const;
    bool GetIcon(wxIconLocation *iconLoc) const;
    bool GetDescription(wxString *desc) const;
    bool GetOpenCommand(wxString *openCmd,
                        const wxFileType::MessageParameters& params) const;
    bool GetPrintCommand(wxString *printCmd,
                         const wxFileType::MessageParameters& params) const;

    size_t GetAllCommands(wxArrayString * verbs, wxArrayString * commands,
                          const wxFileType::MessageParameters& params) const;

    bool Unassociate();

    // set an arbitrary command, ask confirmation if it already exists and
    // overwriteprompt is TRUE
    bool SetCommand(const wxString& cmd,
                    const wxString& verb,
                    bool overwriteprompt = TRUE);

    bool SetDefaultIcon(const wxString& cmd = wxEmptyString, int index = 0);

    // this is called  by Associate
    bool SetDescription (const wxString& desc);

private:
    // helper function: reads the command corresponding to the specified verb
    // from the registry (returns an empty string if not found)
    wxString GetCommand(const wxChar *verb) const;

    // get the registry path for the given verb
    wxString GetVerbPath(const wxString& verb) const;

    // check that the registry key for our extension exists, create it if it
    // doesn't, return FALSE if this failed
    bool EnsureExtKeyExists();

    wxString m_strFileType,         // may be empty
             m_ext;

    // these methods are not publicly accessible (as wxMimeTypesManager
    // doesn't know about them), and should only be called by Unassociate

    bool RemoveOpenCommand();
    bool RemoveCommand(const wxString& verb);
    bool RemoveMimeType();
    bool RemoveDefaultIcon();
    bool RemoveDescription();
};

class WXDLLIMPEXP_BASE wxMimeTypesManagerImpl
{
public:
    // nothing to do here, we don't load any data but just go and fetch it from
    // the registry when asked for
    wxMimeTypesManagerImpl() { }

    // implement containing class functions
    wxFileType *GetFileTypeFromExtension(const wxString& ext);
    wxFileType *GetOrAllocateFileTypeFromExtension(const wxString& ext);
    wxFileType *GetFileTypeFromMimeType(const wxString& mimeType);

    size_t EnumAllFileTypes(wxArrayString& mimetypes);

    // this are NOPs under Windows
    bool ReadMailcap(const wxString& WXUNUSED(filename), bool WXUNUSED(fallback) = TRUE)
        { return TRUE; }
    bool ReadMimeTypes(const wxString& WXUNUSED(filename))
        { return TRUE; }

    // create a new filetype association
    wxFileType *Associate(const wxFileTypeInfo& ftInfo);

    // create a new filetype with the given name and extension
    wxFileType *CreateFileType(const wxString& filetype, const wxString& ext);
};

#endif // wxUSE_MIMETYPE

#endif
  //_MIMETYPE_IMPL_H

