#**********************************************************************************
#
#   Makefile do Dado Burger (TF INF01203)
#
#   Uso (na raiz do projeto):
#     make            -> compila o executável dado_burger.exe
#     make run        -> compila se necessário e abre o jogo
#     make clean      -> apaga objetos e o executável
#
#   O compilador é resolvido nesta ordem:
#     1. tools/w64devkit/bin/gcc.exe   (toolchain portátil do projeto)
#     2. gcc do PATH                   (ex.: C:/raylib/w64devkit/bin)
#
#   A raylib é procurada nesta ordem:
#     1. tools/raylib                  (pacote portátil do projeto)
#     2. C:/raylib                     (instalador oficial da raylib)
#     3. RAYLIB_PATH=<caminho>         (passe na linha de comando se instalar
#                                       em outro lugar: make RAYLIB_PATH=D:/libs/raylib)
#
#**********************************************************************************

.PHONY: all run clean

PROJECT_NAME ?= dado_burger
TARGET       = $(PROJECT_NAME).exe
BUILD_DIR    = build

# -------------------------------- Compilador --------------------------------
ifeq ($(OS),Windows_NT)
    ifneq ($(wildcard tools/w64devkit/bin/gcc.exe),)
        CC := tools/w64devkit/bin/gcc.exe
    endif
endif
CC ?= gcc

# ---------------------------------- raylib ----------------------------------
RAYLIB_PATH ?= $(if $(wildcard tools/raylib/include/raylib.h),tools/raylib,$(if $(wildcard C:/raylib/include/raylib.h),C:/raylib,tools/raylib))

# ----------------------------------- Flags ----------------------------------
CFLAGS  := -Wall -std=c99 -O1
INCLUDES := -I$(RAYLIB_PATH)/include
LDLIBS   := -L$(RAYLIB_PATH)/lib -lraylib -lopengl32 -lgdi32 -lwinmm

# --------------------------------- Fontes -----------------------------------
SRC_DIRS := src src/core src/core/data_structures src/core/sort src/core/time src/presentation src/io src/gameplay
SRCS := $(foreach d,$(SRC_DIRS),$(wildcard $(d)/*.c))
OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))

# ---------------------------------- Regras ----------------------------------
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(LDLIBS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
	@echo Limpeza concluida
