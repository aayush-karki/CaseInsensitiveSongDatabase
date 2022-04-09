# Case Insensitive Song Database
Case insensetive database to store names of a artist and thier songs.

It is a console-based program.

Has the following methods implemented:
 - can add artist and their song to the database
 -  can print the database
 -  can print all the unique songs names in the database regardless of their artist.
 -  can search the database for keywords. 

-------------------------------------------------------------------------------------------
## Populating the database

When populating the database, if the artist exist in the database then the song is 
added to the already existing artist list. Furthermore for each artist only unique songs 
are added. That is, if different artists have same song title than they are both added to 
the artist's respective song list; but if the a artist have two songs with same name then only 
one of them is added to the artist's song list.

```c++
// same song name  but y is lowecased; does not get added 
SongDatabase.AddToDatabase("Lil Wayne", "In Your Face");
SongDatabase.AddToDatabase("Lil Wayne", "In your Face"); 

SongDatabase.AddToDatabase("Neil Diamond", "In Your Face");
// same artist name  but d is lowecased; does not get added
SongDatabase.AddToDatabase("Neil diamond", "In Your Face"); 
// same song name  but our is lowecased; does not get added
SongDatabase.AddToDatabase("Neil Diamond", "In YOUR Face");

// "One Kiss", and "1 kiss" are different names so they are both added
SongDatabase.AddToDatabase("Butch Hancock", { "Already Gone", "One Kiss", "1 kiss"}); 

// "King for a Day" is only added once
SongDatabase.AddToDatabase("Chaos UK", { "Victimized", "King for a Day", "King for a DAy" }); 
```

There is only one way to populate the database--by using the AddToDatabase. It takes two parameter:
artistName, and artistSongs. But it is overloaded to accept a vector list, initializer list, 
or a string as a second parameter. Below is the signatures of the funciton.

```c++
void AddToDatabase(std::string a_artistName, const std::vector<std::string>& a_artistSongList);
void AddToDatabase(std::string a_artistName, const std::initializer_list < std::string >& a_artistSongList);
void AddToDatabase(std::string a_artistName, std::string a_artistSong);
```

#### Sample code for Populating the database
```c++
std::vector<std::string> artistSongList;
// adding songs using vector to add artist with multiple songs
artistSongList.push_back("True Self");
artistSongList.push_back("In Your Face");
SongDatabase.AddToDatabase("Spitboy", artistSongList);

//clearing the vector to add in new artist and their songs
artistSongList.clear();

// for Lil Wayne
SongDatabase.AddToDatabase("Lil Wayne", "In Your Face");
// song name is same but y is lowecased; does not get added 
SongDatabase.AddToDatabase("Lil Wayne", "In your Face"); 


SongDatabase.AddToDatabase("Neil Diamond", "In Your Face");
// same artist name  but d is lowecased; does not get added
SongDatabase.AddToDatabase("Neil diamond", "In Your Face"); 
// same song name  but our is lowecased; does not get added
SongDatabase.AddToDatabase("Neil Diamond", "In YOUR Face"); 

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

// for Butch Hancock
// "One Kiss", and "1 kiss" are different names so they are both added
SongDatabase.AddToDatabase("Butch Hancock", { "Already Gone", "One Kiss", "1 kiss"}); 

// for Chaos UK
// "King for a Day" is only added once
SongDatabase.AddToDatabase("Chaos UK", { "Victimized", "King for a Day", "King for a DAy" }); 
```
## Printing the database
There are two ways to print the data base. First method is to print the whole database by calling the 
<code>PrintDatabase()</code>. And second is to print only the unique songs in the database by calling the 
<code>PrintInSongAlphabeticalOrder()</code>.
 
#### <code>PrintDatabase()</code>
It prints the following when [sample code to populate the database is used](#Sample-code-for-Populating-the-database).
<p align="center">
  <img src="https://user-images.githubusercontent.com/68620206/162557526-4052de8c-bcb7-4b7f-accd-8fc764052661.png" 
       alt="result of PrintDatabase() function") 
</p>
  
#### <code>PrintInSongAlphabeticalOrder()</code>
It prints the following when [sample code to populate the database is used](#Sample-code-for-Populating-the-database).
<p align="center">
  <img src="https://user-images.githubusercontent.com/68620206/162557872-0716cdce-50f8-4031-8062-d0bf2eac4678.png" 
       alt="result of PrintInSongAlphabeticalOrder() function") 
</p>

## Search the database for a keyword
#### <code>UserSearch()</code>
 
 This funciton promts the user for a keyword and searches the database and then displays all 
 the songs with their artist that matches the keyword.

If the keyword matches is found in a artist name then all their songs are displayed. 
But if a keyword matches a song then only that song and its artist is displayed. 
It does not display other song that the artist may have 
  
**Note:** this runs in a infinite loop and only way to exit the loop is by typing "-exit" as a keyword
  
It prints the following when [sample code to populate the database is used](#Sample-code-for-Populating-the-database) 
and the keyword entered is "ub"
<p align="center">
  <img src="https://user-images.githubusercontent.com/68620206/162558623-2b3f0e1e-47d8-42a0-b69c-a13b0003a428.png" 
       alt="result of UserSearch() function and &quotub&quot is used as a keyword") 
<img>
</p>

It prints the the keyword entered is "a"
<p align="center">
  <img src="https://user-images.githubusercontent.com/68620206/162558522-b3d70af1-6786-44a8-ab91-1cbaabfffa5d.png" 
       alt="result of UserSearch() function and &quota&quot is used as a keyword") 
<img>
</p>

Entering "-exit" as a keyword returns from the funciton. 
<p align="center">
  <img src="https://user-images.githubusercontent.com/68620206/162558594-10693d55-aaf8-430c-8274-62b7c95972be.png" 
       alt="result of UserSearch() function and &quot-exit&quot is used as a keyword") 
<img>
</p>


