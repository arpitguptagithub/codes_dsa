void writeCompressedData(string inputFilePath, unordered_map<char, string> &huffmanCodes, string outputFilePath) {
    // Open input file for reading
    ifstream inputFile(inputFilePath, ios::binary);
    inputFile.seekg(0, ios::end);
    int fileSize = inputFile.tellg();
    inputFile.seekg(0, ios::beg);

    // Write Huffman codes to output file
    ofstream outputFile(outputFilePath, ios::binary);
    for (auto pair : huffmanCodes) {
        char ch = pair.first;
        string code = pair.second;
        int codeLength = code.length();
        outputFile.write(reinterpret_cast<const char*>(&ch), sizeof(ch));
        outputFile.write(reinterpret_cast<const char*>(&codeLength), sizeof(codeLength));
        for (char bit : code) {
            outputFile.write(reinterpret_cast<const char*>(&bit), sizeof(bit));
        }
    }

    // Compress data using Huffman codes and write to output file
    int bitsWritten = 0;
    char byte = 0;
    int byteIndex = 7;
    for (int i = 0; i < fileSize; i++) {
        char ch = inputFile.get();
        string code = huffmanCodes[ch];
        for (char bit : code) {
            if (bit == '1') {
                byte |= (1 << byteIndex);
            }
            byteIndex--;
            if (byteIndex < 0) {
                outputFile.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
                byte = 0;
                byteIndex = 7;
                bitsWritten += 8;
            }
        }
    }
    if (byteIndex != 7) {
        outputFile.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
        bitsWritten += (7 - byteIndex);
    }
    inputFile.close();
    outputFile.close();

    cout << "Compressed file written to " << outputFilePath << endl;
    cout << "Original file size: " << fileSize << " bytes" << endl;
    cout << "Compressed file size: " << bitsWritten / 8 << " bytes" << endl;
}