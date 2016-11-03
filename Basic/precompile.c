#include "stdio.h"

#define PI 3.1415
#define S(R) PI * R * R;
#define L(R) 2 * PI * R;

// 此处宏定义的参数只是简单的替换，逗号后不要加空格
#define MULTI(X,Y) X * Y 

int main()
{
	float r;
	float l;
	float s;

	printf("Please input radius:");
	scanf("%f", &r);

	l = L(r);
	s = S(r);

	printf("L=%f,S=%f",l ,s);

	return 0;
}

#undef PI