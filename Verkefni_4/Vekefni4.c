#pragma config(Sensor, in8,    lightSensor,         sensorReflection)
#pragma config(Sensor, dgtl7,  sonarSensor,    sensorSONAR_cm)
#pragma config(Motor,  port2,           rightMotor,    tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           leftMotor,     tmotorServoContinuousRotation, openLoop)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)

void stop_robottasks()
{
	motor[leftMotor] =0;
	motor[rightMotor] =0;
	wait1Msec(100);
}
void turn_left()
{
	motor[leftMotor] =-60;
	motor[rightMotor] =60;
	wait1Msec(900);
}
void turn_right()
{
	motor[leftMotor] = 60;
	motor[rightMotor] = -60;
	wait1Msec(900);
}
void drive()
{
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;


	while(SensorValue(sonarSensor) > 40 || SensorValue(sonarSensor) ==-1)  // While less than 5 rotations on the leftEncoder... 320 hringur
		{
			if(SensorValue(lightSensor)>300)
			{
		 		while(SensorValue(lightSensor)>300)
				{
					stop_robottasks();
				}
			}
			if(vexRT[Btn8U] == 1)
			{
				StopAllTasks();
			}
	  	if(SensorValue[rightEncoder] == SensorValue[leftEncoder]) // If rightEncoder has counted the same amount as leftEncoder:
			{
				// Move Forward
				motor[rightMotor] = 80;		    // Right Motor is run at power level 80
				motor[leftMotor]  = 80;		    // Left Motor is run at power level 80
			}
			else if(SensorValue[rightEncoder] > SensorValue[leftEncoder])	// If rightEncoder has counted more encoder counts
			{
				// Turn slightly right
				motor[rightMotor] = 60;		    // Right Motor is run at power level 60
				motor[leftMotor]  = 80;		    // Left Motor is run at power level 80
			}
			else	// Only runs if leftEncoder has counted more encoder counts
			{
				// Turn slightly left
				motor[rightMotor] = 80;		    // Right Motor is run at power level 80
				motor[leftMotor]  = 60;		    // Left Motor is run at power level 60
			}
		}
}



task main()
{

	while(1 == 1)
	{
		wait1Msec(500);
		drive();
		stop_robottasks();
		int beygja =0;
		beygja = rand()%2;
		if(beygja == 1)
		{
			turn_right();
		}
		else
		{
			turn_left();
		}
		stop_robottasks();
	}

}
