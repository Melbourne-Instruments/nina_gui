/**
 *-----------------------------------------------------------------------------
 * Copyright (c) 2021-2022 Melbourne Instruments, Australia
 *-----------------------------------------------------------------------------
 * @file  background.cpp
 * @brief Background class implementation.
 *-----------------------------------------------------------------------------
 */
#include <QTimer>
#include "background.h"
#include "common.h"

//----------------------------------------------------------------------------
// Background
//----------------------------------------------------------------------------
Background::Background(QWidget *parent, Qt::WindowFlags f) 
    : Background("", parent, f)
{
    // Setup the label parameters
    setStyleSheet("QLabel { background-color : black; }");
    setScaledContents(true);
    resize(LCD_WIDTH, LCD_HEIGHT);
}

//----------------------------------------------------------------------------
// Background
//----------------------------------------------------------------------------
Background::Background(const QString &text, QWidget *parent, Qt::WindowFlags f) 
    : QLabel(text, parent, f)
{
    // Nothing specific to do
}

//----------------------------------------------------------------------------
// set_image
//----------------------------------------------------------------------------
void Background::set_image(const std::string &path)
{
    // Show the image
    setPixmap(QPixmap(path.c_str()));
}

//----------------------------------------------------------------------------
// clear_image
//----------------------------------------------------------------------------
void Background::clear_image()
{
    // Clear the image
    setPixmap(QPixmap());
}
