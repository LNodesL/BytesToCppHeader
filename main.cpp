#include <iostream>
#include <fstream>
#include <vector>

// Function to convert byte array back to original file
void testConversion(const std::vector<unsigned char>& data, const std::string& originalFileName) {
    std::string testFileName = "TEST-" + originalFileName;
    std::ofstream outputFile(testFileName, std::ios::binary);

    if (!outputFile.is_open()) {
        std::cerr << "Failed to create " << testFileName << std::endl;
        return;
    }

    for (auto byte : data) {
        outputFile.put(static_cast<char>(byte));
    }

    std::cout << "Test file created successfully: " << testFileName << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input.original> <output.h>" << std::endl;
        return 1;
    }

    std::ifstream originalFile(argv[1], std::ios::binary);
    if (!originalFile.is_open()) {
        std::cerr << "Failed to open " << argv[1] << std::endl;
        return 1;
    }

    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(originalFile), {});

    std::ofstream headerFile(argv[2]);
    if (!headerFile.is_open()) {
        std::cerr << "Failed to create " << argv[2] << std::endl;
        return 1;
    }

    headerFile << "#ifndef PAYLOAD_DATA_H\n#define PAYLOAD_DATA_H\n\n";
    headerFile << "unsigned char payloadData[] = {";
    for (size_t i = 0; i < buffer.size(); ++i) {
        headerFile << "0x" << std::hex << (int)buffer[i];
        if (i < buffer.size() - 1) headerFile << ", ";
        if ((i + 1) % 12 == 0) headerFile << "\n";
    }
    headerFile << "};\n\n";
    headerFile << "unsigned int payloadDataSize = sizeof(payloadData);\n\n";
    headerFile << "#endif // PAYLOAD_DATA_H\n";

    std::cout << "Conversion completed successfully." << std::endl;

    // Call test function to verify conversion integrity
    testConversion(buffer, argv[1]);

    return 0;
}
