# Cipher machine with 5 rotors (256 characters - ASCII)

#### I don't test every edge case, so if you try to break, IT WILL BREAK =D.

#### How to use:

1. Compile:
  `gcc -std=c17 -pedantic -Wall -o rotor.exe rotor.c`

2. Run
   `./rotor mode n phrase1 phrase2 phrasen k1 l1 k2 l2 kn ln input output`

   - mode = C to Cipher or D to Decipher;
   - n = Quantity of rotors;
   - phrase1..n = Key phrase to initialize the current rotor;
   - k1..n = Number of ciphers that are necessary be made to rotate the current rotor;
   - l1..n = Number of positions that the rotor will be rotated at every k pos;
   - input = input file name (can be whatever: images, pdfs, videos, mp3, plaintext, or just binaries .bin);
   - output = Name of the output file to be created (if the mode is C, then the output is the ciphered content. Otherwise, the output is the deciphered content);

   ##### Example of usage with the example carta.txt file:   
   `.\rotor.exe C 5 GIROSCOPIO BAUNILHA FEIJAO ARROZ BATATA 1000000000 255 1 13 25 26 1 3 0 0 carta.txt carta.bin`

   `.\rotor.exe D 5 GIROSCOPIO BAUNILHA FEIJAO ARROZ BATATA 1000000000 255 1 13 25 26 1 3 0 0 carta.bin decodificado.txt`
   
#### To Do:
1. [ ] Refactor the code to split into more files and functions;
2. [ ] Improve README;
3. [ ] Comments;
4. [ ] Tests.
