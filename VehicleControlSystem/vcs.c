/*
 * vcs.c
 *
 *  Created on: ٣١‏/١٢‏/٢٠٢٣
 *      Author: AS.Mahrous
 */
#include <stdio.h>

#define WITH_ENGINE_TEMP_CONTROLLER 1         // Define for engine temperature controller

enum state
{
	OFF,ON                // OFF & ON are constant integers with values of 0 & 1 respectively
};

struct systemData        // this is a data structure that contains all the system data
{
	int ac;
	int engine;
	int engine_temp_controller;
	int speed;
	int room_temp;
	int engine_temp;

}vehicle;

void on_off_print(int s);    // this function to print ON or OFF based on the state in the structure

void trafficLight(char ch);  // this function sets the vehicle speed based on the light sensor readings

void setAC(int roomTemp);    // it changes the AC state & sets the room temp based on the room temp sensor readings

void set_eng_temp_controller(int engineTemp); // changes the state of engine temperature controller

void sensorsMenu(void);         // this function prints the sensors menu

void askTheUser(char *in_ptr);  // based on user input it changes the engine state or quit the system

void vehicleData(char in2);  // this function applies some changes to the vehicle system data

void speed_30_checker(int speed);  // this function checks if speed=30 , to perform specific operations

void displayData(void);      // this function prints the data of the vehicle system

int main(void)
{
	setvbuf(stdout,NULL,_IONBF,0);
	setvbuf(stderr,NULL,_IONBF,0);  // this line & the above is to make the print functions appear correctly on console

	char input=0;
	vehicle.speed=60;           // setting initial value for the speed
	vehicle.room_temp=18;           // setting initial value for the room temperature
	vehicle.engine_temp=100;        // setting initial value for the engine temperature
	askTheUser(&input);             // calling ask the user function & passing input value by address

	return 0;
}

void speed_30_checker(int speed)
{
	if(speed==30)            // if speed = 30 , the following operations happen based on requirement (7.d)
	{
		vehicle.ac=ON;
		vehicle.room_temp*=(5/4) + 1 ;

#if WITH_ENGINE_TEMP_CONTROLLER == 1
		vehicle.engine_temp*=(5/4) + 1 ;
		vehicle.engine_temp_controller=ON;
#endif
	}
}

void displayData(void)
{
	speed_30_checker(vehicle.speed);  // calling speed checker to check if speed=30 before displaying system data
	printf("\n");
	printf("Engine is "); on_off_print(vehicle.engine);
	printf("AC is "); on_off_print(vehicle.ac);
	printf("Vehicle Speed = %d km/h \n",vehicle.speed);
	printf("Room Temperature: %d C \n",vehicle.room_temp);

#if WITH_ENGINE_TEMP_CONTROLLER == 1
	printf("Engine Temperature Controller is "); on_off_print(vehicle.engine_temp_controller);
	printf("Engine Temperature: %d C \n",vehicle.engine_temp);
#endif

	printf("\n");
}

void on_off_print(int s)
{
	if(s==ON)
	{
		printf("ON \n");
	}
	else
	{
		printf("OFF \n");
	}
}

void sensorsMenu(void)
{
	printf("a. Turn off the engine.\n");
	printf("b. Set the traffic light color.\n");
	printf("c. Set the room temperature (Temperature Sensor).\n");

#if WITH_ENGINE_TEMP_CONTROLLER == 1
	printf("d. Set the engine temperature (Engine Temperature Sensor).\n\n");
#endif

	printf("Your Choice is : ");
}

/* I used recursion to avoid program termination and going back again to the menu & ask the user again for input
 * I used the switch case because i'm checking on equality as all user inputs are characters  */

void askTheUser(char *in_ptr)
{
	char in=*in_ptr;
	printf("a. Turn on the vehicle engine.\n");
	printf("b. Turn off the vehicle engine.\n");
	printf("c. Quit the system.\n\n");
	printf("Your Choice is : ");
	scanf(" %c",&in);
	printf("\n");
	switch(in)
		{
		case 'a':
			vehicle.engine=ON;               // changing the state of the engine to ON
			printf("Sensors set menu:\n");
			vehicleData(in);                 // calling the function vehicle data
			break;

		case 'b':
			printf("Turn off the vehicle engine\n");
			printf("\n");
			vehicle.engine=OFF;             // changing the state of the engine to ON
			askTheUser(&in);                // recursion used to return to the same menu again
			break;

		case 'c':
			printf("\n");
			printf("Quit the system\n");
			break;                          // Quitting the system and terminating the program

		default:
			printf("\n");
			printf("Wrong Choice.\n\n");
			askTheUser(&in);                 // recursion used to return to the same menu again
		}
}

void trafficLight(char ch)
{
	printf("Choose the color: ");
	scanf(" %c",&ch);
	switch(ch)
	{
	case 'g':
		vehicle.speed=100;       // setting the speed to 100 kilometer/hour
		break;

	case 'o':
		vehicle.speed=30;        // setting the speed to 30 kilometer/hour
		break;

	case 'r':
		vehicle.speed=0;         // setting the speed to 0 kilometer/hour
		break;

	default:
		printf("Choose between: (g) or (o) or (r)\n");
		trafficLight(ch);                    // recursion used to return to the same menu again
	}
}

void vehicleData(char in2)
{
	sensorsMenu();                         // calling sensor menu function to print the menu
	scanf(" %c",&in2);

	switch(in2)
		{
		case 'a':
			askTheUser(&in2);      // calling ask the user to return to first menu again
			break;

		case 'b':
			trafficLight(in2);    // calling traffic function the vehicle speed based on the light sensor readings
			displayData();        // calling display data function to print all the current system data
			vehicleData(in2);     // recursion used to return to the same menu again (2nd menu)
			break;

		case 'c':
			printf("Enter the room temperature : ");
			scanf("%d",&vehicle.room_temp);
			setAC(vehicle.room_temp);    // calling set AC function to change the AC state
			displayData();               // calling display data function to print all the current system data
			vehicleData(in2);            // recursion used to return to the same menu again (2nd menu)
			break;

		case 'd':
			printf("Enter the engine temperature : ");
			scanf("%d",&vehicle.engine_temp);
			set_eng_temp_controller(vehicle.engine_temp); // function call to change the engine temp controller state
			displayData();            // calling display data function to print all the current system data
			vehicleData(in2);         // recursion used to return to the same menu again (2nd menu)
			break;

		default:
			printf("Wrong Choice.\n\n");
			vehicleData(in2);        // recursion used to return to the same menu again (2nd menu)
		}
}

void set_eng_temp_controller(int engineTemp)
{
#if WITH_ENGINE_TEMP_CONTROLLER == 1
	if(engineTemp<100 || engineTemp>150)   // using (logical or) cause the 2 conditions will give the same modification
	{
		vehicle.engine_temp_controller=ON;   // changing the state of engine temperature controller to ON
		vehicle.engine_temp=125;             // setting the value of engine temperature to be 125 C
	}
	else
	{
		vehicle.engine_temp_controller=OFF;  // changing the state of engine temperature controller to ON
	}
#endif
}

void setAC(int roomTemp)
{
	if(roomTemp<10 || roomTemp>30)      // using (logical or) cause the 2 conditions will give the same modification
	{
		vehicle.ac=ON;                  // changing the state of AC to ON
		vehicle.room_temp=20;           // setting the value of room temperature to be 20 C
	}
	else
	{
		vehicle.ac=OFF;                 // changing the state of AC to OFF
	}
}
