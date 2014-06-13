
\page xI2C_page xI2C page

xI2C document
======

xI2C Master Interrupt  {#xI2C_INT_Master_md}
================
这组宏定义在CoX中是强制的，在每个系列中都必须实现这样一组宏。其强制的形式为固定的宏名称： xI2C_MASTER_INT_DATA 。
这个宏的意义是使能 I2C 主机的中断功能。
有些系列并不需要使能（默认就是使能的，而且不能除能），我们将它空实现，比如LPC17xx系列。
这个参数作为 API \ref xI2CMasterIntEnable 和 \ref xI2CMasterIntDisable 的ulIntType参数传入。

|  xI2C Master Interrupts  |         all series     |
|--------------------------|------------------------|
|  xI2C_MASTER_INT_DATA    |xI2C_MASTER_INT_DATA    |


xI2C Master Event  {#xI2C_Event_Master_md}
================
这个参数是中断的事件，当I2C主机中断发生时 用这个参数来判断 当前的 中断源 是什么。
中断事件和类型，基本保持一致。
参数的形式为固定的宏名称：
 - \ref xI2C_MASTER_EVENT_TX
 - \ref xI2C_MASTER_EVENT_RX

这个将在回调函数中使用，以判断已经发生的中断源。比如要判断 xI2C_MASTER_EVENT_TX 是否发生，只需在回调函数中 用参数 ulMsgParam 和 xI2C_MASTER_EVENT_TX进行与(&)运算。

示例:
if(ulMsgParam & xI2C_MASTER_EVENT_TX)
{

}

下面是各个系列的实现的情况。

|  xI2C Master Event       |         all series     |
|--------------------------|------------------------|
|  xI2C_MASTER_EVENT_TX    |            Y           |
|  xI2C_MASTER_EVENT_RX    |            Y           |

\note 1. 当出现某个系列，没有这个功能的时候，对应的宏空实现。
\note 2. 当  xI2C_MASTER_EVENT_TX 和 xI2C_MASTER_EVENT_RX为枚举值的时候，使用一个位域表示一个时间标志。比如：使用 1,2,4,8 ... 代替 0,1,2,3 ...

xI2C Slave Interrupt  {#xI2C_INT_Slave_md}
================
这组宏定义了 I2C 从机中断的类型，概括来说从机有三种中断，数据、收到起始位、收到停止位。其中数据中断是必选项，其余两个为可选项。
其强制的形式为固定的宏名称：
 - \ref  xI2C_SLAVE_INT_DATA
 - \ref  xI2C_SLAVE_INT_START
 - \ref  xI2C_SLAVE_INT_STOP

这组参数作为 API \ref xI2CSlaveIntEnable 和 \ref xI2CSlaveIntDisable 的ulIntType参数传入。

 有些系列并不需要使能（默认就是使能的，而且不能除能），我们将它空实现，比如LPC17xx系列。以下是可选项在各个系列的实现情况：

|  xI2C Slave Interrupts   | LPC17xx |
|--------------------------|---------|
|  xI2C_SLAVE_INT_DATA     |   Y     |
|  xI2C_SLAVE_INT_START    |   N     |
|  xI2C_SLAVE_INT_STOP     |   N     |



xI2C Slave Event  {#xI2C_Event_Slave_md}
================
这个参数是中断的事件，当I2C从机中断发生时 用这个参数来判断 当前的 中断源 是什么。
中断事件和类型，基本保持一致。
参数的形式为固定的宏名称：
 - \ref xI2C_SLAVE_EVENT_START
 - \ref xI2C_SLAVE_EVENT_STOP
 - \ref xI2C_SLAVE_EVENT_TREQ
 - \ref xI2C_SLAVE_EVENT_RREQ

这个将在回调函数中使用，以判断已经发生的中断源。比如要判断 xI2C_SLAVE_EVENT_TREQ 是否发生，只需在回调函数中 用参数 ulMsgParam 和 xI2C_SLAVE_EVENT_TREQ 进行与(&)运算。

示例:
if(ulMsgParam & xI2C_SLAVE_EVENT_TREQ)
{

}

下面是各个系列的实现的情况。

|  xI2C Slave Event        | LPC17xx |
|--------------------------|---------|
|  xI2C_SLAVE_EVENT_START  |   N     |
|  xI2C_SLAVE_EVENT_STOP   |   N     |
|  xI2C_SLAVE_EVENT_TREQ   |   Y     |
|  xI2C_SLAVE_EVENT_RREQ   |   Y     |

\note 1. 当出现某个系列，没有这个功能的时候，对应的宏空实现。
\note 2. 当  xI2C_MASTER_EVENT_TX 和 xI2C_MASTER_EVENT_RX为枚举值的时候，使用一个位域表示一个时间标志。比如：使用 1,2,4,8 ... 代替 0,1,2,3 ...
\note 3. 虽然将 Slave Event 和 Master Event分开了，但在枚举 中断事件的时候，Slave Event 和 Master Event 不能使用重复位域。


xI2C Master Error  {#xI2C_Master_Error_md}
================
I2C主机在发送数据后，可能会出现错误，比如 地址无响应，数据无响应，仲裁丢失等
这组宏定义了常见的错误类型。

参数的形式为固定的宏名称：
 - \ref xI2C_MASTER_ERR_NONE
 - \ref xI2C_MASTER_ERR_ADDR_ACK
 - \ref xI2C_MASTER_ERR_DATA_ACK
 - \ref xI2C_MASTER_ERR_ARB_LOST

这组参数将作为 API \ref xI2CMasterError 的返回值传出。
比如判断当前主机是否发生错误
只需 if (xI2CMasterError(ulBase) != xI2C_MASTER_ERR_NONE) 即可。

下面是各个系列的实现的情况。
|  xI2C Master Error        |LPC17xx |
|---------------------------|--------|
|  xI2C_MASTER_ERR_NONE     |    Y   |
|  xI2C_MASTER_ERR_ADDR_ACK |    Y   |
|  xI2C_MASTER_ERR_DATA_ACK |    Y   |
|  xI2C_MASTER_ERR_ARB_LOST |    Y   |



xI2C General Call  {#xI2C_General_Call_md}
================
一般 I2C 从机都支持 广播地址，这组宏就是用来使能和除能广播地址功能的。
参数的形式为固定的宏名称：
 - \ref xI2C_GENERAL_CALL_DIS
 - \ref xI2C_GENERAL_CALL_EN
这组参数在 从机 初始化(\ref xI2CSlaveInit)的时候作为 ulGeneralCall 参数调用。

下面是各个系列的实现的情况。
|  xI2C General Call     |LPC17xx |
|------------------------|--------|
|  xI2C_GENERAL_CALL_DIS |    Y   |
|  xI2C_GENERAL_CALL_EN  |    Y   |


xI2C API   {#xI2C_Exported_APIs_md}
=====
|       xI2C API                     | LPC17xx |
|------------------------------------|---------|
| \ref  xI2CMasterInit               |    Y    |
| \ref  xI2CMasterEnable             |    Y    |
| \ref  xI2CMasterDisable            |    Y    |
| \ref  xI2CMasterBusBusy            |    Y    |
| \ref  xI2CMasterBusy               |    Y    |
| \ref  xI2CMasterError              |    Y    |
| \ref  xI2CMasterDataPut            |    Y    |
| \ref  xI2CMasterDataGet            |    Y    |
| \ref  xI2CMasterStop               |    Y    |
| \ref  xI2CMasterWriteRequestS1     |    Y    |
| \ref  xI2CMasterWriteRequestS2     |    Y    |
| \ref  xI2CMasterWriteS1            |    Y    |
| \ref  xI2CMasterWriteS2            |    Y    |
| \ref  xI2CMasterWriteBufS1         |    Y    |
| \ref  xI2CMasterWriteBufS2         |    Y    |
| \ref  xI2CMasterReadRequestS1      |    Y    |
| \ref  xI2CMasterReadRequestS2      |    Y    |
| \ref  xI2CMasterReadLastRequestS2  |    Y    |
| \ref  xI2CMasterReadS1             |    Y    |
| \ref  xI2CMasterReadS2             |    Y    |
| \ref  xI2CMasterReadBufS1          |    Y    |
| \ref  xI2CMasterReadBufS2          |    Y    |
| \ref  xI2CMasterIntEnable          |    Y    |
| \ref  xI2CMasterIntDisable         |    Y    |
| \ref  xI2CMasterIntFlagGet         |    Y    |
| \ref  xI2CSlaveIntEnable           |    Y    |
| \ref  xI2CSlaveIntDisable          |    Y    |
| \ref  xI2CSlaveIntFlagGet          |    Y    |
| \ref  xI2CSlaveInit                |    Y    |
| \ref  xI2CSlaveEnable              |    Y    |
| \ref  xI2CSlaveDisable             |    Y    |
| \ref  xI2CSlaveDataPut             |    Y    |
| \ref  xI2CSlaveDataGet             |    Y    |
| \ref  xI2CIntCallbackInit          |    Y    |

从宏观上来看，API分为两组： 
 - master 组
 - slave 组。

一般来说同一个 I2C 外设在应用中很少即作为 master 又作为 slave (即使用过程中切换 master 和 slave)。所以区分 master 和 slave 之后，一旦应用场景确定。
所需用到的API 参数等 都是很清晰的。
下面从具体的场景介绍API的开发和使用。

slave 模式
-------
slave 模式的 API 比较少，应用也比较简单，CoX中定义用中断方式来进行数据传输。

\note 查询模式也是可以使用的，只是CoX没有提出来标准。

步骤很简单。
 - 使能时钟和复位外设
 - 配置管脚
 - 初始化，设置slave地址和广播地址
 - 使能 I2C并 使能 I2C 中断
 - 设置回调函数
在以上整个步骤中需要 改变的不多，只有两个地方： 管脚设置 和 初始化(slave地址)
 
~~~{.c}
unsigned long ulSlave = I2C1_BASE;
unsigned char ucTempData[5];
unsigned char ucTempCount = 0;
unsigned char ucTempCount1 = 0;

unsigned long I2CSlaveCallback(void *pvCBData, 
                               unsigned long ulEvent,
                               unsigned long ulMsgParam,
                               void *pvMsgData)
{
    if(ulMsgParam == xI2C_SLAVE_EVENT_RREQ)
    {
        ucTempData[ucTempCount] = xI2CSlaveDataGet(ulSlave);
        ucTempCount++;
    }
    else if (ulMsgParam == xI2C_SLAVE_EVENT_TREQ)
    {
        xI2CSlaveDataPut(ulSlave, ucTempData[ucTempCount1]);
        ucTempCount1++;
        if(ucTempCount1 == 5)
        {
            xI2CSlaveIntDisable(ulSlave, xI2C_SLAVE_INT_DATA);
        }
    }
    return 0;
}

int main()
{
    xSysCtlPeripheralEnable2(ulSlave);
    xSysCtlPeripheralReset2(ulSlave);
    
    xSPinTypeI2C(I2C1SCK, PB6);
    xSPinTypeI2C(I2C1SDA, PB7);
    
    xI2CSlaveInit(ulSlave, 0x12, xI2C_GENERAL_CALL_DIS);
    xI2CSlaveEnable(ulSlave);
    xI2CSlaveIntEnable(ulSlave, xI2C_SLAVE_INT_DATA);
    xIntEnable(xSysCtlPeripheraIntNumGet(ulSlave));
    xI2CIntCallbackInit(ulSlave, I2CSlaveCallback);
}
~~~

master 模式
-------

