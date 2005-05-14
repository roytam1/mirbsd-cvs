/* Instruction opcode header for iq2000.

THIS FILE IS MACHINE GENERATED WITH CGEN.

Copyright 1996-2005 Free Software Foundation, Inc.

This file is part of the GNU Binutils and/or GDB, the GNU debugger.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.

*/

#ifndef IQ2000_OPC_H
#define IQ2000_OPC_H

/* -- opc.h */

/* Allows reason codes to be output when assembler errors occur.  */
#define CGEN_VERBOSE_ASSEMBLER_ERRORS

/* Override disassembly hashing - there are variable bits in the top
   byte of these instructions.  */
#define CGEN_DIS_HASH_SIZE 8
#define CGEN_DIS_HASH(buf,value) (((* (unsigned char*) (buf)) >> 6) % CGEN_DIS_HASH_SIZE)

/* following activates check beyond hashing since some iq2000 and iq10
   instructions have same mnemonics but different functionality. */
#define CGEN_VALIDATE_INSN_SUPPORTED

extern int iq2000_cgen_insn_supported (CGEN_CPU_DESC cd, const CGEN_INSN *insn);

/* -- asm.c */
/* Enum declaration for iq2000 instruction types.  */
typedef enum cgen_insn_type {
  IQ2000_INSN_INVALID, IQ2000_INSN_ADD2, IQ2000_INSN_ADD, IQ2000_INSN_ADDI2
 , IQ2000_INSN_ADDI, IQ2000_INSN_ADDIU2, IQ2000_INSN_ADDIU, IQ2000_INSN_ADDU2
 , IQ2000_INSN_ADDU, IQ2000_INSN_ADO162, IQ2000_INSN_ADO16, IQ2000_INSN_AND2
 , IQ2000_INSN_AND, IQ2000_INSN_ANDI2, IQ2000_INSN_ANDI, IQ2000_INSN_ANDOI2
 , IQ2000_INSN_ANDOI, IQ2000_INSN_NOR2, IQ2000_INSN_NOR, IQ2000_INSN_OR2
 , IQ2000_INSN_OR, IQ2000_INSN_ORI2, IQ2000_INSN_ORI, IQ2000_INSN_RAM
 , IQ2000_INSN_SLL, IQ2000_INSN_SLLV2, IQ2000_INSN_SLLV, IQ2000_INSN_SLMV2
 , IQ2000_INSN_SLMV, IQ2000_INSN_SLT2, IQ2000_INSN_SLT, IQ2000_INSN_SLTI2
 , IQ2000_INSN_SLTI, IQ2000_INSN_SLTIU2, IQ2000_INSN_SLTIU, IQ2000_INSN_SLTU2
 , IQ2000_INSN_SLTU, IQ2000_INSN_SRA2, IQ2000_INSN_SRA, IQ2000_INSN_SRAV2
 , IQ2000_INSN_SRAV, IQ2000_INSN_SRL, IQ2000_INSN_SRLV2, IQ2000_INSN_SRLV
 , IQ2000_INSN_SRMV2, IQ2000_INSN_SRMV, IQ2000_INSN_SUB2, IQ2000_INSN_SUB
 , IQ2000_INSN_SUBU2, IQ2000_INSN_SUBU, IQ2000_INSN_XOR2, IQ2000_INSN_XOR
 , IQ2000_INSN_XORI2, IQ2000_INSN_XORI, IQ2000_INSN_BBI, IQ2000_INSN_BBIN
 , IQ2000_INSN_BBV, IQ2000_INSN_BBVN, IQ2000_INSN_BEQ, IQ2000_INSN_BEQL
 , IQ2000_INSN_BGEZ, IQ2000_INSN_BGEZAL, IQ2000_INSN_BGEZALL, IQ2000_INSN_BGEZL
 , IQ2000_INSN_BLTZ, IQ2000_INSN_BLTZL, IQ2000_INSN_BLTZAL, IQ2000_INSN_BLTZALL
 , IQ2000_INSN_BMB0, IQ2000_INSN_BMB1, IQ2000_INSN_BMB2, IQ2000_INSN_BMB3
 , IQ2000_INSN_BNE, IQ2000_INSN_BNEL, IQ2000_INSN_JALR, IQ2000_INSN_JR
 , IQ2000_INSN_LB, IQ2000_INSN_LBU, IQ2000_INSN_LH, IQ2000_INSN_LHU
 , IQ2000_INSN_LUI, IQ2000_INSN_LW, IQ2000_INSN_SB, IQ2000_INSN_SH
 , IQ2000_INSN_SW, IQ2000_INSN_BREAK, IQ2000_INSN_SYSCALL, IQ2000_INSN_ANDOUI
 , IQ2000_INSN_ANDOUI2, IQ2000_INSN_ORUI2, IQ2000_INSN_ORUI, IQ2000_INSN_BGTZ
 , IQ2000_INSN_BGTZL, IQ2000_INSN_BLEZ, IQ2000_INSN_BLEZL, IQ2000_INSN_MRGB
 , IQ2000_INSN_MRGB2, IQ2000_INSN_BCTXT, IQ2000_INSN_BC0F, IQ2000_INSN_BC0FL
 , IQ2000_INSN_BC3F, IQ2000_INSN_BC3FL, IQ2000_INSN_BC0T, IQ2000_INSN_BC0TL
 , IQ2000_INSN_BC3T, IQ2000_INSN_BC3TL, IQ2000_INSN_CFC0, IQ2000_INSN_CFC1
 , IQ2000_INSN_CFC2, IQ2000_INSN_CFC3, IQ2000_INSN_CHKHDR, IQ2000_INSN_CTC0
 , IQ2000_INSN_CTC1, IQ2000_INSN_CTC2, IQ2000_INSN_CTC3, IQ2000_INSN_JCR
 , IQ2000_INSN_LUC32, IQ2000_INSN_LUC32L, IQ2000_INSN_LUC64, IQ2000_INSN_LUC64L
 , IQ2000_INSN_LUK, IQ2000_INSN_LULCK, IQ2000_INSN_LUM32, IQ2000_INSN_LUM32L
 , IQ2000_INSN_LUM64, IQ2000_INSN_LUM64L, IQ2000_INSN_LUR, IQ2000_INSN_LURL
 , IQ2000_INSN_LUULCK, IQ2000_INSN_MFC0, IQ2000_INSN_MFC1, IQ2000_INSN_MFC2
 , IQ2000_INSN_MFC3, IQ2000_INSN_MTC0, IQ2000_INSN_MTC1, IQ2000_INSN_MTC2
 , IQ2000_INSN_MTC3, IQ2000_INSN_PKRL, IQ2000_INSN_PKRLR1, IQ2000_INSN_PKRLR30
 , IQ2000_INSN_RB, IQ2000_INSN_RBR1, IQ2000_INSN_RBR30, IQ2000_INSN_RFE
 , IQ2000_INSN_RX, IQ2000_INSN_RXR1, IQ2000_INSN_RXR30, IQ2000_INSN_SLEEP
 , IQ2000_INSN_SRRD, IQ2000_INSN_SRRDL, IQ2000_INSN_SRULCK, IQ2000_INSN_SRWR
 , IQ2000_INSN_SRWRU, IQ2000_INSN_TRAPQFL, IQ2000_INSN_TRAPQNE, IQ2000_INSN_TRAPREL
 , IQ2000_INSN_WB, IQ2000_INSN_WBU, IQ2000_INSN_WBR1, IQ2000_INSN_WBR1U
 , IQ2000_INSN_WBR30, IQ2000_INSN_WBR30U, IQ2000_INSN_WX, IQ2000_INSN_WXU
 , IQ2000_INSN_WXR1, IQ2000_INSN_WXR1U, IQ2000_INSN_WXR30, IQ2000_INSN_WXR30U
 , IQ2000_INSN_LDW, IQ2000_INSN_SDW, IQ2000_INSN_J, IQ2000_INSN_JAL
 , IQ2000_INSN_BMB, IQ2000_INSN_ANDOUI_Q10, IQ2000_INSN_ANDOUI2_Q10, IQ2000_INSN_ORUI_Q10
 , IQ2000_INSN_ORUI2_Q10, IQ2000_INSN_MRGBQ10, IQ2000_INSN_MRGBQ102, IQ2000_INSN_JQ10
 , IQ2000_INSN_JALQ10, IQ2000_INSN_JALQ10_2, IQ2000_INSN_BBIL, IQ2000_INSN_BBINL
 , IQ2000_INSN_BBVL, IQ2000_INSN_BBVNL, IQ2000_INSN_BGTZAL, IQ2000_INSN_BGTZALL
 , IQ2000_INSN_BLEZAL, IQ2000_INSN_BLEZALL, IQ2000_INSN_BGTZ_Q10, IQ2000_INSN_BGTZL_Q10
 , IQ2000_INSN_BLEZ_Q10, IQ2000_INSN_BLEZL_Q10, IQ2000_INSN_BMB_Q10, IQ2000_INSN_BMBL
 , IQ2000_INSN_BRI, IQ2000_INSN_BRV, IQ2000_INSN_BCTX, IQ2000_INSN_YIELD
 , IQ2000_INSN_CRC32, IQ2000_INSN_CRC32B, IQ2000_INSN_CNT1S, IQ2000_INSN_AVAIL
 , IQ2000_INSN_FREE, IQ2000_INSN_TSTOD, IQ2000_INSN_CMPHDR, IQ2000_INSN_MCID
 , IQ2000_INSN_DBA, IQ2000_INSN_DBD, IQ2000_INSN_DPWT, IQ2000_INSN_CHKHDRQ10
 , IQ2000_INSN_RBA, IQ2000_INSN_RBAL, IQ2000_INSN_RBAR, IQ2000_INSN_WBA
 , IQ2000_INSN_WBAU, IQ2000_INSN_WBAC, IQ2000_INSN_RBI, IQ2000_INSN_RBIL
 , IQ2000_INSN_RBIR, IQ2000_INSN_WBI, IQ2000_INSN_WBIC, IQ2000_INSN_WBIU
 , IQ2000_INSN_PKRLI, IQ2000_INSN_PKRLIH, IQ2000_INSN_PKRLIU, IQ2000_INSN_PKRLIC
 , IQ2000_INSN_PKRLA, IQ2000_INSN_PKRLAU, IQ2000_INSN_PKRLAH, IQ2000_INSN_PKRLAC
 , IQ2000_INSN_LOCK, IQ2000_INSN_UNLK, IQ2000_INSN_SWRD, IQ2000_INSN_SWRDL
 , IQ2000_INSN_SWWR, IQ2000_INSN_SWWRU, IQ2000_INSN_DWRD, IQ2000_INSN_DWRDL
 , IQ2000_INSN_CAM36, IQ2000_INSN_CAM72, IQ2000_INSN_CAM144, IQ2000_INSN_CAM288
 , IQ2000_INSN_CM32AND, IQ2000_INSN_CM32ANDN, IQ2000_INSN_CM32OR, IQ2000_INSN_CM32RA
 , IQ2000_INSN_CM32RD, IQ2000_INSN_CM32RI, IQ2000_INSN_CM32RS, IQ2000_INSN_CM32SA
 , IQ2000_INSN_CM32SD, IQ2000_INSN_CM32SI, IQ2000_INSN_CM32SS, IQ2000_INSN_CM32XOR
 , IQ2000_INSN_CM64CLR, IQ2000_INSN_CM64RA, IQ2000_INSN_CM64RD, IQ2000_INSN_CM64RI
 , IQ2000_INSN_CM64RIA2, IQ2000_INSN_CM64RS, IQ2000_INSN_CM64SA, IQ2000_INSN_CM64SD
 , IQ2000_INSN_CM64SI, IQ2000_INSN_CM64SIA2, IQ2000_INSN_CM64SS, IQ2000_INSN_CM128RIA2
 , IQ2000_INSN_CM128RIA3, IQ2000_INSN_CM128RIA4, IQ2000_INSN_CM128SIA2, IQ2000_INSN_CM128SIA3
 , IQ2000_INSN_CM128SIA4, IQ2000_INSN_CM128VSA, IQ2000_INSN_CFC, IQ2000_INSN_CTC
} CGEN_INSN_TYPE;

/* Index of `invalid' insn place holder.  */
#define CGEN_INSN_INVALID IQ2000_INSN_INVALID

/* Total number of insns in table.  */
#define MAX_INSNS ((int) IQ2000_INSN_CTC + 1)

/* This struct records data prior to insertion or after extraction.  */
struct cgen_fields
{
  int length;
  long f_nil;
  long f_anyof;
  long f_opcode;
  long f_rs;
  long f_rt;
  long f_rd;
  long f_shamt;
  long f_cp_op;
  long f_cp_op_10;
  long f_cp_grp;
  long f_func;
  long f_imm;
  long f_rd_rs;
  long f_rd_rt;
  long f_rt_rs;
  long f_jtarg;
  long f_jtargq10;
  long f_offset;
  long f_count;
  long f_bytecount;
  long f_index;
  long f_mask;
  long f_maskq10;
  long f_maskl;
  long f_excode;
  long f_rsrvd;
  long f_10_11;
  long f_24_19;
  long f_5;
  long f_10;
  long f_25;
  long f_cam_z;
  long f_cam_y;
  long f_cm_3func;
  long f_cm_4func;
  long f_cm_3z;
  long f_cm_4z;
};

#define CGEN_INIT_PARSE(od) \
{\
}
#define CGEN_INIT_INSERT(od) \
{\
}
#define CGEN_INIT_EXTRACT(od) \
{\
}
#define CGEN_INIT_PRINT(od) \
{\
}


#endif /* IQ2000_OPC_H */
