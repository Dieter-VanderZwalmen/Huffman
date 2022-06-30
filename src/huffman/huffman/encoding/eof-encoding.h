
#ifndef EOF_ENCODING_H
#define EOF_ENCODING_H

#include <iostream>
#include "encoding.h"

namespace encoding
{

	/*
	* We vervangen het volgende
	Encoding<2, 3> eof_encoding2();
	Encoding<3, 4> eof_encoding3();
	Encoding<4, 5> eof_encoding4();
	Encoding<5, 6> eof_encoding5();
	
	met deze template class zodat we voor elke mogelijkheid iets klaar hebben
	
	*/


	std::shared_ptr<EncodingImplementation> create_eof_implementation(const u64 domain_size);


	template<u64 N>
	Encoding<N, N + 1> eof_encoding()
	{
		return Encoding<N, N + 1>(create_eof_implementation(N));
	}

}


#endif // !EOF_ENCODING_H
