LuxIRC:
=======
Lux is the SI symbol for illuminance. IRC is an old and vast social gathering which gives the potential to illuminate your mind.

LuxIRC is intended to be a basic IRC client without too much bloat (I hope). It is a self-project of mine to learn the basics of GUI and network programming while making something useful. I am testing and developing the program in Arch Linux only (for now).

I have recently started working on the project again and I will try to finish the basic function of the software soon.

Current Progress:
-----------------
* 2016/08/17 - Segfaults dealing with removing Channels/Connections are fixed. Still need to call QTcpSocket->disconnectFromHost() some how. Calling it from the MainWindow before deleting the Connection caused a segfault, no idea why yet. Currently, the Connection is deleted while its thread is running which throws a "Thread destroyed while running" warning. I'll probably have to set up a signal/slot to stop the thread first since if I delete the Connection, then try to reconnect to the same network, it seems like I'm still logged in (ident issues). I still need to check if the offline issues persist, I wonder if those segfaults have anything to do with the QTcpSocket::disconnectFromHost() segfault...
* 2016/08/15 - I made MainWindow::updateOutputTE() more modular and fixed everything regarding that to this point. I did not bother testing offline problems. There are issues removing channels/connections from the QTreeWidget which is causing segfaults, but I'm sure it has something to do with my order of deleting objects.
* 2016/08/12 - Offline issues still persist, but I narrowed it down to what I think is some kind of issue dealing with Channel objects stored in the Connection class. The number of channels added to the QList is originally two, but upon clicking the tree, it either segfaults or changes to 1. It is odd as it sometimes does not segfault, but usually it does. Also, I need to re-design Mainwindow::updateOutputTE since if I'm connected to more than one network at a time, the QTextEdit is constantly clearing and re-posting text. The slider implementation from earlier is also no good since each channel has a different number of lines of text. I'd need to save slider position for each channel as well. Good news is, I'm not as disheartened as before, but I may need to re-design parts of this program, if not all of it.
* 2016/08/10 - Fixed double spacing for QTextEdit. Fouled up something else. No idea what happend but now connecting doesn't work as expected. Also, I discovered segfaults if I'm offline and click the tree widget which makes no sense as it doesn't do that if I'm connected to the internet and a network. I wasted a whole day on this and if I don't fix it by the end of the week, I'm most likely going to redesign this program from scratch. I'm feeling like I have too much of the code tangled with each other.
* 2016/08/08 - Successfully implemented data sharing between Connection objects and MainWindow. I created another object, Channel, to keep track of data specific to each channel and then used a QList&lt;Channel&gt; data member in the Connection object. Now, messages are stored in QStringLists one for network notices, and one for each channel connected. The next logical thing to tackle might be handling channel removals from the QTreeWidget, and basic commands to join/part channels.
* 2016/08/05 - Threading and connecting are working. Had data written to QTextEdit but looking for a better way to accomplish it.
* 2016/08/04 - I can now get a working connection, but having trouble with threads. I'll have to look into it more.
* 2016/08/03 - Working on getting a real connection to server which I have done in a test method. Also working on how to update outputTE if new data is received or if networkTree items are clicked.
* 2016/08/01 - Upon 'connect' in NetworkDlg, network is added to QTreeWidget along with children items (#channels). Also able to remove networks via Ctrl+W.
* 2016/07/29 - Implemented the Connection class to successfully transfer data in Connection objects from NetworkDlg to MainWindow. Also fixed a segfault which occured if clicking 'Cancel' in NetworkDlg which sent a null pointer to MainWindow.
* 2016/07/27 - Started to implement the Connection class.
* 2016/07/25 - Created the Connection class for handling the logic of connecting to networks. Each Connection will connect through its own thread.
* 2016/04/05 - Started implementing the network side. I want to complete this rather quickly and get basic functionality for my portfolio.
* 2015/10/23 - I am working on the front-end only and making sure basic file I/O is working properly. I am nearly ready to start delving into the network side of the project.

Libraries and modules used so far:
----------------------------------
Qt5:
   * QtCore
   * QtNetwork
   * QtWidgets
