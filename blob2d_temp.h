//blob2d_temp.h
// Class template representing movable, temporary circular object in 2D plane.
// Size of the object is equal to diameter (2 x riadius).
//
// It is intended to be instantiated by a number type (int, float, etc. )

#ifndef BLOB2D_TEMP_H
#define BLOB2D_TEMP_H

#include <iostream>
#include <sstream>
#include "blob2d.h"

using std::ostream;
using std::istream;

template <typename T>
class Blob2d_temp : public Blob2d<T> {

	private:
	int ttl_;

	protected:
	virtual std::string string_for_operator() const;

	public:

	Blob2d_temp( T position_x, T position_y, T size,
		T velocity_x = 0, T velocity_y = 0, int ttl = 120 );
	Blob2d_temp( std::istream & is ) { is >> *this; }
	Blob2d_temp() { Blob2d<T>(); }
	Blob2d_temp( const Blob2d<T> & );
	virtual ~Blob2d_temp() {}

	virtual std::string toString() const;
	virtual char type() const { return 't'; } // identify as movable temp blob

	void operator--() { --ttl_; }

// set methods

	void ttl( int new_ttl ) { ttl_ = new_ttl; }

// get methods

	int ttl() { return ttl_; }
// friends
	template <typename U>
	friend ostream & operator<<( ostream &, const Blob2d_temp<U> & );

};

template <typename T>
Blob2d_temp<T>::Blob2d_temp( T position_x, T position_y, T size,
		T velocity_x, T velocity_y, int ttl) :
		Blob2d<T>( position_x, position_y, size, velocity_x, velocity_y, ttl ) {

		ttl_ = ttl;
}

template <typename T>
Blob2d_temp<T>::Blob2d_temp( const Blob2d<T> & b) :
		Blob2d<T>( b ) {
	ttl_ = 120;
}

template <typename T>
std::string Blob2d_temp<T>::toString() const {
	std::ostringstream strs;
	strs << "Blob2d::place[" << Blob2d_fix<T>::x() << "x" <<
		Blob2d_fix<T>::y() << "]radius[" << Blob2d_fix<T>::radius() << "]speed["
		<< Blob2d<T>::speedX() << "x" << Blob2d<T>::speedY() << "]active["
		<< Blob2d_fix<T>::active() << "]ttl[" << ttl_ << "]" << std::endl;
	return strs.str();
}

template <typename T>
std::string Blob2d_temp<T>::string_for_operator() const {
	std::stringstream sstr;
	sstr << Blob2d<T>::string_for_operator() << ' ' << ttl_;
	return sstr.str();
}

// Operator outputs object's state (7 variables) separated by spaces
template <typename T>
ostream & operator<<( ostream & os, const Blob2d_temp<T> & b ) {

	os << b.string_for_operator() << std::endl;
	return os;
}

// Extraction operator gets 7 <T>s from the input stream and assings its
// value to object's varibles. It is intended to be used with  strings
// created by << operator. Numbers should be separated only with white spaces.
// On error it throws const char* "Operator >> failed".
template <typename T>
istream & operator>>( istream & is, Blob2d_temp<T> & b ) {

	T x,y,r, sx, sy;
	bool a;
	int t;

	if( is >> x >> y >> r >> a >> sx >> sy >> t) {
		b.place(x,y);
		b.radius(r);
		b.active(a);
		b.speed(sx, sy);
		b.ttl(t);
		return is;
	}

	throw "Operator>>( istream &, Blob2d_temp<T> &) failed";
	return is;
}

#endif
