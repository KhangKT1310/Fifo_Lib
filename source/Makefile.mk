# -include $(PROJECT_DIR)/source/fifo/Makefile.mk
-include $(PROJECT_DIR)/source/myfifo/Makefile.mk

CFLAGS  += -I$(PROJECT_DIR)/source
VPATH += $(PROJECT_DIR)/source

OBJS += $(OBJSDIR)/main.o
