TARGET = main.out
HDRS_DIR = /home/umaru/workspace/Engine_control/headers

SRCS = \
         /home/umaru/workspace/Engine_control/scr/EngineControl.c

.PHONY: all clean

all: $(SRCS)
        $(CC) -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)

clean:
        rm -rf $(TARGET)
