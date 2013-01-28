//**********************************************************************************************************
//
//! \brif CH376 File system layer V1.0 */
//! support frequently used function of file system
//! not used function can be dropped to save ROM and RAM
//!
//! \param name refers to short file name, root directory symbol can be included
//!        but do not include path separator and the hole length shouldn't exceed 1+8+1+3+1 bytes
//!
//! \param PathName refers to full path short file name, include root directory
//!        symbol, sub-folder name, path separator, file name/directory name
//!
//! \param LongName refers to long file name which encoded by UNICODE little endian, end with two bytes of 0.
//!        you should first define a global buffer GlobalBuf and its length should greater than 64 bytes to
//!        use long file name feature. This global buffer is shared by other functions in this file.
//
//************************************************************************************************************

#ifndef	__CH376_FS_H__
#define __CH376_FS_H__

//#include "hw_CH376INC.h"

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib
//! @{
//! \addtogroup USB
//! @{
//! \addtogroup USB File Management Controller
//! @{
//! \addtogroup CH376
//! @{
//! \addtogroup CH376_Driver_Single
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CH376_User_Config
//! CH376 Interface Configure
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! define NO_DEFAULT_CH376_INT to disable default Wait376Interrupt() function,
//!               and you should define a same function to implement same work.
//! define DEF_INT_TIMEOUT to set default timeout time/count in Wait376Interrupt()
//!                 function.If it is defined to 0, timeout limit will be forever.
//! define EN_DIR_CREATE to enable creating multi-sub-folder functions, default is disabled
//! define EN_DISK_QUERY to enable disk capacity and available volume querying function, default is disabled
//! define EN_SECTOR_ACCESS to enable sector read/write function, default is disabled
//! define EN_LONG_NAME to support long file name and related functions, default is not supporting long file name
//
//*****************************************************************************
#define EN_DIR_CREATE
#define EN_DISK_QUERY
#define EN_SECTOR_ACCESS
//#define EN_LONG_NAME

#ifdef	EN_LONG_NAME
#ifndef	LONG_NAME_BUF_LEN
//
//! Self defined buffer length for long file name, minimal length is LONG_NAME_PER_DIR*1
//
#define	LONG_NAME_BUF_LEN	( LONG_NAME_PER_DIR * 20 )
#endif
#endif
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CH376_FileSystem_Layer_Driver_API
//! @{
//
//*****************************************************************************

//
//! get the relative offset of a structure member
//
#define	STRUCT_OFFSET( s, m )	( (UINT32)( & ((s *)0) -> m ) )

//
//! Read data block from current USB host receiving buffer,return the length of data block
//
extern UINT8 	CH376ReadBlock( PUINT8 buf );

//
//! Write requested data block to specified buffer, return data length
//
extern UINT8 	CH376WriteReqBlock( PUINT8 buf );

//
//! Write specified length of data block to USB host sending buffer
//
extern void	CH376WriteHostBlock( PUINT8 buf, UINT8 len );

//
//! Write specified length of data block to specified offset address of USB host internal buffer
//
extern void	CH376WriteOfsBlock( PUINT8 buf, UINT8 ofs, UINT8 len );

//
//! Set file name to be manipulated
//
extern void	CH376SetFileName( PUINT8 name );

//
//! Read 32bit data from ch376 and end command
//
extern UINT32 	CH376Read32bitDat( void );

//
//! Read CH376 internal 8bit variable
//
extern UINT8 	CH376ReadVar8( UINT8 var );

//
//! Write CH376 internal 8bit variable
//
extern void		CH376WriteVar8( UINT8 var, UINT8 dat );

//
//! Read CH376 internal 32bit variable
//
extern UINT32 	CH376ReadVar32( UINT8 var );

//
//! Write CH376 internal 8bit variable
//
extern void	CH376WriteVar32( UINT8 var, UINT32 dat );

//
//! Call this function after invoking CH376DirInfoRead() to get FAT_DIR_INFO
//
extern void	CH376EndDirInfo( void );

//
//! Get current file size
//
extern UINT32	CH376GetFileSize( void );

//
//! Get disk and file system status
//
extern UINT8	CH376GetDiskStatus( void );

//
//! Get interrupt status and cancel interrupt request
//
extern UINT8	CH376GetIntStatus( void );

//
//! Wait for CH376 interrupt(INT# low level), return interrupt status code, if timeout return ERR_USB_UNKNOWN
//
#ifndef	NO_DEFAULT_CH376_INT
    extern UINT8	Wait376Interrupt( void );
#endif

//
//! Send command and wait for interrupt
//
extern UINT8	CH376SendCmdWaitInt( UINT8 mCmd );

//
//! Send command and one byte of data then wait for interrupt
//
extern UINT8	CH376SendCmdDatWaitInt( UINT8 mCmd, UINT8 mDat );

//
//! Check USB disk error
//
extern UINT8	CH376DiskReqSense( void );

//
//! Check if disk is connected, not support SD card
//
extern UINT8	CH376DiskConnect( void );

//
//! Initialize disk and check if disk is ready
//
extern UINT8	CH376DiskMount( void );

//
//! Open file in root directory or current directory
//
extern UINT8	CH376FileOpen( PUINT8 name );

//
//! Create file in root directory or current directory, if file exists, delete it first.
//
extern UINT8	CH376FileCreate( PUINT8 name );

//
//! Create directory/folder in root directory and open the directory, if the directory exists, only open it.
//
extern UINT8	CH376DirCreate( PUINT8 name );

//
//! Separate the last level of file or directory name, return the byte offset of the last level file or directory name in the path name
//
extern UINT8	CH376SeparatePath( PUINT8 path );

//
//! Open the file in multilevel directory or directory's parent directory.
// Support multilevel directory and path separator, the max
// length of pathname should not exceed 255 characters.
// StopName point to the last level file or directory name.
//
extern UINT8	CH376FileOpenDir( PUINT8 PathName, UINT8 StopName );

//
//! Open the file or directory in multilevel directory.
// Support multilevel directory and path separator, the max
// length of pathname should not exceed 255 characters.
//
extern UINT8	CH376FileOpenPath( PUINT8 PathName );

//
//! Create file in multilevel directory
// Support multilevel directory and path separator, the max
// length of pathname should not exceed 255 characters.
//
extern UINT8	CH376FileCreatePath( PUINT8 PathName );

//
//! Create directory/folder in multilevel directory and open the directory.
// Support multilevel directory and path separator, the max
// length of pathname should not exceed 255 characters.
//
#ifdef	EN_DIR_CREATE
    extern UINT8	CH376DirCreatePath( PUINT8 PathName );
#endif

//
//! Delete the file. If file is opened, system will directly delete, or the file will open and then delete.
// Support multilevel directory
//
extern UINT8	CH376FileErase( PUINT8 PathName );

//
//! Close current opened file or directory/folder
//
extern UINT8	CH376FileClose( UINT8 UpdateSz );

//
//! Read current file's information
//
extern UINT8	CH376DirInfoRead( void );

//
//! Save current file's information
//
extern UINT8	CH376DirInfoSave( void );

//
//! Move file pointer by unit of byte
//
extern UINT8	CH376ByteLocate( UINT32 offset );

//
//! Read data block from current file address by unit of byte
//
extern UINT8	CH376ByteRead( PUINT8 buf, UINT16 ReqCount, PUINT16 RealCount );

//
//! Write data block to current file address by unit of byte
//
extern UINT8	CH376ByteWrite( PUINT8 buf, UINT16 ReqCount, PUINT16 RealCount );

#ifdef	EN_DISK_QUERY

//
//! Query disk capacity, return sector count
//
extern UINT8	CH376DiskCapacity( PUINT32 DiskCap );

//
//! Query disk remain volume, return sector count
//
extern UINT8	CH376DiskQuery( PUINT32 DiskFre );

#endif

//
//! Move file pointer by unit of sector
//
extern UINT8	CH376SecLocate( UINT32 offset );

#ifdef	EN_SECTOR_ACCESS

//
//! Read multiple sector of data to buffer, do not support SD card
//
extern UINT8	CH376DiskReadSec( PUINT8 buf, UINT32 iLbaStart, UINT8 iSectorCount );

//
//! Write multiple sector of data to disk, do not support SD card
//
extern UINT8	CH376DiskWriteSec( PUINT8 buf, UINT32 iLbaStart, UINT8 iSectorCount );

//
//! Read data block from current address by unit of sector, do not support SD card
//
extern UINT8	CH376SecRead( PUINT8 buf, UINT8 ReqCount, PUINT8 RealCount );

//
//! Write data block to current address by unit of sector, do not support SD card
//
UINT8	CH376SecWrite( PUINT8 buf, UINT8 ReqCount, PUINT8 RealCount );

#endif

#ifdef	EN_LONG_NAME

//
//! Dedicated byte write function for long file name
//
extern UINT8	CH376LongNameWrite( PUINT8 buf, UINT16 ReqCount );

//
//! Compute the short file name's check sum of long file name.
// The input DirName is fixed no separator and point name of 11 bytes
//
extern UINT8	CH376CheckNameSum( PUINT8 DirName );

//
//! Move file point from upper level of directory to the sector which current file information located,
// use first 12 bytes of GlobalBuf.
//
extern UINT8	CH376LocateInUpDir( PUINT8 PathName );

//
//! Get long file name from short file name
// Need to input full PathName of short file name and receive buffer
// to receive LongName(encoded by UNICODE,end with two bytes of 0)
// use first 34 bytes of GlobalBuf
//
extern UINT8	CH376GetLongName( PUINT8 PathName, PUINT8 LongName );

//
//! Create file with long file name. LongName must be located in RAM
// Need to input full PathName of short file name and receive buffer
// to receive LongName(encoded by UNICODE,end with two bytes of 0)
//
extern UINT8	CH376CreateLongName( PUINT8 PathName, PUINT8 LongName );

#endif

//*****************************************************************************
//
//! @}
//!
//! @}
//! @}
//! @}
//! @}
//! @}
//
//*****************************************************************************

#ifdef __cplusplus
}
#endif

#endif
