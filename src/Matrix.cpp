#include "stdafx.h"
#include<vector>
#include<map>
#include<memory.h>
#include<assert.h>
#include"Poly.h"
#include"Matrix.h"
int main()
{
	Poly p1({'c', 'b', 'z'});
	p1.SetCoeff({ {'c',1},{'b',2} }, 1.5);
	p1.SetCoeff({ {'z',-2},{'c',-2} }, 0.5);

	Poly p2({ 'x', 'y', 'z' });
	p2.SetCoeff({ { 'x',1 },{ 'y',2 } }, -2);
	p2.SetCoeff({ { 'z',2 } }, 2);

	Poly p3 = p1 * p2;
	Poly p4 =  - p2 - p1;
	Matrix<double> mat(2,3), mat2(3,3);
	mat.Set_Element(0, 1, 1.2);
	mat2.Set_Element(1, 2, 1);
	mat2.Set_Element(0, 1, -2.2);
	auto ma3 = mat * mat2;

	Matrix<Poly> mp1(1, 2), mp2(2,1);
	mp1.Set_Element(0, 0, p1);
	mp2.Set_Element(0, 0, p2);
	auto mp3 = (-mp2)*mp1 ;

    return 0;
}


