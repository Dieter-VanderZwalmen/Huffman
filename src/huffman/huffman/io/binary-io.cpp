#include "binary-io.h"


namespace io
{

	//| bitswise or werkt op de volgende manier (als een vd twee 1 is krijg je 1)
	//stel je hebt
	//1001 0010
	//1111 0110
	//---------
	//1111 1110

	u64 read_bits(u64 nbits, io::InputStream& input)
	{
	
		u64 result = 0;

		for (unsigned x = 0; x < nbits; x++)
		{
	
			if (input.end_reached()) return result;
			else {
			// | is een bitwise or 
			//input.read() leest een byte
			//de bits van input.read worden met x naar links geschoven
			result = result | (input.read() << x);
			}
		}

	
		
		return result;

	}
	void write_bits(u64 value, u64 nbits, io::OutputStream& output)
	{
		u64 een = 1;

		for (unsigned x = 0; x < nbits; x++)
		{
			//& is een bitwise AND operator
			output.write((value & (een << x)) >> x);
		}
	}
}