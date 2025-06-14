# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Include directories
INCLUDES = -I./includes -I./config -I./database -I./models -I./routes -I/usr/include/mysql-cppconn-8/

# Libraries to link
LIBS = -lmysqlcppconn -lpthread

# JSON library (nlohmann/json) is header-only, no need to link

# Source files
SOURCES = main.cpp \
          config/env.cpp \
          database/mysql.cpp \
          models/transaction.cpp \
          routes/transaction_routes.cpp

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = server

# Default target
all: $(EXECUTABLE)

# Link the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

# Compile object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
