#    File : makefile
#    Programmer : Mohammad Lotfi
#    Used : make
#    Design Pattern : none
#    Types of memory : none
#    Total Tread : Nothing
#    Site : https://www.mahsen.ir
#    Tel : +989124662703
#    Email : info@mahsen.ir
#    Last Update : 2025/1/31

# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -Wall -fdiagnostics-color=always -g -pthread -static
# Library
LIBRARY = -lsqlite3 -ldl
# Build dir
BUILD_DIR = Build
# Target executable
TARGET = $(BUILD_DIR)/Application
# Source files
SRCS = *.cpp \
	Module/*.cpp \
	Core/*.cpp
# Source files www
SRCS_WWW = Web/www/

all:
	clang-format -i -style=file  $(SRCS)
	clear
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LIBRARY_DIR) $(LIBRARY)
	chmod +x $(TARGET)

	sudo docker start 2c750d76098f
	sudo docker cp "$(SRCS_WWW)" "2c750d76098f:/"
	sudo docker cp "$(TARGET)" "2c750d76098f:/www/cgi-bin/"	
	sudo docker exec -it 2c750d76098f /etc/init.d/uhttpd start

clean:
	del $(TARGET)
