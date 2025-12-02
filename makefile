CC = gcc
CFLAGS = -Wall -Wextra 
SRCDIR = src
TARGET = intelligent_temp_controller 

SRCS = $(SRCDIR)/main.c \
       $(SRCDIR)/config_manager.c\
       $(SRCDIR)/sensor_simulator.c\
       $(SRCDIR)/decision_engine.c\
#       $(SRCDIR)/logger.c\           #phase2
#       $(SRCDIR)/report_generator.c\  #phase3
#       $(SRCDIR)/cli_interface.c	#phase 3


all :run

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -I$(SRCDIR) $(SRCS) -o $(TARGET)


run: $(TARGET)
	@echo "running ..."
	@echo ""
	./$(TARGET)



clean:
	rm -f $(TARGET)


















