/*
 * main_window.h
 * Copyright 2014 Michał Lipski
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions, and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions, and the following disclaimer in the documentation
 *    provided with the distribution.
 *
 * This software is provided "as is" and without any warranty, express or
 * implied. In no event shall the authors be liable for any damages arising from
 * the use of this software.
 */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QLabel>
#include <QSlider>
#include <QTimer>

#include <libaudcore/drct.h>

#include "ui_main_window.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow (QMainWindow * parent = 0);
    ~MainWindow ();

public slots:
    void timeCounterSlot ();
    void sliderValueChanged (int value);
    void sliderPressed ();
    void sliderReleased ();

private:
    QLabel * timeCounterLabel;
    QTimer * timeCounter;
    QSlider * slider;
    void setTimeCounterLabel (int time, int length);
    void enableSlider ();
    void disableSlider ();
    void enableTimeCounter ();
    void disableTimeCounter ();

    static void title_change_cb (void * unused, MainWindow * window)
    {
        window->setWindowTitle (QString ("Audacious - ") + QString (aud_drct_get_title ()));
    }

    static void playback_begin_cb (void * unused, MainWindow * window)
    {
        window->setWindowTitle ("Audacious - Buffering...");

        pause_cb (NULL, window);
    }

    static void playback_ready_cb (void * unused, MainWindow * window)
    {
        title_change_cb (NULL, window);
        pause_cb (NULL, window);

        window->enableSlider ();
        window->enableTimeCounter ();
    }

    static void pause_cb (void * unused, MainWindow * window)
    {
        QIcon icon;
        if (aud_drct_get_paused ())
            icon.addFile (QStringLiteral (":/images/playback-start.png"), QSize (), QIcon::Normal, QIcon::Off);
        else
            icon.addFile (QStringLiteral (":/images/playback-pause.png"), QSize (), QIcon::Normal, QIcon::Off);
        window->actionPlayPause->setIcon (icon);
    }

    static void playback_stop_cb (void * unused, MainWindow * window)
    {
        window->setWindowTitle ("Audacious");
        window->disableTimeCounter ();
        window->disableSlider ();

        QIcon icon;
        icon.addFile (QStringLiteral (":/images/playback-start.png"), QSize (), QIcon::Normal, QIcon::Off);
        window->actionPlayPause->setIcon (icon);
    }
};

#endif
