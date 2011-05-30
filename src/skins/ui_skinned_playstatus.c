/*
 * Audacious - a cross-platform multimedia player
 * Copyright (c) 2007 Tomasz Moń
 * Copyright (c) 2011 John Lindgren
 *
 * Based on:
 * BMP - Cross-platform multimedia player
 * Copyright (C) 2003-2004  BMP development team.
 * XMMS:
 * Copyright (C) 1998-2003  XMMS development team.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; under version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses>.
 *
 * The Audacious team does not consider modular code linking to
 * Audacious or using our public API to be a derived work.
 */

#include "draw-compat.h"
#include "ui_skin.h"
#include "ui_skinned_playstatus.h"

static gint playstatus_width, playstatus_height;
static PStatus playstatus_status;

DRAW_FUNC_BEGIN (playstatus_draw)
    if (! playstatus_width || ! playstatus_height)
        goto DONE;

    GdkPixbuf * p = gdk_pixbuf_new (GDK_COLORSPACE_RGB, TRUE, 8,
     playstatus_width, playstatus_height);

    if (playstatus_status == STATUS_PLAY)
        skin_draw_pixbuf (wid, aud_active_skin, p, SKIN_PLAYPAUSE, 36, 0, 0, 0,
         3, playstatus_height);
    else
        skin_draw_pixbuf (wid, aud_active_skin, p, SKIN_PLAYPAUSE, 27, 0, 0, 0,
         2, playstatus_height);

    switch (playstatus_status)
    {
    case STATUS_STOP:
        skin_draw_pixbuf (wid, aud_active_skin, p, SKIN_PLAYPAUSE, 18, 0, 2, 0,
         9, playstatus_height);
        break;
    case STATUS_PAUSE:
        skin_draw_pixbuf (wid, aud_active_skin, p, SKIN_PLAYPAUSE, 9, 0, 2, 0,
         9, playstatus_height);
        break;
    case STATUS_PLAY:
        skin_draw_pixbuf (wid, aud_active_skin, p, SKIN_PLAYPAUSE, 1, 0, 3, 0,
         8, playstatus_height);
        break;
    }

    pixbuf_draw (cr, p, 0, 0, FALSE);

    g_object_unref (p);

DONE:
DRAW_FUNC_END

GtkWidget * ui_skinned_playstatus_new (void)
{
    GtkWidget * playstatus = gtk_drawing_area_new ();
    g_signal_connect (playstatus, DRAW_SIGNAL, (GCallback) playstatus_draw, NULL);
    return playstatus;
}

void ui_skinned_playstatus_set_status (GtkWidget * playstatus, PStatus status)
{
    playstatus_status = status;
    gtk_widget_queue_draw (playstatus);
}

void ui_skinned_playstatus_set_size (GtkWidget * playstatus, gint width, gint
 height)
{
    playstatus_width = width;
    playstatus_height = height;

    gtk_widget_set_size_request (playstatus, width, height);
    gtk_widget_queue_draw (playstatus);
}
