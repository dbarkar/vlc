/*****************************************************************************
 * win32.cpp : Win32 interface plugin for vlc
 *****************************************************************************
 * Copyright (C) 2002 VideoLAN
 *
 * Authors: Olivier Teuli�re <ipkiss@via.ecp.fr> 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111, USA.
 *****************************************************************************/

/*****************************************************************************
 * Preamble
 *****************************************************************************/
#include <stdlib.h>                                      /* malloc(), free() */
#include <string.h>

#include <vlc/vlc.h>

#include "win32.h"                                       /* Borland specific */

/*****************************************************************************
 * Capabilities defined in the other files.
 *****************************************************************************/
void _M( intf_getfunctions ) ( function_list_t * p_function_list );

/*****************************************************************************
 * Build configuration tree.
 *****************************************************************************/

#define MAX_LINES_TEXT N_("maximum number of lines in the log window")
#define MAX_LINES_LONGTEXT N_( \
    "You can set the maximum number of lines that the log window will display."\
    " Enter -1 if you want to keep all messages." )

MODULE_CONFIG_START
ADD_CATEGORY_HINT( N_("Miscellaneous"), NULL )
    ADD_INTEGER( "intfwin-max-lines", 500, NULL, MAX_LINES_TEXT, MAX_LINES_LONGTEXT )
MODULE_CONFIG_STOP

MODULE_INIT_START
    SET_DESCRIPTION( _("Win32 interface module") )
    ADD_CAPABILITY( INTF, 100 )
    ADD_SHORTCUT( "win" )
    ADD_SHORTCUT( "win32" )
MODULE_INIT_STOP

MODULE_ACTIVATE_START
    _M( intf_getfunctions )( &p_module->p_functions->intf );
MODULE_ACTIVATE_STOP

MODULE_DEACTIVATE_START
MODULE_DEACTIVATE_STOP

