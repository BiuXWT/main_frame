TARGET = ./bin/mainframe
DEBUG_TARGET = ./bin/mainframe_g

SRC = ./src
SOURCES = $(wildcard $(SRC)/*.c ${SHARE}/*.c)
OBJS = $(patsubst %.c, %.o, $(SOURCES))
LSTS = $(patsubst %.c, %.lst, $(SOURCES))

#API_PATH = ./bwutils
#API_SRC = $(wildcard $(API_PATH)/*.c ${SHARE}/*.c)
#API_OBJS = $(patsubst %.c, %.o, $(API_SRC))
#API_LSTS = $(patsubst %.c, %.lst, $(API_SRC))

EXTRAINCDIRS = ./inc
#EXTRAINCDIRS =
#EXTRAINCDIRS += ./bwutils
#EXTRAINCDIRS += ./h
#EXTRAINCDIRS += ./h/bwinc
#EXTRAINCDIRS += ./h/libxml

INC = $(patsubst %,-I%,$(EXTRAINCDIRS))
LIB=`xml2-config --libs` -L./lib

HEADERS = $(wildcard ./inc/*.h)

OPTIM=-O2
DEBUG=-g 
STRIP=-s
	
CC=gcc
AR=ar

CFLAGS = -D_DEBUG_MAIN -D_GNU_SOURCE  -D__STDC_CONSTANT_MACROS $(DEBUG) $(OPTIM) -Wall $(INC) 
CPPFLAGS = -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS $(DEBUG) $(OPTIM) -Wall $(INC) 
#LDFLAGS1 = $(LIB) -lbw -lutils_x64 -lpthread 
LDFLAGS1 = $(LIB) -lm -lpthread 

LDFLAGS = $(LDFLAGS1)

all:$(TARGET) $(DEBUG_TARGET)

$(TARGET): $(OBJS) 
	$(CC) $(STRIP) $(OBJS)  \
	$(LDFLAGS) \
	-o $(TARGET) 
	
$(DEBUG_TARGET): $(OBJS)
	$(CC) $(OBJS)   \
	$(LDFLAGS) \
	-o $(DEBUG_TARGET) 
	

%.o:%.c 
	$(CC) $(CFLAGS) \
	-c $<  -o $@
	
%.o:%.cpp $(HEADERS) 
	$(CPP) $(CPPFLAGS) \
	-c $<  -o $@
	
clean: 
	rm -vf $(OBJS)  \
 	$(TARGET) $(DEBUG_TARGET) 
