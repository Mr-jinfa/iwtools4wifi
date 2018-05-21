/*create by jinfa 
 *这是一个应用接口,它依赖于iwlist.c iwevent.c iwconfig.c
 *由之前的iwmulticall.c改成
 *
*/

/***************************** INCLUDES *****************************/

#include <libgen.h>	/* Basename */
#include "iwlib.h"

#define WITHNO_ACCOUNT		0
#define WITH_ACCOUNT 		1

/*
 *获取wifi对象信息
 *operstate_fd 由open (/sys/class/net/wlan0/operstate)可得
 *operstate fd 为0时 link参数无效。 
*/
struct p_curwifi *get_curwifi_info(struct p_curwifi *cur_wifi, int operstate_fd) //调用iwconfig
{
   if(main_iwconfig(cur_wifi, operstate_fd))
   		return NULL;
   	return cur_wifi;
}

//获取wifi列表
void get_wifi_list(struct p_wifi_list *wifi_list_head)	//调用iwlist
{
   main_iwlist(wifi_list_head);
}

/*
 *功能:给用户提供链接wifi接口
 *参数:
 *conn_wifi:用户传入需要链接的对象
 *mode: 用户指定系统是否只使用conn_wifi这个信息链接wifi
 *当mode为WITH_ACCOUNT系统只使用conn_wifi这个信息链接wifi
 *当mode为WITHNO_ACCOUNT系统使用当前wpa2_wpa.conf脚本存留的信息链接wifi \
 *这种情况多用于,用户已经配置wifi并系统刚启动的情况
*/
int link_wifi(struct p_connect *conn_wifi, int mode)
{
	char acount[256] = {0};
	if(mode == WITH_ACCOUNT)
	{
		sprintf(acount, "sed  -i \" s/ssid=.*/ssid=\"\\\"%s\"\\\" / ; s/psk=.*/psk=\"\\\"%s\"\\\" /\" /etc/wpa_wpa2.conf", \
										conn_wifi->essid, conn_wifi->password_wifi);
		system(acount);
	}
   system("wpa_supplicant -iwlan0 -B -c /etc/wpa_wpa2.conf");
   return 0;
}

int open_udhcpc()
{
	//启动udhcpc动态获取ip
	int ret = system("udhcpc -b -i wlan0 -p /var/run/udhcpc.pid  -R");
	if (-1 == ret || 0 == WIFEXITED(ret) || WEXITSTATUS(ret) != 0)
	{
		printf("run udhcpc error\n");
		return -1;
	}
	return 0;
}

int close_udhcpc()
{
	int ret = system("killall udhcpc");
	if (-1 == ret || 0 == WIFEXITED(ret) || WEXITSTATUS(ret) != 0)
	{
		printf("killall udhcpc error\n");
		return -1;
	}
	return 0;
}
int unlink_wifi(void)
{
	//这里关闭wpa_supplicant
	int ret = system("killall wpa_supplicant");
	if (-1 == ret || 0 == WIFEXITED(ret) || WEXITSTATUS(ret) != 0)
	{
		printf("killall wpa_supplicant error\n");
		return -1 ;
	}
	return 0;
}
///tongzhi 



