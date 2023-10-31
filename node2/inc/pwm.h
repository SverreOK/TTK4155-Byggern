#define MCK         84E6

#define PERIOD_A    20E-3
#define DIVA        84
#define CLK_A       1E6
#define CPRDA       (int) (PERIOD_A * MCK / DIVA)

#define DIVB        84
#define CLK_B       1E6


void pwm_init();

void pwm_set_dutycycle(float dutycycle);

void pwm_set_dutycycle_ms();

void pwm_disable();