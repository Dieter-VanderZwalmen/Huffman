
#include "eof-encoding.h"
#include "encoding.h"





//anonymous namespace
//reden? we kunnen dezelfde functie naam 2 keer gebruiken in 2 verschillende namespaces (denk ik :) )
namespace
{


	class EofEncodingImplementation : public encoding::EncodingImplementation
	{
	public:
		EofEncodingImplementation(u64 domain_size) : domain_size(domain_size) {}



		void encode(io::InputStream& input, io::OutputStream& output) override {
			//zolang je niet aan het einde van de input zit
			//schijft naar de output 
			while (!input.end_reached())
			{
				output.write(input.read());
			}

			//waarom moet de domain_size ook weggeschreven worden?
			//dit is verwarrend
			//ZIE extra informatie onderaan de file
			output.write(domain_size);

		};

		void decode(io::InputStream& input, io::OutputStream& output) override {
			//zolang je niet aan het einde van de input zit
			//schijft naar de output 
			while (!input.end_reached())
			{

				//deze logica snap ik niet
				//opnieuw die domain_Size dat me in de war brengt
				//ZIE extra informatie onderaan de file
				Datum date = input.read();
				if (date != domain_size) {
					output.write(date);
				}
				else
				{
					return;
				}
			}

		
		};


	private:
		const u64 domain_size;
	};
	



}

std::shared_ptr<encoding::EncodingImplementation> encoding::create_eof_implementation(const u64 domain_size) 
{
	return std::make_shared<EofEncodingImplementation>(domain_size);
}



//EXTRA INFORMATIE
// http://pvm.leone.ucll.be/huffman/implementation/eof-encoding.html
//The EOF encoding needs to add an extra symbol.For example, 
//if its input stream has domain size 16, it should add a 17th symbol.In our example, we had domain size 256, 
//making EOF the 257th symbol.However, there is no reason our implementation of EOF encoding should make any assumptions about the domain size of its input.Instead
//, it should be told what it is by its creator.