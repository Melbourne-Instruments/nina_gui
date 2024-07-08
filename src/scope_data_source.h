/**
 *-----------------------------------------------------------------------------
 * Copyright (c) 2023 Melbourne Instruments, Australia
 *-----------------------------------------------------------------------------
 * @file  scope_data_source.h
 * @brief Scope Data Source class definitions.
 *-----------------------------------------------------------------------------
 */
#ifndef SCOPE_DATA_SOURCE_H
#define SCOPE_DATA_SOURCE_H

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <QtCore/QElapsedTimer>
#include <QtCore/QTimer>
#include "scope.h"
#include "common.h"

// Scope Data Source class
class ScopeDataSource : public QObject
{
    Q_OBJECT
public:
    ScopeDataSource(GuiScopeMode& scope_mode, QObject *parent=0);
    ~ScopeDataSource();

    void start(Scope *scope);
    void updateData(float *samples);

public slots:
    void refreshSeries();

private:
    // Private data
    GuiScopeMode& _scope_mode;
    QVector<QPointF> _data1;
    QVector<QPointF> _data2;
    QVector<QPointF> *_data;
    QTimer _scope_refresh_timer;
    Scope *_scope;
    float _scope_idle_threshold;
    uint _scope_idle_frame_count;

    // Private functions
    QPointF _rotate_point(float x, float y);
};

#endif
