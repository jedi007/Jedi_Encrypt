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

QString FileTools::encryptDirnames(QString strDirName)
{
    qDebug()<<"encryptDirnames called: "<<strDirName<<endl;

    QFileInfo finfo(strDirName);

    QString basename = finfo.baseName();
    if(finfo.isFile())
    {
        basename = strDirName.split("/").last();
        if(basename.lastIndexOf('.')<basename.size())
            basename = basename.left(basename.lastIndexOf('.'));
    }

    QString key = "super";
    QByteArray newname;
    for(int i=0;i<basename.toLocal8Bit().size();i++ )
    {
        newname.append( basename.toLocal8Bit().at(i)^key.toLocal8Bit().at(i%key.size()) );
    }

    QString newnamepath;
    if(finfo.isDir())
    {
        QDir dir(strDirName);
        newnamepath = QString("%1/jedi_encrypt_%2")
                .arg(finfo.absoluteDir().path())
                .arg( QString(newname.toHex()) ).replace("//","/");
        bool ok = dir.rename( strDirName, newnamepath );

        if(!ok)
        {
            qDebug()<<"rename to "<<newnamepath<<"  failed"<<endl;
            return strDirName;
        }

        QDir newdir(newnamepath);
        QStringList listDir  = newdir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
        QStringList listFile = newdir.entryList(QDir::Files, QDir::Name);

        foreach (QString strFileName, listFile)
        {

            FileTools::encryptDirnames(newnamepath+"/"+strFileName);
        }

        foreach (QString strSubDir, listDir)
        {
            FileTools::encryptDirnames(newnamepath+"/"+strSubDir);
        }
    }
    else if(finfo.isFile())
    {
        QFile file(strDirName);
        newnamepath = QString("%1/jedi_encrypt_%2.%3")
                .arg(finfo.absoluteDir().path())
                .arg( QString(newname.toHex()) )
                .arg(finfo.suffix());
        file.rename( strDirName, newnamepath );
    }
    return newnamepath;
}

QString FileTools::decryptDirnames(QString strDirName)
{
    qDebug()<<"decryptDirnames called: "<<strDirName<<endl;

    QFileInfo finfo(strDirName);

    QString basename = finfo.baseName();

    QRegExp rx("^jedi_encrypt_.*");
    if( rx.exactMatch(basename) )
    {
        qDebug()<<"匹配"<<endl;
        basename = basename.replace("jedi_encrypt_","");
    } else {
        qDebug()<<"不匹配"<<endl;
        return finfo.path();
    }

    QByteArray bytes = FileTools::HexStringToByteArray( basename );
    QString key = "super";
    QByteArray newname;
    for(int i=0;i<bytes.size();i++ )
    {
        newname.append( bytes.at(i)^key.toLocal8Bit().at(i%key.size()) );
    }

    QString newnamepath;
    if(finfo.isDir())
    {
        QDir dir(strDirName);
        newnamepath = QString("%1/%2")
                .arg(finfo.absoluteDir().path())
                .arg( QString::fromLocal8Bit(newname) ).replace("//","/");
        bool ok = dir.rename( strDirName,  newnamepath);
        if(!ok)
        {
            qDebug()<<"rename to "<<newnamepath<<"  failed"<<endl;
            return strDirName;
        }
        qDebug()<<"rename to "<<newnamepath<<"  successed"<<endl;

        QDir newdir(newnamepath);
        QStringList listDir  = newdir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
        QStringList listFile = newdir.entryList(QDir::Files, QDir::Name);

        foreach (QString strFileName, listFile)
        {
            FileTools::decryptDirnames(newnamepath+"/"+strFileName);
        }

        foreach (QString strSubDir, listDir)
        {
            FileTools::decryptDirnames(newnamepath+"/"+strSubDir);
        }

    }
    else
    {
        QFile file(strDirName);
        newnamepath = QString("%1/%2.%3")
                .arg(finfo.absoluteDir().path())
                .arg( QString::fromLocal8Bit(newname) )
                .arg(finfo.suffix());

        file.rename( strDirName,newnamepath );
    }

    return newnamepath;
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
