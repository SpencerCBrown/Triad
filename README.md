I have decided after much consideration to discontinue my work on Triad.  In building it I have learned a lot, even though it didn't get anywhere near completion.  I started Triad because I could not find anything like it (for linux, touch-compatible, onenote-like).  I am going to try to contribute to the development of https://github.com/lordadamson/Journal, which I hope anyone that found an interest in my project will check out.
~~# Triad
Robust and pleasant cross-platform note taking application.

Triad is split into two parts, a frontend UI written in QML/Javascript, and a backend for data management written in Qt/C++.

Roadmap:
First goal is a fully functional rich text editor that allows "content" containers to be placed all over the application.  This will save in directories with raw html files.

~~Next step is compliance with the MS-ONE specification.  This will allow Triad to interoperate with [Outline](outline.ws) and [Onenote](onenote.com).~~ *This may or may not happen, as I was under the (very mistaken!) impression that OneNote used a form of xml to store notebooks.  In any case, it'll be after Triad is fully-usable with its own storage format.*
Nothing like this exists on Linux, and considerations for that platform will drive development.  As a secondary consideration, Triad should also function on Windows and MacOSX.

Triad should be able to sync with WebDav instances, other cloud storage providers like Dropbox, Google Drive, etc.
Syncing with OneDrive and iCloud should also be considered.

A functioning Android build is a priority.~~
