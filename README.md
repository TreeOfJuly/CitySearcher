SETUP TO RUN THE PROGRAM:
  -Have Arial.ttf and uscities.csv be placed in the cmake-build-debug.
  -Also, have SFML downloaded on your OS.
  -Add this to your CMakeLists.txt after creating it!
  *
  set(SFML_STATIC_LIBRARIES TRUE)
  set(SFML_DIR C:/SFML/lib/cmake/SFML) 
  **Set this to wherever your SFML folder is**
  find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
  
  include_directories(c:/SFML/include/SFML)
  **Set this to wherever your SFML folder is**
  target_link_libraries(-nameOfProject sfml-system sfml-window sfml-graphics sfml-audio)
  *
NOTES FOR RUNNING PROGRAM:
  -There will be a SFML-based GUI when first running the program and also a CLI after the SFML-based GUI. 
  -To access the CLI, you must simply just close the two windowss that will pop up during the SFML gui.
  -For both interfaces it is critical that the city is spelled correctly and the first letter of each word is capitalized. Another thing to note is that the punctuation associated with cities must be included.
  -To exit out of the CLI just exit out of the Command Prompt, Git Bash, Powershell, or whatever terminal you are using. There will also be a command to exit out of CLI.
  -There are several other things to note, one being that in the beginning of the CLI runtime, there will be a message that will show the results of the time it took to find all the cities in the csv files
   and you will notice that there is 0 seconds for the separate chaining portion and an average of 9 seconds for the linear search. The 0 seconds is not 0 seconds but actually an average of 80 miliseconds which is       rounded down.

We were told by a TA that using separate chaining and linear probing met the requirements:
![Project3Image](https://github.com/TreeOfJuly/CitySearcher/assets/166689388/01a64fff-3b1f-4695-a70c-56d91ba0096b)
