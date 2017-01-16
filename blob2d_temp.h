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
	int ttl_{120}; //frame to live - TODO add external multiplicator to manage time
	void load_blob_els( istream & );
	void fromStream( istream & );

	public:

	Blob2d_temp(
		T position_x,
		T position_y,
		T size,
		int ttl,
		T velocity_x,
		T velocity_y
	);
	Blob2d_temp( std::istream & is );
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
	template <typename U>
	friend istream & operator>>( istream &, Blob2d_temp<U> & );

};

template <typename T>
Blob2d_temp<T>::Blob2d_temp(
		T position_x, T position_y,
		T size,
		int ttl,
		T velocity_x, T velocity_y) :
	Blob2d<T>( position_x, position_y, size, velocity_x, velocity_y ),
	ttl_(ttl)
{}

template <typename T>
Blob2d_temp<T>::Blob2d_temp( std::istream & is ) : Blob2d<T>( is ) {
	load_blob_els( is );
}

template <typename T>
void Blob2d_temp<T>::load_blob_els( istream & is ) {
	if( ! (is >> ttl_ ) )
		throw "Loading Blob2d_temp<T> elements failed";
}

template <typename T>
Blob2d_temp<T>::Blob2d_temp( const Blob2d<T> & b) :
		Blob2d<T>( b )
{}

template <typename T>
std::string Blob2d_temp<T>::toString() const {
	std::stringstream sstr;
	sstr << Blob2d<T>::toString() << ' ' << ttl_;
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
