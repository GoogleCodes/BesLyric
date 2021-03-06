/*
	BesLyric  一款 操作简单、功能实用的 专门用于制作网易云音乐滚动歌词的 歌词制作软件。
    Copyright (C) 2017  
	Author: BensonLaur <BensonLaur@163.com>
	Author:

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
* @file       Define.h
* 
* Describe    定义了 程序使用的一些结构
*/

#pragma once
#include "stdafx.h"
#include <vector>
#include <string>
#include "Globle.h"
using namespace std;

/* 宏定义 */
#ifdef _DEBUG

#define UPDATE_LOOP  0			/* 是否在启动时更新程序 */

#else

#define UPDATE_LOOP  1

#endif


#define OPEN_DEBUG_LOG 0					//是否打开调试

#define SG  (CGloble::GetInstance())


#if OPEN_DEBUG_LOG == 1
#define DLOG(info)			SG->AppendLog(info)
#define DELETE_LOG()		;
#else 
#define DLOG(info)			;
#define DELETE_LOG()		SG->DeleteLogFile();
#endif



#define RET_SUCCEEDED	0
#define MAX_BUFFER_SIZE	 (260 * 2)

#define MSG_USER_MAKING_START_BUTTON	WM_USER+1					//制作页面开始播放消息
#define MSG_USER_PLAYING_START_BUTTON	WM_USER+2					//播放页面开始播放消息

#define MSG_USER_UPDATE_CHECK_PROGRESS	WM_USER+3					//更新检测进度消息
#define MSG_USER_CLOSE_CHECK_PROGRESS	WM_USER+4					//关闭检测过程消息

#define MSG_USER_DROP_FILE				WM_USER+5					//拖动文件消息

#define MSG_USER_SHOW_LYRIC_RESULT		WM_USER+6					//显示搜索歌词结果消息

#define MSG_USER_SEARCH_WITH_GUESS_RESULT		WM_USER+7			//带着猜测的结果来搜索歌词
#define MSG_USER_SEARCH_NCM_WITH_GUESS_RESULT	WM_USER+8			//带着猜测的结果来搜索NCM

#define MSG_USER_SHOW_ID_RESULT		WM_USER+9						//显示ncm ID结果

#define MSG_USER_UPDATE_DOWNLOAD_PROCESS_SPEED	WM_USER+10			//更新下载过程数据的消息,WPARAM 为下载速度，单位 byte/ms
#define MSG_USER_UPDATE_DOWNLOAD_PROCESS_TOTAL	WM_USER+11			//更新下载过程数据的消息,WPARAM 为接收总数，单位 byte 

/* 结构定义 */

//在制作歌词页面 和 滚动预览 页面中，需要选择音乐路径，歌词路径，输出路径等信息
//该结构用于存储 路径名 以及 是否已被选择的状态
typedef struct _PATH_STATE
{	
	TCHAR nameOfPath[_MAX_PATH];
	bool isInited;
}PATH_STATE; 

namespace ENCODING_TYPE{
	enum encoding_type			//文件编码类型
	{
		ASCII,						
		UNICODE_LITTLE_ENDIAN,
		UNICODE_BIG_ENDIAN,
		UTF_8,
		UTF_8_NO_BOM,
		OTHER
	};
}//为了避免 warning (nonstandard extension used: enum 'ENCODING_TYPE' used in qualified name) 而定义的命名空间

//储存获取的单个歌词信息
struct LyricInfo
{
	wstring strPlaneText;
	wstring strLabelText;
	wstring strSong;
	wstring strArtist;
	wstring strLyricFrom;
};

struct LyricSearchResult
{
	bool bCurrentSearchDone;						//标记本次搜索是否结束
	bool bAppendToList;								//是否为追加到列表，false 则先清空
	vector<LyricInfo> vecLyricInfoTotal;			//所有获得的歌词
	bool bShowUnexpectedResultTip;					//是否显示意外结果的提示
	SStringW strUnexpectedResultTip;				//意外结果的提示
};

//储存获取的单个歌曲ID信息
struct IDInfo
{
	wstring strSong;
	wstring strArtist;
	wstring strID;
};

struct IDSearchResult
{
	vector<IDInfo> vecIDInfoTotal;					//所有获得的歌词
	bool bShowUnexpectedResultTip;					//是否显示意外结果的提示
	SStringW strUnexpectedResultTip;				//意外结果的提示
};



//网易云歌曲信息结构（可用于存储从网易云搜索到的数据）
typedef struct _SONG_INFO{
	int nID;
	wstring strArtists;
	wstring strSong;
} SONGINFO;


struct SongInfoGuessResult
{
	int nResultType;   //1 表示获得到了歌曲名和歌手名  2 表示只获取歌曲名  3表示没有获取到任何猜测结果
	SStringW strSongName;		//歌曲名
	SStringW strArtist;			//歌手信息
};

//定义更新信息文件结构
struct UpdateItem
{
	wstring fileName;
	wstring link;
	wstring local;
	string md5;
};



/* 全局变量定义 */
/* 版本格式说明：X.Y.Z  
X表示主版本，架构性修改时更新
Y表示次版本，较大修改时更新
Z表示修改号，小问题时更新
*/
static const wstring VERSION_NUMBER = L"2.2.5";		//版本号（注意每次更改版本号时需要更改2处，1处是这里，1处是 BesLyric.rc 中的Version）

// v 2.1.10 以及以前的版本使用的链接
static const wstring  LINK_VERSION_LOG= L"http://files.cnblogs.com/files/BensonLaur/versionLog.zip";			//链接，指向版本日志文件
static const wstring  LINK_LAST_VERSION_INFO= L"http://files.cnblogs.com/files/BensonLaur/lastVersion.zip";		//链接，指向最后版本信息的文件
static const wstring  LINK_LAST_EXE= L"http://files.cnblogs.com/files/BensonLaur/BesLyricExe.zip";				//链接，指向最新的 EXE文件

// v 2.1.11 以及以后的版本使用的链接
static const wstring  LINK_VERSION_LOG_2= L"http://files.cnblogs.com/files/BensonLaur/versionLog.rar";			//链接，指向版本日志文件
static const wstring  LINK_LAST_VERSION_INFO_2= L"http://files.cnblogs.com/files/BensonLaur/lastVersion.rar";	//链接，指向最后版本信息的文件
static const wstring  LINK_LAST_EXE_2= L"http://files.cnblogs.com/files/BensonLaur/BesLyricExe.rar";			//链接，指向最新的 EXE文件

static const wstring LINK_SEND_LOGIN = L"http://beslyric.320.io/BesBlog/beslyric/login.action";

static const wstring FLODER_NAME_ETC = L"etc";									//文件夹名称，存放各种临时或配置杂项
static const wstring FILE_NAME_LAST_VERSION_INFO = L"version";					//文件名，从 LINK_LAST_VERSION_INFO 下载下来储存的文件
static const wstring FILE_NAME_TEMP = L"temp";									//文件名，储存临时下载下来的文件
static const wstring FILE_NAME_NEED_UPDATE = L"needUpdate";						//文件名，标志是否需要更新
static const wstring FILE_NAME_LAST_EXE_TEMP = L"BesLyric";						//文件名，从 LINK_LAST_EXE 下载下来储存的文件
static const wstring SETTING_FILE_NAME = L"setting";							//文件名，储存设置
static const wstring NCM_ID_FILE_NAME = L"ncm_id";							//文件名，储存设置

static const wstring TEMP_WAV_FLODER_NAME = L"wav";								//文件夹名称，存放临时转换得到的wav文件
static const wstring TEMP_MP3_FLODER_NAME = L"mp3";								//文件夹名称，存放下载下来的MP3文件

static const wstring SERVER_FILE_EXTENTION_W = L".zip";							//定义上传到 cnblog服务器的文件拓展名
static const string SERVER_FILE_EXTENTION_A = ".zip";	

static const wstring LINK_SERVER_PATH = L"http://files.cnblogs.com/files/BensonLaur/";		//链接，服务器地址

static const wstring LINK_DOWNLOAD_FFMPEG_1 = L"https://github.com/BensonLaur/image-storage/raw/master/General Resource/download/ffmpeg.exe";	//ffmpeg.exe 下载链接1
static const wstring LINK_DOWNLOAD_FFMPEG_2 = L"https://gitee.com/BensonLaur/resource-provider-gitee/raw/master/beslyric/ffmpeg.exe";	//ffmpeg.exe 下载链接2
static const wstring LINK_DOWNLOAD_FFMPEG_3 = L"https://master.dl.sourceforge.net/project/resource-provider-sourceforge/Beslyric/ffmpeg.exe";	//ffmpeg.exe 下载链接3
static const wstring LINK_DOWNLOAD_FFMPEG_4 = L"https://gitlab.com/BensonLaur/resource-provider-gitlab/raw/master/beslyric/ffmpeg.exe";	//ffmpeg.exe 下载链接4
static const wstring LINK_DOWNLOAD_FFMPEG_5 = L"https://bitbucket.org/bensonlaur/resource-provider-bitbucket/raw/1ee69f772fd4819f1b39d953fbf3220c5606b3c8/beslyric/ffmpeg.exe";	//ffmpeg.exe 下载链接5 bitbucket


//static const wstring LINK_UPDATE_ITEM_FILE = L"http://ovfwclhwl.bkt.clouddn.com/update";				//链接，更新项文件(七牛云有时会缓存过去的文件)
static const wstring LINK_UPDATE_ITEM_FILE = L"https://files.cnblogs.com/files/BensonLaur/update.xml";	//链接，更新项文件