bool fla = false;
void Level::camera(Level lvl)
{
	//find furthest player away from center (x and y)
	float percent;
	float x = 0;
	float y = 0;
	float buffer = 500;
	float distance = 0;
	float temp = 0;
	bool isX = false;

	// obtain furthest distance away from center
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if (lvl.player[i]->stats.lifeState == ALIVE)
		{
			// use distance formula from coordinates to (0,0)
			// scale = max (coor x , coor y)

			temp = sqrt(pow(0 - player[i]->body.center.x, 2) + pow(0 - player[i]->body.center.y, 2));
			if (temp > distance)
			{
				distance = temp;
				percent = max(abs(player[i]->body.center.x), abs(player[i]->body.center.y));
				if (percent == player[i]->body.center.x)
					isX = true;
				else
					isX = false;
			}
		}
	}

	
	if (distance > (height_resolution) || distance > (width_resolution))
	{
		if (isX)
			percent = (percent - (width_resolution)) / width_resolution;
		else
			percent = (percent - (height_resolution)) / height_resolution;

		height_ortho = (1.0f + percent) *  height_resolution;
		width_ortho = (1.0f + percent) * width_resolution;
	}

	if (width_ortho > 1.5f * width_resolution || height_ortho > 1.5f * height_resolution)
	{
		width_ortho = 1.5f * width_resolution;
		height_ortho = 1.5f * height_resolution;
	}
	else if (distance < (height_resolution) && distance < (width_resolution))
	{
		width_ortho = width_resolution;
		height_ortho = height_resolution;
	}		
}