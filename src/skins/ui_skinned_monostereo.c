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
#include "ui_skinned_monostereo.h"

static gint monostereo_num_channels;

DRAW_FUNC_BEGIN (monostereo_draw)
    GdkPixbuf * p = gdk_pixbuf_new (GDK_COLORSPACE_RGB, TRUE, 8, 56, 12);

    switch (monostereo_num_channels)
    {
    case -1:
    case 0:
        skin_draw_pixbuf (wid, aud_active_skin, p, SKIN_MONOSTEREO, 29, 12, 0, 0, 27, 12);
        skin_draw_pixbuf (wid, aud_active_skin, p, SKIN_MONOSTEREO, 0, 12, 27, 0, 29, 12);
        break;
    case 1:
        skin_draw_pixbuf (wid, aud_active_skin, p, SKIN_MONOSTEREO, 29, 0, 0, 0, 27, 12);
        skin_draw_pixbuf (wid, aud_active_skin, p, SKIN_MONOSTEREO, 0, 12, 27, 0, 29, 12);
        break;
    default:
        skin_draw_pixbuf (wid, aud_active_skin, p, SKIN_MONOSTEREO, 29, 12, 0, 0, 27, 12);
        skin_draw_pixbuf (wid, aud_active_skin, p, SKIN_MONOSTEREO, 0, 0, 27, 0, 29, 12);
        break;
    }

    pixbuf_draw (cr, p, 0, 0, FALSE);

    g_object_unref (p);
DRAW_FUNC_END

GtkWidget * ui_skinned_monostereo_new (void)
{
    GtkWidget * monostereo = gtk_drawing_area_new ();
    gtk_widget_set_size_request (monostereo, 56, 12);
    g_signal_connect (monostereo, DRAW_SIGNAL, (GCallback) monostereo_draw, NULL);
    return monostereo;
}

void ui_skinned_monostereo_set_num_channels (GtkWidget * monostereo, gint nch)
{
    monostereo_num_channels = nch;
    gtk_widget_queue_draw (monostereo);
}
