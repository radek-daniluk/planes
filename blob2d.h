//blob2d.h
// Class template representing movable circular object in 2D plane.
// Size of the object is equal to diameter (2 x riadius).
//
// It is intended to be instantiated by a numeric type (int, float, etc. )

#ifndef BLOB2D_H
#define BLOB2D_H

#include <iostream>
#include <sstream>
#include <limits>
#include "blob2d_fix.h"

using std::ostream;
using std::istream;

template <typename T>
class Blob2d : public Blob2d_fix<T> {

	private:

	T velocity_x_{ 0 };
	T velocity_y_{ 0 };
	T max_x_;
	T min_x_;
	T max_y_;
	T min_y_;
	void load_blob_els( istream & );
	void fromStream( istream & );

	public:

//constructors, destructor
	Blob2d(
		T position_x,
		T position_y,
		T size,
		T velocity_x = 0,
		T velocity_y = 0,
		T max_x = std::numeric_limits<T>::max(), // By default
		T min_x = std::numeric_limits<T>::min(), // no max, min speed limits
		T max_y = std::numeric_limits<T>::max(), // (numeric type is a limit)
		T min_y = std::numeric_limits<T>::min(),
		bool active = false
	);
	Blob2d( const Blob2d_fix<T> & bf ) : Blob2d_fix<T>(bf) {}
	Blob2d( std::istream & is );
	virtual ~Blob2d() {}

	virtual std::string toString() const;
	virtual char type() const { return 'm'; } // identify as movable blob

//methods
	// changeDir( angle )
	/*void next( T speed_multiplicator ) {
		this->xAdd( velocity_x_*speed_multiplicator );
		this->yAdd( velocity_y_*speed_multiplicator );
	}*/

	void accel( T delta_x, T delta_y );
	void stopX() { velocity_x_ = 0; }
	void stopY() { velocity_y_ = 0; }
	void stop() { velocity_x_ = velocity_y_ = 0; }

	void step( T speed_multiplicator );
	void operator++() { this->xAdd(velocity_x_); this->yAdd(velocity_y_); }

// set methods
	void speed( T new_velocity_x, T new_velocity_y ) {
		velocity_x_ = new_velocity_x;
		velocity_y_ = new_velocity_y;
	}
	void speedX ( T new_velocity_x ) { velocity_x_ = new_velocity_x; }
	void speedY ( T new_velocity_y ) { velocity_y_ = new_velocity_y; }

	void maxMin( T max_x, T min_x, T max_y, T min_y ) {
		max_x_ = max_x; min_x_ = min_x;  max_y_ = max_y; min_y_ = min_y;
	}

// get methods
	T speedX () const { return velocity_x_; }
	T speedY () const { return velocity_y_; }
	T maxX () const { return max_x_; };
	T minX () const { return min_x_; };
	T maxY () const { return max_y_; };
	T minY () const { return min_y_; };

	double speed ( void ) const {
		return sqrt( velocity_x_ * velocity_x_ + velocity_y_ * velocity_y_ );
	}
// friends
	template <typename U>
	friend ostream & operator<<( ostream &, const Blob2d<U> & );
	template <typename U>
	friend istream & operator>>( istream &, Blob2d<U> & );

};

// take a movement step according to current speed and multiplicator
template <typename T>
void Blob2d<T>::step( T speed_multiplicator ) {
	this->xAdd( velocity_x_*speed_multiplicator );
	this->yAdd( velocity_y_*speed_multiplicator );
}


template <typename T>
Blob2d<T>::Blob2d(
		T position_x, T position_y,
		T size,
		T velocity_x, T velocity_y,
		T max_x, T min_x,
		T max_y, T min_y,
		bool active ) :
	Blob2d_fix<T>( position_x, position_y, size, active ),
	velocity_x_(velocity_x),
	velocity_y_(velocity_y),
	max_x_(max_x),
	min_x_(min_x),
	max_y_(max_y),
	min_y_(min_y)
{}

template <typename T>
Blob2d<T>::Blob2d( std::istream & is ) : Blob2d_fix<T>( is ) {
	load_blob_els( is );
}

// method changes x and y elements of Blob's velocity
// It checks max and min velocity limits
template <typename T>
void Blob2d<T>::accel( T delta_x, T delta_y ) {

	T tempv = velocity_x_ + delta_x;
	if( tempv > max_x_ )
		velocity_x_ = max_x_;
	else if( tempv < min_x_ )
		velocity_x_ = min_x_;
	else
		velocity_x_ = tempv;

	tempv = velocity_y_ + delta_y;
	if( tempv > max_y_ )
		velocity_y_ = max_y_;
	else if( tempv < min_y_ )
		velocity_y_ = min_y_;
	else
		velocity_y_ = tempv;
}

template <typename T>
std::string Blob2d<T>::toString() const {

	std::stringstream sstr;
	sstr << Blob2d_fix<T>::toString() << ' '
		<< velocity_x_ << ' ' << velocity_y_ << ' '
		<< max_x_ << ' ' << min_x_ << ' '
		<< max_y_ << ' ' << min_y_;
	return sstr.str();
}

template <typename T>
void Blob2d<T>::fromStream( istream & is ) {

	Blob2d_fix<T>::load_blob_els( is );
	load_blob_els( is );

}

// Operator outputs object's state (all variables) separated by spaces
template <typename T>
ostream & operator<<( ostream & os, const Blob2d<T> & b ) {

	os << b.toString() << std::endl;
	return os;
}

template <typename T>
void Blob2d<T>::load_blob_els( istream & is ) {

	if( ! (is >> velocity_x_ >> velocity_y_
			>> max_x_ >> min_x_ >> max_y_ >> min_y_) )
	throw "Loading Blob2d<T> elements failed";
}

// Extraction operator gets all elements from the input stream and assings its
// value to object's varibles. It is intended to be used with strings
// created by << operator (e.g. load<->save). Numbers should be separated
// only with white spaces.
// On error it throws const char* "Operator>>( istream &, Blob2d<T> &) failed".
template <typename T>
istream & operator>>( istream & is, Blob2d<T> & b ) {

	b.fromStream( is );

	return is;
}

#endif
