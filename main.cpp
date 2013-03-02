/* ------------------------------------------------------------------
main.cpp is part of picture-show2.
.....................................................................

picture-show2 is free software: you can redistribute it and/or modify
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

author: Sebastian Schäfer
February 2013

--------------------------------------------------------------------*/

#include <QtGui/QGuiApplication>
#include <QtWidgets/QApplication>
#include <QtQml>
#include <QTimer>
#include <QGLFormat>
#include <QMessageBox>
#include "qtquick2applicationviewer.h"

#include "settingsdialog.h"
#include "supervisor.h"

int main(int argc, char *argv[])
{
    QString appVersion = QString("2.01 beta ");

    #if defined (_MSC_VER)
        #if _MSC_VER >= 1600
            appVersion += QString("(MSVC v10.0 ");
        #elif _MSC_VER >= 1500
            appVersion += QString("(MSVC v9.0 ");
        #else
            appVersion += QString("(MSVC < 9.0 ");
        #endif
    #elif defined (__GNUC__)
        std::ostringstream os;
        os << __GNUC__ << "." << __GNUC_MINOR__;
        appVersion += QString("(GCC v") + QString(os.str().c_str()) + QString(" ");
    #elif defined (__MINGW32__)
        std::ostringstream os;
        os << __MINGW32_MAJOR_VERSION << "." << __MINGW32_MINOR_VERSION;
        appVersion += QString("MinGW v") + QString(os.str().c_str());
    #else
        appVersion += QString("(unknown compiler ");
    #endif

    #if defined (_M_X64) || defined (__x86_64__)
        appVersion += QString("x64)");
    #else
        appVersion += QString("x86)");
    #endif

    QApplication app(argc, argv);
    app.setApplicationName(QString("picture-show 2"));
    app.setApplicationVersion(appVersion);

    if (!QGLFormat::hasOpenGL())
    {
        QMessageBox warning(QMessageBox::Warning,
                            QString("OpenGL nicht unterstützt - OpenGL not supported"),
                            QString("OpenGL Unterstützung wurde auf diesem System nicht gefunden. Das Programm wird keinen optimalen Leistungen erzielen! Soll dennoch gestartet werden?\n\nOpenGL not found on the system. The application will not achieve best performance! Should we start anyway?"),
                            QMessageBox::Yes | QMessageBox::No);

        if (warning.exec() == QMessageBox::No)
            return app.quit();
    }
//    qmlRegisterType<SettingsDialog>("CustomComponents", 1, 0, "SettingsDialog");

//    QtQuick2ApplicationViewer viewer;

//    SettingsDialog s_dialog;

//    int new_x_pos = viewer.position().x() + (int(viewer.size().width()/2) - int(s_dialog.size().width()/2));
//    int new_y_pos = viewer.position().y() + (int(viewer.size().height()/2) - int(s_dialog.size().height()/2));

//    s_dialog.move(new_x_pos, new_y_pos);

//    //QTimer::singleShot(1000, &s_dialog, SLOT(show()));
//    //s_dialog.show();

//    QQmlContext * context = viewer.engine()->rootContext();
//    context->setContextProperty("_settings_dialog", &s_dialog);

    Supervisor sup(&app);
    if (!sup.isQmlReady())
        return app.quit();
//    superV->setDialog(&s_dialog);
//    superV->setView(&viewer);

//    context->setContextProperty("_supervisor", superV);

//    viewer.showExpanded();
//    viewer.setMainQmlFile(QStringLiteral("qml/picture-show2/main.qml"));

//    superV->bindings();

    return app.exec();
}
