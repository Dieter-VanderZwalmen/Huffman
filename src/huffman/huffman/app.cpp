#ifndef TEST_BUILD

/*
*   This file is only active in non-test builds (i.e., builds where TEST_BUILD is not defined).
*/

#include <iostream>
#include "util.h"
#include <string>
#include "io/files.h"
#include "encoding/eof-encoding.h"
#include "encoding/huffman/huffman-encoding.h"
#include "encoding/encoding-combiner.h"
#include "encoding/bit-grouper.h"
/*
* This is the main entry point of your application.
* Note that it will only work in non-test builds.
*/

int main(unsigned argumenten,char* args[])
{

#ifdef NDEBUG
    std::cout << "You are running the release build" << std::endl;
#else
    std::cout << "You are running the debug build";
    std::cout << "swakke" << std::endl;

	std::cout << bits_needed(2) << std::endl;
	std::cout << bits_needed(3) << std::endl;
	std::cout << bits_needed(4) << std::endl;
	std::cout << bits_needed(5) << std::endl;
	std::cout << bits_needed(6) << std::endl;
	std::cout << bits_needed(9) << std::endl;
	std::cout << bits_needed(128) << std::endl;
	std::cout << bits_needed(129) << std::endl;
	std::cout << bits_needed(1'000'000) << std::endl;


#endif

	printf("Huffman encoding");
	printf("\r\n");
	printf("kies uit volgende 2 opties:");
	printf("\r\n");
	printf("Hufman compress input ouput");
	printf("\r\n");
	printf("Hufman decompress input ouput");
	printf("\r\n");

	

	

	//checken of user wel 4 argumenten ingegeven heeft
	
		if (argumenten != 4) {
		printf("geef 4 argumenten aub");
		printf("\r\n");
		}
	
	
		//huffman compress/decompress x y

	//source en desination maken
	//zie files.h/cpp
	//x en y
	auto inputstream = io::create_file_data_source(args[2]);
	auto outputstream = io::create_file_data_destination(args[3]);

	
	//aanmaken van huffmanencoding
	auto huffman = encoding::huffman::huffman_encoding<257>();
	
	//aanmaken van eof encoding
	auto eofencoding = encoding::eof_encoding<256>();
	//de groepjes
	auto groupsEncoding = encoding::bit_grouper<8>();

	//samengezet
	auto totaalpaket = eofencoding | huffman | groupsEncoding;
	

	
	
	//command uit lezen
	if (args[1] == std::string("compress")) {
		totaalpaket->encode(*inputstream->create_input_stream(), *outputstream->create_output_stream());
	}if (args[1] == std::string("decompress")) {
		totaalpaket->decode(*inputstream->create_input_stream(), *outputstream->create_output_stream());
	}
	else
	{
		printf("compress of decompress als 2de argument aub");
	}
	
	
	

}



#endif