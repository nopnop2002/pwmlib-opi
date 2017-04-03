uint16_t pwm_enable();
uint16_t pwm_disable();
uint16_t pwm_prescale(uint16_t val);
uint16_t pwm_entirecycles(uint16_t val);
uint16_t pwm_activecycles(uint16_t val);
uint32_t pwm_freqperiod(void);
uint32_t pwm_begin(float period);
void pwm_active(float period);
void pwm_end(void);
