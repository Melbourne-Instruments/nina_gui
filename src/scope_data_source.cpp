/**
 *-----------------------------------------------------------------------------
 * Copyright (c) 2023 Melbourne Instruments, Australia
 *-----------------------------------------------------------------------------
 * @file  scope_data_source.cpp
 * @brief Scope Data Source class implementation.
 *-----------------------------------------------------------------------------
 */

#include <cmath>
#include "scope.h"
#include "scope_data_source.h"
#include "common.h"
#include "timer.h"

// Constants
constexpr uint REFRESH_RATE_MS        = ((1.f / 60.f) * 1000.f);
constexpr uint SCOPE_IDLE_FRAME_COUNT = 60 * 3;
const float PI                        = std::acos(-1);
const float ROTATE_SCOPE_XY_ANGLE     = 45;
const float ROTATE_SCOPE_XY_SIN       = std::sin((ROTATE_SCOPE_XY_ANGLE * PI) / 180.f);
const float ROTATE_SCOPE_XY_COS       = std::cos((ROTATE_SCOPE_XY_ANGLE * PI) / 180.f);

//----------------------------------------------------------------------------
// ScopeDataSource
//----------------------------------------------------------------------------
ScopeDataSource::ScopeDataSource(GuiScopeMode& scope_mode, QObject *parent) : 
    QObject(parent),
    _scope_mode(scope_mode)
{
    // Initialise class variables
    _data1.clear();
    _data2.clear();
    for (uint i=0; i<SCOPE_NUM_SAMPLES; i++) {
        float x = -1.0f + ((qreal(i) / SCOPE_NUM_SAMPLES) * 2);
        _data1.append(QPointF(x, 0.0f));
        _data2.append(QPointF(x, 0.0f));
    }     
    _data = &_data1;
    _scope = nullptr;
    _scope_idle_threshold = 0.0f;
    _scope_idle_frame_count = 0;
}

//----------------------------------------------------------------------------
// ~ScopeDataSource
//----------------------------------------------------------------------------
ScopeDataSource::~ScopeDataSource()
{
    // Nothing specific to do
}

//----------------------------------------------------------------------------
// start
//----------------------------------------------------------------------------
void ScopeDataSource::start(Scope *scope)
{
    // Save the scope and calculate the idle threshold (+/- 1px)
    _scope = scope;
    _scope_idle_threshold = 1.0f / (_scope->height() / 2);

    // Start the scope refresh timer
    _scope_refresh_timer.setInterval(REFRESH_RATE_MS);
    _scope_refresh_timer.setSingleShot(false);
    QObject::connect(&_scope_refresh_timer, &QTimer::timeout, this, &ScopeDataSource::refreshSeries);
    _scope_refresh_timer.start();
}

//----------------------------------------------------------------------------
// updateData
//----------------------------------------------------------------------------
void ScopeDataSource::updateData(float *samples)
{
    // Get the alternate data to update and clear it
    QVector<QPointF>& data = (_data == &_data1) ? _data2 : _data1;
    data.clear();

    // If there is a scope mode
    if (_scope_mode != GuiScopeMode::SCOPE_MODE_OFF) {
        bool scope_idle = _scope->display_mode() == ScopeDisplayMode::BACKGROUND;

        // Add the points to the data
        for (uint i=0; i<SCOPE_NUM_SAMPLES; i++) {
            QPointF point;

            // Get the L/R samples
            auto l_sample = *samples++;
            auto r_sample = *samples++;

            // If the scope samples are idle so far
            if (scope_idle) {
                // Check if these L and R samples are no longer idle
                if ((l_sample < -(_scope_idle_threshold)) || (l_sample > _scope_idle_threshold) ||
                    (r_sample < -(_scope_idle_threshold)) || (r_sample > _scope_idle_threshold)) {
                    // No longer idle - make sure the scope is shown if it is in
                    // background
                    if (_scope->display_mode() == ScopeDisplayMode::BACKGROUND) {
                        _scope->show();
                    }
                    _scope_idle_frame_count = 0;
                    scope_idle = false;
                }
            }

            // Check the scope mode
            if (_scope_mode == GuiScopeMode::SCOPE_MODE_OSC) {
                // Oscillator - add the scope point
                qreal x = ((qreal(i) / qreal(SCOPE_NUM_SAMPLES)) * 2) - 1.0;
                qreal y = l_sample + r_sample;
                point = QPointF(x, y);
            }
            else {
                // X/Y - add the scope point (rotated)
                point = _rotate_point(l_sample, r_sample);             
            }
            data.append(point);
        }

        // If the scope is currently shown in the background and these samples were idle
        if (scope_idle && _scope->shown() && (_scope->display_mode() == ScopeDisplayMode::BACKGROUND)) {
            // Increment the idle frame count, and if it exceeds the idle
            // threshold then hide the scope (don't reset the display mode when hiding)
            _scope_idle_frame_count++;
            if (_scope_idle_frame_count >= SCOPE_IDLE_FRAME_COUNT) {
                _scope->hide(false);
                _scope_idle_frame_count = 0;      
            }
        }
    }

    // Set the data pointer to the updated data
    _data = &data;    
}

//----------------------------------------------------------------------------
// _rotate_point
//----------------------------------------------------------------------------
QPointF ScopeDataSource::_rotate_point(float x, float y)
{
    // Rotate the point
    qreal rotated_x = (x * ROTATE_SCOPE_XY_COS) - (y * ROTATE_SCOPE_XY_SIN);
    qreal rotated_y = (x * ROTATE_SCOPE_XY_SIN) + (y * ROTATE_SCOPE_XY_COS);
    return QPointF(rotated_x, rotated_y);
}

//----------------------------------------------------------------------------
// refreshSeries
//----------------------------------------------------------------------------
void ScopeDataSource::refreshSeries()
{
    // Refresh the scope
    if (_scope) {
        _scope->refresh_data(*_data);
    }
}
