#ifndef VEC_H_
#define VEC_H_

#include <iostream>

#define SIZE 100

using namespace std;

class Vec{
public:
	float x, y;

	Vec(){
		x = y = 0;
	}

	Vec(const Vec& vec){
		x = vec.x;
		y = vec.y;
	}

	Vec(float x, float y){
		this->x = x;
		this->y = y;
	}

	Vec operator-(){
		return Vec(-x, -y);
	}

	Vec operator-(Vec v){
		return Vec(x - v.x, y - v.y);
	}

	Vec operator+(Vec v){
		return Vec(x + v.x, y + v.y);
	}

	float long2(){
		return x*x + y*y;
	}

	void print(){
		cout << " (" << x << ";" << y << ") ";
	}
};

#endif