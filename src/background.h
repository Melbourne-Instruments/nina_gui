/**
 *-----------------------------------------------------------------------------
 * Copyright (c) 2021-2022 Melbourne Instruments, Australia
 *-----------------------------------------------------------------------------
 * @file  background.cpp
 * @brief Background class definitions.
 *-----------------------------------------------------------------------------
 */
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QLabel>

// Background class
class Background : public QLabel
{
	Q_OBJECT
public:
	// Constructors
	explicit Background(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
	explicit Background(const QString &text, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

	// Public functions
	void set_image(const std::string &path);
	void clear_image();
};

#endif
