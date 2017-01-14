//blob2d.h
// Class template representing movable circular object in 2D plane.
// Size of the object is equal to diameter (2 x riadius).
//
// It is intended to be instantiated by a number type (int, float, etc. )

#ifndef BLOB2D_H
#define BLOB2D_H

#include <iostream>
#include <sstream>
#include "blob2d_fix.h"

using std::ostream;
using std::istream;

template <typename T>
class Blob2d : public Blob2d_fix<T> {

	private:

	T velocity_x_;
	T velocity_y_;

	protected:
	virtual std::string string_for_operator() const;

	public:

	Blob2d( T position_x, T position_y, T size,
		T velocity_x = 0, T velocity_y = 0);
	Blob2d( std::istream & is ) { is >> *this; }
	Blob2d () { Blob2d_fix<T>(); }
	virtual ~Blob2d() {}

	virtual std::string toString() const;
	virtual char type() const { return 'm'; } // identify as movable blob

	void operator+( T speed_multiplicator ) {
		this->xAdd( velocity_x_*speed_multiplicator );
		this->yAdd( velocity_y_*speed_multiplicator );
	}
	void operator++() { xAdd(velocity_x_); yAdd(velocity_y_); }

// set methods

	void speed( T new_velocity_x, T new_velocity_y ) {
		velocity_x_ = new_velocity_x;
		velocity_y_ = new_velocity_y;
	}
	void speedX ( T new_velocity_x ) { velocity_x_ = new_velocity_x; }
	void speedY ( T new_velocity_y ) { velocity_y_ = new_velocity_y; }

// get methods

	T speedX ( void ) const { return velocity_x_; }
	T speedY ( void ) const { return velocity_y_; }

	double speed ( void ) const {
		return sqrt( velocity_x_ * velocity_x_ + velocity_y_ * velocity_y_ );
	}
// friends
	template <typename U>
	friend ostream & operator<<( ostream &, const Blob2d<U> & );

};

template <typename T>
Blob2d<T>::Blob2d( T position_x, T position_y, T size,
		T velocity_x, T velocity_y) :
		Blob2d_fix<T>( position_x, position_y, size ) {

	velocity_x_ = velocity_x;
	velocity_y_ = velocity_y;
}

template <typename T>
std::string Blob2d<T>::toString() const {
	std::ostringstream strs;
	strs << "Blob2d::place[" << Blob2d_fix<T>::x() << "x" <<
		Blob2d_fix<T>::y() << "]radius[" << Blob2d_fix<T>::radius() << "]speed["
		<< velocity_x_ << "x" << velocity_y_ << "]active["
		<< Blob2d_fix<T>::active() << "]" << std::endl;
	return strs.str();
}

template <typename T>
std::string Blob2d<T>::string_for_operator() const {
	std::stringstream sstr;
	sstr << Blob2d_fix<T>::string_for_operator() << ' ' << velocity_x_ << ' '
		<< velocity_y_;
	return sstr.str();
}

// Operator outputs object's state (6 variables) separated by spaces
template <typename T>
ostream & operator<<( ostream & os, const Blob2d<T> & b ) {

	os << b.string_for_operator() << std::endl;
	return os;
}


// Extraction operator gets 6 <T>s from the input stream and assings its
// value to object's varibles. It is intended to be used with  strings
// created by << operator. Numbers should be separated only with white spaces.
// On error it throws const char* "Operator >> failed".
template <typename T>
istream & operator>>( istream & is, Blob2d<T> & b ) {

	T x,y,r, sx, sy;
	bool a;

	if( is >> x >> y >> r >> a >> sx >> sy ) {
		b.place(x,y);
		b.radius(r);
		b.active(a);
		b.speed(sx, sy);
		return is;
	}

	throw "Operator>>( istream &, Blob2d<T> &) failed";
	return is;
}

#endif
