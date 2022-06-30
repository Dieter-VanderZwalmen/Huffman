#ifndef ENCODING_H
#define ENCODING_H

#include <iostream>
#include "io/binary-io.h"
#include "io/memory-buffer.h"
#include "io/files.h"

namespace encoding
{

	class EncodingImplementation 
	{
	public:
		//deconstructor
		virtual ~EncodingImplementation() {}
		//virtual zorgt dat het overschreven kan worden
		virtual void encode(io::InputStream& in, io::OutputStream& out) {}
		virtual void decode(io::InputStream& in, io::OutputStream& out) {}
	};



	template<u64 IN, u64 OUT>
	class Encoding {
		// keep a raw EncodingImplementation object: ... some sort of pointer/reference must be used.
		std::shared_ptr<EncodingImplementation> encoding;


	public: 
		//constructor
		//met parameter encoding 
		//std::move het verplaatsen van object (al verklaard geweest)
		Encoding(std::shared_ptr<EncodingImplementation> encoding) :encoding(std::move(encoding)) {}


		//operator overloading ->
		//encoding.implementation()->encode(input, output);
		//wordt
		//encoding->encode(input, output);

		//const versie
		const std::shared_ptr<EncodingImplementation>& operator ->() const {
			return encoding;
		};

		//non const versie
		std::shared_ptr<EncodingImplementation>& operator ->() {
			return encoding;
		};

		



	};


	template<u64 IN, u64 OUT>
	void encode(io::DataSource<IN> source, Encoding<IN, OUT> encoding, io::DataDestination<OUT> destination) {
		encoding->encode(*source->create_input_stream(), *destination->create_output_stream());
	};

	template<u64 IN, u64 OUT>
	void decode(io::DataSource<OUT> source, Encoding<IN, OUT> encoding, io::DataDestination<IN> destination) {
		encoding->decode(*source->create_input_stream(), *destination->create_output_stream());
	};

}
#endif