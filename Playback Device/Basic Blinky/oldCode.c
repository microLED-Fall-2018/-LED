void TCC0_Handler()
{
	//testByColor(RED,1);
	//testByColor(GREEN,1);
	//testByColor(BLUE,1);
	// Action completed RED, GREEN, BLUE
	if (TCC0->INTFLAG.reg & TCC_INTFLAG_MC0)
	{
		TCC0->CC[RED].reg += diffs[RED];
		action(RED); // Load next action
		TCC0->INTFLAG.reg |= TCC_INTFLAG_MC0;
	}
	
	if (TCC0->INTFLAG.reg & TCC_INTFLAG_MC1)
	{
		TCC0->CC[GREEN].reg += diffs[GREEN];
		action(GREEN);
		TCC0->INTFLAG.reg |= TCC_INTFLAG_MC1;
	}
	
	if (TCC0->INTFLAG.reg & TCC_INTFLAG_MC2)
	{
		TCC0->CC[BLUE].reg += diffs[BLUE];
		action(BLUE);
		TCC0->INTFLAG.reg |= TCC_INTFLAG_MC2;
	}
		
	// Beat completed
	if (TCC0->INTFLAG.reg & TCC_INTFLAG_OVF)
	{
		// RED = 0, GREEN = 1, BLUE = 2
		uint8_t i;
		
		for(i = 0; i < 3; i++)
		{
			
		// testByColor(i,1);
			
			if (--beatsRemaining[i] == 0)
			{
				nextInstruction(i);
				processInstruction(sequences[sequenceCurr][tracker[i].curr]);			
				/*TCC0->INTFLAG.reg |= TCC_INTFLAG_MC0;
				TCC0->INTFLAG.reg |= TCC_INTFLAG_MC1;
				TCC0->INTFLAG.reg |= TCC_INTFLAG_MC2;
				TCC0->INTFLAG.reg |= TCC_INTFLAG_OVF;
				return;*/		
			}
			else
				TCC0->CC[i].reg = TCC0->COUNT.reg + diffs[i];
		}
		TCC0->INTFLAG.reg |= TCC_INTFLAG_OVF;
	}
	
	//testByColor(RED,0);
	//testByColor(GREEN,0);
	//testByColor(BLUE,0);
}

void TC3_Handler()
{	
	//testByColor(RED,1);

	if ((TC3->COUNT8.INTFLAG.reg & TC_INTFLAG_MC0) && TC3->COUNT8.CC[0].reg != 0)
	{
		PORTA.OUT.reg |= 1 << 2;
		TC3->COUNT8.INTFLAG.reg |= TC_INTFLAG_MC0;
	}
	else if ((TC3->COUNT8.INTFLAG.reg & TC_INTFLAG_OVF) && TC3->COUNT8.CC[0].reg != 255)
	{
		PORTA.OUT.reg &= ~(1 << 2);
		TC3->COUNT8.INTFLAG.reg |= TC_INTFLAG_OVF;
	}	
	//testByColor(RED,0);

}

void TC4_Handler()
{
	//testByColor(GREEN,1);

	if ((TC4->COUNT8.INTFLAG.reg & TC_INTFLAG_MC0) && TC4->COUNT8.CC[0].reg != 0)
	{
		PORTA.OUT.reg |= (1 << 4);
		TC4->COUNT8.INTFLAG.reg |= TC_INTFLAG_MC0;
	}
	else if ((TC4->COUNT8.INTFLAG.reg & TC_INTFLAG_OVF) && TC4->COUNT8.CC[0].reg != 255)
	{
		PORTA.OUT.reg &= ~(1 << 4);
		TC4->COUNT8.INTFLAG.reg |= TC_INTFLAG_OVF;
	}
	//testByColor(GREEN,0);

}

void TC5_Handler()
{
	//testByColor(BLUE,1);

	if ((TC5->COUNT8.INTFLAG.reg & TC_INTFLAG_MC0) && TC5->COUNT8.CC[0].reg != 0)
	{
		PORTA.OUT.reg |= (1 << 5);
		TC5->COUNT8.INTFLAG.reg |= TC_INTFLAG_MC0;
	}
	else if ((TC5->COUNT8.INTFLAG.reg & TC_INTFLAG_OVF) && TC5->COUNT8.CC[0].reg != 255)
	{
		PORTA.OUT.reg &= ~(1 << 5);
		TC5->COUNT8.INTFLAG.reg |= TC_INTFLAG_OVF;
	}
	//testByColor(BLUE,0);

}

switch(whatKind)
	{
		case FLASH:
			intensity[whichColor] = inst.bright;
			beatsRemaining[whichColor] = inst.dur;
			//isOn[whichColor] = 0; //isOn[whichColor] ? 1 : 0;
			diffs[whichColor] = (stepsPerBeat / inst.rate) >> 1;
			//nextAction[whichColor] = diffs[whichColor];	
		
			action = &flash;
			break;
		case FADE:
			break;
		case RAMPUP:
			break;
		case RAMPDN:
			break;
		default:
			while(1) // Error state
			{
				PORTA.OUTTGL.reg = 1 << 2 | 1 << 4 | 1 << 5;
				delay_ms(500);
			}
			break;
	}
	
	//if (firstTime < 3)
	//{
		PORTA.OUT.reg &= ~(1 << 4 | 1 << 5);
		delay_ms(250);
		PORTA.OUT.reg |= 1 << 4 | 1 << 5;
		delay_ms(250);
		
	
		//firstTime++;
		switch(whichColor)
			{
			case RED:
				TCC0->CC[0].reg = TCC0->COUNT.reg + diffs[RED];
				TC3->COUNT8.CC[0].reg = intensity[RED];
				break;
			case GREEN:
				TCC0->CC[1].reg = TCC0->COUNT.reg + diffs[GREEN];
				TC4->COUNT8.CC[0].reg = intensity[GREEN];
				break;
			case BLUE:
				TCC0->CC[2].reg = TCC0->COUNT.reg + diffs[BLUE];
				TC5->COUNT8.CC[0].reg = intensity[BLUE];
				break;
			default:
				while(1) // Error state
				{
					PORTA.OUTTGL.reg = 1 << 2 | 1 << 4 | 1 << 5;
					delay_ms(500);
				}
				break;
			}
	/*}
	else
	{
		switch(whichColor)
		{
			case RED:
				TC3->COUNT8.CC[0].reg = intensity[RED];
			break;
			case GREEN:
				TC4->COUNT8.CC[0].reg = intensity[GREEN];
			break;
			case BLUE:
				TC5->COUNT8.CC[0].reg = intensity[BLUE];
			break;
			default:
				while(1) // Error state
				{
					PORTA.OUTTGL.reg = 1 << 2 | 1 << 4 | 1 << 5;
					delay_ms(500);
				}
			break;
		}
	}*/
}