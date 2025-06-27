# Address Book Merge
The stated purpose of this application is to merge eMail entries in multiple Thunderbird Address Books
exported to CSV files.
It does a little more than that:

  - It removes entries with no discernable eMail Address
  - It removes entries with eMail addresses that begin with four digits
  - It removes entries that will not respond
  - It removes entries that are very long
  - It tries to fix entries where the eMail address is not in the eMail field
  - It attempts to fix names with things like "Smith, Jr." which were not enclosed in quotes so the
comma separated line is screwed up
  - It merges duplicate eMails and deletes one of the entries

Then it produces a CSV file that is suitable to importing back into Thunderbird's Address Book.

The sequence of events should be as follows:

  - Export all Thunderbird Address Books to CSV files, for example:
    * AddressBook.csv
    * Collected Addresses.csv
    * ExtraBook.csv
    * Personal Address Book.csv
  - Use the App to create a new Single Address Book, give it a unique name (I used Ugly10.csv)
  - Import Ugly10.csv into thunderbird's Address Book
  - You should be able to view several address books in TAB
    * AddressBook
    * Collected Addresses
    * ExtraBook
    * Personal Address Book
    * Ugly10
  - Now hold your breath, look at the Ugly10 address book and convince yourself that it has all the
addresses.
  - Highlight "ExtraBook" and press the delete key -- This will delete the book for the list of books.
  - Highlight "AddressBook" and press the delete key
    * The Personal Address and the Collected Address Books cannot be deleted this way, so:
      * Select Personal Address Book, the move the mouse to any eMail record in the book.  The press
Ctrl-A.  This will highlight all entries in the book.  Then press the Delete Key.  This will eventually
delete all entries in the book.
      * Select the Collected Addresses Book and perform the Ctrl-A deletion described above.
  - Now the only book with addresses should be the Ugly10 Book.  Since this name is "ugly" I then
highlight all entries in the Ugly10 book and drag them into the Personal Address Book (I make sure that
I use a move operation).  Then I delete the empty Ugly10 book.  Make sure the Personal Address Book
has entries first.

### BuidData Application

The BuildData Application (BDA) is used to create the Addr Module (i.e. Addr.h and Addr.cpp).  It is
only used during modification of the Thunderbird Address Book Configuration which then forces changes to
AddrBookMerge.  See the help file in BDA to figure out how it is used...  It is not included in the
intaller.

## Getting Started

The application is built with Visual Studio 2017 (VS17).  It was compiled with the following properties:

  o Windows Latest SDK Version
  o Platfor Toolset: visual Studio 2022
  o MFC: Use MFC in a Shared DLL
  o Character Set:  Use Unicode Character Set
  o Additional Include Directories:
    * $(ProjectDir)
    * $(SolutionDir)..\..\Library\Library.prj\
    * $(SolutionDir)..\..\Library\Extras\
  o  Precompiled Header:  Not Using Precompiled Headers
  o  Linker/Additional Dependencies:  Htmlhelp.lib

The HTML Help Workshop (HHW), Version 4.74.8702.0 was used to prepare the help file (WixApp.chm).  It is
copied into the Release directory.  I used Dreamweaver (DW) to do most of the content production of the
help files that the HTML Help Workshop produces (i.e. HHW is used to produce the pages/files needed
and DW is used to fill in the content).

The Installer requires the Wix Extension to VS17

### Prerequisites

The WiX Toolset must be installed in Visual Studio.  The "HTML Help Workshop" (google it) must be
installed.  Visual Studio 2017 or later.

## History

I started this project many years ago when I noticed a some duplication in the address book and
Thunderbird's function did not work.

## Update

### Update 6/26/25

Improve memory leak debugging.

### Update 8/4/24

Library Update

### Update 7/25/24

Restored the help files to the build.

### Update 7/24/24

The new Thunderbird puts a line feed character in one of the fields in the csv file.  Replaced
the line feed with " *** ".

### Update 6/22/24

Added an icon to the MIT License rtf file.

### Update 6/21/24

Added the MIT License to the installer and the Start Menu Folder.

###update 6/13/24

Fix WinPos.

### Update 5/15/24

Add MyToolBar class to deal with the differences between Doc/View and Dialog Box Toolbars.

### Update 4/17/24 & 4/18/24

Improved the way Toolbars and Window Position and size are handled.

### Update 2/16/24

Reorganized the Library so that it compiles once into Debug and Release directories under the Library
directory.

### Update 12/11/23

Improve (modify) ExpandableP and associated changes.

### Update 6/25/23

Library modifications and added one additional verification feature.

### Update 3/31/23

Added report orientation to both applications.

### Update 3/15/23

Complete move of orientation to reports.

### Update 3/13/23

When there are multiple reports the printed output orientation is by report, not the printer.  Thus the
orientation is associated with the report and the standard Options dialog contains the orientation for the
NotePad Report.  Other reports will need a way to designate the printer output orietation.

The NotePad output managers have been moved into CScrView so that it is available in all applications
without further development.  Of course other reports may be written following the pattern of the NotePad
report.

Some additional bug fixes.

### Update 3/8/23

Added numbers to notepad archive output.

### Update 3/7/23

Fixed (hopefully) Print and Print Preview.  See MakeApp for details.

### Update 10/30/22

All logic to start app with same position and size as when it last exited.  Update toolbar background.
Update help file icons.

### Update 8/3/22

Minor Library update.

### Update 4/15/22

Big adventure started in February when I started moving to a new Win11 and Visual Studio 2022.  I now
feel that this version is working in the new environment.  There were several changes made to the app
in order to compile properly on VS22.

### Update 01/31/22

Updates to the library, mostly about the toolbar, but also NewAllocator, and a minor addition to
Expandable.

Also scrubbed the project files to remove all references to precompiled header files which I turned off
in VS17.  Unfortnately VS does not remove all references and pch files kept cropping up.  Not only does
that slow down the compiler but the files are large...

### Update 12/18/21

While creating a template for a dialog box only application with a toolbar the Library was added to and
changed to hopefully simplify toolbar creation.  This version of the toolbar includes buttons, edit boxes,
combo boxes and drop down menus as well as the traditional 16x15 icons.

AddressBookMerge is a tradional App, has a traditional 16x15 pixel icon toolbar.

### Update 11/12/21

Change processing to remove duplicates to remove three or more duplicates.  But the major changes are in
the library:

  - Expandable and ExpandableP -- moved the functions out of the class to make the compilation smaller,
also fixed one bug (or feature) in the ExpandableP insert sorted function that would throw out entries
that were already in in the array.
  - FileIO -- Changed the type of path from "String&" to "TCchar*".  It turns out that automatic
conversion from String to TCchar* is easy, but the reverse is is not easy.  Also added a function to
get the length of a file given a path.
  - FineName -- Added a function to get the directory name of from a path
  - NewAllocator -- Corrected the debug dependency from if to ifdef
  - ToolBar -- Added data for drop down menus

### Update 10/31/21

Changed Resources (i.e. xxx.rc data) access so that it will work with a dll.  Changed the logic in the
About Box code.  Some other library changes.  Some corresponding changes in the application.

### Update 10/2/21

Library improvements only.

### Update 4/14/21

Just some minor changes.

### Update 3/7/21

Renamed PathDsc and changed the way it is initialized.

### Update 2/14/21

Started with a fresh application from Make App and integrated the relevant modules from the ThdrBrdAddrBk
application begun some years ago.  Renamed to work in a separate domain.  This version probably could be
made to work on other eMail clients provided they have export and import of csv files.  The details in
the AddrBook Module would necessarily change with changes to Addr Module.

## Prerequisites

Windows 7 or above.  visual Studio 2017 or above.  Wix Installer extension to VS17.
HTML Help Workshop (HHW), Version 4.74.8702.0.

## Installing

Run msi file.

## Authors

Robert R. Van Tuyl

Contact:  romeo romeo victor tango alpha tango sam whisky delta echo dot charlie oscar mike

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
