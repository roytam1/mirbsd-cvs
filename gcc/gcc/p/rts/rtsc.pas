{ This file was generated automatically by make-rtsc-pas.
  DO NOT CHANGE THIS FILE MANUALLY! }

{ Pascal declarations of the GPC Run Time System routines that are
  implemented in C

  Note about the `GPC_' prefix:
  This is inserted so that some identifiers don't conflict with the
  built-in ones. In some cases, the built-in ones do exactly the
  same as the ones declared here, but often enough, they contain
  some "magic", so they should be used instead of the plain
  declarations here. In general, routines with a `GPC_' prefix
  should not be called from programs. They may change or disappear
  in future GPC versions.

  Copyright (C) 1998-2005 Free Software Foundation, Inc.

  Author: Frank Heckenbach <frank@pascal.gnu.de>

  This file is part of GNU Pascal.

  GNU Pascal is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published
  by the Free Software Foundation; either version 2, or (at your
  option) any later version.

  GNU Pascal is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with GNU Pascal; see the file COPYING. If not, write to the
  Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA
  02111-1307, USA.

  As a special exception, if you link this file with files compiled
  with a GNU compiler to produce an executable, this does not cause
  the resulting executable to be covered by the GNU General Public
  License. This exception does not however invalidate any other
  reasons why the executable file might be covered by the GNU
  General Public License. }

{$gnu-pascal,I-}

unit RTSC; attribute (name = 'GPC');

interface

const
  { Maximum size of a variable }
  MaxVarSize = MaxInt div 8;

{ If set, characters >= #$80 are assumed to be letters even if the
  locale routines don't say so. This is a kludge because some
  systems don't have correct non-English locale tables. }
var
  FakeHighLetters: Boolean = False; attribute (name = '_p_FakeHighLetters');

type
  PCStrings = ^TCStrings;
  TCStrings = array [0 .. MaxVarSize div SizeOf (CString) - 1] of CString;

  Int64 = Integer attribute (Size = 64);
  UnixTimeType = LongInt;  { This is hard-coded in the compiler. Do not change here. }
  MicroSecondTimeType = LongInt;
  FileSizeType = LongInt;
  SignedSizeType = Integer attribute (Size = BitSizeOf (SizeType));
  TSignalHandler = procedure (Signal: CInteger);

  StatFSBuffer = record
    BlockSize, BlocksTotal, BlocksFree: LongInt;
    FilesTotal, FilesFree: CInteger
  end;

  InternalSelectType = record
    Handle: CInteger;
    Read, Write, Exception: Boolean
  end;

  PString = ^String;

  { `Max' so the range of the array does not become invalid for
    Count = 0 }
  PPStrings = ^TPStrings;
  TPStrings (Count: Cardinal) = array [1 .. Max (Count, 1)] of PString;

  GlobBuffer = record
    Result: PPStrings;
    Internal1: Pointer;
    Internal2: PCStrings;
    Internal3: CInteger
  end;

{@internal}
  TCPasswordEntry = record
    UserName, RealName, Password, HomeDirectory, Shell: CString;
    UID, GID: CInteger
  end;

  PCPasswordEntries = ^TCPasswordEntries;
  TCPasswordEntries = array [0 .. MaxVarSize div SizeOf (TCPasswordEntry) - 1] of TCPasswordEntry;

{$define SqRt InternalSqRt} {$define Exp InternalExp} {$define Ln InternalLn}  { @@ }
{@endinternal}

{ Mathematical routines }

{@internal}
Real _p_Sin (Real x) attribute (const);
Real _p_Cos (Real x) attribute (const);
Real _p_ArcSin (Real x) attribute (const);
Real _p_ArcCos (Real x) attribute (const);
Real _p_ArcTan (Real x) attribute (const);
Real _p_SqRt (Real x) attribute (const);
Real _p_Ln (Real x) attribute (const);
Real _p_Exp (Real x) attribute (const);
Real _p_Power (Real x; Real y) attribute (const);
Real _p_InternalHypot (Real x; Real y) attribute (const);
Real _p_InternalLn1Plus (Real x) attribute (const);
long Real _p_LongReal_Sin (long Real x) attribute (const);
long Real _p_LongReal_Cos (long Real x) attribute (const);
long Real _p_LongReal_ArcSin (long Real x) attribute (const);
long Real _p_LongReal_ArcCos (long Real x) attribute (const);
long Real _p_LongReal_ArcTan (long Real x) attribute (const);
long Real _p_LongReal_SqRt (long Real x) attribute (const);
long Real _p_LongReal_Ln (long Real x) attribute (const);
long Real _p_LongReal_Exp (long Real x) attribute (const);
long Real _p_LongReal_Power (long Real x; long Real y) attribute (const);
{@endinternal}

Real _p_SinH (Real x) attribute (const);
Real _p_CosH (Real x) attribute (const);
Real _p_ArcTan2 (Real y; Real x) attribute (const);
Boolean _p_IsInfinity (long Real x) attribute (const);
Boolean _p_IsNotANumber (long Real x) attribute (const);
void _p_SplitReal (long Real x; CInteger *Exponent; long Real *Mantissa)

{ Character routines }

{ Convert a character to upper case, according to the current
Char _p_UpCase (Char ch) attribute (const);

{ Convert a character to lower case, according to the current
Char _p_LoCase (Char ch) attribute (const);
Boolean _p_IsUpCase (Char ch) attribute (const);
Boolean _p_IsLoCase (Char ch) attribute (const);
Boolean _p_IsAlpha (Char ch) attribute (const);
Boolean _p_IsAlphaNum (Char ch) attribute (const);
Boolean _p_IsAlphaNumUnderscore (Char ch) attribute (const);
Boolean _p_IsSpace (Char ch) attribute (const);
Boolean _p_IsPrintable (Char ch) attribute (const);

{ Time routines }

{ Sleep for a given number of seconds. }
void _p_Sleep (CInteger Seconds)

{ Sleep for a given number of microseconds. }
void _p_SleepMicroSeconds (CInteger MicroSeconds)

{ Set an alarm timer. }
CInteger _p_Alarm (CInteger Seconds)

{ Convert a Unix time value to broken-down local time.
void _p_UnixTimeToTime (UnixTimeType Time; CInteger *Year; CInteger *Month; CInteger *Day; CInteger *Hour; CInteger *Minute; CInteger *Second;
                                CInteger *TimeZone; Boolean *DST; CString *TZName1; CString *TZName2)

{ Convert broken-down local time to a Unix time value. }
UnixTimeType _p_TimeToUnixTime (CInteger Year; CInteger Month; CInteger Day; CInteger Hour; CInteger Minute; CInteger Second)

{ Get the real time. MicroSecond can be Null and is ignored then. }
UnixTimeType _p_GetUnixTime (CInteger *MicroSecond)

{ Get the CPU time used. MicroSecond can be Null and is ignored
CInteger _p_GetCPUTime (CInteger *MicroSecond)

{@internal}
void _p_InitTime
CInteger _p_CFormatTime (UnixTimeType Time; CString Format; CString Buf; CInteger Size)
{@endinternal}


{ Signal and process routines }

{ Extract information from the status returned by PWait }
Boolean _p_StatusExited (CInteger Status) attribute (const);
CInteger _p_StatusExitCode (CInteger Status) attribute (const);
Boolean _p_StatusSignaled (CInteger Status) attribute (const);
CInteger _p_StatusTermSignal (CInteger Status) attribute (const);
Boolean _p_StatusStopped (CInteger Status) attribute (const);
CInteger _p_StatusStopSignal (CInteger Status) attribute (const);

{ Install a signal handler and optionally return the previous
Boolean _p_InstallSignalHandler (CInteger Signal; TSignalHandler Handler; Boolean Restart; Boolean UnlessIgnored;
  TSignalHandler *OldHandler; Boolean *OldRestart)

{ Block or unblock a signal. }
void _p_BlockSignal (CInteger Signal; Boolean Block)

{ Test whether a signal is blocked. }
Boolean _p_SignalBlocked (CInteger Signal)

{ Sends a signal to a process. Returns True if successful. If Signal
Boolean _p_Kill (CInteger PID; CInteger Signal)

{ Constant for WaitPID }
const
  AnyChild = -1;

{ Waits for a child process with the given PID (or any child process
CInteger _p_WaitPID (CInteger PID; CInteger *WStatus; Boolean Block)

{ Returns the process ID. }
CInteger _p_ProcessID

{ Returns the process group. }
CInteger _p_ProcessGroup

{ Returns the real or effective user ID of the process. }
CInteger _p_UserID (Boolean Effective)

{ Tries to change the real and/or effective user ID. }
Boolean _p_SetUserID (CInteger Real; CInteger Effective)

{ Returns the real or effective group ID of the process. }
CInteger _p_GroupID (Boolean Effective)

{ Tries to change the real and/or effective group ID. }
Boolean _p_SetGroupID (CInteger Real; CInteger Effective)

{ Low-level file routines. Mostly for internal use. }

{ Get information about a file system. }
Boolean _p_StatFS (CString Path; StatFSBuffer *Buf)
Pointer _p_CStringOpenDir (CString DirName)
CString _p_CStringReadDir (Pointer Dir)
void _p_CStringCloseDir (Pointer Dir)

{ Returns the value of the symlink FileName in a CString allocated
CString _p_ReadLink (protected CString FileName)

{ Returns a pointer to a *static* buffer! }
CString _p_CStringRealPath (CString Path)

{ File mode constants that are ORed for BindingType.Mode, ChMod,
const
  fm_SetUID           = 04000;
  fm_SetGID           = 02000;
  fm_Sticky           = 01000;
  fm_UserReadable     = 00400;
  fm_UserWritable     = 00200;
  fm_UserExecutable   = 00100;
  fm_GroupReadable    = 00040;
  fm_GroupWritable    = 00020;
  fm_GroupExecutable  = 00010;
  fm_OthersReadable   = 00004;
  fm_OthersWritable   = 00002;
  fm_OthersExecutable = 00001;

{ Constants for Access and OpenHandle }
const
  MODE_EXEC     = 1 << 0;
  MODE_WRITE    = 1 << 1;
  MODE_READ     = 1 << 2;
  MODE_FILE     = 1 << 3;
  MODE_CREATE   = 1 << 4;
  MODE_EXCL     = 1 << 5;
  MODE_TRUNCATE = 1 << 6;
  MODE_BINARY   = 1 << 7;

{ Check if a file name is accessible. }
CInteger _p_Access (protected CString FileName; CInteger Request)

{ Get information about a file. Any argument except FileName can
CInteger _p_Stat (protected CString FileName; FileSizeType *Size;
  UnixTimeType *ATime; UnixTimeType *MTime; UnixTimeType *CTime;
  CInteger *User; CInteger *Group; CInteger *Mode; CInteger *Device; CInteger *INode; CInteger *Links;
  Boolean *SymLink; Boolean *Dir; Boolean *Special)
CInteger _p_OpenHandle (protected CString FileName; CInteger Mode)
SignedSizeType _p_ReadHandle (CInteger Handle; Pointer Buffer; SizeType Size)
SignedSizeType _p_WriteHandle (CInteger Handle; Pointer Buffer; SizeType Size)
CInteger _p_CloseHandle (CInteger Handle)
void _p_FlushHandle (CInteger Handle)
CInteger _p_DupHandle (CInteger Src; CInteger Dest)
CInteger _p_CStringRename (protected CString OldName; protected CString NewName)
CInteger _p_CStringUnlink (protected CString FileName)
CInteger _p_CStringChDir (protected CString FileName)
CInteger _p_CStringMkDir (protected CString FileName)
CInteger _p_CStringRmDir (protected CString FileName)
CInteger _p_UMask (CInteger Mask) attribute (ignorable);
CInteger _p_CStringChMod (protected CString FileName; CInteger Mode)
CInteger _p_CStringChOwn (protected CString FileName; CInteger Owner; CInteger Group)
CInteger _p_CStringUTime (protected CString FileName; UnixTimeType AccessTime; UnixTimeType ModificationTime)

{ Constants for SeekHandle }
const
  SeekAbsolute = 0;
  SeekRelative = 1;
  SeekFileEnd  = 2;

{ Seek to a position on a file handle. }
FileSizeType _p_SeekHandle (CInteger Handle; FileSizeType Offset; CInteger Whence)
CInteger _p_TruncateHandle (CInteger Handle; FileSizeType Size)
Boolean _p_LockHandle (CInteger Handle; Boolean WriteLock; Boolean Block)
Boolean _p_UnlockHandle (CInteger Handle)
CInteger _p_SelectHandle (CInteger Count; InternalSelectType *Events; MicroSecondTimeType MicroSeconds)

{ Constants for MMapHandle and MemoryMap }
const
  mm_Readable   = 1;
  mm_Writable   = 2;
  mm_Executable = 4;

{ Try to map (a part of) a file to memory. }
Pointer _p_MMapHandle (Pointer Start; SizeType Length; CInteger Access; Boolean Shared; CInteger Handle; FileSizeType Offset)

{ Unmap a previous memory mapping. }
CInteger _p_MUnMapHandle (Pointer Start; SizeType Length)

{ Returns the file name of the terminal device that is open on
CString _p_GetTerminalNameHandle (CInteger Handle; Boolean NeedName; CString DefaultName)

{ System routines }

{ Sets the process group of Process (or the current one if Process
Boolean _p_SetProcessGroup (CInteger Process; CInteger ProcessGroup)

{ Sets the process group of a terminal given by Terminal (as a file
Boolean _p_SetTerminalProcessGroup (CInteger Handle; CInteger ProcessGroup)

{ Returns the process group of a terminal given by Terminal (as a
CInteger _p_GetTerminalProcessGroup (CInteger Handle)

{ Set the standard input's signal generation, if it is a terminal. }
void _p_SetInputSignals (Boolean Signals)

{ Get the standard input's signal generation, if it is a terminal. }
Boolean _p_GetInputSignals

{ Internal routines }

{ Returns system information if available. Fields not available will
void _p_CStringSystemInfo (CString *SysName; CString *NodeName; CString *Release; CString *Version; CString *Machine; CString *DomainName)

{ Returns the path of the running executable *if possible*. }
protected CString _p_CStringExecutablePath (CString Buffer)

{@internal}

{ Returns a temporary directory name *if possible*. }
protected CString _p_CStringGetTempDirectory (CString Buffer; CInteger Size)

{ Executes a command line. }
CInteger _p_CSystem (CString CmdLine)
PCStrings _p_GetStartEnvironment (PCStrings ValueIfNotFound)
void _p_CStringSetEnv (CString VarName; CString Value; CString NewEnvCString; Boolean UnSet)
{@endinternal}


{ Sets ErrNo to the value of `errno' and returns the description
protected CString _p_CStringStrError (CInteger *ErrNo)

{@internal}

{ Returns a description for a signal. May return nil if not supported! }
protected CString _p_CStringStrSignal (CInteger Signal)
CInteger _p_FNMatch (protected CString Pattern; protected CString FileName)
void _p_GlobInternal (GlobBuffer *Buf; CString Pattern)
void _p_GlobFreeInternal (GlobBuffer *Buf)
Boolean _p_CGetPwNam (CString UserName; TCPasswordEntry *Entry)
Boolean _p_CGetPwUID (CInteger UID; TCPasswordEntry *Entry)
CInteger _p_CGetPwEnt (PCPasswordEntries *Entries)
void _p_InitMisc
void _p_InitMalloc (void (*WarnProc) (CString Msg))
void _p_ExitProgram (CInteger Status; Boolean AbortFlag) attribute (noreturn);
{@endinternal}

{@internal}
{ rtsc.pas }
type
  PProcedure = ^procedure;
  PProcList = ^TProcList;
  TProcList = record
    Next, Prev: PProcList;
    Proc: PProcedure
  end;

procedure RunFinalizers (var AtExitProcs: PProcList); attribute (name = '_p_RunFinalizers');

{@endinternal}

implementation

{ @@ from files.pas }
procedure Initialize_Std_Files; attribute (iocritical); external name '_p_Initialize_Std_Files';

{ This file is always compiled with debug information (see
  Makefile.in), but the file name of the following routine is set to
  a magic name, so a debugger can recognize it automatically and
  step over it into the finalizers themselves. }
{$ifndef DEBUG}
#line 1 "<implicit code>"
{$endif}
procedure RunFinalizers (var AtExitProcs: PProcList);
var
  p: PProcList;
  Proc: PProcedure;
begin
  while AtExitProcs <> nil do
    begin
      p := AtExitProcs;
      AtExitProcs := AtExitProcs^.Next;
      Proc := p^.Proc;
      Dispose (p);
      Proc^
    end
end;

{$I+}

begin
  InitMisc;
  InitTime;
  Initialize_Std_Files  { Do this very early, so standard files are available for messages etc. }
end.
