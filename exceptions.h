//exceptions.h
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept> //std::runtime_error
#include <ios>		//std::ios_base::failure

class SdlExcept : public std::runtime_error {
public:
  SdlExcept( const std::string & s ) : std::runtime_error( s ) { }
};

class FileExcept : public std::ios_base::failure {
public:
  FileExcept( const std::string & s ) : std::ios_base::failure( s ) { }
};
#endif
