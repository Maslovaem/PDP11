CC = g++
BUILD_DIR = build
SOURCE_DIR = source
HEADER_DIR = ../headers
CXXFLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

FILES = command.c load.c logger.c main.c mem.c run.c test_mem.c
OBJS = $(addprefix $(SOURCE_DIR)/, $(FILES))

all: $(OBJS)
	$(CC) -I$(HEADER_DIR) $(OBJS) -o PDP11

%.o: %.c
	g++ -o $@ -c $< $(compile_flags) $(build_flags) $(addprefix -I, $(relative_include_dirs))


$(SOURCE_DIR)/%.o: $(SOURCE_DIR)/%.c
	echo $(CC) -I$(HEADER_DIR) -c $(SOURCE_DIR)/*.c $(CXXFLAGS)
	$(CC) -I$(HEADER_DIR) -c $(SOURCE_DIR)/*.c $(CXXFLAGS)

start: all
	.\PDP11.exe


