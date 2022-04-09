#pragma once
#include <iostream> 
#include<map>
#include<string>
#include <vector>
#include <iomanip>
#include <algorithm>

///
/// @brief CaseInsensetive namespace so that it does not polute the code 
///
namespace CaseInsensetive
{
	// Comparator function to make a case insensentive map

	///
	/// @struct
	/// @brief Comparator is passed to the map as third argument when constructing a map
	///		so to make a case insensentive map
	///
	struct Comparator
	{
		/// 
		/// @brief overloading the () operator to compare two string
		/// 
		/// @param a_string1 string in map to compare with
		/// @param a_string2 string which is trying to be added to add to map
		/// @return true if a_string1 is less than a_string2; else returns false
		/// 
		bool operator() (const std::string& a_string1, const std::string& a_string2) const
		{
			// strings to store the transformed string 1 and string 2
			std::string string1(a_string1.length(), ' ');
			std::string string2(a_string2.length(), ' ');

			// converting the strings to lowercase
			std::transform(a_string1.begin(), a_string1.end(), string1.begin(), tolower);
			std::transform(a_string2.begin(), a_string2.end(), string2.begin(), tolower);

			return  string1 < string2;
		}
	};
}

/// 
/// @class SongDatabase "SongDatabase.h"
/// @brief Case insensetive database to store names of a artist and thier songs
/// 
class SongDatabase
{
#define songVec std::vector<std::string>
#define artistSongNamePair std::pair<std::string, std::string>

	// =============================== public member funciton ======================
public:
	SongDatabase(); // default constructor

	// add to database
	void AddToDatabase(std::string a_artistName, const songVec& a_artistSongList);
	void AddToDatabase(std::string a_artistName,
					   const std::initializer_list < std::string >& a_artistSongList);
	void AddToDatabase(std::string a_artistName, std::string a_artistSong);

	void UserSearch() const; // asks users to enter a keyword to search the database

	void PrintDatabase() const; // print the database

	// prints a unique song list albhabetically sorted
	// the characters are lowered cased
	void PrintInSongAlphabeticalOrder() const;

	// =============================== private member funciton ======================

	// checks if artist exist in the database; true if exist
	bool CheckArtistExist(std::string a_artistName) const;

	// check if the song exits in the database for that particular artist; true if exist
	// assumes that the artist already exist
	bool CheckArtistSongExits(const std::string& a_artistName, const std::string& a_artistSong) const;

	void SortArtistSong(std::string a_artistName); // sorts the artist song list

	// searching for keyword
	void Search(std::string a_keyWord, std::vector<artistSongNamePair>& a_result) const;// searches for the keyword
	void PrintSearchResults(const std::vector<artistSongNamePair>& a_result) const; // print searchResult

	// overloaded function to add song to existing artist
	void AddSongToAlreadyExistingArtist(std::string a_artistName, std::string a_artistSong);
	void AddSongToAlreadyExistingArtist(std::string a_artistName, const songVec& a_artistSongList);
	void AddSongToAlreadyExistingArtist(std::string a_artistName,
										const std::initializer_list < std::string >& a_artistSongList);

	// =============================== private data member === ======================
private:
	std::map<std::string, songVec, CaseInsensetive::Comparator> m_database;
	unsigned m_longestArtistNameLen; // used for formating
};

