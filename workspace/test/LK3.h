var:1
float steering;

input:0

output:0

CAN_input:0

CAN_output:1
10:0x7FE:1
steering STEER

code:
{
	// sensor data
	float track_width = internal_data[0];
	float distance = internal_data[1];
	float track_angle = internal_data[2];
	float yaw = internal_data[3];

	// parameters
	float dist_th = 0.2;

	float SC_amin = 4.0;
	float SC_amax = 6.0;
	float SC_atan = (SC_amax - SC_amin) / dist_th;

	float SC_dmin = 16.0;
	float SC_dmax = 40.0;
	float SC_dtan = (SC_dmax - SC_dmin) / dist_th;

	// get difference of angle
	float diff_angle = track_angle - yaw;

	float pi = 3.141594;
	while (diff_angle > pi) {
	    diff_angle -= 2*pi;
	}
	while (diff_angle < -pi) {
	    diff_angle += 2*pi;
	}

	// calculate steering value
	if (track_width == 0.0)	{
		steering = 0.0;
	}
	else {
		float SC_angle, SC_dist;
		float norm_dist = distance / track_width;

		if (distance < dist_th && distance > -dist_th) {
			SC_angle = SC_amax - SC_atan * distance;
			SC_dist = SC_dmax - SC_dtan * distance;
		}
		else {
			SC_angle = SC_amin;
			SC_dist = SC_dmin;
		}

		steering = SC_angle * diff_angle - SC_dist * norm_dist;
	}
}
