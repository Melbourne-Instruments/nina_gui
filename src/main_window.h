/**
 *-----------------------------------------------------------------------------
 * Copyright (c) 2021-2023 Melbourne Instruments, Australia
 *-----------------------------------------------------------------------------
 * @file  main_window.cpp
 * @brief Main Window class definitions.
 *-----------------------------------------------------------------------------
 */
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <thread>
#include <atomic>
#include <QMainWindow>
#include <QLabel>
#include <QListWidget>
#include <QTreeWidget>
#include <QTimer>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include "background.h"
#include "timer.h"
#include "gui_msg_thread.h"
#include "wt_file.h"
#include "scope_msg_thread.h"
#include "scope_data_source.h"
#include "scope.h"
#ifdef SPI_STATUS_MONITOR
#include "spi_monitor_thread.h"
#endif

// Use the Qt Charts namespace
QT_CHARTS_USE_NAMESPACE

// Constants
constexpr uint NUM_ASCII_CHARS   = (1 + 26 + 10 + 1);
constexpr uint ASCII_PICKER_SIZE = 7;

// Main Window class
class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
    // Constructor
    MainWindow(QString colour_str, QColor colour, QWidget *parent = nullptr);
    ~MainWindow();
    void set_system_colour(QString colour_str, QColor colour);

public slots:
    void set_left_status(const LeftStatus& msg);
    void set_layer_status(const LayerStatus& msg);
    void set_midi_status(const MidiStatus& msg);
    void set_tempo_status(const TempoStatus& msg);
    void show_home_screen(const HomeScreen& msg);
    void show_list_items(const ListItems& msg);
    void list_select_item(const ListSelectItem& msg);
    void set_soft_buttons(const SoftButtons& msg);
    void set_soft_buttons_state(const SoftButtonsState& msg);
    void process_param_update(const ParamUpdate& msg);
    void process_param_value_update(const ParamValueUpdate& msg);
    void process_enum_param_update(const EnumParamUpdate& msg);
    void process_enum_param_value_update(const ListSelectItem& msg);
    void process_edit_name(const EditName& msg);
    void process_edit_name_select_char(const EditNameSelectChar& msg);
    void process_edit_name_change_char(const EditNameChangeChar& msg);
    void show_confirmation_screen(const ConfirmationScreen& msg);
    void show_warning_screen(const WarningScreen& msg);
    void clear_boot_warning();
    void set_system_colour(const SetSystemColour& msg);  
#ifdef SPI_STATUS_MONITOR
    void set_spi_status(uint count);
#endif

private:
    // Private variables
    Background *_background;
    QLabel *_boot_warning_background;
    QLabel *_default_background;  
    QLabel *_status_bar_background;
    QLabel *_left_status;
    QLabel *_patch_modified_status;
    QLabel *_layer_status;
    QLabel *_midi_status;
    QLabel *_tempo_status;    
    QLabel *_spi_status;
    QLabel *_param_value;
    QLabel *_param_value_tag;
    QListWidget *_params_list;
    QListWidget *_enum_param_list;
    QListWidget *_wt_enum_param_list;
    Scope *_wt_scope;
    QTimer *_wt_chart_timer;
    QListWidget *_main_area_list;
    QLabel *_soft_button1;
    QLabel *_soft_button2;
    QLabel *_soft_button3;
    QLabel *_edit_name[EDIT_NAME_STR_LEN];
    QLabel *_ascii_picker[ASCII_PICKER_SIZE];
    QLabel *_confirmation_screen_background;
    QLabel *_confirmation_screen_line_1;
    QLabel *_confirmation_screen_line_2;
    QLabel *_warning_screen_background_1;
    QLabel *_warning_screen_background_2;
    QLabel *_warning_screen_line_1;
    QLabel *_warning_screen_line_2;
    QLabel *_warning_screen_hourglass;
    Scope *_scope;
    QLabel *_dummy_label;
    char _ascii_chars[NUM_ASCII_CHARS];
    int _selected_char;
    std::vector<std::string> _list_items;
    std::vector<bool> _list_items_enabled;
    std::vector<bool> _list_items_separator;
    std::vector<std::string> _enum_list_items;
    GuiMsgThread *_gui_thread;
    ScopeMsgThread *_scope_thread;
#ifdef SPI_STATUS_MONITOR
    SpiMonitorThread *_spi_thread;
#endif
    Timer *_conf_screen_timer;
    QString _system_colour_str;
    QColor _system_colour;
    uint _hourglass_pixmap_index = 0;
    std::vector<QPixmap> _hourglass_pixmaps;
    QTimer *_hourglass_timer;
    WtFile _wt_file;
    GuiScopeMode _scope_mode;
    ScopeDataSource _scope_data_source{_scope_mode};

    // Private functions
    void _show_default_background(bool show, bool show_scope);
    void _show_top_bar(bool show);
    void _show_logo_obj(bool show);
    void _show_param_obj(bool show);
    void _show_enum_param_list_obj(bool show);
    void _show_list_obj(bool show);
    void _show_soft_buttons(bool show);
    void _show_edit_name_obj(bool show);
    void _show_confirmation_screen_obj(bool show);
    void _show_warning_screen_obj(bool show, bool show_hourglass=false);
    void _set_soft_button_text(QLabel *soft_button, const char *txt);
    void _set_soft_button_state(QLabel *soft_button, int state);
    void _set_ascii_picker_geometry(bool hide);
    void _create_gui_objs();
    void _set_gui_objs_system_colour();  
    void _conf_screen_timer_callback();
    void _left_status_set_text(const char *text, bool patch_modified=false);
    void _label_set_text(QLabel *label, const char *text, int max_width);
    void _wt_label_set_text(QLabel *label, const char *text);
    void _list_label_set_text(QLabel *label, QString text, bool selected, bool enabled, bool separator);
    void _list_add_item(QListWidget *list, const char *text, int list_width);
    void _list_add_item(QListWidget *list, const char *text, int list_width, bool selected, bool enabled);
    QPixmap _set_pixmap_to_system_colour(const QPixmap& pixmap);
    QString _get_dimmed_system_stylesheet_colour();
    void _clear_scope();
    void _update_wt_chart();
    void _show_zero_wt_chart();
    void _clear_wt_chart();
    void _update_hourglass_image();
};

#endif
