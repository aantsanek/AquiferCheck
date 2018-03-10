#include "EntryPoint.h"

EntryPoint::EntryPoint()
{
}


EntryPoint::~EntryPoint()
{
}

extern "C" __declspec(dllexport) int doNothing()
{
	return EntryPoint::doNothing();
}