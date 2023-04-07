-include $(PROJECT_DIR)/source/fifo/Makefile.mk

CFLAGS  += -I$(PROJECT_DIR)/source
VPATH += $(PROJECT_DIR)/source

OBJS += $(OBJSDIR)/main.o
