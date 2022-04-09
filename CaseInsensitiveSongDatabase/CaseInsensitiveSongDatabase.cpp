// CaseInsensitiveSongDatabase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SongDatabase.h"

int main()
{
	SongDatabase SongDatabasebase;

	std::vector<std::string> artistSongList;

	// =============== Populating the database ==============================

	// adding songs using vector to add artist with multiple songs
	artistSongList.push_back("True Self");
	artistSongList.push_back("In Your Face");
	SongDatabasebase.AddToDatabase("Spitboy", artistSongList);

	//clearing the vector to add in new artist and their songs
	artistSongList.clear();

	// for Lil Wayne
	SongDatabasebase.AddToDatabase("Lil Wayne", "In Your Face");
	SongDatabasebase.AddToDatabase("Lil Wayne", "In your Face"); // same song name  but y is lowecased; does not get added 

	SongDatabasebase.AddToDatabase("Neil Diamond", "In Your Face");
	SongDatabasebase.AddToDatabase("Neil diamond", "In Your Face"); // same artist name  but d is lowecased; does not get added
	SongDatabasebase.AddToDatabase("Neil Diamond", "In YOUR Face"); // same song name  but our is lowecased; does not get added

	// adding single song using strings
	SongDatabasebase.AddToDatabase("Incubus", "Admiration");
	SongDatabasebase.AddToDatabase("Johnboy", "Admiration");
	SongDatabasebase.AddToDatabase("Jawbreaker", "Kiss the Bottle");
	SongDatabasebase.AddToDatabase("Minor Threat", "Straight Edge");
	SongDatabasebase.AddToDatabase("Bikini Kill", "Rebel Girl");
	SongDatabasebase.AddToDatabase("MC 900 Foot Jesus", "Killer Inside Me");
	SongDatabasebase.AddToDatabase("Sonic Youth", "Kill Yr Idols");
	SongDatabasebase.AddToDatabase("Husker Du", "Eight Miles High");
	SongDatabasebase.AddToDatabase("The Clash", "Complete Control");

	// adding songs using inializer list for artists with multiple songs
	SongDatabasebase.AddToDatabase("Chaos UK", { "Victimized", "King for a Day" });
	SongDatabasebase.AddToDatabase("UB40", { "Johnny Too Bad", "Red Red Wine" });
	SongDatabasebase.AddToDatabase("Butch Hancock", { "One Kiss", "Already Gone" });

	// printing the whole database
	SongDatabasebase.PrintDatabase();

	SongDatabasebase.UserSearch();

	// printing all the songs in the database in alphabetical order
	SongDatabasebase.PrintInSongAlphabeticalOrder();

	return 0;
}