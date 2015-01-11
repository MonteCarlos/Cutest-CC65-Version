void CuStringAppendULong(CuString *str, unsigned long int num){
	char numStr[20];
	sprintf(numStr, "%lu", num);
	CuStringAppend(str, numStr);
}

