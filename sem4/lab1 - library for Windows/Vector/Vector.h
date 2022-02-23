#pragma once
#include <Number.h>
#include <string>
#include <windows.h>
#include <math.h>

namespace Math {
	class Vector {
	private:
		Number x, y;
	public:
		Vector(Number x, Number y);
		Vector add(Vector other);
		
		std::string toString();
        double getPolarAngle();
        double getPolarRadius();

		static Vector ZERO_VECTOR;
		static Vector ONE_VECTOR;
	};
}

#ifdef __cplusplus
extern "C"
#endif

__declspec(dllexport) std::string __cdecl doStuff();

