#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
//#include <sys/types.h>
//#include <sys/socket.h>
#include <string.h>
//#include <arpa/inet.h>
//#include <unistd.h>
#include <windows.h>
#include <dos.h>
#include <iostream>
#include <pthread.h>
#include "crc.h"
#include "cJSON.h"
#include "ftp_client.h"
#include "tcp_client.h"
#include <ws2tcpip.h>
#include "proto.h"
#include "udp.h"
#include<iostream>
#include<cstring>

#define У׼ CMD_ACC 
#define ��� CMD_TAKEOFF 
#define ���� CMD_LAND 
#define ���� CMD_UP 
#define ���� CMD_LEFT 
#define �½� CMD_DOWN 
#define ���� CMD_RIGHT 
#define ǰ�� CMD_FORWARD 
#define ��� CMD_BACK 
#define ���� CMD_TAKE_PHOTO 
#define ���� CMD_TOF_ALT 
#define ��� CMD_SHOOT 
#define ��ɸ߶� CMD_TAKEOFF_ALTH
#define ������ת CMD_LEFT_YAW
#define ������ת CMD_RIGHT_YAW
#define �ȴ�(t) Sleep(t)
#define Ҫ��(c) action_cmd(c);
#define Ҫ��߶�(up,height) action_cmd(up,height);
#define Ҫ����(action,power,length) action_cmd(action,power,length);
#define ������() TAKEOFF()
#define ��ʮ�� 1300
#define ��ʮ��� 650
#define ����� else
#define ��� if
#define �� true
#define ���� ==
#define ����(text) printf(text);
#define ������ת TURNLEFT()
#define ������ת TURNRIGHT()


static bool TAKEOFF()
{
	action_cmd(CMD_TAKEOFF);
	if (get_control_mode() == true && batt_get_cap() > 20) {
		set_control_mode();
		return true;
	}
	return false;
}

inline static bool TURNRIGHT()
{
	action_cmd(CMD_RIGHT_TURN, 60, 0);
	return true;
}
inline static bool TURNLEFT()
{
	action_cmd(CMD_LEFT_TURN, 60, 0);
	return true;
}
/*******************************************************
action_cmd(cmd,val,time)

 cmd:�����������£�
	CMD_ACC,                 //У׼
	CMD_TAKEOFF,             //���
	CMD_LAND,                //����
	CMD_FORWARD_TURN,        //ǰ��
	CMD_BACK_TURN,           //��
	CMD_LEFT_TURN,           //��
	CMD_RIGHT_TURN,          //�ҷ�
	CMD_UP,                  //����
	CMD_DOWN,                //�½�
	CMD_LEFT,                //����
	CMD_RIGHT,               //����
	CMD_FORWARD,             //��ǰ
	CMD_BACK,                //���
	CMD_LEFT_YAW,            //����
	CMD_RIGHT_YAW,           //����
	CMD_TAKE_PHOTO,          //����
	CMD_TOF_ALT,             //����
	CMD_TAKEOFF_ALTH,        //��ɸ߶�
	CMD_MODE_CHANGE,         //ģʽ�л�
	CMD_SHOOT,               //���

 val:����ֵ���߸߶�ֵ�����綨�ߺ���ɸ߶�������Ҫ�߶�ֵ(����),ǰ����������Ϊ����ֵ��0-100��

 time:ÿ������ִ��ʱ��(ms)

ע�⣺
ǰ������ÿ��ָ�Ҫ����ʱ���ɻ���Ҫʱ������,ʱ��Խ����Ч��Խ��
����ԽС��ָ��ִ��ʱ��ҪԽ��
*******************************************************************/

void action_start()
{
	if (TAKEOFF() == true) {            //���
		printf("��ɳɹ�\n");
		Sleep(2000);


		/*****

	ע�⣺
	���˻�ʵ�ط���ʾ����ʵ�ʻ�����ÿ���ɻ�������Ҫ΢����
	ÿ�η��к����ʱ����Ҫʱ������, ʱ��Խ����Ч��Խ��
		��ǰ���������ң���ת���м�����ֲ��������ٶ�0-100.   100�������
	*******************************************************************/


		action_cmd(CMD_TAKEOFF);        //���
		Sleep(3000);
		action_cmd(CMD_TOF_ALT, 150);    //����150����

		action_cmd(CMD_FORWARD, 100, 150);  //��ǰ
		Sleep(3000);
		action_cmd(CMD_LEFT, 100, 320);    //����
		Sleep(3000);

		action_cmd(CMD_SHOOT);          //���
		Sleep(3000);

		action_cmd(CMD_RIGHT, 100, 0);    //����
		Sleep(3000);
		action_cmd(CMD_TOF_ALT, 150);    //����150����

		action_cmd(CMD_SHOOT);          //���
		Sleep(3000);

		action_cmd(CMD_RIGHT, 100, 100);    //����
		Sleep(3000);

		action_cmd(CMD_TOF_ALT, 150);    //����150����

		action_cmd(CMD_FORWARD, 100, 700);  //��ǰ
		Sleep(3000);

		action_cmd(CMD_TOF_ALT, 150);    //����150����

		action_cmd(CMD_LEFT_YAW, 100, 1300);    //����ת90��
		Sleep(3000);

		action_cmd(CMD_LEFT_YAW, 100, 1300);    //����ת90��
		Sleep(3000);

		action_cmd(CMD_TOF_ALT, 150);    //����150����

		action_cmd(CMD_BACK, 100, 100);    //���
		Sleep(3000);

		action_cmd(CMD_SHOOT);          //���
		Sleep(3000);
		action_cmd(CMD_TOF_ALT, 150);    //����150����

		action_cmd(CMD_RIGHT, 100, 800);    //����
		Sleep(3000);
		action_cmd(CMD_SHOOT);          //���
		Sleep(3000);
		action_cmd(CMD_RIGHT, 100, 100);    //����
		Sleep(3000);

		action_cmd(CMD_TOF_ALT, 150);    //����150����

		action_cmd(CMD_FORWARD, 100, 700);  //��ǰ
		Sleep(3000);
		action_cmd(CMD_TOF_ALT, 150);    //����150����

		action_cmd(CMD_LEFT, 100, 700);    //����
		Sleep(3000);

		action_cmd(CMD_BACK, 100, 200);    //���
		Sleep(3000);
		action_cmd(CMD_RIGHT_YAW, 100, 1350);    //����ת90��
		Sleep(3000);

		action_cmd(CMD_TAKE_PHOTO);     //����
		Sleep(3000);

		action_cmd(CMD_LEFT, 100, 400);    //����
		Sleep(3000);

		action_cmd(CMD_FORWARD, 100, 250);    //��ǰ
		Sleep(3000);

		action_cmd(CMD_LAND);           //����


	//	action_cmd(CMD_SHOOT);          //���
	//	action_cmd(CMD_TAKE_PHOTO);     //����
	//  Sleep(1000);                    //��ʱ1s
	//	action_cmd(CMD_TOF_ALT,150);    //����150����
	//	action_cmd(CMD_LEFT,50,1000);     //����
	//	Sleep(2000);
	//	action_cmd(CMD_FORWARD,20,1000);  //��ǰ
	//	Sleep(2000);
	//	action_cmd(CMD_BACK,50,2000);     //���
	//	Sleep(2000);
	//	action_cmd(CMD_UP,50,2000);       //����
	//	Sleep(2000);
	//	action_cmd(CMD_DOWN,20,1000);     //����
	//	Sleep(2000);
	//	action_cmd(CMD_RIGHT,20,1000);    //����
	//	action_cmd(CMD_LEFT_YAW,50,1000);   //��ת
	//	action_cmd(CMD_RIGHT_YAW,50, 1000);  //��ת
	//	Sleep(3000);
	//	action_cmd(CMD_LAND);           //����
	}
	else {
		printf("���ʧ��\n");
	}
}

void defa()
{
	��� (������() ���� ��)
	{
		����("��ɳɹ�\n");
		�ȴ�(2000);
		Ҫ��߶�(����, 150);
		�ȴ�(3000);
		Ҫ����(ǰ��, 30, 100); //ǰ��100����,30%����
		�ȴ�(3000);
		Ҫ��(���);
		Ҫ����(������ת, 30, ��ʮ��);
		������ת;
		����;
		Ҫ��(����);
	}
	�����
	{
		����("�������쳣");
	}
}
