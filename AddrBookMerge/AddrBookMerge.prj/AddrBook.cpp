// Merge Address Books


#include "stdafx.h"
#include "AddrBook.h"
#include "CSVrcds.h"
#include "NotePad.h"
#include "match.h"
#include "qsort.h"


AddrBook addrBook;



void AddrBook::onProcess() {

  getRecords();

  cleanupRecords();

  removeTroublesomeEmails();

  sort();

  noDups();
  }


void AddrBook::getRecords() {
CSVIter  iter(csvRcds);
CSVRcd*  csvRcd;
bool     isHeader   = true;
bool     invalidMsg = false;

  notePad.clear();   rcds.clear();

  for (csvRcd = iter(); csvRcd; csvRcd = iter++) {

    if (isHeader) {header = *csvRcd;   isHeader = false;   continue;}

    AddrRcd* addrRcd = rcds.allocate();     if (!addrRcd) continue;

    *addrRcd = *csvRcd;

    if (!validate(*addrRcd)) {
      if (!invalidMsg) {notePad << _T("Invalid Entries") << nCrlf << nCrlf; invalidMsg = true;}

      addrRcd->dspAsCSV();   rcds.deallocate(addrRcd);   continue;
      }

    rcds += addrRcd;
    }
  }


bool AddrBook::validate(AddrRcd& rcd) {
ARIter   iter(rcd);
String*  fld;
String&  pmail = rcd.getEmail();

  if (pmail.isEmpty()) return false;

  if (!validateEmail(pmail) && !fixEmail(rcd)) return false;

  for (fld = iter(); fld; fld = iter++) if (fld->length()) return true;

  return false;
  }


bool AddrBook::fixEmail(AddrRcd& rcd) {

String& first  = rcd.First_Name;
String& last   = rcd.Last_Name;
String& displ  = rcd.Display_Name;
String& pmail  = rcd.Primary_Email;
String& smail  = rcd.Secondary_Email;
String& screen = rcd.Screen_Name;

  if (validateEmail(screen)) {
    last = first; first = pmail; pmail = screen; screen = _T(""); displ = first + _T(" ") + last;
    return true;
    }

  if (validateEmail(smail)) {pmail = smail; smail = _T(""); return true;}

  return false;
  }


bool AddrBook::validateEmail(String& fld) {int x = fld.find(_T('@')); return 0 < x && x <= 45;}


static RegExpr junior(_T(".*Jr.*"));
static RegExpr juniorFirst(_T("^Jr.*"));



void AddrBook::cleanupRecords() {
ABIter   iter(addrBook);
AddrRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) {
    String& first  = rcd->First_Name;     first.trim();
    String& last   = rcd->Last_Name;      last.trim();
    String& displ  = rcd->Display_Name;   displ.trim();
    String& nickN  = rcd->Nickname;       nickN.trim();
    String& screen = rcd->Screen_Name;    screen.trim();

    if (junior.match(first))      first.clear();
    if (nickN == _T("Jr."))       nickN.clear();
    if (juniorFirst.match(last))  removeJr(last);
    if (juniorFirst.match(displ)) removeJr(displ);
    if (juniorFirst.match(nickN)) removeJr(nickN);

    int firstLng  = first.length();
    int lastLng   = last.length();
    int displLng  = displ.length();
    int nickNLng  = nickN.length();
    int screenLng = screen.length();

    if (firstLng && lastLng && displLng) continue;

    if (!firstLng && lastLng)
      splitStg(last, first, last, firstLng, lastLng);

    if (firstLng && !lastLng)
      splitStg(first, first, last, firstLng, lastLng);

    if (!displLng && (firstLng || lastLng))
      {displ = first + _T(" ") + last; continue;}

    if (!firstLng && !lastLng) {
      if (displLng && displLng > nickNLng && displLng > screenLng) {
        if (splitStg(displ, first, last, firstLng, lastLng)) continue;

        first = displ; continue;
        }

      if (screenLng && screenLng > nickNLng) {
        if (splitStg(screen, first, last, firstLng, lastLng)) continue;

        first = screen; continue;
        }

      if (nickNLng) {
        if (splitStg(nickN, first, last, firstLng, lastLng)) continue;

        first = nickN; continue;
        }
      }

    if (!firstLng) {
      if (displLng && displLng > nickNLng && displLng > screenLng && displLng > lastLng) {
        if (splitStg(displ, first, last, firstLng, lastLng)) continue;

        first = displ; continue;
        }

      if (screenLng && screenLng > nickNLng && screenLng > lastLng) {
        if (splitStg(screen, first, last, firstLng, lastLng)) continue;

        first = screen; continue;
        }

      if (nickNLng && nickNLng > lastLng) {
        if (splitStg(nickN, first, last, firstLng, lastLng)) continue;

        first = nickN; continue;
        }
      }
    }
  }


void AddrBook::removeJr(String& s) {
String pat = _T("Jr.");
int    pos = s.find(pat);
String t;

  if (pos < 0) {pat = _T("Jr"); pos = s.find(pat);}

  if (pos > 0) t = s.substr(0, pos);

  t += s.substr(pos + pat.length());

  s = t.trim();
  }


bool AddrBook::splitStg(String s, String& first, String& last, int& firstLng, int& lastLng) {
int pos;
int pos1;

  pos = s.find(_T('&'));  pos1 = s.find(_T(' '), pos+2);

  if (pos >= 0 && s[pos+1] != _T(' ')) {
    pos1 = s.findLastOf(_T(' '));
    }

  if (pos1 < 0) {
    if (pos <= 0) return false;

    last = s.substr(pos+1); first = s.substr(0, pos+1);
    }

  else {last = s.substr(pos1+1); first = s.substr(0, pos1);}

  firstLng = first.length(); lastLng = last.length(); return true;
  }


static RegExpr  noReply(_T("noreply"));
static RegExpr  noReply1(_T("no_reply"));
static RegExpr  reply(_T("reply"));
static RegExpr  service(_T("^service"));
static RegExpr  sales(_T("^sales"));
static RegExpr  specials(_T("^specials"));
static RegExpr  news(_T("^news"));
static RegExpr  news1(_T("^News"));
static RegExpr  support(_T("^support"));


void AddrBook::removeTroublesomeEmails() {
ABIter   iter(*this);
AddrRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) {
    String& eMail = rcd->Primary_Email;

    if (isTroublesomeEmail(eMail)) {iter.remove(); continue;}
    if (displIsEmail(*rcd))        {iter.remove(); continue;}
    if (noReply.match(eMail))      {iter.remove(); continue;}
    if (noReply1.match(eMail))     {iter.remove(); continue;}
    if (reply.match(eMail))        {iter.remove(); continue;}
    if (service.match(eMail))      {iter.remove(); continue;}
    if (sales.match(eMail))        {iter.remove(); continue;}
    if (specials.match(eMail))     {iter.remove(); continue;}
    if (news.match(eMail))         {iter.remove(); continue;}
    if (news1.match(eMail))        {iter.remove(); continue;}
    if (support.match(eMail))      {iter.remove(); continue;}
    if (eMail.length() > 60)       {iter.remove(); continue;}
    }
  }


bool AddrBook::isTroublesomeEmail(String& eMail) {
int   i;
Tchar ch;

  for (i = 0; i < 3; i++) {
    ch = eMail[i];
    if (ch < _T('0') || _T('9') < ch)
      return false;}

  return true;
  }


bool AddrBook::displIsEmail(AddrRcd& rcd) {
  if (!rcd.First_Name.isEmpty()) return false;
  if (!rcd.Last_Name.isEmpty())  return false;
  if (_tcsicmp(rcd.Display_Name, rcd.Primary_Email) != 0) return false;
  return _tcsicmp(rcd.Nickname, rcd.Primary_Email) == 0;
  }


void AddrBook::sort() {
int last = rcds.end()-1;

  qsort(&rcds[0], &rcds[last]);
  }



void AddrBook::noDups() {
ABIter   iter(*this);
AddrRcd* rcd;

  notePad << nCrlf << nCrlf;
  notePad << _T("Duplicate Records -----------------------------------") << nCrlf << nCrlf;

  for (rcd = iter(); rcd; rcd = iter++) {

    if (adjacentRcdsEmailsSame(iter)) {
      rcd->dspAsCSV();

      ABIter nxt(iter); AddrRcd* nxtRcd = nxt++;   nxtRcd->dspAsCSV(); notePad << nCrlf;

      mergeDups(iter);

      nxt.remove();
      }
    }
  }


bool AddrBook::adjacentRcdsEmailsSame(ABIter abIter) {
ABIter   nxt(abIter);
AddrRcd* curRcd = abIter.current();
AddrRcd* nxtRcd = nxt++;

  if (!curRcd || !nxtRcd) return false;

  return *curRcd == *nxtRcd;
  }


void AddrBook::mergeDups(ABIter abIter) {
ABIter   nxt(abIter);
AddrRcd* curRcd = abIter.current();   if (!curRcd) return;
AddrRcd* nxtRcd = nxt++;              if (!nxtRcd) return;
ARIter   iter(*curRcd);
String*  s;
int      i;

  for (i = 0, s = iter(); s; i++, s = iter++) {
    s->trim();
    String& t = *nxtRcd->datum(i);   t.trim();

    bool sAvail = !s->empty();
    bool tAvail = !t.empty();

    if (!tAvail) continue;

    if (!sAvail && tAvail) *s = t;

    if (!addrBook.fieldsAreSame(*s, t)) {
      int xLng = s->length();
      int yLng = t.length();
      if (xLng > yLng) continue;
      if (yLng > xLng) {*s = t; continue;}

      *s += _T(" ") + t;
      }
    }
  }


void AddrBook::dspRecords() {
ABIter   iter(*this);
AddrRcd* rcd;
String   s;

  notePad << nCrlf;

  s.format(_T("Number of Address Records: %i"), rcds.end());  notePad << s << nCrlf << nCrlf;

  for (rcd = iter(); rcd; rcd = iter++) rcd->dspAsCSV();
  }


void AddrBook::dataOut(Archive& ar) {
ABIter   iter(*this);
AddrRcd* rcd;

  header.dataOut(ar);

  for (rcd = iter(); rcd; rcd = iter++) rcd->dataOut(ar);
  }

