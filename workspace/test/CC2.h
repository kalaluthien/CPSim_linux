var:2
float accel;
float brake;

input:0

output:0

CAN_input:1
0:0x7FC:2
car_output[TRACK_DISTANCE]

CAN_output:1
10:0x7FF:2
accel ACCEL
brake BRAKE

code:
{
	// sensor data
	float speed = internal_data[0];
	float distance = car_output[DISTANCE];

	// parameters
	float speed_min = 4.5 * distance + 6.0;
	float speed_max = 4.5 * distance + 8.0;

	float SC_atan = 0.2;
	float SC_btan = 0.15;

	// calculate acceleration & brake value
	accel = SC_atan * (speed_min - speed);
	brake = SC_btan * (speed - speed_max);
}
