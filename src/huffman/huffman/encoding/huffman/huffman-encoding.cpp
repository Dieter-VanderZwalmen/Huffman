
#include "huffman-encoding.h"

namespace
{
	//superclass EncodingImplementation
	class HuffmanEncodingImplementation : public encoding::EncodingImplementation
	{
		u64 group_size;
	public:
		HuffmanEncodingImplementation(u64 group_size) :group_size(group_size) {};
		//~HuffmanEncodingImplementation(); //geen deconstructor nodig


		//overschrijven van encode en decode
		void encode(io::InputStream& input, io::OutputStream& output) override
		{
			//alle data in een vector steken
			std::vector<Datum> datums = encoding::huffman::copy_to_vector(input);
			//alle frequenties tellen
			data::FrequencyTable<Datum>& frequencies = data::count_frequencies(datums);


			//als je weldegelijk data hebt
			if (frequencies.values().size() != 0)
			{
				//hulp variabele tree
				auto temp_tree = encoding::huffman::build_tree(frequencies);
				//een map van alle codes
				auto map = encoding::huffman::build_codes(*temp_tree);

				//onze echte tree
				//																	//[] is lambda hier staat eigenlijk gewoon (parameters) {functie}
				auto tree = data::map<std::pair<Datum, unsigned>, Datum>(*temp_tree, [](const std::pair<Datum, unsigned>& pair) {return pair.first; });
				//hoeveel bits hebben wij nodig?
				auto bits = bits_needed(group_size);


				encoding::huffman::encode_tree(*tree, bits, output);

				for (unsigned i = 0; i < datums.size(); i++)
				{
					auto& var = map[datums[i]];

					for (unsigned j = 0; j < var.size(); j++)
					{
						io::write_bits(var[j], 1, output);
					}
				}
			}
		};




		void decode(io::InputStream& input, io::OutputStream& output) override {
			auto bits = bits_needed(group_size);
			auto tree = encoding::huffman::decode_tree(bits, input);

			const data::Leaf<Datum>* leaf = dynamic_cast<const data::Leaf<Datum>*>(&(*tree));
			if (leaf == nullptr)
			{
				while (!input.end_reached())
				{
					Datum datum = encoding::huffman::decode_datum(input, *tree);
					output.write(datum);
				}
			}
			else
			{
				while (!input.end_reached())
				{
					input.read();
					output.write(leaf->get_leaf());
				}
			}

		};


	private:

	};


}



namespace encoding
{
	namespace huffman
	{
		std::shared_ptr<encoding::EncodingImplementation> createHuffmanEncodingImplementation(const u64 domain_size) {
			return std::make_shared<HuffmanEncodingImplementation>(domain_size);
		}

		//er wordt gezegd dat dit(copy_to_vector) in een aparte file zou moeten maar dit lijkt mij overzichtelijker.
		
		//Write a function copy_to_vector that takes an InputStream and copies all data into a std::vector.
		// 
		//de data omzetten naar een vector aangezien we 2 keer door de data moeten kunnen
		std::vector<Datum> copy_to_vector(io::InputStream& input) {
			//aanmaken van ons resultaat
			std::vector<Datum> datums;//data lijkt mij niet de beste naam

			//zolang we nog niet aan het einde zitten
			while (!input.end_reached())
			{
				//"push_back adds a new element at the end of the vector"
				datums.push_back(input.read());
			}

			//return
			return datums;

		}


		//extra herhaling: unique_ptr " is a smart pointer that owns and manages another object through a pointer

		//tree opbouwen
		//todo kan de parameter niet beter?
		//  "It is a large object." && It needs no modifications.&& No ownership transfer is necessary.
		//const en objectType&?

		std::unique_ptr<data::Node<std::pair<Datum, unsigned>>> build_tree(data::FrequencyTable<Datum> datums)
		{
			//1) we maken een variabelen nodes
			//2) deze steken we eerst vol
			//3) dan halen we deze "leeg" -> boom maken

			//1)
			//vector van pointer -> node bestaat uit een paar<Datum,unsigned>
			std::vector<std::unique_ptr<data::Node<std::pair<Datum, unsigned>>>> nodes;


			//2)
			//geeft vector van waarden
			//std::vector<Datum> values = datums.values();
			auto values = datums.values();

			//we gaan lopen over elke value
			//foreach loop
			for (Datum value : values)
			{
				//we maken een pair aan
				auto pair = std::pair<Datum, unsigned>(value, datums[value]);


				//we steken deze leaf dat bestaat uit een pair in nodes
				//extra herhaling: make_unique is zoals new maar de betere versie in c++
				nodes.push_back(std::make_unique<data::Leaf<std::pair<Datum, unsigned>>>(pair));
			}


			//3) je kan ook < en > overloaden in Node om zo de sort hier makkelijker te maken
			//https://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects

			while (nodes.size() > 1) {
				//std::sort(begin,einde,comparator) sorteert een lijst van het begin tot het einde

				//(begin,einde,comparator)
				//comparator = eerste node, tweede node {gewicht eerste > gewicht tweede}    DIT IS EEN LAMBDA
				std::sort(nodes.begin(), nodes.end(), [](const std::unique_ptr<data::Node<std::pair<Datum, unsigned>>>& first, const std::unique_ptr<data::Node<std::pair<Datum, unsigned>>>& second) {return weight(*first) > weight(*second); });

				//std::move is used to indicate that an object t may be "moved from", i.e. allowing the efficient transfer of resources from t to another
				//vector.back() Returns a reference to the last element in the vector
				auto first = std::move(nodes.back());
				//vector.pop_back Removes the last element in the vector
				nodes.pop_back();

				//nog is voor 2de element
				auto second = std::move(nodes.back());
				nodes.pop_back();


				//hier gaan we de moved gebruiken.
				//we maken een nieuwe branch en steken die in nodes
				std::unique_ptr<data::Branch<std::pair<Datum, unsigned>>> branch = std::make_unique<data::Branch<std::pair<Datum, unsigned>>>(std::move(first), std::move(second));
				nodes.push_back(std::move(branch));

			}

			//std::vector::front Returns a reference to the first element in the vector.
			//Unlike  vector::begin, which returns an iterator to this same element,

			return std::move(nodes.front());
		}


		//wat is gewicht?
		//nodig voor de comparator in  build_tree

		//we hebben een node (const)
		unsigned weight(const data::Node<std::pair<Datum, unsigned>>& node) {

			//we maken een leaf = cast van node naar leaf
			const data::Leaf<std::pair<Datum, unsigned>>* leaf = dynamic_cast<const data::Leaf<std::pair<Datum, unsigned>>*>(&node);


			//als dit lukt dan return je right_child
			//todo test dit nog een beetje voor de zekerheid (een leaf heeft namelijk 2 childeren)
			if (leaf != nullptr) {
				return leaf->get_leaf().second;
			}

			//anders? het is geen leaf -> het is een branch

			else {
				//Cast naar een branch
				const data::Branch<std::pair<Datum, unsigned>>* branch = dynamic_cast<const data::Branch<std::pair<Datum, unsigned>>*>(&node);


				//als dit gelukt is
				if (branch != nullptr) {
					//return de weight van linker +rechter kant
					return weight(branch->get_left_child()) + weight(branch->get_right_child());
				}
			}
			//als je hier geraakt is het geen leaf nog een branch
			return 0;
		}

		//het geven van een waarde aan elke datum
		void build_tree_codes(const data::Node<std::pair<Datum, unsigned>>& tree, std::vector<Datum> datums, std::map<Datum, std::vector<Datum>>& map)
		{
			//eerst kijken of tree een leaf is of niet
			const data::Leaf<std::pair<Datum, unsigned>>* leaf = dynamic_cast<const data::Leaf<std::pair<Datum, unsigned>>*>(&tree);

			//als je een leaf hebt
			if (leaf != nullptr)
			{
				map[leaf->get_leaf().first] = datums;
			}

			//als je geen leaf hebt
			else
			{
				//maak een branch aan = cast tree									//als een static cast faalt krijg je een compile error		=> we kunnen er vanuit gaan dat het een branch is 
				const data::Branch<std::pair<Datum, unsigned>>* branch = static_cast<const data::Branch<std::pair<Datum, unsigned>>*>(&tree);

				//links en rechts aanmaken
				std::vector<Datum> prefix_left = datums;
				std::vector<Datum> prefix_right = datums;

				//links en rechts waarde geven
				prefix_left.push_back(0);
				prefix_right.push_back(1);

				//build codes opnieuw oproepen (recursie)
				build_tree_codes((*branch).get_left_child(), prefix_left, map);
				build_tree_codes((*branch).get_right_child(), prefix_right, map);
			}

		}

		std::map<Datum, std::vector<Datum>> build_codes(const data::Node<std::pair<Datum, unsigned>>& node) {
			//een map van datum en vector van datum
			std::map<Datum, std::vector<Datum>> map;
			//een vector van datums
			std::vector<Datum> vector;
			//een leaf
			const data::Leaf<std::pair<Datum, unsigned>>* leaf = dynamic_cast<const data::Leaf<std::pair<Datum, unsigned>>*>(&node);


			//indien de leaf geen leaf is
			if (leaf == nullptr)
			{
				build_tree_codes(node, vector, map);
				return map;
			}
			//indien het wel een leaf is 
			else
			{
				vector.push_back(0);
				map[leaf->get_leaf().first] = vector;
				return map;
			}
		}







		Datum decode_datum(io::InputStream& input, const data::Node<Datum>& datums) {
			//aanmaken van een leaf
			const data::Leaf<Datum>* leaf = dynamic_cast<const data::Leaf<Datum>*>(&datums);


			//is het een leaf?
			if (leaf != nullptr) {
				//return de leaf
				auto var = leaf->get_leaf();
				return var;
			}
			//indien je al op het einde zit
			if (input.end_reached())
			{

				return 0;
			}

			//aangezien je weet dat het GEEN leaf is 
			//maak een branch aan
			const data::Branch<Datum>* branch = dynamic_cast<const data::Branch<Datum>*>(&datums);

			//lees 1 bit
			Datum bit = io::read_bits(1, input);

			//zolang uw branch effectief een branch is
			if (branch != nullptr)
			{
				//een 0 wordt gevolgd door 8bits
				if (bit == 0)
				{
					return decode_datum(input, branch->get_left_child());
				}
				//anders ga je dieper in de tree
				else
				{
					return decode_datum(input, branch->get_right_child());
				}
			}
			return 0;
		}




	}
}




