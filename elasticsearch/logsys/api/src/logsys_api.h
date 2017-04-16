
/**
 * Tencent is pleased to support the open source community by making MSEC available.
 *
 * Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.
 *
 * Licensed under the GNU General Public License, Version 2.0 (the "License"); 
 * you may not use this file except in compliance with the License. You may 
 * obtain a copy of the License at
 *
 *     https://opensource.org/licenses/GPL-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the 
 * License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language governing permissions
 * and limitations under the License.
 */


#ifndef  _MSEC_LOGSYS_API_H_
#define  _MSEC_LOGSYS_API_H_

#include <map>
#include <string>
#include <cassert>
#include <set>
#include <stdarg.h>

namespace msec  
{

enum {
    ERROR_CREATE_SOCKET = 10001,
    ERROR_CONNECT_SERVER,
    ERROR_COMPOSE_PACKET,
    ERROR_SEND,
};

class LogsysApi
{
public:

    //��־����
    enum 
    {
        TRACE = 0,
        DEBUG,
        INFO,
        ERROR,
        FATAL,
        NONE,
    };

    static const char* s_level_list[];

    static LogsysApi* GetInstance()
    {
        if (s_logsys_api_ptr == NULL)
        {
            s_logsys_api_ptr = new LogsysApi;
            assert(s_logsys_api_ptr != NULL);
        }

        return s_logsys_api_ptr;
    }

    ~LogsysApi();

    /*
    * ���������ļ���ʼ��API
    * ����ֵ�� 0��ʾ��ʼ���ɹ��� ������ʾ��ʼ��ʧ��
    */
    int Init(const char* conf_filename);

    /*
    * ��¼��־�����ݿ�
    * ����ֵ�� 0��ʾ�ɹ���������ʾʧ��
    */
    int Log(int level, const std::map<std::string, std::string>&  headers,
        const std::string& body);

    /*
    * ��¼��־�����ݿ�, ʹ��inner headers
    * ����ֵ�� 0��ʾ�ɹ���������ʾʧ��
    */
    int Log(int level, const std::string& body);

    LogsysApi& LogSetHeader(const std::string& key, const std::string& value);

    int GetLevel() { return m_log_level;  }

    /*
    * �ж��Ƿ�������־��¼������ ����Ⱦɫ����
    * ����ֵ�� true��ʾ���㣬false��ʾ������
    */
    bool IsLogWritable(int level, const std::map<std::string, std::string>&  headers);

    /*
    * �ж��Ƿ�������־��¼������ ����Ⱦɫ����
    * ʹ��inner headers
    * ����ֵ�� true��ʾ���㣬false��ʾ������
    */
    bool IsLogWritable(int level);

private:
    LogsysApi(): m_log_level(ERROR), m_socket(-1)
    {
    }

    static LogsysApi*  s_logsys_api_ptr;

    std::set<std::pair<std::string, std::string> > m_color_conditions;
    int m_log_level;
    int m_socket;
    std::map<std::string, std::string> m_inner_headers;
};

LogsysApi& LogSetHeader(const std::string& key, const std::string& value);

bool LogIsWritable(int level);
bool LogIsWritable(int level, const std::map<std::string, std::string>&  headers);

void LOG(int level, const char* format, ...);
void LOG(int level, const std::map<std::string, std::string>&  headers, const char* format, ...);
void LOG(int level, const std::map<std::string, std::string>&  headers, const char* format, va_list ap);

}

#endif
