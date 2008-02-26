/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/tdfx/tdfxdefs.h,v 1.14 2003/06/18 16:17:41 eich Exp $ */
/*
   Voodoo Banshee driver version 1.0.1

   Author: Daryll Strauss

   Copyright: 1998,1999
*/

#ifndef _TDFXDEFS_H_
#define _TDFXDEFS_H_

#define TDFXIOMAPSIZE 0x2000000

/* Flags */
#define BIT(n)  (1UL<<(n))
#define SST_SGRAM_OFLOP_DEL_ADJ_SHIFT   20
#define SST_SGRAM_CLK_NODELAY           BIT(13)
#define SST_DRAM_REFRESH_EN             BIT(0)
#define SST_DRAM_REFRESH_VALUE_SHIFT    1
#define SST_DRAM_REFRESH_VALUE          (0x1FF<<SST_DRAM_REFRESH_VALUE_SHIFT)
#define SST_SGRAM_TYPE_SHIFT            27
#define SST_SGRAM_TYPE                  (0x1L<<SST_SGRAM_TYPE_SHIFT)
#define SST_SGRAM_NUM_CHIPSETS          BIT(26)
#define SST_SGRAM_TYPE_8MBIT		(0x0L<<SST_SGRAM_TYPE_SHIFT)
#define SST_SGRAM_TYPE_16MBIT		(0x1L<<SST_SGRAM_TYPE_SHIFT)
#define SST_DISABLE_2D_BLOCK_WRITE      BIT(15)
#define SST_MCTL_TYPE_SDRAM             BIT(30)
#define SST_DAC_MODE_2X			BIT(0)
#define SST_VIDEO_2X_MODE_EN            BIT(26)
#define SST_VGA0_EXTENSIONS             BIT(6)
#define SST_WAKEUP_3C3                  1
#define SST_VGA0_WAKEUP_SELECT_SHIFT    8
#define SST_VGA0_LEGACY_DECODE_SHIFT    9
#define SST_VGA0_LEGACY_DECODE          (1 << SST_VGA0_LEGACY_DECODE_SHIFT)
#define SST_VGA0_ENABLE_DECODE          0
#define SST_ENABLE_ALT_READBACK         0
#define SST_VGA0_CLUT_SELECT_SHIFT      2
#define SST_CLUT_SELECT_6BIT            0
#define SST_CLUT_SELECT_8BIT            1
#define SST_VGA0_CONFIG_READBACK_SHIFT  10
#define SST_VIDEO_PROCESSOR_EN          BIT(0)
#define SST_CURSOR_MODE_SHIFT           1
#define SST_CURSOR_X11                  (1<<SST_CURSOR_MODE_SHIFT)
#define SST_DESKTOP_EN                  BIT(7)
#define SST_DESKTOP_PIXEL_FORMAT_SHIFT  18
#define SST_DESKTOP_CLUT_BYPASS         BIT(10)
#define SST_INTERLACE                   BIT(3)
#define SST_HALF_MODE                   BIT(4)
#define SST_CURSOR_EN                   BIT(27)
#define SST_FBI_BUSY                    BIT(7)
#define SST_BUSY                        BIT(9)
#define SST_RETRACE			BIT(6)
#define SST_COMMANDEXTRA_VSYNC          BIT(2)

#define MEM_TYPE_SGRAM  0
#define MEM_TYPE_SDRAM  1
/*
 * SST_RAW_LFB_ADDR_STRIDE(Lg2SizeInK) takes the
 * lfbMemoryConfig value for SGRAMStrideInTiles.  This
 * is given by this table:
 *  SGRAMStrideInBytes        lfbMemoryConfig Value
 *  ==================        =====================
 *          1k                          0
 *          2k                          1
 *          4k                          2
 *          8k                          3
 *         16k                          4
 *
 * FWIW, the right hand column is log2(left hand column)-10
 */
#define SST_RAW_LFB_ADDR_STRIDE_SHIFT 13
#define SST_RAW_LFB_ADDR_STRIDE(Lg2SizeInK) \
		((Lg2SizeInK)<<SST_RAW_LFB_ADDR_STRIDE_SHIFT)
#define SST_RAW_LFB_ADDR_STRIDE_4K SST_RAW_LFB_ADDR_STRIDE(2)
#define SST_RAW_LFB_ADDR_STRIDE_8K SST_RAW_LFB_ADDR_STRIDE(3)
#define SST_RAW_LFB_ADDR_STRIDE_16K SST_RAW_LFB_ADDR_STRIDE(4)
#define SST_RAW_LFB_TILE_STRIDE_SHIFT 16

#define BLIT_LEFT 1
#define BLIT_UP 2

/* Base Registers */
#define STATUS 0x0
#define PCIINIT0 0x4
#define SIPMONITOR 0x8
#define LFBMEMORYCONFIG 0xC
#define MISCINIT0 0x10
#define MISCINIT1 0x14
#define DRAMINIT0 0x18
#define DRAMINIT1 0x1C
#define AGPINIT 0x20
#define TMUGBEINIT 0x24
#define VGAINIT0 0x28
#define VGAINIT1 0x2c
#define DRAMCOMMAND 0x30
#define DRAMDATA 0x34
#define PLLCTRL0 0x40
#define PLLCTRL1 0x44
#define PLLCTRL2 0x48
#define DACMODE 0x4c
#define DACADDR 0x50
#define DACDATA 0x54
#define RGBMAXDELTA 0x58
#define VIDPROCCFG 0x5c
#define HWCURPATADDR 0x60
#define HWCURLOC 0x64
#define HWCURC0 0x68
#define HWCURC1 0x6c
#define VIDINFORMAT 0x70
#define VIDINSTATUS 0x74
#define VIDSERIALPARALLELPORT 0x78
#define VIDINXDECIMDELTAS 0x7c
#define VIDINDECIMINITERRS 0x80
#define VIDYDECIMDELTA 0x84
#define VIDPXELBUGTHOLD 0x88
#define VIDCHROMAMIN 0x8c
#define VIDCHROMAMAX 0x90
#define VIDCURRENTLINE 0x94
#define VIDSCREENSIZE 0x98
#define VIDOVERLAYSTARTCOORDS 0x9c
#define VIDOVERLAYENDSCREENCOORDS 0xa0
#define VIDOVERLAYDUDX 0xa4
#define VIDOVERLAYDUDXOFFSETSRCWIDTH 0xa8
#define VIDOVERLAYDVDY 0xac
#define VIDOVERLAYDVDYOFFSET 0xe0
#define VIDDESKTOPSTARTADDR 0xe4
#define VIDDESKTOPOVERLAYSTRIDE 0xe8
#define VIDINADDR0 0xec
#define VIDINADDR1 0xf0
#define VIDINADDR2 0xf4
#define VIDINSTRIDE 0xf8
#define VIDCUROVERLAYSTARTADDR 0xfc

/* 2D Commands */
#define SST_2D_NOP 0
#define SST_2D_SCRNTOSCRNBLIT 1
#define SST_2D_SCRNTOSCRNSTRETCH 2
#define SST_2D_HOSTTOSCRNBLIT 3
#define SST_2D_HOSTTOSCRNSTRECH 4
#define SST_2D_RECTANGLEFILL 5
#define SST_2D_LINE (6 | SST_2D_REVERSIBLE)
#define SST_2D_POLYLINE (7 | SST_2D_REVERSIBLE)
#define SST_2D_POLYGONFILL (8 | SST_2D_REVERSIBLE)

/* Flags */
#define SST_2D_REVERSIBLE               BIT(9)
#define SST_2D_STIPPLE_LINE             BIT(12)
#define SST_2D_MONOCHROME_PATTERN       BIT(13)
#define SST_2D_X_RIGHT_TO_LEFT          BIT(14)
#define SST_2D_Y_BOTTOM_TO_TOP          BIT(15)
#define SST_2D_TRANSPARENT_MONOCHROME   BIT(16)
#define SST_2D_SOURCE_PACKING_SHIFT     22
#define SST_2D_SOURCE_PACKING_BYTE      (1<<SST_2D_SOURCE_PACKING_SHIFT)
#define SST_2D_SOURCE_PACKING_WORD      (2<<SST_2D_SOURCE_PACKING_SHIFT)
#define SST_2D_SOURCE_PACKING_DWORD     (3<<SST_2D_SOURCE_PACKING_SHIFT)
#define SST_2D_X_PATOFFSET_SHIFT	17
#define SST_2D_Y_PATOFFSET_SHIFT	20
#define SST_2D_SRC_FORMAT_SHIFT		16
#define SST_2D_PIXFMT_1BPP		(0<<SST_2D_SRC_FORMAT_SHIFT)
#define SST_2D_SRC_COLORKEY_EX		BIT(0)
#define SST_2D_GO			BIT(8)
#define SST_2D_USECLIP1			BIT(23)

/* 2D Registers */
#define SST_2D_OFFSET           0x100000
#define SST_2D_CLIP0MIN SST_2D_OFFSET+0x8
#define SST_2D_CLIP0MAX SST_2D_OFFSET+0xC
#define SST_2D_DSTBASEADDR SST_2D_OFFSET+0x10
#define SST_2D_DSTFORMAT SST_2D_OFFSET+0x14
#define SST_2D_SRCCOLORKEYMIN SST_2D_OFFSET+0x18
#define SST_2D_SRCCOLORKEYMAX SST_2D_OFFSET+0x1c
#define SST_2D_DSTCOLORKEYMIN SST_2D_OFFSET+0x20
#define SST_2D_DSTCOLORKEYMAX SST_2D_OFFSET+0x24
#define SST_2D_BRESERROR0 SST_2D_OFFSET+0x28
#define SST_2D_BRESERROR1 SST_2D_OFFSET+0x2c
#define SST_2D_ROP SST_2D_OFFSET+0x30
#define SST_2D_SRCBASEADDR SST_2D_OFFSET+0x34
#define SST_2D_COMMANDEXTRA SST_2D_OFFSET+0x38
#define SST_2D_LINESTIPPLE SST_2D_OFFSET+0x3c
#define SST_2D_LINESTYLE SST_2D_OFFSET+0x40
#define SST_2D_CLIP1MIN SST_2D_OFFSET+0x4C
#define SST_2D_CLIP1MAX SST_2D_OFFSET+0x50
#define SST_2D_SRCFORMAT SST_2D_OFFSET+0x54
#define SST_2D_SRCSIZE SST_2D_OFFSET+0x58
#define SST_2D_SRCXY SST_2D_OFFSET+0x5C
#define SST_2D_COLORBACK SST_2D_OFFSET+0x60
#define SST_2D_COLORFORE SST_2D_OFFSET+0x64
#define SST_2D_DSTSIZE SST_2D_OFFSET+0x68
#define SST_2D_DSTXY SST_2D_OFFSET+0x6C
#define SST_2D_COMMAND SST_2D_OFFSET+0x70
#define SST_2D_LAUNCH SST_2D_OFFSET+0x80
#define SST_2D_PATTERN0 SST_2D_OFFSET+0x100
#define SST_2D_PATTERN1 SST_2D_OFFSET+0x104

/* 3D Commands */
#define SST_3D_NOP 0

/* 3D Registers */
#define SST_3D_OFFSET           	0x200000
#define SST_3D_STATUS			SST_3D_OFFSET+0
#define SST_3D_LFBMODE               	SST_3D_OFFSET+0x114
#define SST_3D_COMMAND 			SST_3D_OFFSET+0x120
#define SST_3D_SWAPBUFFERCMD		SST_3D_OFFSET+0x128
#define SST_3D_SLICTRL 			SST_3D_OFFSET+0x20C
#define SST_3D_AACTRL			SST_3D_OFFSET+0x210
#define SST_3D_SWAPPENDING		SST_3D_OFFSET+0x24C
#define SST_3D_LEFTOVERLAYBUF		SST_3D_OFFSET+0x250
#define SST_3D_RIGHTOVERLAYBUF		SST_3D_OFFSET+0x254
#define SST_3D_FBISWAPHISTORY		SST_3D_OFFSET+0x258

/* NAPALM REGISTERS */
#define CFG_PCI_COMMAND			4
#define CFG_MEM0BASE			16
#define CFG_MEM1BASE			20
#define CFG_INIT_ENABLE        		64
#define CFG_PCI_DECODE         		72
#define CFG_VIDEO_CTRL0        		128
#define CFG_VIDEO_CTRL1        		132
#define CFG_VIDEO_CTRL2        		136
#define CFG_SLI_LFB_CTRL       		140
#define CFG_AA_ZBUFF_APERTURE  		144
#define CFG_AA_LFB_CTRL        		148
#define CFG_SLI_AA_MISC        		172

/* Pixel Formats */
#define GR_PIXFMT_I_8                   0x0001
#define GR_PIXFMT_AI_88                 0x0002
#define GR_PIXFMT_RGB_565               0x0003
#define GR_PIXFMT_ARGB_1555             0x0004
#define GR_PIXFMT_ARGB_8888             0x0005
#define GR_PIXFMT_AA_2_RGB_565          0x0006
#define GR_PIXFMT_AA_2_ARGB_1555        0x0007
#define GR_PIXFMT_AA_2_ARGB_8888        0x0008
#define GR_PIXFMT_AA_4_RGB_565          0x0009
#define GR_PIXFMT_AA_4_ARGB_1555        0x000a
#define GR_PIXFMT_AA_4_ARGB_8888        0x000b

/* pciInit0 */
#define SST_PCI_STALL_ENABLE            BIT(0)
#define SST_PCI_LOWTHRESH_SHIFT         2
#define SST_PCI_LOWTHRESH               (0xF << SST_PCI_LOWTHRESH_SHIFT)
#define SST_PCI_HARDCODE_BASE           BIT(7)
#define SST_PCI_READ_WS                 BIT(8)
#define SST_PCI_WRITE_WS                BIT(9)
#define SST_PCI_DISABLE_IO              BIT(11)
#define SST_PCI_DISABLE_MEM             BIT(12)
#define SST_PCI_RETRY_INTERVAL_SHIFT    13
#define SST_PCI_RETRY_INTERVAL          (0x1F << SST_PCI_RETRY_INTERVAL_SHIFT)
#define SST_PCI_INTERRUPT_ENABLE        BIT(18)
#define SST_PCI_TIMEOUT_ENABLE          BIT(19)
#define SST_PCI_FORCE_FB_HIGH           BIT(26)

#define SST_AA_CLK_INVERT               BIT(20)
#define SST_AA_CLK_DELAY_SHIFT          21
#define SST_AA_CLK_DELAY                (0xF<<SST_AA_CLK_DELAY_SHIFT)

#define CFG_SWAP_ALGORITHM_VSYNC	(0x00)
#define CFG_SWAP_ALGORITHM_SYNCIN	(0x01)
#define CFG_SWAPBUFFER_ALGORITHM_SHIFT	(25)

/* CFG_INIT_ENABLE */
#define CFG_UPDATE_MEMBASE_LSBS		BIT(10)
#define CFG_SNOOP_EN			BIT(11)
#define CFG_SNOOP_MEMBASE0_EN		BIT(12)
#define CFG_SNOOP_MEMBASE1_EN		BIT(13)
#define CFG_SNOOP_SLAVE			BIT(14)
#define CFG_SNOOP_MEMBASE0_SHIFT	15
#define CFG_SNOOP_MEMBASE0		(0x3FF<<CFG_SNOOP_MEMBASE0_SHIFT)
#define CFG_SWAP_ALGORITHM		BIT(25)
#define CFG_SWAP_MASTER			BIT(26)
#define CFG_SWAP_QUICK			BIT(27)
#define CFG_MULTI_FUNCTION_DEV		BIT(28)
#define CFG_LFB_RD_CACHE_DISABLE	BIT(29)
#define CFG_SNOOP_FBIINIT_WR_EN		BIT(30)
#define CFG_SNOOP_MEMBASE0_DECODE_SHIFT	10
#define CFG_SNOOP_MEMBASE0_DECODE	(0xF<<CFG_SNOOP_MEMBASE0_DECODE_SHIFT)
#define CFG_SNOOP_MEMBASE1_DECODE_SHIFT	14
#define CFG_SNOOP_MEMBASE1_DECODE	(0xF<<CFG_SNOOP_MEMBASE1_DECODE_SHIFT)
#define CFG_SNOOP_MEMBASE1_SHIFT	18
#define CFG_SNOOP_MEMBASE1		(0x3FF<<CFG_SNOOP_MEMBASE1_SHIFT)

/* CFG_VIDEO_CTRL0 */
#define CFG_ENHANCED_VIDEO_EN		BIT(0)
#define CFG_ENHANCED_VIDEO_SLV		BIT(1)
#define CFG_VIDEO_TV_OUTPUT_EN		BIT(2)
#define CFG_VIDEO_LOCALMUX_SEL		BIT(3)
#define CFG_VIDEO_LOCALMUX_DESKTOP_PLUS_OVERLAY	BIT(3)
#define CFG_VIDEO_OTHERMUX_SEL_TRUE_SHIFT 	4
#define CFG_VIDEO_OTHERMUX_SEL_FALSE_SHIFT	6
#define CFG_VIDEO_OTHERMUX_SEL_TRUE	(0x3<<CFG_VIDEO_OTHERMUX_SEL_TRUE_SHIFT)
#define CFG_VIDEO_OTHERMUX_SEL_FALSE	(0x3<<CFG_VIDEO_OTHERMUX_SEL_FALSE_SHIFT)
#define CFG_VIDEO_OTHERMUX_SEL_PIPE	0
#define CFG_VIDEO_OTHERMUX_SEL_PIPE_PLUS_AAFIFO	1
#define CFG_VIDEO_OTHERMUX_SEL_AAFIFO 	2
#define CFG_SLI_FETCH_COMPARE_INV	BIT(8)
#define CFG_SLI_CRT_COMPARE_INV		BIT(9)
#define CFG_SLI_AAFIFO_COMPARE_INV	BIT(10)
#define CFG_VIDPLL_SEL                 	BIT(11)
#define CFG_DIVIDE_VIDEO_SHIFT		12
#define CFG_DIVIDE_VIDEO		(0x7<<CFG_DIVIDE_VIDEO_SHIFT)
#define CFG_DIVIDE_VIDEO_BY_1		(0x0<<CFG_DIVIDE_VIDEO_SHIFT)
#define CFG_DIVIDE_VIDEO_BY_2		(0x1<<CFG_DIVIDE_VIDEO_SHIFT)
#define CFG_DIVIDE_VIDEO_BY_4		(0x2<<CFG_DIVIDE_VIDEO_SHIFT)
#define CFG_DIVIDE_VIDEO_BY_8		(0x3<<CFG_DIVIDE_VIDEO_SHIFT)
#define CFG_DIVIDE_VIDEO_BY_16		(0x4<<CFG_DIVIDE_VIDEO_SHIFT)
#define CFG_DIVIDE_VIDEO_BY_32		(0x5<<CFG_DIVIDE_VIDEO_SHIFT)
#define CFG_ALWAYS_DRIVE_AA_BUS		BIT(15)
#define CFG_VSYNC_IN_DEL_SHIFT		16
#define CFG_VSYNC_IN_DEL		(0xF<<CFG_VSYNC_IN_DEL_SHIFT)
#define CFG_DAC_VSYNC_TRISTATE		BIT(24)
#define CFG_DAC_HSYNC_TRISTATE		BIT(25)

/* CFG_VIDEO_CTRL1 */
#define CFG_SLI_RENDERMASK_FETCH_SHIFT	0
#define CFG_SLI_RENDERMASK_FETCH	(0xFF<<CFG_SLI_RENDERMASK_FETCH_SHIFT)
#define CFG_SLI_COMPAREMASK_FETCH_SHIFT 8
#define CFG_SLI_COMPAREMASK_FETCH	(0xFF<<CFG_SLI_COMPAREMASK_FETCH_SHIFT)
#define CFG_SLI_RENDERMASK_CRT_SHIFT	16
#define CFG_SLI_RENDERMASK_CRT		(0xFF<<CFG_SLI_RENDERMASK_CRT_SHIFT)
#define CFG_SLI_COMPAREMASK_CRT_SHIFT	24 
#define CFG_SLI_COMPAREMASK_CRT		(0xFF<<CFG_SLI_COMPAREMASK_CRT_SHIFT)

/* CFG_VIDEO_CTRL2 */
#define CFG_SLI_RENDERMASK_AAFIFO_SHIFT 0
#define CFG_SLI_RENDERMASK_AAFIFO	(0xFF<<CFG_SLI_RENDERMASK_AAFIFO_SHIFT)
#define CFG_SLI_COMPAREMASK_AAFIFO_SHIFT 8
#define CFG_SLI_COMPAREMASK_AAFIFO	(0xFF<<CFG_SLI_COMPAREMASK_AAFIFO_SHIFT)

/* CFG_SLI_LFB_CTRL */
#define CFG_SLI_LFB_RENDERMASK_SHIFT	0
#define CFG_SLI_LFB_RENDERMASK		(0xFF<<CFG_SLI_LFB_RENDERMASK_SHIFT)
#define CFG_SLI_LFB_COMPAREMASK_SHIFT	8
#define CFG_SLI_LFB_COMPAREMASK		(0xFF<<CFG_SLI_LFB_COMPAREMASK_SHIFT)
#define CFG_SLI_LFB_SCANMASK_SHIFT	16	
#define CFG_SLI_LFB_SCANMASK		(0xFF<<CFG_SLI_LFB_SCANMASK_SHIFT)
#define CFG_SLI_LFB_NUMCHIPS_LOG2_SHIFT 24
#define CFG_SLI_LFB_NUMCHIPS_LOG2	(0x3<<CFG_SLI_LFB_NUMCHIPS_LOG2_SHIFT)
#define CFG_SLI_LFB_CPU_WR_EN		BIT(26)
#define CFG_SLI_LFB_DPTCH_WR_EN		BIT(27)
#define CFG_SLI_RD_EN			BIT(28)

/* CFG_AA_ZBUFF_APERTURE */
#define CFG_AA_DEPTH_BUFFER_BEG_SHIFT	0
#define CFG_AA_DEPTH_BUFFER_BEG		(0x7FFF<<CFG_AA_DEPTH_BUFFER_BEG_SHIFT)
#define CFG_AA_DEPTH_BUFFER_END_SHIFT	16
#define CFG_AA_DEPTH_BUFFER_END		(0xFFFF<<CFG_AA_DEPTH_BUFFER_END_SHIFT)

/* CFG_AA_LFB_CTRL */
#define CFG_AA_BASEADDR_SHIFT		0
#define CFG_AA_BASEADDR			(0x3FFFFFF<<CFG_AA_BASEADDR_SHIFT)
#define CFG_AA_LFB_CPU_WR_EN		BIT(26)
#define CFG_AA_LFB_DPTCH_WR_EN		BIT(27)
#define CFG_AA_LFB_RD_EN		BIT(28)
#define CFG_AA_LFB_RD_FORMAT_SHIFT	29
#define CFG_AA_LFB_RD_FORMAT		(0x3<<CFG_AA_LFB_RD_FORMAT_SHIFT)
#define CFG_AA_LFB_RD_FORMAT_16BPP	(0x0<<CFG_AA_LFB_RD_FORMAT_SHIFT)
#define CFG_AA_LFB_RD_FORMAT_15BPP	(0x1<<CFG_AA_LFB_RD_FORMAT_SHIFT)
#define CFG_AA_LFB_RD_FORMAT_32BPP	(0x2<<CFG_AA_LFB_RD_FORMAT_SHIFT)
#define CFG_AA_LFB_RD_DIVIDE_BY_4	BIT(31)

/* CFG_SLI_AA_MISC */
#define CFG_VGA_VSYNC_OFFSET_SHIFT	0
#define CFG_VGA_VSYNC_OFFSET		(0x1ff<<CFG_VGA_VSYNC_OFFSET_SHIFT)
#define CFG_VGA_VSYNC_OFFSET_PIXELS_SHIFT	0
#define CFG_VGA_VSYNC_OFFSET_CHARS_SHIFT	3
#define CFG_VGA_VSYNC_OFFSET_HXTRA_SHIFT	6 
#define CFG_HOTPLUG_SHIFT		9
#define CFG_HOTPLUG_TRISTATE		(0x0<<CFG_HOTPLUG_SHIFT)
#define CFG_HOTPLUG_DRIVE0		(0x2<<CFG_HOTPLUG_SHIFT)
#define CFG_HOTPLUG_DRIVE1		(0x3<<CFG_HOTPLUG_SHIFT)
#define CFG_AA_LFB_RD_SLV_WAIT		BIT(12)

/* SLICTL_3D_CTRL */
#define SLICTL_3D_RENDERMASK_SHIFT	0
#define SLICTL_3D_RENDERMASK		(0xFF<<SLICTL_3D_RENDERMASK_SHIFT)
#define SLICTL_3D_COMPAREMASK_SHIFT	8
#define SLICTL_3D_COMPAREMASK		(0xFF<<SLICTL_3D_COMPAREMASK_SHIFT)
#define SLICTL_3D_SCANMASK_SHIFT	16	
#define SLICTL_3D_SCANMASK		(0xFF<<SLICTL_3D_SCANMASK_SHIFT)
#define SLICTL_3D_NUMCHIPS_LOG2_SHIFT 	24
#define SLICTL_3D_NUMCHIPS_LOG2		(0x3<<SLICTL_3D_NUMCHIPS_LOG2_SHIFT)
#define SLICTL_3D_EN			BIT(26)

#define SST_POWERDOWN_DAC               BIT(8)

#endif
