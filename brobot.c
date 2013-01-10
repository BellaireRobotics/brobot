/***
 * Documentation on VEX Cortex Programming API can be found:
 *  http://www.robotc.net/wiki/VEX2
 */

#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl3, side, sensorDigitalIn)
#pragma config(Sensor, dgtl4, autonomous_alert_1, sensorLEDtoVCC)
#pragma config(Sensor, dgtl5, autonomous_alert_2, sensorLEDtoVCC)
#pragma config(Sensor, dgtl7, battery_alert_1, sensorLEDtoVCC)
#pragma config(Sensor, dgtl8, battery_alert_2, sensorLEDtoVCC)
#pragma config(Sensor, dgtl12, active_led, sensorLEDtoVCC)
#pragma config(Sensor, I2C_1, armMotor, sensorQuadEncoderOnI2CPort, , AutoAssign)
#pragma config(Motor, port1, flappers, tmotorVex393, openLoop)
#pragma config(Motor, port2, frontRight, tmotorVex393, openLoop, reversed)
#pragma config(Motor, port3, backRight, tmotorVex393, openLoop, reversed)
#pragma config(Motor, port4, frontLeft, tmotorVex393, openLoop, reversed)
#pragma config(Motor, port5, backLeft, tmotorVex393, openLoop, reversed)
#pragma config(Motor, port7, arm1, tmotorVex393, openLoop)
#pragma config(Motor, port8, arm2, tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor, port10, stabilizer, tmotorVex393, openLoop)

#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "Vex_Competition_Includes.c"

#define NORM(n) (127 * n / 10)

void forward(int n);
void reverse(int n);
void right(int n);
void left(int n);
void turn_right(int n);
void turn_left(int n);
void stop();
void arm_up(int n);
void arm_down(int n);
void arm_stop();
void flapper_in(int n);
void flapper_out(int n);
void flapper_stop();
void stabilizer_open();
void check_battery();
void check_avg_battery();
void active_on(int mode);
void battery_alert(int mode);
void autonomous_alert(int mode);

void pre_auton() {
  bStopTasksBetweenModes = true;
  active_on(1);
  SensorValue[armMotor] = 0;
}

task autonomous() {
  autonomous_alert(1);
  check_avg_battery();

  stabilizer_open();

  reverse(127);
  Sleep(200);

  forward(127);
  Sleep(75);
  stop();

  arm_up(127);
  Sleep(500);
  arm_stop();

  autonomous_alert(0);
}

task usercontrol() {
  check_battery();

  int X2 = 0, Y1 = 0, X1 = 0, threshold = 15, arm_pos = 0, arm_pos_set = 0;
  int i = 0;

  while (1) {
    if (abs(vexRT[Ch4]) > threshold || abs(vexRT[Ch4Xmtr2]) > threshold) {
      Y1 = vexRT[Ch4] ? vexRT[Ch4] : vexRT[Ch4Xmtr2];
    } else {
      Y1 = 0;
    }

    if (abs(vexRT[Ch1]) > threshold || abs(vexRT[Ch1Xmtr2]) > threshold) {
      X1 = vexRT[Ch1] ? -vexRT[Ch1] : -vexRT[Ch1Xmtr2];
    } else {
      X1 = 0;
    }

    if (abs(vexRT[Ch2]) > threshold || abs(vexRT[Ch2Xmtr2]) > threshold) {
      X2 = vexRT[Ch2] ? vexRT[Ch2] : vexRT[Ch2Xmtr2];
    } else {
      X2 = 0;
    }

    motor[frontRight] = Y1 - X2 - X1;
    motor[backRight] =  Y1 - X2 + X1;
    motor[frontLeft] = Y1 + X2 + X1;
    motor[backLeft] =  Y1 + X2 - X1;

    // Flappers
    if (vexRT[Btn6U] || vexRT[Btn6UXmtr2]) {
      motor[flappers] = 127;
    } else if (vexRT[Btn6D] || vexRT[Btn6DXmtr2]) {
      motor[flappers] = -127;
    } else {
      motor[flappers] = 0;
    }

    // Arms
    if (vexRT[Btn5U] || vexRT[Btn5UXmtr2]) {
      motor[arm1] = 127;
      motor[arm2] = 127;
      arm_pos_set = 0;
    } else if (vexRT[Btn5D] || vexRT[Btn5DXmtr2]) {
      motor[arm1] = -127;
      motor[arm2] = -127;
      arm_pos_set = 0;
    } else {
      motor[arm1] = 0;
      motor[arm2] = 0;

      if (arm_pos_set == 0) {
        arm_pos = SensorValue[I2C_1];
        arm_pos_set = 1;
      }

      // Stabilize arm
      if (SensorValue[I2C_1] > arm_pos) {
        motor[arm1] = 15;
        motor[arm2] = 15;
      } else if (SensorValue[I2C_1] < arm_pos) {
        motor[arm1] = -15;
        motor[arm2] = -15;
      } else {
        motor[arm1] = 0;
        motor[arm2] = 0;
      }
    }

    // Stabilizer
    if (vexRT[Btn7U] || vexRT[Btn7UXmtr2]) {
      motor[stabilizer] = 50;
    } else if (vexRT[Btn7D] || vexRT[Btn7DXmtr2]) {
      motor[stabilizer] = -50;
    } else {
      motor[stabilizer] = 0;
    }

    if (vexRT[Btn7R] && vexRT[Btn8L] || vexRT[Btn7RXmtr2] && vexRT[Btn8LXmtr2]) {
      StartTask(autonomous);

      for (i = 0; i < 15; i++) {
        Sleep(1000);

        if (vexRT[Btn7R] && vexRT[Btn8R] || vexRT[Btn7RXmtr2] && vexRT[Btn8RXmtr2]) {
          autonomous_alert(0);
          break;
        }
      }
    }
  }
}

void forward(int n) {
  //n = NORM(n);
  motor[frontRight] = -n;
  motor[backRight] = -n;
  motor[frontLeft] = n;
  motor[backLeft] =  n;
}

void reverse(int n) {
  forward(-n);
}

void right(int n) {
  //n = NORM(n);
  motor[frontRight] = -n;
  motor[backRight] = n;
  motor[frontLeft] = n;
  motor[backLeft] = -n;
}

void left(int n) {
  right(-n);
}

void turn_right(int n) {
  //n = NORM(n);
  motor[frontRight] = n;
  motor[backRight] =  n;
  motor[frontLeft] = n;
  motor[backLeft] =  n;
}

void turn_left(int n) {
  turn_right(-n);
}

void stop() {
  motor[frontRight] = 0;
  motor[backRight] = 0;
  motor[frontLeft] = 0;
  motor[backLeft] =  0;
}

void arm_up(int n) {
  //n = NORM(n);
  motor[arm1] = n;
  motor[arm2] = n;
}

void arm_down(int n) {
  arm_up(-n);
}

void arm_stop() {
  motor[arm1] = 0;
  motor[arm2] = 0;
}

void flapper_in(int n) {
  //n = NORM(n);
  motor[flappers] = n;
}

void flapper_out(int n) {
  flapper_in(-n);
}

void flapper_stop() {
  motor[flappers] = 0;
}

void stabilizer_open() {
  motor[stabilizer] = 50;
  Sleep(500);
  motor[stabilizer] = 0;
}

void check_battery() {
  if (nImmediateBatteryLevel <= 6) {
    battery_alert(1);
  } else {
    battery_alert(0);
  }
}

void check_avg_battery() {
  if (nAvgBatteryLevel <= 5) {
    battery_alert(1);
  } else {
    battery_alert(0);
  }
}

void active_on(int mode) {
  if (mode > 1 || mode < 0) {
    mode = 0;
  }

  SensorValue[active_led] = mode;
}

void battery_alert(int mode) {
  if (mode > 1 || mode < 0) {
    mode = 0;
  }

  SensorValue[battery_alert_1] = mode;
  SensorValue[battery_alert_2] = mode;
}

void autonomous_alert(int mode) {
  if (mode > 1 || mode < 0) {
    mode = 0;
  }

  SensorValue[autonomous_alert_1] = mode;
  SensorValue[autonomous_alert_2] = mode;
}
