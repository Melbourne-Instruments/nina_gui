/**
 *-----------------------------------------------------------------------------
 * Copyright (c) 2021-2023 Melbourne Instruments, Australia
 *-----------------------------------------------------------------------------
 * @file  main.cpp
 * @brief Main entry point to the Nina GUI.
 *-----------------------------------------------------------------------------
 */
#include <signal.h>
#include <QApplication>
#include <QScreen>
#include <QSplashScreen>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "main_window.h"
#include "common.h"
#include "version.h"

// Constants
constexpr char CONFIG_FILE[] = "/udata/nina/config.json";

// Local functions
QString _get_system_colour();
QPixmap _set_pixmap_colour(const QPixmap& pixmap, QColor colour);
void _print_nina_gui_info();
void _sigint_handler([[maybe_unused]] int sig);

//----------------------------------------------------------------------------
// main
//----------------------------------------------------------------------------
int main(int argc, char *argv[ ])
{
	QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication app(argc, argv);

    // Get the system colour
    QString system_colour_str = _get_system_colour();

    // Convert the system colour to an integer value
    QRgb colour;
    try {
        colour = std::stoi(system_colour_str.toStdString(), nullptr, 16);
    }
    catch (...) {
        colour = std::stoi(DEFAULT_SYSTEM_COLOUR, nullptr, 16);
    }
    QColor system_colour(colour);

    // Show the first splash while we are getting ready
    QPixmap pixmap1(MELB_INST_SPLASH_PNG_RES);
    QSplashScreen splash1(_set_pixmap_colour(pixmap1, system_colour));
    splash1.show();    

    // Setup the exit signal handler (e.g. ctrl-c, kill)
    signal(SIGINT, _sigint_handler);
    signal(SIGTERM, _sigint_handler);

    // Show the app info
    _print_nina_gui_info();

    // Show the second splash while we are getting ready
    QPixmap pixmap2(NINA_SPLASH_PNG_RES);
    QSplashScreen splash2(_set_pixmap_colour(pixmap2, system_colour));
    splash1.finish(&splash2);
    splash2.show();

    // Show the main window and execute the app
    MainWindow main_window(system_colour_str, system_colour);
    splash2.finish(&main_window);
    main_window.show();
    int res = app.exec();

    // Nina GUI has exited
    MSG("NINA GUI exited");    
    return res; 
}

//----------------------------------------------------------------------------
// _get_system_colour
//----------------------------------------------------------------------------
QString _get_system_colour()
{
    QString colour = DEFAULT_SYSTEM_COLOUR;

    // We need to read the system colour from the NINA config file
    // Firstly open and read the config file
    QFile file;
    QString config_json;
    file.setFileName(CONFIG_FILE);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Read the file contents
        config_json = file.readAll();
        file.close();

        // Now get the system colour
        QJsonDocument doc = QJsonDocument::fromJson(config_json.toUtf8());
        QJsonObject obj = doc.object();
        QJsonValue val = obj.value(QString("system_colour"));
        if ((val != QJsonValue::Undefined) && val.isString()) {
            // Set the system colour
            colour = val.toString();            
        }
    }
    return colour;
}

//----------------------------------------------------------------------------
// _set_pixmap_colour
//----------------------------------------------------------------------------
QPixmap _set_pixmap_colour(const QPixmap& pixmap, QColor colour)
{
    // Convert the Pixmap colour
    QColor default_colour(0xFF, 0x00, 0x00);
    QImage tmp(pixmap.toImage());
    for (int y=0; y<tmp.height(); y++) {
        for (int x=0; x<tmp.width(); x++){
            // Change the pixel colour if needed
            colour.setAlpha(tmp.pixelColor(x, y).alpha());
            default_colour.setAlpha(tmp.pixelColor(x, y).alpha());
            if (tmp.pixelColor(x, y) == default_colour)
                tmp.setPixelColor(x, y, colour);
        }
    }
    return QPixmap::fromImage(tmp);
}

//----------------------------------------------------------------------------
// _print_nina_gui_info
//----------------------------------------------------------------------------
void _print_nina_gui_info()
{
    MSG("NINA GUI - Copyright (c) 2023 Melbourne Instruments, Australia");
#ifdef NINA_GUI_BETA_RELEASE    
    MSG("Version " << NINA_GUI_MAJOR_VERSION << "." 
                   << NINA_GUI_MINOR_VERSION << "." 
                   << NINA_GUI_PATCH_VERSION << "-beta" 
                   << " (" << NINA_GUI_GIT_COMMIT_HASH << ")");
#else
    MSG("Version " << NINA_GUI_MAJOR_VERSION << "." 
                   << NINA_GUI_MINOR_VERSION << "." 
                   << NINA_GUI_PATCH_VERSION
                   << " (" << NINA_GUI_GIT_COMMIT_HASH << ")");
#endif
    MSG("");
}

//----------------------------------------------------------------------------
// _sigint_handler
//----------------------------------------------------------------------------
void _sigint_handler([[maybe_unused]] int sig)
{
    // Quit the QT app and clean everything up
    qApp->quit();
}
