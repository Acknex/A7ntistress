

function coniscale()
{
	while(my)
	{
		if(my.skill1 == 1)
		{
			my.skill1 = 20;
		}
		while(my.skill1 > 0)
		{
			my.skill2+= 2*time_step;
			my.skill1-= 0.5*time_step;
			my.scale_y+= sinv(my.skill2*10);
			my.scale_x+= sinv(my.skill2*10);
			wait(1);
		}
		wait(1);
	}
}

void conimove()
{
	set(my, PASSABLE);
	var vTimer = 0;
	my.ambient = 100;
	coniscale();
	while (me)
	{	
		vTimer += time_step;	
		my->x = 200 * sinv(5*vTimer) + 1000;
		my->y = 320 * sinv(5*vTimer);
		my->z = 240 * cosv(5*vTimer);	
		my.pan = 50 * sinv(5*vTimer);		
		wait(1);
	}
}

void InitConitec()
{
	ent_create("conitec.tga", nullvector, conimove);	
}

