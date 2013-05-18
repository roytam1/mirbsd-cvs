/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/nsc/gfx/gfx_disp.c,v 1.2 2003/01/14 09:34:34 alanh Exp $ */
/*
 * $Workfile: gfx_disp.c $
 *
 * This file contains routines to program the display controller.  
 *
 * The "disp_gu1.c" and "disp_gu2.c" files implement the following routines:
 *
 *    gfx_get_display_mode_count
 *    gfx_get_display_mode
 *    gfx_is_display_mode_supported
 *    gfx_get_display_details
 *    gfx_set_display_mode
 *    gfx_set_display_bpp
 *	  gfx_set_display_timings
 *    gfx_set_vtotal
 *    gfx_get_display_pitch
 *    gfx_set_display_pitch
 *    gfx_set_display_offset
 *    gfx_set_display_palette
 *    gfx_set_display_palette_entry
 *    gfx_set_cursor_enable
 *    gfx_set_cursor_colors
 *    gfx_set_cursor_position
 *	  gfx_set_cursor_shape32
 *	  gfx_set_cursor_shape64
 *    gfx_set_icon_enable
 *    gfx_set_icon_colors
 *    gfx_set_icon_position
 *    gfx_set_icon_shape64
 *    gfx_set_compression_enable
 *    gfx_set_compression_offset
 *    gfx_set_compression_pitch
 *    gfx_set_compression_size
 *    gfx_set_display_priority_high
 *    gfx_test_timing_active
 *    gfx_test_vertical_active
 *    gfx_wait_vertical_blank
 *    gfx_reset_timing_lock
 *
 * And the following routines if GFX_READ_ROUTINES is set:
 *	
 *	  gfx_get_hactive
 *    gfx_get_hblank_start
 *    gfx_get_hsync_start
 *    gfx_get_hsync_end
 *    gfx_get_hblank_end
 *    gfx_get_htotal
 *    gfx_get_vactive
 *    gfx_get_vblank_start
 *    gfx_get_vsync_start
 *    gfx_get_vsync_end
 *    gfx_get_vblank_end
 *    gfx_get_vtotal
 *    gfx_get_vline
 *    gfx_get_display_bpp
 *    gfx_get_display_offset
 *    gfx_get_display_palette
 *    gfx_get_cursor_enable
 *    gfx_get_cursor_base
 *    gfx_get_cursor_position
 *    gfx_get_cursor_offset
 *    gfx_get_cursor_color
 *    gfx_get_icon_enable
 *    gfx_get_icon_color
 *    gfx_get_icon_offset
 *    gfx_get_icon_position
 *    gfx_get_compression_enable
 *    gfx_get_compression_offset
 *    gfx_get_compression_pitch
 *    gfx_get_compression_size
 *    gfx_get_display_priority_high
 *    gfx_get_valid_bit
 *
 * NSC_LIC_ALTERNATIVE_PREAMBLE
 *
 * Revision 1.0
 *
 * National Semiconductor Alternative GPL-BSD License
 *
 * National Semiconductor Corporation licenses this software 
 * ("Software"):
 *
 *      Durango
 *
 * under one of the two following licenses, depending on how the 
 * Software is received by the Licensee.
 * 
 * If this Software is received as part of the Linux Framebuffer or
 * other GPL licensed software, then the GPL license designated 
 * NSC_LIC_GPL applies to this Software; in all other circumstances 
 * then the BSD-style license designated NSC_LIC_BSD shall apply.
 *
 * END_NSC_LIC_ALTERNATIVE_PREAMBLE */

/* NSC_LIC_BSD
 *
 * National Semiconductor Corporation Open Source License for Durango
 *
 * (BSD License with Export Notice)
 *
 * Copyright (c) 1999-2001
 * National Semiconductor Corporation.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met: 
 *
 *   * Redistributions of source code must retain the above copyright 
 *     notice, this list of conditions and the following disclaimer. 
 *
 *   * Redistributions in binary form must reproduce the above 
 *     copyright notice, this list of conditions and the following 
 *     disclaimer in the documentation and/or other materials provided 
 *     with the distribution. 
 *
 *   * Neither the name of the National Semiconductor Corporation nor 
 *     the names of its contributors may be used to endorse or promote 
 *     products derived from this software without specific prior 
 *     written permission. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
 * NATIONAL SEMICONDUCTOR CORPORATION OR CONTRIBUTORS BE LIABLE FOR ANY 
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER 
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE,
 * INTELLECTUAL PROPERTY INFRINGEMENT, OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * EXPORT LAWS: THIS LICENSE ADDS NO RESTRICTIONS TO THE EXPORT LAWS OF 
 * YOUR JURISDICTION. It is licensee's responsibility to comply with 
 * any export regulations applicable in licensee's jurisdiction. Under 
 * CURRENT (2001) U.S. export regulations this software 
 * is eligible for export from the U.S. and can be downloaded by or 
 * otherwise exported or reexported worldwide EXCEPT to U.S. embargoed 
 * destinations which include Cuba, Iraq, Libya, North Korea, Iran, 
 * Syria, Sudan, Afghanistan and any other country to which the U.S. 
 * has embargoed goods and services. 
 *
 * END_NSC_LIC_BSD */

/* NSC_LIC_GPL
 *
 * National Semiconductor Corporation Gnu General Public License for Durango
 *
 * (GPL License with Export Notice)
 *
 * Copyright (c) 1999-2001
 * National Semiconductor Corporation.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version  
 *
 * In addition to the terms of the GNU General Public License, neither 
 * the name of the National Semiconductor Corporation nor the names of 
 * its contributors may be used to endorse or promote products derived 
 * from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
 * NATIONAL SEMICONDUCTOR CORPORATION OR CONTRIBUTORS BE LIABLE FOR ANY 
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER 
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE, 
 * INTELLECTUAL PROPERTY INFRINGEMENT, OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE. See the GNU General Public License for more details. 
 *
 * EXPORT LAWS: THIS LICENSE ADDS NO RESTRICTIONS TO THE EXPORT LAWS OF 
 * YOUR JURISDICTION. It is licensee's responsibility to comply with 
 * any export regulations applicable in licensee's jurisdiction. Under 
 * CURRENT (2001) U.S. export regulations this software 
 * is eligible for export from the U.S. and can be downloaded by or 
 * otherwise exported or reexported worldwide EXCEPT to U.S. embargoed 
 * destinations which include Cuba, Iraq, Libya, North Korea, Iran, 
 * Syria, Sudan, Afghanistan and any other country to which the U.S. 
 * has embargoed goods and services. 
 *
 * You should have received a copy of the GNU General Public License 
 * along with this file; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 
 *
 * END_NSC_LIC_GPL */

unsigned short PanelWidth = 0;
unsigned short PanelHeight = 0;
unsigned short PanelEnable = 0;
unsigned short ModeWidth;
unsigned short ModeHeight;

int DeltaX = 0;
int DeltaY = 0;
unsigned long prevstartAddr = 0;
unsigned long panelTop = 0;
unsigned long panelLeft = 0;

int gbpp = 8;

int gfx_compression_enabled = 0;
int gfx_compression_active = 0;
int gfx_line_double = 0;
int gfx_pixel_double = 0;
int gfx_timing_lock = 0;
DISPLAYMODE gfx_display_mode;

/* DISPLAY MODE TIMINGS */

DISPLAYMODE DisplayParams[] = {

/* 320 x 200 */

   {GFX_MODE_70HZ |			/* refresh rate = 60  */
    GFX_MODE_8BPP | GFX_MODE_16BPP |	/* 8 and 16 BPP valid */
    GFX_MODE_NEG_HSYNC |		/* negative HSYNC     */
    GFX_MODE_PIXEL_DOUBLE |		/* Double width       */
    GFX_MODE_LINE_DOUBLE,		/* Double height      */
    0x140, 0x288, 0x290, 0x2F0, 0x318, 0x320,	/* horizontal timings */
    0x0C8, 0x197, 0x19C, 0x19E, 0x1BA, 0x1C1,	/* vertical timings   */
    0x00192CCC,				/* freq = 25.175 MHz  */
    },

/* 320 x 240 */

   {GFX_MODE_75HZ |			/* refresh rate = 75  */
    GFX_MODE_8BPP | GFX_MODE_16BPP |	/* 8 and 16 BPP valid */
    GFX_MODE_NEG_HSYNC | GFX_MODE_NEG_VSYNC |	/* negative syncs     */
    GFX_MODE_PIXEL_DOUBLE |		/* Double width       */
    GFX_MODE_LINE_DOUBLE,		/* Double height      */
    0x0140, 0x0280, 0x0290, 0x02D0, 0x0348, 0x0348,	/* horizontal timings */
    0x00F0, 0x01E0, 0x01E1, 0x01E4, 0x01F4, 0x01F4,	/* vertical timings   */
    0x001F8000,				/* freq = 31.5 MHz    */
    },

/* 400 x 300 */

   {GFX_MODE_75HZ |			/* refresh rate = 75  */
    GFX_MODE_8BPP | GFX_MODE_16BPP |	/* 8 and 16 BPP valid */
    GFX_MODE_PIXEL_DOUBLE |		/* Double width       */
    GFX_MODE_LINE_DOUBLE,		/* Double height      */
    0x0190, 0x0320, 0x0330, 0x0380, 0x0420, 0x0420,	/* horizontal timings */
    0x012C, 0x0258, 0x0259, 0x025C, 0x0271, 0x0271,	/* vertical timings   */
    0x00318000,				/* freq = 49.5 MHz    */
    },

/* 512 x 384 */

   {GFX_MODE_75HZ |			/* refresh rate = 75  */
    GFX_MODE_8BPP | GFX_MODE_16BPP |	/* 8 and 16 BPP valid */
    GFX_MODE_PIXEL_DOUBLE |		/* Double width       */
    GFX_MODE_LINE_DOUBLE,		/* Double height      */
    0x0200, 0x0400, 0x0410, 0x0470, 0x0520, 0x0520,	/* horizontal timings */
    0x0180, 0x0300, 0x0301, 0x0304, 0x0320, 0x0320,	/* vertical timings   */
    0x004EC000,				/* freq = 78.75 MHz   */
    },

/* 640 x 400 */

   {GFX_MODE_70HZ |			/* refresh rate = 60  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* all BPP valid      */
    GFX_MODE_16BPP | GFX_MODE_24BPP | GFX_MODE_NEG_HSYNC,	/* negative HSYNC     */
    0x280, 0x288, 0x290, 0x2F0, 0x318, 0x320,	/* horizontal timings */
    0x190, 0x197, 0x19C, 0x19E, 0x1BA, 0x1C1,	/* vertical timings   */
    0x00192CCC,				/* freq = 25.175 MHz  */
    },

/* 640x480 */

   {GFX_MODE_60HZ |			/* refresh rate = 60  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* all BPP valid      */
    GFX_MODE_16BPP | GFX_MODE_24BPP | GFX_MODE_NEG_HSYNC | GFX_MODE_NEG_VSYNC,	/* negative syncs     */
    0x0280, 0x0288, 0x0290, 0x02E8, 0x0318, 0x0320,	/* horizontal timings */
    0x01E0, 0x01E8, 0x01EA, 0x01EC, 0x0205, 0x020D,	/* vertical timings   */
    0x00192CCC,				/* freq = 25.175 MHz  */
    },

   {GFX_MODE_72HZ |			/* refresh rate = 72  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* all BPP valid      */
    GFX_MODE_16BPP | GFX_MODE_24BPP | GFX_MODE_NEG_HSYNC | GFX_MODE_NEG_VSYNC,	/* negative syncs     */
    0x0280, 0x0288, 0x0298, 0x02c0, 0x0338, 0x0340,	/* horizontal timings */
    0x01e0, 0x01e8, 0x01e9, 0x01ec, 0x0200, 0x0208,	/* vertical timings   */
    0x001F8000,				/* freq = 31.5 MHz    */
    },

   {GFX_MODE_75HZ |			/* refresh rate = 75  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* all BPP valid      */
    GFX_MODE_16BPP | GFX_MODE_24BPP | GFX_MODE_NEG_HSYNC | GFX_MODE_NEG_VSYNC,	/* negative syncs     */
    0x0280, 0x0280, 0x0290, 0x02D0, 0x0348, 0x0348,	/* horizontal timings */
    0x01E0, 0x01E0, 0x01E1, 0x01E4, 0x01F4, 0x01F4,	/* vertical timings   */
    0x001F8000,				/* freq = 31.5 MHz    */
    },

   {GFX_MODE_85HZ |			/* refresh rate = 85  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* all BPP valid      */
    GFX_MODE_16BPP | GFX_MODE_24BPP | GFX_MODE_NEG_HSYNC | GFX_MODE_NEG_VSYNC,	/* negative syncs     */
    0x0280, 0x0280, 0x02B8, 0x02F0, 0x0340, 0x0340,	/* horizontal timings */
    0x01E0, 0x01E0, 0x01E1, 0x01E4, 0x01FD, 0x01FD,	/* vertical timings   */
    0x00240000,				/* freq = 36.0 MHz    */
    },

/* 800x600 */

   {GFX_MODE_56HZ |			/* refresh rate = 56  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* all BPP valid      */
    GFX_MODE_16BPP | GFX_MODE_24BPP,
    0x0320, 0x0328, 0x0348, 0x03D0, 0x0418, 0x0420,	/* horizontal timings */
    0x0258, 0x0258, 0x0259, 0x025D, 0x0274, 0x0274,	/* vertical timings   */
    0x00240000,				/* freq = 36.00 MHz   */
    },

   {GFX_MODE_60HZ |			/* refresh rate = 60  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* all BPP valid      */
    GFX_MODE_16BPP | GFX_MODE_24BPP,
    0x0320, 0x0328, 0x0348, 0x03D0, 0x0418, 0x0420,	/* horizontal timings */
    0x0258, 0x0258, 0x0259, 0x025D, 0x0274, 0x0274,	/* vertical timings   */
    0x00280000,				/* freq = 40.00 MHz   */
    },

   {GFX_MODE_72HZ |			/* refresh rate = 72  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* all BPP valid      */
    GFX_MODE_16BPP | GFX_MODE_24BPP,
    0x0320, 0x0320, 0x0358, 0x03D0, 0x0410, 0x0410,	/* horizontal timings */
    0x0258, 0x0258, 0x027D, 0x0283, 0x029A, 0x029A,	/* vertical timings   */
    0x00320000,				/* freq = 49.5 MHz    */
    },

   {GFX_MODE_75HZ |			/* refresh rate = 75  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* all BPP valid      */
    GFX_MODE_16BPP | GFX_MODE_24BPP,
    0x0320, 0x0320, 0x0330, 0x0380, 0x0420, 0x0420,	/* horizontal timings */
    0x0258, 0x0258, 0x0259, 0x025C, 0x0271, 0x0271,	/* vertical timings   */
    0x00318000,				/* freq = 49.5 MHz    */
    },

   {GFX_MODE_85HZ |			/* refresh rate = 85  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* all BPP valid      */
    GFX_MODE_16BPP | GFX_MODE_24BPP,
    0x0320, 0x0320, 0x0340, 0x0380, 0x0418, 0x0418,	/* horizontal timings */
    0x0258, 0x0258, 0x0259, 0x025C, 0x0277, 0x0277,	/* vertical timings   */
    0x00384000,				/* freq = 56.25 MHz   */
    },

/* 1024x768 */

   {GFX_MODE_60HZ |			/* refresh rate = 60  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* all BPP valid      */
    GFX_MODE_16BPP | GFX_MODE_24BPP | GFX_MODE_NEG_HSYNC | GFX_MODE_NEG_VSYNC,	/* negative syncs     */
    0x0400, 0x0400, 0x0418, 0x04A0, 0x0540, 0x0540,	/* horizontal timings */
    0x0300, 0x0300, 0x0303, 0x0309, 0x0326, 0x0326,	/* vertical timings   */
    0x00410000,				/* freq = 65.00 MHz   */
    },

   {GFX_MODE_70HZ |			/* refresh rate = 70  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* all BPP valid      */
    GFX_MODE_16BPP | GFX_MODE_24BPP | GFX_MODE_NEG_HSYNC | GFX_MODE_NEG_VSYNC,	/* negative syncs     */
    0x0400, 0x0400, 0x0418, 0x04A0, 0x0530, 0x0530,	/* horizontal timings */
    0x0300, 0x0300, 0x0303, 0x0309, 0x0326, 0x0326,	/* vertical timings   */
    0x004B0000,				/* freq = 78.75 MHz   */
    },

   {GFX_MODE_75HZ |			/* refresh rate = 75  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* all BPP valid      */
    GFX_MODE_16BPP | GFX_MODE_24BPP,
    0x0400, 0x0400, 0x0410, 0x0470, 0x0520, 0x0520,	/* horizontal timings */
    0x0300, 0x0300, 0x0301, 0x0304, 0x0320, 0x0320,	/* vertical timings   */
    0x004EC000,				/* freq = 78.75 MHz   */
    },

   {GFX_MODE_85HZ |			/* refresh rate = 85  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* all BPP valid      */
    GFX_MODE_16BPP | GFX_MODE_24BPP,
    0x0400, 0x0400, 0x0430, 0x0490, 0x0560, 0x0560,	/* horizontal timings */
    0x0300, 0x0300, 0x0301, 0x0304, 0x0328, 0x0328,	/* vertical timings   */
    0x005E8000,				/* freq = 94.50 MHz   */
    },

/* 1152x864 */

   {GFX_MODE_75HZ |			/* refresh rate = 75  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* all BPP valid      */
    GFX_MODE_16BPP | GFX_MODE_24BPP,
    0x0480, 0x0480, 0x04C0, 0x0540, 0x0640, 0x0640,	/* horizontal timings */
    0x0360, 0x0360, 0x0361, 0x0364, 0x0384, 0x0384,	/* vertical timings   */
    0x006C0000,				/* freq = 108.00 MHz  */
    },

/* 1280x1024 */

   {GFX_MODE_60HZ |			/* refresh rate = 60  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* Up to 16 bpp       */
    GFX_MODE_16BPP | GFX_MODE_24BPP,
    0x0500, 0x0500, 0x0530, 0x05A0, 0x0698, 0x0698,	/* horizontal timings */
    0x0400, 0x0400, 0x0401, 0x0404, 0x042A, 0x042A,	/* vertical timings   */
    0x006C0000,				/* freq = 108.0 MHz   */
    },

   {GFX_MODE_75HZ |			/* refresh rate = 75  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* Up to 16 bpp       */
    GFX_MODE_16BPP | GFX_MODE_24BPP,
    0x0500, 0x0500, 0x0510, 0x05A0, 0x0698, 0x0698,	/* horizontal timings */
    0x0400, 0x0400, 0x0401, 0x0404, 0x042A, 0x042A,	/* vertical timings   */
    0x00870000,				/* freq = 135.0 MHz   */
    },

   {GFX_MODE_85HZ |			/* refresh rate = 85  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* Up to 16 bpp       */
    GFX_MODE_16BPP | GFX_MODE_24BPP,
    0x0500, 0x0500, 0x0540, 0x05E0, 0x06C0, 0x06C0,	/* horizontal timings */
    0x0400, 0x0400, 0x0401, 0x0404, 0x0430, 0x0430,	/* vertical timings   */
    0x009D8000,				/* freq = 157.5 MHz   */
    },

/*********************************/
/* BEGIN REDCLOUD-SPECIFIC MODES */
/*-------------------------------*/

/* 1600 x 1200 */

   {GFX_MODE_60HZ |			/* refresh rate = 60  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* Up to 32 bpp       */
    GFX_MODE_16BPP | GFX_MODE_24BPP,
    0x0640, 0x0640, 0x0680, 0x0740, 0x0870, 0x0870,	/* horizontal timings */
    0x04B0, 0x04B0, 0x04B1, 0x04B4, 0x04E2, 0x04E2,	/* vertical timings   */
    0x00A20000,				/* freq = 162.0 MHz   */
    },

   {GFX_MODE_70HZ |			/* refresh rate = 70  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* Up to 32 bpp       */
    GFX_MODE_16BPP | GFX_MODE_24BPP,
    0x0640, 0x0640, 0x0680, 0x0740, 0x0870, 0x0870,	/* horizontal timings */
    0x04B0, 0x04B0, 0x04B1, 0x04B4, 0x04E2, 0x04E2,	/* vertical timings   */
    0x00BD0000,				/* freq = 189.0 MHz   */
    },

   {GFX_MODE_75HZ |			/* refresh rate = 75  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* Up to 32 bpp       */
    GFX_MODE_16BPP | GFX_MODE_24BPP,
    0x0640, 0x0640, 0x0680, 0x0740, 0x0870, 0x0870,	/* horizontal timings */
    0x04B0, 0x04B0, 0x04B1, 0x04B4, 0x04E2, 0x04E2,	/* vertical timings   */
    0x00CA8000,				/* freq = 202.5 MHz   */
    },

   {GFX_MODE_85HZ |			/* refresh rate = 85  */
    GFX_MODE_8BPP | GFX_MODE_12BPP | GFX_MODE_15BPP |	/* Up to 32 bpp       */
    GFX_MODE_16BPP | GFX_MODE_24BPP,
    0x0640, 0x0640, 0x0680, 0x0740, 0x0870, 0x0870,	/* horizontal timings */
    0x04B0, 0x04B0, 0x04B1, 0x04B4, 0x04E2, 0x04E2,	/* vertical timings   */
    0x00E58000,				/* freq = 229.5 MHz   */
    },
};

/* UPDATE THIS VARIABLE WHENEVER NEW REDCLOUD-SPECIFIC MODES ARE ADDED */

#define REDCLOUD_SPECIFIC_MODES 4

#define NUM_RC_DISPLAY_MODES sizeof(DisplayParams) / sizeof(DISPLAYMODE)
#define NUM_GX_DISPLAY_MODES (NUM_RC_DISPLAY_MODES - REDCLOUD_SPECIFIC_MODES)

FIXEDTIMINGS FixedParams[] = {
/* 640x480 Panel */
   {640, 480, 640, 480,
    0x0280, 0x280, 0x2a8, 0x328, 0x380, 0x380,
    0x1e0, 0x1e0, 0x1e1, 0x1e5, 0x1fc, 0x1fc,
    0x00192CCC,
    },

   {640, 480, 800, 600,
    0x0280, 0x280, 0x2a8, 0x328, 0x380, 0x380,
    0x1e0, 0x1e0, 0x1e1, 0x1e5, 0x1fc, 0x1fc,
    0x00192CCC,
    },

   {640, 480, 1024, 768,
    0x0280, 0x280, 0x2a8, 0x328, 0x380, 0x380,
    0x1e0, 0x1e0, 0x1e1, 0x1e5, 0x1fc, 0x1fc,
    0x00192CCC,
    },

   {640, 480, 1152, 864,
    0x0280, 0x280, 0x2a8, 0x328, 0x380, 0x380,
    0x1e0, 0x1e0, 0x1e1, 0x1e5, 0x1fc, 0x1fc,
    0x00192CCC,
    },

   {640, 480, 1280, 1024,
    0x0280, 0x280, 0x2a8, 0x328, 0x380, 0x380,
    0x1e0, 0x1e0, 0x1e1, 0x1e5, 0x1fc, 0x1fc,
    0x00192CCC,
    },

   {640, 480, 1600, 1200,
    0x0280, 0x280, 0x2a8, 0x328, 0x380, 0x380,
    0x1e0, 0x1e0, 0x1e1, 0x1e5, 0x1fc, 0x1fc,
    0x00192CCC,
    },

/* 800x600 Panel */
   {800, 600, 640, 480,
    0x0280, 0x2d0, 0x2f8, 0x378, 0x3d0, 0x420,
    0x1e0, 0x21c, 0x21d, 0x221, 0x238, 0x274,
    0x00280000,
    },

   {800, 600, 800, 600,
    0x320, 0x320, 0x348, 0x3c8, 0x420, 0x420,
    0x258, 0x258, 0x259, 0x25d, 0x274, 0x274,
    0x00280000,
    },

   {800, 600, 1024, 768,
    0x320, 0x320, 0x348, 0x3c8, 0x420, 0x420,
    0x258, 0x258, 0x259, 0x25d, 0x274, 0x274,
    0x00280000,
    },

   {800, 600, 1152, 864,
    0x320, 0x320, 0x348, 0x3c8, 0x420, 0x420,
    0x258, 0x258, 0x259, 0x25d, 0x274, 0x274,
    0x00280000,
    },

   {800, 600, 1280, 1024,
    0x320, 0x320, 0x348, 0x3c8, 0x420, 0x420,
    0x258, 0x258, 0x259, 0x25d, 0x274, 0x274,
    0x00280000,
    },

   {800, 600, 1600, 1200,
    0x320, 0x320, 0x348, 0x3c8, 0x420, 0x420,
    0x258, 0x258, 0x259, 0x25d, 0x274, 0x274,
    0x00280000,
    },

/* 1024x768 panel */
   {1024, 768, 640, 480,
    0x0280, 0x340, 0x368, 0x3e8, 0x440, 0x500,
    0x1e0, 0x270, 0x271, 0x275, 0x28c, 0x31c,
    0x00410000,
    },

   {1024, 768, 800, 600,
    0x0320, 0x390, 0x3b8, 0x438, 0x490, 0x500,
    0x258, 0x2ac, 0x2ad, 0x2b1, 0x2c8, 0x31c,
    0x00410000,
    },

   {1024, 768, 1024, 768,
    0x0400, 0x400, 0x428, 0x4a8, 0x500, 0x500,
    0x300, 0x300, 0x301, 0x305, 0x31c, 0x31c,
    0x00410000,
    },

   {1024, 768, 1152, 864,
    0x0400, 0x400, 0x428, 0x4a8, 0x500, 0x500,
    0x300, 0x300, 0x301, 0x305, 0x31c, 0x31c,
    0x00410000,
    },

   {1024, 768, 1280, 1024,
    0x0400, 0x400, 0x428, 0x4a8, 0x500, 0x500,
    0x300, 0x300, 0x301, 0x305, 0x31c, 0x31c,
    0x00410000,
    },

   {1024, 768, 1600, 1200,
    0x0400, 0x400, 0x428, 0x4a8, 0x500, 0x500,
    0x300, 0x300, 0x301, 0x305, 0x31c, 0x31c,
    0x00410000,
    },

};

#define NUM_FIXED_TIMINGS_MODES sizeof(FixedParams)/sizeof(FIXEDTIMINGS)

/* INCLUDE SUPPORT FOR FIRST GENERATION, IF SPECIFIED. */

#if GFX_DISPLAY_GU1
#include "disp_gu1.c"
#endif

/* INCLUDE SUPPORT FOR SECOND GENERATION, IF SPECIFIED. */

#if GFX_DISPLAY_GU2
#include "disp_gu2.c"
#endif

void gfx_set_display_video_format(unsigned long format);
void gfx_set_display_video_enable(int enable);
void gfx_set_display_video_yuv_offsets(unsigned long yoffset,
				       unsigned long uoffset,
				       unsigned long voffset);
void gfx_set_display_video_yuv_pitch(unsigned long ypitch,
				     unsigned long uvpitch);
void gfx_set_display_video_downscale(unsigned short srch,
				     unsigned short dsth);
void gfx_set_display_video_vertical_downscale_enable(int enable);
void gfx_get_display_video_yuv_offsets(unsigned long *yoffset,
				       unsigned long *uoffset,
				       unsigned long *voffset);
void gfx_get_display_video_yuv_pitch(unsigned long *ypitch,
				     unsigned long *uvpitch);
unsigned long gfx_get_display_video_downscale_delta(void);
int gfx_get_display_video_downscale_enable(void);
unsigned long gfx_get_display_video_size(void);
void gfx_set_display_video_size(unsigned short width, unsigned short height);
void gfx_set_display_video_offset(unsigned long offset);
unsigned long gfx_get_display_video_offset(void);

/*---------------------------------------------------------------------------
 * gfx_reset_timing_lock
 * 
 * This routine resets the timing change lock. The lock can only be set by
 * setting a flag when calling mode set.
 *---------------------------------------------------------------------------
 */
void
gfx_reset_timing_lock(void)
{
   gfx_timing_lock = 0;
}

/* WRAPPERS IF DYNAMIC SELECTION */
/* Extra layer to call either first or second generation routines. */

#if GFX_DISPLAY_DYNAMIC

/*---------------------------------------------------------------------------
 * gfx_set_display_bpp
 *---------------------------------------------------------------------------
 */
int
gfx_set_display_bpp(unsigned short bpp)
{
   int retval = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      retval = gu1_set_display_bpp(bpp);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      retval = gu2_set_display_bpp(bpp);
#	endif
   return (retval);
}

/*---------------------------------------------------------------------------
 * gfx_is_display_mode_supported
 * check if given mode supported, 
 * return the supported mode on success, -1 on fail
 *---------------------------------------------------------------------------
 */
int
gfx_is_display_mode_supported(int xres, int yres, int bpp, int hz)
{
   int retval = -1;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      retval = gu1_is_display_mode_supported(xres, yres, bpp, hz);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      retval = gu2_is_display_mode_supported(xres, yres, bpp, hz);
#	endif
   return (retval);
}

/*---------------------------------------------------------------------------
 * gfx_set_display_mode
 *---------------------------------------------------------------------------
 */
int
gfx_set_display_mode(int xres, int yres, int bpp, int hz)
{
   int retval = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      retval = gu1_set_display_mode(xres, yres, bpp, hz);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      retval = gu2_set_display_mode(xres, yres, bpp, hz);
#	endif
   return (retval);
}

/*---------------------------------------------------------------------------
 * gfx_set_display_timings
 *---------------------------------------------------------------------------
 */
int
gfx_set_display_timings(unsigned short bpp, unsigned short flags,
			unsigned short hactive, unsigned short hblankstart,
			unsigned short hsyncstart, unsigned short hsyncend,
			unsigned short hblankend, unsigned short htotal,
			unsigned short vactive, unsigned short vblankstart,
			unsigned short vsyncstart, unsigned short vsyncend,
			unsigned short vblankend, unsigned short vtotal,
			unsigned long frequency)
{
   int retval = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      retval = gu1_set_display_timings(bpp, flags,
				       hactive, hblankstart, hsyncstart,
				       hsyncend, hblankend, htotal, vactive,
				       vblankstart, vsyncstart, vsyncend,
				       vblankend, vtotal, frequency);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      retval = gu2_set_display_timings(bpp, flags,
				       hactive, hblankstart, hsyncstart,
				       hsyncend, hblankend, htotal, vactive,
				       vblankstart, vsyncstart, vsyncend,
				       vblankend, vtotal, frequency);
#	endif
   return (retval);
}

/*---------------------------------------------------------------------------
 * gfx_set_display_pitch
 *---------------------------------------------------------------------------
 */
void
gfx_set_display_pitch(unsigned short pitch)
{
#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      gu1_set_display_pitch(pitch);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_set_display_pitch(pitch);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_set_display_offset
 *---------------------------------------------------------------------------
 */
void
gfx_set_display_offset(unsigned long offset)
{
#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      gu1_set_display_offset(offset);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_set_display_offset(offset);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_set_display_palette_entry
 *---------------------------------------------------------------------------
 */
int
gfx_set_display_palette_entry(unsigned long index, unsigned long palette)
{
   int status = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      status = gu1_set_display_palette_entry(index, palette);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      status = gu2_set_display_palette_entry(index, palette);
#	endif
   return (status);
}

/*---------------------------------------------------------------------------
 * gfx_set_display_palette
 *---------------------------------------------------------------------------
 */
int
gfx_set_display_palette(unsigned long *palette)
{
   int status = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      status = gu1_set_display_palette(palette);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      status = gu2_set_display_palette(palette);
#	endif
   return (status);
}

/*---------------------------------------------------------------------------
 * gfx_set_cursor_enable
 *---------------------------------------------------------------------------
 */
void
gfx_set_cursor_enable(int enable)
{
#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      gu1_set_cursor_enable(enable);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_set_cursor_enable(enable);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_set_cursor_colors
 *---------------------------------------------------------------------------
 */
void
gfx_set_cursor_colors(unsigned long bkcolor, unsigned long fgcolor)
{
#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      gu1_set_cursor_colors(bkcolor, fgcolor);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_set_cursor_colors(bkcolor, fgcolor);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_set_cursor_position
 *---------------------------------------------------------------------------
 */
void
gfx_set_cursor_position(unsigned long memoffset,
			unsigned short xpos, unsigned short ypos,
			unsigned short xhotspot, unsigned short yhotspot)
{
#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      gu1_set_cursor_position(memoffset, xpos, ypos, xhotspot, yhotspot);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_set_cursor_position(memoffset, xpos, ypos, xhotspot, yhotspot);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_set_cursor_shape32
 *---------------------------------------------------------------------------
 */
void
gfx_set_cursor_shape32(unsigned long memoffset,
		       unsigned long *andmask, unsigned long *xormask)
{
#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      gu1_set_cursor_shape32(memoffset, andmask, xormask);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_set_cursor_shape32(memoffset, andmask, xormask);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_set_cursor_shape64
 *---------------------------------------------------------------------------
 */
void
gfx_set_cursor_shape64(unsigned long memoffset,
		       unsigned long *andmask, unsigned long *xormask)
{
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_set_cursor_shape64(memoffset, andmask, xormask);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_set_icon_enable
 *---------------------------------------------------------------------------
 */
void
gfx_set_icon_enable(int enable)
{
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_set_icon_enable(enable);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_set_icon_colors
 *---------------------------------------------------------------------------
 */
void
gfx_set_icon_colors(unsigned long color0, unsigned long color1,
		    unsigned long color2)
{
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_set_icon_colors(color0, color1, color2);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_set_icon_position
 *---------------------------------------------------------------------------
 */
void
gfx_set_icon_position(unsigned long memoffset, unsigned short xpos)
{
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_set_icon_position(memoffset, xpos);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_set_icon_shape64
 *---------------------------------------------------------------------------
 */
void
gfx_set_icon_shape64(unsigned long memoffset,
		     unsigned long *andmask, unsigned long *xormask,
		     unsigned int lines)
{
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_set_icon_shape64(memoffset, andmask, xormask, lines);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_set_compression_enable
 *---------------------------------------------------------------------------
 */
int
gfx_set_compression_enable(int enable)
{
   int status = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      status = gu1_set_compression_enable(enable);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      status = gu2_set_compression_enable(enable);
#	endif
   return (status);
}

/*---------------------------------------------------------------------------
 * gfx_set_compression_offset
 *---------------------------------------------------------------------------
 */
int
gfx_set_compression_offset(unsigned long offset)
{
   int status = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      status = gu1_set_compression_offset(offset);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      status = gu2_set_compression_offset(offset);
#	endif
   return (status);
}

/*---------------------------------------------------------------------------
 * gfx_set_compression_pitch
 *---------------------------------------------------------------------------
 */
int
gfx_set_compression_pitch(unsigned short pitch)
{
   int status = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      status = gu1_set_compression_pitch(pitch);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      status = gu2_set_compression_pitch(pitch);
#	endif
   return (status);
}

/*---------------------------------------------------------------------------
 * gfx_set_compression_size
 *---------------------------------------------------------------------------
 */
int
gfx_set_compression_size(unsigned short size)
{
   int status = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      status = gu1_set_compression_size(size);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      status = gu2_set_compression_size(size);
#	endif
   return (status);
}

/*---------------------------------------------------------------------------
 * gfx_set_display_priority_high
 *---------------------------------------------------------------------------
 */
void
gfx_set_display_priority_high(int enable)
{
#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      gu1_set_display_priority_high(enable);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_set_display_video_format (PRIVATE ROUTINE - NOT PART OF API)
 *
 * This routine is called by "gfx_set_video_format".  It abstracts the 
 * version of the display controller from the video overlay routines.
 *---------------------------------------------------------------------------
 */
void
gfx_set_display_video_format(unsigned long format)
{
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_set_display_video_format(format);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_set_display_video_enable (PRIVATE ROUTINE - NOT PART OF API)
 *
 * This routine is called by "gfx_set_video_enable".  It abstracts the 
 * version of the display controller from the video overlay routines.
 *---------------------------------------------------------------------------
 */
void
gfx_set_display_video_enable(int enable)
{
#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      gu1_set_display_video_enable(enable);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_set_display_video_enable(enable);
#	endif
   return;
}

/*---------------------------------------------------------------------------
 * gfx_set_display_video_size (PRIVATE ROUTINE - NOT PART OF API)
 *
 * This routine is called by "gfx_set_video_size".  It abstracts the 
 * version of the display controller from the video overlay routines.
 *---------------------------------------------------------------------------
 */
void
gfx_set_display_video_size(unsigned short width, unsigned short height)
{
#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      gu1_set_display_video_size(width, height);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_set_display_video_size(width, height);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_set_display_video_offset (PRIVATE ROUTINE - NOT PART OF API)
 *
 * This routine is called by "gfx_set_video_offset".  It abstracts the 
 * version of the display controller from the video overlay routines.
 *---------------------------------------------------------------------------
 */
void
gfx_set_display_video_offset(unsigned long offset)
{
#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      gu1_set_display_video_offset(offset);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_set_display_video_offset(offset);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_set_display_video_yuv_offsets (PRIVATE ROUTINE - NOT PART OF API)
 *
 * This routine is called by "gfx_set_video_yuv_offsets".  It abstracts the 
 * version of the display controller from the video overlay routines.
 *---------------------------------------------------------------------------
 */
void
gfx_set_display_video_yuv_offsets(unsigned long yoffset,
				  unsigned long uoffset,
				  unsigned long voffset)
{
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_set_display_video_yuv_offsets(yoffset, uoffset, voffset);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_set_display_video_yuv_pitch (PRIVATE ROUTINE - NOT PART OF API)
 *
 * This routine is called by "gfx_set_video_yuv_pitch".  It abstracts the 
 * version of the display controller from the video overlay routines.
 *---------------------------------------------------------------------------
 */
void
gfx_set_display_video_yuv_pitch(unsigned long ypitch, unsigned long uvpitch)
{
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_set_display_video_yuv_pitch(ypitch, uvpitch);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_set_display_video_downscale (PRIVATE ROUTINE - NOT PART OF API)
 *
 * This routine is called by "gfx_set_video_vertical_downscale".  It abstracts the 
 * version of the display controller from the video overlay routines.
 *---------------------------------------------------------------------------
 */
void
gfx_set_display_video_downscale(unsigned short srch, unsigned short dsth)
{
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_set_display_video_downscale(srch, dsth);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_set_display_video_vertical_downscale_enable (PRIVATE ROUTINE - NOT PART OF API)
 *
 * This routine is called by "gfx_set_video_vertical_downscale_enable".  It abstracts the 
 * version of the display controller from the video overlay routines.
 *---------------------------------------------------------------------------
 */
void
gfx_set_display_video_vertical_downscale_enable(int enable)
{
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_set_display_video_vertical_downscale_enable(enable);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_test_timing_active
 *---------------------------------------------------------------------------
 */
int
gfx_test_timing_active(void)
{
   int status = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      status = gu1_test_timing_active();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      status = gu2_test_timing_active();
#	endif
   return (status);
}

/*---------------------------------------------------------------------------
 * gfx_test_vertical_active
 *---------------------------------------------------------------------------
 */
int
gfx_test_vertical_active(void)
{
   int status = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      status = gu1_test_vertical_active();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      status = gu2_test_vertical_active();
#	endif
   return (status);
}

/*---------------------------------------------------------------------------
 * gfx_wait_vertical_blank
 *---------------------------------------------------------------------------
 */
int
gfx_wait_vertical_blank(void)
{
   int status = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      status = gu1_wait_vertical_blank();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      status = gu2_wait_vertical_blank();
#	endif
   return (status);
}

/*---------------------------------------------------------------------------
 * gfx_delay_milliseconds
 *---------------------------------------------------------------------------
 */
void
gfx_delay_milliseconds(unsigned long milliseconds)
{
#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      gu1_delay_milliseconds(milliseconds);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_delay_milliseconds(milliseconds);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_delay_microseconds
 *---------------------------------------------------------------------------
 */
void
gfx_delay_microseconds(unsigned long microseconds)
{
#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      gu1_delay_microseconds(microseconds);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_delay_microseconds(microseconds);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_enable_panning 
 *
 * This routine  enables the panning when the Mode is bigger than the panel
 * size.
 *---------------------------------------------------------------------------
 */
void
gfx_enable_panning(int x, int y)
{
#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      gu1_enable_panning(x, y);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_enable_panning(x, y);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_set_fixed_timings
 *---------------------------------------------------------------------------
 */
int
gfx_set_fixed_timings(int panelResX, int panelResY, unsigned short width,
		      unsigned short height, unsigned short bpp)
{
   int status = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      status =
	    gu1_set_fixed_timings(panelResX, panelResY, width, height, bpp);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      status =
	    gu2_set_fixed_timings(panelResX, panelResY, width, height, bpp);
#	endif
   return (status);
}

/*---------------------------------------------------------------------------
 * gfx_set_panel_present
 *---------------------------------------------------------------------------
 */
int
gfx_set_panel_present(int panelResX, int panelResY, unsigned short width,
		      unsigned short height, unsigned short bpp)
{
   int status = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      status =
	    gu1_set_panel_present(panelResX, panelResY, width, height, bpp);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      status =
	    gu2_set_panel_present(panelResX, panelResY, width, height, bpp);
#	endif
   return (status);
}

/*---------------------------------------------------------------------------
 * gfx_set_vtotal
 *---------------------------------------------------------------------------
 */
int
gfx_set_vtotal(unsigned short vtotal)
{
   int retval = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      retval = gu1_set_vtotal(vtotal);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      retval = gu2_set_vtotal(vtotal);
#	endif
   return (retval);
}

/*-----------------------------------------------------------------------*
 * THE FOLLOWING READ ROUTINES ARE ALWAYS INCLUDED:                      *                      
 * gfx_get_hsync_end, gfx_get_htotal, gfx_get_vsync_end, gfx_get_vtotal  *
 * are used by the video overlay routines.                               *
 *                                                                       *
 * gfx_get_vline and gfx_vactive are used to prevent an issue for the    *
 * SC1200.                                                               *
 *                                                                       *
 * The others are part of the Durango API.                               *
 *-----------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * gfx_mode_frequency_supported
 *----------------------------------------------------------------------------  
 */
int
gfx_mode_frequency_supported(int xres, int yres, int bpp,
			     unsigned long frequency)
{
   int freq = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      freq = gu1_mode_frequency_supported(xres, yres, bpp, frequency);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      freq = gu2_mode_frequency_supported(xres, yres, bpp, frequency);
#	endif
   return (freq);
}

/*----------------------------------------------------------------------------
 * gfx_refreshrate_from_frequency
 *----------------------------------------------------------------------------  
 */
int
gfx_get_refreshrate_from_frequency(int xres, int yres, int bpp, int *hz,
				   unsigned long frequency)
{
#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      gu1_get_refreshrate_from_frequency(xres, yres, bpp, hz, frequency);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_get_refreshrate_from_frequency(xres, yres, bpp, hz, frequency);
#	endif

   return (1);
}

/*----------------------------------------------------------------------------
 * gfx_refreshrate_from_mode
 *----------------------------------------------------------------------------  
 */
int
gfx_get_refreshrate_from_mode(int xres, int yres, int bpp, int *hz,
			      unsigned long frequency)
{
#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      gu1_get_refreshrate_from_mode(xres, yres, bpp, hz, frequency);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_get_refreshrate_from_mode(xres, yres, bpp, hz, frequency);
#	endif

   return (1);
}

/*----------------------------------------------------------------------------
 * gfx_get_frequency_from_refreshrate
 *----------------------------------------------------------------------------  
 */
int
gfx_get_frequency_from_refreshrate(int xres, int yres, int bpp, int hz,
				   int *frequency)
{
   int retval = -1;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      retval =
	    gu1_get_frequency_from_refreshrate(xres, yres, bpp, hz,
					       frequency);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      retval =
	    gu2_get_frequency_from_refreshrate(xres, yres, bpp, hz,
					       frequency);
#	endif

   return retval;
}

/*---------------------------------------------------------------------------
 * gfx_get_max_supported_pixel_clock
 *---------------------------------------------------------------------------
 */
unsigned long
gfx_get_max_supported_pixel_clock(void)
{
   unsigned long status = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      status = gu1_get_max_supported_pixel_clock();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      status = gu2_get_max_supported_pixel_clock();
#	endif
   return (status);
}

/*---------------------------------------------------------------------------
 * gfx_get_display_pitch
 *---------------------------------------------------------------------------
 */
unsigned short
gfx_get_display_pitch(void)
{
   unsigned short pitch = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      pitch = gu1_get_display_pitch();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      pitch = gu2_get_display_pitch();
#	endif
   return (pitch);
}

/*---------------------------------------------------------------------------
 * gfx_get_display_mode_count 
 * return # of modes supported.
 *---------------------------------------------------------------------------
 */
int
gfx_get_display_mode_count(void)
{
   int retval = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      retval = gu1_get_display_mode_count();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      retval = gu2_get_display_mode_count();
#	endif
   return (retval);
}

/*---------------------------------------------------------------------------
 * gfx_get_frame_buffer_line_size
 *---------------------------------------------------------------------------
 */
unsigned long
gfx_get_frame_buffer_line_size(void)
{
   unsigned long retval = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      retval = gu1_get_frame_buffer_line_size();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      retval = gu2_get_frame_buffer_line_size();
#	endif
   return (retval);
}

/*---------------------------------------------------------------------------
 * gfx_get_display_mode
 * get the curent mode set, 
 * return the supported mode on success, -1 on fail
 *---------------------------------------------------------------------------
 */
int
gfx_get_display_mode(int *xres, int *yres, int *bpp, int *hz)
{
   int retval = -1;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      retval = gu1_get_display_mode(xres, yres, bpp, hz);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      retval = gu2_get_display_mode(xres, yres, bpp, hz);
#	endif
   return (retval);
}

/*---------------------------------------------------------------------------
 * gfx_get_display_details
 * given the mode get's the resoultion details, width, height, freq
 *---------------------------------------------------------------------------
 */
int
gfx_get_display_details(unsigned int mode, int *xres, int *yres, int *hz)
{
   int retval = -1;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      retval = gu1_get_display_details(mode, xres, yres, hz);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      retval = gu2_get_display_details(mode, xres, yres, hz);
#	endif
   return (retval);
}

/*---------------------------------------------------------------------------
 * gfx_get_hactive
 *---------------------------------------------------------------------------
 */
unsigned short
gfx_get_hactive(void)
{
   unsigned short hactive = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      hactive = gu1_get_hactive();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      hactive = gu2_get_hactive();
#	endif
   return (hactive);
}

/*---------------------------------------------------------------------------
 * gfx_get_hsync_start
 *---------------------------------------------------------------------------
 */
unsigned short
gfx_get_hsync_start(void)
{
   unsigned short hsync_start = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      hsync_start = gu1_get_hsync_start();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      hsync_start = gu2_get_hsync_start();
#	endif
   return (hsync_start);
}

/*---------------------------------------------------------------------------
 * gfx_get_hsync_end
 *---------------------------------------------------------------------------
 */
unsigned short
gfx_get_hsync_end(void)
{
   unsigned short hsync_end = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      hsync_end = gu1_get_hsync_end();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      hsync_end = gu2_get_hsync_end();
#	endif
   return (hsync_end);
}

/*---------------------------------------------------------------------------
 * gfx_get_htotal
 *---------------------------------------------------------------------------
 */
unsigned short
gfx_get_htotal(void)
{
   unsigned short htotal = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      htotal = gu1_get_htotal();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      htotal = gu2_get_htotal();
#	endif
   return (htotal);
}

/*---------------------------------------------------------------------------
 * gfx_get_vactive
 *---------------------------------------------------------------------------
 */
unsigned short
gfx_get_vactive(void)
{
   unsigned short vactive = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      vactive = gu1_get_vactive();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      vactive = gu2_get_vactive();
#	endif
   return (vactive);
}

/*---------------------------------------------------------------------------
 * gfx_get_vsync_end
 *---------------------------------------------------------------------------
 */
unsigned short
gfx_get_vsync_end(void)
{
   unsigned short vsync_end = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      vsync_end = gu1_get_vsync_end();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      vsync_end = gu2_get_vsync_end();
#	endif
   return (vsync_end);
}

/*---------------------------------------------------------------------------
 * gfx_get_vtotal
 *---------------------------------------------------------------------------
 */
unsigned short
gfx_get_vtotal(void)
{
   unsigned short vtotal = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      vtotal = gu1_get_vtotal();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      vtotal = gu2_get_vtotal();
#	endif
   return (vtotal);
}

/*---------------------------------------------------------------------------
 *  gfx_get_display_bpp
 *---------------------------------------------------------------------------
 */
unsigned short
gfx_get_display_bpp(void)
{
   unsigned short bpp = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      bpp = gu1_get_display_bpp();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      bpp = gu2_get_display_bpp();
#	endif
   return (bpp);
}

/*---------------------------------------------------------------------------
 * gfx_get_vline
 *---------------------------------------------------------------------------
 */
unsigned short
gfx_get_vline(void)
{
   unsigned short vline = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      vline = gu1_get_vline();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      vline = gu2_get_vline();
#	endif
   return (vline);
}

/*---------------------------------------------------------------------------
 *  gfx_get_display_offset
 *---------------------------------------------------------------------------
 */
unsigned long
gfx_get_display_offset(void)
{
   unsigned long offset = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      offset = gu1_get_display_offset();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      offset = gu2_get_display_offset();
#	endif
   return (offset);
}

/*---------------------------------------------------------------------------
 *  gfx_get_cursor_offset
 *---------------------------------------------------------------------------
 */
unsigned long
gfx_get_cursor_offset(void)
{
   unsigned long base = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      base = gu1_get_cursor_offset();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      base = gu2_get_cursor_offset();
#	endif
   return (base);
}

/*************************************************************/
/*  READ ROUTINES  |  INCLUDED FOR DIAGNOSTIC PURPOSES ONLY  */
/*************************************************************/

#if GFX_READ_ROUTINES

/*---------------------------------------------------------------------------
 * gfx_get_hblank_start
 *---------------------------------------------------------------------------
 */
unsigned short
gfx_get_hblank_start(void)
{
   unsigned short hblank_start = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      hblank_start = gu1_get_hblank_start();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      hblank_start = gu2_get_hblank_start();
#	endif
   return (hblank_start);
}

/*---------------------------------------------------------------------------
 * gfx_get_hblank_end
 *---------------------------------------------------------------------------
 */
unsigned short
gfx_get_hblank_end(void)
{
   unsigned short hblank_end = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      hblank_end = gu1_get_hblank_end();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      hblank_end = gu2_get_hblank_end();
#	endif
   return (hblank_end);
}

/*---------------------------------------------------------------------------
 * gfx_get_vblank_start
 *---------------------------------------------------------------------------
 */
unsigned short
gfx_get_vblank_start(void)
{
   unsigned short vblank_start = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      vblank_start = gu1_get_vblank_start();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      vblank_start = gu2_get_vblank_start();
#	endif
   return (vblank_start);
}

/*---------------------------------------------------------------------------
 * gfx_get_vsync_start
 *---------------------------------------------------------------------------
 */
unsigned short
gfx_get_vsync_start(void)
{
   unsigned short vsync_start = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      vsync_start = gu1_get_vsync_start();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      vsync_start = gu2_get_vsync_start();
#	endif
   return (vsync_start);
}

/*---------------------------------------------------------------------------
 * gfx_get_vblank_end
 *---------------------------------------------------------------------------
 */
unsigned short
gfx_get_vblank_end(void)
{
   unsigned short vblank_end = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      vblank_end = gu1_get_vblank_end();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      vblank_end = gu2_get_vblank_end();
#	endif
   return (vblank_end);
}

/*---------------------------------------------------------------------------
 *  gfx_get_display_palette_entry
 *---------------------------------------------------------------------------
 */
int
gfx_get_display_palette_entry(unsigned long index, unsigned long *palette)
{
   int status = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      status = gu1_get_display_palette_entry(index, palette);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      status = gu2_get_display_palette_entry(index, palette);
#	endif

   return status;
}

/*---------------------------------------------------------------------------
 *  gfx_get_display_palette
 *---------------------------------------------------------------------------
 */
void
gfx_get_display_palette(unsigned long *palette)
{
#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      gu1_get_display_palette(palette);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_get_display_palette(palette);
#	endif
}

/*---------------------------------------------------------------------------
 *  gfx_get_cursor_enable
 *---------------------------------------------------------------------------
 */
unsigned long
gfx_get_cursor_enable(void)
{
   unsigned long enable = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      enable = gu1_get_cursor_enable();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      enable = gu2_get_cursor_enable();
#	endif
   return (enable);
}

/*---------------------------------------------------------------------------
 *  gfx_get_cursor_position
 *---------------------------------------------------------------------------
 */
unsigned long
gfx_get_cursor_position(void)
{
   unsigned long position = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      position = gu1_get_cursor_position();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      position = gu2_get_cursor_position();
#	endif
   return (position);
}

/*---------------------------------------------------------------------------
 *  gfx_get_cursor_clip
 *---------------------------------------------------------------------------
 */
unsigned long
gfx_get_cursor_clip(void)
{
   unsigned long offset = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      offset = gu1_get_cursor_clip();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      offset = gu2_get_cursor_clip();
#	endif
   return (offset);
}

/*---------------------------------------------------------------------------
 *  gfx_get_cursor_color
 *---------------------------------------------------------------------------
 */
unsigned long
gfx_get_cursor_color(int index)
{
   unsigned long color = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      color = gu1_get_cursor_color(index);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      color = gu2_get_cursor_color(index);
#	endif
   return (color);
}

/*---------------------------------------------------------------------------
 *  gfx_get_icon_enable
 *---------------------------------------------------------------------------
 */
unsigned long
gfx_get_icon_enable(void)
{
   unsigned long enable = 0;

#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      enable = gu2_get_icon_enable();
#	endif
   return (enable);
}

/*---------------------------------------------------------------------------
 *  gfx_get_icon_offset
 *---------------------------------------------------------------------------
 */
unsigned long
gfx_get_icon_offset(void)
{
   unsigned long base = 0;

#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      base = gu2_get_icon_offset();
#	endif

   return (base);
}

/*---------------------------------------------------------------------------
 *  gfx_get_icon_position
 *---------------------------------------------------------------------------
 */
unsigned long
gfx_get_icon_position(void)
{
   unsigned long position = 0;

#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      position = gu2_get_icon_position();
#	endif

   return (position);
}

/*---------------------------------------------------------------------------
 *  gfx_get_icon_color
 *---------------------------------------------------------------------------
 */
unsigned long
gfx_get_icon_color(int index)
{
   unsigned long color = 0;

#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      color = gu2_get_icon_color(index);
#	endif

   return (color);
}

/*---------------------------------------------------------------------------
 *  gfx_get_compression_enable
 *---------------------------------------------------------------------------
 */
int
gfx_get_compression_enable(void)
{
   int enable = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      enable = gu1_get_compression_enable();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      enable = gu2_get_compression_enable();
#	endif
   return (enable);
}

/*---------------------------------------------------------------------------
 *  gfx_get_compression_offset
 *---------------------------------------------------------------------------
 */
unsigned long
gfx_get_compression_offset(void)
{
   unsigned long offset = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      offset = gu1_get_compression_offset();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      offset = gu2_get_compression_offset();
#	endif
   return (offset);
}

/*---------------------------------------------------------------------------
 * gfx_get_compression_pitch
 *---------------------------------------------------------------------------
 */
unsigned short
gfx_get_compression_pitch(void)
{
   unsigned short pitch = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      pitch = gu1_get_compression_pitch();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      pitch = gu2_get_compression_pitch();
#	endif
   return (pitch);
}

/*---------------------------------------------------------------------------
 * gfx_get_compression_size
 *---------------------------------------------------------------------------
 */
unsigned short
gfx_get_compression_size(void)
{
   unsigned short size = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      size = gu1_get_compression_size();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      size = gu2_get_compression_size();
#	endif
   return (size);
}

/*---------------------------------------------------------------------------
 * gfx_get_display_priority_high
 *---------------------------------------------------------------------------
 */
int
gfx_get_display_priority_high(void)
{
   int high = GFX_STATUS_UNSUPPORTED;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      high = gu1_get_display_priority_high();
#	endif
   return (high);
}

/*---------------------------------------------------------------------------
 * gfx_get_valid_bit
 *---------------------------------------------------------------------------
 */
int
gfx_get_valid_bit(int line)
{
   int valid = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      valid = gu1_get_valid_bit(line);
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      valid = gu2_get_valid_bit(line);
#	endif
   return (valid);
}

/*---------------------------------------------------------------------------
 * gfx_get_display_video_offset
 *---------------------------------------------------------------------------
 */
unsigned long
gfx_get_display_video_offset(void)
{
   unsigned long offset = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      offset = gu1_get_display_video_offset();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      offset = gu2_get_display_video_offset();
#	endif
   return (offset);
}

/*---------------------------------------------------------------------------
 * gfx_get_display_video_yuv_offsets
 *---------------------------------------------------------------------------
 */
void
gfx_get_display_video_yuv_offsets(unsigned long *yoffset,
				  unsigned long *uoffset,
				  unsigned long *voffset)
{
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_get_display_video_yuv_offsets(yoffset, uoffset, voffset);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_get_display_video_yuv_offsets
 *---------------------------------------------------------------------------
 */
void
gfx_get_display_video_yuv_pitch(unsigned long *ypitch, unsigned long *uvpitch)
{
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      gu2_get_display_video_yuv_pitch(ypitch, uvpitch);
#	endif
}

/*---------------------------------------------------------------------------
 * gfx_get_display_video_downscale_delta
 *---------------------------------------------------------------------------
 */
unsigned long
gfx_get_display_video_downscale_delta(void)
{
   unsigned long ret_value = 0;

#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      ret_value = gu2_get_display_video_downscale_delta();
#	endif

   return ret_value;
}

/*---------------------------------------------------------------------------
 * gfx_get_display_video_downscale_delta
 *---------------------------------------------------------------------------
 */
int
gfx_get_display_video_downscale_enable(void)
{
   int ret_value = 0;

#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      ret_value = gu2_get_display_video_downscale_enable();
#	endif

   return ret_value;
}

/*---------------------------------------------------------------------------
 * gfx_get_display_video_size
 *---------------------------------------------------------------------------
 */
unsigned long
gfx_get_display_video_size(void)
{
   unsigned long size = 0;

#	if GFX_DISPLAY_GU1
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU1)
      size = gu1_get_display_video_size();
#	endif
#	if GFX_DISPLAY_GU2
   if (gfx_display_type & GFX_DISPLAY_TYPE_GU2)
      size = gu2_get_display_video_size();
#	endif
   return (size);
}

#endif /* GFX_READ_ROUTINES */

#endif /* GFX_DISPLAY_DYNAMIC */

/* END OF FILE */
