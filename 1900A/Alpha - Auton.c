#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  catLimSwitch,   sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_5,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_6,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           rightCatMiddle, tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           rightCatFront, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightCatBack,  tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port4,           FL,            tmotorVex393TurboSpeed_MC29, openLoop, encoderPort, I2C_6)
#pragma config(Motor,  port5,           FR,            tmotorVex393TurboSpeed_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port6,           BR,            tmotorVex393TurboSpeed_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port7,           BL,            tmotorVex393TurboSpeed_MC29, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port8,           leftCatFront,  tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           leftCatBack,   tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_5)
#pragma config(Motor,  port10,          leftCatMiddle, tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------------

Variable Library

----------------------------------------------------------------------------------------------------------*/

// Speed Values
float encoderAverage = 0; //establishes encoderAverage as 0;
const int threshold = 15; //establishes deadzone for joystick so that XDRIVE motors don't stall
int catPower = 127; //power to the catapult motors

//Misc Value Holders
bool hasAutonPlayed = false;
int restTime = 800;


void zeroEncoders(){ //zeros all of the motor encoders for new maneuvers
	nMotorEncoder[BL] = 0;
	nMotorEncoder[BR] = 0;
	nMotorEncoder[FL] = 0;
	nMotorEncoder[FR] = 0;
	nMotorEncoder[leftCatBack] = 0;
	nMotorEncoder[rightCatBack] = 0;

}

void setDrivePower(int frontLeft, int frontRight, int backLeft, int backRight){ //function for easily controlling drivetrain motor power
	motor[FL] = frontLeft;
	motor[FR] = frontRight;
	motor[BR] = backRight;
	motor[BL] = backLeft;


}

float getDriveEncoderAverage(){
	encoderAverage = (abs(nMotorEncoder[BL]) + abs(nMotorEncoder[BR]) + abs(nMotorEncoder[FL]) + abs(nMotorEncoder[FR]))/4;
	return encoderAverage;

}

void setCatapultPower(int power){
	motor[leftCatBack] = power;
	motor[leftCatFront] = power;
	motor[rightCatFront] = power;
	motor[rightCatBack] = power;
	motor[leftCatMiddle] = power;
	motor[rightCatMiddle] = power;

}

void driveCatTime(int power, int time){
	motor[rightCatFront] = power;
	motor[rightCatBack] = power;
	motor[leftCatFront] = power;
	motor[leftCatBack] = power;
	motor[leftCatMiddle] = power;
	motor[rightCatMiddle] = power;
	wait1Msec(time);

}

/*----------------------------------------------------------------------------------------------------------

Maneuver Functions (for autonomous) - encoder based

----------------------------------------------------------------------------------------------------------*/

void forward(int power, int counts){//FL, FR, BR, BL
	zeroEncoders();
	while( getDriveEncoderAverage() < counts){
		setDrivePower(127, 127,127,127);
		/*if (nMotorEncoder[BL] > counts){motor[BL] = 0;}
		else if (nMotorEncoder[BR] > counts){motor[BR] = 0}
		else if (nMotorEncoder[FL] > counts){motor[Fl] = 0;}
		else if (nMotorEncoder[FR] > counts){motor[FR] = 0;}*/

	}
}

void backwards(int power, int counts){//FL, FR, BR, BLzeroEncoders();
	while( getDriveEncoderAverage() < counts){
		getDriveEncoderAverage();
		setDrivePower(-127, -127,-127,-127);
	}
}

void strafeLeft(int power, int counts){//FL, FR, BR, BL
	zeroEncoders();
	while(getDriveEncoderAverage() < counts){
		setDrivePower(-127, 127, 127, -127);
	}
}

void strafeRight(int power, int counts){//FL, FR, BR, BL
	zeroEncoders();
	while(getDriveEncoderAverage() < counts){

		setDrivePower(127, -127, -127, 127);
	}
}

void rotate (int power, int counts, int direction){
	if(sgn(direction) == 1){//means that the direction is clockwise
		zeroEncoders();
		while(getDriveEncoderAverage() < counts){//FL, FR, BR, BL
			setDrivePower(-127, 127, 127, -127);

		}

	}
	else if (sgn(direction) == -1){//means the direction is counterclockwise
		zeroEncoders();
		while(getDriveEncoderAverage() < counts){//FL, FR, BR, BL
			setDrivePower(127, -127, -127, 127);

		}
	}
}

void doThaShimmy(){
	int shimmyCounts = 25;
	backwards(127, shimmyCounts);
	forward(127, shimmyCounts);
	backwards(127, shimmyCounts);
	forward(127, shimmyCounts);
	backwards(127, shimmyCounts);
	forward(127, shimmyCounts);
	backwards(127, shimmyCounts);
	forward(127, shimmyCounts);
	backwards(127, shimmyCounts);
	forward(127, shimmyCounts);
	backwards(127, shimmyCounts);
	forward(127, shimmyCounts);
	setDrivePower(0,0,0,0);


}
void rotCatExact(int power, int counts, int direction){
	if(sgn(direction) == 1){//means down
		zeroEncoders();
		while(getDriveEncoderAverage() < counts){//FL, FR, BR, BL
			setCatapultPower(127);
		}
	}
	else if (sgn(direction) == -1){//means pull her up
		zeroEncoders();
		while(getDriveEncoderAverage() < counts){//FL, FR, BR, BL
			setCatapultPower(-127);
		}
	}
}

/*----------------------------------------------------------------------------------------------------------

Miscellaneous Functions - Cutting Motors, resets, etc.

----------------------------------------------------------------------------------------------------------*/
void cutMotors(){
	setDrivePower(0,0,0,0);
	setCatapultPower(0);

}
//Rest Time Functions
void rest(){
	wait1Msec(restTime);
}

void cutAndRest(){
	rest();
	cutMotors();
}

void driveViaTime(string direction,int speed, int time){
	if(direction == "forward"){
		setDrivePower(speed, speed, speed, speed);
		wait1Msec(time);
	}
	else if (direction == "strafeLeft"){
		setDrivePower(-speed, speed, -speed, speed);
		wait1Msec(time);
	}
	else if (direction == "strafeRight"){
		setDrivePower(speed, -speed, speed, -speed);
		wait1Msec(time);
	}
	else if (direction == "backwards"){
		setDrivePower(-speed, -speed, -speed, -speed);
		wait1Msec(time);

	}

}
/*************TASK***********************/

task catapult () { //task to run the catapult motors at the same time as the drivetrain
	while(true){
		if(vexRT[Btn5U] == 1){ //temporary drive controls
			setCatapultPower(catPower);
		}
		else if (vexRT[Btn5D] == 1){
			setCatapultPower(-catPower);
		}
		else if(sensorValue[catLimSwitch] == 1){
			setCatapultPower(0);

		}
		else if (vexRT[Btn8R] == 1){ //ignores button and launches catapult
			setCatapultPower(127);
			wait1Msec(850);

		}
		else {
			setCatapultPower(0);
		}
	}
}

/*----------------------------------------------------------------------------------------------------------

THE FOLLOWING IS THE MAIN TASK AND CONTAINS THE AUTON
TEST CODE. DO NOT LOAD ONTO ROBOT BEFORE COMPETITION!

----------------------------------------------------------------------------------------------------------*/
task main()
{
	/*---------------------------------------
	Play One: Move forward and get three stars, lift up platform to secure stars, move back to clear cube,
	strafe right until almost touching fence. Rotate 90 degrees counter-clockwise and launch stars. Turn 160
	degrees counterclockwise to knock stars off fence. Assuming three far zone stars and two close stars, we get

	Total: 12 points + possible autonomous bonus

	Play Two:
	Do the shimmy, back up, strafe right, then move forward to get cube, lift cube up, rotate 90 degrees
	counter-clockwise and fire cube. Rotate 160ish degrees to knocks stars off

	Total: 12 points + autonomous bonus

	Play Three:
	Do the shimmy, lift catapult, drive forward and knock stars off fence, then strafe right and knock more stars
	off fence. NOTE THIS IS A LAST CASE SCENARIO AND USES ONLY POWER ***VERY UNRELIABLE!!!***

	Total: 1-5 Points + autonomous bonus

	Play Four:
	Do the shimmy and pick up 3 stars in our far zone. This removes them from that zone

	Total: 6 points + autonomous bonus
	---------------------------------------*/


	int LY = 0;
	int LX = 0;
	int RY = 0;
	int RX = 0;
	while(hasAutonPlayed == false){
		if(vexRT[Btn8R] == 1){ //Starts the fence play ***3 POINTS***
			//Play One

			//Shimmy Dance
			doThaShimmy();
			wait1Msec(50);
			rotCatExact(127, 500, -1);
			setDrivePower(127,127,127,127); //drive forward
			wait1Msec(1400);
			setDrivePower(0,0,0,0);
			wait1Msec(500);
			strafeRight(127, 800);
			setDrivePower(0,0,0,0);
			hasAutonPlayed = true; //ends play

		}
		else if(vexRT[Btn8D] == 1){ //starts star - catapult play *** 4-6 POINTS***
			doThaShimmy(); //releases platform
			cutAndRest();
			forward(85, 127); //drives platform under stars in the farzone of the field
			cutAndRest();
			setCatapultPower(-127); //picks stars off ground
			wait1Msec(2500);
			cutAndRest();
			backwards(85, 127); //gets away from cube so we can strafe to fence
			cutAndRest();
			strafeRight(127, 800); //strafes to fence
			cutAndRest();
			setDrivePower(-127, 127, 127, -127); //rotates to launch catapult
			wait1Msec(800);
			cutAndRest();
			setCatapultPower(127); //launches stars
			wait1Msec(3000);
			cutAndRest();
			hasAutonPlayed = true; //ends play
		}


		else if (vexRT[Btn6D] == 1){ //timed encoder straight test
			forward(127, 500);
			backwards(127, 500);

		}
		else if (vexRT[Btn8L] == 1){
			hasAutonPlayed = true;

		}
	}


	startTask(catapult);
	while(true )
	{

		/*
		Ternary Statement: value = (true boolean) ? (false boolean) : value
		If the absolute value of one of these vexRT Channels is greater than the threshold, assign the value
		If it is NOT greater than threshold, make it 0
		*/
		LX = (abs(vexRT[Ch4]) > threshold) ? vexRT[Ch4] : 0;
		LY = (abs(vexRT[Ch3]) > threshold) ? vexRT[Ch3] : 0;
		RY = (abs(vexRT[Ch2]) > threshold) ? vexRT[Ch2] : 0;
		RX = (abs(vexRT[Ch1]) > threshold) ? vexRT[Ch1] : 0;

		motor[FL] = LY + LX;
		motor[FR] = RY - RX;
		motor[BR] = RY + RX;
		motor[BL] = LY - LX;

		wait1Msec(25); // gives computer time to run code in other tasks
		if(vexRT[Btn6U] == 1){ //so that the program will end
			break;
		}
	}
}
