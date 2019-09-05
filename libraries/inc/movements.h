/*=====[movements]=====================================================
*  Author Julian Rodriguez <jnrodriguezz@hotmail.com>
 * All rights reserved.
 * Version: 0.0.0
 * CREA UNSAM (Club de Robotica y Electronica Aplicada - UNSAM)
 */

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef _MOVEMENTS_H_
#define _MOVEMENTS_H_

/*=====[Inclusions of public function dependencies]==========================*/

#include "sapi.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif


/*=====[public structs ]=====================================================*/
typedef enum{
	LEFT, RIGHT
}turn_direction;

typedef enum{
	mtrOFF, mtrFORWARD, mtrBACKWARD
}motor_state;

typedef struct{
   gpioMap_t fwd_signal_pin; //uint8
   gpioMap_t rev_signal_pin; //uint8
   gpioMap_t pwm_signal_pin;
   uint8_t actual_velocity;
   motor_state actual_state;
}motor;

/*=====[external functions declaration]======================================*/

// el movimiento de cada motor esta comandado por 3 seniales:
// senial pwm => la cual modifica la velocidad del motor
// senial para girar hacia adelante => si la senial esta en 1 entonces el motor se mueve hacia adelante
// senial para girar hacia atras => si la senial esta en 1 entonces el motor se mueve hacia atras
// si ambas señales son 1 entonces el motor se para rapidamente.

// transformacion de velocidad (0 a 100) a duty cycle
uint8_t vel_to_duty_cycle(uint8_t velocity);

// asigna un estado (OFF, BACKWARD, FORWARD) a un motor
void set_motor_state(motor* ptr_motor, motor_state state);

// funcion para asignar los pines al motor, tanto gpioMap_t y pwmMap_t son enum
bool_t attach_motor(gpioMap_t rev_signal, gpioMap_t fwd_signal, pwmMap_t pwm_signal, motor motor_to_attach);

// funciones para el movimiento del auto
bool_t forward(motor* ptr_motor, uint8_t velocity);
bool_t backward(motor* ptr_motor, uint8_t velocity);

/*
bool_t turnLeft();
bool_t turnRight();
*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* _MOVEMENTS_ */
