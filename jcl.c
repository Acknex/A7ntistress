
function AddScore(score)
{
	if(!ingame)return;
	gvScore+= score;
	gvScore = clamp(gvScore, -42, 42);	
	if(gvScore == 42 || gvScore == -42)
	{
		ingame = 0;
		if(me)
		{
			me = NULL;
		}
		StartGame();
	}
}

function CodeParticle()
{
	set(my, PASSABLE | TRANSLUCENT | BRIGHT);
	my.alpha = 100;
	my.roll = random(360);
	vec_scale(my.scale_x, random(0.1)+0.1);
	VECTOR vDist;
	vDist.x = random(-10);
	vDist.y = random(-10)+5;
	vDist.z = random(-10)+5;	
	while(my.alpha > 0)
	{
		my.alpha-= 4*time_step;
		my.roll+= 5*time_step;
		my.x+= vDist.x*time_step;		
		my.y+= vDist.y*time_step;
		my.z+= vDist.z*time_step;
		wait(1);
	}
	ent_remove(me);
}

function SpawnCode()
{
	var i;
	for (i=0; i<10; i++)
	{
		ent_create("0.tga", my.x, CodeParticle);
		ent_create("1.tga", my.x, CodeParticle);
	}
}


action DartDesTodes()
{
	set(my, PASSABLE);
	wait(1);
	c_setminmax(my);
	reset(my, PASSABLE);
	while(my.x < 300)
	{
		c_move(me, vector(20*time_step, 0, 0), nullvector, IGNORE_PASSABLE|ACTIVATE_SHOOT);
		my.roll += time_step * 30;
		wait(1);
	}
	ent_remove(my);
}

function Targeting()
{
	ENTITY* d = ent_create("dart.mdl", nullvector, NULL);
	set(d, PASSABLE);
	
	while(ingame)
	{
		counter += 10*time_step;
		temp.x = mouse_pos.x + 20*sin(counter);
		temp.y = mouse_pos.y + 20*cos(counter);
		temp.z = 50;
		vec_for_screen(temp,camera);
		
		vec_set(d.x, temp);
		
		if(mouse_left)
		{
			vSoundhandle = snd_play(sndFlupp, 100, 0);
			snd_tune(vSoundhandle, 0, random(50)+80, 0);
			you = ent_create("dart.mdl", d.x, DartDesTodes);
			while(mouse_left)wait(1);
			wait(1);
		}		
		wait(1);
	}
	
	ent_remove(d);
}

function TargetEvent()
{
	switch(event_type)
	{
		case EVENT_SHOOT:
		my.skill1 = 1; // I´m hit		
		break;	
	}
}

action MoveTarget()
{
	var vRnd = random(3)+1;
	my.ambient = 100;
	vec_scale(my.scale_x, random(0.8)+0.5);
	wait(1); c_setminmax(my);
	while(my.skill1 == 0 && my.y < 96) // hit or out of view?
	{
		c_move(my, nullvector, vector(0,2*time_step,sin(my.y*vRnd)*2*time_step), IGNORE_PASSABLE | GLIDE);
		c_rotate(my, vector(0,0,my.skill2*time_step), IGNORE_PASSABLE | GLIDE);
		wait(1);
	}	
}

// skill1: hit
// skill2: rotate speed
action InitJcl()
{
	ent_setskin(my, pnlLotter.bmap, 1);
	my.skill2 = random(-15)+random(15);
	my.emask |= ENABLE_SHOOT;
	my.event = TargetEvent;
	MoveTarget();
	while(my.skill1 == 0 && my.y < 96)wait(1);
	if(my.skill1 == 1)
	{
		vSoundhandle = snd_play(sndDie, 100, 0);
		snd_tune(vSoundhandle, 0, random(130)+50, 0);
		SpawnCode();
		set(my, INVISIBLE | PASSABLE);
		AddScore(1);
		wait(3);
	}
	else
	{
	 	AddScore(-1);
	}
	if(my)
	{
		ent_remove(my);
		my = NULL;		
	}
}


action InitHalo()
{
	set(my, PASSABLE | BRIGHT | TRANSLUCENT);
	vec_scale(my.scale_x, 0.01);
	while(my.alpha > 0)
	{
		my.alpha-= 3*time_step;
		my.scale_x+= 0.3*time_step;
		my.scale_y = my.scale_x;
		my.scale_z = my.scale_x;
		wait(1);
	}
	ent_remove(my);
}

// skill1: hit
// skill2: rotate speed
action InitEight()
{
	my.skill2 = 0;
	var vRnd = random(3)+1;
	var vRotSpeed = random(-15)+random(15);
	my.emask |= ENABLE_SHOOT;
	my.event = TargetEvent;
	MoveTarget();
	while(my.skill1 == 0 && my.y < 96)wait(1);
	if(my.skill1 == 1)
	{
		ent_create("halo.tga", my.x, InitHalo);
		set(my, INVISIBLE | PASSABLE);
		you = ent_next(NULL); // retrieve first entity
 		while (you) // repeat until there are no more entities
		{ 
			you.skill1 = 1; // make entity invisible
 			you = ent_next(you); // get next entity
 		}	
 		
	}	
	ent_remove(my);
	my = NULL;	
}

action SpawnJcls()
{
	set(my, PASSABLE | INVISIBLE);
	my.z+= 16;
	while(ingame)
	{
		if(random(100) > 10)
		{
			ent_create("jcl.mdl", my.x, InitJcl);
		}
		else
		{
			ent_create("eight.mdl", my.x, InitEight);
		}
		wait(random(-1)-0.5);
	}
}


