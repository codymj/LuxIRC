#include <QCoreApplication>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTcpSocket>
#include <QTextStream>
#include <QDebug>
#include <string>

QTcpSocket socket;

int main() {
   // File for text
   QFile *outFile = new QFile("out.txt");
   QTextStream outStream(outFile);
   
   if (!outFile->open(QFile::WriteOnly | QFile::Text)) {
      qDebug() << "Could not open file for writing.\n";
      return 1;
   }
   
   // Data
   QString host = "chat.freenode.net";
   int port = 6667;
      
   socket.connectToHost(host, port);
   if (socket.waitForConnected(3000)) {
      socket.write("NICK user1234\r\n");
      socket.write("USER user1234 0 * :user1234\r\n");
      socket.waitForBytesWritten();
      socket.waitForReadyRead();
      
      qDebug() << "Reading: " << socket.bytesAvailable() << " bytes.";
      qDebug() << socket.readAll();
      
      std::string serverResp;
      for (;;) {
         socket.waitForReadyRead(100);
         serverResp = socket.readAll().toStdString();
         
         if (!serverResp.empty()) {
            qDebug() << serverResp.c_str();
            outStream << serverResp.c_str();
            
            size_t spaceIdx = serverResp.find(' ');
            if (serverResp.substr(0, spaceIdx).compare("PING") == 0) {
               std::string pongStr = "PONG" + serverResp.substr(spaceIdx);
               socket.write(pongStr.c_str());
               qDebug() << "PONG sent.";
            }
         }
      }
      
      outFile->flush();
      outFile->close();
      delete outFile;
      socket.close();
   }
   else {
      qDebug() << "Not connected...";
   }
   
   return 0;
}
