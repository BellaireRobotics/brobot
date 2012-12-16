#ifndef _config_h
#define _config_h

#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl3, side, sensorDigitalIn)
#pragma config(Sensor, dgtl4, autonomous_alert_1, sensorLEDtoVCC)
#pragma config(Sensor, dgtl5, autonomous_alert_2, sensorLEDtoVCC)
#pragma config(Sensor, dgtl7, battery_alert_1, sensorLEDtoVCC)
#pragma config(Sensor, dgtl8, battery_alert_2, sensorLEDtoVCC)
#pragma config(Sensor, dgtl12, active_led, sensorLEDtoVCC)
#pragma config(Sensor, I2C_1, armMotor, sensorQuadEncoderOnI2CPort, , AutoAssign)
#pragma config(Motor,  port1, flappers, tmotorVex393, openLoop)
#pragma config(Motor,  port2, frontRight, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3, backRight, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4, frontLeft, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port5, backLeft, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7, arm1, tmotorVex393, openLoop)
#pragma config(Motor,  port8, arm2, tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port10, stabilizer, tmotorVex393, openLoop)

#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#endif
