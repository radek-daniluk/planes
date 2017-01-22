//blob2d_shoot.h
// Class template representing movable circular object in 2D plane with shooting
// ability.
// Size of the object is equal to diameter (2 x riadius).
//
// It is intended to be instantiated by a numeric type (int, float, etc. )

#ifndef BLOB2D_SHOOT_H
#define BLOB2D_SHOOT_H

#include <iostream>
#include <sstream>
#include "blob2d.h"

using std::ostream;
using std::istream;

template <typename T>
class Blob2d_shoot : public Blob2d<T> {

	private:

	const T reload_time_{1};
	T to_reload_{0};

	void load_blob_els( istream & );
	void fromStream( istream & );

	void progress_reload( T interval ) {
		if( ( to_reload_ -= interval ) < 0)
			//if( to_reload > reload_time ) unsigned???
			to_reload_ = 0;
	}

	public:

	Blob2d_shoot(
		T position_x, T position_y,
		T size,
		T reload_time,
		T velocity_x, T velocity_y,
		T max_x, T min_x, T max_y, T min_y,
		bool active
	);
	Blob2d_shoot( std::istream & is );
	virtual ~Blob2d_shoot() {}

	virtual std::string toString() const;
	virtual char type() const { return 's'; } // identify as shooting blob

	bool reloaded() const { return !to_reload_; }

	void fire() { to_reload_ = reload_time_; }

	void step( T interval ) {
		Blob2d<T>::step( interval );
		progress_reload( interval );
	}

// friends
	template <typename U>
	friend ostream & operator<<( ostream &, const Blob2d<U> & );
	template <typename U>
	friend istream & operator>>( istream &, Blob2d<U> & );

};

template <typename T>
Blob2d_shoot<T>::Blob2d_shoot(
		T position_x, T position_y,
		T size,
		T reload_time,
		T velocity_x, T velocity_y,
		T max_x, T min_x, T max_y, T min_y,
		bool active ) :
	Blob2d<T>( position_x, position_y, size, velocity_x, velocity_y,
		max_x, min_x, max_y, min_y, active ),
	reload_time_(reload_time)
{}

template <typename T>
Blob2d_shoot<T>::Blob2d_shoot( std::istream & is ) : Blob2d<T>( is ) {
	load_blob_els( is );
}

template <typename T>
std::string Blob2d_shoot<T>::toString() const {
	std::stringstream sstr;
	sstr << Blob2d<T>::toString() << ' ' << reload_time_ << ' ' << to_reload_;
	return sstr.str();
}

template <typename T>
void Blob2d_shoot<T>::fromStream( istream & is ) {
	Blob2d<T>::fromStream( is );
	load_blob_els( is );
}

// Operator outputs object's state (all variables) separated by spaces
template <typename T>
ostream & operator<<( ostream & os, const Blob2d_shoot<T> & b ) {

	os << b.toString() << std::endl;
	return os;
}

template <typename T>
void Blob2d_shoot<T>::load_blob_els( istream & is ) {

	if( ! (is >> reload_time_ >> to_reload_ ) )
	throw "Loading Blob2d_shoot<T> elements failed";
}

// Extraction operator gets all elements from the input stream and assings its
// value to object's varibles. It is intended to be used with strings
// created by << operator (e.g. load<->save). Numbers should be separated
// only with white spaces.
template <typename T>
istream & operator>>( istream & is, Blob2d_shoot<T> & b ) {

	b.fromStream( is );
	return is;
}

#endif
