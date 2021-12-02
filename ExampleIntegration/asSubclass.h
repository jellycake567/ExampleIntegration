#pragma once
#include "AS.h"

class asSubclass : public AS
{
public:
	asSubclass();
	void ExposeFunctions() override;
};