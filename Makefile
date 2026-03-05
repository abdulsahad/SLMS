CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
TARGET = slms

SRCDIR = src
OBJDIR = obj

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

all: $(OBJDIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
ifeq ($(OS),Windows_NT)
	if not exist $(OBJDIR) mkdir $(OBJDIR)
else
	mkdir -p $(OBJDIR)
endif

clean:
ifeq ($(OS),Windows_NT)
	if exist $(OBJDIR) rmdir /s /q $(OBJDIR)
	if exist $(TARGET).exe del $(TARGET).exe
else
	rm -rf $(OBJDIR) $(TARGET)
endif