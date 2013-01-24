//*****************************************************************************
//
//! \file xhw_CH376INC.h
//! \brief C Define for CH376
//! \date 2008.10
//! \author W.ch
//! Website:  http://wch.cn
//
//*****************************************************************************
#ifndef __CH376INC_H__
#define __CH376INC_H__

#ifdef __cplusplus
extern "C" {
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
//! \addtogroup CH376_PreDefine_Data
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CH376_DataType_Define
//! @{
//
//*****************************************************************************

#ifndef		TRUE
#define		TRUE	1
#define		FALSE	0
#endif
#ifndef		NULL
#define		NULL	0
#endif

#ifndef UINT8
    typedef unsigned char                UINT8;
#endif
#ifndef UINT16
    typedef unsigned short               UINT16;
#endif
#ifndef UINT32
    typedef unsigned long                UINT32;
#endif
#ifndef PUINT8
    typedef unsigned char               *PUINT8;
#endif
#ifndef PUINT16
    typedef unsigned short              *PUINT16;
#endif
#ifndef PUINT32
    typedef unsigned long               *PUINT32;
#endif
#ifndef UINT8V
    typedef unsigned char volatile       UINT8V;
#endif
#ifndef PUINT8V
    typedef unsigned char volatile      *PUINT8V;
#endif

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CH376_CMD_Status_Define
//! \brief The following macros are CH376's command and status value definition
//! @{
//
//*****************************************************************************

//
//! Single data pack size
//
#define	CH376_DAT_BLOCK_LEN	0x40			/* USB单个数据包, 数据块的最大长度, 默认缓冲区的长度 */

    /* ********************************************************************************************************************* */
    /* 命令代码 */
    /* 部分命令兼容CH375芯片, 但是输入数据或者输出数据的可能局部不同) */
    /* 一个命令操作顺序包含:
              一个命令码(对于串口方式,命令码之前还需要两个同步码),
              若干个输入数据(可以是0个),
              产生中断通知 或者 若干个输出数据(可以是0个), 二选一, 有中断通知则一定没有输出数据, 有输出数据则一定不产生中断
           仅CMD01_WR_REQ_DATA命令例外, 顺序包含: 一个命令码, 一个输出数据, 若干个输入数据
       命令码起名规则: CMDxy_NAME
           其中的x和y都是数字, x说明最少输入数据个数(字节数), y说明最少输出数据个数(字节数), y如果是H则说明产生中断通知,
           有些命令能够实现0到多个字节的数据块读写, 数据块本身的字节数未包含在上述x或y之内 */
    /* 本文件默认会同时提供与CH375芯片命令码兼容的命令码格式（即去掉x和y之后), 如果不需要, 那么可以定义_NO_CH375_COMPATIBLE_禁止 */

    /* ********************************************************************************************************************* */
    /* 主要命令(手册一), 常用 */
//
//! get CH376 chip code and firmware version
//
#define	CMD01_GET_IC_VER	0x01
    /* 输出: 版本号( 位7为0, 位6为1, 位5~位0为版本号 ) */
    /*           CH376返回版本号的值为041H即版本号为01H */
//
//! serial mode: set serial baud rate(default reset baud rate is 9600bps,determined by D4/D5/D6 pins)
//
#define	CMD21_SET_BAUDRATE	0x02
    /* 输入: 波特率分频系数, 波特率分频常数 */
    /* 输出: 操作状态( CMD_RET_SUCCESS或CMD_RET_ABORT, 其它值说明操作未完成 ) */

//
//enter sleep mode
//
#define	CMD00_ENTER_SLEEP	0x03

//
//! execute hardware reset
//
#define	CMD00_RESET_ALL		0x05

//
//! check communication interface and working state
//
#define	CMD11_CHECK_EXIST	0x06
    /* 输入: 任意数据 */
    /* 输出: 输入数据的按位取反 */

//
//! USB device mode: set USB bus suspend state mode
//
#define	CMD20_CHK_SUSPEND	0x0B
    /* 输入: 数据10H, 检查方式 */
    /*           00H=不检查USB挂起, 04H=以50mS为间隔检查USB挂起, 05H=以10mS为间隔检查USB挂起 */

//
//! SPI interface mode: set SPI SDO pin as interrupt output
//
#define	CMD20_SET_SDO_INT	0x0B
    /* 输入: 数据16H, 中断方式 */
    /*           10H=禁止SDO引脚用于中断输出,在SCS片选无效时三态输出禁止, 90H=SDO引脚在SCS片选无效时兼做中断请求输出 */

//
//! USB host mode: get current file size
//
#define	CMD14_GET_FILE_SIZE	0x0C
    /* 输入: 数据68H */
    /* 输出: 当前文件长度(总长度32位,低字节在前) */

//
//! USB host mode: set current file size
//
#define	CMD50_SET_FILE_SIZE	0x0D
    /* 输入: 数据68H, 当前文件长度(总长度32位,低字节在前) */

//
//! set USB working mode
//
#define	CMD11_SET_USB_MODE	0x15
    /* 输入: 模式代码 */
    /*       00H=未启用的设备方式, 01H=已启用的设备方式并且使用外部固件模式(串口不支持), 02H=已启用的设备方式并且使用内置固件模式 */
    /*       03H=SD卡主机模式/未启用的主机模式,用于管理和存取SD卡中的文件 */
    /*       04H=未启用的主机方式, 05H=已启用的主机方式, 06H=已启用的主机方式并且自动产生SOF包, 07H=已启用的主机方式并且复位USB总线 */
    /* 输出: 操作状态( CMD_RET_SUCCESS或CMD_RET_ABORT, 其它值说明操作未完成 ) */

//
//! get interrupt state and cancel interrupt request
//
#define	CMD01_GET_STATUS	0x22
    /* 输出: 中断状态 */

//
//! USB device mode: release current USB buffer
//
#define	CMD00_UNLOCK_USB	0x23

//
//! read data block from current USB interrupt point buffer or host's RX buffer
//
#define	CMD01_RD_USB_DATA0	0x27
    /* 输出: 长度, 数据流 */

//
//! USB device mode: read data block from current USB interrupt point buffer
//! and release buffer,equal to CMD01_RD_USB_DATA0 + CMD00_UNLOCK_USB
//
#define	CMD01_RD_USB_DATA	0x28
    /* 输出: 长度, 数据流 */

//
//! USB device mode: write data block to USB point 2 TX buffer
//
#define	CMD10_WR_USB_DATA7	0x2B
    /* 输入: 长度, 数据流 */

//
//! write data block to USB host point TX buffer
//
#define	CMD10_WR_HOST_DATA	0x2C
    /* 输入: 长度, 数据流 */

//
//! write requested data block to specified internal buffer
//
#define	CMD01_WR_REQ_DATA	0x2D
    /* 输出: 长度 */
    /* 输入: 数据流 */

//
//! write data block to specified off address in the internal buffer
//
#define	CMD20_WR_OFS_DATA	0x2E
    /* 输入: 偏移, 长度, 数据流 */

//
//! host file mode: set file name
//
#define	CMD10_SET_FILE_NAME	0x2F
    /* 输入: 以0结束的字符串(含结束符0在内长度不超过14个字符) */

    /* ********************************************************************************************************************* */
    /* 主要命令(手册一), 常用, 以下命令总是在操作结束时产生中断通知, 并且总是没有输出数据 */

//
//! host file mode(not support SD card): check if disk is connect.
//
#define	CMD0H_DISK_CONNECT	0x30
    /* 输出中断 */

//
//! host file mode: initialize disk and check if disk is ready.
//
#define	CMD0H_DISK_MOUNT	0x31
    /* 输出中断 */

//
//! host file mode: open file or directory(folder),or enumerate files and directories(folders).
//
#define	CMD0H_FILE_OPEN		0x32
    /* 输出中断 */

//
//! host file mode: continue with enumeration.
//
#define	CMD0H_FILE_ENUM_GO	0x33
    /* 输出中断 */

//
//! host file mode: create a new file. The original file will be deleted if it exists.
//
#define	CMD0H_FILE_CREATE	0x34
    /* 输出中断 */

//
//! host file mode: delete file. If the file is open, it will be deleted directly,
//! otherwise the file will be firstly opened then deleted. The sub folder must open first.
//
#define	CMD0H_FILE_ERASE	0x35
    /* 输出中断 */

//
//! host file mode: close currently opened file or folder.
//
#define	CMD1H_FILE_CLOSE	0x36
    /* 输入: 是否允许更新文件长度 */
    /*          00H=禁止更新长度, 01H=允许更新长度 */
    /* 输出中断 */

//
//! host file mode: read the directory information of the file.
//
#define	CMD1H_DIR_INFO_READ	0x37
    /* 输入: 指定需要读取的目录信息结构在扇区内的索引号 */
    /*           索引号范围为00H~0FH, 索引号0FFH则为当前已经打开的文件 */
    /* 输出中断 */

//
//! host file mode: save the directory information of the file.
//
#define	CMD0H_DIR_INFO_SAVE	0x38
    /* 输出中断 */

//
//! host file mode: move file pointer by byte.
//
#define	CMD4H_BYTE_LOCATE	0x39
    /* 输入: 偏移字节数(总长度32位,低字节在前) */
    /* 输出中断 */

//
//! host file mode: read data block form current address by unit of byte.
//
#define	CMD2H_BYTE_READ		0x3A
    /* 输入: 请求读取的字节数(总长度16位,低字节在前) */
    /* 输出中断 */

//
//! host file mode: continue with byte reading.
//
#define	CMD0H_BYTE_RD_GO	0x3B
    /* 输出中断 */

//
//! host file mode: write data block to current address by unit of byte.
//
#define	CMD2H_BYTE_WRITE	0x3C
    /* 输入: 请求写入的字节数(总长度16位,低字节在前) */
    /* 输出中断 */

//
//! host file mode: continue with byte writing.
//
#define	CMD0H_BYTE_WR_GO	0x3D
    /* 输出中断 */

//
//! host file mode: query physic disk capacity.
//
#define	CMD0H_DISK_CAPACITY	0x3E
    /* 输出中断 */

//
//! host file mode: query remaining capacity.
//
#define	CMD0H_DISK_QUERY	0x3F
    /* 输出中断 */

//
//! host file mode: create directory(folder) and open it.
//! If the directory(folder) exists, the directory(folder) will be only opened.
//
#define	CMD0H_DIR_CREATE	0x40
    /* 输出中断 */

//
//! host file mode: move file pointer by the unit of sector.
//
#define	CMD4H_SEC_LOCATE	0x4A
    /* 输入: 偏移扇区数(总长度32位,低字节在前) */
    /* 输出中断 */

//
//! host file mode(not support SD card): read data block form current address by the unit of sector.
//
#define	CMD1H_SEC_READ		0x4B
    /* 输入: 请求读取的扇区数 */
    /* 输出中断 */

//
//! host file mode(not support SD card): write data block to current address by the unit of sector.
//
#define	CMD1H_SEC_WRITE		0x4C
    /* 输入: 请求写入的扇区数 */
    /* 输出中断 */

//
//! host mode(not support SD card): execute BulkOnly transmit protocol command in USB storage controller
//
#define	CMD0H_DISK_BOC_CMD	0x50
    /* 输出中断 */

//
//! host mode(not support SD card): read physic sector from USB storage
//
#define	CMD5H_DISK_READ		0x54
    /* 输入: LBA物理扇区地址(总长度32位, 低字节在前), 扇区数(01H~FFH) */
    /* 输出中断 */

//
//! host mode(not support SD card): continue reading physic sector from USB storage
//
#define	CMD0H_DISK_RD_GO	0x55
    /* 输出中断 */

//
//! host mode(not support SD card): write physic sector to USB storage
//
#define	CMD5H_DISK_WRITE	0x56
    /* 输入: LBA物理扇区地址(总长度32位, 低字节在前), 扇区数(01H~FFH) */
    /* 输出中断 */

//
//! host mode(not support SD card): continue writing physic sector to USB storage
//
#define	CMD0H_DISK_WR_GO	0x57
    /* 输出中断 */

    /* ********************************************************************************************************************* */
    /* 辅助命令(手册二), 不太常用或者是为了与CH375和CH372兼容 */

#define	CMD10_SET_USB_SPEED	0x04			/* 设置USB总线速度, 在每次CMD11_SET_USB_MODE设置USB工作模式时会自动恢复到12Mbps全速 */
    /* 输入: 总线速度代码 */
    /*           00H=12Mbps全速FullSpeed（默认值）, 01H=1.5Mbps（仅修改频率）, 02H=1.5Mbps低速LowSpeed */

#define	CMD11_GET_DEV_RATE	0x0A			/* 主机方式: 获取当前连接的USB设备的数据速率类型 */
    /* 输入: 数据07H */
    /* 输出: 数据速率类型 */
    /*           位4为1则是1.5Mbps低速USB设备, 否则是12Mbps全速USB设备 */

#define	CMD11_GET_TOGGLE	0x0A			/* 获取OUT事务的同步状态 */
    /* 输入: 数据1AH */
    /* 输出: 同步状态 */
    /*           位4为1则OUT事务同步, 否则OUT事务不同步 */

#define	CMD11_READ_VAR8		0x0A			/* 读取指定的8位文件系统变量 */
    /* 输入: 变量地址 */
    /* 输出: 数据 */

    /*#define	CMD11_GET_MAX_LUN	= CMD11_READ_VAR8( VAR_UDISK_LUN )*/	/* 主机方式: 获取USB存储器最大和当前逻辑单元号 */

#define	CMD20_SET_RETRY		0x0B			/* 主机方式: 设置USB事务操作的重试次数 */
    /* 输入: 数据25H, 重试次数 */
    /*           位7为0则收到NAK时不重试, 位7为1位6为0则收到NAK时无限重试, 位7为1位6为1则收到NAK时最多重试3秒, 位5~位0为超时后的重试次数 */

#define	CMD20_WRITE_VAR8	0x0B			/* 设置指定的8位文件系统变量 */
    /* 输入: 变量地址, 数据 */

    /*#define	CMD20_SET_DISK_LUN	= CMD20_WRITE_VAR8( VAR_UDISK_LUN )*/	/* 主机方式: 设置USB存储器的当前逻辑单元号 */

#define	CMD14_READ_VAR32	0x0C			/* 读取指定的32位文件系统变量 */
    /* 输入: 变量地址 */
    /* 输出: 数据(总长度32位,低字节在前) */

#define	CMD50_WRITE_VAR32	0x0D			/* 设置指定的32位文件系统变量 */
    /* 输入: 变量地址, 数据(总长度32位,低字节在前) */

#define	CMD01_DELAY_100US	0x0F			/* 延时100uS(串口不支持) */
    /* 输出: 延时期间输出0,延时结束输出非0 */

#define	CMD40_SET_USB_ID	0x12			/* 设备方式: 设置USB厂商VID和产品PID */
    /* 输入: 厂商ID低字节, 厂商ID高字节, 产品ID低字节, 产品ID高字节 */

#define	CMD10_SET_USB_ADDR	0x13			/* 设置USB地址 */
    /* 输入: 地址值 */

#define	CMD01_TEST_CONNECT	0x16			/* 主机方式/不支持SD卡: 检查USB设备连接状态 */
    /* 输出: 状态( USB_INT_CONNECT或USB_INT_DISCONNECT或USB_INT_USB_READY, 其它值说明操作未完成 ) */

#define	CMD00_ABORT_NAK		0x17			/* 主机方式: 放弃当前NAK的重试 */

#define	CMD10_SET_ENDP2		0x18			/* 设备方式(串口不支持): 设置USB端点0的接收器 */
    /* 输入: 工作方式 */
    /*           位7为1则位6为同步触发位, 否则同步触发位不变 */
    /*           位3~位0为事务响应方式:  0000-就绪ACK, 1110-正忙NAK, 1111-错误STALL */

#define	CMD10_SET_ENDP3		0x19			/* 设备方式(串口不支持): 设置USB端点0的发送器 */
    /* 输入: 工作方式 */
    /*           位7为1则位6为同步触发位, 否则同步触发位不变 */
    /*           位3~位0为事务响应方式:  0000~1000-就绪ACK, 1110-正忙NAK, 1111-错误STALL */

#define	CMD10_SET_ENDP4		0x1A			/* 设备方式(串口不支持): 设置USB端点1的接收器 */
    /* 输入: 工作方式 */
    /*           位7为1则位6为同步触发位, 否则同步触发位不变 */
    /*           位3~位0为事务响应方式:  0000-就绪ACK, 1110-正忙NAK, 1111-错误STALL */

#define	CMD10_SET_ENDP5		0x1B			/* 设备方式(串口不支持): 设置USB端点1的发送器 */
    /* 输入: 工作方式 */
    /*           位7为1则位6为同步触发位, 否则同步触发位不变 */
    /*           位3~位0为事务响应方式:  0000~1000-就绪ACK, 1110-正忙NAK, 1111-错误STALL */

#define	CMD10_SET_ENDP6		0x1C			/* 设置USB端点2/主机端点的接收器 */
    /* 输入: 工作方式 */
    /*           位7为1则位6为同步触发位, 否则同步触发位不变 */
    /*           位3~位0为事务响应方式:  0000-就绪ACK, 1101-就绪但不返回ACK, 1110-正忙NAK, 1111-错误STALL */

#define	CMD10_SET_ENDP7		0x1D			/* 设置USB端点2/主机端点的发送器 */
    /* 输入: 工作方式 */
    /*           位7为1则位6为同步触发位, 否则同步触发位不变 */
    /*           位3~位0为事务响应方式:  0000-就绪ACK, 1101-就绪但无须应答, 1110-正忙NAK, 1111-错误STALL */

#define	CMD00_DIRTY_BUFFER	0x25			/* 主机文件模式: 清除内部的磁盘和文件缓冲区 */

#define	CMD10_WR_USB_DATA3	0x29			/* 设备方式(串口不支持): 向USB端点0的发送缓冲区写入数据块 */
    /* 输入: 长度, 数据流 */

#define	CMD10_WR_USB_DATA5	0x2A			/* 设备方式(串口不支持): 向USB端点1的发送缓冲区写入数据块 */
    /* 输入: 长度, 数据流 */

    /* ********************************************************************************************************************* */
    /* 辅助命令(手册二), 不太常用或者是为了与CH375和CH372兼容, 以下命令总是在操作结束时产生中断通知, 并且总是没有输出数据 */

#define	CMD1H_CLR_STALL		0x41			/* 主机方式: 控制传输-清除端点错误 */
    /* 输入: 端点号 */
    /* 输出中断 */

#define	CMD1H_SET_ADDRESS	0x45			/* 主机方式: 控制传输-设置USB地址 */
    /* 输入: 地址值 */
    /* 输出中断 */

#define	CMD1H_GET_DESCR		0x46			/* 主机方式: 控制传输-获取描述符 */
    /* 输入: 描述符类型 */
    /* 输出中断 */

#define	CMD1H_SET_CONFIG	0x49			/* 主机方式: 控制传输-设置USB配置 */
    /* 输入: 配置值 */
    /* 输出中断 */

#define	CMD0H_AUTO_SETUP	0x4D			/* 主机方式/不支持SD卡: 自动配置USB设备 */
    /* 输出中断 */

#define	CMD2H_ISSUE_TKN_X	0x4E			/* 主机方式: 发出同步令牌, 执行事务, 该命令可代替 CMD10_SET_ENDP6/CMD10_SET_ENDP7 + CMD1H_ISSUE_TOKEN */
    /* 输入: 同步标志, 事务属性 */
    /*           同步标志的位7为主机端点IN的同步触发位, 位6为主机端点OUT的同步触发位, 位5~位0必须为0 */
    /*           事务属性的低4位是令牌, 高4位是端点号 */
    /* 输出中断 */

#define	CMD1H_ISSUE_TOKEN	0x4F			/* 主机方式: 发出令牌, 执行事务, 建议用CMD2H_ISSUE_TKN_X命令 */
    /* 输入: 事务属性 */
    /*           低4位是令牌, 高4位是端点号 */
    /* 输出中断 */

#define	CMD0H_DISK_INIT		0x51			/* 主机方式/不支持SD卡: 初始化USB存储器 */
    /* 输出中断 */

#define	CMD0H_DISK_RESET	0x52			/* 主机方式/不支持SD卡: 控制传输-复位USB存储器 */
    /* 输出中断 */

#define	CMD0H_DISK_SIZE		0x53			/* 主机方式/不支持SD卡: 获取USB存储器的容量 */
    /* 输出中断 */

#define	CMD0H_DISK_INQUIRY	0x58			/* 主机方式/不支持SD卡: 查询USB存储器特性 */
    /* 输出中断 */

#define	CMD0H_DISK_READY	0x59			/* 主机方式/不支持SD卡: 检查USB存储器就绪 */
    /* 输出中断 */

#define	CMD0H_DISK_R_SENSE	0x5A			/* 主机方式/不支持SD卡: 检查USB存储器错误 */
    /* 输出中断 */

#define	CMD0H_RD_DISK_SEC	0x5B			/* 主机文件模式: 从磁盘读取一个扇区的数据到内部缓冲区 */
    /* 输出中断 */

#define	CMD0H_WR_DISK_SEC	0x5C			/* 主机文件模式: 将内部缓冲区的一个扇区的数据写入磁盘 */
    /* 输出中断 */

#define	CMD0H_DISK_MAX_LUN	0x5D			/* 主机方式: 控制传输-获取USB存储器最大逻辑单元号 */
    /* 输出中断 */

    /* ********************************************************************************************************************* */
    /* the following macros are intended for compatibility with CH375 command */

#ifndef	_NO_CH375_COMPATIBLE_
#define	CMD_GET_IC_VER		CMD01_GET_IC_VER
#define	CMD_SET_BAUDRATE	CMD21_SET_BAUDRATE
#define	CMD_ENTER_SLEEP		CMD00_ENTER_SLEEP
#define	CMD_RESET_ALL		CMD00_RESET_ALL
#define	CMD_CHECK_EXIST		CMD11_CHECK_EXIST
#define	CMD_CHK_SUSPEND		CMD20_CHK_SUSPEND
#define	CMD_SET_SDO_INT		CMD20_SET_SDO_INT
#define	CMD_GET_FILE_SIZE	CMD14_GET_FILE_SIZE
#define	CMD_SET_FILE_SIZE	CMD50_SET_FILE_SIZE
#define	CMD_SET_USB_MODE	CMD11_SET_USB_MODE
#define	CMD_GET_STATUS		CMD01_GET_STATUS
#define	CMD_UNLOCK_USB		CMD00_UNLOCK_USB
#define	CMD_RD_USB_DATA0	CMD01_RD_USB_DATA0
#define	CMD_RD_USB_DATA		CMD01_RD_USB_DATA
#define	CMD_WR_USB_DATA7	CMD10_WR_USB_DATA7
#define	CMD_WR_HOST_DATA	CMD10_WR_HOST_DATA
#define	CMD_WR_REQ_DATA		CMD01_WR_REQ_DATA
#define	CMD_WR_OFS_DATA		CMD20_WR_OFS_DATA
#define	CMD_SET_FILE_NAME	CMD10_SET_FILE_NAME
#define	CMD_DISK_CONNECT	CMD0H_DISK_CONNECT
#define	CMD_DISK_MOUNT		CMD0H_DISK_MOUNT
#define	CMD_FILE_OPEN		CMD0H_FILE_OPEN
#define	CMD_FILE_ENUM_GO	CMD0H_FILE_ENUM_GO
#define	CMD_FILE_CREATE		CMD0H_FILE_CREATE
#define	CMD_FILE_ERASE		CMD0H_FILE_ERASE
#define	CMD_FILE_CLOSE		CMD1H_FILE_CLOSE
#define	CMD_DIR_INFO_READ	CMD1H_DIR_INFO_READ
#define	CMD_DIR_INFO_SAVE	CMD0H_DIR_INFO_SAVE
#define	CMD_BYTE_LOCATE		CMD4H_BYTE_LOCATE
#define	CMD_BYTE_READ		CMD2H_BYTE_READ
#define	CMD_BYTE_RD_GO		CMD0H_BYTE_RD_GO
#define	CMD_BYTE_WRITE		CMD2H_BYTE_WRITE
#define	CMD_BYTE_WR_GO		CMD0H_BYTE_WR_GO
#define	CMD_DISK_CAPACITY	CMD0H_DISK_CAPACITY
#define	CMD_DISK_QUERY		CMD0H_DISK_QUERY
#define	CMD_DIR_CREATE		CMD0H_DIR_CREATE
#define	CMD_SEC_LOCATE		CMD4H_SEC_LOCATE
#define	CMD_SEC_READ		CMD1H_SEC_READ
#define	CMD_SEC_WRITE		CMD1H_SEC_WRITE
#define	CMD_DISK_BOC_CMD	CMD0H_DISK_BOC_CMD
#define	CMD_DISK_READ		CMD5H_DISK_READ
#define	CMD_DISK_RD_GO		CMD0H_DISK_RD_GO
#define	CMD_DISK_WRITE		CMD5H_DISK_WRITE
#define	CMD_DISK_WR_GO		CMD0H_DISK_WR_GO
#define	CMD_SET_USB_SPEED	CMD10_SET_USB_SPEED
#define	CMD_GET_DEV_RATE	CMD11_GET_DEV_RATE
#define	CMD_GET_TOGGLE		CMD11_GET_TOGGLE
#define	CMD_READ_VAR8		CMD11_READ_VAR8
#define	CMD_SET_RETRY		CMD20_SET_RETRY
#define	CMD_WRITE_VAR8		CMD20_WRITE_VAR8
#define	CMD_READ_VAR32		CMD14_READ_VAR32
#define	CMD_WRITE_VAR32		CMD50_WRITE_VAR32
#define	CMD_DELAY_100US		CMD01_DELAY_100US
#define	CMD_SET_USB_ID		CMD40_SET_USB_ID
#define	CMD_SET_USB_ADDR	CMD10_SET_USB_ADDR
#define	CMD_TEST_CONNECT	CMD01_TEST_CONNECT
#define	CMD_ABORT_NAK		CMD00_ABORT_NAK
#define	CMD_SET_ENDP2		CMD10_SET_ENDP2
#define	CMD_SET_ENDP3		CMD10_SET_ENDP3
#define	CMD_SET_ENDP4		CMD10_SET_ENDP4
#define	CMD_SET_ENDP5		CMD10_SET_ENDP5
#define	CMD_SET_ENDP6		CMD10_SET_ENDP6
#define	CMD_SET_ENDP7		CMD10_SET_ENDP7
#define	CMD_DIRTY_BUFFER	CMD00_DIRTY_BUFFER
#define	CMD_WR_USB_DATA3	CMD10_WR_USB_DATA3
#define	CMD_WR_USB_DATA5	CMD10_WR_USB_DATA5
#define	CMD_CLR_STALL		CMD1H_CLR_STALL
#define	CMD_SET_ADDRESS		CMD1H_SET_ADDRESS
#define	CMD_GET_DESCR		CMD1H_GET_DESCR
#define	CMD_SET_CONFIG		CMD1H_SET_CONFIG
#define	CMD_AUTO_SETUP		CMD0H_AUTO_SETUP
#define	CMD_ISSUE_TKN_X		CMD2H_ISSUE_TKN_X
#define	CMD_ISSUE_TOKEN		CMD1H_ISSUE_TOKEN
#define	CMD_DISK_INIT		CMD0H_DISK_INIT
#define	CMD_DISK_RESET		CMD0H_DISK_RESET
#define	CMD_DISK_SIZE		CMD0H_DISK_SIZE
#define	CMD_DISK_INQUIRY	CMD0H_DISK_INQUIRY
#define	CMD_DISK_READY		CMD0H_DISK_READY
#define	CMD_DISK_R_SENSE	CMD0H_DISK_R_SENSE
#define	CMD_RD_DISK_SEC		CMD0H_RD_DISK_SEC
#define	CMD_WR_DISK_SEC		CMD0H_WR_DISK_SEC
#define	CMD_DISK_MAX_LUN	CMD0H_DISK_MAX_LUN
#endif

    /* ********************************************************************************************************************* */
    /* 并口方式, 状态端口(读命令端口)的位定义 */
#ifndef	PARA_STATE_INTB
#define	PARA_STATE_INTB		0x80			/* 并口方式状态端口的位7: 中断标志,低有效 */
#define	PARA_STATE_BUSY		0x10			/* 并口方式状态端口的位4: 忙标志,高有效 */
#endif

    /* ********************************************************************************************************************* */
    /* 串口方式, 操作命令前的引导同步码 */
#ifndef	SER_CMD_TIMEOUT
#define	SER_CMD_TIMEOUT		32				/* 串口命令超时时间, 单位为mS, 同步码之间及同步码与命令码之间的间隔应该尽量短, 超时后的处理方式为丢弃 */
#define	SER_SYNC_CODE1		0x57			/* 启动操作的第1个串口同步码 */
#define	SER_SYNC_CODE2		0xAB			/* 启动操作的第2个串口同步码 */
#endif

    /* ********************************************************************************************************************* */
    /* 操作状态 */

#ifndef	CMD_RET_SUCCESS
#define	CMD_RET_SUCCESS		0x51			/* 命令操作成功 */
#define	CMD_RET_ABORT		0x5F			/* 命令操作失败 */
#endif

    /* ********************************************************************************************************************* */
    /* USB中断状态 */

#ifndef	USB_INT_EP0_SETUP

    /* 以下状态代码为特殊事件中断, 如果通过CMD20_CHK_SUSPEND启用USB总线挂起检查, 那么必须处理USB总线挂起和睡眠唤醒的中断状态 */
#define	USB_INT_USB_SUSPEND	0x05			/* USB总线挂起事件 */
#define	USB_INT_WAKE_UP		0x06			/* 从睡眠中被唤醒事件 */

    /* 以下状态代码0XH用于USB设备方式 */
    /*   内置固件模式下只需要处理: USB_INT_EP1_OUT, USB_INT_EP1_IN, USB_INT_EP2_OUT, USB_INT_EP2_IN */
    /*   位7-位4为0000 */
    /*   位3-位2指示当前事务, 00=OUT, 10=IN, 11=SETUP */
    /*   位1-位0指示当前端点, 00=端点0, 01=端点1, 10=端点2, 11=USB总线复位 */
#define	USB_INT_EP0_SETUP	0x0C			/* USB端点0的SETUP */
#define	USB_INT_EP0_OUT		0x00			/* USB端点0的OUT */
#define	USB_INT_EP0_IN		0x08			/* USB端点0的IN */
#define	USB_INT_EP1_OUT		0x01			/* USB端点1的OUT */
#define	USB_INT_EP1_IN		0x09			/* USB端点1的IN */
#define	USB_INT_EP2_OUT		0x02			/* USB端点2的OUT */
#define	USB_INT_EP2_IN		0x0A			/* USB端点2的IN */
    /* USB_INT_BUS_RESET	0x0000XX11B */		/* USB总线复位 */
#define	USB_INT_BUS_RESET1	0x03			/* USB总线复位 */
#define	USB_INT_BUS_RESET2	0x07			/* USB总线复位 */
#define	USB_INT_BUS_RESET3	0x0B			/* USB总线复位 */
#define	USB_INT_BUS_RESET4	0x0F			/* USB总线复位 */

#endif

    /* 以下状态代码2XH-3XH用于USB主机方式的通讯失败代码 */
    /*   位7-位6为00 */
    /*   位5为1 */
    /*   位4指示当前接收的数据包是否同步 */
    /*   位3-位0指示导致通讯失败时USB设备的应答: 0010=ACK, 1010=NAK, 1110=STALL, 0011=DATA0, 1011=DATA1, XX00=超时 */
    /* USB_INT_RET_ACK	0x001X0010B */			/* 错误:对于IN事务返回ACK */
    /* USB_INT_RET_NAK	0x001X1010B */			/* 错误:返回NAK */
    /* USB_INT_RET_STALL	0x001X1110B */		/* 错误:返回STALL */
    /* USB_INT_RET_DATA0	0x001X0011B */		/* 错误:对于OUT/SETUP事务返回DATA0 */
    /* USB_INT_RET_DATA1	0x001X1011B */		/* 错误:对于OUT/SETUP事务返回DATA1 */
    /* USB_INT_RET_TOUT	0x001XXX00B */			/* 错误:返回超时 */
    /* USB_INT_RET_TOGX	0x0010X011B */			/* 错误:对于IN事务返回数据不同步 */
    /* USB_INT_RET_PID	0x001XXXXXB */			/* 错误:未定义 */

    /* 以下状态代码1XH用于USB主机方式的操作状态代码 */
#ifndef	USB_INT_SUCCESS
#define	USB_INT_SUCCESS		0x14			/* USB事务或者传输操作成功 */
#define	USB_INT_CONNECT		0x15			/* 检测到USB设备连接事件, 可能是新连接或者断开后重新连接 */
#define	USB_INT_DISCONNECT	0x16			/* 检测到USB设备断开事件 */
#define	USB_INT_BUF_OVER	0x17			/* USB传输的数据有误或者数据太多缓冲区溢出 */
#define	USB_INT_USB_READY	0x18			/* USB设备已经被初始化(已经分配USB地址) */
#define	USB_INT_DISK_READ	0x1D			/* USB存储器请求数据读出 */
#define	USB_INT_DISK_WRITE	0x1E			/* USB存储器请求数据写入 */
#define	USB_INT_DISK_ERR	0x1F			/* USB存储器操作失败 */
#endif

    /* 以下状态代码用于主机文件模式下的文件系统错误码 */
#ifndef	ERR_DISK_DISCON
#define	ERR_DISK_DISCON		0x82			/* 磁盘尚未连接,可能磁盘已经断开 */
#define	ERR_LARGE_SECTOR	0x84			/* 磁盘的扇区太大,只支持每扇区512字节 */
#define	ERR_TYPE_ERROR		0x92			/* 磁盘分区类型不支持,只支持FAT12/FAT16/BigDOS/FAT32,需要由磁盘管理工具重新分区 */
#define	ERR_BPB_ERROR		0xA1			/* 磁盘尚未格式化,或者参数错误,需要由WINDOWS采用默认参数重新格式化 */
#define	ERR_DISK_FULL		0xB1			/* 磁盘文件太满,剩余空间太少或者已经没有,需要磁盘整理 */
#define	ERR_FDT_OVER		0xB2			/* 目录(文件夹)内文件太多,没有空闲的目录项,FAT12/FAT16根目录下的文件数应该少于512个,需要磁盘整理 */
#define	ERR_FILE_CLOSE		0xB4			/* 文件已经关闭,如果需要使用,应该重新打开文件 */
#define	ERR_OPEN_DIR		0x41			/* 指定路径的目录(文件夹)被打开 */
#define	ERR_MISS_FILE		0x42			/* 指定路径的文件没有找到,可能是文件名称错误 */
#define	ERR_FOUND_NAME		0x43			/* 搜索到相匹配的文件名,或者是要求打开目录(文件夹)而实际结果却打开了文件 */
    /* 以下文件系统错误码用于文件系统子程序 */
#define	ERR_MISS_DIR		0xB3			/* 指定路径的某个子目录(文件夹)没有找到,可能是目录名称错误 */
#define	ERR_LONG_BUF_OVER	0x48			/* 长文件缓冲区溢出 */
#define	ERR_LONG_NAME_ERR	0x49			/* 短文件名没有对应的长文件名或者长文件名错误 */
#define	ERR_NAME_EXIST		0x4A			/* 同名的短文件已经存在,建议重新生成另外一个短文件名 */
//
//! additional USB acknowledge status
//! Unknow error which should not happen, may be caused by hardware or software fail
//
#define		ERR_USB_UNKNOWN		0xFA
#endif

    /* ********************************************************************************************************************* */
    /* 以下状态代码用于主机文件模式下的磁盘及文件状态, VAR_DISK_STATUS */
#ifndef	DEF_DISK_UNKNOWN
#define	DEF_DISK_UNKNOWN	0x00			/* 尚未初始化,未知状态 */
#define	DEF_DISK_DISCONN	0x01			/* 磁盘没有连接或者已经断开 */
#define	DEF_DISK_CONNECT	0x02			/* 磁盘已经连接,但是尚未初始化或者无法识别该磁盘 */
#define	DEF_DISK_MOUNTED	0x03			/* 磁盘已经初始化成功,但是尚未分析文件系统或者文件系统不支持 */
#define	DEF_DISK_READY		0x10			/* 已经分析磁盘的文件系统并且能够支持 */
#define	DEF_DISK_OPEN_ROOT	0x12			/* 已经打开根目录,使用后必须关闭,注意FAT12/FAT16根目录是固定长度 */
#define	DEF_DISK_OPEN_DIR	0x13			/* 已经打开子目录(文件夹) */
#define	DEF_DISK_OPEN_FILE	0x14			/* 已经打开文件 */
#endif

    /* ********************************************************************************************************************* */
    /* 文件系统常用定义 */

#ifndef	DEF_SECTOR_SIZE
#define	DEF_SECTOR_SIZE		512				/* U盘或者SD卡默认的物理扇区的大小 */
#endif

#ifndef	DEF_WILDCARD_CHAR
#define	DEF_WILDCARD_CHAR	0x2A			/* 路径名的通配符 '*' */
#define	DEF_SEPAR_CHAR1		0x5C			/* 路径名的分隔符 '\' */
#define	DEF_SEPAR_CHAR2		0x2F			/* 路径名的分隔符 '/' */
#define	DEF_FILE_YEAR		2004			/* 默认文件日期: 2004年 */
#define	DEF_FILE_MONTH		1				/* 默认文件日期: 1月 */
#define	DEF_FILE_DATE		1				/* 默认文件日期: 1日 */
#endif

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CH376_FileSystem_Data_Structure_Define
//! @{
//
//*****************************************************************************
#ifndef	ATTR_DIRECTORY

    /* FAT数据区中文件目录信息 */
    typedef struct _FAT_DIR_INFO
    {
        UINT8	DIR_Name[11];					/* 00H,文件名,共11字节,不足处填空格 */
        UINT8	DIR_Attr;						/* 0BH,文件属性,参考后面的说明 */
        UINT8	DIR_NTRes;						/* 0CH */
        UINT8	DIR_CrtTimeTenth;				/* 0DH,文件创建的时间,以0.1秒单位计数 */
        UINT16	DIR_CrtTime;					/* 0EH,文件创建的时间 */
        UINT16	DIR_CrtDate;					/* 10H,文件创建的日期 */
        UINT16	DIR_LstAccDate;					/* 12H,最近一次存取操作的日期 */
        UINT16	DIR_FstClusHI;					/* 14H */
        UINT16	DIR_WrtTime;					/* 16H,文件修改时间,参考前面的宏MAKE_FILE_TIME */
        UINT16	DIR_WrtDate;					/* 18H,文件修改日期,参考前面的宏MAKE_FILE_DATE */
        UINT16	DIR_FstClusLO;					/* 1AH */
        UINT32	DIR_FileSize;					/* 1CH,文件长度 */
    } FAT_DIR_INFO, *P_FAT_DIR_INFO;			/* 20H */

    /* 文件属性 */
#define ATTR_READ_ONLY			0x01		/* 文件为只读属性 */
#define ATTR_HIDDEN				0x02		/* 文件为隐含属性 */
#define ATTR_SYSTEM				0x04		/* 文件为系统属性 */
#define ATTR_VOLUME_ID			0x08		/* 卷标 */
#define ATTR_DIRECTORY			0x10		/* 子目录(文件夹) */
#define ATTR_ARCHIVE			0x20		/* 文件为存档属性 */
#define ATTR_LONG_NAME			( ATTR_READ_ONLY | ATTR_HIDDEN | ATTR_SYSTEM | ATTR_VOLUME_ID )	/* 长文件名属性 */
#define ATTR_LONG_NAME_MASK		( ATTR_LONG_NAME | ATTR_DIRECTORY | ATTR_ARCHIVE )
    /* 文件属性 UINT8 */
    /* bit0 bit1 bit2 bit3 bit4 bit5 bit6 bit7 */
    /*  只   隐   系   卷   目   存   未定义   */
    /*  读   藏   统   标   录   档            */
    /* 文件时间 UINT16 */
    /* Time = (Hour<<11) + (Minute<<5) + (Second>>1) */
#define MAKE_FILE_TIME( h, m, s )	( (h<<11) + (m<<5) + (s>>1) )	/* 生成指定时分秒的文件时间数据 */
    /* 文件日期 UINT16 */
    /* Date = ((Year-1980)<<9) + (Month<<5) + Day */
#define MAKE_FILE_DATE( y, m, d )	( ((y-1980)<<9) + (m<<5) + d )	/* 生成指定年月日的文件日期数据 */

#define LONE_NAME_MAX_CHAR		(255*2)		/* 长文件名最多字符数/字节数 */
#define LONG_NAME_PER_DIR		(13*2)		/* 长文件名在每个文件目录信息结构中的字符数/字节数 */

#endif

/* SCSI命令和数据输入输出结构 */

#ifndef	SPC_CMD_INQUIRY

    /* SCSI命令码 */
#define SPC_CMD_INQUIRY			0x12
#define SPC_CMD_READ_CAPACITY	0x25
#define SPC_CMD_READ10			0x28
#define SPC_CMD_WRITE10			0x2A
#define SPC_CMD_TEST_READY		0x00
#define SPC_CMD_REQUEST_SENSE	0x03
#define SPC_CMD_MODESENSE6		0x1A
#define SPC_CMD_MODESENSE10		0x5A
#define SPC_CMD_START_STOP		0x1B

    /* BulkOnly协议的命令块 */
    typedef struct _BULK_ONLY_CBW
    {
        UINT32	CBW_Sig;
        UINT32	CBW_Tag;
        UINT8	CBW_DataLen0;					/* 08H,输入: 数据传输长度,对于输入数据其有效值是0到48,对于输出数据其有效值为0到33 */
        UINT8	CBW_DataLen1;
        UINT16	CBW_DataLen2;
        UINT8	CBW_Flag;						/* 0CH,输入: 传输方向等标志,位7为1则输入数据,位为0则输出数据或者没有数据 */
        UINT8	CBW_LUN;
        UINT8	CBW_CB_Len;						/* 0EH,输入: 命令块的长度,有效值是1到16 */
        UINT8	CBW_CB_Buf[16];					/* 0FH,输入: 命令块,该缓冲区最多为16个字节 */
    } BULK_ONLY_CBW, *P_BULK_ONLY_CBW;			/* BulkOnly协议的命令块, 输入CBW结构 */

    /* INQUIRY命令的返回数据 */
    typedef struct _INQUIRY_DATA
    {
        UINT8	DeviceType;					/* 00H, 设备类型 */
        UINT8	RemovableMedia;				/* 01H, 位7为1说明是移动存储 */
        UINT8	Versions;					/* 02H, 协议版本 */
        UINT8	DataFormatAndEtc;			/* 03H, 指定返回数据格式 */
        UINT8	AdditionalLength;			/* 04H, 后续数据的长度 */
        UINT8	Reserved1;
        UINT8	Reserved2;
        UINT8	MiscFlag;					/* 07H, 一些控制标志 */
        UINT8	VendorIdStr[8];				/* 08H, 厂商信息 */
        UINT8	ProductIdStr[16];			/* 10H, 产品信息 */
        UINT8	ProductRevStr[4];			/* 20H, 产品版本 */
    } INQUIRY_DATA, *P_INQUIRY_DATA;		/* 24H */

    /* REQUEST SENSE命令的返回数据 */
    typedef struct _SENSE_DATA
    {
        UINT8	ErrorCode;					/* 00H, 错误代码及有效位 */
        UINT8	SegmentNumber;
        UINT8	SenseKeyAndEtc;				/* 02H, 主键码 */
        UINT8	Information0;
        UINT8	Information1;
        UINT8	Information2;
        UINT8	Information3;
        UINT8	AdditSenseLen;				/* 07H, 后续数据的长度 */
        UINT8	CmdSpecInfo[4];
        UINT8	AdditSenseCode;				/* 0CH, 附加键码 */
        UINT8	AddSenCodeQual;				/* 0DH, 详细的附加键码 */
        UINT8	FieldReplaUnit;
        UINT8	SenseKeySpec[3];
    } SENSE_DATA, *P_SENSE_DATA;			/* 12H */

#endif

/* 主机文件模式下的数据输入和输出结构 */

#ifndef	MAX_FILE_NAME_LEN

#define MAX_FILE_NAME_LEN		(13+1)		/* 文件名最大长度,最大长度是1个根目录符+8个主文件名+1个小数点+3个类型名+结束符=14 */

    /* 命令的输入数据和输出数据 */
    typedef union _CH376_CMD_DATA
    {
        struct
        {
            UINT8	mBuffer[ MAX_FILE_NAME_LEN ];
        } Default;

        INQUIRY_DATA	DiskMountInq;			/* 返回: INQUIRY命令的返回数据 */
        /* CMD0H_DISK_MOUNT: 初始化磁盘并测试磁盘是否就绪,首次执行时 */

        FAT_DIR_INFO	OpenDirInfo;			/* 返回: 枚举到的文件目录信息 */
        /* CMD0H_FILE_OPEN: 枚举文件和目录(文件夹) */

        FAT_DIR_INFO	EnumDirInfo;			/* 返回: 枚举到的文件目录信息 */
        /* CMD0H_FILE_ENUM_GO: 继续枚举文件和目录(文件夹) */

        struct
        {
            UINT8	mUpdateFileSz;				/* 输入参数: 是否允许更新文件长度, 0则禁止更新长度 */
        } FileCLose;							/* CMD1H_FILE_CLOSE: 关闭当前已经打开的文件 */

        struct
        {
            UINT8	mDirInfoIndex;				/* 输入参数: 指定需要读取的目录信息结构在扇区内的索引号, 0FFH则为当前已经打开的文件 */
        } DirInfoRead;							/* CMD1H_DIR_INFO_READ: 读取文件的目录信息 */

        union
        {
            UINT32	mByteOffset;				/* 输入参数: 偏移字节数,以字节为单位的偏移量(总长度32位,低字节在前) */
            UINT32	mSectorLba;					/* 返回: 当前文件指针对应的绝对线性扇区号,0FFFFFFFFH则已到文件尾(总长度32位,低字节在前) */
        } ByteLocate;							/* CMD4H_BYTE_LOCATE: 以字节为单位移动当前文件指针 */

        struct
        {
            UINT16	mByteCount;					/* 输入参数: 请求读取的字节数(总长度16位,低字节在前) */
        } ByteRead;								/* CMD2H_BYTE_READ: 以字节为单位从当前位置读取数据块 */

        struct
        {
            UINT16	mByteCount;					/* 输入参数: 请求写入的字节数(总长度16位,低字节在前) */
        } ByteWrite;							/* CMD2H_BYTE_WRITE: 以字节为单位向当前位置写入数据块 */

        union
        {
            UINT32	mSectorOffset;				/* 输入参数: 偏移扇区数,以扇区为单位的偏移量(总长度32位,低字节在前) */
            UINT32	mSectorLba;					/* 返回: 当前文件指针对应的绝对线性扇区号,0FFFFFFFFH则已到文件尾(总长度32位,低字节在前) */
        } SectorLocate;							/* CMD4H_SEC_LOCATE: 以扇区为单位移动当前文件指针 */

        struct
        {
            UINT8	mSectorCount;				/* 输入参数: 请求读取的扇区数 */
            /* 返回: 允许读取的扇区数 */
            UINT8	mReserved1;
            UINT8	mReserved2;
            UINT8	mReserved3;
            UINT32	mStartSector;				/* 返回: 允许读取的扇区块的起始绝对线性扇区号(总长度32位,低字节在前) */
        } SectorRead;							/* CMD1H_SEC_READ: 以扇区为单位从当前位置读取数据块 */

        struct
        {
            UINT8	mSectorCount;				/* 输入参数: 请求写入的扇区数 */
            /* 返回: 允许写入的扇区数 */
            UINT8	mReserved1;
            UINT8	mReserved2;
            UINT8	mReserved3;
            UINT32	mStartSector;				/* 返回: 允许写入的扇区块的起始绝对线性扇区号(总长度32位,低字节在前) */
        } SectorWrite;							/* CMD1H_SEC_WRITE: 以扇区为单位在当前位置写入数据块 */

        struct
        {
            UINT32	mDiskSizeSec;				/* 返回: 整个物理磁盘的总扇区数(总长度32位,低字节在前) */
        } DiskCapacity;							/* CMD0H_DISK_CAPACITY: 查询磁盘物理容量 */

        struct
        {
            UINT32	mTotalSector;				/* 返回: 当前逻辑盘的总扇区数(总长度32位,低字节在前) */
            UINT32	mFreeSector;				/* 返回: 当前逻辑盘的剩余扇区数(总长度32位,低字节在前) */
            UINT8	mDiskFat;					/* 返回: 当前逻辑盘的FAT类型,1-FAT12,2-FAT16,3-FAT32 */
        } DiskQuery;							/* CMD_DiskQuery, 查询磁盘信息 */

        BULK_ONLY_CBW	DiskBocCbw;				/* 输入参数: CBW命令结构 */
        /* CMD0H_DISK_BOC_CMD: 对USB存储器执行BulkOnly传输协议的命令 */

        struct
        {
            UINT8	mMaxLogicUnit;				/* 返回: USB存储器的最大逻辑单元号 */
        } DiskMaxLun;							/* CMD0H_DISK_MAX_LUN: 控制传输-获取USB存储器最大逻辑单元号 */

        INQUIRY_DATA	DiskInitInq;			/* 返回: INQUIRY命令的返回数据 */
        /* CMD0H_DISK_INIT: 初始化USB存储器 */

        INQUIRY_DATA	DiskInqData;			/* 返回: INQUIRY命令的返回数据 */
        /* CMD0H_DISK_INQUIRY: 查询USB存储器特性 */

        SENSE_DATA		ReqSenseData;			/* 返回: REQUEST SENSE命令的返回数据 */
        /* CMD0H_DISK_R_SENSE: 检查USB存储器错误 */

        struct
        {
            UINT32	mDiskSizeSec;				/* 返回: 整个物理磁盘的总扇区数(总长度32位,高字节在前) */
        } DiskSize;								/* CMD0H_DISK_SIZE: 获取USB存储器的容量 */

        struct
        {
            UINT32	mStartSector;				/* 输入参数: LBA扇区地址(总长度32位,低字节在前) */
            UINT8	mSectorCount;				/* 输入参数: 请求读取的扇区数 */
        } DiskRead;								/* CMD5H_DISK_READ: 从USB存储器读数据块(以扇区为单位) */

        struct
        {
            UINT32	mStartSector;				/* 输入参数: LBA扇区地址(总长度32位,低字节在前) */
            UINT8	mSectorCount;				/* 输入参数: 请求写入的扇区数 */
        } DiskWrite;							/* CMD5H_DISK_WRITE: 向USB存储器写数据块(以扇区为单位) */
    } CH376_CMD_DATA, *P_CH376_CMD_DATA;

#endif

    /* ********************************************************************************************************************* */
    /* 主机文件模式下的文件系统变量的地址 */

#ifndef	VAR_FILE_SIZE

    /* 8位/单字节变量 */
#define	VAR_SYS_BASE_INFO	0x20			/* 当前系统的基本信息 */
    /*           位6用于指示USB存储设备的子类别SubClass-Code, 位6为0则说明子类别为6, 位6为1则说明子类别是非6的其它值 */
    /*           位5用于指示USB设备方式下的USB配置状态和USB主机方式下的USB设备连接状态 */
    /*                USB设备方式下, 位5为1则USB配置完成, 位5位0则尚未配置 */
    /*                USB主机方式下, 位5为1则USB端口存在USB设备, 位5位0则USB端口没有USB设备 */
    /*           位4用于指示USB设备方式下的缓冲区锁定状态, 位4为1则说明USB缓冲区处于锁定状态, 位6为1则说明已经释放 */
    /*           其它位, 保留,请勿修改 */
#define	VAR_RETRY_TIMES		0x25			/* USB事务操作的重试次数 */
    /*           位7为0则收到NAK时不重试, 位7为1位6为0则收到NAK时无限重试(可以用CMD_ABORT_NAK命令放弃重试), 位7为1位6为1则收到NAK时最多重试3秒 */
    /*           位5~位0为超时后的重试次数 */
#define	VAR_FILE_BIT_FLAG	0x26			/* 主机文件模式下的位标志 */
    /*           位1和位0, 逻辑盘的FAT文件系统标志, 00-FAT12, 01-FAT16, 10-FAT32, 11-非法 */
    /*           位2, 当前缓冲区中的FAT表数据是否被修改标志, 0-未修改, 1-已修改 */
    /*           位3, 文件长度需要修改标志, 当前文件被追加数据, 0-未追加无需修改, 1-已追加需要修改 */
    /*           其它位, 保留,请勿修改 */
#define	VAR_DISK_STATUS		0x2B			/* 主机文件模式下的磁盘及文件状态 */
#define	VAR_SD_BIT_FLAG		0x30			/* 主机文件模式下SD卡的位标志 */
    /*           位0, SD卡版本, 0-只支持SD第一版,1-支持SD第二版 */
    /*           位1, 自动识别, 0-SD卡, 1-MMC卡 */
    /*           位2, 自动识别, 0-标准容量SD卡, 1-大容量SD卡(HC-SD) */
    /*           位4, ACMD41命令超时 */
    /*           位5, CMD1命令超时 */
    /*           位6, CMD58命令超时 */
    /*           其它位, 保留,请勿修改 */
#define	VAR_UDISK_TOGGLE	0x31			/* USB存储设备的BULK-IN/BULK-OUT端点的同步标志 */
    /*           位7, Bulk-In端点的同步标志 */
    /*           位6, Bulk-In端点的同步标志 */
    /*           位5~位0, 必须为0 */
#define	VAR_UDISK_LUN		0x34			/* USB存储设备的逻辑单元号 */
    /*           位7~位4, USB存储设备的当前逻辑单元号,CH376初始化USB存储设备后,默认是访问0#逻辑单元 */
    /*           位3~位0, USB存储设备的最大逻辑单元号,加1后等于逻辑单元数 */
#define	VAR_SEC_PER_CLUS	0x38			/* 逻辑盘的每簇扇区数 */
#define	VAR_FILE_DIR_INDEX	0x3B			/* 当前文件目录信息在扇区内的索引号 */
#define	VAR_CLUS_SEC_OFS	0x3C			/* 当前文件指针在簇内的扇区偏移,为0xFF则指向文件末尾,簇结束 */

    /* 32位/4字节变量 */
#define	VAR_DISK_ROOT		0x44			/* 对于FAT16盘为根目录占用扇区数,对于FAT32盘为根目录起始簇号(总长度32位,低字节在前) */
#define	VAR_DSK_TOTAL_CLUS	0x48			/* 逻辑盘的总簇数(总长度32位,低字节在前) */
#define	VAR_DSK_START_LBA	0x4C			/* 逻辑盘的起始绝对扇区号LBA(总长度32位,低字节在前) */
#define	VAR_DSK_DAT_START	0x50			/* 逻辑盘的数据区域的起始LBA(总长度32位,低字节在前) */
#define	VAR_LBA_BUFFER		0x54			/* 当前磁盘数据缓冲区的数据对应的LBA(总长度32位,低字节在前) */
#define	VAR_LBA_CURRENT		0x58			/* 当前读写的磁盘起始LBA地址(总长度32位,低字节在前) */
#define	VAR_FAT_DIR_LBA		0x5C			/* 当前文件目录信息所在的扇区LBA地址(总长度32位,低字节在前) */
#define	VAR_START_CLUSTER	0x60			/* 当前文件或者目录(文件夹)的起始簇号(总长度32位,低字节在前) */
#define	VAR_CURRENT_CLUST	0x64			/* 当前文件的当前簇号(总长度32位,低字节在前) */
#define	VAR_FILE_SIZE		0x68			/* 当前文件的长度(总长度32位,低字节在前) */
#define	VAR_CURRENT_OFFSET	0x6C			/* 当前文件指针,当前读写位置的字节偏移(总长度32位,低字节在前) */

#endif
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CH376_USB_CMD
//! \brief Frequently used USB command of CH376
//! @{
//
//*****************************************************************************
    /* USB的包标识PID, 主机方式可能用到 */
#ifndef	DEF_USB_PID_SETUP
#define	DEF_USB_PID_NULL	0x00			/* 保留PID, 未定义 */
#define	DEF_USB_PID_SOF		0x05
#define	DEF_USB_PID_SETUP	0x0D
#define	DEF_USB_PID_IN		0x09
#define	DEF_USB_PID_OUT		0x01
#define	DEF_USB_PID_ACK		0x02
#define	DEF_USB_PID_NAK		0x0A
#define	DEF_USB_PID_STALL	0x0E
#define	DEF_USB_PID_DATA0	0x03
#define	DEF_USB_PID_DATA1	0x0B
#define	DEF_USB_PID_PRE		0x0C
#endif

    /* USB请求类型, 外置固件模式可能用到 */
#ifndef	DEF_USB_REQ_TYPE
#define	DEF_USB_REQ_READ	0x80			/* 控制读操作 */
#define	DEF_USB_REQ_WRITE	0x00			/* 控制写操作 */
#define	DEF_USB_REQ_TYPE	0x60			/* 控制请求类型 */
#define	DEF_USB_REQ_STAND	0x00			/* 标准请求 */
#define	DEF_USB_REQ_CLASS	0x20			/* 设备类请求 */
#define	DEF_USB_REQ_VENDOR	0x40			/* 厂商请求 */
#define	DEF_USB_REQ_RESERVE	0x60			/* 保留请求 */
#endif

    /* USB标准设备请求, RequestType的位6位5=00(Standard), 外置固件模式可能用到 */
#ifndef	DEF_USB_GET_DESCR
#define	DEF_USB_CLR_FEATURE	0x01
#define	DEF_USB_SET_FEATURE	0x03
#define	DEF_USB_GET_STATUS	0x00
#define	DEF_USB_SET_ADDRESS	0x05
#define	DEF_USB_GET_DESCR	0x06
#define	DEF_USB_SET_DESCR	0x07
#define	DEF_USB_GET_CONFIG	0x08
#define	DEF_USB_SET_CONFIG	0x09
#define	DEF_USB_GET_INTERF	0x0A
#define	DEF_USB_SET_INTERF	0x0B
#define	DEF_USB_SYNC_FRAME	0x0C
#endif

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
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
