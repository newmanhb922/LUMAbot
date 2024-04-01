CC = gcc
CFLAGS = -Wall -Wextra -g -lpaho-mqtt3c -lwiringPi
TARGET = LUMABOT-1
# SRC_DIR = src
# SRC = $(wildcard $(SRC_DIR)/*.c)
# OBJ = $(SRC:.c=.o)

# all: $(TARGET)

# $(TARGET): $(OBJ)
# 	$(CC) $(CFLAGS) -o $@ $^

# $(SRC_DIR)/%.o: $(SRC_DIR)/%.c
# 	$(CC) $(CFLAGS) -c -o $@ $<

# clean:
# 	rm -f $(OBJ) $(TARGET)

$(TARGET): src/main.c Fsm.o Controller.o MotorControl.o Position.o I2CModule.o MQTTModule.o Ultrasonic.o
	$(CC) $(CFLAGS) -o ($TARGET) src/main.c

Fsm.o: src/AutomatedControls/Fsm.c
	$(CC) $(CFLAGS) -c src/AutomatedControls/Fsm.c

Controller.o: src/Controller/Controller.c
	$(CC) $(CFLAGS) -c src/Controller/Controller.c

MotorControl.o: src/GeneralControls/Motors/MotorControl.c
	$(CC) $(CFLAGS) -c src/GeneralControls/Motors/MotorControl.c

Position.o: src/GeneralControls/Position/Position.c
	$(CC) $(CFLAGS) -c src/GeneralControls/Position/Position.c

I2CModule.o: src/I2C_Module/I2CModule.c
	$(CC) $(CFLAGS) -c src/I2C_Module/I2CModule.c

MQTTModule.o: src/MQTT_Comms/MQTTModule.c
	$(CC) $(CFLAGS) -c src/MQTT_Comms/MQTTModule.c

Ultrasonic.o: src/Sensors/Ultrasonic.c
	$(CC) $(CFLAGS) -c src/Sensors/Ultrasonic.c