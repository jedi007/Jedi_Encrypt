#ifndef FILETOOLS_H
#define FILETOOLS_H

#include <QString>

class FileTools
{
public:
    //拷贝文件夹
    static bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist = true);
    //删除文件夹
    static void deleteDir(QString strDirName);

    static QString encryptDirnames(QString strDirName);

    static QString decryptDirnames(QString strDirName);

    static QByteArray HexStringToByteArray(QString HexString);
private:
    FileTools();

};
#endif // FILETOOLS_H
