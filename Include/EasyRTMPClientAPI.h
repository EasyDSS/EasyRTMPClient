/*
	Copyright (c) 2013-2015 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
#ifndef _Easy_RTMPClient_API_H
#define _Easy_RTMPClient_API_H

#include "EasyTypes.h"

#define	RTMP_PROG_NAME	"EasyRTMPClient v1.6.17.0901"

/*
	_channelId:		ͨ����,��ʱ����
	_channelPtr:	ͨ����Ӧ����,��ʱ����
	_frameType:		EASY_SDK_VIDEO_FRAME_FLAG/EASY_SDK_AUDIO_FRAME_FLAG/EASY_SDK_EVENT_FRAME_FLAG/...	
	_pBuf:			�ص������ݲ��֣������÷���Demo
	_frameInfo:		֡�ṹ����
*/
typedef int (Easy_APICALL *RTSPSourceCallBack)( int _channelId, void *_channelPtr, int _frameType, char *pBuf, RTSP_FRAME_INFO* _frameInfo);


/*
	userPtr: �û��Զ�������ָ��
	frameType: EASY_SDK_VIDEO_FRAME_FLAG/EASY_SDK_AUDIO_FRAME_FLAG/EASY_SDK_EVENT_FRAME_FLAG/...	
	pBuf: ԭʼ��Ƶ����Ƶ������
	segLen: ��ǰ֡���ݷ�Ƭ����
	length: ��ǰ֡����   
	timestamp: ��ǰ֡ʱ���
remark:
  if ( NULL == pBuf && -1 == segLen ) 
  { 
      1. lenֵָ��Ϊ��ǰ��Ƶ/��Ƶ����Ƶ/��Ƶ��frameType���֣��������ͣ�
      2. lenֵ��Ϊ��������ʱ������ܵ�ֵ�μ�EasyTypes.h ������Ƶ/��Ƶ��������
	  3. lenֵ��Ϊ��������ʱ������ص���һ��rtmp�Ự��������Ƶ/��Ƶ���ص�һ�Σ�
	     �һص�ʱ�����������ڴ��ݾ�����Ƶ/��Ƶ����֮ǰ
  }
*/
/*
typedef int (Easy_APICALL *RTMPSourceCallBack)( 
											   void * userPtr,
											   int frameType,
											   unsigned char * pBuf,
											   unsigned int segLen,
											   unsigned int length,
											   unsigned int timestamp 
											   );
*/



#define RTMPSourceCallBack                    RTSPSourceCallBack
#define Easy_RTMP_Handle                      void *
#define EASY_SDK_AUDIO_CODEC_MP3              2

typedef enum
{
	Easy_RTMP_Unsupported_codec = -100,
	Easy_RTMP_Handshake_error = -101,
	Easy_RTMP_Network_exception = -102,
	Easy_RTMP_Connect_error = -103,
	Easy_RTMP_Createstream_error = -104,
	Easy_RTMP_Play_error = -105
}Easy_RTMP_ERROR_CODE;


#ifdef __cplusplus
extern "C"
{
#endif
	/* ��ȡ���һ�δ���Ĵ����� */
	Easy_API int Easy_APICALL EasyRTMP_GetErrCode(Easy_RTMP_Handle handle);

	/* ���� */
#ifdef ANDROID
	Easy_API int Easy_APICALL EasyRTMP_Activate(char *license, char* userPtr);
#else
	Easy_API int Easy_APICALL EasyRTMP_Activate(char *license);
#endif

	/* ����RTMPClient���  ����0��ʾ�ɹ������ط�0��ʾʧ�� */
	Easy_API int Easy_APICALL EasyRTMP_Init(Easy_RTMP_Handle *handle);

	/* �ͷ�RTMPClient ����ΪRTMPClient��� */
	Easy_API int Easy_APICALL EasyRTMP_Deinit(Easy_RTMP_Handle *handle);

	/* �������ݻص� */
	Easy_API int Easy_APICALL EasyRTMP_SetCallback(
												   Easy_RTMP_Handle handle, 
												   RTMPSourceCallBack _callback
												   );  

	/* �������� */
	Easy_API int Easy_APICALL EasyRTMP_OpenStream(
												  Easy_RTMP_Handle handle, 
												  //int _channelid, 
												  const char *_url, 
												  //EASY_RTP_CONNECT_TYPE _connType, 
												  //unsigned int _mediaType, 
												  //char *_username, 
												  //char *_password, 
												  void *userPtr, //�û��Զ�������ָ��
												  int _reconn/*1000��ʾ������,���������Ͽ��Զ�����, ����ֵΪ���Ӵ���*/, 
												  int outFlvTag/*Ĭ��Ϊ0,���ص����ԭʼ����Ƶ֡, ���Ϊ1,�����flv tag��*/, 
												  //int heartbeatType/*0x00:���������� 0x01:OPTIONS 0x02:GET_PARAMETER*/,
												  int _verbosity/*��־��ӡ����ȼ���0��ʾ�����*/
												  );
	
	/* �ر������� */
	Easy_API int Easy_APICALL EasyRTMP_CloseStream(Easy_RTMP_Handle handle);

#ifdef __cplusplus
}
#endif

#endif
