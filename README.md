# TERRY WELCOMES YOU

This is a depiction our friend Terry on a table. Here is how to see him:

- `chmod +x run.sh`
- run `run.sh`
- say hi to terry

Our program uses the assimp (https://github.com/assimp/assimp) library for importing terry's stl data to a generic format readable by native c++ via the importer.cc script, which is stored in terry.bin. Then, that data is read into our main program in terry.cc, and rendered in the opengl scene. We have tested it on the school computers to ensure that this method works, and it does. 

We have not included the assimp library because it is too large, so the importer.cc script will not work without assimp globally installed. But it is not necessary to run the program, as we have included the terry.bin file, which is the output of the importer.cc script. We have only included importer.cc for reference.
