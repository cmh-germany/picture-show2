/* ------------------------------------------------------------------
loaddirectory.h is part of picture-show2.
.....................................................................

picture-show is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

picture-show2 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with picture-show. If not, see <http://www.gnu.org/licenses/>.

......................................................................

author: Sebastian Sch�fer
March 2013

--------------------------------------------------------------------*/

#ifndef LOADDIRECTORY_H
#define LOADDIRECTORY_H

#include <QThread>
#include <QList>
#include <QSet>
#include <QPair>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QDateTime>

#include "readExif.h"
#include "global.h"

static bool fileCreateLessThan(const QPair<QFileInfo, QDateTime> &f1, const QPair<QFileInfo, QDateTime> &f2);
static bool fileNameLessThan(const QFileInfo &f1, const QFileInfo &f2);
static int LARGE_DATA = 50000;
static int LARGE_DATA2 = 1000;
static int LARGE_DATA3 = 20000;

class loadDirectory : public QThread
{
    Q_OBJECT
public:
    loadDirectory();

    void setDirectory(const QString &path);
    const QString & getDirectory();
    void setDirectoryList(QList<QFileInfo> *list);
    void setDropList(QSet<QString> *d_list);
    void setSorting(Sorting sortType);
    Sorting getSorting();
    bool getIncludeSubdirs();
    void setIncludeSubdirs(bool sd);

    void setOpenModeToDropList();
    void setOpenModeToFolder();

    void setForceLargeData(bool state);

    QString& getErrorMsg();

    void run();
    
signals:
    void loadDirectoryFinished(bool success);

private:
    void addItemsInDir(QList<QString> &t_list, QStringList t_filters, QDir t_directory);

    Sorting m_sorting;
    QString m_path;
    bool m_subdirs;
    QString m_error_msg;
    QSet<QString> * m_dropList;
    QList<QFileInfo> * m_dirList;

    bool m_openMode_drop;
    bool m_forcing_large_data;
    
};

#endif // LOADDIRECTORY_H
