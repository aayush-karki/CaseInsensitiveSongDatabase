// CaseInsensitiveSongDatabase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SongDatabase.h"

int main()
{
	SongDatabase SongDatabase;

	std::vector<std::string> artistSongList;

	// =============== Populating the database ==============================

	// adding songs using vector to add artist with multiple songs
	artistSongList.push_back("True Self");
	artistSongList.push_back("In Your Face");
	SongDatabase.AddToDatabase("Spitboy", artistSongList);

	//clearing the vector to add in new artist and their songs
	artistSongList.clear();

	// for Lil Wayne
	SongDatabase.AddToDatabase("Lil Wayne", "In Your Face");
	SongDatabase.AddToDatabase("Lil Wayne", "In your Face"); // same song name  but y is lowecased; does not get added 

	SongDatabase.AddToDatabase("Neil Diamond", "In Your Face");
	SongDatabase.AddToDatabase("Neil diamond", "In Your Face"); // same artist name  but d is lowecased; does not get added
	SongDatabase.AddToDatabase("Neil Diamond", "In YOUR Face"); // same song name  but our is lowecased; does not get added

	// adding single song using strings
	SongDatabase.AddToDatabase("Incubus", "Admiration");
	SongDatabase.AddToDatabase("Johnboy", "Admiration");
	SongDatabase.AddToDatabase("Jawbreaker", "Kiss the Bottle");
	SongDatabase.AddToDatabase("Minor Threat", "Straight Edge");
	SongDatabase.AddToDatabase("Bikini Kill", "Rebel Girl");
	SongDatabase.AddToDatabase("MC 900 Foot Jesus", "Killer Inside Me");
	SongDatabase.AddToDatabase("Sonic Youth", "Kill Yr Idols");
	SongDatabase.AddToDatabase("Husker Du", "Eight Miles High");
	SongDatabase.AddToDatabase("The Clash", "Complete Control");

	// adding songs using inializer list for artists with multiple songs
	SongDatabase.AddToDatabase("UB40", { "Johnny Too Bad", "Red Red Wine" });
	SongDatabase.AddToDatabase("Butch Hancock", { "Already Gone",
								   "One Kiss", "1 kiss" }); // "One Kiss", and "1 kiss" are different names so they are both added

	SongDatabase.AddToDatabase("Chaos UK", { "Victimized",
								   "King for a Day", "King for a DAy" }); // "King for a Day" is only added once

	// printing the whole database
	SongDatabase.PrintDatabase();

	SongDatabase.UserSearch();

	// printing all the songs in the database in alphabetical order
	SongDatabase.PrintInSongAlphabeticalOrder();

	return 0;
}