#pragma once

namespace Spatio
{
	enum mino_code {
		I_H = 0,
		I_V,
		T_U,
		T_D,
		T_L,
		T_R,
		O,
		S_H,
		S_V,
		Z_H,
		Z_V,
		L_U,
		L_D,
		L_L,
		L_R,
		J_U,
		J_D,
		J_L,
		J_R = 18
	};

	enum state_code {
		NOT_OVER = 0,
		GOING_1ST_WIN,
		GOING_2ND_WIN
	};
}