#pragma once

constexpr int factr_cnstexpr(int t)
{
	return t > 0 ? t * factr_cnstexpr(t - 1) : 1;
}

