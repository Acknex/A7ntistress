COLOR newcolor;
COLOR oldcolor;
var factor = 0.0;

function skychange()
{
	vec_set(oldcolor.blue, screen_color.blue);
	vec_set(newcolor.blue, vector(random(255), random(255), random(255)) );
	while(1)
	{
		factor += .2 * time_step;
		factor = clamp(factor, 0.0, 1.0);
		vec_lerp(screen_color.blue, oldcolor.blue, newcolor.blue, factor);
		vec_set(sky_color.blue, screen_color.blue);
		if(factor == 1.0)
		{
			factor = 0.0;
			vec_set(oldcolor.blue, screen_color.blue);
			vec_set(newcolor.blue, vector(random(255), random(255), random(255)) );	
		}	
		wait(1);
	}
}