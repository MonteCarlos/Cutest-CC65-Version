void CuStringInit(CuString* str)
{
	str->length = 0;
	str->size = STRING_MAX;
	str->buffer = (char*) malloc(sizeof(char) * str->size);
	assert(str->buffer != NULL);
	str->buffer[0] = '\0';
}
