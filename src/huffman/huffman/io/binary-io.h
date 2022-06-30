
#ifndef BINARY_IO_H
#define BINARY_IO_H

#include <io/streams.h>

namespace io
{
	//in de guide staat om unsigned te gebruiken
	//dit zorgde voor errors
	//dus ik heb hier u64 van gemaakt
	u64 read_bits(u64 nbits, io::InputStream& input);
	void write_bits(u64 value, u64 nbits, io::OutputStream& output);
}
#endif
