/*****************************************************************************
 * disc.cpp: "Open disc" dialog box.
 *****************************************************************************
 * Copyright (C) 2002 VideoLAN
 *
 * Authors: Olivier Teuliere <ipkiss@via.ecp.fr>
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

#include <vcl.h>
#pragma hdrstop

#include <vlc/vlc.h>
#include <vlc/intf.h>

#include "disc.h"
#include "win32_common.h"

//---------------------------------------------------------------------------
//#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"

extern  intf_thread_t *p_intfGlobal;

//---------------------------------------------------------------------------
__fastcall TDiscDlg::TDiscDlg( TComponent* Owner )
        : TForm( Owner )
{
    /* Simulate a click to get the correct device name */
    RadioGroupTypeClick( RadioGroupType );
}
//---------------------------------------------------------------------------
void __fastcall TDiscDlg::FormShow( TObject *Sender )
{
    p_intfGlobal->p_sys->p_window->MenuOpenDisc->Checked = true;
    p_intfGlobal->p_sys->p_window->PopupOpenDisc->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TDiscDlg::FormHide( TObject *Sender )
{
    p_intfGlobal->p_sys->p_window->MenuOpenDisc->Checked = false;
    p_intfGlobal->p_sys->p_window->PopupOpenDisc->Checked = false;
}
//---------------------------------------------------------------------------
void __fastcall TDiscDlg::BitBtnCancelClick( TObject *Sender )
{
    Hide();
}
//---------------------------------------------------------------------------
void __fastcall TDiscDlg::BitBtnOkClick( TObject *Sender )
{
    AnsiString  Device, Source, Method, Title, Chapter;
    int         i_end = p_intfGlobal->p_vlc->p_playlist->i_size;

    Hide();

    Device = EditDevice->Text;

    /* Check which method was activated */
    if( RadioGroupType->ItemIndex == 0 )
    {
        Method = "dvd";
    }
    else
    {
        Method = "vcd";
    }

    /* Select title and chapter */
    Title.sprintf( "%d", SpinEditTitle->Value );
    Chapter.sprintf( "%d", SpinEditChapter->Value );

    /* Build source name and add it to playlist */
    Source = Method + ":" + Device + "@" + Title + "," + Chapter;
    intf_PlaylistAdd( p_intfGlobal->p_vlc->p_playlist,
                      PLAYLIST_END, Source.c_str() );

    /* update the display */
    p_intfGlobal->p_sys->p_playlist->
                            UpdateGrid( p_intfGlobal->p_vlc->p_playlist );

    /* stop current item, select added item */
    if( p_intfGlobal->p_vlc->p_input_bank->pp_input[0] != NULL )
    {
        p_intfGlobal->p_vlc->p_input_bank->pp_input[0]->b_eof = 1;
    }

    intf_PlaylistJumpto( p_intfGlobal->p_vlc->p_playlist, i_end - 1 );
}
//---------------------------------------------------------------------------
void __fastcall TDiscDlg::RadioGroupTypeClick( TObject *Sender )
{
    TRadioGroup *RadioGroupType = (TRadioGroup *)Sender;
    char *psz_device;

    if( RadioGroupType->ItemIndex == 0 )
    {
        psz_device = config_GetPsz( p_intfGlobal, "dvd" );
    }
    else
    {
        psz_device = config_GetPsz( p_intfGlobal, "vcd" );
    }

    if( psz_device )
    {
        EditDevice->Text = psz_device;
        free( psz_device );
    }
}
//---------------------------------------------------------------------------

