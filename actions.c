#include "actions.h"

#define NORM(n) (127 * n / 10)

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

void stabilize() {
  motor[stabilizer] = 127;
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
