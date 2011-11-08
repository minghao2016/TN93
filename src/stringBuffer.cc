#include "stringBuffer.h"
#include <stdlib.h>
#include <strings.h>

long StringBuffer::sbDefaultLength = 16,
	 StringBuffer::sbDefaultBoost  = 16,
	 Vector::vDefaultLength		   = 16,
	 Vector::vDefaultBoost		   = 16;

/*---------------------------------------------------------------------------------------------------- */

StringBuffer::StringBuffer (void)
{
	sLength  = 0;
	saLength = StringBuffer::sbDefaultLength;
	sData = (char*)malloc (sizeof(char)*(saLength+1));
	sData[0] = 0;
}

/*---------------------------------------------------------------------------------------------------- */

StringBuffer::~StringBuffer (void)
{
	free (sData);
}

/*---------------------------------------------------------------------------------------------------- */

void StringBuffer::appendChar (const char c)
{
	long addThis; 
	if (saLength == sLength)
	{
		addThis = saLength / 8;
		if (StringBuffer::sbDefaultBoost > addThis)
			addThis = StringBuffer::sbDefaultBoost;
		saLength += addThis;
		sData = (char*)realloc (sData,sizeof(char)*(saLength+1));
	}
	sData[sLength] = c;
	sData[++sLength] = 0;
}

/*---------------------------------------------------------------------------------------------------- */

void StringBuffer::appendBuffer (const char *buffer)
{
	long addThis,
		 pl = strlen(buffer);
	
	if (pl>0)
	{
		if (saLength < sLength + pl)
		{
			addThis = saLength / 8;
			
			if (StringBuffer::sbDefaultBoost > addThis)
				addThis = StringBuffer::sbDefaultBoost;
			if (addThis < pl)
				addThis = pl;
				
			saLength += addThis;
			sData = (char*)realloc (sData,sizeof(char)*(saLength+1));
		}
		for (addThis = 0; addThis < pl; addThis++)
			sData[sLength++] = buffer[addThis];

		sData[sLength] = 0;
	}
}

/*---------------------------------------------------------------------------------------------------- */

void StringBuffer::resetString (void)
{
	sLength        = 0;
	sData[sLength] = 0;
}

/*---------------------------------------------------------------------------------------------------- */

Vector::Vector (void)
{
	vLength  = 0;
	vaLength = Vector::vDefaultLength;
	vData = (long*)malloc (sizeof(long)*vaLength);
}

/*---------------------------------------------------------------------------------------------------- */

Vector::~Vector (void)
{
	free (vData);
}

/*---------------------------------------------------------------------------------------------------- */

void Vector::appendValue (const long l)
{
	long addThis; 
	if (vLength == vaLength)
	{
		addThis = vaLength / 8;
		if (Vector::vDefaultBoost > addThis)
			addThis = Vector::vDefaultBoost;
		vaLength += addThis;
		vData = (long*)realloc (vData,sizeof(long)*vaLength);
	}
	vData[vLength++] = l;
}

/*---------------------------------------------------------------------------------------------------- */

void Vector::storeValue (const long v, const long l)
{
	long addThis; 
	if (l >= vaLength)
	{
		addThis = l-vaLength+1;
		if (Vector::vDefaultBoost > addThis)
			addThis = Vector::vDefaultBoost;
		vaLength += addThis;
		vData = (long*)realloc (vData,sizeof(long)*vaLength);
		vLength = l+1;
	}
	vData[l] = v;
}


/*---------------------------------------------------------------------------------------------------- */

void Vector::storeVector (const Vector& v, const long l)
{
	if (l < vLength && vData[l])
		delete (Vector*)(vData[l]);
		
	storeValue ((long)&v, l);
}

/*---------------------------------------------------------------------------------------------------- */

int long_comp(const void * v1, const void *v2)
{
	long l1 = *(long*)v1,
		 l2 = *(long*)v2;
	if (l1<l2)
		return -1;
	if (l1>l2)
		return 1;
	return 0;
}

/*---------------------------------------------------------------------------------------------------- */

void Vector::sort (void)
{
	qsort((void*)vData, vLength, sizeof (long), long_comp);
}

/*---------------------------------------------------------------------------------------------------- */

void Vector::resetVector (void)
{
	vLength        = 0;
}
