
#ifndef TREE_ENCODING_H
#define TREE_ENCODING_H

#include <data/binary-tree.h>
#include <io/streams.h>

#include "util.h"
#include "data/binary-tree.h"
#include "io/binary-io.h"
#include "io/streams.h"
#include "io/memory-buffer.h"
#include "data/binary-tree.h"

namespace encoding
{
	namespace huffman
	{
		//zie tree-encoding.cpp vanboven staat een visuele representatie van de huffman boom

		void encode_tree(const data::Node<Datum>& root, unsigned bits_per_datum, io::OutputStream& output);

		//ik moet echt is vragen aan fredje waarom unique ptr gebruikt wordt (niet meer)
		//=>http://pvm.leone.ucll.be/huffman/implementation/parameter-types.html#_unique_ptrt_x hier uitgelegd
		std::unique_ptr<data::Node<Datum>> decode_tree(u64 bits_per_datum, io::InputStream& input);
	}
}
#endif