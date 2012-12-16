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
void stabilize();
void check_battery();
void check_avg_battery();
void active_on(int mode);
void battery_alert(int mode);
void autonomous_alert(int mode);
