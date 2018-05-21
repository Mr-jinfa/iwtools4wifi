#create by jinfa

SRCS := $(wildcard main_wifi.c)
APP_NAME=wifi_app

CC=$(CROSS_COMPILE)gcc
LDFLAGS = -L ../iw_tools/ -lwifi_opt   -L ../iw_tools/ -l iw -lm
CFLAGS = -I../iw_tools/
all:
	@echo -e "\e[0;32;1mCompile $(APP_NAME)...\e[0;36;1m\e[0m"
	$(CC) $(SRCS)  -o $(APP_NAME) $(CFLAGS) $(LDFLAGS)


clean:
	@rm -f $(APP_NAME)

distclean: clean

.PHONY: $(PHONY)