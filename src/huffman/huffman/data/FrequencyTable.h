#ifndef FREQUENCY_TABLE_H
#define FREQUENCY_TABLE_H

#include<vector>
#include<map>
namespace data
{
	template<typename T>
	class FrequencyTable
	{
	private:
		//unsigned omdat negatieve frequenties niet mogelijk zijn en er gevraagd wordt naar een datatype met zo groot mogelijk bereik
		std::map<T, unsigned> map;

	public:
		//const omdat T x niet mag aangepast worden (enkel read acces)
		//T& uitleg :This passes a reference to x. This means the function receives the address of x,
		void increment(const T& x) {
			//als het element niet in de map zit krijg je een map.end
			if (map.find(x) != map.end())									
			{
				map[x]++;
			}
			else
			{
				map[x] = 1;//indien niet gevonden gelijk stellen aan 1
			}
			
		}


		//[] overschrijven
		//de laatste const zorgt ervoor dat de methode const wordt
		//dit zorgt ervoor dat alle variabelen die onder this staan niet aangepast kunnen worden 
		const unsigned operator [] (const T& x) const 
		{
			if (map.find(x) != map.end())
			{
				return map.find(x)->second; 
				//x -> first geeft de key (bij maps)
				//x -> second geeft de value (bij maps)
				
			}
			else
			{
				return 0;
			}
		}

		//deze method is const omdat hij opnieuw geen waarden mag aanpassen
		//geeft alle keys
		std::vector<T> values() const {

			//LIJST van waarden
			std::vector<T> value;
			//voor elke pair

			for (const auto& pair : map) //https://stackoverflow.com/questions/26281979/c-loop-through-map hier staat waarom je .first gebruikt
			{
				//.push_back "Adds a new element at the end of the vector, after its current last element."
				value.push_back(pair.first);
			}
			return value;
		}

	protected:


	};

	
	//simpele functie dat de frequencies telt
	template<typename T>
	//& -> werken met refrences
	FrequencyTable<T>& count_frequencies(const std::vector<T>& values) 
	{
		auto map = new FrequencyTable<T>();//maak een result map aan

		for (auto i = 0; i < values.size(); i++) 
		{ 
			map->increment(values[i]);  //elke waarde dat je tegenkomt ++
		}
		return *map;					//return de map

	}
};

#endif
