int PlayerItemCollision(int playrex,int playery,int playerw,int playerh,int itemx,int itemy,int itemw,int itemh)
{
	if (((itemx > playrex && itemx < playrex + playerw) ||
		(playrex > itemx && playrex < itemx + itemw)) &&
		((itemy > playery && itemy < playery + playerh) ||
			(playery > itemy && playery < itemy + itemh)))
	{
		return 0;
	}
}