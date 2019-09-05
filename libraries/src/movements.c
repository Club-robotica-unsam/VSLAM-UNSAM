/*=====[movements]=====================================================
*  Author Julian Rodriguez <jnrodriguezz@hotmail.com>
 * All rights reserved.
 * Version: 0.0.0
 * CREA UNSAM (Club de Robotica y Electronica Aplicada - UNSAM)
 */
 
/*=====[Inclusion of own header]=============================================*/

#include "movements.h"

/*=====[Implementations of public functions]=================================*/

// funcion la cual adhiere los señales enable_signal (gpio) y pwm_signal (pwm) al motor
// motor_to_attach

// el parametro velocidad que se introduce es un % de la velocidad maxima que se puede alcanzar
// el duty cycle que puede tener el pulso pwm está discretizado en

// transformacion de velocidad (0 a 100) a duty cycle
uint8_t vel_to_duty_cycle(uint8_t velocity){
	uint8_t duty_cycle = 0;

	if (velocity == 0){
		duty_cycle = 0;
	} else{
		duty_cycle = (int) velocity*2.5; //regla de 3 simple duty_cycle = vel*255/100
	}
	return duty_cycle;
}

// asigna un estado (OFF, BACKWARD, FORWARD) a un motor
void set_motor_state(motor* ptr_motor, motor_state state){
	ptr_motor->actual_state = state;
	if (state == mtrOFF){
		gpioWrite( ptr_motor->fwd_signal_pin, 0); // se pone en 0 las seniales
		gpioWrite( ptr_motor->rev_signal_pin, 0); // de fw y rev
		gpioWrite( ptr_motor->pwm_signal_pin, 0); // asigna una pwm de duty cycle 0, por lo tanto no se habilita y se frena el motor
		ptr_motor->actual_velocity = 0;
	}
	return;
}

// funcion para asignar los pines al motor, tanto gpioMap_t y pwmMap_t son enum
void attach_motor(gpioMap_t rev_signal, gpioMap_t fwd_signal, pwmMap_t pwm_signal, motor* motor_to_attach){
   motor_to_attach->fwd_signal_pin = fwd_signal;
   motor_to_attach->rev_signal_pin = rev_signal;
   motor_to_attach->pwm_signal_pin = pwm_signal;

   set_motor_state(motor_to_attach, mtrOFF); //cuando se attachea un motor a un pin, se apaga
   return;
}  

bool_t forward(motor* ptr_motor, uint8_t velocity){
	bool_t success = 0;
	uint8_t duty_cycle = 0;
	duty_cycle = vel_to_duty_cycle(velocity);

	gpioWrite( ptr_motor->fwd_signal_pin, HIGH ); // cuando la senial fwd este en HIGH y la senial
	gpioWrite( ptr_motor->rev_signal_pin, LOW ); // rev en LOW entonces el motor va hacia adelante

	success = pwmWrite( ptr_motor->pwm_signal_pin, duty_cycle );
	if (success == TRUE ){
		ptr_motor->actual_state = mtrFORWARD;
		ptr_motor->actual_velocity = velocity; //se guarda la velocidad actual del motor en una variable
	}
	return success; //retorna un 1 si se asigno correctamente el duty cycle a la señal pwm
}

bool_t backward(motor* ptr_motor, uint8_t velocity){
	bool_t success = 0;
	uint8_t duty_cycle = 0;
	duty_cycle = vel_to_duty_cycle(velocity);

	gpioWrite( ptr_motor->fwd_signal_pin, LOW ); // cuando la senial rev este en HIGH y la senial
	gpioWrite( ptr_motor->rev_signal_pin, HIGH ); // fwd en LOW entonces el motor va hacia adelante

	success = pwmWrite( ptr_motor->pwm_signal_pin, duty_cycle );
	if (success == TRUE ){
		ptr_motor->actual_state = mtrBACKWARD;
		ptr_motor->actual_velocity = velocity;
	}
	return success; //retorna un 1 si se asigno correctamente el duty cycle a la señal pwm
}

