//blob2d_temp.h
// Class template representing movable, temporary circular object in 2D plane.
// Size of the object is equal to diameter (2 x riadius).
//
// It is intended to be instantiated by a numeric type (int, float, etc. )

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
	double ttl_start{3};
	double ttl_;
	void load_blob_els( istream & );
	void fromStream( istream & );

	public:

	Blob2d_temp(
		T position_x,
		T position_y,
		T size,
		double ttl,
		T velocity_x,
		T velocity_y
	);
	Blob2d_temp( std::istream & is );
	Blob2d_temp( const Blob2d<T> &, double );
	Blob2d_temp( const Blob2d_temp<T> &, double );
	virtual ~Blob2d_temp() {}

	virtual std::string toString() const;
	virtual char type() const { return 't'; } // identify as movable temp blob

	void step( T interval ) {
		Blob2d<T>::step( interval );
		ttl_ -= interval;
	}

// set methods

	void ttl( double new_ttl ) { ttl_ = new_ttl; }

// get methods

	double ttlStart() const { return ttl_start; }
	double ttl() const { return ttl_; }
// friends
	template <typename U>
	friend ostream & operator<<( ostream &, const Blob2d_temp<U> & );
	template <typename U>
	friend istream & operator>>( istream &, Blob2d_temp<U> & );

};

template <typename T>
Blob2d_temp<T>::Blob2d_temp(
		T position_x, T position_y,
		T size,
		double ttl,
		T velocity_x, T velocity_y) :
	Blob2d<T>( position_x, position_y, size, velocity_x, velocity_y ),
	ttl_start(ttl),
	ttl_(ttl)
{}

template <typename T>
Blob2d_temp<T>::Blob2d_temp( std::istream & is ) : Blob2d<T>( is ) {
	load_blob_els( is );
}

template <typename T>
void Blob2d_temp<T>::load_blob_els( istream & is ) {
	if( ! (is >> ttl_start >> ttl_ ) )
		throw "Loading Blob2d_temp<T> elements failed";
}

template <typename T>
Blob2d_temp<T>::Blob2d_temp( const Blob2d<T> & b, double ttl) :
		Blob2d<T>( b ),
		ttl_start( ttl ),
		ttl_( ttl )
{}

template <typename T>
Blob2d_temp<T>::Blob2d_temp( const Blob2d_temp<T> & b, double ttl) :
		Blob2d<T>( b ),
		ttl_start( ttl ),
		ttl_( ttl )
{}

template <typename T>
std::string Blob2d_temp<T>::toString() const {
	std::stringstream sstr;
	sstr << Blob2d<T>::toString() << ' ' << ttl_start << ' ' << ttl_;
	return sstr.str();
}

template <typename T>
void Blob2d_temp<T>::fromStream( istream & is ) {

	Blob2d<T>::fromStream( is );
	load_blob_els( is );
}

// Operator outputs object's state (all variables) separated by spaces
template <typename T>
ostream & operator<<( ostream & os, const Blob2d_temp<T> & b ) {

	os << b.toString() << std::endl;
	return os;
}

// Extraction operator gets numerics from the input stream and assings its
// value to object's varibles. It is intended to be used with  strings
// created by << operator. Numbers should be separated only with white spaces.
template <typename T>
istream & operator>>( istream & is, Blob2d_temp<T> & b ) {

	b.fromStream( is );
	return is;
}

#endif
