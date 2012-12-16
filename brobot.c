#include "config.h"
#include "actions.h"
#include "Vex_Competition_Includes.c"

void pre_auton() {
  bStopTasksBetweenModes = true;
  active_on(1);
  SensorValue[armMotor] = 0;
}

task autonomous() {
  autonomous_alert(1);
  check_avg_battery();

  stabilize();

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

    if (vexRT[Btn6U] || vexRT[Btn6UXmtr2]) {
      motor[flappers] = 127;
    } else if (vexRT[Btn6D] || vexRT[Btn6DXmtr2]) {
      motor[flappers] = -127;
    } else {
      motor[flappers] = 0;
    }

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

    if (vexRT[Btn7U] || vexRT[Btn7UXmtr2]) {
      motor[stabilizer] = 127;
    } else if (vexRT[Btn7D] || vexRT[Btn7DXmtr2]) {
      motor[stabilizer] = -127;
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
