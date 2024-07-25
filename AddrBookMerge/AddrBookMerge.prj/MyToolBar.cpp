// My ToolBar


#include "pch.h"
#include "MyToolBar.h"
#include "Resource.h"


static int NoOfButtonControls = 0;
static int NoOfButtons        = 8;


#ifdef ButtonDefs

MyToolBar::MyToolBar() : button(ID_Button), editBox(ID_EditBox),     menu(ID_Menu),
                         menu1(ID_Menu1),   saveMenu(ID_TBSaveMenu), cboBx(ID_CboBx)
                        {toolBarDim.initialize(NoOfButtonControls, NoOfButtons);}
#else

MyToolBar::MyToolBar() {toolBarDim.initialize(NoOfButtonControls, NoOfButtons);}
#endif

#ifdef ButtonDefs

bool MyToolBar::addButton( uint id, TCchar* caption) {
  return add(button,  id, caption);
  }


bool MyToolBar::addEditBox(uint id, int noChars)              {
  return add(editBox, id, noChars);
  }


CString MyToolBar::getText(uint id) {

  if (id == editBox.getId()) {return ToolBarBase::getText(editBox);}

  return 0;
  }

#ifdef DocViewTB

bool MyToolBar::addMenu(uint id, int idr, TCchar* caption) {
int menuID  = menu.getId();
int menu1ID = menu1.getId();
int saveID  = saveMenu.getId();

  if (id == menuID)  return add(menu,     id, idr, caption);
  if (id == menu1ID) return add(menu1,    id, idr, caption);
  if (id == saveID)  return add(saveMenu, id, idr, caption);

  return false;
  }


bool MyToolBar::addMenu(uint id, int idr, int index) {
int menuID  = menu.getId();
int menu1ID = menu1.getId();
int saveID  = saveMenu.getId();

  if (id == menuID)  return add(menu,     id, idr, index);
  if (id == menu1ID) return add(menu1,    id, idr, index);
  if (id == saveID)  return add(saveMenu, id, idr, index);

  return false;
  }


bool MyToolBar::addMenu(uint id, CbxItem cbxItem[], int n, TCchar* caption) {
  return add(menu1, id, cbxItem, n, caption);
  }

#else


bool MyToolBar::addMenu(uint id, int idr, TCchar* caption) {
  return add(cbxMenu, id, idr, caption);
  }


bool MyToolBar::addMenu(uint id, CbxItem cbxItem[], int n, TCchar* caption) {
  return add(cbxMenu1, id, cbxItem, n, caption);
  }


void MyToolBar::dispatch(uint id) {
uint cbxId  = cbxMenu.getId();
uint cbxId1 = cbxMenu1.getId();

  if (id == cbxId)  ToolBarBase::dispatch(cbxMenu);
  if (id == cbxId1) ToolBarBase::dispatch(cbxMenu1);
  }

#endif




bool MyToolBar::addCBx(uint id) {
  return add(cboBx,  id, 10);
  }


bool MyToolBar::addCBx(uint id, int idr, TCchar* caption) {
  return add(cboBx,  id, idr, caption);
  }


bool MyToolBar::addCbxItem(uint id, TCchar* txt, int data) {
int cbxID = cboBx.getId();

  if (id == cbxID) {return addItem(cboBx, txt, data);}
  return false;
  }

#ifdef DocViewTB
#else

bool MyToolBar::addCBx(uint id, CbxItem cbxItem[], int n, TCchar* caption) {
  return add(cboBx1,  id, cbxItem, n, caption);
  }
#endif

bool MyToolBar::addCbxItemSorted(uint id, TCchar* txt, int data) {
int cbxID = cboBx.getId();

  if (id == cbxID) {return addItemSorted(cboBx, txt, data);}
  return false;
  }


void MyToolBar::setCaption(uint id, TCchar* caption) {
int cbxID = cboBx.getId();

  if (id == cbxID) ToolBarBase::setCaption(cboBx, caption);
  }


void MyToolBar::setWidth(uint id) {
int cbxID = cboBx.getId();

  if (id == cbxID) ToolBarBase::setWidth(cboBx);
  }


void MyToolBar::setHeight( uint id) {
int cbxID = cboBx.getId();

  if (id == cbxID) ToolBarBase::setHeight(cboBx);
  }


#ifdef DocViewTB

bool MyToolBar::getCurSel( uint id, String& s, int& data) {
int cbxID = cboBx.getId();

  if (id == cbxID) return ToolBarBase::getCurSel(cboBx, s, data);
  return false;
  }

#else

bool MyToolBar::getCurSel( uint id, String& s, int& data) {
int cbxID  = cboBx.getId();
int cbxID1 = cboBx1.getId();

  if (id == cbxID)  return ToolBarBase::getCurSel(cboBx,  s, data);
  if (id == cbxID1) return ToolBarBase::getCurSel(cboBx1, s, data);
  return false;
  }

#endif

//#else


bool MyToolBar::addMenu(uint id, int idr, int index) {
int saveID  = saveMenu.getId();

  if (id == saveID)  return add(saveMenu, id, idr, index);

  return false;
  }

#endif

