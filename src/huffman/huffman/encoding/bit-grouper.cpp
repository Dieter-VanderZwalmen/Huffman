#include "bit-grouper.h"
#include "encoding.h"

namespace
{
	//Do not be confused by the name Bit Grouper.
	//It groups bits into bytes when encoding.
	//It splits bytes into bits when decoding.

	class BitGrouperImplementation : public encoding::EncodingImplementation {
		//groupsize = which represents the number of bits it has to group together.
		u64 group_size;


	public:
		//constructor
		BitGrouperImplementation(u64 group_size) : group_size(group_size) {}

		
		void encode(io::InputStream& input, io::OutputStream& output) override {
			//zolang je niet op het einde bent
			//schrijf naar output (read_bits)
			while (!input.end_reached())
			{
				output.write(io::read_bits(group_size, input));
			}

		};
		void decode(io::InputStream& input, io::OutputStream& output) override {
			//zolang je niet op het einde bent
			//schrijf naar write_bits => output.write
			while (!input.end_reached())
			{
				io::write_bits(input.read(), group_size, output);

			}

		};
	private:



	};
}
//deze dient voor de header file
//waarom kan je niet direct naar BitGrouperImplementation gaan?
// =>anonymous namespace
std::shared_ptr<encoding::EncodingImplementation> encoding::create_bit_grouper_implementation(const u64 domain_size) {
	return std::make_shared<BitGrouperImplementation>(domain_size);
}