#include "tree-encoding.h"

//herhaling: visuele representatie voor huffman tree
//hier zie je hoe het bouwen van een boom gaat
// https://youtu.be/dM6us854Jk0?t=130 (niet huffman boom)
//https://youtu.be/dM6us854Jk0?t=495 (de superieure huffman boom)

namespace encoding
{
    namespace huffman
    {
        //implementatie ENCODING (recursief); parameters(root van boom, number bits per datum,output stream)
        //datum = uint64_t aka een int
        void encode_tree(const data::Node<Datum>& root, unsigned bits_per_datum, io::OutputStream& output) {
            //neem de waarde van je root (leaf)
            const data::Leaf<Datum>* leaf = dynamic_cast<const data::Leaf<Datum>*>(&root);

            //als de knoop geen kinderen heeft
            //schrijf een 0
            //schrijf de waarde van je leaf

            //leaf == nullptr wnr het geen leaf is 
            //dus wnr je een leaf hebt doe het volgende
            if (leaf != nullptr) {
                io::write_bits(0, 1, output);
                io::write_bits(leaf->get_leaf(), bits_per_datum, output);
            }


            //als de knoop WEL kinderen heeft | als het geen leaf is
            else {
                //maak een branch aan ipv knoop
                const data::Branch<Datum>* branch = dynamic_cast<const data::Branch<Datum>*>(&root);

                //als deze branch niet null is
                if (branch != nullptr) {
                    //schrijf een 1 weg
                    io::write_bits(1, 1, output);
                    
                    //recursief heroproepen met linker en rechter kant van de knoop
                    //door gaan tot dat je een leaf hebt
                    encode_tree(branch->get_left_child(), bits_per_datum, output);
                    encode_tree(branch->get_right_child(), bits_per_datum, output);
                }
            }

        };



        //implementatie DECODING (recursief)


        std::unique_ptr<data::Node<Datum>> decode_tree(u64 bits_per_datum, io::InputStream& input) {

            // bij het tegenkomen van een 0 zijn de volgende bits een leaf
            if (io::read_bits(1, input) == 0) {
                return std::make_unique<data::Leaf<Datum>>(io::read_bits(bits_per_datum, input));
            }
            //anders roep je het L EN R kind van de branch op
            else {
                auto left_child = decode_tree(bits_per_datum, input);
                auto right_child = decode_tree(bits_per_datum, input);
                return std::make_unique<data::Branch<Datum>>(std::move(left_child), std::move(right_child));
            }
        }

    }
	
        
	
}


