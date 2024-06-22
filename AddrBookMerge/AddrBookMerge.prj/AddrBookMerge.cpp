// AddrBookMerge.cpp : Defines the class behaviors for the application.


#include "stdafx.h"
#include "AddrBookMerge.h"
#include "AboutDlg.h"
#include "IniFile.h"
#include "MainFrame.h"
#include "NotePad.h"
#include "Resource.h"
#include "AddrBookMergeDoc.h"
#include "AddrBookMergeView.h"


AddrBookMerge theApp;                       // The one and only AddrBookMerge object
IniFile     iniFile;


// AddrBookMerge

BEGIN_MESSAGE_MAP(AddrBookMerge, CWinAppEx)
  ON_COMMAND(ID_File_New,         &CWinAppEx::OnFileNew)
  ON_COMMAND(ID_Help,             &OnHelp)
  ON_COMMAND(ID_App_About,        &OnAppAbout)
END_MESSAGE_MAP()


// AddrBookMerge initialization

BOOL AddrBookMerge::InitInstance() {

  CWinAppEx::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

  notePad.clear();

  SetRegistryKey(appID);

  LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

  // Register the application's document templates.  Document templates
  // serve as the connection between documents, frame windows and views

  CSingleDocTemplate* pDocTemplate;

  pDocTemplate = new CSingleDocTemplate(
    IDR_MAINFRAME,
    RUNTIME_CLASS(AddrBookMergeDoc),
    RUNTIME_CLASS(MainFrame),       // main SDI frame window
    RUNTIME_CLASS(AddrBookMergeView));

  if (!pDocTemplate) return FALSE;

  AddDocTemplate(pDocTemplate);

  // Parse command line for standard shell commands, DDE, file open

  CCommandLineInfo cmdInfo;   ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

  if (!ProcessShellCommand(cmdInfo)) return FALSE;

  setAppName(_T("ThunderBird Address Book")); setTitle(_T("Merge Books"));

  view()->setFont(_T("Arial"), 12.0);

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }



int AddrBookMerge::ExitInstance() {

#ifdef DebugMemoryLeaks
  _CrtDumpMemoryLeaks();
#endif

  return CApp::ExitInstance();
  }


void AddrBookMerge::OnHelp() {
String topic = m_pszHelpFilePath; topic += _T(">Introduction");

  ::HtmlHelp(m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 0);
  }


void AddrBookMerge::OnAppAbout() {AboutDlg aboutDlg; aboutDlg.DoModal();}

