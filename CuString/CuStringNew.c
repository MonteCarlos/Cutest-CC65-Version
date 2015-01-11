CuString* CuStringNew(void)
{
	CuString* str = (CuString*) malloc(sizeof(CuString));
	assert(NULL!=str);
	CuStringInit(str);

	return str;
}
