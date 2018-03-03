#include "EncryptionAlgTest.h"

void EncryptionAlgTest::start() {
    before();
    std::for_each(m_lengths.begin(), m_lengths.end(), [this](int &length) {

        /* Initializing variables */
        auto message = new signed char[length];
        auto key = new signed char[16];
        auto cipher = new signed char[length];
        auto decryptedMessage = new signed char[length];
        generate(message, length);
        generate(key, 16);

        /* Main testing */
        enc_function(key, message, cipher, length);
        dec_function(key, cipher, decryptedMessage, length);

        for (int i = 0; i < length; i++) {
            if (message[i] != decryptedMessage[i]) {
                std::cout << "Length: " << length << std::endl;
                std::cout << "Number of wrong symbol: " << i << std::endl;
                std::cout << "Source symbol: " << message[i] << std::endl;
                std::cout << "Decrypted symbol: " << decryptedMessage[i] << std::endl;

                break;
            }
        }

        /* Freeing memory */
        delete message;
        delete key;
        delete cipher;
        delete decryptedMessage;
    });
    after();
}

void EncryptionAlgTest::before() {

}

void EncryptionAlgTest::after() {

}

EncryptionAlgTest::EncryptionAlgTest(const IAlgorithmicTest::TestFunction &m_enc_function,
                                     const IAlgorithmicTest::TestFunction &m_dec_function) : IAlgorithmicTest(
        m_enc_function, m_dec_function) {
    m_lengths = std::vector<int>(31);
    static int i = 1;
    std::generate(m_lengths.begin(), m_lengths.end(), [] { return i++; });
}


EncryptionAlgTest::~EncryptionAlgTest() = default;