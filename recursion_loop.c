int sumseries(ival)
    int ival;
{
  	int sum;
  	if (ival<=0) return 0;
  	if (ival>100) return -1;
  	sum =ival+ sumseries(ival-1);
    return sum;
}
