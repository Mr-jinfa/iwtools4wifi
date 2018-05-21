#include <stdio.h>
#include "iwlib.h"

#define PERIPHERAL_MAGIC	0x40

#define WIFIPOWERON_CMD			_IOW(PERIPHERAL_MAGIC,0x01,unsigned long)
#define WIFIPOWERDOWN_CMD		_IOW(PERIPHERAL_MAGIC,0x02,unsigned long)

#define GPRSRESET_CMD			_IOW(PERIPHERAL_MAGIC,0x03,unsigned long)
#define GPRSPOWERON_CMD			_IOW(PERIPHERAL_MAGIC,0x04,unsigned long)
#define GPRSPOWERDOWN_CMD		_IOW(PERIPHERAL_MAGIC,0x05,unsigned long)

#define WITHNO_ACCOUNT		0
#define WITH_ACCOUNT 		1

void show_list();

#define wifi_script 		   "/etc/wpa_wpa2.conf"

void usage(void)
{
	printf("*********************************\n");	
	printf("\t1.link .\n");	
	printf("\t2.unlink .\n");	
//	printf("\t3.get dynamic ip  .\n");
	printf("\t4.exit .\n");
	printf("*********************************\n");	
	printf("input:");
}

int main(int argc, char const *argv[])
{
	struct p_connect *con_wifi;
	struct p_curwifi *cur_wifi;
	struct p_wifi_list *wifi_list_head;
	int fd_wifi_script=0, pperipheral_fd;	
	int 		  operstate_fd;
	struct p_wifi_list *q;
	if((fd_wifi_script =open(wifi_script, O_RDONLY)) <0)
	{
		printf("please prepare a wpa_supplicant run script\n");
		return -1;
	}
	close(fd_wifi_script);

	con_wifi 		= malloc(sizeof(struct p_connect));
	cur_wifi 		= malloc(sizeof(struct p_curwifi));	
	wifi_list_head 	= malloc(sizeof(struct p_wifi_list));
	wifi_list_head->next = NULL;

	operstate_fd =open("/sys/class/net/wlan0/operstate", O_RDONLY);
	if(operstate_fd <0)
	{
		printf("open operstate fd fail\n");
		return -1;
	}

	bzero(cur_wifi, sizeof(struct p_curwifi));
	get_curwifi_info(cur_wifi, operstate_fd);
	printf("[test] curwifi ssid:%s\n", cur_wifi->ESSID);
	printf("[test] curwifi Singal:%d\n", cur_wifi->Singal);	
	printf("[test] curwifi link:%d\n", cur_wifi->link);
	close(operstate_fd);
	bzero(wifi_list_head, sizeof(struct p_wifi_list));
//	get_wifi_list(wifi_list_head);
	
//	show_list(wifi_list_head);
	int flag=0,run=1, mode=0;
	char *IP;
#if 0
	ioctl(pperipheral_fd,WIFIPOWERON_CMD,0);
	ioctl(pperipheral_fd,GPRSPOWERDOWN_CMD,0);

	unlink_wifi();
	close_udhcpc();
	sleep(1);
	
	link_wifi(con_wifi, 0);
	sleep(1);
	open_udhcpc();
	bzero(cur_wifi, sizeof(struct p_curwifi));
	get_curwifi_info(cur_wifi);
	printf("[test] curwifi ssid:%s\n", cur_wifi->ESSID);
	printf("[test] curwifi Singal:%d\n", cur_wifi->Singal); 
	printf("[test] curwifi link:%d\n", cur_wifi->link);
#endif
		

#if 0
	usage();
	while(run)
	{
		scanf("%d", &flag);
		switch (flag)
		{
			case 1:
#if 0
				printf("please input mode & account & password\n");
				printf("flag:");
				scanf("%d", &mode);
				if(mode == WITH_ACCOUNT)
				{
					printf("account:");
					scanf("%s", con_wifi->essid);
					printf("password:");
					scanf("%s", con_wifi->password_wifi);
				}
#endif
				printf("go...\n");
				
				link_wifi(con_wifi, mode);	//在链接之前先做unlink清除上下文
				break;
			case 2:
				unlink_wifi();
				break;
			case 4:
				run = 0;
				break;
			default :
				break;
		}
	}

	free(con_wifi);
	free(cur_wifi);
	q = wifi_list_head;
	while(q !=NULL)
	{
		free(q);
		q = q->next;
	}
#endif
	return 0;
}

void show_list(struct p_wifi_list *wifi_list_head)
{
	struct p_wifi_list *q = wifi_list_head->next;
	printf("\n========================================================================\n");
	while(q !=NULL)
	{
		printf("\t[test] list ssid:%s\n", q->ESSID);
		printf("\t[test] list Singal:%d\n", q->Singal);
		q = q->next;
	}
	printf("========================================================================\n");	
}
