#include "filetools.h"

#include <QDir>
#include <QDebug>

bool FileTools::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */
            if(!copyDirectoryFiles(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()),
                coverFileIfExist))
                return false;
        }
        else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                targetDir.remove(fileInfo.fileName());
            }

            /// 进行文件copy
            if(!QFile::copy(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()))){
                    return false;
            }
        }
    }
    return true;
}

void FileTools::deleteDir(QString strDirName)
{
    QDir dir(strDirName);

    QStringList listDir  = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
    QStringList listFile = dir.entryList(QDir::Files, QDir::Name);

    foreach (QString strFileName, listFile)
    {
        QFile::remove(strDirName + "/" + strFileName);
    }

    foreach (QString strSubDir, listDir)
    {
        deleteDir(strDirName + "/" + strSubDir);
    }

    QString name = dir.dirName();
    dir.cdUp();
    dir.rmdir(name);

    //dir.mkdir(strDirName);
}

void FileTools::encryptDirnames(QString strDirName)
{
    QFileInfo finfo(strDirName);
    if(finfo.isDir())
    {
        QString basename = finfo.baseName();
        QString key = "super";
        QByteArray newname;
        for(int i=0;i<basename.toLocal8Bit().size();i++ )
        {
            newname.append( basename.toLocal8Bit().at(i)^key.toLocal8Bit().at(i%key.size()) );
        }

        QDir dir(strDirName);

        bool ok = dir.rename( strDirName, QString("%1/jedi_encrypt_%2")
                                            .arg(finfo.absoluteDir().path())
                                            .arg( QString(newname.toHex()) ) );


        qDebug()<<"encrypt "<<ok<<endl;
    }
}

void FileTools::decryptDirnames(QString strDirName)
{
    QFileInfo finfo(strDirName);
    if(finfo.isDir())
    {
        QString basename = finfo.baseName();

        QRegExp rx("^jedi_encrypt_.*");
        if( rx.exactMatch(basename) )
        {
            qDebug()<<"匹配"<<endl;
            basename = basename.replace("jedi_encrypt_","");
        } else {
            qDebug()<<"不匹配"<<endl;
            return;
        }

        QByteArray bytes = FileTools::HexStringToByteArray( basename );
        QString key = "super";
        QByteArray newname;
        for(int i=0;i<bytes.size();i++ )
        {
            newname.append( bytes.at(i)^key.toLocal8Bit().at(i%key.size()) );
        }
        qDebug()<<"QString::fromLocal8Bit(newname): "<<QString::fromLocal8Bit(newname)<<endl;

        QDir dir(strDirName);

        bool ok = dir.rename( strDirName, QString("%1/%2")
                                            .arg(finfo.absoluteDir().path())
                                            .arg( QString::fromLocal8Bit(newname) ) );


        qDebug()<<"decrypt "<<ok<<endl;
    }
}

QByteArray FileTools::HexStringToByteArray(QString HexString)
{
    bool ok;
    QByteArray ret;
    HexString = HexString.replace(" ","");

    for(int i = 1;i<HexString.size();i += 2)
    {
        QString hex = HexString.mid(i-1,2);
        char c = hex.toInt(&ok,16)&0xFF;
        if(ok){
            ret.append(c);
        }else{
            qDebug()<<"非法的16进制字符："<<hex;
        }
    }
    return ret;
}

FileTools::FileTools()
{

}
