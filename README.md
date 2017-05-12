# Triad
Robust and pleasant cross-platform note taking application.

Triad is split into two parts, a frontend UI written in QML/Javascript, and a backend for data management written in Qt/C++.

Roadmap:
First goal is a fully functional rich text editor that allows "content" containers to be placed all over the application.  This will save in directories with raw html files.

Next step is compliance with the MS-ONESTORE specification.  This will allow Triad to interoperate with [Outline](outline.ws) and [Onenote](onenote.com).
Nothing like this exists on Linux, and considerations for that platform will drive development.  As a secondary consideration, Triad should also function on Windows and MacOSX.

Triad should be able to sync with WebDav instances, other cloud storage providers like Dropbox, Google Drive, etc.
Syncing with OneDrive and iCloud should also be considered.

A functioning Android build is a priority.
