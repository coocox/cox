/* CH376芯片 文件系统层 V1.2 */
/* 提供文件系统常用子程序,提供命令打包 */
/* 不使用的子程序可以注释掉,从而节约单片机的程序ROM空间和数据RAM空间 */
/* 这里的子程序是通过括号中的变量传递参数,如果参数较多,为了节约RAM,也可以参考CH375子程序库改成通过同一全局变量/联合结构CH376_CMD_DATA传递 */

/* name 参数是指短文件名, 可以包括根目录符, 但不含有路径分隔符, 总长度不超过1+8+1+3+1字节 */
/* PathName 参数是指全路径的短文件名, 包括根目录符、多级子目录及路径分隔符、文件名/目录名 */
/* LongName 参数是指长文件名, 以UNICODE小端顺序编码, 以两个0字节结束, 使用长文件名子程序必须先定义全局缓冲区GlobalBuf, 长度不小于64字节, 可以与其它子程序共用 */

/* 定义 NO_DEFAULT_CH376_INT 用于禁止默认的Wait376Interrupt子程序,禁止后,应用程序必须自行定义一个同名子程序 */
/* 定义 DEF_INT_TIMEOUT 用于设置默认的Wait376Interrupt子程序中的等待中断的超时时间/循环计数值, 0则不检查超时而一直等待 */
/* 定义 EN_DIR_CREATE 用于提供新建多级子目录的子程序,默认是不提供 */
/* 定义 EN_DISK_QUERY 用于提供磁盘容量查询和剩余空间查询的子程序,默认是不提供 */
/* 定义 EN_SECTOR_ACCESS 用于提供以扇区为单位读写文件的子程序,默认是不提供 */
/* 定义 EN_LONG_NAME 用于提供支持长文件名的子程序,默认是不提供 */
/* 定义 DEF_IC_V43_U 用于去掉支持低版本的程序代码,仅支持V4.3及以上版本的CH376芯片,默认是支持低版本 */

#include	"xhw_CH376INC.H"
#include        "CH376.H"
#include	"CH376_FS.H"

UINT8	CH376ReadBlock( PUINT8 buf )  /* 从当前主机端点的接收缓冲区读取数据块,返回长度 */
{
    UINT8	s, l;
    xWriteCH376Cmd( CMD01_RD_USB_DATA0 );
    s = l = xReadCH376Data( );  /* 长度 */
    if ( l )
    {
        do
        {
            *buf = xReadCH376Data( );
            buf ++;
        }
        while ( -- l );
    }
    xEndCH376Cmd( );
    return( s );
}

UINT8	CH376WriteReqBlock( PUINT8 buf )  /* 向内部指定缓冲区写入请求的数据块,返回长度 */
{
    UINT8	s, l;
    xWriteCH376Cmd( CMD01_WR_REQ_DATA );
    s = l = xReadCH376Data( );  /* 长度 */
    if ( l )
    {
        do
        {
            xWriteCH376Data( *buf );
            buf ++;
        }
        while ( -- l );
    }
    xEndCH376Cmd( );
    return( s );
}

void	CH376WriteHostBlock( PUINT8 buf, UINT8 len )  /* 向USB主机端点的发送缓冲区写入数据块 */
{
    xWriteCH376Cmd( CMD10_WR_HOST_DATA );
    xWriteCH376Data( len );  /* 长度 */
    if ( len )
    {
        do
        {
            xWriteCH376Data( *buf );
            buf ++;
        }
        while ( -- len );
    }
    xEndCH376Cmd( );
}

void	CH376WriteOfsBlock( PUINT8 buf, UINT8 ofs, UINT8 len )  /* 向内部缓冲区指定偏移地址写入数据块 */
{
    xWriteCH376Cmd( CMD20_WR_OFS_DATA );
    xWriteCH376Data( ofs );  /* 偏移地址 */
    xWriteCH376Data( len );  /* 长度 */
    if ( len )
    {
        do
        {
            xWriteCH376Data( *buf );
            buf ++;
        }
        while ( -- len );
    }
    xEndCH376Cmd( );
}

void	CH376SetFileName( PUINT8 name )  /* 设置将要操作的文件的文件名 */
{
    /*	UINT8	i;*/
    UINT8	c;
#ifndef	DEF_IC_V43_U
    UINT8	s;
    xWriteCH376Cmd( CMD01_GET_IC_VER );
    if ( xReadCH376Data( ) < 0x43 )
    {
        if ( CH376ReadVar8( VAR_DISK_STATUS ) < DEF_DISK_READY )
        {
            xWriteCH376Cmd( CMD10_SET_FILE_NAME );
            xWriteCH376Data( 0 );
            s = CH376SendCmdWaitInt( CMD0H_FILE_OPEN );
            if ( s == USB_INT_SUCCESS )
            {
                s = CH376ReadVar8( 0xCF );
                if ( s )
                {
                    CH376WriteVar32( 0x4C, CH376ReadVar32( 0x4C ) + ( (UINT16)s << 8 ) );
                    CH376WriteVar32( 0x50, CH376ReadVar32( 0x50 ) + ( (UINT16)s << 8 ) );
                    CH376WriteVar32( 0x70, 0 );
                }
            }
        }
    }
#endif
    xWriteCH376Cmd( CMD10_SET_FILE_NAME );
    c = *name;
    xWriteCH376Data( c );
    while ( c )
    {
        name ++;
        c = *name;
        if ( c == DEF_SEPAR_CHAR1 || c == DEF_SEPAR_CHAR2 ) c = 0;  /* 强行将文件名截止 */
        xWriteCH376Data( c );
    }
    xEndCH376Cmd( );
}

UINT32	CH376Read32bitDat( void )  /* 从CH376芯片读取32位的数据并结束命令 */
{
    UINT8	c0, c1, c2, c3;
    c0 = xReadCH376Data( );
    c1 = xReadCH376Data( );
    c2 = xReadCH376Data( );
    c3 = xReadCH376Data( );
    xEndCH376Cmd( );
    return( c0 | (UINT16)c1 << 8 | (UINT32)c2 << 16 | (UINT32)c3 << 24 );
}

UINT8	CH376ReadVar8( UINT8 var )  /* 读CH376芯片内部的8位变量 */
{
    UINT8	c0;
    xWriteCH376Cmd( CMD11_READ_VAR8 );
    xWriteCH376Data( var );
    c0 = xReadCH376Data( );
    xEndCH376Cmd( );
    return( c0 );
}

void	CH376WriteVar8( UINT8 var, UINT8 dat )  /* 写CH376芯片内部的8位变量 */
{
    xWriteCH376Cmd( CMD20_WRITE_VAR8 );
    xWriteCH376Data( var );
    xWriteCH376Data( dat );
    xEndCH376Cmd( );
}

UINT32	CH376ReadVar32( UINT8 var )  /* 读CH376芯片内部的32位变量 */
{
    xWriteCH376Cmd( CMD14_READ_VAR32 );
    xWriteCH376Data( var );
    return( CH376Read32bitDat( ) );  /* 从CH376芯片读取32位的数据并结束命令 */
}

void	CH376WriteVar32( UINT8 var, UINT32 dat )  /* 写CH376芯片内部的32位变量 */
{
    xWriteCH376Cmd( CMD50_WRITE_VAR32 );
    xWriteCH376Data( var );
    xWriteCH376Data( (UINT8)dat );
    xWriteCH376Data( (UINT8)( (UINT16)dat >> 8 ) );
    xWriteCH376Data( (UINT8)( dat >> 16 ) );
    xWriteCH376Data( (UINT8)( dat >> 24 ) );
    xEndCH376Cmd( );
}

void	CH376EndDirInfo( void )  /* 在调用CH376DirInfoRead获取FAT_DIR_INFO结构之后应该通知CH376结束 */
{
    CH376WriteVar8( 0x0D, 0x00 );
}

UINT32	CH376GetFileSize( void )  /* 读取当前文件长度 */
{
    return( CH376ReadVar32( VAR_FILE_SIZE ) );
}

UINT8	CH376GetDiskStatus( void )  /* 获取磁盘和文件系统的工作状态 */
{
    return( CH376ReadVar8( VAR_DISK_STATUS ) );
}

UINT8	CH376GetIntStatus( void )  /* 获取中断状态并取消中断请求 */
{
    UINT8	s;
    xWriteCH376Cmd( CMD01_GET_STATUS );
    s = xReadCH376Data( );
    xEndCH376Cmd( );
    return( s );
}

#ifndef	NO_DEFAULT_CH376_INT
UINT8	Wait376Interrupt( void )  /* 等待CH376中断(INT#低电平)，返回中断状态码, 超时则返回ERR_USB_UNKNOWN */
{
#ifdef	DEF_INT_TIMEOUT
#if		DEF_INT_TIMEOUT < 1
    while ( Query376Interrupt( ) == FALSE );  /* 一直等中断 */
    return( CH376GetIntStatus( ) );  /* 检测到中断 */
#else
    UINT32	i;
    for ( i = 0; i < DEF_INT_TIMEOUT; i ++ )    /* 计数防止超时 */
    {
        if ( Query376Interrupt( ) ) return( CH376GetIntStatus( ) );  /* 检测到中断 */
        /* 在等待CH376中断的过程中,可以做些需要及时处理的其它事情 */
    }
    return( ERR_USB_UNKNOWN );  /* 不应该发生的情况 */
#endif
#else
    UINT32	i;
    for ( i = 0; i < 5000000; i ++ )    /* 计数防止超时,默认的超时时间,与单片机主频有关 */
    {
        if ( Query376Interrupt( ) ) return( CH376GetIntStatus( ) );  /* 检测到中断 */
        /* 在等待CH376中断的过程中,可以做些需要及时处理的其它事情 */
    }
    return( ERR_USB_UNKNOWN );  /* 不应该发生的情况 */
#endif
}
#endif

UINT8	CH376SendCmdWaitInt( UINT8 mCmd )  /* 发出命令码后,等待中断 */
{
    xWriteCH376Cmd( mCmd );
    xEndCH376Cmd( );
    return( Wait376Interrupt( ) );
}

UINT8	CH376SendCmdDatWaitInt( UINT8 mCmd, UINT8 mDat )  /* 发出命令码和一字节数据后,等待中断 */
{
    xWriteCH376Cmd( mCmd );
    xWriteCH376Data( mDat );
    xEndCH376Cmd( );
    return( Wait376Interrupt( ) );
}

UINT8	CH376DiskReqSense( void )  /* 检查USB存储器错误 */
{
    UINT8	s;
    mDelaymS( 5 );
    s = CH376SendCmdWaitInt( CMD0H_DISK_R_SENSE );
    mDelaymS( 5 );
    return( s );
}

UINT8	CH376DiskConnect( void )  /* 检查U盘是否连接,不支持SD卡 */
{
    if ( Query376Interrupt( ) ) CH376GetIntStatus( );  /* 检测到中断 */
    return( CH376SendCmdWaitInt( CMD0H_DISK_CONNECT ) );
}

UINT8	CH376DiskMount( void )  /* 初始化磁盘并测试磁盘是否就绪 */
{
    return( CH376SendCmdWaitInt( CMD0H_DISK_MOUNT ) );
}

UINT8	CH376FileOpen( PUINT8 name )  /* 在根目录或者当前目录下打开文件或者目录(文件夹) */
{
    CH376SetFileName( name );  /* 设置将要操作的文件的文件名 */
#ifndef	DEF_IC_V43_U
    if ( name[0] == DEF_SEPAR_CHAR1 || name[0] == DEF_SEPAR_CHAR2 ) CH376WriteVar32( VAR_CURRENT_CLUST, 0 );
#endif
    return( CH376SendCmdWaitInt( CMD0H_FILE_OPEN ) );
}

UINT8	CH376FileCreate( PUINT8 name )  /* 在根目录或者当前目录下新建文件,如果文件已经存在那么先删除 */
{
    if ( name ) CH376SetFileName( name );  /* 设置将要操作的文件的文件名 */
    return( CH376SendCmdWaitInt( CMD0H_FILE_CREATE ) );
}

UINT8	CH376DirCreate( PUINT8 name )  /* 在根目录下新建目录(文件夹)并打开,如果目录已经存在那么直接打开 */
{
    CH376SetFileName( name );  /* 设置将要操作的文件的文件名 */
#ifndef	DEF_IC_V43_U
    if ( name[0] == DEF_SEPAR_CHAR1 || name[0] == DEF_SEPAR_CHAR2 ) CH376WriteVar32( VAR_CURRENT_CLUST, 0 );
#endif
    return( CH376SendCmdWaitInt( CMD0H_DIR_CREATE ) );
}

UINT8	CH376SeparatePath( PUINT8 path )  /* 从路径中分离出最后一级文件名或者目录(文件夹)名,返回最后一级文件名或者目录名的字节偏移 */
{
    PUINT8	pName;
    for ( pName = path; *pName != 0; ++ pName );  /* 到文件名字符串结束位置 */
    while ( *pName != DEF_SEPAR_CHAR1 && *pName != DEF_SEPAR_CHAR2 && pName != path ) pName --;  /*  搜索倒数第一个路径分隔符 */
    if ( pName != path ) pName ++;  /* 找到了路径分隔符,则修改指向目标文件的最后一级文件名,跳过前面的多级目录名及路径分隔符 */
    return( pName - path );
}

UINT8	CH376FileOpenDir( PUINT8 PathName, UINT8 StopName )  /* 打开多级目录下的文件或者目录的上级目录,支持多级目录路径,支持路径分隔符,路径长度不超过255个字符 */
/* StopName 指向最后一级文件名或者目录名 */
{
    UINT8	i, s;
    s = 0;
    i = 1;  /* 跳过有可能的根目录符 */
    while ( 1 )
    {
        while ( PathName[i] != DEF_SEPAR_CHAR1 && PathName[i] != DEF_SEPAR_CHAR2 && PathName[i] != 0 ) ++ i;  /* 搜索下一个路径分隔符或者路径结束符 */
        if ( PathName[i] ) i ++;  /* 找到了路径分隔符,修改指向目标文件的最后一级文件名 */
        else i = 0;  /* 路径结束 */
        s = CH376FileOpen( &PathName[s] );  /* 打开文件或者目录 */
        if ( i && i != StopName )    /* 路径尚未结束 */
        {
            if ( s != ERR_OPEN_DIR )    /* 因为是逐级打开,尚未到路径结束,所以,如果不是成功打开了目录,那么说明有问题 */
            {
                if ( s == USB_INT_SUCCESS ) return( ERR_FOUND_NAME );  /* 中间路径必须是目录名,如果是文件名则出错 */
                else if ( s == ERR_MISS_FILE ) return( ERR_MISS_DIR );  /* 中间路径的某个子目录没有找到,可能是目录名称错误 */
                else return( s );  /* 操作出错 */
            }
            s = i;  /* 从下一级目录开始继续 */
        }
        else return( s );  /* 路径结束,USB_INT_SUCCESS为成功打开文件,ERR_OPEN_DIR为成功打开目录(文件夹),其它为操作出错 */
    }
}

UINT8	CH376FileOpenPath( PUINT8 PathName )  /* 打开多级目录下的文件或者目录(文件夹),支持多级目录路径,支持路径分隔符,路径长度不超过255个字符 */
{
    return( CH376FileOpenDir( PathName, 0xFF ) );
}

UINT8	CH376FileCreatePath( PUINT8 PathName )  /* 新建多级目录下的文件,支持多级目录路径,支持路径分隔符,路径长度不超过255个字符 */
{
    UINT8	s;
    UINT8	Name;
    Name = CH376SeparatePath( PathName );  /* 从路径中分离出最后一级文件名,返回最后一级文件名的偏移 */
    if ( Name )    /* 是多级目录 */
    {
        s = CH376FileOpenDir( PathName, Name );  /* 打开多级目录下的最后一级目录,即打开新建文件的上级目录 */
        if ( s != ERR_OPEN_DIR )    /* 因为是打开上级目录,所以,如果不是成功打开了目录,那么说明有问题 */
        {
            if ( s == USB_INT_SUCCESS ) return( ERR_FOUND_NAME );  /* 中间路径必须是目录名,如果是文件名则出错 */
            else if ( s == ERR_MISS_FILE ) return( ERR_MISS_DIR );  /* 中间路径的某个子目录没有找到,可能是目录名称错误 */
            else return( s );  /* 操作出错 */
        }
    }
    return( CH376FileCreate( &PathName[Name] ) );  /* 在根目录或者当前目录下新建文件 */
}

#ifdef	EN_DIR_CREATE
UINT8	CH376DirCreatePath( PUINT8 PathName )  /* 新建多级目录下的目录(文件夹)并打开,支持多级目录路径,支持路径分隔符,路径长度不超过255个字符 */
{
    UINT8	s;
    UINT8	Name;
    UINT8	ClustBuf[4];
    Name = CH376SeparatePath( PathName );  /* 从路径中分离出最后一级目录名,返回最后一级文件名的偏移 */
    if ( Name )    /* 是多级目录 */
    {
        s = CH376FileOpenDir( PathName, Name );  /* 打开多级目录下的最后一级目录,即打开新建目录的上级目录 */
        if ( s != ERR_OPEN_DIR )    /* 因为是打开上级目录,所以,如果不是成功打开了目录,那么说明有问题 */
        {
            if ( s == USB_INT_SUCCESS ) return( ERR_FOUND_NAME );  /* 中间路径必须是目录名,如果是文件名则出错 */
            else if ( s == ERR_MISS_FILE ) return( ERR_MISS_DIR );  /* 中间路径的某个子目录没有找到,可能是目录名称错误 */
            else return( s );  /* 操作出错 */
        }
        xWriteCH376Cmd( CMD14_READ_VAR32 );
        xWriteCH376Data( VAR_START_CLUSTER );  /* 上级目录的起始簇号 */
        for ( s = 0; s != 4; s ++ ) ClustBuf[ s ] = xReadCH376Data( );
        xEndCH376Cmd( );
        s = CH376DirCreate( &PathName[Name] );  /* 在当前目录下新建目录 */
        if ( s != USB_INT_SUCCESS ) return( s );
        s = CH376ByteLocate( sizeof(FAT_DIR_INFO) + STRUCT_OFFSET( FAT_DIR_INFO, DIR_FstClusHI ) );  /* 移动文件指针 */
        if ( s != USB_INT_SUCCESS ) return( s );
        s = CH376ByteWrite( &ClustBuf[2], 2, NULL );  /* 写入上级目录的起始簇号的高16位 */
        if ( s != USB_INT_SUCCESS ) return( s );
        s = CH376ByteLocate( sizeof(FAT_DIR_INFO) + STRUCT_OFFSET( FAT_DIR_INFO, DIR_FstClusLO ) );  /* 移动文件指针 */
        if ( s != USB_INT_SUCCESS ) return( s );
        s = CH376ByteWrite( ClustBuf, 2, NULL );  /* 写入上级目录的起始簇号的低16位 */
        if ( s != USB_INT_SUCCESS ) return( s );
        s = CH376ByteLocate( 0 );  /* 移动文件指针,恢复到目录头位置 */
        if ( s != USB_INT_SUCCESS ) return( s );
    }
    else    /* 不是多级目录 */
    {
        if ( PathName[0] == DEF_SEPAR_CHAR1 || PathName[0] == DEF_SEPAR_CHAR2 ) return( CH376DirCreate( PathName ) );  /* 在根目录下新建目录 */
        else return( ERR_MISS_DIR );  /* 必须提供完整路径才能实现在当前目录下新建目录 */
    }
}
#endif

UINT8	CH376FileErase( PUINT8 PathName )  /* 删除文件,如果已经打开则直接删除,否则对于文件会先打开再删除,支持多级目录路径 */
{
    UINT8	s;
    if ( PathName )    /* 文件尚未打开 */
    {
        for ( s = 1; PathName[s] != DEF_SEPAR_CHAR1 && PathName[s] != DEF_SEPAR_CHAR2 && PathName[s] != 0; ++ s );  /* 搜索下一个路径分隔符或者路径结束符 */
        if ( PathName[s] )    /* 有路径分隔符,是多级目录下的文件或者目录 */
        {
            s = CH376FileOpenPath( PathName );  /* 打开多级目录下的文件或者目录 */
            if ( s != USB_INT_SUCCESS && s != ERR_OPEN_DIR ) return( s );  /* 操作出错 */
        }
        else CH376SetFileName( PathName );  /* 没有路径分隔符,是根目录或者当前目录下的文件或者目录,设置将要操作的文件的文件名 */
    }
    return( CH376SendCmdWaitInt( CMD0H_FILE_ERASE ) );
}

UINT8	CH376FileClose( UINT8 UpdateSz )  /* 关闭当前已经打开的文件或者目录(文件夹) */
{
    return( CH376SendCmdDatWaitInt( CMD1H_FILE_CLOSE, UpdateSz ) );
}

UINT8	CH376DirInfoRead( void )  /* 读取当前文件的目录信息 */
{
    return( CH376SendCmdDatWaitInt( CMD1H_DIR_INFO_READ, 0xFF ) );
}

UINT8	CH376DirInfoSave( void )  /* 保存文件的目录信息 */
{
    return( CH376SendCmdWaitInt( CMD0H_DIR_INFO_SAVE ) );
}

UINT8	CH376ByteLocate( UINT32 offset )  /* 以字节为单位移动当前文件指针 */
{
    xWriteCH376Cmd( CMD4H_BYTE_LOCATE );
    xWriteCH376Data( (UINT8)offset );
    xWriteCH376Data( (UINT8)((UINT16)offset >> 8) );
    xWriteCH376Data( (UINT8)(offset >> 16) );
    xWriteCH376Data( (UINT8)(offset >> 24) );
    xEndCH376Cmd( );
    return( Wait376Interrupt( ) );
}

UINT8	CH376ByteRead( PUINT8 buf, UINT16 ReqCount, PUINT16 RealCount )  /* 以字节为单位从当前位置读取数据块 */
{
    UINT8	s;
    xWriteCH376Cmd( CMD2H_BYTE_READ );
    xWriteCH376Data( (UINT8)ReqCount );
    xWriteCH376Data( (UINT8)(ReqCount >> 8) );
    xEndCH376Cmd( );
    if ( *RealCount ) *RealCount = 0;
    while ( 1 )
    {
        s = Wait376Interrupt( );
        if ( s == USB_INT_DISK_READ )
        {
            s = CH376ReadBlock( buf );  /* 从当前主机端点的接收缓冲区读取数据块,返回长度 */
            xWriteCH376Cmd( CMD0H_BYTE_RD_GO );
            xEndCH376Cmd( );
            buf += s;
            *RealCount += s;
        }
        /*		else if ( s == USB_INT_SUCCESS ) return( s );*/  /* 结束 */
        else return( s );  /* 错误 */
    }
}

UINT8	CH376ByteWrite( PUINT8 buf, UINT16 ReqCount, PUINT16 RealCount )  /* 以字节为单位向当前位置写入数据块 */
{
    UINT8	s;
    xWriteCH376Cmd( CMD2H_BYTE_WRITE );
    xWriteCH376Data( (UINT8)ReqCount );
    xWriteCH376Data( (UINT8)(ReqCount >> 8) );
    xEndCH376Cmd( );
    if ( *RealCount ) *RealCount = 0;
    while ( 1 )
    {
        s = Wait376Interrupt( );
        if ( s == USB_INT_DISK_WRITE )
        {
            s = CH376WriteReqBlock( buf );  /* 向内部指定缓冲区写入请求的数据块,返回长度 */
            xWriteCH376Cmd( CMD0H_BYTE_WR_GO );
            xEndCH376Cmd( );
            buf += s;
            *RealCount += s;
        }
        /*		else if ( s == USB_INT_SUCCESS ) return( s );*/  /* 结束 */
        else return( s );  /* 错误 */
    }
}

#ifdef	EN_DISK_QUERY

UINT8	CH376DiskCapacity( PUINT32 DiskCap )  /* 查询磁盘物理容量,扇区数 */
{
    UINT8	s;
    s = CH376SendCmdWaitInt( CMD0H_DISK_CAPACITY );
    if ( s == USB_INT_SUCCESS )    /* 参考CH376INC.H文件中CH376_CMD_DATA结构的DiskCapacity */
    {
        xWriteCH376Cmd( CMD01_RD_USB_DATA0 );
        xReadCH376Data( );  /* 长度总是sizeof(CH376_CMD_DATA.DiskCapacity) */
        *DiskCap = CH376Read32bitDat( );  /* CH376_CMD_DATA.DiskCapacity.mDiskSizeSec,从CH376芯片读取32位的数据并结束命令 */
    }
    else *DiskCap = 0;
    return( s );
}

UINT8	CH376DiskQuery( PUINT32 DiskFre )  /* 查询磁盘剩余空间信息,扇区数 */
{
    UINT8	s;
    UINT8	c0, c1, c2, c3;
#ifndef	DEF_IC_V43_U
    xWriteCH376Cmd( CMD01_GET_IC_VER );
    if ( xReadCH376Data( ) < 0x43 )
    {
        if ( CH376ReadVar8( VAR_DISK_STATUS ) >= DEF_DISK_READY ) CH376WriteVar8( VAR_DISK_STATUS, DEF_DISK_MOUNTED );
    }
#endif
    s = CH376SendCmdWaitInt( CMD0H_DISK_QUERY );
    if ( s == USB_INT_SUCCESS )    /* 参考CH376INC.H文件中CH376_CMD_DATA结构的DiskQuery */
    {
        xWriteCH376Cmd( CMD01_RD_USB_DATA0 );
        xReadCH376Data( );  /* 长度总是sizeof(CH376_CMD_DATA.DiskQuery) */
        xReadCH376Data( );  /* CH376_CMD_DATA.DiskQuery.mTotalSector */
        xReadCH376Data( );
        xReadCH376Data( );
        xReadCH376Data( );
        c0 = xReadCH376Data( );  /* CH376_CMD_DATA.DiskQuery.mFreeSector */
        c1 = xReadCH376Data( );
        c2 = xReadCH376Data( );
        c3 = xReadCH376Data( );
        *DiskFre = c0 | (UINT16)c1 << 8 | (UINT32)c2 << 16 | (UINT32)c3 << 24;
        xReadCH376Data( );  /* CH376_CMD_DATA.DiskQuery.mDiskFat */
        xEndCH376Cmd( );
    }
    else *DiskFre = 0;
    return( s );
}

#endif

UINT8	CH376SecLocate( UINT32 offset )  /* 以扇区为单位移动当前文件指针 */
{
    xWriteCH376Cmd( CMD4H_SEC_LOCATE );
    xWriteCH376Data( (UINT8)offset );
    xWriteCH376Data( (UINT8)((UINT16)offset >> 8) );
    xWriteCH376Data( (UINT8)(offset >> 16) );
    xWriteCH376Data( 0 );  /* 超出最大文件尺寸 */
    xEndCH376Cmd( );
    return( Wait376Interrupt( ) );
}

#ifdef	EN_SECTOR_ACCESS

UINT8	CH376DiskReadSec( PUINT8 buf, UINT32 iLbaStart, UINT8 iSectorCount )  /* 从U盘读取多个扇区的数据块到缓冲区,不支持SD卡 */
/* iLbaStart 是准备读取的线性起始扇区号, iSectorCount 是准备读取的扇区数 */
{
    UINT8	s, err;
    UINT16	mBlockCount;
    for ( err = 0; err != 3; ++ err )    /* 出错重试 */
    {
        xWriteCH376Cmd( CMD5H_DISK_READ );  /* 从USB存储器读扇区 */
        xWriteCH376Data( (UINT8)iLbaStart );  /* LBA的最低8位 */
        xWriteCH376Data( (UINT8)( (UINT16)iLbaStart >> 8 ) );
        xWriteCH376Data( (UINT8)( iLbaStart >> 16 ) );
        xWriteCH376Data( (UINT8)( iLbaStart >> 24 ) );  /* LBA的最高8位 */
        xWriteCH376Data( iSectorCount );  /* 扇区数 */
        xEndCH376Cmd( );
        for ( mBlockCount = iSectorCount * DEF_SECTOR_SIZE / CH376_DAT_BLOCK_LEN; mBlockCount != 0; -- mBlockCount )    /* 数据块计数 */
        {
            s = Wait376Interrupt( );  /* 等待中断并获取状态 */
            if ( s == USB_INT_DISK_READ )    /* USB存储器读数据块,请求数据读出 */
            {
                s = CH376ReadBlock( buf );  /* 从当前主机端点的接收缓冲区读取数据块,返回长度 */
                xWriteCH376Cmd( CMD0H_DISK_RD_GO );  /* 继续执行USB存储器的读操作 */
                xEndCH376Cmd( );
                buf += s;
            }
            else break;  /* 返回错误状态 */
        }
        if ( mBlockCount == 0 )
        {
            s = Wait376Interrupt( );  /* 等待中断并获取状态 */
            if ( s == USB_INT_SUCCESS ) return( USB_INT_SUCCESS );  /* 操作成功 */
        }
        if ( s == USB_INT_DISCONNECT ) return( s );  /* U盘被移除 */
        CH376DiskReqSense( );  /* 检查USB存储器错误 */
    }
    return( s );  /* 操作失败 */
}

UINT8	CH376DiskWriteSec( PUINT8 buf, UINT32 iLbaStart, UINT8 iSectorCount )  /* 将缓冲区中的多个扇区的数据块写入U盘,不支持SD卡 */
/* iLbaStart 是写入的线起始性扇区号, iSectorCount 是写入的扇区数 */
{
    UINT8	s, err;
    UINT16	mBlockCount;
    for ( err = 0; err != 3; ++ err )    /* 出错重试 */
    {
        xWriteCH376Cmd( CMD5H_DISK_WRITE );  /* 向USB存储器写扇区 */
        xWriteCH376Data( (UINT8)iLbaStart );  /* LBA的最低8位 */
        xWriteCH376Data( (UINT8)( (UINT16)iLbaStart >> 8 ) );
        xWriteCH376Data( (UINT8)( iLbaStart >> 16 ) );
        xWriteCH376Data( (UINT8)( iLbaStart >> 24 ) );  /* LBA的最高8位 */
        xWriteCH376Data( iSectorCount );  /* 扇区数 */
        xEndCH376Cmd( );
        for ( mBlockCount = iSectorCount * DEF_SECTOR_SIZE / CH376_DAT_BLOCK_LEN; mBlockCount != 0; -- mBlockCount )    /* 数据块计数 */
        {
            s = Wait376Interrupt( );  /* 等待中断并获取状态 */
            if ( s == USB_INT_DISK_WRITE )    /* USB存储器写数据块,请求数据写入 */
            {
                CH376WriteHostBlock( buf, CH376_DAT_BLOCK_LEN );  /* 向USB主机端点的发送缓冲区写入数据块 */
                xWriteCH376Cmd( CMD0H_DISK_WR_GO );  /* 继续执行USB存储器的写操作 */
                xEndCH376Cmd( );
                buf += CH376_DAT_BLOCK_LEN;
            }
            else break;  /* 返回错误状态 */
        }
        if ( mBlockCount == 0 )
        {
            s = Wait376Interrupt( );  /* 等待中断并获取状态 */
            if ( s == USB_INT_SUCCESS ) return( USB_INT_SUCCESS );  /* 操作成功 */
        }
        if ( s == USB_INT_DISCONNECT ) return( s );  /* U盘被移除 */
        CH376DiskReqSense( );  /* 检查USB存储器错误 */
    }
    return( s );  /* 操作失败 */
}

UINT8	CH376SecRead( PUINT8 buf, UINT8 ReqCount, PUINT8 RealCount )  /* 以扇区为单位从当前位置读取数据块,不支持SD卡 */
{
    UINT8	s;
    UINT8	cnt;
    UINT32	StaSec;
#ifndef	DEF_IC_V43_U
    UINT32	fsz, fofs;
#endif
    if ( RealCount ) *RealCount = 0;
    do
    {
#ifndef	DEF_IC_V43_U
        xWriteCH376Cmd( CMD01_GET_IC_VER );
        cnt = xReadCH376Data( );
        if ( cnt == 0x41 )
        {
            xWriteCH376Cmd( CMD14_READ_VAR32 );
            xWriteCH376Data( VAR_FILE_SIZE );
            xReadCH376Data( );
            fsz = xReadCH376Data( );
            fsz |= (UINT16)(xReadCH376Data( )) << 8;
            cnt = xReadCH376Data( );
            fsz |= (UINT32)cnt << 16;
            xWriteCH376Cmd( CMD14_READ_VAR32 );
            xWriteCH376Data( VAR_CURRENT_OFFSET );
            xReadCH376Data( );
            fofs = xReadCH376Data( );
            fofs |= (UINT16)(xReadCH376Data( )) << 8;
            fofs |= (UINT32)(xReadCH376Data( )) << 16;
            if ( fsz >= fofs + 510 ) CH376WriteVar8( VAR_FILE_SIZE + 3, 0xFF );
            else cnt = 0xFF;
        }
        else cnt = 0xFF;
#endif
        xWriteCH376Cmd( CMD1H_SEC_READ );
        xWriteCH376Data( ReqCount );
        xEndCH376Cmd( );
        s = Wait376Interrupt( );
#ifndef	DEF_IC_V43_U
        if ( cnt != 0xFF ) CH376WriteVar8( VAR_FILE_SIZE + 3, cnt );
#endif
        if ( s != USB_INT_SUCCESS ) return( s );
        xWriteCH376Cmd( CMD01_RD_USB_DATA0 );
        xReadCH376Data( );  /* 长度总是sizeof(CH376_CMD_DATA.SectorRead) */
        cnt = xReadCH376Data( );  /* CH376_CMD_DATA.SectorRead.mSectorCount */
        xReadCH376Data( );
        xReadCH376Data( );
        xReadCH376Data( );
        StaSec = CH376Read32bitDat( );  /* CH376_CMD_DATA.SectorRead.mStartSector,从CH376芯片读取32位的数据并结束命令 */
        if ( cnt == 0 ) break;
        s = CH376DiskReadSec( buf, StaSec, cnt );  /* 从U盘读取多个扇区的数据块到缓冲区 */
        if ( s != USB_INT_SUCCESS ) return( s );
        buf += cnt * DEF_SECTOR_SIZE;
        if ( RealCount ) *RealCount += cnt;
        ReqCount -= cnt;
    }
    while ( ReqCount );
    return( s );
}

UINT8	CH376SecWrite( PUINT8 buf, UINT8 ReqCount, PUINT8 RealCount )  /* 以扇区为单位在当前位置写入数据块,不支持SD卡 */
{
    UINT8	s;
    UINT8	cnt;
    UINT32	StaSec;
    if ( RealCount ) *RealCount = 0;
    do
    {
        xWriteCH376Cmd( CMD1H_SEC_WRITE );
        xWriteCH376Data( ReqCount );
        xEndCH376Cmd( );
        s = Wait376Interrupt( );
        if ( s != USB_INT_SUCCESS ) return( s );
        xWriteCH376Cmd( CMD01_RD_USB_DATA0 );
        xReadCH376Data( );  /* 长度总是sizeof(CH376_CMD_DATA.SectorWrite) */
        cnt = xReadCH376Data( );  /* CH376_CMD_DATA.SectorWrite.mSectorCount */
        xReadCH376Data( );
        xReadCH376Data( );
        xReadCH376Data( );
        StaSec = CH376Read32bitDat( );  /* CH376_CMD_DATA.SectorWrite.mStartSector,从CH376芯片读取32位的数据并结束命令 */
        if ( cnt == 0 ) break;
        s = CH376DiskWriteSec( buf, StaSec, cnt );  /* 将缓冲区中的多个扇区的数据块写入U盘 */
        if ( s != USB_INT_SUCCESS ) return( s );
        buf += cnt * DEF_SECTOR_SIZE;
        if ( RealCount ) *RealCount += cnt;
        ReqCount -= cnt;
    }
    while ( ReqCount );
    return( s );
}

#endif

#ifdef	EN_LONG_NAME

UINT8	CH376LongNameWrite( PUINT8 buf, UINT16 ReqCount )  /* 长文件名专用的字节写子程序 */
{
    UINT8	s;
#ifndef	DEF_IC_V43_U
    UINT8	c;
    c = CH376ReadVar8( VAR_DISK_STATUS );
    if ( c == DEF_DISK_OPEN_ROOT ) CH376WriteVar8( VAR_DISK_STATUS, DEF_DISK_OPEN_DIR );
#endif
    xWriteCH376Cmd( CMD2H_BYTE_WRITE );
    xWriteCH376Data( (UINT8)ReqCount );
    xWriteCH376Data( (UINT8)(ReqCount >> 8) );
    xEndCH376Cmd( );
    while ( 1 )
    {
        s = Wait376Interrupt( );
        if ( s == USB_INT_DISK_WRITE )
        {
            if ( buf ) buf += CH376WriteReqBlock( buf );  /* 向内部指定缓冲区写入请求的数据块,返回长度 */
            else
            {
                xWriteCH376Cmd( CMD01_WR_REQ_DATA );  /* 向内部指定缓冲区写入请求的数据块 */
                s = xReadCH376Data( );  /* 长度 */
                while ( s -- ) xWriteCH376Data( 0 );  /* 填充0 */
            }
            xWriteCH376Cmd( CMD0H_BYTE_WR_GO );
            xEndCH376Cmd( );
        }
        /*		else if ( s == USB_INT_SUCCESS ) return( s );*/  /* 结束 */
        else
        {
#ifndef	DEF_IC_V43_U
            if ( c == DEF_DISK_OPEN_ROOT ) CH376WriteVar8( VAR_DISK_STATUS, c );
#endif
            return( s );  /* 错误 */
        }
    }
}

UINT8	CH376CheckNameSum( PUINT8 DirName )  /* 计算长文件名的短文件名检验和,输入为无小数点分隔符的固定11字节格式 */
{
    UINT8	NameLen;
    UINT8	CheckSum;
    CheckSum = 0;
    for ( NameLen = 0; NameLen != 11; NameLen ++ ) CheckSum = ( CheckSum & 1 ? 0x80 : 0x00 ) + ( CheckSum >> 1 ) + *DirName++;
    return( CheckSum );
}

UINT8	CH376LocateInUpDir( PUINT8 PathName )  /* 在上级目录(文件夹)中移动文件指针到当前文件目录信息所在的扇区 */
/* 另外,顺便将当前文件目录信息所在的扇区的前一个扇区的LBA地址写入CH376内部VAR_FAT_DIR_LBA变量(为了方便收集长文件名时向前搜索,否则要多移动一次) */
/* 使用了全局缓冲区GlobalBuf的前12个字节 */
{
    UINT8	s;
    xWriteCH376Cmd( CMD14_READ_VAR32 );
    xWriteCH376Data( VAR_FAT_DIR_LBA );  /* 当前文件目录信息所在的扇区LBA地址 */
    for ( s = 4; s != 8; s ++ ) GlobalBuf[ s ] = xReadCH376Data( );  /* 临时保存于全局缓冲区中,节约RAM */
    xEndCH376Cmd( );
    s = CH376SeparatePath( PathName );  /* 从路径中分离出最后一级文件名或者目录名,返回最后一级文件名或者目录名的偏移 */
    if ( s ) s = CH376FileOpenDir( PathName, s );  /* 是多级目录,打开多级目录下的最后一级目录,即打开文件的上级目录 */
    else s = CH376FileOpen( "/" );  /* 根目录下的文件,则打开根目录 */
    if ( s != ERR_OPEN_DIR ) return( s );
    *(PUINT32)(&GlobalBuf[0]) = 0;  /* 目录扇区偏移扇区数,保存在全局缓冲区中,节约RAM */
    while ( 1 )    /* 不断移动文件指针,直到与当前文件目录信息所在的扇区LBA地址匹配 */
    {
        s = CH376SecLocate( *(PUINT32)(&GlobalBuf[0]) );  /* 以扇区为单位在上级目录中移动文件指针 */
        if ( s != USB_INT_SUCCESS ) return( s );
        CH376ReadBlock( &GlobalBuf[8] );  /* 从内存缓冲区读取CH376_CMD_DATA.SectorLocate.mSectorLba数据块,返回长度总是sizeof(CH376_CMD_DATA.SectorLocate) */
        if ( *(PUINT32)(&GlobalBuf[8]) == *(PUINT32)(&GlobalBuf[4]) ) return( USB_INT_SUCCESS );  /* 已到当前文件目录信息扇区 */
        xWriteCH376Cmd( CMD50_WRITE_VAR32 );
        xWriteCH376Data( VAR_FAT_DIR_LBA );  /* 得到前一个扇区,设置为新的文件目录信息扇区LBA地址 */
        for ( s = 8; s != 12; s ++ ) xWriteCH376Data( GlobalBuf[ s ] );
        xEndCH376Cmd( );
        ++ *(PUINT32)(&GlobalBuf[0]);
    }
}

UINT8	CH376GetLongName( PUINT8 PathName, PUINT8 LongName )  /* 由短文件名或者目录(文件夹)名获得相应的长文件名 */
/* 需要输入短文件名的完整路径PathName,需要提供缓冲区接收长文件名LongName(以UNICODE小端编码,以双0结束) */
/* 使用了全局缓冲区GlobalBuf的前34个字节,sizeof(GlobalBuf)>=sizeof(FAT_DIR_INFO)+2 */
{
    UINT8	s;
    UINT16	NameCount;	/* 长文件名字节计数 */
    s = CH376FileOpenPath( PathName );  /* 打开多级目录下的文件或者目录 */
    if ( s != USB_INT_SUCCESS && s != ERR_OPEN_DIR ) return( s );
    s = CH376DirInfoRead( );  /* 读取当前文件的目录信息FAT_DIR_INFO,将相关数据调到内存中 */
    if ( s != USB_INT_SUCCESS ) return( s );
    CH376ReadBlock( GlobalBuf );  /* 从内存缓冲区读取FAT_DIR_INFO数据块,返回长度总是sizeof(FAT_DIR_INFO) */
    CH376EndDirInfo( );  /* 获取完FAT_DIR_INFO结构 */
    GlobalBuf[32] = CH376CheckNameSum( GlobalBuf );  /* 计算长文件名的短文件名检验和,保存在全局缓冲区中,节约RAM */
    GlobalBuf[33] = CH376ReadVar8( VAR_FILE_DIR_INDEX );  /* 当前文件目录信息在扇区内的索引号,保存在全局缓冲区中,节约RAM */
    NameCount = 0;
    while ( 1 )
    {
        if ( GlobalBuf[33] == 0 )    /* 当前的文件目录信息扇区处理结束,转到前一个扇区 */
        {
            s = CH376LocateInUpDir( PathName );  /* 在上级目录中移动文件指针到当前文件目录信息所在的扇区 */
            if ( s != USB_INT_SUCCESS ) break;
            if ( CH376ReadVar32( VAR_CURRENT_OFFSET ) == 0 )    /* 当前已经处于目录扇区的开始,无法获取长文件名 */
            {
                s = ERR_LONG_NAME_ERR;
                break;
            }
            GlobalBuf[33] = DEF_SECTOR_SIZE / sizeof( FAT_DIR_INFO );  /* 指向前一个扇区的最后一个文件目录信息 */
        }
        GlobalBuf[33] --;  /* 从后向前搜索文件目录信息 */
        s = CH376SendCmdDatWaitInt( CMD1H_DIR_INFO_READ, GlobalBuf[33] );  /* 读取指定的目录信息FAT_DIR_INFO,将相关数据调到内存中 */
        if ( s != USB_INT_SUCCESS ) break;
        CH376ReadBlock( GlobalBuf );  /* 从内存缓冲区读取FAT_DIR_INFO数据块,返回长度总是sizeof(FAT_DIR_INFO) */
        CH376EndDirInfo( );  /* 获取完FAT_DIR_INFO结构 */
        if ( ( GlobalBuf[11] & ATTR_LONG_NAME_MASK ) != ATTR_LONG_NAME || GlobalBuf[13] != GlobalBuf[32] )    /* 类型错误或者校验和错误 */
        {
            s = ERR_LONG_NAME_ERR;
            break;  /* 没有直接返回是因为如果是打开了根目录那么必须要关闭后才能返回 */
        }
        for ( s = 1; s < sizeof( FAT_DIR_INFO ); s += 2 )    /* 收集长文件名,长文件名的字符在磁盘上UNICODE用小端方式存放 */
        {
            if ( s == 1 + 5 * 2 ) s = 14;  /* 从长文件名的第一组1-5个字符跳到第二组6-11个字符 */
            else if ( s == 14 + 6 * 2 ) s = 28;  /* 从长文件名的第二组6-11个字符跳到第三组12-13个字符 */
            LongName[ NameCount++ ] = GlobalBuf[ s ];
            LongName[ NameCount++ ] = GlobalBuf[ s + 1 ];
            if ( GlobalBuf[ s ] == 0 && GlobalBuf[ s + 1 ] == 0 ) break;  /* 长文件名结束 */
            if ( NameCount >= LONG_NAME_BUF_LEN )    /* 长文件名缓冲区溢出 */
            {
                s = ERR_LONG_BUF_OVER;
                goto CH376GetLongNameE;
            }
        }
        if ( GlobalBuf[0] & 0x40 )    /* 长文件名目录信息块结束 */
        {
            if ( s >= sizeof( FAT_DIR_INFO ) ) *(PUINT16)( &LongName[ NameCount ] ) = 0x0000;  /* 尚未收集到长文件名的结束符,则强制结束 */
            s = USB_INT_SUCCESS;  /* 成功完成长文件名收集完成 */
            break;
        }
    }
CH376GetLongNameE:
    CH376FileClose( FALSE );  /* 对于根目录则必须要关闭 */
    return( s );
}

UINT8	CH376CreateLongName( PUINT8 PathName, PUINT8 LongName )  /* 新建具有长文件名的文件,关闭文件后返回,LongName输入路径必须在RAM中 */
/* 需要输入短文件名的完整路径PathName(请事先参考FAT规范由长文件名自行产生),需要输入以UNICODE小端编码的以双0结束的长文件名LongName */
/* 使用了全局缓冲区GlobalBuf的前64个字节,sizeof(GlobalBuf)>=sizeof(FAT_DIR_INFO)*2 */
{
    UINT8	s, i;
    UINT8	DirBlockCnt;	/* 长文件名占用文件目录结构的个数 */
    UINT16	count;			/* 临时变量,用于计数,用于字节读文件方式下实际读取的字节数 */
    UINT16	NameCount;		/* 长文件名字节计数 */
    UINT32	NewFileLoc;		/* 当前文件目录信息在上级目录中的起始位置,偏移地址 */
    for ( count = 0; count < LONG_NAME_BUF_LEN; count += 2 ) if ( *(PUINT16)(&LongName[count]) == 0 ) break;  /* 到结束位置 */
    if ( count == 0 || count >= LONG_NAME_BUF_LEN || count > LONE_NAME_MAX_CHAR ) return( ERR_LONG_NAME_ERR );  /* 长文件名无效 */
    DirBlockCnt = count / LONG_NAME_PER_DIR;  /* 长文件名占用文件目录结构的个数 */
    i = count - DirBlockCnt * LONG_NAME_PER_DIR;
    if ( i )    /* 有零头 */
    {
        if ( ++ DirBlockCnt * LONG_NAME_PER_DIR > LONG_NAME_BUF_LEN ) return( ERR_LONG_BUF_OVER );  /* 缓冲区溢出 */
        count += 2;  /* 加上0结束符后的长度 */
        i += 2;
        if ( i < LONG_NAME_PER_DIR )    /* 最末的文件目录结构不满 */
        {
            while ( i++ < LONG_NAME_PER_DIR ) LongName[count++] = 0xFF;  /* 把剩余数据填为0xFF */
        }
    }
    s = CH376FileOpenPath( PathName );  /* 打开多级目录下的文件 */
    if ( s == USB_INT_SUCCESS )     /* 短文件名存在则返回错误 */
    {
        s = ERR_NAME_EXIST;
        goto CH376CreateLongNameE;
    }
    if ( s != ERR_MISS_FILE ) return( s );
    s = CH376FileCreatePath( PathName );  /* 新建多级目录下的文件 */
    if ( s != USB_INT_SUCCESS ) return( s );
    i = CH376ReadVar8( VAR_FILE_DIR_INDEX );  /* 临时用于保存当前文件目录信息在扇区内的索引号 */
    s = CH376LocateInUpDir( PathName );  /* 在上级目录中移动文件指针到当前文件目录信息所在的扇区 */
    if ( s != USB_INT_SUCCESS ) goto CH376CreateLongNameE;  /* 没有直接返回是因为如果是打开了根目录那么必须要关闭后才能返回 */
    NewFileLoc = CH376ReadVar32( VAR_CURRENT_OFFSET ) + i * sizeof(FAT_DIR_INFO);  /* 计算当前文件目录信息在上级目录中的起始位置,偏移地址 */
    s = CH376ByteLocate( NewFileLoc );  /* 在上级目录中移动文件指针到当前文件目录信息的位置 */
    if ( s != USB_INT_SUCCESS ) goto CH376CreateLongNameE;
    s = CH376ByteRead( &GlobalBuf[ sizeof(FAT_DIR_INFO) ], sizeof(FAT_DIR_INFO), NULL );  /* 以字节为单位读取数据,获得当前文件的目录信息FAT_DIR_INFO */
    if ( s != USB_INT_SUCCESS ) goto CH376CreateLongNameE;
    for ( i = DirBlockCnt; i != 0; -- i )    /* 搜索空闲的文件目录结构用于存放长文件名 */
    {
        s = CH376ByteRead( GlobalBuf, sizeof(FAT_DIR_INFO), &count );  /* 以字节为单位读取数据,获得下一个文件目录信息FAT_DIR_INFO */
        if ( s != USB_INT_SUCCESS ) goto CH376CreateLongNameE;
        if ( count == 0 ) break;  /* 无法读出数据,上级目录结束了 */
        if ( GlobalBuf[0] && GlobalBuf[0] != 0xE5 )    /* 后面有正在使用的文件目录结构,由于长文件名必须连接存放,所以空间不够,必须放弃当前位置并向后转移 */
        {
            s = CH376ByteLocate( NewFileLoc );  /* 在上级目录中移动文件指针到当前文件目录信息的位置 */
            if ( s != USB_INT_SUCCESS ) goto CH376CreateLongNameE;
            GlobalBuf[ 0 ] = 0xE5;  /* 文件删除标志 */
            for ( s = 1; s != sizeof(FAT_DIR_INFO); s ++ ) GlobalBuf[ s ] = GlobalBuf[ sizeof(FAT_DIR_INFO) + s ];
            s = CH376LongNameWrite( GlobalBuf, sizeof(FAT_DIR_INFO) );  /* 写入一个文件目录结构,用于删除之前新建的文件,实际上稍后会将之转移到目录的最末位置 */
            if ( s != USB_INT_SUCCESS ) goto CH376CreateLongNameE;
            do    /* 向后搜索空闲的文件目录结构 */
            {
                s = CH376ByteRead( GlobalBuf, sizeof(FAT_DIR_INFO), &count );  /* 以字节为单位读取数据,获得下一个文件目录信息FAT_DIR_INFO */
                if ( s != USB_INT_SUCCESS ) goto CH376CreateLongNameE;
            }
            while ( count && GlobalBuf[0] );    /* 如果仍然是正在使用的文件目录结构则继续向后搜索,直到上级目录结束或者有尚未使用过的文件目录结构 */
            NewFileLoc = CH376ReadVar32( VAR_CURRENT_OFFSET );  /* 用上级目录的当前文件指针作为当前文件目录信息在上级目录中的起始位置 */
            i = DirBlockCnt + 1;  /* 需要的空闲的文件目录结构的个数,包括短文件名本身一个和长文件名 */
            if ( count == 0 ) break;  /* 无法读出数据,上级目录结束了 */
            NewFileLoc -= sizeof(FAT_DIR_INFO);  /* 倒回到刚才搜索到的空闲的文件目录结构的起始位置 */
        }
    }
    if ( i )    /* 空闲的文件目录结构不足以存放长文件名,原因是上级目录结束了,下面增加上级目录的长度 */
    {
        s = CH376ReadVar8( VAR_SEC_PER_CLUS );  /* 每簇扇区数 */
        if ( s == 128 )    /* FAT12/FAT16的根目录,容量是固定的,无法增加文件目录结构 */
        {
            s = ERR_FDT_OVER;  /* FAT12/FAT16根目录下的文件数应该少于512个,需要磁盘整理 */
            goto CH376CreateLongNameE;
        }
        count = s * DEF_SECTOR_SIZE;  /* 每簇字节数 */
        if ( count < i * sizeof(FAT_DIR_INFO) ) count <<= 1;  /* 一簇不够则增加一簇,这种情况只会发生于每簇为512字节的情况下 */
        s = CH376LongNameWrite( NULL, count );  /* 以字节为单位向当前位置写入全0数据块,清空新增加的文件目录簇 */
        if ( s != USB_INT_SUCCESS ) goto CH376CreateLongNameE;
    }
    s = CH376ByteLocate( NewFileLoc );  /* 在上级目录中移动文件指针到当前文件目录信息的位置 */
    if ( s != USB_INT_SUCCESS ) goto CH376CreateLongNameE;
    GlobalBuf[11] = ATTR_LONG_NAME;
    GlobalBuf[12] = 0x00;
    GlobalBuf[13] = CH376CheckNameSum( &GlobalBuf[ sizeof(FAT_DIR_INFO) ] );  /* 计算长文件名的短文件名检验和 */
    GlobalBuf[26] = 0x00;
    GlobalBuf[27] = 0x00;
    for ( s = 0; DirBlockCnt != 0; )    /* 长文件名占用的文件目录结构计数 */
    {
        GlobalBuf[0] = s ? DirBlockCnt : DirBlockCnt | 0x40;  /* 首次要置长文件名入口标志 */
        DirBlockCnt --;
        NameCount = DirBlockCnt * LONG_NAME_PER_DIR;
        for ( s = 1; s < sizeof( FAT_DIR_INFO ); s += 2 )    /* 输出长文件名,长文件名的字符在磁盘上UNICODE用小端方式存放 */
        {
            if ( s == 1 + 5 * 2 ) s = 14;  /* 从长文件名的第一组1-5个字符跳到第二组6-11个字符 */
            else if ( s == 14 + 6 * 2 ) s = 28;  /* 从长文件名的第二组6-11个字符跳到第三组12-13个字符 */
            GlobalBuf[ s ] = LongName[ NameCount++ ];
            GlobalBuf[ s + 1 ] = LongName[ NameCount++ ];
        }
        s = CH376LongNameWrite( GlobalBuf, sizeof(FAT_DIR_INFO) );  /* 以字节为单位写入一个文件目录结构,长文件名 */
        if ( s != USB_INT_SUCCESS ) goto CH376CreateLongNameE;
    }
    s = CH376LongNameWrite( &GlobalBuf[ sizeof(FAT_DIR_INFO) ], sizeof(FAT_DIR_INFO) );  /* 以字节为单位写入一个文件目录结构,这是转移来的之前新建的文件的目录信息 */
CH376CreateLongNameE:
    CH376FileClose( FALSE );  /* 对于根目录则必须要关闭 */
    return( s );
}

#endif
