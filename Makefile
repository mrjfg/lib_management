CC      := g++
CCOPT := -g -Wall -O2

 
#当前makefile路径
CURRENT_PATH := $(shell pwd)
#头文件路径
INC_PATH := $(CURRENT_PATH)/inc
#lib库路径
LIB_PATH := $(CURRENT_PATH)/lib
#源文件路径
SRC_PATH := $(CURRENT_PATH)/src
#object文件路径
OBJS_PATH := $(CURRENT_PATH)/build


#获取.cpp文件
SrcFiles=$(wildcard $(SRC_PATH)/*.cpp)
#使用替换函数获取.o文件
ObjFiles=$(patsubst %.cpp,%.o,$(SrcFiles))
#生成的可执行文件
all:main

#目标文件依赖于.o文件
main:$(ObjFiles)
	g++ -o $@ -I ./inc $(SrcFiles)	`mysql_config --cflags --libs`
#.o文件依赖于.cpp文件，通配使用，一条就够
%.o:%.cpp
	g++ -c -I ./inc $<

.PHONY:clean all

clean:
	rm -f *.o
	rm -f main 