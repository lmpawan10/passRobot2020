#include "robo_init.h"
#include "motor.h"
#include "encoder.h"
#include "joystick.h"

motor gMotor[4];
static Motor_config motor_configurations[4];
// extern JoyStick joystick;
//static  encoder_config encoder_configurations[4];

static void motor_init();
//static void encoder_init();
static void pid_init();

void robo_init()
{
	// printf("\nLet's Begin\n");
	pid_init();
	encoder_init();
	motor_init();

	// joystick.init();
}

static void pid_init()
{
	// 2.6
	gMotor[0].setPID_constraints(1.90, 42, 0.00, 65, -65); //(1.9312, 0.0454, 0.00, 50, -50); //(3.5,0.594,0,40,-40)
	gMotor[1].setPID_constraints(1.79, 49, 0.00, 65, -65); //(2.0536, 0.0397, 0.00, 50, -50); //(2.7,0.36,0,37,-37)
	gMotor[2].setPID_constraints(1.50, 45, 0.00, 65, -65); //(2.0183, 0.0362, 0.00, 50, -50); //1.494(3.4,0.79,0,39,-39)
	gMotor[3].setPID_constraints(1.70, 48, 0.00, 65, -65); //(2.1134, 0.0379, 0.00, 50, -50); //(2.4,0.268,0,37,-37)
							       //gMotors[3].set_omega(40);
}

void motor_init()
{
	motor_configurations[0].htim = &htim8;
	motor_configurations[0].in1_port = GPIOD;
	motor_configurations[0].in1_pin = GPIO_PIN_0;
	motor_configurations[0].in2_port = GPIOE;
	motor_configurations[0].in2_pin = GPIO_PIN_5;
	motor_configurations[0].channel = TIM_CHANNEL_1;
	motor_configurations[0].max_omega = 70;
	motor_configurations[0].tolerance = 1;

	motor_configurations[1].htim = &htim8;
	motor_configurations[1].in1_port = GPIOA;
	motor_configurations[1].in1_pin = GPIO_PIN_10;
	motor_configurations[1].in2_port = GPIOB;
	motor_configurations[1].in2_pin = GPIO_PIN_5;
	motor_configurations[1].channel = TIM_CHANNEL_2;
	motor_configurations[1].max_omega = 70;
	motor_configurations[1].tolerance = 1;

	motor_configurations[2].htim = &htim8;
	motor_configurations[2].in1_port = GPIOE;
	motor_configurations[2].in1_pin = GPIO_PIN_3;
	motor_configurations[2].in2_port = GPIOD;
	motor_configurations[2].in2_pin = GPIO_PIN_2;
	motor_configurations[2].channel = TIM_CHANNEL_3;
	motor_configurations[2].max_omega = 70;
	motor_configurations[2].tolerance = 1;

	motor_configurations[3].htim = &htim8;
	motor_configurations[3].in1_port = GPIOC;
	motor_configurations[3].in1_pin = GPIO_PIN_13;
	motor_configurations[3].in2_port = GPIOE;
	motor_configurations[3].in2_pin = GPIO_PIN_1;
	motor_configurations[3].channel = TIM_CHANNEL_4;
	motor_configurations[3].max_omega = 70;
	motor_configurations[3].tolerance = 1;

	HAL_TIM_Base_Start(&htim8);
	HAL_TIM_PWM_Start(motor_configurations[0].htim, motor_configurations[0].channel);
	HAL_TIM_PWM_Start(motor_configurations[1].htim, motor_configurations[1].channel);
	HAL_TIM_PWM_Start(motor_configurations[2].htim, motor_configurations[2].channel);
	HAL_TIM_PWM_Start(motor_configurations[3].htim, motor_configurations[3].channel);
	for (int i = 0; i < 4; i++)
	{
		gMotor[i].set_config(&motor_configurations[i]);
	}
}
