.PHONY: all, install, clean  

TARGET=app-test

CROSSCOMPILE =
PROJECT_DIR  = $(PWD)
OBJSDIR=  $(PROJECT_DIR)/build
CC   = 	  $(CROSSCOMPILE)gcc  
CXX  = 	  $(CROSSCOMPILE)g++ 

CFLAGS += -Wall -g  
VPATH +=


OBJS +=
HDRS += 


include $(PROJECT_DIR)/source/Makefile.mk

LDFLAGS =

all: create $(OBJSDIR)/$(TARGET)

create:
	@mkdir -p $(OBJSDIR)

$(OBJSDIR)/$(TARGET) : $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS) 

$(OBJSDIR)/%.o:%.c $(HDRS)
	$(CC) -c $< -o $@ $(CFLAGS) 

$(OBJSDIR)/%.o:%.cpp $(HDRS)
	$(CXX) -c $< -o $@ $(CFLAGS) 

clean: 
	rm -f $(OBJSDIR)/*.o *~
	rm -f $(TARGET)
	