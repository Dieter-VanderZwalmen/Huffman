#ifndef ENCODING_COMBINER_H
#define ENCODING_COMBINER_H

#include "encoding.h"

/*
As explained earlier, we want to combine encodings using the following syntax:

Encoding<256, 2> huffman = huffman_encoding();
Encoding<2, 256> grouper = bit_grouper<8>();

Encoding<256, 256> combined = huffman | grouper;
In other words, an Encoding<256, 2> and an Encoding<2, 256> can be combined into a single Encoding<256, 256>



*/


namespace encoding
{

	template<u64 N1, u64 N2, u64 N3>
	//herhaling waarom we public gebruiken  https://www.programiz.com/cpp-programming/public-protected-private-inheritance
	//int kort door public blijft public public
	//bij private wordt alles private 
	class EncodingCombinerImplementation : public encoding::EncodingImplementation {
		//N1: The input domain size of e1.
		//N2: The output domain size of e1 which must be equal to the input domain size of e2.
		//N3 : The output domain size of e2
		// DUS huffman<n1,n2> grouper<n2, n3>
		Encoding<N1, N2> e1;
		Encoding<N2, N3> e2;
		io::MemoryBuffer<N2> encode_buffer;
		io::MemoryBuffer<N2> decode_buffer;
	
	
	
	public:
		//constructor(e1,e2)  huffman<n1,n2> grouper<n2, n3>
		EncodingCombinerImplementation(Encoding<N1, N2> e1, Encoding<N2, N3> e2) :e1(e1), e2(e2) {}

		//encode geef je altijd input en output
		void encode(io::InputStream& input, io::OutputStream& output) override {

			//de e1 is n1 = input domain size, n2 = output domain size
			e1->encode(input, *encode_buffer.destination()->create_output_stream());
			//de e2 is n1 = input domain size, n2 = output domain size
			e2->encode(*encode_buffer.source()->create_input_stream(), output);
		};

		//dit is exact hetzelfde enkel gebruik je hier decode ipv encode
		void decode(io::InputStream& input, io::OutputStream& output) override {
			e2->decode(input, *decode_buffer.destination()->create_output_stream());
			e1->decode(*decode_buffer.source()->create_input_stream(), output);
		};

		//herhaling:
		//de rede dat we *encode_buffer.source() doen is omdat 
		//"derefrences a pointer"
	};


	//enkel gemaakt voor de methode hieronder
	template<u64 N1, u64 N2, u64 N3>
	std::shared_ptr<encoding::EncodingImplementation> create_combining_implementation(Encoding<N1, N2> e1, Encoding<N2, N3> e2) {
		return std::make_shared<EncodingCombinerImplementation<N1, N2, N3>>(e1, e2);
	}


	//"Define operator |."
	//encoding | encoding een betekenis geven

	//zelfde template gebruiken
	template<u64 N1, u64 N2, u64 N3>
	//returned <n1, n3>  Encoding<256, 2>  | Encoding<2, 256> = Encoding<256, 256>
	//defineren van de operator |
	//parameters: 2 encodings
	Encoding<N1, N3> operator |(Encoding<N1, N2> e1, Encoding<N2, N3> e2) {
		//return een nieuwe encoding
		//m b v de create
		return Encoding<N1, N3>(encoding::create_combining_implementation<N1, N2, N3>(e1, e2));
	}


	
}





#endif