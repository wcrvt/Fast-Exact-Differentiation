# KTSP Makefile
# 2013/10/21

CC = g++
LD = g++

CFLAGS  = -I. -Wall -Weffc++ -O3
LDFLAGS = -L. -lm

.SUFFIXES:.cc .hh .o
SRC=$(shell ls *.cc)

# KTSPライブラリは含めないでMake
def: FED.o FED

# KTSPライブラリも含めて全部Make
all: clean FED.o FED

# クリーン
clean:
	@rm -f *.o FED



# 制御用実行関数群をコンパイル
FED.o: FED.cc
	@$(CC) $(CFLAGS) -c $<

# 最終リンク
KTSP: FED.o
	@$(LD) -s -o FED FED.o $(LDFLAGS)

