/*
* Status Icon Plugin for Audacious
*
* Copyright 2005-2007 Giacomo Lozito <james@develia.org>
* Copyright 2010 Michał Lipski <tallica@o2.pl>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*
*/

#ifndef STATUS_ICON_H
#define STATUS_ICON_H

enum {
    SI_CFG_SCROLL_ACTION_VOLUME,
    SI_CFG_SCROLL_ACTION_SKIP
};

/* util.c */
void si_volume_change (int value);

#endif
