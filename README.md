LuxIRC:
=======
Lux is the SI symbol for illuminance. IRC is an old and vast social gathering which gives the potential to illuminate your mind.

LuxIRC is intended to be a basic IRC client without too much bloat (I hope). It is a self-project of mine to learn the basics of GUI and network programming while making something useful. I am testing and developing the program in Arch Linux only (for now).

I have recently started working on the project again and I will try to finish the basic function of the software soon.

Current Progress:
-----------------
* 2016/08/01 - Upon 'connect' in NetworkDlg, network is added to QTreeWidget along with children items (#channels). Also able to remove networks via Ctrl+W.
* 2016/07/29 - Implemented the Connection class to successfully transfer data in Connection objects from NetworkDlg to MainWindow. Also fixed a segfault which occured if clicking 'Cancel' in NetworkDlg which sent a null pointer to MainWindow.
* 2016/07/27 - Started to implement the Connection class.
* 2016/07/25 - Created the Connection class for handling the logic of connecting to networks. Each Connection will connect through its own thread.
* 2016/04/05 - Started implementing the network side. I want to complete this rather quickly and get basic functionality for my portfolio.
* 2015/10/23 - I am working on the front-end only and making sure basic file I/O is working properly. I am nearly ready to start delving into the network side of the project.

Libraries and modules used so far:
----------------------------------
Qt5:
   * QtWidgets
   * QtCore
   * QtNetwork
