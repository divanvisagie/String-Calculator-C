# String-Calculator-C
The string calculator from the string kata problem done in C

After many years writing higher level languages I wanted to go back to the roots,
not just my roots but deeper, since I have previously worked with C++ and Objective-C
I wanted to go all the way to basics and deal with just plain C. 

The string calculator kata example I think is a perfect example of a problem that
can be solved in a simple way in C, yet it is complex enough to be interesting.
I am also familiar with the problem and have implemented it in other languages 
before so I can focus on the language and not the problem.

The reason I experiment with languages in the first place is to see the unique ways
they idiomaticly solve problems. I can then take lessons learned and apply them 
to other languages.

## Setup 
```sh
cmake .
```

Make the LSP less angry
```sh
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=YES .
```

### To run the unit tests:
```sh
make run_tests
```
To pull this template with git do a shallow clone and then detach the remote
```sh
git clone --depth 1
git remote rm origin
```
You can now use your own remote

