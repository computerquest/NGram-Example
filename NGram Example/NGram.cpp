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

void NGram::add(string to, int value)
{
	ng[to] += value;
}