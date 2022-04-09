#include "SongDatabase.h"

///
/// @public
/// @brief default constructor
/// 
/// inializes m_longestArtistNameLen to 0
///
SongDatabase::SongDatabase() : m_longestArtistNameLen(0)
{}

///
/// @public
/// @brief adds a artist and their songs  to the database
/// 
/// If the artist exists in the database then 
///		adds the songlist passed to their songlist
/// 
/// @param a_artistName name of the artist 
/// @param a_artistSongList refernce to vector containing name of the songs to add to database
/// 
void SongDatabase::AddToDatabase(std::string a_artistName, const songVec& a_artistSongList)
{
	// set artist Max length if the artist name is hight than currmax
	m_longestArtistNameLen = m_longestArtistNameLen < a_artistName.length() ? a_artistName.length() : m_longestArtistNameLen;

	m_database.insert(std::pair<std::string, songVec>(a_artistName, a_artistSongList));
	SortArtistSong(a_artistName);
}

///
/// @public
/// @brief adds a artist and their songs  to the database
/// 
/// If the artist exists in the database then 
///		adds the songlist passed to their songlist
/// 
/// @param a_artistName name of the artist
/// @param a_artistSongList refernce to initializer_list containing name of the songs to add to database 
/// 
void SongDatabase::AddToDatabase(std::string a_artistName, const std::initializer_list<std::string>& a_artistSongList)
{
	if(!CheckArtistExist(a_artistName))
	{
		// artist not found in the database; adding to database
		songVec songList = a_artistSongList;
		AddToDatabase(a_artistName, songList);
	}
	else
	{
		// artist exists in the database
		AddSongToAlreadyExistingArtist(a_artistName, a_artistName);
	}
}

///
/// @public
/// @brief adds a artist and their song to the database
/// 
/// If the artist exists in the database then 
///		adds the song passed to their songlist
/// 
/// @param a_artistName name of the artist 
/// @param a_artistSong name of the songs to add to database
void SongDatabase::AddToDatabase(std::string a_artistName, std::string a_artistSong)
{
	if(!CheckArtistExist(a_artistName))
	{
		AddToDatabase(a_artistName, { a_artistSong });
	}
	else
	{
		// artist exists in the database
		AddSongToAlreadyExistingArtist(a_artistName, a_artistSong);
	}
}

/// 
/// @public
/// @brief asks the users to enter a keyword and display all 
///		the songs with their artist that matches the keyword.
/// 
/// If the keyword matches is found in a artist name then 
///		all their songs are displayed. But if a keyword matches
///		a song then only that song and its artist is displayed. 
///		It does not display other song that the artist may have
/// 
/// @waring this runs in a infinite loop and only way to exit the 
///		loop is by typing "-exit" as a keyword
/// 
void SongDatabase::UserSearch() const
{
	// ask user for keyword and do a search
	for(;;)
	{
		std::cout << std::endl;
		std::cout << "Please enter a keyword to search or enter \"-exit\" to stop searching: " << std::endl;

		std::string keyword;
		std::cin >> keyword;

		// checking if -exit command was passed
		if(keyword == "-exit")
		{
			break;
		}

		std::vector<artistSongNamePair> result;
		Search(keyword, result);

		// printing the results
		PrintSearchResults(result);

		// cleaning the vector
		result.clear();

		std::cout << std::endl;
	}
}

/// 
/// @public
/// @brief Prints the whole database
/// 
void SongDatabase::PrintDatabase() const
{
	unsigned width = m_longestArtistNameLen + 5;

	std::cout << std::setw(width) << std::left
		<< "Artist" << "Song Name" << std::endl;
	std::cout << std::setw(width) << std::left
		<< "------" << "---------" << std::endl;

	// printing the list for each artist
	for(const auto& kv : m_database)
	{
		auto tempIte = kv.second.begin();

		while(tempIte != kv.second.end())
		{
			std::cout << std::setw(width) << std::left
				<< kv.first << *tempIte << std::endl;
			++tempIte;
		}
	}
}

/// 
/// @public
/// @brief Prints all the unique songs name in alphabetical order 
///		while also printing how many time the song name was seen
///		in the database.
/// 
/// @note It does not print the artist name. 
/// 
void SongDatabase::PrintInSongAlphabeticalOrder() const
{
	// case insensitive map
	std::map<std::string, int, CaseInsensetive::Comparator> sortedSongList;
	unsigned longestSongNameLen = 0;

	// adding the songs to the list
	for(const auto kv : m_database)
	{
		for(const auto song : kv.second)
		{
			// checking if the songName is already in the sortedSongList
			auto findResult = sortedSongList.find(song);
			if(findResult != sortedSongList.end())
			{
				// match found; increasing the count
				++findResult->second;
			}
			else
			{
				// adding the song to the list
				sortedSongList[ song ] = 1;
				longestSongNameLen = longestSongNameLen < song.length() ? song.length() : longestSongNameLen;

			}
		}
	}

	// printing the song list
	std::cout << std::endl;
	std::cout << "List of all the unique songs name alphabetically arranged:" << std::endl;

	unsigned width = longestSongNameLen + 5;

	std::cout << std::setw(width) << std::left
		<< "Song Name" << "frequency" << std::endl;
	std::cout << std::setw(width) << std::left
		<< "---------" << "---------" << std::endl;

	// updating the width so that the frequency comes in the middle
	width += 4;

	// printing the list
	for(const auto& songWithFreqPair : sortedSongList)
	{
		std::cout << std::setw(width) << std::left
			<< songWithFreqPair.first << songWithFreqPair.second << std::endl;
	}

}

///
/// @private
/// @brief Checks if the artist already exists in the database or not
/// 
/// @param a_artistName artist name to search in the database 
/// 
/// @return if the artist exist in the database it returns true; 
///		returns false
/// 
bool SongDatabase::CheckArtistExist(std::string a_artistName) const
{
	auto artistFindResult = m_database.find(a_artistName);

	return artistFindResult != m_database.end();
}

///
/// @private
/// @brief Checks if the artist's song already exists in the database or not
/// 
/// It checks in the artist's list. 
/// 
/// @param a_artistName name of the artist whose song is being searched in the database 
/// @param a_artistSong song name to search in the database  
/// 
///  @return if the artist's exist in their list it returns true; 
///		returns false
/// 
bool SongDatabase::CheckArtistSongExits(const std::string& a_artistName, const std::string& a_artistSong) const
{
	std::string artistSong(a_artistSong.length(), ' ');
	std::transform(a_artistSong.begin(), a_artistSong.end(), artistSong.begin(), std::tolower);

	// get the artist's songList
	const songVec artistSongList = m_database.find(a_artistName)->second;

	// checking if the song is in the list
	for(std::string song : artistSongList)
	{
		std::transform(song.begin(), song.end(), song.begin(), std::tolower);

		if(song == artistSong)
		{
			return true; // song found
		}

	}

	return  false; // song not found
}

/// 
/// @private
/// @brief sorts artists song in alphabetical order
/// 
/// @param a_artistName name of the artist whose song list is to be sorted
/// 
void SongDatabase::SortArtistSong(std::string a_artistName)
{
	std::sort(m_database[ a_artistName ].begin(), m_database[ a_artistName ].end());
}

/// 
/// @private
/// @brief searches the database for the keyword
/// 
/// If the keyword matches is found in a artist name then
///		all their songs are added to the a_result vector.
///		 But if a keyword matches a song then only that song 
///		and its artist is added to the a_result vector.
/// 
/// @param a_keyWord keyword that is used to search the database
/// @param a_result reference to a vector where the successful 
///		matches are stored.
/// 
void SongDatabase::Search(std::string a_keyWord, std::vector<artistSongNamePair>& a_result) const
{
	// converting the a_keyWord to lowercase
	std::transform(a_keyWord.begin(), a_keyWord.end(), a_keyWord.begin(), tolower);

	for(const auto& keyValuePair : m_database)
	{
		// converting the artist name to lowercase
		std::string artistName = keyValuePair.first;
		std::transform(artistName.begin(), artistName.end(), artistName.begin(), tolower);

		// looking for the keyword in the artists
		if(artistName.find(a_keyWord) != std::string::npos)
		{
			// match found; pushing all the artist song to the result
			auto tempIte = keyValuePair.second.begin();

			while(tempIte != keyValuePair.second.end())
			{
				a_result.push_back(artistSongNamePair{ keyValuePair.first, *tempIte });
				++tempIte;
			}

		}
		else
		{
			// looking for the keyword in artist's song
			auto tempIte = keyValuePair.second.begin();

			while(tempIte != keyValuePair.second.end())
			{
				// converitng the song to lowercase
				std::string currSong = *tempIte;
				std::transform(currSong.begin(), currSong.end(), currSong.begin(), tolower);

				if(( currSong ).find(a_keyWord) != std::string::npos)
				{
					// match found; pushing the artist and song to the search result
					a_result.push_back(artistSongNamePair{ keyValuePair.first, *tempIte });
				}
				++tempIte;
			}
		}
	}
}

/// 
/// @private
/// @brief Prints the successful search result
/// 
/// @param a_result reference to a vector where the successful 
///		matches that Search() funciton found are stored.
/// 
void SongDatabase::PrintSearchResults(const std::vector<artistSongNamePair>& a_result) const
{
	std::cout << std::endl;

	// checking if match found or not
	if(a_result.empty())
	{
		std::cout << "No Match Found!!!!!" << std::endl;
		return;
	}

	std::cout << "Below is your search result" << std::endl;

	unsigned width = m_longestArtistNameLen + 5;

	std::cout << std::setw(width) << std::left
		<< "Artist" << "Song Name" << std::endl;
	std::cout << std::setw(width) << std::left
		<< "------" << "---------" << std::endl;

	// printing the list
	for(const artistSongNamePair& pair : a_result)
	{
		std::cout << std::setw(width) << std::left
			<< pair.first << pair.second << std::endl;
	}
}

/// 
/// @private
/// @brief Adds a song to a artist who alreday is in the database
/// 
/// @note Assumes that the artist exists in the database
/// 
/// @param a_artistName name of the artist who is already exists in the database
/// @param a_artistSong name of the songs to be add to database
/// 
void SongDatabase::AddSongToAlreadyExistingArtist(std::string a_artistName, std::string a_artistSong)
{
	// check if the songExist for the artist
	bool songExist = CheckArtistSongExits(a_artistName, a_artistSong);

	// if false add to the their list
	if(!songExist)
	{
		m_database[ a_artistName ].push_back(a_artistSong);
		SortArtistSong(a_artistName); // sorting the vector after inserting
	}

}

/// 
/// @private
/// @brief Adds a song to a artist who alreday is in the database
/// 
/// @note Assumes that the artist exists in the database
/// 
/// @param a_artistName name of the artist who is already exists in the database
/// @param a_artistSongList refernce to vector containing name of the songs to add to database
/// 
void SongDatabase::AddSongToAlreadyExistingArtist(std::string a_artistName, const songVec& a_artistSongList)
{
	// add each element to the list
	for(auto song : a_artistSongList)
	{
		AddSongToAlreadyExistingArtist(a_artistName, song);
	}
}

/// 
/// @private
/// @brief Adds a song to a artist who alreday is in the database
/// 
/// @note Assumes that the artist exists in the database
/// 
/// @param a_artistName name of the artist who is already exists in the database
/// @param a_artistSongList refernce to initializer_list containing name of the songs to add to database 
/// 
void SongDatabase::AddSongToAlreadyExistingArtist(std::string a_artistName, const std::initializer_list<std::string>& a_artistSongList)
{
	// add each element to the list
	for(auto song : a_artistSongList)
	{
		AddSongToAlreadyExistingArtist(a_artistName, song);
	}
}
