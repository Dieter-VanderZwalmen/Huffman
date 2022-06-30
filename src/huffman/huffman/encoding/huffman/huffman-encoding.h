//geen idee waarom er in de guide niets staat over een header file
// maar het lijkt mij wel logischer om er een te maken
// en niemand houdt me tegen

//er wordt even later wel gezegd om een header file te maken
//dit zorgt er voor dat je je methodes kan testen
//anders zijn ze verborgen in de cpp file

//deze file bevat dus gewoon alle methdoes zonder implementatie.


#ifndef HUFFMAN_ENCODING_H
#define HUFFMAN_ENCODING_H

#include "encoding/encoding.h"
#include "tree-encoding.h"
#include "data/FrequencyTable.h"
#include "data/binary-tree.h"
#include <algorithm>
#include <functional>



namespace encoding
{
	namespace huffman
	{
		std::shared_ptr<encoding::EncodingImplementation> createHuffmanEncodingImplementation(const u64 domain_size);

		template<u64 n>
		encoding::Encoding<n, 2> huffman_encoding() {
			return encoding::Encoding<n, 2>(createHuffmanEncodingImplementation(n));
		}

		std::vector<Datum> copy_to_vector(io::InputStream& input);
		std::unique_ptr<data::Node<std::pair<Datum, unsigned>>> build_tree(data::FrequencyTable<Datum> datums);
		unsigned weight(const data::Node<std::pair<Datum, unsigned>>& node);
		void build_tree_codes(const data::Node<std::pair<Datum, unsigned>>& tree, std::vector<Datum> datums, std::map<Datum, std::vector<Datum>>& map);

		std::map<Datum, std::vector<Datum>> build_codes(const data::Node<std::pair<Datum, unsigned>>& tree);

		Datum decode_datum(io::InputStream& input, const data::Node<Datum>& datums);
	}
}


#endif 
