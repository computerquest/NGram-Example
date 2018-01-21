#include "stdafx.h"
#include "NGram.h"

NGram::NGram(string source)
{
	phrase = source;
}

void NGram::add(string to)
{
	ng[to]++;
}
