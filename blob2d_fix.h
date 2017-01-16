//blob2d_fix.h
// Class template representing motionless circular object placed in 2D plane.
// Size of the object is equal to diameter (2 x riadius).
//
// It is intended to be instantiated by a numeric type (int, float, etc. )

#ifndef BLOB2D_FIX_H
#define BLOB2D_FIX_H

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

using std::string;
using std::ostream;
using std::istream;
using std::sqrt;

template <typename T>
class Blob2d_fix {

	private:

	T x_;
	T y_;
	T radius_;
	bool active_{ false };

	protected:
	void load_blob_els( istream & );

	public:

	Blob2d_fix(
		T position_x,
		T position_y,
		T size,
		bool active
	);
	Blob2d_fix( std::istream & is ) { load_blob_els( is ); }
	virtual ~Blob2d_fix() {}

	T distance( const Blob2d_fix<T> &) const;
	virtual std::string toString() const;
	virtual char type() const { return 'f'; } // identify as fixed blob

	void xAdd( T delta_x ) { x_ += delta_x; }
	void yAdd( T delta_y ) { y_ += delta_y; }

// set Methods
	void x(T new_position_x) { x_ = new_position_x; }
	void y(T new_position_y) { y_ = new_position_y; }
	void place(T new_x, T new_y) { x_ = new_x; y_ = new_y; }
	void active(bool active) { active_ = active; }

	void size(T new_size) { radius_ = new_size/2.0; } //round int???
	void radius(T new_radius ) { radius_ = new_radius; }

// get Methods
	T x() const { return x_; }
	T y() const { return y_; }

	T size() const { return radius_*2; }
	T radius() const { return radius_; }
	bool active() const { return active_; }
//friends
	template <typename U>
	friend ostream & operator<<( ostream &, const Blob2d_fix<U> & );
};

// constructor
template <typename T>
Blob2d_fix<T>::Blob2d_fix( T position_x, T position_y, T size, bool active ) :
	x_(position_x),
	y_(position_y),
	radius_(size/2.0), // round int???
	active_(active)
{}

// Function calculates distance between 2 objects' centers and then substracts
// their radiuses. If distance is less than 0 objects overlaps.
// Basic collision detection
template <typename T>
T Blob2d_fix<T>::distance( const Blob2d_fix<T> & b) const {
	return sqrt( (b.x_ - x_)*(b.x_ - x_) + (b.y_ - y_)*(b.y_ - y_ ) )
		- radius_ - b.radius_;
}

template <typename T>
std::string Blob2d_fix<T>::toString() const {
	std::stringstream sstr;
	sstr << x_ << ' ' << y_ << ' ' << radius_ << ' ' << active_;
	return sstr.str();
}

// Operator outputs object's state (all variables) separated by spaces
template <typename T>
ostream & operator<<( ostream & os, const Blob2d_fix<T> & b ) {

	os << b.toString() << std::endl;
	return os;
}

template <typename T>
void Blob2d_fix<T>::load_blob_els( istream & is ) {
	if( ! ( is >> x_ >> y_ >> radius_ >> active_ ) )
		throw "Loading Blob2d_fix<T> elements failed";
}

// Extraction operator gets numerics from the input stream and assings its
// value to object's varibles. It is intended to be used with  strings
// created by << operator. Numbers should be separated only with white spaces.
template <typename T>
istream & operator>>( istream & is, Blob2d_fix<T> & b ) {

	b.load_blob_els( is );
	return is;
}

#endif
