void start()
{
	while (true)
	{
		GetHitKeyStateAll(keys);
		for (auto i = 0; i < 256; i++) { oldkeys[i] = keys[i]; }
		ClearDrawScreen(); //�N���A

		if (keys[KEY_INPUT_A])
		{
			break;
		}

		ScreenFlip();
		WaitTimer(20);
		if (ProcessMessage() == -1) { break; }
	}
}