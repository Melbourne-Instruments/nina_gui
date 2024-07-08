/**
 *-----------------------------------------------------------------------------
 * Copyright (c) 2021-2023 Melbourne Instruments, Australia
 *-----------------------------------------------------------------------------
 * @file  main_window.cpp
 * @brief Main Window class implementation.
 *-----------------------------------------------------------------------------
 */
#include <QFontDatabase>
#include <QHeaderView>
#include <QMovie>
#include "main_window.h"
#include "common.h"
#include "version.h"

// Constants
constexpr char STANDARD_FONT_NAME[]      = "OCR-B";
constexpr char PARAM_VALUE_FONT_NAME[]   = "DSEG7 Classic";
constexpr uint VISIBLE_LCD_MARGIN_LEFT   = 9;
constexpr uint VISIBLE_LCD_MARGIN_RIGHT  = 1;
constexpr uint VISIBLE_LCD_WIDTH         = (LCD_WIDTH - VISIBLE_LCD_MARGIN_LEFT - VISIBLE_LCD_MARGIN_RIGHT);
constexpr uint VISIBLE_LCD_MARGIN_TOP    = 5;
constexpr uint VISIBLE_LCD_MARGIN_BOTTOM = 5;
constexpr uint VISIBLE_LCD_HEIGHT        = (LCD_HEIGHT - VISIBLE_LCD_MARGIN_TOP - VISIBLE_LCD_MARGIN_BOTTOM);
constexpr uint NINA_LOGO_WIDTH           = 853;
constexpr uint NINA_LOGO_HEIGHT          = 479;
constexpr uint TOP_ROW_MARGIN_LEFT       = VISIBLE_LCD_MARGIN_LEFT;
constexpr uint TOP_ROW_MARGIN_TOP        = VISIBLE_LCD_MARGIN_TOP;
constexpr uint TOP_ROW_WIDTH             = VISIBLE_LCD_WIDTH;
constexpr uint TOP_ROW_HEIGHT            = 60;
constexpr uint LEFT_STATUS_MARGIN_LEFT   = (TOP_ROW_MARGIN_LEFT + 20);
constexpr uint LEFT_STATUS_MARGIN_TOP    = TOP_ROW_MARGIN_TOP;
constexpr uint LEFT_STATUS_HEIGHT        = TOP_ROW_HEIGHT;
constexpr uint LEFT_STATUS_FONT_SIZE     = 36;
constexpr uint MIDI_STATUS_MARGIN_RIGHT  = (20 + VISIBLE_LCD_MARGIN_RIGHT);
constexpr uint MIDI_STATUS_MARGIN_TOP    = TOP_ROW_MARGIN_TOP;
constexpr uint MIDI_STATUS_HEIGHT        = TOP_ROW_HEIGHT;
constexpr uint LIST_MARGIN_LEFT          = VISIBLE_LCD_MARGIN_LEFT;
constexpr uint LIST_MARGIN_TOP           = (LEFT_STATUS_MARGIN_TOP + LEFT_STATUS_HEIGHT + 1);
constexpr uint LIST_WIDTH                = VISIBLE_LCD_WIDTH;
constexpr uint LIST_ROW_HEIGHT           = 48;
constexpr uint LIST_HEIGHT               = (7 * LIST_ROW_HEIGHT);
constexpr uint LIST_FONT_SIZE            = 30;
constexpr uint WT_LIST_WIDTH             = (VISIBLE_LCD_WIDTH/2);
constexpr uint WT_CHART_MARGIN_LEFT      = (LIST_MARGIN_LEFT + WT_LIST_WIDTH + 10);
constexpr uint WT_CHART_MARGIN_TOP       = (LIST_MARGIN_TOP + 10);
constexpr uint WT_CHART_WIDTH            = (VISIBLE_LCD_WIDTH - WT_LIST_WIDTH - 20);
constexpr uint WT_CHART_HEIGHT           = LIST_HEIGHT - 20;
constexpr uint PARAM_LIST_WIDTH          = (VISIBLE_LCD_WIDTH/2);
constexpr uint PARAM_VALUE_MARGIN_LEFT   = 20;
constexpr uint PARAM_VALUE_MARGIN_RIGHT  = PARAM_LIST_WIDTH + 20;
constexpr uint PARAM_VALUE_WIDTH         = (VISIBLE_LCD_WIDTH - PARAM_VALUE_MARGIN_RIGHT - PARAM_VALUE_MARGIN_LEFT);
constexpr uint PARAM_VALUE_NUM_FONT_SIZE = 80;
constexpr uint PARAM_VALUE_TXT_FONT_SIZE = 36;
constexpr uint PARAM_VALUE_TAG_FONT_SIZE = 30;
constexpr uint SOFT_BUTTONS_MARGIN_LEFT  = VISIBLE_LCD_MARGIN_LEFT;
constexpr uint SOFT_BUTTONS_MARGIN_TOP   = (LIST_MARGIN_TOP + LIST_HEIGHT + 1);
constexpr uint SOFT_BUTTON_1_WIDTH       = 278;
constexpr uint SOFT_BUTTON_2_WIDTH       = 278;
constexpr uint SOFT_BUTTON_3_WIDTH       = 288;
constexpr uint SOFT_BUTTON_HEIGHT        = (VISIBLE_LCD_HEIGHT - SOFT_BUTTONS_MARGIN_TOP);
constexpr uint SOFT_BUTTON_FONT_SIZE     = 32;
constexpr uint EDIT_NAME_MARGIN_LEFT     = 184;
constexpr uint EDIT_NAME_SEL_CHAR_WIDTH  = 32;
constexpr uint EDIT_NAME_CHAR_WIDTH      = 24;
constexpr uint EDIT_NAME_CHAR_HEIGHT     = 44;
constexpr uint EDIT_NAME_FONT_SIZE       = 32;
constexpr uint ASCII_PICKER_MARGIN_LEFT  = EDIT_NAME_MARGIN_LEFT;
constexpr uint ASCII_PICKER_MARGIN_TOP   = 76;
constexpr uint ASCII_PICKER_ITEM_WIDTH   = EDIT_NAME_SEL_CHAR_WIDTH;
constexpr uint ASCII_PICKER_ITEM_HEIGHT  = EDIT_NAME_CHAR_HEIGHT;
constexpr uint ASCII_PICKER_FONT_SIZE    = EDIT_NAME_FONT_SIZE;
constexpr uint WARNING_SCREEN_1_MARGIN_LEFT = VISIBLE_LCD_MARGIN_LEFT;
constexpr uint WARNING_SCREEN_1_MARGIN_TOP  = (TOP_ROW_MARGIN_TOP + TOP_ROW_HEIGHT);
constexpr uint WARNING_SCREEN_1_WIDTH       = VISIBLE_LCD_WIDTH;
constexpr uint WARNING_SCREEN_1_HEIGHT      = (SOFT_BUTTONS_MARGIN_TOP - WARNING_SCREEN_1_MARGIN_TOP);
constexpr uint WARNING_SCREEN_2_MARGIN_LEFT = (WARNING_SCREEN_1_MARGIN_LEFT + 40);
constexpr uint WARNING_SCREEN_2_MARGIN_TOP  = (WARNING_SCREEN_1_MARGIN_TOP + 40);
constexpr uint WARNING_SCREEN_2_WIDTH       = (WARNING_SCREEN_1_WIDTH - 80);
constexpr uint WARNING_SCREEN_2_HEIGHT      = (WARNING_SCREEN_1_HEIGHT - 80);
constexpr uint CONFIRMATION_SCREEN_MARGIN_LEFT = VISIBLE_LCD_MARGIN_LEFT;
constexpr uint CONFIRMATION_SCREEN_MARGIN_TOP  = (LEFT_STATUS_MARGIN_TOP + LEFT_STATUS_HEIGHT);
constexpr uint CONFIRMATION_SCREEN_WIDTH       = VISIBLE_LCD_WIDTH;
constexpr uint CONFIRMATION_SCREEN_HEIGHT      = (SOFT_BUTTONS_MARGIN_TOP - CONFIRMATION_SCREEN_MARGIN_TOP);
constexpr uint SCOPE_MARGIN_TOP                = TOP_ROW_HEIGHT + 15;
constexpr uint SCOPE_HEIGHT                    = (VISIBLE_LCD_HEIGHT - SCOPE_MARGIN_TOP - SOFT_BUTTON_HEIGHT - 15);
constexpr uint OSC_SCOPE_WIDTH                 = VISIBLE_LCD_WIDTH;
constexpr uint XY_SCOPE_WIDTH                  = SCOPE_HEIGHT;
constexpr uint OSC_SCOPE_MARGIN_LEFT           = VISIBLE_LCD_MARGIN_LEFT;
constexpr uint XY_SCOPE_MARGIN_LEFT            = VISIBLE_LCD_MARGIN_LEFT + ((VISIBLE_LCD_WIDTH - XY_SCOPE_WIDTH) / 2);

#ifdef SPI_STATUS_MONITOR
constexpr uint SPI_STATUS_MARGIN_RIGHT   = 10;
constexpr uint SPI_STATUS_MARGIN_TOP     = 0;
constexpr uint SPI_STATUS_HEIGHT         = 80;
constexpr uint SPI_STATUS_FONT_SIZE      = 35;
#endif

//----------------------------------------------------------------------------
// MainWindow
//----------------------------------------------------------------------------
MainWindow::MainWindow(QString system_colour_str, QColor system_colour, QWidget *parent) : QMainWindow(parent)
{
    // Register the meta types
    qRegisterMetaType<LeftStatus>();
    qRegisterMetaType<LayerStatus>();
    qRegisterMetaType<MidiStatus>();
    qRegisterMetaType<TempoStatus>();
    qRegisterMetaType<HomeScreen>();
    qRegisterMetaType<ListItems>();
    qRegisterMetaType<ListSelectItem>();
    qRegisterMetaType<SoftButtons>();
    qRegisterMetaType<SoftButtonsState>();
    qRegisterMetaType<ParamUpdate>();
    qRegisterMetaType<ParamValueUpdate>();
    qRegisterMetaType<EnumParamUpdate>();
    qRegisterMetaType<EditName>();
    qRegisterMetaType<EditNameSelectChar>();
    qRegisterMetaType<EditNameChangeChar>();
    qRegisterMetaType<ConfirmationScreen>();
    qRegisterMetaType<WarningScreen>();
    qRegisterMetaType<SetSystemColour>();

    // Add the Melbourne Instruments specific fonts
    QFontDatabase::addApplicationFont(OCR_B_FONT_RES);
    QFontDatabase::addApplicationFont(DSEG7_CLASSIC_FONT_RES);

    // Set the system colour
    set_system_colour(system_colour_str, system_colour);

    // Create the GUI objects
    _create_gui_objs();

    // Resize the display for the Nina LCD screen
    resize(LCD_WIDTH, LCD_HEIGHT);

    // Set the default Scope mode to OFF
    _scope_mode = GuiScopeMode::SCOPE_MODE_OFF; 

    // Create the thread to process incoming GUI messages from the Nina UI App, and connect
    // to this thread
    _gui_thread = new GuiMsgThread(this);
    connect(_gui_thread, SIGNAL(left_status_msg(LeftStatus)), this, SLOT(set_left_status(LeftStatus)));
    connect(_gui_thread, SIGNAL(layer_status_msg(LayerStatus)), this, SLOT(set_layer_status(LayerStatus)));
    connect(_gui_thread, SIGNAL(midi_status_msg(MidiStatus)), this, SLOT(set_midi_status(MidiStatus)));
    connect(_gui_thread, SIGNAL(tempo_status_msg(TempoStatus)), this, SLOT(set_tempo_status(TempoStatus)));
    connect(_gui_thread, SIGNAL(home_screen_msg(HomeScreen)), this, SLOT(show_home_screen(HomeScreen)));
    connect(_gui_thread, SIGNAL(list_items_msg(ListItems)), this, SLOT(show_list_items(ListItems)));
    connect(_gui_thread, SIGNAL(list_select_item_msg(ListSelectItem)), this, SLOT(list_select_item(ListSelectItem)));
    connect(_gui_thread, SIGNAL(soft_buttons_msg(SoftButtons)), this, SLOT(set_soft_buttons(SoftButtons)));
    connect(_gui_thread, SIGNAL(soft_buttons_state_msg(SoftButtonsState)), this, SLOT(set_soft_buttons_state(SoftButtonsState)));
    connect(_gui_thread, SIGNAL(param_update_msg(ParamUpdate)), this, SLOT(process_param_update(ParamUpdate)));
    connect(_gui_thread, SIGNAL(param_value_update_msg(ParamValueUpdate)), this, SLOT(process_param_value_update(ParamValueUpdate)));
    connect(_gui_thread, SIGNAL(enum_param_update_msg(EnumParamUpdate)), this, SLOT(process_enum_param_update(EnumParamUpdate)));
    connect(_gui_thread, SIGNAL(enum_param_value_update_msg(ListSelectItem)), this, SLOT(process_enum_param_value_update(ListSelectItem)));
    connect(_gui_thread, SIGNAL(edit_name_msg(EditName)), this, SLOT(process_edit_name(EditName)));
    connect(_gui_thread, SIGNAL(edit_name_select_char_msg(EditNameSelectChar)), this, SLOT(process_edit_name_select_char(EditNameSelectChar)));
    connect(_gui_thread, SIGNAL(edit_name_change_char_msg(EditNameChangeChar)), this, SLOT(process_edit_name_change_char(EditNameChangeChar)));
    connect(_gui_thread, SIGNAL(confirmation_screen_msg(ConfirmationScreen)), this, SLOT(show_confirmation_screen(ConfirmationScreen)));
    connect(_gui_thread, SIGNAL(warning_screen_msg(WarningScreen)), this, SLOT(show_warning_screen(WarningScreen)));
    connect(_gui_thread, SIGNAL(clear_boot_warning_msg()), this, SLOT(clear_boot_warning()));
    connect(_gui_thread, SIGNAL(set_system_colour_msg(SetSystemColour)), this, SLOT(set_system_colour(SetSystemColour)));
    _gui_thread->start();

    // Start the samples thread
    _scope_thread = new ScopeMsgThread(_scope_data_source, this);
    _scope_thread->start();
    _conf_screen_timer = new Timer(TimerType::ONE_SHOT);

    // Create the SPI monitor thread, and connect to the thread
#ifdef SPI_STATUS_MONITOR
    _spi_thread = new SpiMonitorThread(this);
    connect(_spi_thread, SIGNAL(spi_status_msg(uint)), this, SLOT(set_spi_status(uint)));
    _spi_thread->start();
#endif
}

//----------------------------------------------------------------------------
// ~MainWindow
//----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    // Delete and stop the scope and GUI threads
    delete _scope_thread;
    delete _gui_thread;

    // Note QT handles the deletion of other allocated objects
}

//----------------------------------------------------------------------------
// set_system_colour
//----------------------------------------------------------------------------
void MainWindow::set_system_colour(QString colour_str, QColor colour)
{
    // Save the system colour
    _system_colour_str = "#" + colour_str;
    _system_colour = colour;
}

//----------------------------------------------------------------------------
// set_left_status
//----------------------------------------------------------------------------
void MainWindow::set_left_status(const LeftStatus& msg)
{
    // Update the Left status object
    _left_status_set_text(msg.status);
}

//----------------------------------------------------------------------------
// set_layer_status
//----------------------------------------------------------------------------
void MainWindow::set_layer_status(const LayerStatus& msg)
{
    // Update the Layer Status
    _layer_status->setText(msg.status);
}

//----------------------------------------------------------------------------
// set_midi_status
//----------------------------------------------------------------------------
void MainWindow::set_midi_status(const MidiStatus& msg)
{
    // Update the MIDI status
    (msg.midi_active) ?
        _midi_status->setVisible(true) :
        _midi_status->setVisible(false);
}

//----------------------------------------------------------------------------
// set_tempo_status
//----------------------------------------------------------------------------
void MainWindow::set_tempo_status(const TempoStatus& msg)
{
    // Update the Tempo Status
    _tempo_status->setText(msg.tempo_string);
}

//----------------------------------------------------------------------------
// show_home_screen
//----------------------------------------------------------------------------
void MainWindow::show_home_screen(const HomeScreen& msg)
{
    // Save the Scope mode
    _scope_mode = msg.scope_mode;

    // Set the scope geometry based on the mode
    (_scope_mode == GuiScopeMode::SCOPE_MODE_XY) ?
        _scope->setGeometry(XY_SCOPE_MARGIN_LEFT, SCOPE_MARGIN_TOP, XY_SCOPE_WIDTH, SCOPE_HEIGHT) :
        _scope->setGeometry(OSC_SCOPE_MARGIN_LEFT, SCOPE_MARGIN_TOP, OSC_SCOPE_WIDTH, SCOPE_HEIGHT);

    // Update the left status if a patch name has been specified
    // Otherwise leave the left status unchanged - this can happen if this
    // home screen message is an update, where the patch name has already
    // been set
    if (std::strlen(msg.patch_name) > 0) {
        _left_status_set_text(msg.patch_name, msg.patch_modified);
    }
    _show_default_background(true, true);
    _show_list_obj(false);
    //_show_soft_buttons(false);
    _show_param_obj(false);
    _show_enum_param_list_obj(false);
    _show_edit_name_obj(false);
    _show_warning_screen_obj(false);
}

//----------------------------------------------------------------------------
// show_list_items
//----------------------------------------------------------------------------
void MainWindow::show_list_items(const ListItems& msg)
{
    // If any list items are specified
    if (msg.num_items > 0) 
    {
        // Add the items to the list
        // Note: If the list has items, scroll to the start of the list to reset the scroll
        if (_main_area_list->count()) {
            _main_area_list->scrollToItem(_main_area_list->item(0), QAbstractItemView::PositionAtCenter);
        }
        _main_area_list->clear();
        _list_items.clear();
        _list_items_enabled.clear();
        _list_items_separator.clear();
        for (uint i=0; i<msg.num_items; i++) {
            // Special case!
            if (std::strcmp(msg.items[i], "GUI_VER") == 0) {
                char sw_ver[40];
                std::sprintf(sw_ver, "GUI: %d.%d.%d-%c%c%c%c%c%c%c", NINA_GUI_MAJOR_VERSION, NINA_GUI_MINOR_VERSION, NINA_GUI_PATCH_VERSION, 
                                                                     NINA_GUI_GIT_COMMIT_HASH[0], NINA_GUI_GIT_COMMIT_HASH[1], NINA_GUI_GIT_COMMIT_HASH[2],
                                                                     NINA_GUI_GIT_COMMIT_HASH[3], NINA_GUI_GIT_COMMIT_HASH[4], NINA_GUI_GIT_COMMIT_HASH[5],
                                                                     NINA_GUI_GIT_COMMIT_HASH[6]);                
                _list_add_item(_main_area_list, sw_ver, LIST_WIDTH-40);
            }
            else {
                if (!msg.process_enabled_state) {
                    _list_add_item(_main_area_list, msg.items[i], LIST_WIDTH-40);
                }
                else {
                    _list_add_item(_main_area_list, msg.items[i], LIST_WIDTH-40, (i == msg.selected_item), msg.list_item_enabled[i]);                    
                }
            }
        }
        if (msg.selected_item < msg.num_items) {
            _main_area_list->setCurrentRow(msg.selected_item);
        }

        // Trick to make QT scroll LOGICALLY and CONSISTENTLY (duh)
        // Note this assumes that there are 6 items shown in the list
        uint index = ((int)msg.selected_item == -1) ? 0 : msg.selected_item;
        if (index < 4)
            index = 0;
        if (index == 4)
            index = 3;
        _main_area_list->scrollToItem(_main_area_list->item(index), QAbstractItemView::PositionAtCenter);

        // Show the list
        _show_list_obj(true);
        _show_default_background(false, false);
        _show_param_obj(false);
        _show_enum_param_list_obj(false);
        _show_edit_name_obj(false);        
    }
}

//----------------------------------------------------------------------------
// list_select_item
//----------------------------------------------------------------------------
void MainWindow::list_select_item(const ListSelectItem& msg)
{
    // List - check the selected item is within range
    if (msg.selected_item < (uint)_main_area_list->count()) 
    {
        // Its within range, so select that row
        _main_area_list->setCurrentRow(msg.selected_item);
        
        // Trick to make QT scroll LOGICALLY and CONSISTENTLY (duh)
        // Note this assumes that there are 6 items shown in the list
        uint index = msg.selected_item;
        if (index < 4)
            index = 0;
        if (index == 4)
            index = 3;
        _main_area_list->scrollToItem(_main_area_list->item(index), QAbstractItemView::PositionAtCenter);

        if ((_list_items.size() > 0) && (_list_items_enabled.size() > 0)) {
            for (uint i=0; i<(uint)_main_area_list->count(); i++) {
                auto item = reinterpret_cast<QLabel *>(_main_area_list->itemWidget(_main_area_list->item(i)));
                _list_label_set_text(item, _list_items[i].c_str(), (i == msg.selected_item), _list_items_enabled[i], false);
            }
        }      
    }
}

//----------------------------------------------------------------------------
// set_soft_buttons
//----------------------------------------------------------------------------
void MainWindow::set_soft_buttons(const SoftButtons& msg)
{
    // If all soft buttons are undefined
    if ((std::strlen(msg.button1) == 0) &&
        (std::strlen(msg.button2) == 0) &&
        (std::strlen(msg.button3) == 0)) {
        // Hide the soft buttons
        _soft_button1->setVisible(false);
        _soft_button2->setVisible(false);
        _soft_button3->setVisible(false);
    }
    else {
        // Update the soft buttons text
        _set_soft_button_text(_soft_button1, msg.button1);
        _set_soft_button_text(_soft_button2, msg.button2); 
        _set_soft_button_text(_soft_button3, msg.button3);
        _soft_button1->setVisible(true);
        _soft_button2->setVisible(true);
        _soft_button3->setVisible(true);        
    }
}

//----------------------------------------------------------------------------
// set_soft_buttons_state
//----------------------------------------------------------------------------
void MainWindow::set_soft_buttons_state(const SoftButtonsState& msg)
{
    // Update the soft buttons state
    _set_soft_button_state(_soft_button1, msg.state_button1);
    _set_soft_button_state(_soft_button2, msg.state_button2);
    _set_soft_button_state(_soft_button3, msg.state_button3);
}

//----------------------------------------------------------------------------
// process_param_update
//----------------------------------------------------------------------------
void MainWindow::process_param_update(const ParamUpdate& msg)
{
    // Update the Left status object
    _left_status_set_text(msg.name);

    // Was a display string specified? If so - show this as the value
    QString str = "";
    if (std::strlen(msg.display_string) > 0) 
    {
        // Show the param value as a text string
        str = msg.display_string;
        _param_value->setFont(QFont(STANDARD_FONT_NAME, PARAM_VALUE_TXT_FONT_SIZE));
        _param_value->setText(str);              
    }
    else 
    {
        // Show the param value as a numerical value
        str = msg.value_string;
        _param_value->setFont(QFont(PARAM_VALUE_FONT_NAME, PARAM_VALUE_NUM_FONT_SIZE));
        _param_value->setText(str);
    }
    _param_value->adjustSize();

    // Set the value geometry
    uint width = _param_value->width();
    while (width > PARAM_VALUE_WIDTH) {
        str = str.mid(0, str.size() - 1);
        QString trunc_str = str + "~";
        _param_value->setText(trunc_str);
        _param_value->adjustSize();
        width = _param_value->width();
    }
    int x = (VISIBLE_LCD_WIDTH - width - PARAM_VALUE_MARGIN_LEFT);
    int y = TOP_ROW_HEIGHT + ((VISIBLE_LCD_HEIGHT - TOP_ROW_HEIGHT - SOFT_BUTTON_HEIGHT - _param_value->height()) / 2);
    _param_value->setGeometry (x, y, width, _param_value->height());

    if (std::strlen(msg.value_tag) > 0) {
        str = msg.value_tag;
        _param_value_tag->setText(msg.value_tag);
        _param_value_tag->adjustSize();
        uint width = _param_value_tag->width();
        while (width > PARAM_VALUE_WIDTH) {
            str = str.mid(0, str.size() - 1);
            QString trunc_str = str + "~";
            _param_value_tag->setText(trunc_str);
            _param_value_tag->adjustSize();
            width = _param_value_tag->width();
        }
        x = (VISIBLE_LCD_WIDTH - _param_value_tag->width() - 20);
        y += _param_value->height() + 10;
        _param_value_tag->setGeometry (x, y, _param_value_tag->width(), _param_value_tag->height());
        _param_value_tag->setVisible(true);  
    }
    else {
        _param_value_tag->setText("");
        _param_value_tag->adjustSize();
        _param_value_tag->setVisible(false); 
    }
    if ((uint)_param_value_tag->width() > width)
        width = _param_value_tag->width();

    // Add the items to the list
    // Note: If the list has items, scroll to the start of the list to reset the scroll
    if (_params_list->count()) {
        _params_list->scrollToItem(_params_list->item(0), QAbstractItemView::PositionAtCenter);
    }
    _params_list->clear();
    _list_items.clear();
    _list_items_enabled.clear();
    _list_items_separator.clear();

    for (uint i=0; i<msg.num_items; i++) {
        _label_set_text(_dummy_label, msg.list_items[i], PARAM_LIST_WIDTH-30);
        auto label = new QLabel(this);
        auto item = new QListWidgetItem(_params_list);
        label->setFont(QFont(STANDARD_FONT_NAME, LIST_FONT_SIZE));
        _list_label_set_text(label, _dummy_label->text(), (i == msg.selected_item), msg.list_item_enabled[i], msg.list_item_separator[i]);
        item->setSizeHint(QSize(PARAM_LIST_WIDTH, LIST_ROW_HEIGHT));
        _params_list->addItem(item);
        _params_list->setItemWidget(item, label);
        _list_items.push_back(_dummy_label->text().toStdString());
        _list_items_enabled.push_back(msg.list_item_enabled[i]);
        _list_items_separator.push_back(msg.list_item_separator[i]);
    }

    if (msg.selected_item < msg.num_items)
        _params_list->setCurrentRow(msg.selected_item);
    else
        _params_list->setCurrentRow(0);
    _params_list->setVisible(true);

    // Trick to make QT scroll LOGICALLY and CONSISTENTLY (duh)
    // Note this assumes that there are 6 items shown in the list
    uint index = msg.selected_item;
    if (index < 4)
        index = 0;
    if (index == 4)
        index = 3;
    _params_list->scrollToItem(_params_list->item(index), QAbstractItemView::PositionAtCenter);

    if (_enum_param_list->isVisible() || _wt_enum_param_list->isVisible()) {
        _show_enum_param_list_obj(false);
    } 
    _show_param_obj(true);
    if (_default_background->isVisible() || (_scope->display_mode() == ScopeDisplayMode::FOREGROUND)) {
        _show_default_background(false, msg.show_scope);
    }
    _show_list_obj(false);
    _show_edit_name_obj(false);

    if (msg.num_items == 0) {
        _param_value->setVisible(false);
        _set_soft_button_text(_soft_button2, "----"); 
        _set_soft_button_text(_soft_button3, "----");             
    }
    else {
        _param_value->setVisible(true);          
    }
}

//----------------------------------------------------------------------------
// process_param_value_update
//----------------------------------------------------------------------------
void MainWindow::process_param_value_update(const ParamValueUpdate& msg)
{
    // Was a display string specified? If so - show this as the value
    QString str = "";
    if (std::strlen(msg.display_string) > 0) 
    {
        // Show the param value as a text string
        str = msg.display_string;
        _param_value->setFont(QFont(STANDARD_FONT_NAME, PARAM_VALUE_TXT_FONT_SIZE));
        _param_value->setText(str);              
    }
    else 
    {
        // Show the param value as a numerical value
        str = msg.value_string;
        _param_value->setFont(QFont(PARAM_VALUE_FONT_NAME, PARAM_VALUE_NUM_FONT_SIZE));
        _param_value->setText(str);
    }
    _param_value->adjustSize();

    // Set the value geometry
    uint width = _param_value->width();
    while (width > PARAM_VALUE_WIDTH) {
        str = str.mid(0, str.size() - 1);
        QString trunc_str = str + "~";
        _param_value->setText(trunc_str);
        _param_value->adjustSize();
        width = _param_value->width();
    }
    int x = (VISIBLE_LCD_WIDTH - width - PARAM_VALUE_MARGIN_LEFT);
    int y = TOP_ROW_HEIGHT + ((VISIBLE_LCD_HEIGHT - TOP_ROW_HEIGHT - SOFT_BUTTON_HEIGHT - _param_value->height()) / 2);
    _param_value->setGeometry(x, y, width, _param_value->height());

    if (std::strlen(msg.value_tag) > 0) {
        str = msg.value_tag;
        _param_value_tag->setText(msg.value_tag);
        _param_value_tag->adjustSize();
        uint width = _param_value_tag->width();
        while (width > PARAM_VALUE_WIDTH) {
            str = str.mid(0, str.size() - 1);
            QString trunc_str = str + "~";
            _param_value_tag->setText(trunc_str);
            _param_value_tag->adjustSize();
            width = _param_value_tag->width();
        }
        x = (VISIBLE_LCD_WIDTH - _param_value_tag->width() - 20);
        y += _param_value->height() + 10;
        _param_value_tag->setGeometry (x, y, _param_value_tag->width(), _param_value_tag->height());
        _param_value_tag->setVisible(true);  
    }
    else {
        _param_value_tag->setText("");
        _param_value_tag->adjustSize();
        _param_value_tag->setVisible(false); 
    }

    if ((uint)_param_value_tag->width() > width)
        width = _param_value_tag->width();

    // Check the selected item is within range
    if ((msg.selected_item != -1) && msg.selected_item < _params_list->count()) 
    {
        // Its within range, so select that row
        _params_list->setCurrentRow(msg.selected_item);
        
        // Trick to make QT scroll LOGICALLY and CONSISTENTLY (duh)
        // Note this assumes that there are 6 items shown in the list
        uint index = msg.selected_item;
        if (index < 4)
            index = 0;
        if (index == 4)
            index = 3;
        _params_list->scrollToItem(_params_list->item(index), QAbstractItemView::PositionAtCenter);

        for (int i=0; i<_params_list->count(); i++) {
            auto item = reinterpret_cast<QLabel *>(_params_list->itemWidget(_params_list->item(i)));
            _list_label_set_text(item, _list_items[i].c_str(), (i == msg.selected_item), _list_items_enabled[i], _list_items_separator[i]);
        }
    }
}

//----------------------------------------------------------------------------
// process_enum_param_update
//----------------------------------------------------------------------------
void MainWindow::process_enum_param_update(const EnumParamUpdate& msg)
{
    // Set a pointer to the enum list object to update
    auto enum_param_list = msg.wt_list ? _wt_enum_param_list : _enum_param_list;
    auto list_width = msg.wt_list ? WT_LIST_WIDTH : LIST_WIDTH;

    // Update the Left status object
    _left_status_set_text(msg.name);

    // Add the items to the list
    // Note: If the list has items, scroll to the start of the list to reset the scroll
    if (enum_param_list->count()) {
        enum_param_list->scrollToItem(enum_param_list->item(0), QAbstractItemView::PositionAtCenter);
    }
    enum_param_list->clear();
    _enum_list_items.clear();
    for (uint i=0; i<msg.num_items; i++) {
        msg.wt_list ?
            _wt_label_set_text(_dummy_label, msg.list_items[i]) :
            _label_set_text(_dummy_label, msg.list_items[i], (list_width - 30));
        auto label = new QLabel(this);
        auto item = new QListWidgetItem(enum_param_list);
        label->setFont(QFont(STANDARD_FONT_NAME, LIST_FONT_SIZE));
        if (i == msg.selected_item)
            label->setText(_dummy_label->text());
        else
            label->setText("<span style='color: " + _system_colour_str + "'>" + _dummy_label->text() + "</span>");
        label->adjustSize();
        item->setSizeHint(QSize(list_width, LIST_ROW_HEIGHT));  
        enum_param_list->addItem(item);
        enum_param_list->setItemWidget(item, label);
        _enum_list_items.push_back(msg.list_items[i]);
    }

    if (msg.selected_item < msg.num_items)
        enum_param_list->setCurrentRow(msg.selected_item);
    else
        enum_param_list->setCurrentRow(0);
    enum_param_list->setVisible(true);

    // Trick to make QT scroll LOGICALLY and CONSISTENTLY (duh)
    // Note this assumes that there are 6 items shown in the list
    uint index = msg.selected_item;
    if (index < 4)
        index = 0;
    if (index == 4)
        index = 3;
    enum_param_list->scrollToItem(enum_param_list->item(index), QAbstractItemView::PositionAtCenter);
    _show_default_background(false, false);
    _show_list_obj(false);
    _params_list->setVisible(false);
    _param_value->setVisible(false);
    _param_value_tag->setVisible(false);

    // Are we showing a WT list?
    if (msg.wt_list) {
        // Get the WT filename
        auto wt_filename = (msg.selected_item < msg.num_items) ? 
                                _enum_list_items[msg.selected_item] :
                                _enum_list_items[0];

        // Load the WT file
        if (_wt_file.load(wt_filename)) {
            // Start the WT timer and show the WT chart
            _wt_chart_timer->start(WT_CHART_REFRESH_RATE);
        }
        else {
            // The WT file could not be loaded, so just display a line at 0.0
            _show_zero_wt_chart();
        }
        _scope->setVisible(false);
        _wt_scope->setVisible(true);
    }
    else {
        // Make sure the WT enum param list and chart is not shown
        _wt_enum_param_list->setVisible(false);
        _wt_chart_timer->stop();
        _wt_file.unload();
        _clear_wt_chart();
        QCoreApplication::processEvents();
        _wt_scope->setVisible(false);
    }
}

//----------------------------------------------------------------------------
// process_enum_param_value_update
//----------------------------------------------------------------------------
void MainWindow::process_enum_param_value_update(const ListSelectItem& msg)
{
    // Set a pointer to the enum list object to update
    auto enum_param_list = msg.wt_list ? _wt_enum_param_list : _enum_param_list;

    // Check the selected item is within range
    if (msg.selected_item < (uint)enum_param_list->count()) 
    {
        // Its within range, so select that row
        enum_param_list->setCurrentRow(msg.selected_item);
        
        // Trick to make QT scroll LOGICALLY and CONSISTENTLY (duh)
        // Note this assumes that there are 6 items shown in the list
        uint index = msg.selected_item;
        if (index < 4)
            index = 0;
        if (index == 4)
            index = 3;
        enum_param_list->scrollToItem(enum_param_list->item(index), QAbstractItemView::PositionAtCenter);

        for (uint i=0; i<(uint)enum_param_list->count(); i++) {
            auto item = reinterpret_cast<QLabel *>(enum_param_list->itemWidget(enum_param_list->item(i)));
            if (i == msg.selected_item)
                item->setText(_enum_list_items[i].c_str());
            else
                item->setText("<span style='color: " + _system_colour_str + "'>" + QString(_enum_list_items[i].c_str()) + "</span>");
        }

        // Are we showing a WT list?
        if (msg.wt_list) {
            // Stop the WT timer
            _wt_chart_timer->stop();

            // Load the WT file
            if (_wt_file.load(_enum_list_items[msg.selected_item] )) {
                // Start the WT timer and show the WT chart
                _wt_scope->setVisible(true);
                _wt_chart_timer->start(WT_CHART_REFRESH_RATE);
            }
            else {
                // The WT file could not be loaded, so just display a line at 0.0
                _show_zero_wt_chart();
            }            
        }
    }
}

//----------------------------------------------------------------------------
// process_edit_name
//----------------------------------------------------------------------------
void MainWindow::process_edit_name(const EditName& msg)
{
    // Has a selected character been specified?
    if (_selected_char == -1) 
    {
        int x_offset = ASCII_PICKER_MARGIN_LEFT;
        int width;

        // No - always select one following the last character
        _selected_char = (std::strlen(msg.name) < EDIT_NAME_STR_LEN) ? std::strlen(msg.name) : (EDIT_NAME_STR_LEN-1);

        // Set the style for each character in the name
        for (uint i=0; i<EDIT_NAME_STR_LEN; i++) 
        {
            // Highlight the selected character
            if (i == (uint)_selected_char) {
                _edit_name[i]->setStyleSheet("QLabel { background-color:  " + _system_colour_str + "; color : black; }");
                width = EDIT_NAME_SEL_CHAR_WIDTH;
            }
            else {
                _edit_name[i]->setStyleSheet("QLabel { color : " + _system_colour_str + "; }");
                width = EDIT_NAME_CHAR_WIDTH;
            }

            // Set the character geometry
            _edit_name[i]->setGeometry (x_offset, 76+(3*44), width, 44);
            x_offset += width;            
        }
    }

    // Set the name text
    for (uint i=0; i<EDIT_NAME_STR_LEN; i++) 
    {
        // Show each character in the name
        std::string s;
        s = msg.name[i];
        _edit_name[i]->setText(s.c_str());
        _edit_name[i]->setVisible(true);
    }

    // Set the ASCII picker geometry
    _set_ascii_picker_geometry(true);
    
    // Hide the other controls
    _show_default_background(false, false);
    _show_param_obj(false);
    _show_enum_param_list_obj(false);
    _show_list_obj(false);
}

//----------------------------------------------------------------------------
// process_edit_name_select_char
//----------------------------------------------------------------------------
void MainWindow::process_edit_name_select_char(const EditNameSelectChar& msg)
{
    int x_offset = ASCII_PICKER_MARGIN_LEFT;
    int width;

    // Process each character in the edit name
    _selected_char = msg.selected_char;
    for (uint i=0; i<EDIT_NAME_STR_LEN; i++) 
    {
        // Is this the selected character?
        if (i == msg.selected_char) 
        {
            // Highlight it and set the selected character width
            _edit_name[i]->setStyleSheet("QLabel { background-color:  " + _system_colour_str + "; color : black; }");
            width = ASCII_PICKER_ITEM_WIDTH;
        }
        else if (i < msg.selected_char)
        {
            // Show the character normally
            _edit_name[i]->setStyleSheet("QLabel { color : " + _system_colour_str + "; }");
            width = EDIT_NAME_CHAR_WIDTH;
        }
        else {
            // Show a dimmed character
            _edit_name[i]->setStyleSheet("QLabel { color : " + _get_dimmed_system_stylesheet_colour() + "; }");
            width = EDIT_NAME_CHAR_WIDTH;            
        }

        // Set the character geometry
        _edit_name[i]->setGeometry (x_offset, 76+(3*44), width, 44);
        x_offset += width;
    }
    
    // Set the ASCII picker geometry (this also hides it until a character is selected for editing)
    _set_ascii_picker_geometry(true);
}

//----------------------------------------------------------------------------
// process_edit_name_change_char
//----------------------------------------------------------------------------
void MainWindow::process_edit_name_change_char(const EditNameChangeChar& msg)
{
    // Get the ASCII list index to show and range check it
    // If out of range select the default character
    uint list_index = msg.change_char;
    if (list_index > (NUM_ASCII_CHARS-1))
        list_index = 1;
    
    // Hide the selected character in the name
    _edit_name[_selected_char]->setVisible(false);

    // Set the ASCII chars to show in the list
    int index = list_index - 3;
    for (uint i=0; i<ASCII_PICKER_SIZE; i++)
    {
        // If the index can be used to show a character
        if ((index >=0) && (index < (int)NUM_ASCII_CHARS))
        {
            // Set the list item character and show it
            std::string str;
            str = _ascii_chars[index];
            _ascii_picker[i]->setText(str.c_str());
            _ascii_picker[i]->setVisible(true);
        }
        else
        {
            // The index is out of range, so don't show this picker item
            _ascii_picker[i]->setVisible(false);
        }
        index++;
    }
}

//----------------------------------------------------------------------------
// show_confirmation_screen
//----------------------------------------------------------------------------
void MainWindow::show_confirmation_screen(const ConfirmationScreen& msg)
{
    // Stop the timer before restarting it
    _conf_screen_timer->stop();

    // Show the confirmation screen
    _confirmation_screen_line_1->setText(msg.line_1);
    _confirmation_screen_line_1->adjustSize();
    _confirmation_screen_line_2->setText(msg.line_2);
    _confirmation_screen_line_2->adjustSize();
    auto x = (LCD_WIDTH - _confirmation_screen_line_1->width()) / 2;
    if (x < (CONFIRMATION_SCREEN_MARGIN_LEFT + 40)) {
        x = CONFIRMATION_SCREEN_MARGIN_LEFT + 40;
    }
    auto y = CONFIRMATION_SCREEN_MARGIN_TOP + ((CONFIRMATION_SCREEN_HEIGHT - _confirmation_screen_line_1->height() - 20 -
                                               _confirmation_screen_line_2->height()) / 2);
    _confirmation_screen_line_1->setGeometry (x, y, 
                                             _confirmation_screen_line_1->width(), 
                                              _confirmation_screen_line_1->height());

    x = (LCD_WIDTH - _confirmation_screen_line_2->width()) / 2;
    if (x < (CONFIRMATION_SCREEN_MARGIN_LEFT + 40)) {
        x = CONFIRMATION_SCREEN_MARGIN_LEFT + 40;
    }    
    y += _confirmation_screen_line_1->height() + 20;
    _confirmation_screen_line_2->setGeometry (x, y, 
                                             _confirmation_screen_line_2->width(),
                                              _confirmation_screen_line_2->height()); 
    _show_confirmation_screen_obj(true);

    // Start the activity timer
    _conf_screen_timer->start(1000, std::bind(&MainWindow::_conf_screen_timer_callback, this));    
}

//----------------------------------------------------------------------------
// show_warning_screen
//----------------------------------------------------------------------------
void MainWindow::show_warning_screen(const WarningScreen& msg)
{
    if (msg.show) {
        // Show the warning screen
        _label_set_text(_warning_screen_line_1, msg.line_1, (WARNING_SCREEN_2_WIDTH - 30));
        _label_set_text(_warning_screen_line_2, msg.line_2, (WARNING_SCREEN_2_WIDTH - 30));
        auto x = (LCD_WIDTH - _warning_screen_line_1->width()) / 2;
        if (x < (WARNING_SCREEN_1_MARGIN_LEFT + 15)) {
            x = WARNING_SCREEN_1_MARGIN_LEFT + 15;
        }
        int y;
        if (msg.show_hourglass) {
            y = WARNING_SCREEN_1_MARGIN_TOP + ((WARNING_SCREEN_1_HEIGHT - _warning_screen_line_1->height() - 20 -
                                               _warning_screen_line_2->height() - 20 - _warning_screen_hourglass->height()) / 2);
        }
        else {
            y = WARNING_SCREEN_1_MARGIN_TOP + ((WARNING_SCREEN_1_HEIGHT - _warning_screen_line_1->height() - 20 -
                                               _warning_screen_line_2->height()) / 2);
        }
        _warning_screen_line_1->setGeometry (x, y, 
                                                _warning_screen_line_1->width(), 
                                                _warning_screen_line_1->height());

        x = (LCD_WIDTH - _warning_screen_line_2->width()) / 2;
        if (x < (WARNING_SCREEN_1_MARGIN_LEFT + 15)) {
            x = WARNING_SCREEN_1_MARGIN_LEFT + 15;
        }   
        y += _warning_screen_line_1->height() + 20;
        _warning_screen_line_2->setGeometry (x, y, 
                                                _warning_screen_line_2->width(),
                                                _warning_screen_line_2->height());
        if (msg.show_hourglass) {
            x = (LCD_WIDTH - _warning_screen_hourglass->width()) / 2;                                        
            y += _warning_screen_line_2->height() + 20;
            _warning_screen_hourglass->setGeometry (x, y, 
                                                    _warning_screen_hourglass->width(),
                                                    _warning_screen_hourglass->height());
            _hourglass_pixmap_index = 0;
            _hourglass_timer->start(40);
        }              
    }
    else {
        _hourglass_timer->stop();
    }
    _show_warning_screen_obj(msg.show, msg.show_hourglass);   
}

//----------------------------------------------------------------------------
// clear_boot_warning
//----------------------------------------------------------------------------
void MainWindow::clear_boot_warning()
{
    // Hide the boot warning background screen and start processing the scope
    _boot_warning_background->setVisible(false);
    _scope_data_source.start(_scope);
}

//----------------------------------------------------------------------------
// set_system_colour
//----------------------------------------------------------------------------
void MainWindow::set_system_colour(const SetSystemColour& msg)
{
    // Convert the system colour to an integer value
    QRgb colour;
    try {
        colour = std::stoi(msg.colour, nullptr, 16);
    }
    catch (...) {
        colour = std::stoi(DEFAULT_SYSTEM_COLOUR, nullptr, 16);
    }

    // Set the system colour and update the GUI objects
    set_system_colour(msg.colour, QColor(colour));
    _set_gui_objs_system_colour();
}

#ifdef SPI_STATUS_MONITOR
//----------------------------------------------------------------------------
// set_spi_status
//----------------------------------------------------------------------------
void MainWindow::set_spi_status(uint count)
{
    // Update the SPI status label
    _spi_status->setText("S" + QString::number(count));
    _spi_status->adjustSize();
    _spi_status->setGeometry ((LCD_WIDTH - _spi_status->width() - _right_status->width() - (SPI_STATUS_MARGIN_RIGHT + RIGHT_STATUS_MARGIN_RIGHT)), 
                              SPI_STATUS_MARGIN_TOP, 
                              _spi_status->width(),
                              SPI_STATUS_HEIGHT);  
}
#endif

//----------------------------------------------------------------------------
// _create_gui_objs
//----------------------------------------------------------------------------
void MainWindow::_create_gui_objs()
{
    // Set the default background to all black, no image
    _background = new Background(this);

    // Create the default background object - the NINA logo
    auto image = QPixmap(NINA_SPLASH_PNG_RES);
    _default_background = new QLabel(this);
    _default_background->setPixmap(_set_pixmap_to_system_colour(image));
    _default_background->setAlignment(Qt::AlignCenter);
    _default_background->setGeometry (0, 0, LCD_WIDTH, LCD_HEIGHT);
    _default_background->setVisible(false);

    // Create the Osc scope
    _scope = new Scope(SCOPE_NUM_SAMPLES, this);
    _scope->set_colour(_system_colour);
    _scope->setGeometry (OSC_SCOPE_MARGIN_LEFT, SCOPE_MARGIN_TOP, OSC_SCOPE_WIDTH, SCOPE_HEIGHT);
    _scope->setVisible(false);
    _scope_data_source.start(_scope);

    // Create the status bar background object
    _status_bar_background = new QLabel(this);
	_status_bar_background->setStyleSheet("QLabel { background-color: " + _system_colour_str + "; color : black; }");
    _status_bar_background->setGeometry (TOP_ROW_MARGIN_LEFT, TOP_ROW_MARGIN_TOP, TOP_ROW_WIDTH, TOP_ROW_HEIGHT);

    // Create the Left Status object
    _left_status = new QLabel(this);
	_left_status->setFont(QFont(STANDARD_FONT_NAME, LEFT_STATUS_FONT_SIZE));
	_left_status->setStyleSheet("QLabel { background-color: " + _system_colour_str + "; color : black; }"); 
    _left_status->setAlignment(Qt::AlignCenter);
    _left_status->setText("----");
    _left_status->adjustSize();
    _left_status->setGeometry (LEFT_STATUS_MARGIN_LEFT, 
                               LEFT_STATUS_MARGIN_TOP, 
                               _left_status->width(), 
                               LEFT_STATUS_HEIGHT);

    // Create the Patch Modified Status object
    _patch_modified_status = new QLabel(this);
	_patch_modified_status->setFont(QFont(STANDARD_FONT_NAME, LEFT_STATUS_FONT_SIZE));
	_patch_modified_status->setStyleSheet("QLabel { background-color: " + _system_colour_str + "; color : black; }"); 
    _patch_modified_status->setAlignment(Qt::AlignCenter);
    _patch_modified_status->setVisible(false);   

    // Create the Tempo Status object
    _tempo_status = new QLabel(this);
	_tempo_status->setFont(QFont(PARAM_VALUE_FONT_NAME, 30));
	_tempo_status->setStyleSheet("QLabel { background-color: " + _system_colour_str + "; color : black; }"); 
    _tempo_status->setAlignment(Qt::AlignCenter);
    _tempo_status->setText("000");
    _tempo_status->adjustSize();
    _tempo_status->setGeometry ((LCD_WIDTH - _tempo_status->width() - MIDI_STATUS_MARGIN_RIGHT), 
                                LEFT_STATUS_MARGIN_TOP+8, 
                                _tempo_status->width(), 
                                _tempo_status->height());

    // Create the MIDI Status object
    image = QPixmap(MIDI_STATUS_PNG_RES);
    image = image.scaled(40,40);
    _midi_status = new QLabel(this);
    _midi_status->setPixmap(image);
    _midi_status->adjustSize();
    _midi_status->setGeometry ((LCD_WIDTH - _tempo_status->width() - 10 - _midi_status->width() - MIDI_STATUS_MARGIN_RIGHT), 
                                 MIDI_STATUS_MARGIN_TOP+7, 
                                 _midi_status->width(),
                                 _midi_status->height());
    _midi_status->setVisible(false);

    // Create the Layer Status object
    _layer_status = new QLabel(this);
	_layer_status->setFont(QFont(STANDARD_FONT_NAME, LEFT_STATUS_FONT_SIZE));
	_layer_status->setStyleSheet("QLabel { background-color: " + _system_colour_str + "; color : black; }"); 
    _layer_status->setAlignment(Qt::AlignCenter);
    _layer_status->setText("L1");
    _layer_status->adjustSize();
    _layer_status->setGeometry ((LCD_WIDTH - _tempo_status->width() - 10 - _midi_status->width() - 10 - _layer_status->width() - MIDI_STATUS_MARGIN_RIGHT), 
                                LEFT_STATUS_MARGIN_TOP, 
                                _layer_status->width(), 
                                LEFT_STATUS_HEIGHT);

    // Create the Params List object
    _params_list = new QListWidget(this);
    _params_list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _params_list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _params_list->setFont(QFont(STANDARD_FONT_NAME, LIST_FONT_SIZE));
	_params_list->setStyleSheet(
        "QListWidget { background-color: transparent; color : " + _system_colour_str + "; }");
    _params_list->setVisible(false);
    _params_list->setGeometry (LIST_MARGIN_LEFT,
                               LIST_MARGIN_TOP, 
                               PARAM_LIST_WIDTH,
                               LIST_HEIGHT);
    
    // Create the Param Value object
    _param_value = new QLabel(this);
	_param_value->setFont(QFont(PARAM_VALUE_FONT_NAME, PARAM_VALUE_NUM_FONT_SIZE));
	_param_value->setStyleSheet("QLabel { color : " + _system_colour_str + "; }");

    // Create the Param Value tag object
    _param_value_tag = new QLabel(this);
	_param_value_tag->setFont(QFont(STANDARD_FONT_NAME, PARAM_VALUE_TAG_FONT_SIZE));
	_param_value_tag->setStyleSheet("QLabel { color : " + _system_colour_str + "; }");
    _param_value_tag->setVisible(false);

    // Create the Enum Param List object
    _enum_param_list = new QListWidget(this);
    _enum_param_list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _enum_param_list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _enum_param_list->setFont(QFont(STANDARD_FONT_NAME, LIST_FONT_SIZE));
	_enum_param_list->setStyleSheet(
        "QListWidget { background-color: black; color : " + _system_colour_str + "; }"
        "QListWidget::item { padding-left: 20px; padding-right: 10px; border-bottom-width: 0.5px; border-bottom-style: solid; border-bottom-color: " + _system_colour_str + "; }"
        "QListWidget::item::selected { color: black; background: " + _system_colour_str + "; }");
    _enum_param_list->setVisible(false);
    _enum_param_list->setGeometry (LIST_MARGIN_LEFT,
                                   LIST_MARGIN_TOP, 
                                   LIST_WIDTH,
                                   LIST_HEIGHT);

    // Create the WT Enum Param List object
    _wt_enum_param_list = new QListWidget(this);
    _wt_enum_param_list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _wt_enum_param_list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _wt_enum_param_list->setFont(QFont(STANDARD_FONT_NAME, LIST_FONT_SIZE));
	_wt_enum_param_list->setStyleSheet(
        "QListWidget { background-color: black; color : " + _system_colour_str + "; }"
        "QListWidget::item { padding-left: 20px; padding-right: 10px; border-bottom-width: 0.5px; border-bottom-style: solid; border-bottom-color: " + _system_colour_str + "; }"
        "QListWidget::item::selected { color: black; background: " + _system_colour_str + "; }");
    _wt_enum_param_list->setVisible(false);
    _wt_enum_param_list->setGeometry (LIST_MARGIN_LEFT,
                                      LIST_MARGIN_TOP, 
                                      WT_LIST_WIDTH,
                                      LIST_HEIGHT);

    // Create the WT scope
    _wt_scope = new Scope(WtFile::NumSamplesPerWave(), this);
    _wt_scope->set_colour(_system_colour);
    _wt_scope->setGeometry (WT_CHART_MARGIN_LEFT,
                            WT_CHART_MARGIN_TOP,
                            WT_CHART_WIDTH,
                            WT_CHART_HEIGHT);
    _wt_scope->setVisible(false);

    // Create the WT chart timer
    _wt_chart_timer = new QTimer(this);
    connect(_wt_chart_timer, &QTimer::timeout, this, &MainWindow::_update_wt_chart);

    // Create the Main Area List object
    _main_area_list = new QListWidget(this);
    _main_area_list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _main_area_list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _main_area_list->setFont(QFont(STANDARD_FONT_NAME, LIST_FONT_SIZE));
	_main_area_list->setStyleSheet(
        "QListWidget { background-color: black; color : " + _system_colour_str + "; }"
        "QListWidget::item { padding-left: 20px; padding-right: 10px; border-bottom-width: 0.5px; border-bottom-style: solid; border-bottom-color: " + _system_colour_str + "; }"
        "QListWidget::item::selected { color: black; background: " + _system_colour_str + "; }");       
    _main_area_list->setVisible(false);
    _main_area_list->setGeometry (LIST_MARGIN_LEFT,
                                  LIST_MARGIN_TOP, 
                                  LIST_WIDTH,
                                  LIST_HEIGHT);

    // Create the Soft Button objects
    _soft_button1 = new QLabel(this);
	_soft_button1->setFont(QFont(STANDARD_FONT_NAME, SOFT_BUTTON_FONT_SIZE));
    _soft_button1->setStyleSheet("QLabel { color: " + _system_colour_str + "; background-color: black; border-top: 2px solid " + _system_colour_str + "; border-right: 1px solid " + _system_colour_str + ";}");
    _soft_button1->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    _soft_button1->setText("----");
    _soft_button1->setGeometry (SOFT_BUTTONS_MARGIN_LEFT, 
                                SOFT_BUTTONS_MARGIN_TOP,
                                SOFT_BUTTON_1_WIDTH,
                                SOFT_BUTTON_HEIGHT);
    _soft_button2 = new QLabel(this);
	_soft_button2->setFont(QFont(STANDARD_FONT_NAME, SOFT_BUTTON_FONT_SIZE));
	_soft_button2->setStyleSheet("QLabel { color: " + _system_colour_str + "; background-color: black; border-top: 2px solid " + _system_colour_str + "; border-right: 1px solid " + _system_colour_str + ";}");
    _soft_button2->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    _soft_button2->setText("----");
    _soft_button2->setGeometry ((SOFT_BUTTONS_MARGIN_LEFT+SOFT_BUTTON_1_WIDTH),
                                 SOFT_BUTTONS_MARGIN_TOP,
                                 SOFT_BUTTON_2_WIDTH,
                                 SOFT_BUTTON_HEIGHT);
    _soft_button3 = new QLabel(this);
	_soft_button3->setFont(QFont(STANDARD_FONT_NAME, SOFT_BUTTON_FONT_SIZE));
	_soft_button3->setStyleSheet("QLabel { color: " + _system_colour_str + "; background-color: black; border-top: 2px solid " + _system_colour_str + ";}");
    _soft_button3->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    _soft_button3->setText("----");
    _soft_button3->setGeometry ((SOFT_BUTTONS_MARGIN_LEFT+SOFT_BUTTON_1_WIDTH+SOFT_BUTTON_2_WIDTH),
                                 SOFT_BUTTONS_MARGIN_TOP,
                                 SOFT_BUTTON_3_WIDTH,
                                 SOFT_BUTTON_HEIGHT);

    // Create the Edit Name object (array of labels)
    int x_offset = EDIT_NAME_MARGIN_LEFT;
    uint width = EDIT_NAME_SEL_CHAR_WIDTH;
    for (uint i=0; i<EDIT_NAME_STR_LEN; i++) 
    {
        // Create the character object - note the edit name is shown in the middle of the
        // ASCII picker
        _edit_name[i] = new QLabel(this);
        _edit_name[i]->setFont(QFont(STANDARD_FONT_NAME, EDIT_NAME_FONT_SIZE));
        _edit_name[i]->setGeometry (x_offset, 
                                    (ASCII_PICKER_MARGIN_TOP+(3*ASCII_PICKER_ITEM_HEIGHT)),
                                    width,
                                    EDIT_NAME_CHAR_HEIGHT);
        
        // If this is the first character
        if (i == 0) 
        {
            // Highlight the character and move to the next char
            _edit_name[i]->setStyleSheet("QLabel { background-color:  " + _system_colour_str + "; color : black; }");
            x_offset += EDIT_NAME_SEL_CHAR_WIDTH;
            width = EDIT_NAME_CHAR_WIDTH;
        }          
        else 
        {
            // Don't Highlight the character and move to the next char
            _edit_name[i]->setStyleSheet("QLabel { color : " + _system_colour_str + "; }");
            x_offset += EDIT_NAME_CHAR_WIDTH;
        }

        // Set the alignment and show the character
        _edit_name[i]->setAlignment(Qt::AlignCenter);
        _edit_name[i]->setVisible(false);
    }

    // Create an array of ASCII characters we are allowed to display when editing a name
    // Add 0-9 and A-Z only
    uint j=0;
    _ascii_chars[j++] = ' ';
    for (uint i=0; i<26; i++) {
        _ascii_chars[j++] = 'A' + i; 
    }
    for (uint i=0; i<10; i++) {
        _ascii_chars[j++] = '0' + i; 
    }
    _ascii_chars[j] = '-';

    // Create the ASCII picker object (array of labels)
    for (uint i=0; i<ASCII_PICKER_SIZE; i++) 
    {
        _ascii_picker[i] = new QLabel(this);
        _ascii_picker[i]->setFont(QFont(STANDARD_FONT_NAME, ASCII_PICKER_FONT_SIZE));
        _ascii_picker[i]->setStyleSheet("QLabel { color : " + _system_colour_str + "; }");
        _ascii_picker[i]->setGeometry (ASCII_PICKER_MARGIN_LEFT, 
                                       (ASCII_PICKER_MARGIN_TOP+(i*ASCII_PICKER_ITEM_HEIGHT)),
                                       ASCII_PICKER_ITEM_WIDTH,
                                       ASCII_PICKER_ITEM_HEIGHT);
        _ascii_picker[i]->setAlignment(Qt::AlignCenter);
        _ascii_picker[i]->setVisible(false);
    }
    _ascii_picker[3]->setStyleSheet("QLabel { background-color:  " + _system_colour_str + "; color : black; }");

    /* Create the Confirmation Screen objects */
    _warning_screen_background_1 = new QLabel(this);
	_warning_screen_background_1->setStyleSheet("QLabel { background-color: black; }");
    _warning_screen_background_1->setGeometry (WARNING_SCREEN_1_MARGIN_LEFT,
                                               WARNING_SCREEN_1_MARGIN_TOP, 
                                               WARNING_SCREEN_1_WIDTH,
                                               WARNING_SCREEN_1_HEIGHT);
    _warning_screen_background_2 = new QLabel(this);
	_warning_screen_background_2->setStyleSheet("QLabel { background-color: black; border: 10px solid " + _system_colour_str + "; }");
    _warning_screen_background_2->setGeometry (WARNING_SCREEN_2_MARGIN_LEFT,
                                               WARNING_SCREEN_2_MARGIN_TOP, 
                                               WARNING_SCREEN_2_WIDTH,
                                               WARNING_SCREEN_2_HEIGHT);                                               
    _warning_screen_line_1 = new QLabel(this);
	_warning_screen_line_1->setFont(QFont(STANDARD_FONT_NAME, 30));
	_warning_screen_line_1->setStyleSheet("QLabel { background-color: black; color : " + _system_colour_str + "; }"); 
    _warning_screen_line_1->setAlignment(Qt::AlignCenter);
    _warning_screen_line_2 = new QLabel(this);
	_warning_screen_line_2->setFont(QFont(STANDARD_FONT_NAME, 30));
	_warning_screen_line_2->setStyleSheet("QLabel { background-color: black; color : " + _system_colour_str + "; }"); 
    _warning_screen_line_2->setAlignment(Qt::AlignCenter);
    _warning_screen_background_1->setVisible(false);
    _warning_screen_background_2->setVisible(false);
    _warning_screen_line_1->setVisible(false);
    _warning_screen_line_2->setVisible(false);

    // Create the warning hourglass - firstly we need to read each pixmap
    // from the hourglass GIF
    auto *movie = new QMovie(HOURGLASS_GIF_RES);
    movie->setScaledSize(QSize(60, 60));
    for (int i=0; i<movie->frameCount(); i++) {
        movie->jumpToFrame(i);
        _hourglass_pixmaps.push_back(_set_pixmap_to_system_colour(movie->currentPixmap()));
    }

    // Create the warning hourglass label
    _warning_screen_hourglass = new QLabel(this);
    _warning_screen_hourglass->setAlignment(Qt::AlignCenter);
    _warning_screen_hourglass->setGeometry (0, 0, 60, 60);
    _warning_screen_hourglass->setVisible(false);

    // Create the warning hourglass timer
    _hourglass_timer = new QTimer(this);
    connect(_hourglass_timer, &QTimer::timeout, this, &MainWindow::_update_hourglass_image);

    /* Create the Confirmation Screen objects */
    _confirmation_screen_background = new QLabel(this);
	_confirmation_screen_background->setStyleSheet("QLabel { background-color: " + _system_colour_str + "; color : black; border: 40px solid black; }");
    _confirmation_screen_background->setGeometry (CONFIRMATION_SCREEN_MARGIN_LEFT,
                                                  CONFIRMATION_SCREEN_MARGIN_TOP, 
                                                  CONFIRMATION_SCREEN_WIDTH,
                                                  CONFIRMATION_SCREEN_HEIGHT);
    _confirmation_screen_line_1 = new QLabel(this);
	_confirmation_screen_line_1->setFont(QFont(STANDARD_FONT_NAME, 30));
	_confirmation_screen_line_1->setStyleSheet("QLabel { background-color: " + _system_colour_str + "; color : black; }"); 
    _confirmation_screen_line_1->setAlignment(Qt::AlignCenter);
    _confirmation_screen_line_2 = new QLabel(this);
	_confirmation_screen_line_2->setFont(QFont(STANDARD_FONT_NAME, 40));
	_confirmation_screen_line_2->setStyleSheet("QLabel { background-color: " + _system_colour_str + "; color : black; }"); 
    _confirmation_screen_line_2->setAlignment(Qt::AlignCenter);
    _confirmation_screen_background->setVisible(false);
    _confirmation_screen_line_1->setVisible(false);
    _confirmation_screen_line_2->setVisible(false);

    // Always show the boot warning until cleared
    image = QPixmap(BOOT_WARNING_PNG_RES);
    _boot_warning_background = new QLabel(this);
    _boot_warning_background->setPixmap(_set_pixmap_to_system_colour(image));
    _boot_warning_background->setAlignment(Qt::AlignCenter);
    _boot_warning_background->setGeometry (0, 0, LCD_WIDTH, LCD_HEIGHT);

    // Create the dummy label - not visible
    // This is used to calculate max string lengths (generally used in lists)
    _dummy_label = new QLabel(this);
	_dummy_label->setFont(QFont(STANDARD_FONT_NAME, LIST_FONT_SIZE)); 
    _dummy_label->setVisible(false);

#ifdef SPI_STATUS_MONITOR
    // Create the SPI Status item
    _spi_status = new QLabel(this);
	_spi_status->setFont(QFont(STANDARD_FONT_NAME, SPI_STATUS_FONT_SIZE));
	_spi_status->setStyleSheet("QLabel { color : " + _system_colour_str + "; }");
    _spi_status->setAlignment(Qt::AlignCenter);
    _spi_status->setText("");
    _spi_status->adjustSize();
    _spi_status->setGeometry ((LCD_WIDTH - _spi_status->width() - _right_status->width() - (SPI_STATUS_MARGIN_RIGHT + RIGHT_STATUS_MARGIN_RIGHT)), 
                              SPI_STATUS_MARGIN_TOP, 
                              _spi_status->width(),
                              SPI_STATUS_HEIGHT);
    _spi_status->setVisible(false);
#endif
}

//----------------------------------------------------------------------------
// _set_gui_objs_system_colour
//----------------------------------------------------------------------------
void MainWindow::_set_gui_objs_system_colour()
{
    // Set the system colour for all GUI objects
    // Default background object - the NINA logo
    auto image = QPixmap(NINA_SPLASH_PNG_RES);
    _default_background->setPixmap(_set_pixmap_to_system_colour(image));

    // Osc Scope
    _scope->set_colour(_system_colour);

    // Status bar background object
	_status_bar_background->setStyleSheet("QLabel { background-color: " + _system_colour_str + "; color : black; }");

    // Left Status object
	_left_status->setStyleSheet("QLabel { background-color: " + _system_colour_str + "; color : black; }"); 

    // Patch Modified Status object
	_patch_modified_status->setStyleSheet("QLabel { background-color: " + _system_colour_str + "; color : black; }");   

    // Tempo Status object
	_tempo_status->setStyleSheet("QLabel { background-color: " + _system_colour_str + "; color : black; }"); 

    // Layer Status object
	_layer_status->setStyleSheet("QLabel { background-color: " + _system_colour_str + "; color : black; }");

    // Params List object
	_params_list->setStyleSheet(
        "QListWidget { background-color: transparent; color : " + _system_colour_str + "; }");
    
    // Param Value object
	_param_value->setStyleSheet("QLabel { color : " + _system_colour_str + "; }");

    // Param Value tag object
	_param_value_tag->setStyleSheet("QLabel { color : " + _system_colour_str + "; }");

    // Enum Param List object
	_enum_param_list->setStyleSheet(
        "QListWidget { background-color: black; color : " + _system_colour_str + "; }"
        "QListWidget::item { padding-left: 20px; padding-right: 10px; border-bottom-width: 0.5px; border-bottom-style: solid; border-bottom-color: " + _system_colour_str + "; }"
        "QListWidget::item::selected { color: black; background: " + _system_colour_str + "; }");

    // WT Enum Param List object
	_wt_enum_param_list->setStyleSheet(
        "QListWidget { background-color: black; color : " + _system_colour_str + "; }"
        "QListWidget::item { padding-left: 20px; padding-right: 10px; border-bottom-width: 0.5px; border-bottom-style: solid; border-bottom-color: " + _system_colour_str + "; }"
        "QListWidget::item::selected { color: black; background: " + _system_colour_str + "; }");

    // WT Scope
    _wt_scope->set_colour(_system_colour);  

    // Main Area List object
	_main_area_list->setStyleSheet(
        "QListWidget { background-color: black; color : " + _system_colour_str + "; }"
        "QListWidget::item { padding-left: 20px; padding-right: 10px; border-bottom-width: 0.5px; border-bottom-style: solid; border-bottom-color: " + _system_colour_str + "; }"
        "QListWidget::item::selected { color: black; background: " + _system_colour_str + "; }");       

    // Soft Button objects - not assumes soft button 2 (EDIT) is selected
    _set_soft_button_state(_soft_button1, false);
    _set_soft_button_state(_soft_button2, true);
    _set_soft_button_state(_soft_button3, false);

    // Create the Edit Name object (array of labels)
    for (uint i=0; i<EDIT_NAME_STR_LEN; i++) 
    {       
        // If this is the first character
        if (i == 0) 
        {
            // Highlight the character and move to the next char
            _edit_name[i]->setStyleSheet("QLabel { background-color:  " + _system_colour_str + "; color : black; }");
        }          
        else 
        {
            // Don't Highlight the character and move to the next char
            _edit_name[i]->setStyleSheet("QLabel { color : " + _system_colour_str + "; }");
        }
    }

    // Create the ASCII picker object (array of labels)
    for (uint i=0; i<ASCII_PICKER_SIZE; i++) 
    {
        _ascii_picker[i]->setStyleSheet("QLabel { color : " + _system_colour_str + "; }");
    }
    _ascii_picker[3]->setStyleSheet("QLabel { background-color:  " + _system_colour_str + "; color : black; }");

    /* Create the Confirmation Screen objects */
	_warning_screen_background_1->setStyleSheet("QLabel { background-color: black; }");
	_warning_screen_background_2->setStyleSheet("QLabel { background-color: black; border: 10px solid " + _system_colour_str + "; }");
	_warning_screen_line_1->setStyleSheet("QLabel { background-color: black; color : " + _system_colour_str + "; }"); 
	_warning_screen_line_2->setStyleSheet("QLabel { background-color: black; color : " + _system_colour_str + "; }"); 

    // Create the warning hourglass - firstly we need to read each pixmap
    // from the hourglass GIF
    auto *movie = new QMovie(HOURGLASS_GIF_RES);
    movie->setScaledSize(QSize(60, 60));
    _hourglass_pixmaps.clear();
    for (int i=0; i<movie->frameCount(); i++) {
        movie->jumpToFrame(i);
        _hourglass_pixmaps.push_back(_set_pixmap_to_system_colour(movie->currentPixmap()));
    }

    /* Create the Confirmation Screen objects */
	_confirmation_screen_background->setStyleSheet("QLabel { background-color: " + _system_colour_str + "; color : black; border: 40px solid black; }");
	_confirmation_screen_line_1->setStyleSheet("QLabel { background-color: " + _system_colour_str + "; color : black; }"); 
	_confirmation_screen_line_2->setStyleSheet("QLabel { background-color: " + _system_colour_str + "; color : black; }");
}

//----------------------------------------------------------------------------
// _show_default_background
//----------------------------------------------------------------------------
void MainWindow::_show_default_background(bool show, bool show_scope)
{
    // If showing
    if (show) {
        // Show the Scope or default background
        if ((_scope_mode == GuiScopeMode::SCOPE_MODE_OFF) || !show_scope) {
            // No Scope, show the default background        
            _clear_scope();
            _scope->hide();
            _default_background->setVisible(true);
        }
        else {
            // Show the scope in the foreground and hide the default background
            _scope->show(ScopeDisplayMode::FOREGROUND);
            _default_background->setVisible(false);            
        }
    }
    else {
        // Show/hide the Scope
        if ((_scope_mode == GuiScopeMode::SCOPE_MODE_OFF) || !show_scope) {
            // No Scope
            _clear_scope();
            _scope->hide();                    
        }
        else {
            // Show the scope in the background
            _scope->show(ScopeDisplayMode::BACKGROUND);
        }

        // Hide the default background
        _default_background->setVisible(false); 
    }
}

//----------------------------------------------------------------------------
// _show_param_obj
//----------------------------------------------------------------------------
void MainWindow::_show_param_obj(bool show)
{
    // Show/hide the Param
    _param_value->setVisible(show);
    _param_value_tag->setVisible(show);
    _params_list->setVisible(show);
}

//----------------------------------------------------------------------------
// _show_enum_param_list_obj
//----------------------------------------------------------------------------
void MainWindow::_show_enum_param_list_obj(bool show)
{
    // Show/hide the enum Param lists
    _enum_param_list->setVisible(show);
    _wt_enum_param_list->setVisible(show);

    // If hiding, make sure the WT chart is stopped and cleared
    if (!show) {
        _wt_chart_timer->stop();
        _wt_file.unload();
        _clear_wt_chart();
        QCoreApplication::processEvents();
    }

    // Show/hide the WT chart
    _wt_scope->setVisible(show);
}

//----------------------------------------------------------------------------
// _show_list_obj
//----------------------------------------------------------------------------
void MainWindow::_show_list_obj(bool show)
{
    // Show/hide the List
    _main_area_list->setVisible(show);
}

//----------------------------------------------------------------------------
// _show_soft_buttons
//----------------------------------------------------------------------------
void MainWindow::_show_soft_buttons(bool show)
{
    _soft_button1->setVisible(show);
    _soft_button2->setVisible(show);
    _soft_button3->setVisible(show);
}

//----------------------------------------------------------------------------
// _show_edit_name_obj
//----------------------------------------------------------------------------
void MainWindow::_show_edit_name_obj(bool show)
{
    // Show/hide the Edit Name and ASCII Picker
    for (uint i=0; i<EDIT_NAME_STR_LEN; i++)
        _edit_name[i]->setVisible(show);
    for (uint i=0; i<ASCII_PICKER_SIZE; i++)
        _ascii_picker[i]->setVisible(show);
    if (!show)
        _selected_char = -1;
}

//----------------------------------------------------------------------------
// _show_confirmation_screen_obj
//----------------------------------------------------------------------------
void MainWindow::_show_confirmation_screen_obj(bool show)
{
    _confirmation_screen_background->setVisible(show);
    _confirmation_screen_line_1->setVisible(show);
    _confirmation_screen_line_2->setVisible(show);
}

//----------------------------------------------------------------------------
// _show_warning_screen_obj
//----------------------------------------------------------------------------
void MainWindow::_show_warning_screen_obj(bool show, bool show_hourglass)
{
    _warning_screen_background_1->setVisible(show);
    _warning_screen_background_2->setVisible(show);
    _warning_screen_line_1->setVisible(show);
    _warning_screen_line_2->setVisible(show);
    _warning_screen_hourglass->setVisible(show && show_hourglass);
}

//----------------------------------------------------------------------------
// _set_soft_button_text
//----------------------------------------------------------------------------
void MainWindow::_set_soft_button_text(QLabel *soft_button, const char *txt)
{
    if (std::strlen(txt) > 0)
        soft_button->setText(txt);
    else
        soft_button->setText("----");
}

//----------------------------------------------------------------------------
// _set_soft_button_state
//----------------------------------------------------------------------------
void MainWindow::_set_soft_button_state(QLabel *soft_button, int state)
{
    if (state != -1) {
        if (state) {
            if (soft_button == _soft_button1) {
	            soft_button->setStyleSheet("QLabel { color: black; background-color: " + _system_colour_str + "; border-top: 2px solid " + _system_colour_str + "; border-right: 1px solid " + _system_colour_str + ";}");
            }
            else if (soft_button == _soft_button2) {
	            soft_button->setStyleSheet("QLabel { color: black; background-color: " + _system_colour_str + "; border-top: 2px solid " + _system_colour_str + "; border-right: 1px solid " + _system_colour_str + "; border-left: 1px solid " + _system_colour_str + ";}");
            }
            else {
	            soft_button->setStyleSheet("QLabel { color: black; background-color: " + _system_colour_str + "; border-top: 2px solid " + _system_colour_str + "; border-left: 1px solid " + _system_colour_str + ";}");
            }
        }
        else {
            if (soft_button == _soft_button1) {
	            soft_button->setStyleSheet("QLabel { color: " + _system_colour_str + "; background-color: black; border-top: 2px solid " + _system_colour_str + "; border-right: 1px solid " + _system_colour_str + ";}");
            }
            else if (soft_button == _soft_button2) {
                soft_button->setStyleSheet("QLabel { color: " + _system_colour_str + "; background-color: black; border-top: 2px solid " + _system_colour_str + "; border-right: 1px solid " + _system_colour_str + "; border-left: 1px solid " + _system_colour_str + ";}");
            }
            else {
	            soft_button->setStyleSheet("QLabel { color: " + _system_colour_str + "; background-color: black; border-top: 2px solid " + _system_colour_str + ";}");
            }                            
        }       
    }
}

//----------------------------------------------------------------------------
// _set_ascii_picker_geometry
//----------------------------------------------------------------------------
void MainWindow::_set_ascii_picker_geometry(bool hide)
{
    // Set the ASCII picker geometry based on the currently selected character
    for (uint i=0; i<ASCII_PICKER_SIZE; i++)
    {
        // Set the geometry and hide the picker
        _ascii_picker[i]->setGeometry((ASCII_PICKER_MARGIN_LEFT+(_selected_char*EDIT_NAME_CHAR_WIDTH)),
                                _ascii_picker[i]->geometry().y(),
                                ASCII_PICKER_ITEM_WIDTH,
                                ASCII_PICKER_ITEM_HEIGHT);
        if (hide)
            _ascii_picker[i]->setVisible(false);
    }
}

//----------------------------------------------------------------------------
// _conf_screen_timer_callback
//----------------------------------------------------------------------------
void MainWindow::_conf_screen_timer_callback()
{
    // Hide the confirmation screen
    _show_confirmation_screen_obj(false);    
}

//----------------------------------------------------------------------------
// _left_status_set_text
//----------------------------------------------------------------------------
void MainWindow::_left_status_set_text(const char *text, bool patch_modified)
{
    auto max_width = (LCD_WIDTH - LEFT_STATUS_MARGIN_LEFT - 20 - _tempo_status->width() - 10 - _midi_status->width() - 10 - _layer_status->width() - MIDI_STATUS_MARGIN_RIGHT);

    // Has the patch been modified?
    if (patch_modified) {
        _patch_modified_status->setText("*");
        _patch_modified_status->adjustSize();
        _patch_modified_status->setVisible(true);
        max_width -= _patch_modified_status->width();
    }
    else {
        _patch_modified_status->setVisible(false); 
    }

    // Show the home screen
    _label_set_text(_left_status, text, max_width);
    _left_status->setGeometry (LEFT_STATUS_MARGIN_LEFT, 
                               LEFT_STATUS_MARGIN_TOP, 
                               _left_status->width(), 
                               LEFT_STATUS_HEIGHT);
    if (patch_modified) {
        _patch_modified_status->setGeometry (LEFT_STATUS_MARGIN_LEFT + _left_status->width(), 
                                            LEFT_STATUS_MARGIN_TOP, 
                                            _patch_modified_status->width(), 
                                            LEFT_STATUS_HEIGHT);
    }
}

//----------------------------------------------------------------------------
// _label_set_text
//----------------------------------------------------------------------------
void MainWindow::_label_set_text(QLabel *label, const char *text, int max_width)
{
    QString str = text;

    // Update the object text
    label->setText(str);
    label->adjustSize();
    if (max_width != -1) {
        uint width = label->width();
        while (width > (uint)max_width) {
            str = str.mid(0, str.size() - 1);
            QString trunc_str = str + "~";
            label->setText(trunc_str);
            label->adjustSize();
            width = label->width();
        }
    }
}

//----------------------------------------------------------------------------
// _wt_label_set_text
//----------------------------------------------------------------------------
void MainWindow::_wt_label_set_text(QLabel *label, const char *text)
{
    // Get the start and end strings to use if string truncation is needed
    QString str1 = text;
    QString str2 = text;
    str1 = str1.mid(0, (str1.size() - 3));
    str2 = str2.mid((str2.size()-3), 3);

    // Update the object text
    label->setText(text);
    label->adjustSize();
    uint width = label->width();
    while (width > (WT_LIST_WIDTH - 30)) {
        str1 = str1.mid(0, str1.size() - 1);
        QString trunc_str = str1 + "~" + str2;
        label->setText(trunc_str);
        label->adjustSize();
        width = label->width();
    }
}

//----------------------------------------------------------------------------
// _list_label_set_text
//----------------------------------------------------------------------------
void MainWindow::_list_label_set_text(QLabel *label, QString text, bool selected, bool enabled, bool separator)
{
    QString fontColour = _system_colour_str + ";";
    QString bgColour = "transparent;";
    QString paddingTop = "0px;";
    QString borderStyle = "solid;";
    QString borderWidth = "0.5px;";
    QString borderColour = _system_colour_str + ";";

    // Set the param list label text depending on the state of this list item
    if (selected) {
        if (!enabled) {
            // Show the text dimmed
            fontColour = _get_dimmed_system_stylesheet_colour();
        }
        else {
            fontColour = "black;";
        }
        bgColour = _system_colour_str + ";";
        if (separator) {
            borderColour = "black;";
        }            
    }
    else {
        if (!enabled) {
            // Show the text dimmed
            fontColour = _get_dimmed_system_stylesheet_colour();
        }               
    }
    if (separator) {
        paddingTop = "2.0px;";
        borderStyle = "dotted;";
        borderWidth = "3.0px;";
    }        
    label->setText(text);
    label->setStyleSheet(
        "QLabel { color:" + fontColour + "; background-color:" + bgColour + 
        "padding-left: 20px; padding-right: 10px; padding-top:" + paddingTop +
        "border-style:" + borderStyle + "border-bottom-width:" + borderWidth + "border-color:" + borderColour + "; }");
}

//----------------------------------------------------------------------------
// _list_add_item
//----------------------------------------------------------------------------
void MainWindow::_list_add_item(QListWidget *list, const char *text, int list_width)
{
    // Firstly find the text we can display, truncated if necessary
    // We do this with the dummy QLabel object  
    _label_set_text(_dummy_label, text, list_width);

    // Add the item to the list
    list->addItem(_dummy_label->text());
    auto item = list->item(list->count() - 1);
    item->setSizeHint(QSize(list_width, LIST_ROW_HEIGHT));   
}

//----------------------------------------------------------------------------
// _list_add_item
//----------------------------------------------------------------------------
void MainWindow::_list_add_item(QListWidget *list, const char *text, int list_width, bool selected, bool enabled)
{
    // Firstly find the text we can display, truncated if necessary
    // We do this with the dummy QLabel object  
    _label_set_text(_dummy_label, text, list_width);
    auto label = new QLabel(this);
    auto item = new QListWidgetItem(list);
    label->setFont(QFont(STANDARD_FONT_NAME, LIST_FONT_SIZE));
    _list_label_set_text(label, _dummy_label->text(), selected, enabled, false);
    item->setSizeHint(QSize(list_width, LIST_ROW_HEIGHT));
    list->addItem(item);
    list->setItemWidget(item, label);

    _list_items.push_back(_dummy_label->text().toStdString());
    _list_items_enabled.push_back(enabled);  
}

//----------------------------------------------------------------------------
// _set_pixmap_colour
//----------------------------------------------------------------------------
QPixmap MainWindow::_set_pixmap_to_system_colour(const QPixmap& pixmap)
{
    // Convert the Pixmap colour
    QColor default_colour(0xFF, 0x00, 0x00);
    QColor system_colour = _system_colour;
    QImage tmp(pixmap.toImage());
    for (int y=0; y<tmp.height(); y++) {
        for (int x=0; x<tmp.width(); x++){
            // Change the pixel colour if needed
            system_colour.setAlpha(tmp.pixelColor(x, y).alpha());
            default_colour.setAlpha(tmp.pixelColor(x, y).alpha());
            if (tmp.pixelColor(x, y) == default_colour)
                tmp.setPixelColor(x, y, system_colour);
        }
    }
    return QPixmap::fromImage(tmp);
}

//----------------------------------------------------------------------------
// _get_dimmed_system_stylesheet_colour
//----------------------------------------------------------------------------
QString MainWindow::_get_dimmed_system_stylesheet_colour()
{
    // Return the system colour dimmed (half it's intensity)
    int rgb = _system_colour.rgb();
    return QString("#%1%2%3").arg(((rgb >> 16) & 0xFF) / 2, 2, 16, QChar('0')).arg(((rgb >> 8) & 0xFF) / 2, 2, 16, QChar('0')).arg((rgb & 0xFF) / 2, 2, 16, QChar('0'));
}

//----------------------------------------------------------------------------
// _clear_scope
//----------------------------------------------------------------------------
void MainWindow::_clear_scope()
{
    QVector<QPointF> data;

    // Set all points as 0,0 - no lines will be drawn, but the OSC scope will
    // be cleared
    for (uint i=0; i<WtFile::NumSamplesPerWave(); i++) {
        data.append(QPointF(0, 0));
    }

    // Refresh the scope
    _scope->refresh_data(data);  
}

//----------------------------------------------------------------------------
// _update_wt_chart
//----------------------------------------------------------------------------
void MainWindow::_update_wt_chart()
{
    QVector<QPointF> data;

    // Get the next wave samples to display
    auto samples = _wt_file.next_wave_samples();
    if (samples.size() > 0) {
        // Add the points to the data
        for (uint i=0; i<samples.size(); i++) {
            auto x = -1.0f + ((qreal(i) / samples.size()) * 2);
            data.append(QPointF(x, samples[i]));
        }

        // Refresh the scope
        _wt_scope->refresh_data(data);
    }   
}

//----------------------------------------------------------------------------
// _show_zero_wt_chart
//----------------------------------------------------------------------------
void MainWindow::_show_zero_wt_chart()
{
    QVector<QPointF> data;

    // Add the zero points to the data
    for (uint i=0; i<WtFile::NumSamplesPerWave(); i++) {
        auto x = -1.0f + ((qreal(i) / WtFile::NumSamplesPerWave()) * 2);
        data.append(QPointF(x, 0));
    }

    // Refresh the chart
    _wt_scope->refresh_data(data);    
}

//----------------------------------------------------------------------------
// _clear_wt_chart
//----------------------------------------------------------------------------
void MainWindow::_clear_wt_chart()
{
    QVector<QPointF> data;

    // Set all points as 0,0 - no lines will be drawn, but the WT scope will
    // be cleared
    for (uint i=0; i<WtFile::NumSamplesPerWave(); i++) {
        data.append(QPointF(0, 0));
    }

    // Refresh the chart
    _wt_scope->refresh_data(data);  
}

//----------------------------------------------------------------------------
// _update_hourglass_image
//----------------------------------------------------------------------------
void MainWindow::_update_hourglass_image()
{
    // Show the next hourglass image
    _warning_screen_hourglass->setPixmap(_hourglass_pixmaps.at(_hourglass_pixmap_index++));
    if (_hourglass_pixmap_index == _hourglass_pixmaps.size()) {
        _hourglass_pixmap_index = 0;
    }
}
