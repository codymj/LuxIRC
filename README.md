LuxIRC:
=======
Lux is the SI symbol for illuminance. IRC is an old and vast social gathering which gives the potential to illuminate your mind.

LuxIRC is intended to be a basic IRC client without too much bloat (I hope). It is a self-project of mine to learn the basics of GUI and network programming while making something useful. I am testing and developing the program in Arch Linux only (for now).

I have recently started working on the project again and I will try to finish the basic function of the software soon.

Current Progress:
-----------------
* 2016/09/07 - Today I edited the format of the QTextEdit outputTE. I have introduced left padding all nick names with spaces and set the font to the monospace family. The number of spaces is a function of the "NICKLEN" attribute given to clients upon connection from the IRC server and also the length of the nick itself. I want to implement a hanging indent for wrapped lines but that is going to take some creativity as I don't see how to do it immediately from the reference pages on QTextEdit or QTextBlockFormat classes.

* 2016/09/01 - I've implemented basic message writing, finally. I've also added a feature which determines how many characters left for typing. IRC protocol has a max amount of 512 characters for all data including command, parameters and CR-LF chars. I've also noticed when trying to run the program on Windows 10, there is an issue with QFile::open() due to not being able to find the specified path. I messed around with it in vain. It really should not be this difficult to fix but since it works in Linux just fine, I blame Qt. I remember having this issue before as well but I forgot how to resolve it. I've tried using native separators and absolute paths, but nothing seems to work. Sometimes the file saves, but won't read from it also, again only on Windows.

* 2016/08/31 - Fixed segfaults dealing with outputTE. If all Connection objects were deleted, it was still trying to access data dealing with scroll bar position for each Connection and Channel. I've also figured out how to implement socket writing. I simply store all outgoing data into a QQueue&lt;QByteArray&gt; created as a data member for each Connection. I then changed waitForReadyRead() to waitForReadyRead(1000) in the connection loop. That way, it will check for data each second which allows me to then write data stored into the QQueue each second as well. If the QQueue is empty with no data, it simply skips that branch. I have also changed how the user list is constructed. Instead of a QStringList with all users, I broke it up into a QList&lt;QStringList&gt; holding a separate list for owners, sops, ops, hops, voiced and regular users with each sorted and then passed to the MainWindow->userList to populate the GUI list of users.

* 2016/08/29 - I tracked the segfault down to a null PART message in the arg index (data.at(3) in Connection::parseData()). If it didn't crash on the first part from channel, which it did maybe 20% of the time, it would always crash on the second part from channel. The argument data.at(3) represents the PART message in the form of QString. I'm guessing it is NULL and should be set manually in a settings widget when I implement that. Writing with the socket created in Connection::run() has proven to be a challenge. I have a few ideas to try and hopefully one works. I will first try subclassing QTcpSocket to create a custom slot for writing inside of run().

* 2016/08/26 - I have implemented user lists for each Channel, however another segfault exists. If a user joins a channel and parts twice in a row, it causes a segfault. Unsure why at this point. I'll have to look into it further, maybe tomorrow.

* 2016/08/24 - I fixed the Connection loop algorithm. It now waits and appends data until each block of data receieved is terminated with "\r\n" which makes it much easier to parse. Here is an example of how I parsed the data:
<p align="center">
  <img src="http://i.imgur.com/k36VH1c.png"/>
</p>
I have also implemented the topic signal/slot for the Channel object. Now, when viewing a Channel, the topic is displayed in the QLineEdit at the top of MainWindow.

* 2016/08/22 - Overhauled Connection::parseData() and made Connection::processData() to do all of the data sorting for various IRC commands (JOIN, PRIVMSG, NOTICE, etc) and it seems to be working okay. Fun stuff will begin soon.

* 2016/08/20 - I did some testing and I could not create a segfault. I also added some small functions to facilitate changing nick between the changeNickBtn and the nick stored in Connection objects. I want to add a regular expression to make sure the nick name fields comply with IRC protocal, but that has proven to be difficult as I am not good with regex. If nothing else comes up, I'll start with expanding my data parsing and socket->write() next week.

* 2016/08/19 - Fixed segfaults dealing with QTcpSockets. I read from a Qt source that QTcpSockets do something behind the scenes AFTER disconnecting from host, but since I was deleting the entire Connection object before that happens, the socket pointer is no longer accessible, causing the segfault. I also implemented another signal to tell the main thread when the Connection thread is finished, calling another implemented slot to delete that Connection. This makes the Connection thread exit safely and thus, no more "Thread destroyed while running" warnings. Tomorrow, I am going to go through the code and try to modularize it a bit more because I think I can do a few things in the Connection class which I'm doing in the MainWindow class, such as deleting Channels in the Connection class itself rather than doing it in MainWindow. I will also do some "stress" testing and see if I can break the program some how. After that, I should be ready to implement some of the fun things, like parsing message formats and implementing some socket->write() functions.

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
   * QtGui
   * QtNetwork
   * QtWidgets
