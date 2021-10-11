﻿/**
* \file shm_channel.h
* \brief 共享内存双工通道
*
* 使用两个共享内存管道，一个读，一个写，
* 实现跨进程双工通信。
*
* Copyright (c) 2019
* All rights reserved.
*
* \version 1.0
* \author jj
*/

#ifndef __SHM_CHANNEL_H__
#define __SHM_CHANNEL_H__

#include "typedef.h"
#include "app/app.h"
#include "pipe/shm_pipe.h"
#include "pipe/shm_sem.h"

namespace frame
{
    /**
    * \brief 共享内存双工通道类
    * \ingroup app_group
    */
    class ShmChannel : public IChannel
    {
    public:
        /**
        * \brief 构造函数
        */
        ShmChannel(void);

        /**
        * \brief 析构函数
        */
        virtual ~ShmChannel(void);

        /**
        * \brief 创建共享内存双工通道
        * \param stRecvInfo 接收共享内存数据
        * \param stSendInfo 发送共享内存数据
        * \return 创建成功返回true，否则返回false
        */
        bool Create(const SHM_CHANNEL_INFO &stRecvInfo, const SHM_CHANNEL_INFO &stSendInfo);

        /**
        * \brief 释放
        */
        virtual void Release();

        /**
        * \brief 发送数据
        * \param pMsg 消息数据
        * \param nLen 数据大小
        * \return 发送成功的数据大小，<0表示发送失败
        */
        virtual int32 Send(LPCSTR pMsg, size_t nLen);

        /**
        * \brief 接收数据
        * \param szBuffer 接收数据的缓冲区
        * \param nLen 接收数据的缓冲区大小
        * \return 接收数据大小，=0表示管道已经没数据了，<0表示接收失败
        */
        virtual int32 Recv(char *szBuffer, size_t nLen);

        /**
        * \brief 阻塞等待信号
        * \return true表示有信号，false表示无信号
        */
        virtual bool Wait();

        /**
        * \brief 停止等待信号
        */
        virtual void Stop();

    private:
        ShmPipe     m_RecvPipe;     ///< 接收管道
        ShmPipe     m_SendPipe;     ///< 发送管道
    };
}

#endif // __SHM_CHANNEL_H__